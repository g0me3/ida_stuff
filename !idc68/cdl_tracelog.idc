
#include <idc.idc>

#define DO_CDL
//#define DO_OFS

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
			_str = substr(disaEa,0,8);
			ofs = xtol(_str);
			MakeComm(ofs, " *code");
			MakeCode(ofs);
			AutoMark(ofs, AU_CODE);
			Wait();
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
