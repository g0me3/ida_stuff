
#include <idc.idc>
#include <functions.idc>

#define DEBUG

static code_patterns(void) {
	auto cnt;
}

static main(void) {
	auto cdlFileName, cdlFile, cdlFileOpened, extPos, idbFileName = GetIdbPath();
	auto i, j, cd, seg, segcounter = 0;
	auto segea, segeai, segorg, secondpass = 0;
	auto codelog = 0, datalog = 0, unusedlog = 0;
	auto opcode, optype, opvalue;
	auto banksnum = 0, curbank = -1, prebank = -1, preea = -1, bankflag = 0;
	auto ctype = Byte(0x0147);
	auto prgset = BADADDR, switchptr = BADADDR, switchopc = -1;
	auto farcall_cnt = 0, switch_cnt = 0, param_cnt = 0;
	auto farcall_s = 0, switch_es = 0, param_s = 0;
	auto farcall_cnt_prev = 0, switch_cnt_prev = 0, param_cnt_prev = 0, result = 0;

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

		while (SegByName(form(".%02X",0x80|banksnum)) != -1) {banksnum++;}

		Message("Total Banks: %d\n", banksnum);

//		while ((seg = SegByName(form(".%02X",0x80|segcounter))) != -1) {
		while (segcounter < banksnum) {

			seg = SegByName(form(".%02X",0x80|segcounter));
			segea = SegByBase(seg);

			segorg = 0x8000;	// default LoROM
			// TODO: HiRom support also

			if(secondpass==0) {
#ifdef DEBUG
				Message("DEBUG: name='.%02X', SegByName=%02X, SegByBase=0x%08X cdlpos=%08X\n",0x80|segcounter, seg, segea, ftell(cdlFile));
#endif
				Message("Seg %02x start pass %d", seg, secondpass);
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

					MakeComm(segeai, "");
					auto cmt = "";

					if(cd & 1) {
						cmt = cmt + "opcode ";
						MakeCode(segeai);
						codelog++;
					}
					if(cd & 2) {
						cmt = cmt + "operand ";
						codelog++;
					}
					if(cd & 4) {
						cmt = cmt + "data ";
						datalog++;
					}
					if(cd & 8) {
						cmt = cmt + "dma ";
						datalog++;
					}
					if(cd & 0x80) {
						cmt = cmt + "dsp ";
						datalog++;
					} else {
						unusedlog++;
					}

					MakeComm(segeai, cmt);

					// FIRST PASS END
				} else {
					// SECOND PASS START
					// SECOND PASS END
				}
				i++;
			} while (i < 0x8000);

//	end work here

//		if(secondpass == 0) {
//			secondpass++;
//		} else {
//			secondpass = 0;
			segcounter++;
			Message("\n");
//		}

		}	// while (SegByName(form(".%02X",0x80|seg) != -1)

		Message("\nScript completed, summary:\n");
		Message("\tCODE bytes:\t0x%x\n",codelog);
		Message("\tDATA bytes:\t0x%x\n",datalog);
		Message("\tUNUSED bytes:\t0x%x\n",unusedlog);

		if(cdlFileOpened == 1)
			fclose(cdlFile);
}

static makeOffset(ea,val,s,opnum,bnum,cbank) {
//	if((val >= 0x0) && (val < 0x4000))
//		OpOff(ea,opnum,0);
//	else if((val >=0x4000) && (val < 0x8000)) {
//		if(s == 0) {
//			if(bnum == 2)
//				OpOff(ea,opnum,MK_FP(AskSelector(1),0));
//			else if(cbank!=-1)
//				OpOff(ea,opnum,MK_FP(AskSelector(cbank),0));
//		} else
//			OpOff(ea,opnum,MK_FP(AskSelector(s),0));
//	} else if((val >=0x8000) && (val < 0x9800))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CHRRAM")),0));
//	else if((val >=0x9800) && (val < 0x9C00))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP1")),0));
//	else if((val >=0x9C00) && (val < 0xA000))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP2")),0));
//	else if((val >=0xA000) && (val < 0xC000))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CRAM")),0));
//	else if((val >=0xC000) && (val < 0xD000))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAM0")),0));
//	else if((val >=0xD000) && (val < 0xE000))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAMB")),0));
//	else if((val >=0xFE00) && (val < 0xFEA0))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("OAM")),0));
//	else if((val >=0xFF00) && (val < 0xFF80))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("HWREGS")),0));
//	else if((val >=0xFF80) && (val < 0xFFFF))
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("ZRAM")),0));
//	else if(val ==0xFFFF)
//		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("IENABLE")),0));
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
