
#include <idc.idc>
#include <functions.idc>

#define DEBUG
#define SHOW_CORRUPT
//#define SHOW_UPDATES
//#define DATA_CODE_REGS_FROM_CDL

static fread_str(handle, start, size) {
	auto i, ret = "";
	if(start != -1)
		fseek(handle, start, 0);
	for(i = 0; i < size; i++) ret = ret + fgetc(handle);
	return ret;
}

static cdl_chunk_search(handle, chunk, max) {
	auto name, size, len, i, ret = 0;
	while (ret == 0) {
		name = "";
		size = 0;
		len = fgetc(handle);								// get chunk name len
		name = fread_str(handle, -1, len);					// read chunk name
		size = readlong(handle, 0);							// read file size
		if(name != chunk) {
			fseek(handle, size, 1);							// read skip file
			max--;
			if(max == 0)
				ret = -1;
		} else {
			ret = ftell(handle);
			Message("\tFound:   \"%s\" (size %08x)\n\n",name, size);
		}
	}
	return ret;
}

static main(void) {
	auto cdlFileName, cdlFile, cdlFileOpened, idbFileName = GetIdbPath();
	auto i, j, cd, seg, segcounter = 0;
	auto segea, segeai, segorg, segsize, secondpass = 0;
	auto codelog = 0, datalog = 0, unusedlog = 0;
	auto opcode, optype, opvalue;
	auto banksnum = 0, curbank = -1, prebank = -1, preea = -1, bankflag = 0;
	auto prgset = BADADDR, switchptr = BADADDR, switchopc = -1;
	auto farcall_cnt = 0, switch_cnt = 0, param_cnt = 0;
	auto farcall_s = 0, switch_es = 0, param_s = 0;
	auto farcall_cnt_prev = 0, switch_cnt_prev = 0, param_cnt_prev = 0;
	auto cart_mode = -1;
	auto cdlROMOfs, cdlDirectPageOfs, cdlDataBankOfs;

	cdlFileName = substr(idbFileName, 0, strstr(idbFileName, ".idb")) + ".cdl";
	cdlFile = fopen(cdlFileName, "rb");
	if( cdlFile == 0 ) {
		cdlFileName = AskFile(0,"*.cdl","Choose a CDL-file Manually");
		cdlFile = fopen(cdlFileName, "rb");
	}
	if (cdlFile != 0) {
		auto cdlSignature = "", cdlType = "", cdlFiles=0;
		cdlSignature = fread_str(cdlFile, 1, 13);							// read signature
		cdlType = fread_str(cdlFile, 15, 15);								// read type
		cdlFiles = readlong(cdlFile, 0);									// read files count
		if ((cdlSignature == "BIZHAWK-CDL-2")&&(cdlType == "SNES           ")) {
			Message("CDL file opened succesfully.\n\tName:    \"%s\"\n\tVersion: \"%s\"\n\tType:    \"%s\"\n\tChunks:  %d\n", cdlFileName,cdlSignature,cdlType,cdlFiles);

			auto tmp_seek = ftell(cdlFile);
			cdlROMOfs = cdl_chunk_search(cdlFile, "CARTROM", cdlFiles);
			if(cdlROMOfs == -1) {
				Message("Can't find proper Data chunk\nStartig disassembly without CDL.\n", cdlFileName);
				cdlFileOpened = 0;
			} else
				cdlFileOpened = 1;
			fseek(cdlFile, tmp_seek, 0);
			cdlDirectPageOfs = cdl_chunk_search(cdlFile, "CARTROM-D", cdlFiles);
			fseek(cdlFile, tmp_seek, 0);
			cdlDataBankOfs = cdl_chunk_search(cdlFile, "CARTROM-DB", cdlFiles);

		} else {
			Message("CDL file not in SNES format (%s, %s)!\nStartig disassembly without CDL.\n", cdlSignature, cdlType);
			cdlFileOpened = 0;
		}
	} else {
		Message("Can't open CDL file: \"%s\"\nStartig disassembly without CDL.\n", cdlFileName);
		cdlFileOpened = 0;
	}

	if(SegByName(".80") != -1) {			// LoROM
		cart_mode = 0x80;
		segorg = 0x8000;
		segsize = 0x8000;
	} else if(SegByName(".C0") != -1) {		// HiROM
		cart_mode = 0xC0;
		segorg = 0x0000;
		segsize = 0x10000;
	} else
		Message("Unknown Cart Type!\n");

	while (SegByName(form(".%02X",cart_mode|banksnum)) != -1) {banksnum++;}

	Message("Total Banks: %d\n", banksnum);

	while (segcounter < banksnum) {
		auto segname = form(".%02X",cart_mode|segcounter);
		seg = SegByName(segname);
		segea = SegByBase(seg);

		if(secondpass==0) {
#ifdef DEBUG
			Message("DEBUG: name='.%02X', SegByName=%02X, SegByBase=0x%08X cdlpos=%08X\n",cart_mode|segcounter, seg, segea, cdlROMOfs);
#endif
			Message("Seg %s start pass %d", segname, secondpass);
		}
		else
			Message(" %d", secondpass);

		i = 0;
		auto last_seg_B = -1;

//	work here
		do {
			segeai = segea + i;
			if(secondpass == 0) {
				// FIRST PASS START
				if(cdlFileOpened == 1) {
					fseek(cdlFile, cdlROMOfs + i, 0);
					cd = fgetc(cdlFile);
				} else
					cd = 0;

				auto update = "";

#ifdef SHOW_UPDATES
				auto tmpcmt = CommentEx(segeai,0);
				if((tmpcmt[0]=="-") || (strstr(tmpcmt,"   -") != -1)) {
					MakeComm(segeai, "");
					update = "new ";
				}
#else
				MakeComm(segeai, "");
#endif

//				if (cd) cmt = form("cdl: %02X [ ", cd);

				auto DS,D,B,x,m;

				if(cd & 1) {

					x = (cd >> 4) & 1;
					m = (cd >> 5) & 1;

#ifdef DATA_CODE_REGS_FROM_CDL
					SetReg(segeai, "i", x);
					SetReg(segeai, "m", m);
#endif

// CHOOSE WISELY!
//					SetReg(segeai, "B", cart_mode|segcounter);
//					SetReg(segeai, "B", 0x7E);
//					SetReg(segeai, "D", 0);

					if(cdlDirectPageOfs != -1) {
						fseek(cdlFile, cdlDirectPageOfs + (i * 2), 0);
						D = readshort(cdlFile, 0);
						SetReg(segeai, "D", D);
					}

					if(cdlDataBankOfs != -1) {
						fseek(cdlFile, cdlDataBankOfs + i, 0);
						B = fgetc(cdlFile);
						SetReg(segeai, "B", B);
						SetReg(segeai, "DS", B << 12);
					}
#ifdef SHOW_CORRUPT
					if(cd & 6) {
						update = form("corrupt %02X ",cd & 6);
					}
#endif
#ifdef DEBUG
					D = GetReg(segeai, "D");
					B = GetReg(segeai, "B");

					MakeComm(segeai, form("%sopc-.D%04X.B%02X.I%s.A%s",update,D,B,x?"8 ":"16", m?"8 ":"16"));
#else
					MakeComm(segeai, form("%sopc",update));
#endif
					MakeCode(segeai);

					i = i + (ItemSize(segeai) - 1);

					codelog++;
				} else if(cd & 4) {
#ifdef SHOW_CORRUPT
					if(cd & 3) {
						update = "corrupt ";
					}
#endif
					MakeComm(segeai, form("%sdat",update));
					datalog++;
				} else if(cd & 8) {
					MakeComm(segeai, form("%sdma",update));
					datalog++;
				} else {
#ifdef SHOW_CORRUPT
					if(cd & 2) {
						update = "corrupt ";
					}
#endif
#ifdef DEBUG
					if(isCode(GetFlags(segeai))) {
						D = GetReg(segeai, "D");
						B = GetReg(segeai, "B");
						x = GetReg(segeai, "i");
						m = GetReg(segeai, "m");
						MakeComm(segeai, form("%s  -*.D%04X.B%02X.I%s.A%s",update,D,B,x?"8 ":"16", m?"8 ":"16"));
					} else
						MakeComm(segeai, form("%s-*",update));
#else
					MakeComm(segeai, form("%s-*",update));
#endif
					unusedlog++;
				}

				// FIRST PASS END
			} else {
				// SECOND PASS START
				// SECOND PASS END
			}
			i++;
		} while (i < segsize);

		cdlROMOfs = cdlROMOfs + segsize;
		cdlDirectPageOfs = cdlDirectPageOfs + (segsize * 2);
		cdlDataBankOfs = cdlDataBankOfs + segsize;
		segcounter++;
		Message("\n");

	}	// while (SegByName(form(".%02X",0x80|seg) != -1)

	Message("\nScript completed, summary:\n");
	Message("\tCODE bytes:\t0x%06x\n",codelog);
	Message("\tDATA bytes:\t0x%06x\n",datalog);
	Message("\tUNUSED bytes:\t0x%06x\n",unusedlog);

	if(cdlFileOpened == 1)
		fclose(cdlFile);
}
