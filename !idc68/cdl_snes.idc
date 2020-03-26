
#include <idc.idc>
#include <functions.idc>

//#define DEBUG
//#define SHOW_UPDATES

static code_patterns(void) {
	auto cnt;
}

static main(void) {
	auto cdlFileName, cdlFile, cdlFileOpened, extPos, idbFileName = GetIdbPath();
	auto i, j, cd, seg, segcounter = 0;
	auto segea, segeai, segorg, segsize, secondpass = 0;
	auto codelog = 0, datalog = 0, unusedlog = 0;
	auto opcode, optype, opvalue;
	auto banksnum = 0, curbank = -1, prebank = -1, preea = -1, bankflag = 0;
	auto prgset = BADADDR, switchptr = BADADDR, switchopc = -1;
	auto farcall_cnt = 0, switch_cnt = 0, param_cnt = 0;
	auto farcall_s = 0, switch_es = 0, param_s = 0;
	auto farcall_cnt_prev = 0, switch_cnt_prev = 0, param_cnt_prev = 0, result = 0;
	auto cart_mode = -1;

	extPos = strstr(idbFileName, ".idb");
	cdlFileName = substr(idbFileName, 0, extPos) + ".cdl";
	cdlFile = fopen(cdlFileName, "rb");
	if( cdlFile == 0 ) {
		cdlFileName = AskFile(0,"*.cdl","Choose a CDL-file Manually");
		cdlFile = fopen(cdlFileName, "rb");
	}
	if (cdlFile != 0) {
		auto cdlSignature = "", cdlType = "", cdlFiles=0;
		fgetc(cdlFile);														// skip 0D
		for(i=0; i<13; i++) cdlSignature = cdlSignature + fgetc(cdlFile);	// read signature
		fgetc(cdlFile);														// skip 0F
		for(i=0; i<15; i++) cdlType = cdlType + fgetc(cdlFile);				// read type
		for(i=0; i<4; i++) cdlFiles = cdlFiles | (fgetc(cdlFile)<<(i*8));	// read files count
		if ((cdlSignature == "BIZHAWK-CDL-2")&&(cdlType == "SNES           ")) {
			Message("CDL file opened succesfully.\n\tName:    \"%s\"\n\tVersion: \"%s\"\n\tType:    \"%s\"\n\tChunks:  %d\n", cdlFileName,cdlSignature,cdlType,cdlFiles);
			result=cdl_chunk_search(cdlFile, "CARTROM", cdlFiles);
			if(result == -1) {
				Message("Can't find proper Data chunk\nStartig disassembly without CDL.\n", cdlFileName);
				cdlFileOpened = 0;
			} else
				cdlFileOpened = 1;
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
			Message("DEBUG: name='.%02X', SegByName=%02X, SegByBase=0x%08X cdlpos=%08X\n",cart_mode|segcounter, seg, segea, ftell(cdlFile));
#endif
			Message("Seg %s start pass %d", segname, secondpass);
		}
		else
			Message(" %d", secondpass);

		i = 0;
//	work here
		do {
			segeai = segea + i;
			if(secondpass == 0) {
				// FIRST PASS START
				if(cdlFileOpened == 1)
					cd = fgetc(cdlFile);
				else
					cd = 0;

				auto update = "";

#ifdef SHOW_UPDATES
				if(CommentEx(segeai,0)=="--") {
					MakeComm(segeai, "");
					update = "*";
				}
#else
				MakeComm(segeai, "");
#endif

//				if (cd) cmt = form("cdl: %02X [ ", cd);

				if(cd & 1) {
					auto x = cd & 0x10;
					auto m = cd & 0x20;
					SetReg(segeai, "i", x >> 4);
					SetReg(segeai, "m", m >> 5);
					MakeComm(segeai, form("%sopc",update));
					MakeCode(segeai);
					codelog++;
				} else if(cd & 4) {
					MakeComm(segeai, form("%sdat",update));
					datalog++;
				} else if(cd & 8) {
					MakeComm(segeai, form("%sdma",update));
					datalog++;
//				} else if(cd & 0x80) {
//#ifdef SHOW_UPDATES
//					if(update)
//						MakeComm(segeai, "*unk");
//#else
//					MakeComm(segeai, "unk");
//#endif
//					datalog++;
				} else {
					MakeComm(segeai, "--");
					unusedlog++;
				}

//				if (cd) cmt = cmt + "]";

				// FIRST PASS END
			} else {
				// SECOND PASS START
				// SECOND PASS END
			}
			i++;
		} while (i < segsize);

//	end work here

//	if(secondpass == 0) {
//		secondpass++;
//	} else {
//		secondpass = 0;
		segcounter++;
		Message("\n");
//	}

	}	// while (SegByName(form(".%02X",0x80|seg) != -1)

	Message("\nScript completed, summary:\n");
	Message("\tCODE bytes:\t0x%06x\n",codelog);
	Message("\tDATA bytes:\t0x%06x\n",datalog);
	Message("\tUNUSED bytes:\t0x%06x\n",unusedlog);

	if(cdlFileOpened == 1)
		fclose(cdlFile);
}

static cdl_chunk_search(cdl, chunk, max) {
	auto name, size, len, i, ret = 0;

	while(ret==0) {
		name="";
		size=0;
		len=fgetc(cdl);									// get chunk name len
		for(i=0; i<len; i++) name = name + fgetc(cdl);	// read chunk name
		if(name!=chunk) {
			for(i=0; i<4; i++) size = size | (fgetc(cdl)<<(i*8));
														// read file size
			for(i=0; i<size; i++) fgetc(cdl);			// read skip file
			max--;
			if(max==0)
				ret = -1;
//			Message("\tSkip:   \"%s\" (size %08x)\n\n",name, size);
		} else {
			for(i=0; i<4; i++) size = size | (fgetc(cdl)<<(i*8));
			Message("\tFound:   \"%s\" (size %08x)\n\n",name, size);
			ret = size;
		}
	}
	return ret;
}
