
// SCRIPT PARSE HELPERS
// -------------------

static make_auto_ofs16_gb(ea) {
	auto word0, bank0, base = -1;
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
	word0 = Word(ea);
	base = get_base_gb_common(ea, word0);
	if(base != -1)
		OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	return ea + 2;
}

static make_auto_ofs16_nes(ea) {
	auto ofs = Word(ea), bank = GetReg(ea,"ds")-1;
	if(ofs<0x800)
		ea = make_offset_ex(ea, 0, 0, 1);
	else
		ea = make_offset_ex(ea, bank, 0, 1);
/*	else if(ofs>=0xC000) {
		ea = make_offset_ex(ea, 7, 0, 1);
	} else {
		if((bank==7)&&(ofs<0xC000)) {
			ea = make_offset_ex(ea, AskLong(0, "Enter Bank Number"), 0, 1);
		} else
			ea = make_offset_ex(ea, bank, 0, 1);
	}*/
	return ea;
}

static auto_far_ptr() {
	auto ea = ScreenEA();
	auto_far_ptr_ex(ea,0,0);
}

static auto_far_ptr_ex(ea,mode,arg) {
	auto bofs, wofs, base, size, cnt, cnt0, cnt1, tmp0, tmp1;
	auto bank0 = GetReg(ea,"ds");

//	Message("far ptr at 0x%08x, mode %d, arg %d\n",ea,mode,arg);

	if(mode==12) {
//		ea = make_data_array(ea, 1, "");
//		ea = make_data_array(ea, 2, "");
//		cnt0 = Byte(ea);
//		ea = make_data_array(ea, 1, "");
//		for(cnt = 0; cnt < cnt0 / 4; cnt++)
//			ea = make_data_array(ea, 4, "");
//		ea = make_data_array(ea, 7, "");
/*
		ea = make_data_array(ea, 2, "");
		cnt0 = Byte(ea);
		ea = make_data_array(ea, 1, "");
		for(cnt = 0; cnt < cnt0 / 8; cnt++)
			ea = make_data_array(ea, 8, "");
		ea = make_data_array(ea, 1, "");
		ea = make_data_array(ea, 2, "");
		cnt0 = Byte(ea);
		cnt1 = Byte(ea+1);
		ea = make_data_array(ea, 2, "");
		for(cnt = 0; cnt < cnt1; cnt++)
			ea = make_data_array(ea, cnt0, "");
//*/
/*
		auto bank1 = Byte(ea);
		base = MK_FP(AskSelector(bank1 + 1), 0);
		MakeByte(ea);

		MakeUnknown(ea + 1, 8, DOUNK_SIMPLE);

		MakeWord(ea + 1);
		OpOffEx(ea + 1, 0, REF_OFF16, -1, base, 0);
		tmp1 = Word(ea + 1);
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
		Wait();

		MakeWord(ea + 3);
		OpOffEx(ea + 3, 0, REF_OFF16, -1, base, 0);
		tmp1 = Word(ea + 3);
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
		Wait();

		MakeWord(ea + 5);
		OpOffEx(ea + 5, 0, REF_OFF16, -1, base, 0);
		tmp1 = Word(ea + 5);
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
		Wait();

		MakeWord(ea + 7);
		OpOffEx(ea + 7, 0, REF_OFF16, -1, base, 0);
		tmp1 = Word(ea + 7);
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
		Wait();

		Jump(ea + 9);
*/
/*
		ea = make_data_array(ea, 2, "");
		MakeUnknown(ea, 6, DOUNK_SIMPLE);
		auto bank1 = Byte(ea);
		base = MK_FP(AskSelector(bank1 + 1), 0);
		MakeByte(ea);
		MakeWord(ea + 1);
		OpOffEx(ea + 1, 0, REF_OFF16, -1, base, 0);

		bank1 = Byte(ea + 3);
		base = MK_FP(AskSelector(bank1 + 1), 0);
		MakeByte(ea + 3);
		MakeWord(ea + 4);
		OpOffEx(ea + 4, 0, REF_OFF16, -1, base, 0);

		Jump(ea + 6);
*/
/*
			auto temp0 = MK_FP(AskSelector(Byte(ea + 0) + 1), 0);
			auto temp0A = temp0 + (Byte(ea + 1) << 1) + 0x8001;
			auto temp1 = temp0 + Word(temp0A);
			make_data_array(ea, 2, "");
			SetManualInsn(ea, form("FOFSi    %s", Name(temp1)));
			add_dref(ea, temp0A, dr_O|XREF_USER);
			add_dref(ea, temp1, dr_O|XREF_USER);
			Jump(ea + 2);
//*/
/*
		if(Byte(ea + 1)!=0x80) {
			auto temp0 = MK_FP(AskSelector(Byte(ea + 1) + 1), 0);
			auto temp0A = temp0 + (Byte(ea + 0) + 0x8001);
			auto temp1 = temp0 + Word(temp0A);
			make_data_array(ea, 2, "");
			SetManualInsn(ea, form("FOFS    %s", Name(temp1)));
			add_dref(ea, temp0A, dr_O|XREF_USER);
			add_dref(ea, temp1, dr_O|XREF_USER);
//			make_data_array(ea + 2, 4, "");
//			Jump(ea + 2 + 4);
			Jump(ea + 2);
		} else {
			make_data_array(ea, 2, "");
			Jump(ea + 2);
		}
//*/
	} else if(mode==11) {
		auto startea = ea, stop = 0;

		MakeName(ea, "");
		MakeName(ea, form("_msg_res%08x",ea));

		while(!stop) {
			auto cmd = Byte(ea);
//			Message("fetch %02x at 0x%08x\n",cmd, ea);
			if((cmd==0)||(cmd&0xF0)) {	// characters + spaces
				ea++;
			} else {
				if(startea != ea) {	// characters passed
					make_data_array(startea, ea - startea, "");
				}
				if(cmd==1) {
					ea = make_data_array(ea, 3, "");
				} else if((cmd==2)||(cmd==8)||(cmd==9)||(cmd==0xA)) {
					ea = make_data_array(ea, 1, "");
				} else if((cmd==6)||(cmd==7)) {
					ea = make_data_array(ea, 1, "");
					stop = 1;
				} else if((cmd==3)||(cmd==5)) {
					ea = make_data_array(ea, 1, "");
					ea = make_offset_ex(ea, bank0 - 1, 0, 1);
				} else if((cmd==4)||(cmd==0xB)) {
					ea = make_data_array(ea, 2, "");
					ea = make_offset_ex(ea, bank0 - 1, 0, 1);
				} else {
					Message("unk cmd %02x at 0x%08x\n",cmd, ea);
					stop = 1;
				}
				startea = ea;
			}
		}
		Jump(ea);
	} else if(mode==10) {
		MakeUnknown(ea, 1, DOUNK_SIMPLE);
		make_8bit_near_tbl(ea+1,ea+0,0,1);
		MakeWord(ea+2);
		if(Byte(ea+3)!=0) {
			make_8bit_near_tbl(ea+5,ea+4,0,0);
			MakeWord(ea+6);
			base = MK_FP(AskSelector(bank0), 0);
			OpOffEx(ea+6, 0, REF_OFF16, -1, base, 0);
			Jump(ea+8);
		} else {
			Jump(ea+4);
		}
	} else if(mode==9) {
//		ea=make_data_array(ea,2,"");
//		while (Byte(ea)&0x30) {
//		Message("start from 0x%08x\n",ea);
	    for(cnt=0;cnt<arg;cnt++) {
			MakeUnknown(ea, 15, DOUNK_SIMPLE);
			ea=make_data_array(ea,10,"");
			MakeWord(ea);
			wofs=Word(ea);
			if(wofs<0x4000)
				base = MK_FP(AskSelector(0), 0);
			else
				base = MK_FP(AskSelector(bank0), 0);
			if(wofs!=0) {
				OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
				MakeCode(base + wofs);
				AutoMark(base + wofs, AU_CODE);
			}
			MakeWord(ea+2);
			wofs=Word(ea+2);
			if(wofs<0x4000)
				base = MK_FP(AskSelector(0), 0);
			else
				base = MK_FP(AskSelector(bank0), 0);
			if(wofs!=0) {
				OpOffEx(ea + 2, 0, REF_OFF16, -1, base, 0);
				MakeCode(base + wofs);
				AutoMark(base + wofs, AU_CODE);
			}
			MakeByte(ea+4);
			ea=ea+5;
		}
//			ea=make_data_array(ea,1,"");
//			if(Word(ea)<0xA000)
//				ea=make_offset_ex(ea,0,0,1);
//			else if(Word(ea)<0xC000)
//				ea=make_offset_ex(ea,1,0,1);
//			else
//				ea=make_offset_ex(ea,2,0,1);
//		}
//		ea=make_data_array(ea,1,"");
//		if(Word(ea)<0xA000)
//				ea=make_offset_ex(ea,0,0,1);
//		else if(Word(ea)<0xC000)
//				ea=make_offset_ex(ea,1,0,1);
//		else
//				ea=make_offset_ex(ea,2,0,1);
//		Jump(ea);
	} else if(mode==8) {
		ea=FindBinary(ea+1, SEARCH_DOWN|SEARCH_CASE, "FA FF 7F 67 2E ?? E5 75 C3 ?? ??");
		if(ea!=BADADDR) {
			MakeUnknown(ea, 11, DOUNK_SIMPLE);
			MakeCode(ea);
			AutoMark(ea, AU_CODE);
			Wait();
			far_ptr_code(ea, 5, 9, 1, -1);
			Jump(ea+10);
		}
	} else if(mode==7) {
		auto bt;
		while ((bt=Byte(ea))!=0xFF) {
			MakeUnknown(ea, 7, DOUNK_SIMPLE);
			MakeByte(ea+0);
			MakeWord(ea+1);
			MakeWord(ea+3);
			MakeWord(ea+5);
			far_ptr(ea+5, -5, 0, 0, 0);
			ea=ea+7;
		}
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeByte(ea+0);
		MakeWord(ea+1);
		far_ptr(ea+1, -1, 0, 0, 0);
		Jump(ea+3);
	} else if(mode==6) {
		size = 9;
		MakeUnknown(ea, size, DOUNK_SIMPLE);
		MakeByte(ea+0);
		MakeWord(ea+1);
		far_ptr(ea+1, 2, 0, 0, 0);
		MakeByte(ea+3);
		MakeWord(ea+4);
		far_ptr(ea+4, 2, 0, 0, 0);
		MakeByte(ea+6);
		MakeWord(ea+7);
		far_ptr(ea+6, 0, 1, 0, 0);
		Wait();
		Jump(ea+size);
	// --
	} else if(mode == 5) {
		auto loofs = 1;
		auto hiofs = 0;
		auto bbank = 2;
		size = 3;
		MakeUnknown(ea, size, DOUNK_SIMPLE);
		MakeByte(ea);
		MakeByte(ea+1);
		MakeByte(ea+2);
		auto addr = Byte(ea+loofs)|(Byte(ea+hiofs)<<8);
		base = MK_FP(AskSelector(Byte(ea+bbank)), 0);
		OpOffEx(ea + loofs, 0, REF_LOW8, base + addr, base, 0);
		OpOffEx(ea + hiofs, 0, REF_HIGH8, base + addr, base, 0);
		Wait();
		Jump(ea + size);
	} else if(mode == 4) {
	// simple far link
		auto base0, ofs0, name;
		ea = -1;
		while ((ea=FindBinary(ea+1, SEARCH_DOWN, "21 ?? ?? DF"))!=BADADDR) {
			if(isCode(GetFlags(ea)))
				MakeUnknown(ea, 3, DOUNK_SIMPLE);
			MakeCode(ea);
			AutoMark(ea, AU_CODE);
			Wait();
//			Message("ea=0x%08x ", ea);
			base0 = MK_FP(AskSelector(Byte(ea+2)), 0);
//			Message("base=0x%08x ", base0);
			ofs0 = base0 + 0x4001 + (Byte(ea+1)<<1);
//			Message("ofs0=0x%08x ", ofs0);
			ofs0 = base0 + Word(ofs0);
//			Message("ofs1=0x%08x\n", ofs0);
			MakeCode(ofs0);
			AutoMark(ofs0, AU_CODE);
			Wait();
			name = NameEx(BADADDR, ofs0);
			if(name == "") {
				MakeComm(ea, "");
				MakeComm(ea, form("0x%08x",ofs0));
			} else {
				MakeComm(ea, "");
				MakeComm(ea, form("%s", name));
			}
			AddCodeXref(ea, ofs0, fl_CF);
		}
	} else if(mode == 3) {

		while (Byte(ea) != 0) {
			MakeUnknown(ea, 7, DOUNK_SIMPLE);
			MakeByte(ea + 0);
			MakeByte(ea + 1);
			MakeWord(ea + 2);
			far_ptr(ea, 1, 2, 0, 0);
			make_data_array(ea + 4, 3, "");
			ea = ea + 7;
		}
		MakeUnknown(ea, 1, DOUNK_SIMPLE);
		MakeByte(ea + 0);
		ea = ea + 1;
		Jump(ea);
	} else if(mode == 2) {
	// custom far resources	bank/ofs/dst/size

		MakeUnknown(ea, 11, DOUNK_SIMPLE);

		MakeWord(ea + 0);
		MakeWord(ea + 2);
		MakeWord(ea + 4);
		MakeByte(ea + 6);
		MakeWord(ea + 7);
		MakeWord(ea + 9);

		far_ptr(ea, 6, 0, 0, 0);
		far_ptr(ea, 6, 2, 0, 0);
		far_ptr(ea, 6, 4, 0, 0);
		far_ptr(ea, 6, 7, 0, 0);
		far_ptr(ea, 6, 9, 0, 0);

		Jump(ea + 11);
	// --
	} else if(mode == 1) {
	// custom far resources	bank/ofs/dst/size
		auto i,j,k;
		i=Byte(ea);
		MakeWord(ea);
		ea=ea+2;
		j=0;
		while(j<i) {
			size = 6;
			MakeUnknown(ea, size, DOUNK_SIMPLE);
			MakeWord(ea + 0);
			MakeWord(ea + 2);
			MakeWord(ea + 4);
			far_ptr(ea, 3, 4, 0, 0);
			ea = ea + size;
			j++;
		}
		Jump(ea);
	// --
	} else {
//		cnt1 = Byte(ea);
//		MakeUnknown(ea, 1, DOUNK_SIMPLE);
//		MakeByte(ea);
//		ea = ea + 1;
//		for(i=0; i<cnt1; i++) {

//		ea = -1;
//		auto pat = "E5 21 FF 7F EA 50 21 BE 20 FA E1", instr = "MMC_PRG_SET";
//		while((ea=FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
//			Message("found pattern at 0x%08x\n", ea);
//			make_data_array(ea, ((strlen(pat) + 1) / 3), "");
//			SetManualInsn(ea, instr);
//		}
/*
//		bofs = 1;
//		wofs = 2;
//		size = 4;
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeWord(ea);
		MakeByte(ea + 2);
		OpOffEx(ea, 0, REF_OFF16, -1, MK_FP(AskSelector(bank0), 0), 0);
		Jump(ea + 3);*/
/*
		auto v0 = Byte(ea);
		if(v0 == 0) {
			MakeUnknown(ea, 1, DOUNK_SIMPLE);
			MakeByte(ea);
		} else {
			MakeUnknown(ea, (v0 * 4) + 3, DOUNK_SIMPLE);
			MakeByte(ea);
			MakeWord(ea+1);
			ea = ea + 3;
			for(cnt=0;cnt<v0;cnt++)
				ea = make_data_array(ea, 4, "");
		}
//		Jump(ea); //*/

/*
		MakeUnknown(ea, 8, DOUNK_SIMPLE);
		MakeWord(ea + 0);
		MakeByte(ea + 2);
		MakeByte(ea + 3);
		MakeByte(ea + 4);
		MakeByte(ea + 5);
		MakeWord(ea + 6);
		base = MK_FP(AskSelector(Byte(ea + 6)), 0);
		addr = Byte(ea + 3) | (Byte(ea + 2) << 8);
		OpOffEx(ea + 2, 0, REF_HIGH8, base + addr, base, 0);
		OpOffEx(ea + 3, 0, REF_LOW8, base + addr, base, 0);
		addr = Byte(ea + 5) | (Byte(ea + 4) << 8);
		OpOffEx(ea + 4, 0, REF_HIGH8, base + addr, base, 0);
		OpOffEx(ea + 5, 0, REF_LOW8, base + addr, base, 0);
		Jump(ea + 8);
//*

/*
		auto v0 = Byte(ea), v1;
		if((v0==0x4)||(v0==0x9)) {
			MakeUnknown(ea, 6, DOUNK_SIMPLE);
			ea = make_data_array(ea, 1, "");
			v1 = Byte(ea + 4);
			make_data_array(ea, 1, "");
			make_data_array(ea + 1, 1, "");

			addr = Byte(ea + 1) | (Byte(ea) << 8);
			if(addr < 0x4000) v1 = 0;
			base = MK_FP(AskSelector(v1), 0);
			OpOffEx(ea + 1, 0, REF_LOW8, base + addr, base, 0);
			OpOffEx(ea, 0, REF_HIGH8, base + addr, base, 0);

			ea = ea + 2;
			ea = make_data_array(ea, 3, "");
		} else if((v0==0x1)) {
			MakeUnknown(ea, 9, DOUNK_SIMPLE);
			ea = make_data_array(ea, 1, "");
			v1 = Byte(ea + 7);
			make_data_array(ea, 1, "");
			make_data_array(ea + 1, 1, "");

			addr = Byte(ea + 1) | (Byte(ea) << 8);
			if(addr < 0x4000) v1 = 0;
			base = MK_FP(AskSelector(v1), 0);
			OpOffEx(ea + 1, 0, REF_LOW8, base + addr, base, 0);
			OpOffEx(ea, 0, REF_HIGH8, base + addr, base, 0);

			ea = ea + 2;
			ea = make_data_array(ea, 6, "");
		} else {
//			ea = ea - 1;
		}
		Jump(ea); //*/

///* SIMPLE FAR OFS
//if(Word(ea)!=0xFFFF) {
		bofs = 0;
		wofs = 1;
//		if(Byte(ea) == 5)
//			size = 6;
//		else if(Byte(ea) == 4)
//			if((Byte(ea + 6) & 0x80))
//				size = 8;
//			else
//				size = 7;
//		else
			size = 3;
//if((Byte(ea) != 0xFF)) {
		MakeUnknown(ea, size, DOUNK_SIMPLE);
//		make_data_array(ea, size, "");
//} else {
		MakeByte(ea + bofs);
//		MakeWord(ea + bofs);
		MakeWord(ea + wofs);
		//MakeWord(ea + wofs + 2);
//		MakeWord(ea + wofs + 4);
//		if(Word(ea + wofs) > 0x4000)
			base = MK_FP(AskSelector(Byte(ea + bofs)), 0);
//		else
//			base = 0;
//		if(Byte(ea) != 4)
			OpOffEx(ea + wofs, 0, REF_OFF16, -1, base, 0);
//		MakeWord(ea + wofs + 2);
//			OpOffEx(ea + wofs + 2, 0, REF_OFF16, -1, base, 0);
//		base = get_base_gb_common(ea + wofs + 2, Word(ea + wofs + 2));
//		if(Byte(ea) != 4)
//			OpOffEx(ea + wofs + 2, 0, REF_OFF16, -1, base, 0);
//		if(size == 8)
//			MakeWord(ea + wofs + 4);
//		else if(size == 7)
//			MakeByte(ea + wofs + 4);
//		MakeData(ea + 3, FF_BYTE, 5, 0);
//		SetArrayFormat(ea + 3, AP_IDXHEX, 5, 0);
//		MakeWord(ea + 4);
//		MakeWord(ea + 6);
//		MakeByte(ea + wofs + 2);
//}

//		MakeByte(ea + 0);
//		MakeByte(ea + 1);
//		MakeWord(ea + 2);
//		base = MK_FP(AskSelector(Byte(ea + 1)), 0);
//		OpOffEx(ea + 2, 0, REF_OFF16, -1, base, 0);
//		MakeByte(ea + 4);
//		MakeWord(ea + 1 + 4);
//		base = MK_FP(AskSelector(Byte(ea + 4)), 0);
//		OpOffEx(ea + 1 + 4, 0, REF_OFF16, -1, base, 0);
//		MakeByte(ea + 7);
//		MakeWord(ea + 1 + 7);
//		base = MK_FP(AskSelector(Byte(ea + 7)), 0);
//		OpOffEx(ea + 1 + 7, 0, REF_OFF16, -1, base, 0);
//		make_data_array(ea + 3 + 7, 2, "");

//		MakeWord(ea + wofs);
//		MakeWord(ea + wofs + 2);
//		MakeWord(ea + wofs);
//		make_data_array(ea + 4, 4, "");
//		MakeByte(ea + bofs);
//		MakeWord(ea + 3);
//		MakeByte(ea + 0);
//		base = MK_FP(AskSelector(Byte(ea + bofs) & 0x7F), 0);
//		OpOffEx(ea + wofs, 0, REF_OFF16, -1, base, 0);
		Jump(ea + size);
//  }else {
//		MakeUnknown(ea, 1, DOUNK_SIMPLE);
//		MakeByte(ea);
//		MakeWord(ea + 0);
//		base = MK_FP(AskSelector(0), 0);
//		OpOffEx(ea + 1, 0, REF_OFF16, -1, base, 0);
//		Jump(ea + 1);
//}
//*/

/*
		tmp0 = MK_FP(AskSelector(Byte(ea + 2)), 0);
		tmp0 = tmp0 + (Byte(ea + 1) * 3) + 0x4000;
		SetManualInsn(ea, form("ld      de, %s", Name(tmp0)));
		AddCodeXref(ea, tmp0, fl_CF|XREF_USER);
		make_code(tmp0);
//*/

/*
		tmp0 = MK_FP(AskSelector(Byte(ea + 2)), 0);
		tmp1 = (Byte(ea + 3) * 2) + 0x4000;
		tmp1 = Word(tmp0 + tmp1);
		tmp0 = tmp0 + tmp1;
		MakeUnknown(ea, 4, DOUNK_SIMPLE);
		MakeData(ea, FF_BYTE, 4, 0);
		SetArrayFormat(ea, AP_IDXHEX, 4, 0);
		SetManualInsn(ea, form("CHR_SYS %04X, %s", Word(ea + 0), Name(tmp0)));
//		AddCodeXref(ea, tmp0, fl_CF|XREF_USER);
		add_dref(ea, tmp0, dr_O|XREF_USER);
//		make_code(tmp0);
		Jump(ea+4);
//*/

/*
		auto t0 = 0x7bad9, t1 = 0x7bb2a;
		tmp0 = 0x78000;
		tmp1 = 0;
		while(t0 + tmp1 < t1) {
			tmp0 = tmp0 + Byte(t0 + tmp1);
			tmp1 = tmp1 + 1;
			MakeName(tmp0,form("_room_2p%02X",tmp1));
		}

//		MakeUnknown(ea, cnt0 + 1, DOUNK_SIMPLE);
//		MakeData(ea, FF_BYTE, cnt0 + 1, 0);
//		SetArrayFormat(ea, AP_IDXHEX, 16, 0);

//*/
/*
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeByte(ea + 0);
		make_8bit_near_tbl(ea + 2, ea + 1, -1, 1);
		Jump(ea + 3);
//*/
/*
		auto t0 = Byte(ea);
		auto namae = "";
		MakeUnknown(ea, t0+3, DOUNK_SIMPLE);
		for(cnt = 0; cnt < t0; cnt++) {
			auto tmpchar;
			tmpchar = sprintf("%c",Byte(ea+cnt+1)-0x80);
			namae = namae + tmpchar;
		}
		ea = make_data_array(ea, t0+1, namae);
		MakeWord(ea);
		ea = make_auto_ofs16_gb(ea);
		Jump(ea);
//*/
	// --
	}
}

static make_data_array_custom(ea, len, dur, cmt) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
//	if(len == 2) {
//		MakeWord(ea);
//	} else {
		MakeData(ea, FF_BYTE, len, 0);
		SetArrayFormat(ea, AP_IDXHEX, dur, 0);
//	}
	MakeComm(ea, "");
	MakeComm(ea, cmt);
	return ea + len;
}

static make_data_array(ea, len, cmt) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
//	if(len == 2) {
//		MakeWord(ea);
//	} else {
		MakeData(ea, FF_BYTE, len, 0);
		SetArrayFormat(ea, AP_IDXHEX, 16, 0);
//	}
	MakeComm(ea, "");
	MakeComm(ea, cmt);
	return ea + len;
}

static make_offset(ea, bank) {
	return make_offset_ex(ea, bank, 0, 0);
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

static make_offset_ex(ea, bank, execute, nomsg) {
	auto base, ptr = Word(ea);
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeData(ea, FF_WORD, 1, 0);
	if(ptr < 0x8000)
		base = MK_FP(AskSelector(0), 0);
	else
		base = MK_FP(AskSelector(bank + 1), 0);
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	if(execute) {
		make_code(base + ptr);
		Wait();
	}
	if(!nomsg) {
		MakeComm(ea, "");
		MakeComm(ea,  form("ofs 0x%08x", base + ptr));
	}
	return ea + 2;
}

static make_offset_d(ea, bank) {
	auto base, ptr = Word(ea);
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeData(ea, FF_WORD, 1, 0);
	if(ptr < 0x8000)
		base = MK_FP(AskSelector(0), 0);
	else
		base = MK_FP(AskSelector(bank + 1), 0);
	OpOffEx(ea, 0, REF_OFF16, -1, base, -1);
	return ea + 2;
}

static make_offset_gb(ea, bank) {
	auto base, ptr = Word(ea);
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeData(ea, FF_WORD, 1, 0);
	base = MK_FP(AskSelector(bank), 0);
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
//	MakeComm(ea, "");
//	MakeComm(ea,  form("ofs 0x%08x", base + ptr));
	return ea + 2;
}

static make_offset_gb_code(ea, bank) {
	auto base, ptr = Word(ea);
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeData(ea, FF_WORD, 1, 0);
	base = MK_FP(AskSelector(bank), 0);
	OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	make_code(base + ptr);
//	MakeCode(base + ptr);
//	AutoMark(base + ptr, AU_CODE);
	Wait();
//	MakeComm(ea, "");
//	MakeComm(ea,  form("ofs 0x%08x", base + ptr));
	return ea + 2;
}

static make_name(ea, bank, name) {
	auto base, ptr = Word(ea);
	if(ptr < 0x8000)
		base = MK_FP(AskSelector(0), 0);
	else
		base = MK_FP(AskSelector(bank + 1), 0);
	MakeName(base + ptr, "");
	MakeName(base + ptr, form("%s%X", name, base + ptr));
}

// BASE SYSTEM FUNCTIONS!

static getSegSize(seg) {
	auto j, segstart, segea;
	for (j=0x8000; j<0x10000; j=j+0x1000) {
		segea = MK_FP(AskSelector(seg),j);
		segstart = SegStart(segea);
		if(segstart != BADADDR) {
			return SegEnd(segea)-segstart;
		}
	}
	segea = MK_FP(AskSelector(seg),0x6000);
	segstart = SegStart(segea);
	if(segstart != BADADDR) {
		return SegEnd(segea)-segstart;
	}
	return -1;
}

static getSegOrg(seg) {
	auto k, segstart, segea;
	for (k=0x8000; k<0x10000; k=k+0x1000) {
		segea = MK_FP(AskSelector(seg),k);
		if(SegStart(segea) != BADADDR) {
			return k;
		}
	}
	segea = MK_FP(AskSelector(seg),0x6000);
	if(SegStart(segea) != BADADDR) {
		return 0x6000;
	}
	return -1;
}

// PARAMETRIC FUNCTIONS

static parametric_fixsize(opcode, size) {
	auto ea = -1;
	Message(" Fixsize search for \"%s\" start!\n", opcode);
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN|SEARCH_CASE, opcode);
		if(ea != BADADDR) {
			Message(" >found one at 0x%08x\n", ea);
			MakeUnknown(ea, size + 3 + 3, DOUNK_SIMPLE);
			if(size == 2) {
				MakeWord(ea + 3);
				make_auto_ofs16_nes(ea+3);
			}
			else
				MakeData(ea + 3, FF_BYTE, size, 0);
			MakeCode(ea);
			AutoMark(ea + size + 3, AU_CODE);
		}
	} while (ea != BADADDR);
	Wait();
	Message(" Done!\n");
}

static parametric_farcall(opcode, size, segmask, bankop, ofsop, delta, shift, dobankbyte) {
	auto ea = -1;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN|SEARCH_CASE, opcode);
		if(ea != BADADDR) {
			auto bank, base, offs;
//			Message("Pattern found at %08x\n", ea);
			MakeUnknown(ea, size + 3, DOUNK_SIMPLE);

			offs = Word(ea + ofsop);
			if(offs > 0xC000)
				bank = 15 + 1;
			else
				bank = ((Byte(ea + bankop) << shift) & segmask) + 1;
//			else
//				bank = ((Byte(ea + bankop) << shift) & segmask) + 2;
			if(dobankbyte)
				MakeByte(ea + bankop);
			base = MK_FP(AskSelector(bank), 0);
			MakeWord(ea + ofsop);
			OpOffEx(ea + ofsop, 0, REF_OFF16, -1, base, delta);

			MakeCode(ea);
			AutoMark(ea + size + 3, AU_CODE);
			MakeCode(ea + size + 3);
			AutoMark(base + offs, AU_CODE);
			MakeCode(base + offs);
			Wait();
		}
	} while (ea != BADADDR);
//	Message("Done\n");
}

static parametric_stopbytes(opcode, stopbytes) {
	auto size, db, ea = -1;
//	Message("Start at %08x stopbyte %s %s\n", ea, opcode, stopbytes);
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN|SEARCH_CASE, opcode);
		if(ea != BADADDR) {
//			Message("Pattern found at %08x\n", ea);
			size = FindBinary(ea + 3, SEARCH_DOWN|SEARCH_CASE, stopbytes);
			MakeUnknown(ea, size - ea + 3, DOUNK_SIMPLE);
			MakeData(ea + 3, FF_BYTE, size - ea - 2, 0);
			MakeCode(ea);
			//AutoMark(size + 3, AU_CODE);
			Wait();
		}
	} while (ea != BADADDR);
//	Message("Done\n");
}

static parametric_switch(opcode) {
	auto ea = -1;
//	Message("Start at %08x switch for\n", ea);
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN|SEARCH_CASE, opcode);
		if(ea != BADADDR) {
			make_16bit_near_tbl(ea, 0);
			MakeUnknown(ea, 3, DOUNK_SIMPLE);
			MakeCode(ea);
			AutoMark(ea, AU_CODE);
			Wait();
		}
	} while (ea != BADADDR);
//	Message("Done\n");
}

// MAKE TABLES HELPERS

static make_16bit_near_tbl(ea, ofs) {
	auto base, minea, curea, maxea, size, dw;
	base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
	maxea = base + 0xFFFF;
	size = 0;
	do {
		dw = Word(ea + size + 3);
		curea = base + dw;
		if(curea < maxea) maxea = curea;
		MakeUnknown(ea + size + 3, 3, DOUNK_SIMPLE);
		MakeWord(ea + size + 3);
		OpOffEx(ea + size + 3, 0, REF_OFF16, curea - ofs, base, ofs);
//		OpOffEx(ea + size + 3, 0, REF_OFF16, -1, base, ofs);
		MakeUnknown(curea - ofs, 3, DOUNK_SIMPLE);
		MakeCode(curea - ofs);
		AutoMark(curea - ofs, AU_CODE);
		size = size + 2;
	} while (ea + size + 3 < (maxea - ofs));
	Wait();
	MakeCode(ea + size + 3);
	AutoMark(ea + size + 3, AU_CODE);
	MakeCode(maxea - ofs);
	AutoMark(maxea - ofs, AU_CODE);
	Wait();
}

static make_8bit_ofs(ea, loofs, hiofs, ofs) {
	auto base = BADADDR, addr = Byte(ea + loofs + 1) | (Byte(ea + hiofs + 1) << 8), extbank = -1, extbase;
		if(SegByName(form("ROM%X",0))==BADADDR) {	// NES mode
			base = get_base_nes_common(ea, addr);
		} else {
			base = get_base_gb_common(ea, addr);
		}
		if(base == -1)
		{
			if(extbank == -1) {
				extbank = AskLong(1, form("Enter External Bank 0 (ea = %08X addr = %04X)",ea,addr) );
				extbase = MK_FP(AskSelector(extbank + 1), 0);
			}
			base = extbase;
		}
	if(base != BADADDR) {
		OpOffEx(ea + loofs, 0, REF_LOW8, base + addr - ofs, base, ofs);
		OpOffEx(ea + hiofs, 0, REF_HIGH8, base + addr - ofs, base, ofs);
	} else
		Message(" 8bit offset in bad range!\n");
}

static make_8bit_far_ofs(ea, loofs, hiofs, ofs, bank) {
	auto base, arg = 0, addr = Byte(ea + loofs + 1) | (Byte(ea + hiofs + 1) << 8);
	if(SegByName("ROM0")!=BADADDR) {	// GB mode
		bank = bank - 1;
		arg = 1;
		if(addr < 0x4000) bank = 0;
	}
	base = MK_FP(AskSelector(bank), 0);
	OpOffEx(ea + loofs, arg, REF_LOW8, base + addr - ofs, base, ofs);
	OpOffEx(ea + hiofs, arg, REF_HIGH8, base + addr - ofs, base, ofs);
}

static make_8bit_near_tbl(loaddr, hiaddr, ofs, code) {
	auto i, size, extbank = -1,extbase;
	if(hiaddr > loaddr)
		size = hiaddr - loaddr;
	else
		size = loaddr - hiaddr;
	MakeUnknown(loaddr, size, DOUNK_SIMPLE);
	MakeUnknown(hiaddr, size, DOUNK_SIMPLE);
//	Message(form("debug lo = %08x, hi = %08x\n",loaddr, hiaddr));

	for(i=0; i<size; i++) {
		auto lptr, hptr, base, bank, refptr;
		lptr = Byte(loaddr + i);
		hptr = Byte(hiaddr + i);
		refptr = lptr | (hptr << 8);
		if(SegByName(form("ROM%X",0))==BADADDR) {	// NES mode
			base = get_base_nes_common(loaddr, refptr);
		} else {
			base = get_base_gb_common(loaddr, refptr);
		}
		if(base == -1) {
			if(extbank == -1) {
				extbank = AskLong(1, "Enter External Bank 1");
				if(SegByName(form("ROM%X",0))==BADADDR)	// NES mode
					extbank = extbank + 1;
			}
			extbase = MK_FP(AskSelector(extbank), 0);
			base = extbase;
		}
		MakeByte(loaddr + i);
		if(refptr!=0)
			OpOffEx(loaddr + i, 0, REF_LOW8, base + refptr - ofs, base, ofs);
		MakeByte(hiaddr + i);
		if(refptr!=0)
			OpOffEx(hiaddr + i, 0, REF_HIGH8, base + refptr - ofs, base, ofs);
		if (code)
			AutoMark(base + refptr - ofs, AU_CODE);
	}
}

static make_8bit_far_tbl(loaddr, hiaddr, bankaddr, nsize, delta) {
	auto i, size, bank; // = bankaddr;
	if(nsize == 0)
		size = hiaddr - loaddr;
	else
		size = nsize;
	MakeUnknown(loaddr, size, DOUNK_SIMPLE);
	MakeUnknown(hiaddr, size, DOUNK_SIMPLE);
	MakeUnknown(bankaddr, size, DOUNK_SIMPLE);
	Message(form("far table lo = %08x, hi = %08x, bank = %08x\n",loaddr, hiaddr, bankaddr));
	for(i=0; i<size; i++) {
		auto lptr, hptr, base, refptr, bankn;
		lptr = Byte(loaddr + i);
		hptr = Byte(hiaddr + i);
		refptr = lptr | (hptr << 8);
		if (refptr<0xE000) {
			bankn = Byte(bankaddr + i);
			bank = bankn & 0xF;
		} else
			bank = 0x0f;
		base = MK_FP(AskSelector(bank + 1), 0);
		MakeByte(loaddr + i);
		if(refptr!=0)
			OpOffEx(loaddr + i, 0, REF_LOW8, base + refptr + delta, base, delta);
		MakeByte(hiaddr + i);
		if(refptr!=0)
			OpOffEx(hiaddr + i, 0, REF_HIGH8, base + refptr + delta, base, delta);
/*
	MakeUnknown(loaddr, size, DOUNK_SIMPLE);
	MakeUnknown(hiaddr, size, DOUNK_SIMPLE);
	for(i=0; i<size; i++) {
		auto lptr, hptr, base, refptr, bankn;
		lptr = Byte(loaddr + i);
		hptr = Byte(hiaddr + i);
		refptr = (lptr | ((hptr & 0x3F) << 8))|0x8000;
		bank = (hptr >> 6)&3;
		base = MK_FP(AskSelector(bank + 1), 0);
		MakeByte(loaddr + i);
		OpOffEx(loaddr + i, 0, REF_LOW8, base + refptr, base, 0);
		MakeByte(hiaddr + i);
		OpOffEx(hiaddr + i, 0, REF_HIGH8, base + refptr, base, (0x8000-((hptr & 0xC0)<< 8)) - base);
*/
	}
}

// HOTKEY FUNCTIONS

static make_8bit_ofs_selection2() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 2, 0);
}

static make_8bit_far_ofs_selection2() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 2");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 0, 2, 0, bank + 1);
}

static make_8bit_ofs_selection2_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 2, 0, 0);
}

static make_8bit_far_ofs_selection2_i() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 3");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 2, 0, 0, bank + 1);
}

static make_8bit_ofs_selection3() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 3, 0);
}

static make_8bit_ofs_selection3_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 3, 0, 0);
}

static make_8bit_ofs_selection3_d_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 3, 0, -1);
}

static make_8bit_far_ofs_selection3_i() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 4");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 3, 0, 0, bank + 1);
}

static make_8bit_ofs_selection4() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 4, 0);
}

static make_8bit_far_ofs_selection4() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 5");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 0, 4, 0, bank + 1);
}

static make_8bit_ofs_selection4_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 4, 0, 0);
}

static make_8bit_far_ofs_selection4_i() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 6");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 4, 0, 0, bank + 1);
}

static make_8bit_ofs_selection5() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 5, 0);
}

static make_8bit_far_ofs_selection5() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 7");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 0, 5, 0, bank + 1);
}

static make_8bit_ofs_selection5_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 5, 0, 0);
}

static make_8bit_ofs_selection6() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 6, 0);
}

static make_8bit_ofs_selection6_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 6, 0, 0);
}

static make_8bit_ofs_selection7() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 0, 7, 0);
}

static make_8bit_ofs_selection7_i() {
	auto ea = ScreenEA();
	if(ea != BADADDR)
		make_8bit_ofs(ea, 7, 0, 0);
}

static make_8bit_far_ofs_selection6() {
	auto ea = ScreenEA();
	auto bank = AskLong(0, "Enter Bank Number 8");
	if(ea != BADADDR)
		make_8bit_far_ofs(ea, 0, 6, 0, bank + 1);
}

static make_8bit_near_selection() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto mea, b0;
	if((sea == BADADDR) || (eea == BADADDR)) {
		sea = ScreenEA();
		if(Word(sea)<0x8000)
			b0 = 0;
		else if(Word(sea)<0xC000)
			b0 = GetReg(sea, "ds") - 1;
		else if(Word(sea)<0xE000)
			b0 = 0x3E;
		else
			b0 = 0x3F;
		Jump(make_offset_ex(sea, b0, 0, 1));
	} else {
		mea = (sea + eea) / 2;
		make_8bit_near_tbl(sea, mea, 0, 0);
	}
}

static make_8bit_near_selection_d() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto mea, b0;
	if((sea == BADADDR) || (eea == BADADDR)) {
		sea = ScreenEA();
		if(Word(sea)<0xE000)
			b0 = GetReg(sea, "ds") - 1;
		else
			b0 = 0x3F;
		Jump(make_offset_d(sea, b0));
	} else {
		mea = (sea + eea) / 2;
		make_8bit_near_tbl(sea, mea, -1, 1);
	}
}

static make_8bit_near_selection_i() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto mea;
	if((sea == BADADDR) || (eea == BADADDR)) {
		sea = ScreenEA();
		mea = sea + 1;
		make_8bit_near_tbl(mea, sea, 0, 0);
		Jump(sea + 2);
	} else {
		mea = (sea + eea) / 2;
		make_8bit_near_tbl(mea, sea, 0, 0);
	}
}

static make_8bit_near_selection_d_i() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto mea;
	if((sea == BADADDR) || (eea == BADADDR)) {
		sea = ScreenEA();
		mea = sea + 1;
		make_8bit_near_tbl(mea, sea, -1, 1);
		Jump(sea + 2);
	} else {
		mea = (sea + eea) / 2;
		make_8bit_near_tbl(mea, sea, -1, 1);
	}
}

static get_base_nes_common(ea, addr) {
	auto base = -1;
	auto segsize, segorg, segbase, segname, segidx;
	ea = SegStart(ea);
	segname = SegName(ea);
	segidx = SegByName(segname);
	if(segidx == -1) {
		if(substr(segname,0,4) == "BANK") {
			segidx = xtol(substr(segname,4,-1)) + 1;
		}
	}
	segbase = MK_FP(AskSelector(segidx),0);
	segorg = ea - segbase;
	segsize = SegEnd(ea) - ea;
	if(addr < 0x6000) {
		base = MK_FP(AskSelector(0),0);
	} else if((addr >= segorg) && (addr < (segorg + segsize))) {
		base = segbase;
//
	} else if(addr >= 0xC000) { // CUSTOM
		base = MK_FP(AskSelector(15 + 1),0);;
//
	} else if(addr < 0x8000) {
		base = MK_FP(AskSelector(0),0);
	}

//	Message("Seg EA=%08x, BASE=%08x ORG=%04x SIZE=%04x RESULT=%04x\n", ea, segbase, segorg, segsize, base);

	return base;
}

static get_base_gb_common(ea, addr) {
	auto base = -1;
	auto bank = GetReg(ea,"ds");
	if(addr < 0x4000)
		base = MK_FP(AskSelector(0), 0);
	else if((addr >= 0x4000) && (addr < 0x8000)) {
		if(bank > 0)
			base = MK_FP(AskSelector(bank), 0);
//		else
//			base = MK_FP(AskSelector(AskLong(0, "Enter Bank Number")), 0);
	} else if((addr >= 0x8000) && (addr < 0x9800))
		base = MK_FP(AskSelector(SegByName("CHRRAM")),0);
	else if((addr >= 0x9800) && (addr < 0x9C00))
		base = MK_FP(AskSelector(SegByName("BGMAP1")),0);
	else if((addr >= 0x9C00) && (addr < 0xA000))
		base = MK_FP(AskSelector(SegByName("BGMAP2")),0);
	else if((addr >= 0xA000) && (addr < 0xC000))
		base = MK_FP(AskSelector(SegByName("CRAM")),0);
	else if((addr >= 0xC000) && (addr < 0xD000))
		base = MK_FP(AskSelector(SegByName("RAM0")),0);
	else if((addr >= 0xD000) && (addr < 0xE000))
		base = MK_FP(AskSelector(SegByName("RAMB")),0);
	else if((addr >= 0xFE00) && (addr < 0xFEA0))
		base = MK_FP(AskSelector(SegByName("OAM")),0);
	else if((addr >= 0xFF00) && (addr < 0xFF80))
		base = MK_FP(AskSelector(SegByName("HWREGS")),0);
	else if((addr >= 0xFF80) && (addr < 0xFFFF))
		base = MK_FP(AskSelector(SegByName("ZRAM")),0);
	else if(addr == 0xFFFF)
		base = MK_FP(AskSelector(SegByName("IENABLE")),0);
	return base;
}

static make_8bit_ofs_gb_common(ea,loofs,hiofs) {
	auto ofs = 0;
	auto addr = Byte(ea + loofs + 1) | (Byte(ea + hiofs + 1) << 8);
	auto base = get_base_gb_common(ea, addr);
	if ((base == -1)/*||((addr>=0x4000)&&(addr<0x8000))*/)
		base = MK_FP(AskSelector(AskLong(0, "Enter Bank Number 9")), 0);
//	base = MK_FP(AskSelector(1), 0);
//	Message("addr = %08x, base = %08x\n",addr,base);
	OpOffEx(ea + loofs, 1, REF_LOW8, base + addr - ofs, base, ofs);
	OpOffEx(ea + hiofs, 1, REF_HIGH8, base + addr - ofs, base, ofs);
}

static make_8bit_ofs_gb_2() {
	make_8bit_ofs_gb_common(ScreenEA(),0,2);
}

static make_8bit_ofs_gb_2_i() {
	make_8bit_ofs_gb_common(ScreenEA(),2,0);
}

static make_8bit_ofs_gb_3() {
	make_8bit_ofs_gb_common(ScreenEA(),0,3);
}

static make_8bit_ofs_gb_3_i() {
	make_8bit_ofs_gb_common(ScreenEA(),3,0);
}

static make_8bit_ofs_gb_4() {
	make_8bit_ofs_gb_common(ScreenEA(),0,4);
}

static make_8bit_ofs_gb_4_i() {
	make_8bit_ofs_gb_common(ScreenEA(),4,0);
}

static make_8bit_ofs_gb_5() {
	make_8bit_ofs_gb_common(ScreenEA(),0,5);
}

static make_8bit_ofs_gb_5_i() {
	make_8bit_ofs_gb_common(ScreenEA(),5,0);
}

static make_8bit_ofs_gb_6() {
	make_8bit_ofs_gb_common(ScreenEA(),0,6);
}

static make_8bit_ofs_gb_auto() {
	auto loofs = 0;
	auto sofs = 2, hiofs = -1;
	auto ofs = 0;
	auto ea = ScreenEA();
	auto base, addr;
	while(sofs < 10) {
		if(GetOpType(ea + sofs,0)==1) {
			if(Byte(ea + sofs)==0xCE)
				hiofs = sofs;
		}
		sofs++;
	}
	if(hiofs != -1) {
		make_8bit_ofs_gb_common(ea,loofs,hiofs);
	}
}

static find_near_tbls() {
	auto b0, b1, base, loaddr, hiaddr, ea, screa = 0;

	// DO SWITCHES JMP ($XX) TYPE
	// LDA $XXXX/+1,X/Y
	// STA $YY
	// LDA $XXXX/+1,X/Y
	// STA $YY+1
	// ..
	// JMP ($YY)
	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "?? ?? ?? 85 ?? ?? ?? ?? 85");
		if(ea != BADADDR) {
			auto first_byte_ofs = FindBinary(ea + 10, SEARCH_DOWN | SEARCH_CASE, "6C ?? 00");
			if(first_byte_ofs != BADADDR) {
				first_byte_ofs = first_byte_ofs - ea;
				if(first_byte_ofs < 20) {
					b0 = Byte(ea + 0);
					b1 = Byte(ea + 5);
					if((b0 == b1) && ((b0 == 0xBD) || (b0 == 0xB9))) {
						auto ptr_ofs0, ptr_ofs1, ptr_first_byte;
						MakeUnknown(ea, 12, DOUNK_SIMPLE);
						AutoMark(ea, AU_CODE);
						Wait();
						base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
						ptr_first_byte = Byte(ea + first_byte_ofs + 1);
						ptr_ofs0 = Byte(ea + 4);
						ptr_ofs1 = Byte(ea + 9);
						if(ptr_ofs0 == ptr_first_byte) {
							loaddr = base + Word(ea + 1);
							hiaddr = base + Word(ea + 6);
						} else if(ptr_ofs1 == ptr_first_byte) {
							loaddr = base + Word(ea + 6);
							hiaddr = base + Word(ea + 1);
						}
						if((hiaddr-loaddr)>1) {
							Message("8-bit near indirect jump found at 0x%08x base = %08x lo %08x hi %08x sz %04x\n", ea, base, loaddr, hiaddr, hiaddr-loaddr);
							make_8bit_near_tbl(loaddr, hiaddr, 0, 1);
						} else {
							Message("16-bit near indirect jump found at 0x%08x base = %08x ea %08x\n", ea, base, loaddr);
							make_16bit_near_tbl(loaddr-3, 0);
						}
					}
				}
			}
		}
	} while (ea != BADADDR);

	// DO SWITCHES RET TYPE
	// LDA $XXXX+1,X/Y
	// PHA
	// LDA $XXXX,X/Y
	// PHA
	// RTS
	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "?? ?? ?? 48 ?? ?? ?? 48 60");
		if(ea != BADADDR) {
			b0 = Byte(ea + 0);
			b1 = Byte(ea + 4);
			if((b0 == b1) && ((b0 == 0xBD) || (b0 == 0xB9))) {
				MakeUnknown(ea, 9, DOUNK_SIMPLE);
				AutoMark(ea, AU_CODE);
				Wait();
				base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
				loaddr = base + Word(ea + 5);
				hiaddr = base + Word(ea + 1);
				if((hiaddr-loaddr)>1) {
					Message("8-bit RET indirect jump found at 0x%08x base = %08x lo %08x hi %08x sz %04x\n", ea, base, loaddr, hiaddr, hiaddr-loaddr);
					make_8bit_near_tbl(loaddr, hiaddr, -1, 1);
				} else {
					Message("16-bit RET indirect jump found at 0x%08x base = %08x ea %08x\n", ea, base, loaddr);
					make_16bit_near_tbl(loaddr-3, -1);
				}
			}
		}
	} while (ea != BADADDR);

	// DO STACK JUMP
	// LDA $HI
	// PHA
	// LDA $LO
	// PHA
	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "A9 ?? 48 A9 ?? 48");
		if(ea != BADADDR) {
			Message("test 0x%08x\n", ea);
			make_8bit_ofs(ea, 3, 0, -1);
		}
	} while (ea != BADADDR);

	// DO OFFSET
	// LDA #$XX
	// STA $YY
	// LDA #$ZZ
	// STA $YY+1
	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "A9 ?? 85 ?? A9 ?? 85 ??");
		if(ea != BADADDR) {
			if((Byte(ea + 7) - Byte(ea + 3)) == 1) {
				MakeUnknown(ea, 8, DOUNK_SIMPLE);
				AutoMark(ea, AU_CODE);
				Wait();
				make_8bit_ofs(ea, 0, 4, 0);
				ea = ea + 8;
			}
		}
	} while (ea != BADADDR);

	// DO OFFSET
	// LDX #$XX
	// LDY #$YY
	// JSR $ZZZZ / STX + STY
	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "A2 ?? A0 ?? 20");
		if(ea != BADADDR) {
			MakeUnknown(ea, 4, DOUNK_SIMPLE);
			AutoMark(ea, AU_CODE);
			Wait();
			make_8bit_ofs(ea, 0, 2, 0);
		}
	} while (ea != BADADDR);

	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "A2 ?? A0 ?? 8E ?? ?? 8C ?? ??");
		if(ea != BADADDR) {
			MakeUnknown(ea, 4, DOUNK_SIMPLE);
			AutoMark(ea, AU_CODE);
			Wait();
			make_8bit_ofs(ea, 0, 2, 0);
		}
	} while (ea != BADADDR);

	ea = screa;
	do {
		ea = FindBinary(ea + 1, SEARCH_DOWN | SEARCH_CASE, "A2 ?? A0 ?? 84 ?? 86");
		if(ea != BADADDR) {
			MakeUnknown(ea, 4, DOUNK_SIMPLE);
			AutoMark(ea, AU_CODE);
			Wait();
			make_8bit_ofs(ea, 0, 2, 0);
		}
	} while (ea != BADADDR);

	// TODO
	// BD C5 A5 LDA off_3E5C5,X
	// 85 00    STA word_0
	// E8       INX
	// BD C5 A5 LDA off_3E5C5,X
	// 85 01    STA word_0+1
	// 6C 00 00 JMP (word_0)


	Message("Done\n");
}

static auto_array() {
	auto ea = ScreenEA();
	auto i = 1;
	ea = FindUnexplored(ea - 1, SEARCH_DOWN);
//	Message("start ea %08x", ea);
	do {
		auto flags = GetFlags(ea + i);
		auto stop = isUnknown(flags) && !isRef(flags) && !hasName(flags);
		i++;
	} while ((flags != 0) && (stop));
	i=i-1;
//	Message(" stop ea %08x, size = %d\n", ea + i - 1, i);
	if(MakeData(ea, FF_BYTE, i, 0)) {
		if(SetArrayFormat(ea, AP_IDXHEX, 0x10, 0))
			Jump(ea);
		else
			Message("can't set array format!\n");

	} else
		Message("can't make data!\n");
}

static ptr_table(ea, docode) {
	auto base, i = 0, w0, stop = 0, defbase = -1;
	do {
		if(((i&1)==0)&&(!stop)){
			MakeUnknown(ea + i, 2, DOUNK_SIMPLE);
			MakeWord(ea + i);
			w0 = Word(ea + i);

			if((w0 != 0) && (w0 != 0xFFFF)) {
				if(SegByName(form("ROM%X",0))!=BADADDR)	// GB mode
					base = get_base_gb_common(ea, w0);
				else
					base = get_base_nes_common(ea, w0);
				if(base == -1) {
					if(defbase == -1) {
						base = MK_FP(AskSelector(AskLong(0, form("Enter Bank Number at 0x%08X",ea))), 0);
						defbase = base;
					} else
						base = defbase;
				}
				OpOffEx(ea + i, 0, REF_OFF16, -1, base, 0);
			}
			if(docode) {
				make_code(base+w0);
				AutoMark(base+w0, AU_CODE);
				Wait();
			}
			Wait();
		}
		i = i + 2;
		stop = isRef(GetFlags(ea + i)) | isRef(GetFlags(ea + i + 1));	// assume the first offset always present, no need to stop here
	} while (!stop && (i < 0x10000));
	return ea + i;
}

static auto_ptr_table() {
	Jump(ptr_table(ScreenEA(),0));
}

static far_ptr(ea, bofs, wofs, op, opofs) {
	auto base, bank_delta=0;
	if(SegByName(form("ROM%X",0))==BADADDR)
		bank_delta=1;
	if (bank_delta==0) {
		auto ofs = Word(ea + wofs);
		if(ofs<0x4000)
			base = MK_FP(AskSelector(0), 0);
		else if((ofs>=0xC000)&&(ofs<0xD000))
			base = MK_FP(AskSelector(SegByName("RAM0")),0);
		else if((ofs>=0xD000)&&(ofs<0xE000))
			base = MK_FP(AskSelector(SegByName("RAMB")),0);
		else if((ofs>=0xFF80)&&(ofs<=0xFFFF))
			base = MK_FP(AskSelector(SegByName("ZRAM")),0);
		else if((ofs>=0xFF00)&&(ofs<=0xFF7F))
			base = MK_FP(AskSelector(SegByName("HWREGS")),0);
		else {
			if(bofs < 0)
				base = MK_FP(AskSelector(/*GetReg(ea,"ds")*/0-bofs), 0);
			else
				base = MK_FP(AskSelector(Byte(ea + bofs)), 0);
		}
	} else
		base = MK_FP(AskSelector(Byte(ea + bofs) + bank_delta), 0);
	OpOffEx(ea + wofs + opofs, op, REF_OFF16, -1, base, 0);
}

static far_ptr_code(ea, bofs, wofs, op, opofs) {
	auto base;
	auto ofs = Word(ea + wofs);
	if(ofs<0x4000)
		base = MK_FP(AskSelector(0), 0);
	else {
		if(bofs<0)
			base = MK_FP(AskSelector(/*GetReg(ea,"ds")*/0-bofs), 0);
		else
			base = MK_FP(AskSelector(Byte(ea + bofs)), 0);
	}
	OpOffEx(ea + wofs + opofs, op, REF_OFF16, -1, base, 0);
	make_code(base + ofs);
	Wait();
}

// duplicate code marker
static duplicate_marker() {

	auto max_treshold = 0x10;

	auto i, j, result, treshold, starti, zero_cnt, one_cnt;
	auto numbank_src, bankea_src, banksize_src, byte_src, res_src_idx;
	auto numbank_dst, bankea_dst, banksize_dst, byte_dst, res_dst_idx;
	auto numbank_delta;

	if(SegByName(form("ROM%X",0)) == BADADDR) {
		numbank_src = 1;
		numbank_delta = 1;
	} else {
		numbank_src = 0;
		numbank_delta = 0;
	}
	while ((bankea_src = SegByBase(numbank_src)) != BADADDR) {
		banksize_src = getSegSize(numbank_src);
		res_src_idx = form("|%1x",numbank_src-numbank_delta);
		Message("bank %02x found: ea = %04x, size = %04x\n  testing:", numbank_src-numbank_delta, bankea_src, banksize_src);
		numbank_dst = numbank_src + 1;
		while ((bankea_dst = SegByBase(numbank_dst)) != BADADDR) {
//			if(numbank_src != numbank_dst)
			{
				banksize_dst = getSegSize(numbank_dst);
				/* compare here */
				if(banksize_src == banksize_dst) {
					Message(" %02x", numbank_dst-numbank_delta);
					res_dst_idx = form("|%1x",numbank_dst-numbank_delta);
					treshold = 0;
					zero_cnt = 0;
					one_cnt = 0;
					for(i = 0; i < banksize_src; i++) {
						byte_src = Byte(bankea_src + i);
						byte_dst = Byte(bankea_dst + i);
						if(byte_src == byte_dst) {
							if(treshold == 0) {
								starti = i;
							} else if(treshold >= max_treshold) {
								if((zero_cnt + one_cnt) != treshold) {
									if(treshold == max_treshold) {
										Message("\n  match found at 0x%08x\n testing:",starti + bankea_src);
										for(j=0;j<max_treshold;j++) {
											result = CommentEx(bankea_src + starti + j, 0) + res_dst_idx;
											MakeComm(bankea_src + starti + j, "");
											MakeComm(bankea_src + starti + j, result);
											result = CommentEx(bankea_dst + starti + j, 0) + res_src_idx;
											MakeComm(bankea_dst + starti + j, "");
											MakeComm(bankea_dst + starti + j, result);
										}
									}
									result = CommentEx(bankea_src + i, 0) + res_dst_idx;
									MakeComm(bankea_src + i, "");
									MakeComm(bankea_src + i, result);
									result = CommentEx(bankea_dst + i, 0) + res_src_idx;
									MakeComm(bankea_dst + i, "");
									MakeComm(bankea_dst + i, result);
								}
							}
							treshold++;
							if(byte_src == 0)
								zero_cnt++;
							else if(byte_src == 0xff)
								one_cnt++;
						} else {
							treshold = 0;
							zero_cnt = 0;
							one_cnt = 0;
						}
					}
				}
				/* compare here */
			}
			numbank_dst++;
		}
		Message("\n");
		numbank_src++;
	}
}


// autorename ptrs
static auto_rename_ptrs() {
	auto sea = SelStart();
	auto eea = SelEnd();
	auto bank = GetReg(sea,"ds");
	auto extbank = -1, extbase = -1;
	auto base = MK_FP(AskSelector(bank), 0);
//	auto segorg = getSegOrg(bank);
	auto segsize = getSegSize(bank);
	auto name_mask = AskStr("", "Enter Name Mask");
	auto index_start = AskLong(0, "Enter Start Index 11");
	auto index_increment = AskLong(1, "Enter Index Increment 12");
	auto i = index_start;
	while(sea < eea) {
		auto ofs = Word(sea);
		auto nname = form(name_mask,i);
		if(SegByName(form("ROM%X",0))!=BADADDR) {	// GB mode
			if(bank>0){
				if(ofs<0x4000) {
					MakeNameEx(0+ofs,nname,SN_CHECK|SN_NOWARN);
				} else if(ofs<0x8000) {
					MakeNameEx(base+ofs,nname,SN_CHECK|SN_NOWARN);
				}
			} else {
				if(ofs<0x4000) {
					MakeNameEx(0+ofs,nname,SN_CHECK|SN_NOWARN);
				} else if(ofs<0x8000){
					if(extbank==-1) {
						extbank = AskLong(1, "Enter External Bank 13");
						extbase = MK_FP(AskSelector(extbank), 0);
					}
					MakeNameEx(extbase+ofs,nname,SN_CHECK|SN_NOWARN);
				}
			}
		} else {
			if(segsize == 0x2000) {				// NES mode (16x8k)
				if(bank<16){
					if(ofs<0xC000) {
						MakeNameEx(base+ofs,nname,SN_CHECK|SN_NOWARN);
					} else if(ofs<0xE000) {
						MakeNameEx(MK_FP(AskSelector(15), 0)+ofs,nname,SN_CHECK|SN_NOWARN);
					} else {
						MakeNameEx(MK_FP(AskSelector(16), 0)+ofs,nname,SN_CHECK|SN_NOWARN);
					}
				} else {
					if(ofs<0xC000) {
						if(extbank==-1) {
							extbank = AskLong(1, "Enter External Bank 14");
							extbase = MK_FP(AskSelector(extbank+1), 0);
						}
						MakeNameEx(extbase+ofs,nname,SN_CHECK|SN_NOWARN);
					} if(ofs<0xE000) {
						MakeNameEx(MK_FP(AskSelector(15), 0)+ofs,nname,SN_CHECK|SN_NOWARN);
					} else {
						MakeNameEx(MK_FP(AskSelector(16), 0)+ofs,nname,SN_CHECK|SN_NOWARN);
					}
				}
			} else if(segsize == 0x4000) {		// NES mode (8x16k banks)
				if(bank<8){
					if(ofs<0xC000) {
						MakeNameEx(base+ofs,nname,SN_CHECK|SN_NOWARN);
					} else {
						MakeNameEx(MK_FP(AskSelector(8),0)+ofs,nname,SN_CHECK|SN_NOWARN);
					}
				} else {
					if(ofs<0xC000) {
						if(extbank==-1) {
							extbank = AskLong(1, "Enter External Bank 15");
							extbase = MK_FP(AskSelector(extbank+1), 0);
						}
						MakeNameEx(extbase+ofs,nname,SN_CHECK|SN_NOWARN);
					} else {
						MakeNameEx(MK_FP(AskSelector(8),0)+ofs,nname,SN_CHECK|SN_NOWARN);
					}
				}
			} else if(segsize == 0x8000) {				// NES mode (32k banks)
				MakeNameEx(base+ofs,nname,SN_CHECK|SN_NOWARN);
			}
		}
		sea=sea+2;
		i = i + index_increment;
		Wait();
	}
}

// garbage labels collector
static garbage_search(ea) {
	auto /*ea = 0, */count = 0;
	auto flags = GetFlags(ea);
	if( flags & (FF_LABL/*|FF_NAME*/)) {
		if((RfirstB0(ea)==-1)&&(DfirstB(ea)==-1)) {
			Message(">no ref label '%s' at 0x%08x deleted\n", Name(ea), ea);
			MakeName(ea, "");
			count = 1;
		}
	}
	return count;
}

static garbage_collector(void) {
	auto ea = 0;
	Message("garbage collector start\n");
	garbage_search(ea);
	while ((ea = NextAddr(ea)) != BADADDR) {
		garbage_search(ea);
	}
	Message("garbage collector done\n");
}
