// SNES SPECIFIC HELPERS
// ---------------------

static make_8bit_ofs_selection3() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs_snes(ea, 0, 3, 0);
}

static make_8bit_ofs_selection4() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs_snes(ea, 0, 4, 0);
}

static make_8bit_ofs_selection5() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs_snes(ea, 0, 5, 0);
}

static make_8bit_ofs_selection6() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs_snes(ea, 0, 6, 0);
}

static make_8bit_ofs_selection7() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs_snes(ea, 0, 7, 0);
}

static make_8bit_ofs_snes(ea, loofs, hiofs, ofs) {
//	auto base = ea & 0xFF0000;
	auto base = (AskLong(0, "Enter Bank Nunber") & 0xFF ) << 16;
	auto addr = Byte(ea + loofs + 1) | (Byte(ea + hiofs + 1) << 8);
	OpOffEx(ea + loofs, 0, REF_LOW8, base + addr - ofs, base, ofs);
	OpOffEx(ea + hiofs, 0, REF_HIGH8, base + addr - ofs, base, ofs);
}

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
	auto base;
	if(bank == -1)
		base = ea & 0xFF0000;
	else
		base = bank << 16;
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
//	Jump(make_far_ofs16_snes(ScreenEA(), 0, 2, 3, ""));	// wofs, bofs, size

///*
	auto ea = ScreenEA();
	auto size = 2;
	make_far_ofs16_snes(ea, 0, 2, 3, "");
	make_data_array(ea + 2, size, "");
	Jump(ea + size + 2);//*/

/*
	auto ea = ScreenEA();
	auto size = 10;
	make_data_array(ea, 6, "");
	make_far_ofs16_snes(ea + 6, 0, 2, 3, "");
	make_data_array(ea + 8, 2, "");
	Jump(ea + size);//*/

/*	auto ea = ScreenEA();
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
	ea = ea + 2;
	ea = make_far_ofs16_snes(ea, 0, 2, 3, "");
	Jump(ea + 2); //*/

}

static make_ofs32_name(ea, name) {
	auto tmp0 = Dword(ea), segsize = SegEnd(ea);
	MakeUnknown(ea, 4, DOUNK_SIMPLE);
	MakeDword(ea);
	if((tmp0 > 0) && (tmp0 < segsize)) {
		OpOffEx(ea, 0, REF_OFF32, -1, 0x948000, 0);
		if(name)
			MakeNameEx(tmp0, form("%s_%08x",name,tmp0), SN_CHECK|SN_NOWARN);
		Wait();
	}
	return ea + 4;
}

static parametric_fixsize(pat, param, stop, custom) {
	auto ea = -1, size = ((strlen(pat) + 1) / 3), tmp0, tmp1, str;
	auto stopsize = ((strlen(stop) + 1) / 3);
	Message(" Pattern search for \"%s\" start!\n", pat);
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN|SEARCH_CASE, pat);
		if(ea != BADADDR) {
			if(custom != -1) {
				Message(" >found custom one at 0x%08x\n", ea);
				custom(ea);
			} else if(stop != "") {
				Message(" >found stopbyte one at 0x%08x\n", ea);
				param = FindBinary(ea + size, SEARCH_DOWN|SEARCH_CASE, stop);
				MakeUnknown(ea, param - ea + size, DOUNK_SIMPLE);
				MakeData(ea + size, FF_BYTE, param - ea - size + stopsize, 0);
				SetArrayFormat(ea + size, AP_IDXHEX, 16, 0);
				MakeCode(ea);
				AutoMark(ea + size + param + stopsize, AU_CODE);
				Wait();
			} else {
				Message(" >found fixsize one at 0x%08x\n", ea);
				MakeUnknown(ea, size + param, DOUNK_SIMPLE);
				MakeCode(ea);
				if(param == 2)
					MakeWord(ea + size);
				else {
					MakeData(ea + size, FF_BYTE, param, 0);
					SetArrayFormat(ea + size, AP_IDXHEX, 16, 0);
				}
				AutoMark(ea + size + param, AU_CODE);
				Wait();
			}
		}
	} while (ea != BADADDR);
	Message(" Done!\n");
}

static custom_params0(ea) {
	MakeUnknown(ea + 3, 8, DOUNK_SIMPLE);
	MakeByte(ea + 3);
	make_far_ofs16_snes(ea + 4, 0, 2, 3, "");
	MakeData(ea + 7, FF_BYTE, 4, 0);
	SetArrayFormat(ea + 7, AP_IDXHEX, 16, 0);
}

static custom_params1(ea) {
	MakeUnknown(ea + 3, 5, DOUNK_SIMPLE);
	make_far_ofs16_snes(ea + 3, 0, 2, 3, "");
	MakeWord(ea + 6);
}

static custom_params3(ea) {
	MakeUnknown(ea - 10, 10, DOUNK_SIMPLE);
	auto base = Byte(ea - 9) << 16;
	AutoMark(ea - 10, AU_CODE);
	Wait();
	OpOffEx(ea - 7, 0, REF_OFF16, -1, base, 0);
}

static custom_params4(ea) {
	MakeUnknown(ea, 13, DOUNK_SIMPLE);
	auto base = Byte(ea + 8) << 16;
	AutoMark(ea, AU_CODE);
	Wait();
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
}

static custom_params5(ea) {
	MakeUnknown(ea, 10, DOUNK_SIMPLE);
	auto base = Byte(ea + 1) << 16;
	AutoMark(ea, AU_CODE);
	Wait();
	OpOffEx(ea + 5, 0, REF_OFF16, -1, base, 0);
}

static custom_mvn_copy(ea) {
	MakeUnknown(ea, 12, DOUNK_SIMPLE);
	auto base = Byte(ea + 11) << 16;
	AutoMark(ea, AU_CODE);
	Wait();
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
}

static custom_far_args(ea) {
	auto bofs = 8;
	auto wofs = 0;
//	MakeUnknown(ea, 12, DOUNK_SIMPLE);
	auto byte = Byte(ea + bofs);
	auto word = Word(ea + wofs + 1);
	if((byte >= 0x80) && (word >= 0x8000)) {
		auto base = (0x80|byte) << 16;
		MakeCode(ea);
		AutoMark(ea, AU_CODE);
		Wait();
		OpOffEx(ea + wofs, 0, REF_OFF16, -1, base, 0);
	}
}

static custom_params_scw3_far_param4(ea) {
	MakeUnknown(ea + 4, 4, DOUNK_SIMPLE);
	make_far_ofs16_snes(ea + 4, 0, 2, 3, "");
	MakeUnknown(ea + 6, 2, DOUNK_SIMPLE);
	MakeWord(ea + 6);
	MakeCode(ea);
	MakeCode(ea + 8);
}

static custom_params_scw3_far_param3(ea) {
	MakeUnknown(ea + 4, 3, DOUNK_SIMPLE);
	make_far_ofs16_snes(ea + 4, 0, 2, 3, "");
	MakeCode(ea);
	MakeCode(ea + 7);
}

static far_sys_call_search_customA(pat, instr) {
	auto ea = -1, temp0, temp1, temp2;
	while((ea=FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		temp0 = (Byte(ea + 1) | (Byte(ea + 2) << 8));
		temp1 = 0xBFCA0D + temp0;
		temp2 = (Word(temp1) + 1) | (Byte(temp1 + 2) << 16);
		Message(" idx=%04x, ofs=%08x, ptr=%08x, name=%s\n", temp0, temp1, temp2, Name(temp2) );
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeCode(ea);
		SetManualInsn(ea, form(instr, Name(temp2)));
		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		AddCodeXref(ea, temp2, fl_CF|XREF_USER);
	}
}

static auto_custom_array() {
	auto ea = ScreenEA(), ofs, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmpstr = "", stop = 0, str, size, i;
//	parametric_fixsize("A9 ?? ?? A2 ?? 00 22 ?? ?? ??", -1, "", custom_far_args);
//	parametric_fixsize("A9 ?? ?? A0 ?? 00 22 ?? ?? ??", -1, "", custom_far_args);
//	parametric_fixsize("A2 ?? ?? A0 ?? ?? A9 ?? ?? 54 ?? ??", -1, "", custom_mvn_copy);

//	parametric_fixsize("A9 ?? ?? 85 ?? A2 ?? ?? 22 9C FA 82", -1, "", custom_far_args);
//	parametric_fixsize("A9 ?? ?? 8F ?? ?? ?? A9 ?? 00 8F ?? ?? ??", -1, "", custom_far_args);

//	parametric_fixsize("18 69 ?? ?? A8 A9 ?? 00", -1, "", custom_far_args);

//	parametric_fixsize("18 69 ?? ?? A8 A9 ?? 00", -1, "", custom_far_args);

//	parametric_fixsize("A9 ?? 00 A0 ?? ?? 22 22 F4 C6", -1, "", custom_params3);
//	parametric_fixsize("A9 ?? 00 A0 ?? ?? 22 47 F4 C6", -1, "", custom_params3);
//	parametric_fixsize("A9 ?? ?? 85 ?? E2 20 A9 ?? 85 ??", -1, "", custom_params4);
//	parametric_fixsize("A9 ?? 00 85 02 A9 ?? ?? 85 00", -1, "", custom_params5);

//	parametric_fixsize("18 69 ?? ?? A8 A9 ?? 00", -1, "", custom_far_args);

//	parametric_fixsize("20 1E 4A", -1, "FF FF", -1);

//	parametric_fixsize("22 4F 01 C2", 2, "", -1);
//	parametric_fixsize("22 BD 44 EE", 2, "", -1);
//	parametric_fixsize("22 86 02 C2", 4, "", -1);
//	parametric_fixsize("22 05 01 C2", -1, "", custom_params0);
//	parametric_fixsize("22 47 44 EE", -1, "", custom_params0);
//	parametric_fixsize("22 D4 FA E9", -1, "", custom_params1);
//	parametric_fixsize("20 3F 33", 5, "", custom_params1);
//	parametric_fixsize("20 6E 3E", 6, "", -1);
//	parametric_fixsize("22 40 3B EE", -1, "", custom_params1);
//	parametric_fixsize("22 70 03 C2", 7, "", -1);
//	parametric_fixsize("20 72 32", 7, "", -1);
//	parametric_fixsize("20 42 35", 7, "", -1);
//	parametric_fixsize("20 D7 34", 8, "", custom_params0);
//	parametric_fixsize("22 69 49 EE", 7, "", -1);
//	parametric_fixsize("22 C7 F0 C2", 7, "", -1);
//	parametric_fixsize("22 AF F4 C6", 9, "", -1);
//	parametric_fixsize("22 1E 04 C2", 9, "", -1);
//	parametric_fixsize("22 4C 0A C2", 9, "", -1);
//	parametric_fixsize("22 83 05 C2", 11, "", -1);
//	parametric_fixsize("22 20 06 C2", 12, "", -1);
//	parametric_fixsize("22 C7 02 C2", 12, "", -1);
//	parametric_fixsize("22 7F 0C C2", 16, "", -1);
//	parametric_fixsize("22 A6 0E C2", 16, "", -1);
//	parametric_fixsize("22 27 07 C2", 17, "", -1);

//	parametric_fixsize("22 D4 83 80", -1, "", custom_params_scw3_far_param4);
//	parametric_fixsize("22 A0 8A 80", -1, "", custom_params_scw3_far_param3);
//	parametric_fixsize("22 CC 8A 80", -1, "", custom_params_scw3_far_param3);
//	parametric_fixsize("22 59 83 80", -1, "", custom_params_scw3_far_param3);

/*	while(((ofs = Dword(ea)) != 0xFFFFFFFF) && !stop) {
		str = substr(Name(ea),0,5);
		if(str != "_spr_") {
			ea = make_ofs32_name(ea, "_spr_lay");
			tmp0 = Dword(ea);
				tmp0 = make_ofs32_name(tmp0, "_spr_posA");
				tmp0 = make_ofs32_name(tmp0, "_spr_posB");
				MakeUnknown(tmp0, 4, DOUNK_SIMPLE);
				MakeDword(tmp0);
			ea = make_ofs32_name(ea, "_spr_pos");
			tmp0 = Dword(ea);
			tmp1 = tmp0 & 0x18000000;
			tmp0 = tmp0 & 0x07FFFFFF;
			MakeUnknown(ea, 4, DOUNK_SIMPLE);
			MakeDword(ea);
			OpOffEx(ea, 0, REF_OFF32|REFINFO_NOBASE|REFINFO_PASTEND, -1, -tmp1, 0);
			MakeNameEx(tmp0, form("%s_%08x","_spr_chr",tmp0), SN_CHECK|SN_NOWARN);
			Wait();
			ea = ea + 4;
		} else
			stop = 1;
//		ea = make_ofs32_name(ea, "_spr_chr");
	}
	if(!stop) {
		MakeUnknown(ea, 4, DOUNK_SIMPLE);
		MakeDword(ea);
		ea = ea + 4;
		Jump(ea);
	}*/

/*	ofs = Dword(ea);
	ofs = make_ofs32_name(ofs, "");
	make_ofs32_name(ofs, "");
	ofs = Dword(ofs);
	while(Dword(ofs) != 0) {
		tmp0 = Dword(ofs);
		ofs = make_ofs32_name(ofs, "");
			MakeDword(tmp0);
			tmp0 = tmp0 + 4;
			tmp1 = Dword(tmp0);
			tmp0 = make_ofs32_name(tmp0, "");
				MakeDword(tmp1);
				tmp1 = tmp1 + 4;
				MakeDword(tmp1);
				tmp1 = tmp1 + 4;
				tmp2 = Dword(tmp1);
				tmp1 = make_ofs32_name(tmp1, "");
					make_ofs32_name(ea, "");
					tmp2 = Dword(ea);
					if((tmp2 > 0xA5000) && (tmp2 < (4 * 1024 * 1024))) {
						MakeDword(ea);
						auto i = 0, cnt = Byte(tmp2);
						tmp2 = make_data_array(tmp2, 4, "");
						while(i < cnt) {
							tmp2 = make_data_array(tmp2, 6, "");
							tmp2 = make_ofs32_name(tmp2, "");
							i++;
						}
						Jump(ea + 4);
					}
/*			tmp0 = make_ofs32_name(tmp0, "");
		MakeDword(ofs);
		ofs = ofs + 4;
	}
	MakeDword(ofs);
	Jump(ea + 0x0E);
*/
//	Jump(ea + 4);
/*
	while((tmp0 = (Byte(ea) ^ 0xFF)) & 0x80) {
		size = 1 + 4;
		if(tmp0 & 0x40)
			size = size + 2;
		if(tmp0 & 0x20)
			size = size + 2;
		if(tmp0 & 0x10)
			size = size + 2;
		if(tmp0 & 0x08)
			size = size + 2;
		tmp1 = Word(ea + size);
		size = size + 2;
		if(tmp0 & 0x04)
			size = size + 1;
		if(tmp0 & 0x01)
			size = size + 2;
		ea = make_data_array(ea, size, form("%04X", tmp1));
	}
	MakeByte(ea); //*/

/*	tmp0 = Byte(ea);
	tmp1 = Byte(ea + 1);
	MakeUnknown(ea, tmp0 * tmp1 + 2, DOUNK_SIMPLE);
	MakeData(ea, FF_BYTE, 2, 0);
	SetArrayFormat(ea, AP_IDXHEX, 2, 0);
	ea = ea + 2;
	for(i = 0; i < tmp1; i++) {
		MakeData(ea, FF_BYTE, tmp0, 0);
		SetArrayFormat(ea, AP_IDXHEX, tmp0, 0);
		ea = ea + tmp0;
	}*/

//	MakeUnknown(ea, 128, DOUNK_SIMPLE);
//	MakeData(ea, FF_BYTE, 128, 0);
//	SetArrayFormat(ea, AP_IDXHEX, 128, 0);
//	Jump(ea + 128);


//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 63 BC 80", 2, 4, 5, "THRDA   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 A5 BC 80", 2, 4, 5, "THRDB   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 D7 BC 80", 2, 4, 5, "THRDC   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 84 BC 80", 2, 4, 5, "THRDD   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 09 BD 80", 2, 4, 5, "THRDE   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 19 BD 80", 2, 4, 5, "THRDF   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 29 BD 80", 2, 4, 5, "THRDG   %s");
//	far_sys_call_search_custom("A9 ?? ?? A0 ?? ?? 22 39 BD 80", 2, 4, 5, "THRDH   %s");


/*
	tmp0 = Word(ea) + (Byte(ea + 2) << 16);
	ea = make_far_ofs16_snes(ea, 0, 2, 3, "");
		tmp0 = make_far_ofs16_snes(tmp0, 0, 2, 3, "");
		tmp0 = make_data_array(tmp0, 6, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_data_array(tmp0, 4, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_far_ofs16_snes(tmp0, 0, 2, 3, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_far_ofs16_snes(tmp0, 0, 2, 3, "");
		tmp0 = make_near_ofs16_snes(tmp0, -1, "");
		tmp0 = make_far_ofs16_snes(tmp0, 0, 2, 3, "");
	MakeUnknown(ea, 6, DOUNK_SIMPLE);
	MakeWord(ea + 0);
	MakeWord(ea + 2);
	MakeWord(ea + 4);
	Jump(ea + 6); //*/

/*
	tmp2 = 0xBFCA0D;
	tmp0 = Word(ea);
	tmp1 = Byte(ea + 2) << 16;
	MakeUnknown(ea, 9, DOUNK_SIMPLE);
	MakeWord(ea);
	OpOffEx(ea, 0, REF_OFF16|REFINFO_NOBASE, -1, tmp1 + 1, 0);
	MakeName(Word(ea)+(Byte(ea+2)<<16)+1, form("_sys_call%03X",ea - tmp2));
	MakeWord(ea+2);
	MakeWord(ea+4);
	MakeByte(ea+6);
	MakeWord(ea+7);
	Jump(ea + 9); //*/

//	far_sys_call_search_customA("A9 ?? ?? A2 ?? ?? 22 97 DD 80", "CSYS    %s");

//	MakeUnknown(ea, 8, DOUNK_SIMPLE);
//	MakeByte(ea);
//	make_far_ofs16_snes(ea + 1, 0, 2, 3, "");
//	MakeByte(ea+4);
//	make_far_ofs16_snes(ea + 5, 0, 2, 3, "");
//	make_data_array(ea + 4, 4, "");
//	Jump(ea + 8);

///*
	while(Word(ea) != 0xFFFF) {
//		Message("block start 0x%06X\n",ea);
		MakeUnknown(ea, 2, DOUNK_SIMPLE);
		MakeWord(ea);
		OpOffEx(ea, 0, REF_OFF16|REFINFO_NOBASE, -1, 0x828010, 0);
		ea = ea + 2;
//		if(!isRef(GetFlags(ea)))
//			MakeName(ea, form("_unref_obj_res%06X",ea));
		while((tmp0 = Word(ea)) != 0xFFFF) {
//			Message(" chunk at0x%06X\n",ea);
			MakeUnknown(ea, 4, DOUNK_SIMPLE);
			if((tmp0 == 0x02)||(tmp0 == 0x08)||(tmp0 == 0x4C))
				MakeStructEx(ea, -1, "_tobj_o81");
			else
				MakeStructEx(ea, -1, "_tobj_val");
			ea = ea + 4;
		}
		MakeUnknown(ea, 2, DOUNK_SIMPLE);
		MakeWord(ea);
		ea = ea + 2;
//		Jump(ea);
	}
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
//*/
} // SHIFT-C

static make_string(ea) {
	auto tmp0 = ea, tmp1;
	while((tmp1 = Byte(tmp0)) != 0x00) {
		while ((tmp1 != 0x0D) && (tmp1 != 0x00)) {
			tmp0 = tmp0 + 1;
			tmp1 = Byte(tmp0);
		}
		if(tmp1 == 0x0D) {
			MakeStr(ea, tmp0 + 1);
			MakeName(ea, "");
			ea = tmp0 + 1;
			tmp0 = ea;
		} else {
			MakeStr(ea, tmp0 + 1);
			MakeName(ea, "");
		}
	}
	return tmp0 + 1;
}

static far_sys_call_search_custom(pat, b_lo, b_hi, bank, instr) {
	auto ea = -1, temp0, temp1;
	while((ea=FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		temp0 = (Byte(ea + bank) << 16) | (Byte(ea + b_lo) | (Byte(ea + b_hi) << 8));
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeCode(ea);
		SetManualInsn(ea, form(instr, Name(temp0)));
		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		AddCodeXref(ea, temp0, fl_CF|XREF_USER);
	}
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

static make_tbl16_gen(ea, docode) {
	auto base = ea;
	auto i = 0, w0, stop = 0;
	do {
		if((i&1)==0){
			MakeUnknown(ea + i, 2, DOUNK_SIMPLE);
			MakeWord(ea + i);
			w0 = Word(ea + i);
			OpOffEx(ea + i, 0, REF_OFF32|REFINFO_NOBASE, -1, base + i, 0);
			if(docode) {
				MakeCode(base + w0);
				AutoMark(base + w0, AU_CODE);
				Wait();
			}
			Wait();
		}
		i++;
		stop=(isRef(GetFlags(ea + i)));
	} while (!stop && (i < 0x10000));
}

static auto_tbl16() {
	if(SegByName("Z80")!=BADADDR) {	// GEN 16-bit tbl
		make_tbl16_gen(ScreenEA(),0);
	} else {
		make_tbl16_snes(ScreenEA(),0);
	}
}

static make_tbl32_gen(ea, docode) {
	auto base = 0;
	auto i = 0, w0, stop = 0, segsize = SegEnd(ea);
	do {
		if(((i&3)==0)&&(!stop)){
			MakeUnknown(ea + i, 4, DOUNK_SIMPLE);
			MakeDword(ea + i);
			w0 = Dword(ea + i);
			if((w0 < segsize) && (w0 > 0))
				OpOffEx(ea + i, 0, REF_OFF32, -1, base, 0);
			Wait();
		}
		i = i + 4;
		stop = isRef(GetFlags(ea + i)) |
		       isRef(GetFlags(ea + i + 1)) |
		       isRef(GetFlags(ea + i + 2)) |
		       isRef(GetFlags(ea + i + 3));	// assume the first offset always present, no need to stop here
	} while (!stop && (i < segsize));
//	Jump(ea + i);
}

static auto_tbl32_gen() {
	make_tbl32_gen(ScreenEA(),0);
}

static auto_rename() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto base;
	auto name_mask = AskStr("", "Enter Name Mask");
	auto name_increment = AskStr("", "Enter Increment");
	auto i = 0, ofs, nname;
	if (SegByName("ppu")!=BADADDR) {
		base = sea & 0xFF0000;
		while(sea < eea) {
			ofs = Word(sea);
			nname = form(name_mask,i);
			MakeNameEx(base + ofs, nname, SN_CHECK|SN_NOWARN);
			MakeComm(sea, "");
			MakeComm(sea, form("%02X",i));
			sea = sea + 2;
			i = i + name_increment;
		}
	} else if (SegByName("Z80")!=BADADDR) {
		base = 0;
		while(sea < eea) {
			ofs = Dword(sea);
			nname = form(name_mask,i);
			MakeNameEx(base + ofs, nname, SN_CHECK|SN_NOWARN);
			MakeComm(sea, "");
			MakeComm(sea, form("%02X",i));
			sea = sea + 4;
			i = i + name_increment;
		}
	} else
		Message("Unknown System!\n");
}

static auto_snes_registers() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto D_reg = AskLong("", "D=");
	auto B_reg = AskLong("", "B=");
	auto i = 0;
	if (SegByName("ppu")!=BADADDR) {
		while(sea < eea) {
			if(D_reg != -1)
				SetReg(sea, "D", D_reg);
			if(B_reg != -1) {
				SetReg(sea, "B", B_reg);
				SetReg(sea, "DS", B_reg << 12);
			}
			if(isCode(GetFlags(sea))) {
				auto D = GetReg(sea, "D");
				auto B = GetReg(sea, "B");
				auto x = GetReg(sea, "i");
				auto m = GetReg(sea, "m");
				MakeComm(sea, form("*.D%04X.B%02X.I%s.A%s",D,B,x?"8 ":"16", m?"8 ":"16"));
			}
			sea = sea + 1;
		}
	} else
		Message("Unsupported System!\n");
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
	auto ea = ScreenEA(), segend;
	auto i = 1;
	ea = FindUnexplored(ea - 1, SEARCH_DOWN);
	segend = SegEnd(ea);
	do {
		auto flags = GetFlags(ea + i);
		auto stop = (isUnknown(flags) && !isRef(flags)) && ((ea + i) != segend);
		i++;
	} while ((flags != 0) && (stop));
	i = i - 1;
	if(MakeData(ea, FF_BYTE, i, 0)) {
		if(SetArrayFormat(ea, AP_IDXHEX, 0x10, 0))
			Jump(ea);
		else
			Message("can't set array format!\n");

	} else
		Message("can't make data at 0x%08X size %08x!\n", ea, i);
}

// garbage labels collector
static garbage_search(loc) {
	auto ea = 0;
	while ((ea = FindText(ea,SEARCH_DOWN|SEARCH_REGEX,1,0,loc)) != BADADDR) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			Message(">no ref label '%s' at 0x%08x deleted\n", Name(ea), ea);
			MakeName(ea, "");
		}
//		else
//			Message(">ref label '%s' at 0x%08x\n", Name(ea), ea);
		ea = NextHead(ea, -1);
	}
}

static garbage_collector(void) {
	Message("garbage collector start\n");

	garbage_search("loc_.*:");
	garbage_search("unk_.*:");
	garbage_search("byte_.*:");
	garbage_search("word_.*:");
	garbage_search("off_.*:");
	garbage_search("a.*:");
//	garbage_search("_jloc.*:");
//	garbage_search("_j_prg.*:");
//	garbage_search("_j_j_.*:");
//	garbage_search("_jsub.*:");
//	garbage_search("_far.*:");
//	garbage_search("_mmc.*:");
//	garbage_search("_msg.*:");

	Message("garbage collector done\n");
}
