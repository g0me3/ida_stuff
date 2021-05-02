#include <idc.idc>

// ---------------------------------
// POCKET DENSHA GAME SCRIPTS
// ---------------------------------

static make_data_array(ea, len, cmt) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	if(len == 2) {
		MakeWord(ea);
	} else {
		MakeData(ea, FF_BYTE, len, 0);
		SetArrayFormat(ea, AP_IDXHEX, len, 0);
	}
	return ea + len;
}

static make_auto_ofs16_gb(ea, bofs) {
	auto word0, bank0, base;
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
	word0 = Word(ea);
	if(bofs == 0)
		bank0 = GetReg(ea,"ds");
	else {
		if((bofs > 0) && (bofs & 0x100))
			bank0 = bofs & 0xFF;
		else
			bank0 = Byte(ea + bofs);
	}
	if(bank0>0) {
		if(word0<0x4000)
			base = MK_FP(AskSelector(0), 0);
		else
			base = MK_FP(AskSelector(bank0), 0);
	}
	else {
		if(word0<0x4000)
			base = MK_FP(AskSelector(0), 0);
		else
			base = -1;
	}
	if(base!=-1)
		OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	return ea + 2;
}

static make_ram_or_thrd_ofs(ea) {
	if(Word(ea)<0xC000)
		return make_data_array(ea, 2, "");
	else if(Word(ea)<0xD000)
		return make_auto_ofs16_gb(ea, 0x24|0x100);
	else if(Word(ea)<0xE000)
		return make_auto_ofs16_gb(ea, 0x25|0x100);
	else if(Word(ea)<0xFF80)
		return make_auto_ofs16_gb(ea, 0x27|0x100);
	else
		return make_auto_ofs16_gb(ea, 0x28|0x100);
}

static pden_opcode(ea) {
	auto tmp0;
	if(!isCode(GetFlags(ea))) {
		tmp0 = Word(ea);
		ea = make_auto_ofs16_gb(ea, 0);
		if(tmp0 == 0x34C9) {
			ea = make_data_array(ea, 2, "");
			ea = make_auto_ofs16_gb(ea, 4);
			ea = make_data_array(ea, 2, "");
			ea = make_data_array(ea, 1, "");
		} else if(tmp0 == 0x34F0) {
			ea = make_data_array(ea, 6, "");
			ea = make_auto_ofs16_gb(ea, -1);
		} else if(tmp0 == 0x3512) {
			ea = make_data_array(ea, 2, "");
			ea = make_auto_ofs16_gb(ea, -1);
			ea = make_data_array(ea, 2, "");
			ea = make_data_array(ea, 2, "");
		} else if(tmp0 == 0x346D) {
			ea = make_auto_ofs16_gb(ea, 0x05|0x100);
		} else if((tmp0 == 0x3438)||(tmp0 == 0x3487)||(tmp0 == 0x3495)) {
			ea = make_data_array(ea, 1, "");
			ea = make_ram_or_thrd_ofs(ea);
		} else if((tmp0 == 0x34A3)||(tmp0 == 0x345D)||(tmp0 == 0x34B6)) {
			ea = make_data_array(ea, 2, "");
			ea = make_ram_or_thrd_ofs(ea);
		} else if(tmp0 == 0x338A) {
			MakeCode(ea);
			AutoMark(ea, AU_CODE);
			Wait();
			ea = FindBinary(ea, SEARCH_DOWN|SEARCH_CASE, "3E ?? 16 ?? C9");
			ea = ea + 5;
//			ea = MK_FP(AskSelector(bank0), 0) + Byte(ea + 1) | (Byte(ea + 3) << 8);
		} else if(tmp0 == 0x32E1) {
			ea = make_data_array(ea, 2, "");
		} else if(tmp0 == 0x3563) {
			ea = make_data_array(ea, 3, "");
		} else if((tmp0 == 0x3542)||(tmp0 == 0x358A)) {
			ea = make_data_array(ea, 1, "");
			ea = make_data_array(ea, 2, "");
		} else if(tmp0 == 0x3329) {
			ea = make_data_array(ea, 2, "");
			ea = make_data_array(ea, 1, "");
		} else if((tmp0 == 0x366D)||(tmp0 == 0x35AB)||(tmp0 == 0x362C)) {
			ea = make_data_array(ea, 1, "");
		} else if((tmp0 == 0x35D0)||(tmp0 == 0x35E8)) {
			ea = make_ram_or_thrd_ofs(ea);
			ea = make_data_array(ea, 2, "");
			ea = make_data_array(ea, 2, "");
		} else if(tmp0 == 0x3347) {
			ea = make_ram_or_thrd_ofs(ea);
			ea = make_data_array(ea, 2, "");
			ea = make_auto_ofs16_gb(ea, 0);
		} else if(tmp0 == 0x363B) {
			ea = make_ram_or_thrd_ofs(ea);
			ptr_table(MK_FP(AskSelector(bank0), 0) + Byte(ea + 0) | (Byte(ea + 1) << 8), 0);
			ea = make_auto_ofs16_gb(ea, 0);
		} else if(tmp0 == 0x3361) {
			ea = make_ram_or_thrd_ofs(ea);
			ea = make_data_array(ea, 2, "");
			ea = make_data_array(ea, 1, "");
			ea = make_auto_ofs16_gb(ea, 0);
		} else if(tmp0 == 0x3381) {
			ea = make_auto_ofs16_gb(ea, 0);
		} else if(tmp0 == 0x33BE) {
			ea = make_data_array(ea, 2, "");
			ea = make_auto_ofs16_gb(ea, 0x05|0x100);
			ea = make_data_array(ea, 1, "");
		} else if((tmp0 == 0x32DB)||(tmp0 == 0x347C)) {
		} else {
			Message("Unknown command %04X\n", tmp0);
			ea = ea - 2;
		}
		Jump(ea);
	}
}

static pden_script_selection(void) {
	Jump(pden_opcode(ScreenEA()));
}

static main(void) {
	DelHotkey("Shift-P");
	AddHotkey("Shift-P", "pden_script_selection");
}
