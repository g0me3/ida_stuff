
#include <idc.idc>

//#define DO_CDL
#define DO_OFS

static main(void) {
	auto logFileName, logFile, _str, ea, base, ofs;
	auto disaEa, count, optype, opvalue;

#ifdef DO_CDL
	logFileName = AskFile(0,"*.log","Choose the log-file");

	if(logFileName=="") return -1;

	logFile = fopen(logFileName, "rb");

	if (0 != logFile) {
		count = 0;

		do {
			disaEa = readstr(logFile);
			_str = substr(disaEa,1,5);
			ofs = xtol(_str);
//			if((ofs<0x6600))	// 1p
			if((ofs<0xA140)||(ofs>0xDFEF))	// vs
//			if((ofs<0xA140)||(ofs>0xC3F4))	// edit
				ea = MK_FP(AskSelector(0), 0) + ofs;
			else
//				ea = MK_FP(AskSelector(5), 0) + ofs;	// 1p
				ea = MK_FP(AskSelector(6), 0) + ofs;	// vs
//				ea = MK_FP(AskSelector(7), 0) + ofs;	// edit

//			Message("substr \"%s\" code at %04X\n",_str,ea);
//			MakeUnkn(ea, DOUNK_SIMPLE);
			if(MakeCode(ea) == 0) {
				MakeComm(ea, "Can't Make Code");
			} else {
				MakeComm(ea, " *code");
			}
			count++;
		} while (disaEa != -1);
		Message("Log-file has been processed successfully (%d entries).\n", count);
	} else {
		Message("Can't open symbol file:\n%s\n", logFileName);
		return -1;
	}
#endif

#ifdef DO_OFS
	ea = 0;
	while ((ea=FindCode(ea,SEARCH_DOWN))!=BADADDR) {
		optype = GetOpType(ea,0);
		if((optype == 2)||(optype == 4)) {
			opvalue = GetOperandValue(ea,0);
			if (opvalue<0x6000)
				base = MK_FP(AskSelector(0), 0);
			else
				base = MK_FP(AskSelector(GetReg(ea,"ds")), 0);
			OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
		}
	}
#endif
}
