// SNES SPECIFIC HELPERS
// ---------------------

static make_ofs_name_snes(ea, is16bit_ofs, name) {
	auto base, ptr;
	if(is16bit_ofs) {
		ptr = Word(ea);
		base = ea & 0xFF0000;
	} else {
		ptr = Word(ea);
		base = Byte(ea + 2) << 16;
	}
	MakeName(base + ptr, "");
	MakeName(base + ptr, form("%s_%X", name, base + ptr));
}

static make_ofs16i_snes(ea, _far) {
	auto base, bank;
	if(_far) {
		bank = AskLong(0, "Enter Bank Nunber") & 0xFF;
		base = bank << 16;
	} else {
		base = ea & 0xFF0000;
		bank = base >> 16;
	}
	auto dst = GetOperandValue(ea, 0);
	OpOffEx(ea, 0, REF_OFF16, base | (dst + 1), base, -1);
}

static auto_ofs16i_snes() {
	make_ofs16i_snes(ScreenEA(), 0);
}

static auto_far_ofs16i_snes() {
	make_ofs16i_snes(ScreenEA(), 1);
}

static make_far_ofs16_snes(ea, wofs, bofs, size, name) {
	auto dst = Word(ea + wofs);
	auto bank = Byte(ea + bofs) | (((ea & 0xFF0000) >> 16) & 0xC0);
	auto base = bank << 16;
	MakeUnknown(ea, size, DOUNK_SIMPLE);
	MakeWord(ea + wofs);
	OpOffEx(ea + wofs, 0, REF_OFF16, -1, base, 0);
	if(name != "")
		make_ofs_name_snes(ea, 0, name);
	if(size == 3)
		MakeByte(ea + bofs);
	else if(size == 4)
		MakeWord(ea + bofs);
	else {
		MakeData(ea + bofs, FF_BYTE, size - 2, 0);
		SetArrayFormat(ea + bofs, AP_IDXHEX, 16, 0);
	}
	return ea + size;
}

static make_near_ofs16_snes(ea, bank, name) {
	auto dst = Word(ea);
	auto base = bank << 16;
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	MakeComm(ea, "");
	if((name != "") && (bank == (ea >> 16))) {
		make_ofs_name_snes(ea, 1, name);
	} else {
		MakeComm(ea, name);
	}
	return ea + 2;
}

static auto_far_ofs16_snes() {
	Jump(make_far_ofs16_snes(ScreenEA(), 0, 2, 3, ""));	// wofs, bofs, size
}

static auto_custom_array_snes() {
	auto ea = ScreenEA(), far_ea;

	auto cnt0, tmp0 = Byte(ea);
//	ea = make_data_array(ea, 1, "");
//	for(cnt0 = 0; cnt0 < tmp0; cnt0++) {
//		ea = make_data_array(ea, 2, "");
//		far_ea = Word(ea) | (Byte(ea + 2) << 16);
//		ea = make_far_ofs16_snes(ea, 0, 2, 3, "_obj_res");
//		far_ea = ea;
//		far_ea = make_data_array(far_ea, 6, "");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_data_array(far_ea, 10, "");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_far_ofs16_snes(far_ea, 0, 2, 3, "_script");
//		far_ea = make_data_array(far_ea, 1, "");
//		ea = far_ea;
//		ea = make_data_array(ea, 4, "");
//	}

	for(cnt0=0; cnt0<232; cnt0++) {
		ea = make_data_array(ea, 3, "");
		far_ea = Word(ea) | (Byte(ea + 2) << 16);
		make_near_ofs16_snes(far_ea, Byte(ea + 2), "_def_script");
		ea = make_far_ofs16_snes(ea, 0, 2, 3, form("_script%02X",cnt0));
		ea = make_data_array(ea, 2, "");
	}

/*
	ea = make_data_array(ea, 1, "");
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_data_array(ea, 4, "");
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_data_array(ea, 14, "");
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_data_array(ea, 4, "");
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_data_array(ea, 9, "");
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
	ea = make_far_ofs16_snes(ea, 0, 2, 3);
*/
//	Jump(ea);
}

static make_tbl16_snes(ea, docode) {
	auto base = ea & 0xFF0000, bank = base >> 16;
	auto i = 0, w0, stop = 0;
	do {
		if((i&1)==0){
			MakeUnknown(ea + i, 2, DOUNK_SIMPLE);
			MakeWord(ea + i);
			w0 = Word(ea + i);
			OpOffEx(ea + i, 0, REF_OFF16, -1, base, 0);
			if(docode) {
				MakeCode(base + w0);
				AutoMark(base + w0, AU_CODE);
				Wait();
			}
			Wait();
		}
		i++;
		if((i&1)==0) {
			auto tmpp=GetFlags(ea + i);
			stop=(isRef(tmpp));
		}
	} while (!stop && (i < 0x10000));
}

static auto_tbl16_snes() {
	make_tbl16_snes(ScreenEA(),0);
}

static auto_rename_snes() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto base = sea & 0xFF0000;
	auto name_mask = AskStr("", "Enter Name Mask");
	auto i = 0;
	while(sea < eea) {
		auto ofs = Word(sea);
		auto nname = form("%s%02X",name_mask,i);
		MakeNameEx(base + ofs, nname, SN_CHECK|SN_NOWARN);
		sea = sea + 2;
		i++;
	}
}

// MISC SCRIPT PARSE HELPERS
// -------------------

static make_data_array(ea, len, cmt) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	if(len != 2) {
		MakeData(ea, FF_BYTE, len, 0);
		SetArrayFormat(ea, AP_IDXHEX, 16, 0);
	} else {
		MakeWord(ea);
	}
	MakeComm(ea, "");
	MakeComm(ea, cmt);
	return ea + len;
}

static make_code(ea) {
	auto len = 2;
	while((MakeCode(ea)==0)&&(len<4)) {
		MakeUnknown(ea, len, DOUNK_SIMPLE);
		len++;
	}
	AutoMark(ea, AU_CODE);
	Wait();
}

static auto_array() {
	auto ea = ScreenEA();
	auto i = 1;
	ea = FindUnexplored(ea - 1, SEARCH_DOWN);
	do {
		auto flags = GetFlags(ea + i);
		auto stop = isUnknown(flags) && !isRef(flags);
		i++;
	} while ((flags != 0) && (stop));
	i = i - 1;
	if(MakeData(ea, FF_BYTE, i, 0)) {
		if(SetArrayFormat(ea, AP_IDXHEX, 0x10, 0))
			Jump(ea);
		else
			Message("can't set array format!\n");

	} else
		Message("can't make data!\n");
}

// garbage labels collector
static garbage_collector(void) {
	Message("garbage collector start\n");
	auto ea = 0, res;
	while ((ea = FindText(ea,SEARCH_DOWN|SEARCH_REGEX,1,0,"loc_.*:")) != BADADDR) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			MakeName(ea, "");
			Message(">found code label at 0x%08x:", ea);
			Message(" no crossrefs, delete\n");
		}
		ea = FindCode(ea,SEARCH_DOWN);
	}
	ea = 0;
	while ((ea = FindText(ea,SEARCH_DOWN|SEARCH_REGEX,1,0,"unk_.*:")) != BADADDR) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			MakeName(ea, "");
			Message(">found unk label at 0x%08x:", ea);
			Message(" no crossrefs, delete\n");
		}
		ea = FindCode(ea,SEARCH_DOWN);
	}
	ea = 0;
	while ((ea = FindText(ea,SEARCH_DOWN|SEARCH_REGEX,1,0,"byte_.*:")) != BADADDR) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			MakeName(ea, "");
			Message(">found byte label at 0x%08x:", ea);
			Message(" no crossrefs, delete\n");
		}
		ea = FindCode(ea,SEARCH_DOWN);
	}
	ea = 0;
	while ((ea = FindText(ea,SEARCH_DOWN|SEARCH_REGEX,1,0,"word_.*:")) != BADADDR) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			MakeName(ea, "");
			Message(">found word label at 0x%08x:", ea);
			Message(" no crossrefs, delete\n");
		}
		ea = FindCode(ea,SEARCH_DOWN);
	}
	Message("garbage collector done\n");
}
