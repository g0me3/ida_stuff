
#include <idc.idc>
#include <functions.idc>

#define DEBUG

static code_patterns(void) {
	auto cnt;
}

static main(void) {
	auto cdlFileName, cdlFile, cdlFileOpened, extPos, idbFileName = GetIdbPath();
	auto i, j, cd, seg, segcounter = 0, segsize;
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
		if ((cdlSignature == "BIZHAWK-CDL-2")&&(cdlType == "GEN            ")) {
			Message("CDL file opened succesfully.\n\tName:    \"%s\"\n\tVersion: \"%s\"\n\tType:    \"%s\"\n\tChunks:  %d\n", cdlFileName,cdlSignature,cdlType,cdlFiles);
			result=cdl_chunk_search(cdlFile, "MD CART", cdlFiles);
			if(result == -1) {
				Message("Can't find proper Data chunk\nStartig disassembly without CDL.\n", cdlFileName);
				cdlFileOpened = 0;
			} else
				cdlFileOpened = 1;
		} else {
			Message("CDL file not in GEN format (%s, %s)!\nStartig disassembly without CDL.\n", cdlSignature, cdlType);
			cdlFileOpened = 0;
		}
	} else {
		Message("Can't open CDL file: \"%s\"\nStartig disassembly without CDL.\n", cdlFileName);
		cdlFileOpened = 0;
	}

	{
		seg = 0 ; //SegByName("ROM");
		segea = 0 ; //SegByBase(seg);
		segsize = SegEnd(segea);

		Message("Seg ROM SIZE=%08x start\n", segsize);

		auto bar = "";
		for(i=0; i<(segsize>>16); i++)
			bar = bar + "_";
		Message("%s\n", bar);

		i = 0;
		do {
			segeai = segea + i;
			if((segeai & 0xFFFF) == 0)Message(".", segeai);

//  Exec68k = 0x01
//  Data68k = 0x04
//  ExecZ80First = 0x08
//  ExecZ80Operand = 0x10
//  DataZ80 = 0x20
//  DMASource = 0x40 --

				if(cdlFileOpened == 1)
					cd = fgetc(cdlFile);
				else
					cd = 0;
//				MakeComm(segeai, "");
				auto cmt = "";

				if(cd & 1) {
					cmt = cmt + "*c";
					MakeCode(segeai);
					codelog++;
//					i = i + ItemSize(segeai) - 1;
				}
				if(cd & 4) {
					cmt = cmt + "*d";
					datalog++;
				}
				if(cd & 0x40) {
					cmt = cmt + "*dma";
					datalog++;
				} else {
					unusedlog++;
				}
				MakeComm(segeai, cmt);
			i++;
		} while (i < segsize);
	}

	Message("\nScript completed, summary:\n");
	Message("\tCODE bytes:\t0x%x\n",codelog);
	Message("\tDATA bytes:\t0x%x\n",datalog);
	Message("\tUNUSED bytes:\t0x%x\n",unusedlog);

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
