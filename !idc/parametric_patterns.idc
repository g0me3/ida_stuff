
#include <idc.idc>
#include <functions.idc>

// SANDBOX

// WC		- local offset (current bank or bank0)
// W0-W3	- direct offset (up to 4 configurable)
// B0-B3	- prg bank for direct offset (up to 4)
// ?		- any char
// *		- any chars
// S		- get next byte as a LEN, then get LEN chars after it as array

static makevarnotlove(ea,name,len) {
	if(len) {
		MakeUnknown(ea, len, DOUNK_SIMPLE);
		MakeWord(ea);
		MakeData(ea, FF_BYTE, len, 0);
		SetArrayFormat(ea, AP_IDXHEX|AP_ALLOWDUPS, 0x10, 0);
	}
	MakeNameEx(ea,name,SN_CHECK|SN_NOWARN);
}

static script_convert0() {
	auto ea = ScreenEA();
	auto cnt=0, byt, len;

	len=0;
	while((byt=Byte(ea+len))!=0xFF)
		len++;
	ea = make_data_array(ea,len+1,"");
	Jump(ea);
}

static far_sys_call_search(pat, b0, b1, instr) {
	auto ea = -1, temp0, temp1;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		temp0 = MK_FP(AskSelector(Byte(ea + b1) + 1), 0);
		temp1 = temp0 + Word(temp0 + (Byte(ea + b0) + 0x8001));
//		MakeUnknown(ea, 2, DOUNK_SIMPLE);
//		MakeCode(ea);
		SetManualInsn(ea, form("%s    %s", instr, Name(temp1)));
		make_data_array(ea + 2, ((strlen(pat) + 1) / 3) - 2, "");
		SetManualInsn(ea + 2, "ENDM");
		AddCodeXref(ea, temp1, fl_CF|XREF_USER);
	}
}

static far_sys_call_search_b(pat, b_lo, b_hi, bank, instr) {
	auto ea = -1, temp0, temp1;
	while((ea=FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		temp0 = MK_FP(AskSelector((Byte(ea + bank) & 0x3F) + 1), 0);
		temp1 = temp0 + (Byte(ea + b_lo) | (Byte(ea + b_hi) << 8));
//		MakeUnknown(ea, 2, DOUNK_SIMPLE);
//		MakeCode(ea);
		SetManualInsn(ea, form(instr, Name(temp1)));
		make_data_array(ea + 2, ((strlen(pat) + 1) / 3) - 2, "");
		SetManualInsn(ea + 2, "ENDM");
		AddCodeXref(ea, temp1, fl_CF|XREF_USER);
	}
}

static custom_call_search(pat, b_lo, b_hi, c, d, instr) {
	auto ea = -1, temp0, temp1;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, pat))!=BADADDR) {
		auto bank = GetReg(ea, "ds");
		Message("found pattern at 0x%08x\n", ea);
		temp0 = Byte(ea + b_lo) | (Byte(ea + b_hi) << 8);
		if(temp0 >=0xC000)
			bank = 15 + 1;
		temp1 = MK_FP(AskSelector(bank), 0) + temp0;
//		MakeUnknown(ea, 2, DOUNK_SIMPLE);
//		MakeCode(ea);
		if((c == -1) && (d == -1))
			SetManualInsn(ea, form(instr, Name(temp1)));
		else
			SetManualInsn(ea, form(instr, Name(temp1), Byte(ea + c), Byte(ea + d)));
		make_data_array(ea + 2, ((strlen(pat) + 1) / 3) - 2, "");
		SetManualInsn(ea + 2, "ENDM");
		add_dref(ea, temp1, dr_O|XREF_USER);
	}
}

static getbase(ea, val) {
	auto base = 0;
	if((val >= 0x0000) && (val < 0x4000))
		base = 0;
	else if((val >=0x4000) && (val < 0x8000))
		base = MK_FP(AskSelector(GetReg(ea, "ds")),0);
	else if((val >=0x8000) && (val < 0x9800))
		base = MK_FP(AskSelector(SegByName("CHRRAM")),0);
	else if((val >=0x9800) && (val < 0x9C00))
		base = MK_FP(AskSelector(SegByName("BGMAP1")),0);
	else if((val >=0x9C00) && (val < 0xA000))
		base = MK_FP(AskSelector(SegByName("BGMAP2")),0);
	else if((val >=0xA000) && (val < 0xC000))
		base = MK_FP(AskSelector(SegByName("CRAM")),0);
	else if((val >=0xC000) && (val < 0xD000))
		base = MK_FP(AskSelector(SegByName("RAM0")),0);
	else if((val >=0xD000) && (val < 0xE000))
		base = MK_FP(AskSelector(SegByName("RAMB")),0);
	else if((val >=0xFE00) && (val < 0xFEA0))
		base = MK_FP(AskSelector(SegByName("OAM")),0);
	else if((val >=0xFF00) && (val < 0xFF80))
		base = MK_FP(AskSelector(SegByName("HWREGS")),0);
	else if((val >=0xFF80) && (val < 0xFFFF))
		base = MK_FP(AskSelector(SegByName("ZRAM")),0);
	else if(val ==0xFFFF)
		base = MK_FP(AskSelector(SegByName("IENABLE")),0);
	return base;
}

static arg(ea, a) {
	if(a & 0x100) {
		if(a & 0x200)
			return Word(ea + (a & 0xFF));
		else {
			auto temp0 = Word(ea + (a & 0xFF));
			auto temp1 = temp0 + getbase(ea, temp0);
			add_dref(ea, temp1, dr_O|XREF_USER);
			return Name(temp1);
		}
	} else {
		return Byte(ea + (a & 0xFF));
	}
}

static custom_call_search_ex(pat, a, c, d, e, f, instr) {
	auto ea = -1, size = ((strlen(pat) + 1) / 3);
	while((ea=FindBinary(ea+1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		make_data_array(ea, size, "");
		if(c == -1)
			SetManualInsn(ea, form(instr, arg(ea, a)));
		else if(d == -1)
			SetManualInsn(ea, form(instr, arg(ea, a), arg(ea, c)));
		else if(e == -1)
			SetManualInsn(ea, form(instr, arg(ea, a), arg(ea, c), arg(ea, d)));
		else if(f == -1)
			SetManualInsn(ea, form(instr, arg(ea, a), arg(ea, c), arg(ea, d), arg(ea, e)));
		else
			SetManualInsn(ea, form(instr, arg(ea, a), arg(ea, c), arg(ea, d), arg(ea, e), arg(ea, f)));
	}
}

static custom_far_call_search(pat, bank, ofs, instr) {
	auto ea = -1, size = ((strlen(pat) + 1) / 3), temp0, temp1, name, b;
	while((ea=FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		b = Byte(ea + bank);
		temp0 = MK_FP(AskSelector(b), 0);
		temp1 = Word(ea + ofs);
		if(temp1 >= 0x4000)
			temp1 = temp1 + temp0;
//		MakeNameAuto(temp0, ea + ofs, form("_far_prg%02x_sub%08x", b, temp1));
		name = Name(temp1);
//		Message("found pattern at 0x%08x (ref to 0x%08x, name \"%s\")\n", ea, temp1, name);
		SetManualInsn(ea, form(instr, name));
		AddCodeXref(ea, temp1, fl_CF|XREF_USER);
		make_data_array(ea + 1, size - 1, "");
		SetManualInsn(ea + 1, "ENDM");
	}
}

static far_ptr_search() {
	Message("search start\n");

//	far_sys_call_search("A9 ?? 85 58 A9 ?? 85 59 20 0B CC", 1, 5, "FJSR");	// dragon ball z
//	far_sys_call_search("A9 ?? 85 58 A9 ?? 8D 59 00 20 0B CC", 1, 5, "FJSR");
//	far_sys_call_search("A9 ?? 85 58 A9 ?? 85 59 4C 0B CC", 1, 5, "FJMP");

//	far_sys_call_search("A9 ?? 85 46 A9 ?? 85 47 20 E7 CA", 1, 5, "FJSR");	// you you hakusho
//	far_sys_call_search("A9 ?? 85 46 A9 ?? 85 47 4C E7 CA", 1, 5, "FJMP");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 00 85 00 85 01 A9 FF 85 05 85 06 20 3F D1", 1, 5, -1, -1,       "PPUS    %s,00,00,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 FF 85 00 85 01 85 05 85 06 20 3F D1", 1, 5, -1, -1,             "PPUS    %s,FF,FF,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 00 A9 ?? 85 01 A9 FF 85 05 85 06 20 3F D1", 1, 5, 9, 13,  "PPUS    %s,%02x,%02x,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 00 85 00 85 01 A9 FF 85 05 85 06 20 B0 D1", 1, 5, -1, -1,       "PPUQ    %s,00,00,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 FF 85 00 85 01 85 05 85 06 20 B0 D1", 1, 5, -1, -1,             "PPUQ    %s,FF,FF,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 00 A9 ?? 85 01 A9 FF 85 05 85 06 20 B0 D1", 1, 5, 9, 13,  "PPUQ    %s,%02x,%02x,FF,FF");

//	far_sys_call_search("A9 ?? 85 4B A9 ?? 85 4C 20 75 CC", 1, 5, "FJSR");	// j league
//	far_sys_call_search("A9 ?? 85 4B A9 ?? 85 4C 4C 75 CC", 1, 5, "FJMP");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 00 85 00 85 01 A9 FF 85 05 85 06 20 84 D2", 1, 5, -1, -1,       "PPUS    %s,00,00,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 FF 85 00 85 01 85 05 85 06 20 84 D2", 1, 5, -1, -1,             "PPUS    %s,FF,FF,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 20 54 81", 1, 5, -1, -1,             							   "PPUS    %s,FF,FF,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 00 A9 ?? 85 01 A9 FF 85 05 85 06 20 84 D2", 1, 5, 9, 13,  "PPUS    %s,%02x,%02x,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 01 A9 ?? 85 00 A9 FF 85 05 85 06 20 84 D2", 1, 5, 13, 9,  "PPUS    %s,%02x,%02x,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 00 85 00 85 01 A9 FF 85 05 85 06 20 F5 D2", 1, 5, -1, -1,       "PPUQ    %s,00,00,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 FF 85 00 85 01 85 05 85 06 20 F5 D2", 1, 5, -1, -1,             "PPUQ    %s,FF,FF,FF,FF");
//	custom_call_search("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 00 A9 ?? 85 01 A9 FF 85 05 85 06 20 F5 D2", 1, 5, 9, 13,  "PPUQ    %s,%02x,%02x,FF,FF");
//	custom_call_search_ex("A9 ?? 85 10 A9 ?? 85 11 A9 ?? 85 00 A9 ?? 85 01 A9 ?? 85 05 A9 ?? 85 06 20 84 D2", 1, 5, 9, 13, 17, 21, "PPUQ    %s,%02x,%02x,FF,FF");

//	far_sys_call_search("A9 ?? 85 56 A9 ?? 85 57 20 BA CC", 1, 5, "FJSR");	// ultraman
//	far_sys_call_search("A9 ?? 85 56 A9 ?? 85 57 4C BA CC", 1, 5, "FJMP");
//	far_sys_call_search_b("A9 ?? 85 87 A9 ?? 85 88 A9 ?? 20 43 E2", 1, 5, 9, "FJSR    %s");
//	far_sys_call_search_b("A9 ?? 85 87 A9 ?? 85 88 A9 ?? 4C 64 E2", 1, 5, 9, "FJMP    %s");

// gbc absolute x
//                          0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
//	custom_call_search_ex("11 ?? ?? D5 3E ?? F5 33 3E ?? F5 33 3E ?? F5 33 3E ?? F5 33 CD 35 26 E8 06", 1|256, 5, 9, 13, 17, "_rect_draw(%s,%02x,%02x,%02x,%02x);");
//	custom_call_search_ex("11 ?? ?? D5 3E ?? F5 33 3E ?? F5 33 CD B9 25 E8 04", 1|256, 5, 9, -1, -1, "_tiles_load(%s,%02x,%02x);");
//	custom_call_search_ex("11 ?? ?? D5 3E ?? F5 33 3E ?? F5 33 CD 8C 24 E8 04", 1|256, 5, 9, -1, -1, "_effect_load(%s,%02x,%02x);");
//	custom_call_search_ex("11 ?? ?? D5 3E ?? F5 33 3E ?? F5 33 3E ?? F5 33 3E ?? F5 33 CD 96 27 E8 06", 1|256, 5, 9, 13, 17, "_printf(%s,%02x,%02x,%02x,%02x);");
//	custom_call_search_ex("11 ?? ?? D5 3E ?? F5 33 3E ?? F5 33 FA ?? ?? F5 33 3E ?? F5 33 CD 96 27 E8 06", 1|256, 5, 9, 13|256, 18, "_printf(%s,%02x,%02x,[%s],%02x);");

// gb death track

//	custom_far_call_search("F5 E5 21 ?? ?? 3E ?? EF", 6, 3, "FJSR    %s");
//	custom_far_call_search("F5 E5 21 ?? ?? 3E ?? F7", 6, 3, "FJMP    %s");

//	Message("search is over\n");
}

static MakeNameAuto(base, ea, name) {
	auto ofs = Word(ea);
	if(ofs < 0x4000)
		base = MK_FP(AskSelector(0), 0);
	ea = base + ofs;
	Message("    >set name '%s' at 0x%08x (base %08x)\n", name, ea, base);
	if(MakeNameEx(ea,name,SN_CHECK|SN_NOWARN)==0) {
		auto res, nname, nc = 0;
		do {
			nname = form("%s_%d",name,nc);
			nc++;
			res = MakeNameEx(ea,nname,SN_CHECK|SN_NOWARN);
		} while ((res == 0)&&(nc<100));
	}
}

static input_switch_search() {
	auto ea = -1;
	auto base, ofs;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, "21 ?? ?? CD 35 04"))!=BADADDR) {
		base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
		ofs = base + Word(ea + 1);
		Message("found pattern at 0x%08x dst table 0x%08x\n", ea, ofs);
		MakeNameAuto(base, ofs, "_menu_idle");
		MakeNameAuto(base, ofs + 2, "_menu_press_D");
		MakeNameAuto(base, ofs + 4, "_menu_press_U");
		MakeNameAuto(base, ofs + 6, "_menu_press_L");
		MakeNameAuto(base, ofs + 8, "_menu_press_R");
		MakeNameAuto(base, ofs + 10, "_menu_press_START");
		MakeNameAuto(base, ofs + 12, "_menu_press_SELECT");
		MakeNameAuto(base, ofs + 14, "_menu_press_B");
		MakeNameAuto(base, ofs + 16, "_menu_press_A");
	}
}

static main(void) {

//	input_switch_search();

	garbage_collector();

//	far_ptr_search();

//	                   opcode,  size, segmask, bankop, ofsop, delta, shift, dobankbyte
//	parametric_farcall("20 D6 F7", 3,    0x3F,      5,     3,    -1,     0, 1);
//	parametric_farcall("20 05 D8", 3,    0x3F,      5,     3,     0,     0, 1);
//	parametric_farcall("CD A7 05", 3,    0x3F,      5,     3,     0,     0, 1);
//	parametric_farcall("CD 62 21", 3,    0x3F,      5,     3,     0,     0, 1);

//	parametric_fixsize("20 83 CC", 2);
//	parametric_fixsize("20 7F CC", 2);
//	parametric_fixsize("20 95 CC", 2);
//	parametric_fixsize("20 38 C0", 2);
//	parametric_fixsize("CD 12 46", 10);

//	parametric_switch("20 E1 C2");

//	parametric_fixsize("20 C6 B0", 5);
//	parametric_fixsize("20 73 DD", 2);
//	parametric_fixsize("20 89 DD", 2);
//	parametric_fixsize("20 92 DD", 2);
//	parametric_fixsize("20 FD DD", 2);


//	parametric_fixsize("20 70 E2", 2);
//	parametric_fixsize("20 08 8E", 5);
//	parametric_fixsize("20 10 8E", 5);
//	parametric_fixsize("20 1D A4", 10);
//	parametric_fixsize("20 8C 8F", 6);
//	parametric_fixsize("20 56 91", 10);
//	parametric_fixsize("20 AB 98", 4);
//	parametric_fixsize("20 6C 99", 6);
//	parametric_fixsize("20 73 D8", 2);
//	parametric_fixsize("20 87 D9", 2);
//	parametric_fixsize("20 B9 D9", 2);
//	parametric_fixsize("20 AE DB", 2);
//	parametric_fixsize("20 F2 DB", 2);
//	parametric_fixsize("20 E2 E2", 4);
//	parametric_fixsize("20 AB E3", 2);
//	parametric_fixsize("20 03 E4", 2);
//	parametric_fixsize("20 5A E4", 2);
//	parametric_fixsize("20 CB E4", 2);
//	parametric_fixsize("20 5F E5", 2);
//	parametric_fixsize("20 B7 E5", 2);
//	parametric_fixsize("20 15 E6", 2);
//	parametric_fixsize("20 89 E9", 2);
//	parametric_fixsize("20 F5 EA", 2);
//	parametric_fixsize("20 1B EC", 2);
//	parametric_fixsize("20 60 F5", 4);
//	parametric_fixsize("20 74 F5", 2);
//	parametric_fixsize("20 83 F5", 4);
//	parametric_fixsize("20 97 F5", 4);
//	parametric_fixsize("20 2D F6", 2);
//	parametric_fixsize("20 35 F6", 2);

//	parametric_fixsize("20 BE C0", 2);
// 	parametric_fixsize("20 0D F8", 2);
//	parametric_fixsize("20 13 F8", 2);
//	parametric_fixsize("20 19 F8", 2);
//	parametric_fixsize("20 35 D8", 2);
//	parametric_fixsize("20 29 D8", 2);

//	parametric_fixsize("20 34 F8", 2);
//	parametric_fixsize("20 3A F8", 2);
//	parametric_fixsize("20 40 F8", 2);
//	parametric_fixsize("20 46 F8", 2);
//	parametric_fixsize("20 4A F8", 2);

//	parametric_fixsize("20 AD F7", 2);
//	parametric_fixsize("20 80 F7", 2);

//	parametric_stopbytes("CD DE 0C", "65");
//	parametric_stopbytes("CD 63 09", "65");
//	parametric_stopbytes("CD 99 0E", "00");
//	parametric_stopbytes("CD B8 77", "00 00");
//	parametric_stopbytes("20 DE E9", "FF FF 00");
//	parametric_stopbytes("20 21 EA", "FF FF 00");
//	parametric_stopbytes("20 DE E9", "FF FF 00");

//	parametric_stopbytes("CD 96 05", "00");

//	make_8bit_near_tbl(0x21DB7, 0x21D99, -1, 0);

//	make_8bit_far_tbl(0x2e2991,0x2e29cb,0x2e2a05, 0, 0);
//	make_8bit_far_tbl(0x2660a7,0x266117,0x266187, 0, 0);
//	make_8bit_far_tbl(0x62eaa,0x62eeb,0x62f2c, 0, 0);
//	make_8bit_far_tbl(0x632d4,0x632da,0x632ce, 0, 0);
//	make_8bit_far_tbl(0x6361f,0x636ac,0x63739, 0, 0);
//	make_8bit_far_tbl(0xed3a0,0xed3b2,0xed3c4, 0, 0);

//	AddHotkey("Shift-M", "script_convert0");

//	SetCharPrm(INF_GENFLAGS,INFFL_LZERO|INFFL_ALLASM);	// generate leading zeroes in numbers

/*
		makevarnotlove(0x5100,"_MMC5_PRG_SIZE",1);
		makevarnotlove(0x5101,"_MMC5_CHR_SIZE",1);
		makevarnotlove(0x5102,"_MMC5_WRAM0_ENABLE",1);
		makevarnotlove(0x5103,"_MMC5_WRAM1_ENABLE",1);
		makevarnotlove(0x5104,"_MMC5_CHR_MODE",1);
		makevarnotlove(0x5105,"_MMC5_NT_MODE",1);
		makevarnotlove(0x5106,"_MMC5_NT_FILL",1);
		makevarnotlove(0x5107,"_MMC5_AT_FILL",12);
		makevarnotlove(0x5113,"_MMC5_PRG_PAGES",5);
		makevarnotlove(0x5120,"_MMC5_CHR_BANKSA",8);
		makevarnotlove(0x5128,"_MMC5_CHR_BANKSB",8);
		makevarnotlove(0x5200,"_MMC5_SP_MODE",1);
		makevarnotlove(0x5201,"_MMC5_SP_SCROLL",1);
		makevarnotlove(0x5202,"_MMC5_SP_PAGE",2);
		makevarnotlove(0x5204,"_MMC5_IRQ_ENABLE",1);
		makevarnotlove(0x5205,"_MMC5_MUL0",1);
		makevarnotlove(0x5206,"_MMC5_MUL1",1);
		makevarnotlove(0x5C00,"_MMC5_EXRAM",1024);
//*/

//	MakeName(0x2000,"_PPU_CTRL");
//	MakeName(0x2001,"_PPU_MASK");
//	MakeName(0x2002,"_PPU_STATUS");
//	MakeName(0x2003,"_PPU_OAM_ADDR");
//	MakeName(0x2004,"_PPU_OAM_DATA");
//	MakeName(0x2005,"_PPU_SCROLL");
//	MakeName(0x2006,"_PPU_ADDR");
//	MakeName(0x2007,"_PPU_DATA");

//	MakeName(0x4000,"_APU_PULSE1_ENV");
//	MakeName(0x4001,"_APU_PULSE1_SWEEP");
//	MakeName(0x4002,"_APU_PULSE1_TIME");
//	MakeName(0x4003,"_APU_PULSE1_LEN");
//	MakeName(0x4004,"_APU_PULSE2_ENV");
//	MakeName(0x4005,"_APU_PULSE2_SWEEP");
//	MakeName(0x4006,"_APU_PULSE2_TIME");
//	MakeName(0x4007,"_APU_PULSE2_LEN");
//	MakeName(0x4008,"_APU_TRI_COUNT");
//	MakeName(0x4009,"_APU_TRI_UNUSED");
//	MakeName(0x400a,"_APU_TRI_TIME");
//	MakeName(0x400b,"_APU_TRI_LEN");
//	MakeName(0x400c,"_APU_NOISE_ENV");
//	MakeName(0x400d,"_APU_NOISE_UNUSED");
//	MakeName(0x400e,"_APU_NOISE_LOOP");
//	MakeName(0x400f,"_APU_NOISE_LEN");
//	MakeName(0x4010,"_APU_DMC_FREQ");
//	MakeName(0x4011,"_APU_DMC_LOAD");
//	MakeName(0x4012,"_APU_DMC_ADDR");
//	MakeName(0x4013,"_APU_DMC_LEN");
//	MakeName(0x4014,"_PPU_OAM_DMA");
//	MakeName(0x4015,"_APU_STATUS");
//	MakeName(0x4016,"_PAD0_REG");
//	MakeName(0x4017,"_PAD1_REG");

}




