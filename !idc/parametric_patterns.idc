
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

static far_ptr_search() {
	auto ea = -1;
	auto bank_ofs = 9;
	auto wl_ofs = 1;
	auto wh_ofs = 5;
	Message("search start\n");
	while((ea=FindBinary(ea+1, SEARCH_DOWN, "A9 ?? 85 08 A9 ?? 85 09 A9 ?? 20 01 C5"))!=BADADDR) {
		Message("found pattern at 0x%08x\n",ea);
		auto temp0 = MK_FP(AskSelector(Byte(ea + bank_ofs) + 1), 0);
		auto temp1 = Byte(ea + wl_ofs)|(Byte(ea + wh_ofs) << 8);
		OpOffEx(ea + wl_ofs - 1, 0, REF_LOW8, temp0 + temp1, temp0, 0);
		OpOffEx(ea + wh_ofs - 1, 0, REF_HIGH8, temp0 + temp1, temp0, 0);
	}
	Message("search is over\n");
}

static main(void) {

//	                   opcode,  size, segmask, bankop, ofsop, delta, shift, dobankbyte
//	parametric_farcall("20 D6 F7", 3,    0x3F,      5,     3,    -1,     0, 1);
//	parametric_farcall("20 05 D8", 3,    0x3F,      5,     3,     0,     0, 1);
//	parametric_farcall("CD A7 05", 3,    0x3F,      5,     3,     0,     0, 1);
//	parametric_farcall("CD 62 21", 3,    0x3F,      5,     3,     0,     0, 1);

//	parametric_fixsize("CD A2 0F", 1);
//	parametric_fixsize("CD 03 08", 8);
//	parametric_fixsize("CD 74 04", 4);
//	parametric_fixsize("CD 28 1B", 1);
//	parametric_fixsize("CD 12 46", 10);

//	parametric_switch("20 34 EC");

//	parametric_fixsize("20 E1 97", 2);
//	parametric_fixsize("20 73 DD", 2);
//	parametric_fixsize("20 89 DD", 2);
//	parametric_fixsize("20 92 DD", 2);
//	parametric_fixsize("20 FD DD", 2);


//	parametric_fixsize("20 00 8E", 5);
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

//	parametric_stopbytes("CD 0A 78", "00");
//	parametric_stopbytes("CD 2E 78", "00");
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

	garbage_collector();

//	far_ptr_search();

//	SetCharPrm(INF_GENFLAGS,INFFL_LZERO|INFFL_ALLASM);	// generate leading zeroes in numbers
//		makevarnotlove(0x5100,"_MMC5_PRG_SIZE",1);
//		makevarnotlove(0x5101,"_MMC5_CHR_SIZE",1);
//		makevarnotlove(0x5102,"_MMC5_WRAM0_ENABLE",1);
//		makevarnotlove(0x5103,"_MMC5_WRAM1_ENABLE",1);
//		makevarnotlove(0x5104,"_MMC5_CHR_MODE",1);
//		makevarnotlove(0x5105,"_MMC5_NT_MODE",1);
//		makevarnotlove(0x5106,"_MMC5_NT_FILL",1);
//		makevarnotlove(0x5107,"_MMC5_AT_FILL",12);
//		makevarnotlove(0x5113,"_MMC5_PRG_PAGES",5);
//		makevarnotlove(0x5120,"_MMC5_CHR_BANKSA",8);
//		makevarnotlove(0x5128,"_MMC5_CHR_BANKSB",8);
//		makevarnotlove(0x5200,"_MMC5_SP_MODE",1);
//		makevarnotlove(0x5201,"_MMC5_SP_SCROLL",1);
//		makevarnotlove(0x5202,"_MMC5_SP_PAGE",2);
//		makevarnotlove(0x5204,"_MMC5_IRQ_ENABLE",1);
//		makevarnotlove(0x5205,"_MMC5_MUL0",1);
//		makevarnotlove(0x5206,"_MMC5_MUL1",1);
//		makevarnotlove(0x5C00,"_MMC5_EXRAM",1024);

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




