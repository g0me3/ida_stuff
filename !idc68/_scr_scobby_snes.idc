#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// Scooby Doo SCRIPTS
// ---------------------------------

//#define DEBUG

#define ARG_NUM 1
#define ARG_O94 2
#define ARG_O82 3
#define ARG_FAR 4
#define ARG_ITM 5
#define ARG_OBJ 6

static scooby_get_item_name(val) {
	auto ret = "";
	if(val == 0x00) ret = "ITEMA00_barrel"; else
	if(val == 0x01) ret = "ITEMA01_vampires_tuxedo"; else
	if(val == 0x02) ret = "ITEMA02_blank_paper"; else
	if(val == 0x03) ret = "ITEMA03_printing_dye"; else
	if(val == 0x04) ret = "ITEMB03_rope"; else
	if(val == 0x05) ret = "ITEMA05_bookA"; else
	if(val == 0x06) ret = "ITEMA06_bookB"; else
	if(val == 0x07) ret = "ITEMA07_bookB"; else
	if(val == 0x08) ret = "ITEMA08_bookB"; else
	if(val == 0x09) ret = "ITEMA09_snack"; else
	if(val == 0x0A) ret = "ITEMB0A_"; else
	if(val == 0x0B) ret = "ITEMA0B_face_powder"; else
	if(val == 0x0C) ret = "ITEMA0C_rubber_bat"; else
	if(val == 0x0D) ret = "ITEMA0D_false_teeth"; else
	if(val == 0x0E) ret = "ITEMA0E_printing_plate"; else
	if(val == 0x0F) ret = "ITEMB0F_"; else
	if(val == 0x10) ret = "ITEMA10_lamp"; else
	if(val == 0x11) ret = "OBJ11_dark_room"; else
	if(val == 0x12) ret = "ITEMB12_"; else
	if(val == 0x13) ret = "ITEMA13_melon"; else
	if(val == 0x14) ret = "ITEMB14_"; else
	if(val == 0x15) ret = "ITEMA15_old_key"; else
	if(val == 0x16) ret = "ITEMA16_old_key"; else
	if(val == 0x17) ret = "ITEMB17_"; else
	if(val == 0x18) ret = "ITEMA18_boiler_suit"; else
	if(val == 0x19) ret = "ITEMB19_"; else
	if(val == 0x1A) ret = "ITEMA1A_sample_kit"; else
	if(val == 0x1B) ret = "ITEMA1B_tar_pot"; else
	if(val == 0x1C) ret = "ITEMA1C_empty_bucket"; else
	if(val == 0x1D) ret = "ITEMB0F_piece_of_paper"; else
	if(val == 0x1E) ret = "ITEMA1E_geo_map"; else
	if(val == 0x1F) ret = "ITEMA1F_sinister_mask"; else
	if(val == 0x20) ret = "ITEMA20_tar_covered_boots"; else
	if(val == 0x21) ret = "ITEMA21_clown_shoes"; else
	if(val == 0x22) ret = "ITEMA22_clown_hair"; else
	if(val == 0x23) ret = "ITEMB23_piece_of_paper"; else
	if(val == 0x24) ret = "ITEMA24_local_newspaper"; else
	if(val == 0x25) ret = "ITEMA25_safety_equipement"; else
	if(val == 0x26) ret = "ITEMA26_clown_nose"; else
	if(val == 0x27) ret = "ITEMA27_janitor_letter"; else
	if(val == 0x28) ret = "ITEMB28_clown_costume"; else
	if(val == 0x29) ret = "ITEMA29_car_keys"; else
	if(val == 0x2A) ret = "ITEMA2A_strength_manual"; else
	if(val == 0x2B) ret = "ITEMA2B_doll_pass"; else
	if(val == 0x2C) ret = "ITEMA2C_attraction_keys"; else
	if(val == 0x2D) ret = "ITEMA2D_coconut"; else
	if(val == 0x2E) ret = "ITEMA2E_mallet"; else
	if(val == 0x2F) ret = "ITEMA2F_attraction_bell"; else
	if(val == 0x30) ret = "ITEMA30_some_key"; else
	if(val == 0x31) ret = "ITEMA31_5_cents"; else
	if(val == 0x32) ret = "ITEMA32_fan"; else
	if(val == 0x33) ret = "ITEMA33_generator"; else
	if(val == 0x34) ret = "ITEMA34_half_empty_gas"; else
	if(val == 0x35) ret = "ITEMA35_glue"; else
	if(val == 0x36) ret = "ITEMA36_matches"; else
	if(val == 0x37) ret = "ITEMA37_cannon_ball"; else
	if(val == 0x38) ret = "ITEMB38_barrel_powder"; else
	if(val == 0x39) ret = "ITEMB39_red_key"; else
	if(val == 0x3A) ret = "ITEMB3A_blue_key"; else
	if(val == 0x3B) ret = "ITEMB3B_gray_key"; else
	if(val == 0x3C) ret = "ITEMA3C_door_key"; else
	if(val == 0x3D) ret = "ITEMB3D_red_key"; else
	if(val == 0x3E) ret = "ITEMA3E_door_key"; else
	if(val == 0x3F) ret = "ITEMA3F_soap"; else
	if(val == 0x40) ret = "ITEMA40_area_map"; else
	if(val == 0x41) ret = "ITEMA41_diving_gear"; else
	if(val == 0x42) ret = "ITEMA42_treasure_chest"; else
	if(val == 0x43) ret = "ITEMA43_gold"; else
	if(val == 0x44) ret = "ITEMA44_eye_patch"; else
	if(val == 0x45) ret = "ITEMA45_scrap_of_paper"; else
	if(val == 0x46) ret = "ITEMB46_projection_gear"; else
	if(val == 0x47) ret = "ITEMA47_crate"; else
	if(val == 0x48) ret = "ITEMB48_unknown_bottle"; else
	if(val == 0x49) ret = "ITEMA49_power_cable"; else
	if(val == 0x4A) ret = "ITEMB4A_gray_rope"; else
	if(val == 0x4B) ret = "ITEMB4B_rug"; else
	if(val == 0x4C) ret = "ITEMA4C_sturdy_planks"; else
	if(val == 0x4D) ret = "ITEMA4D_wooden_peg"; else
	if(val == 0x4E) ret = "ITEMB4E_"; else
	if(val == 0x4F) ret = "ITEMA4F_old_fish"; else
	if(val == 0x50) ret = "ITEMA50_fun_fair_key"; else
	if(val == 0x51) ret = "ITEMB51_doll"; else
	if(val == 0x52) ret = "ITEMA52_tires"; else
	if(val == 0x53) ret = "ITEMA53_grubby_old_stick"; else
	if(val == 0x54) ret = "ITEMA54_geological_report"; else
	if(val == 0x55) ret = "ITEMA55_old_cheese"; else
	if(val == 0x56) ret = "ITEMA56_just_a_plank"; else
	if(val == 0x57) ret = "ITEMA57_trolley"; else
	if(val == 0x58) ret = "ITEMA58_clown_mask"; else
	if(val == 0x59) ret = "ITEMA59_welding_torch"; else
	if(val == 0x5A) ret = "ITEMA5A_tin_can"; else
	if(val == 0x5B) ret = "ITEMA5B_gun_powder_for_trap"; else
	if(val == 0x5C) ret = "ITEMA5C_teddy"; else
	if(val == 0x5D) ret = "ITEMA5D_gun_powder"; else
// special non item objects
	if(val == 0x6C) ret = "OBJ_6C_base_trap_barrel"; else
	                ret = form("ITEM%02X_UNKNOWN",val);
	return ret;
}

static scooby_get_obj_name(val) {
	auto ret = "";
	if(val == 0x00) ret = "OBJ00_Velma"; else
	if(val == 0x02) ret = "OBJ02_Daphne"; else
	if(val == 0x04) ret = "OBJ04_Freddy"; else
	if(val == 0x06) ret = "OBJ06_Shaggy"; else
	if(val == 0x08) ret = "OBJ06_Scooby"; else
	           ret = form("OBJ%02X",val);
	return ret;
}

static scooby_get_opc_name(opc) {
	auto ret = "";
	if(opc == 0x04) ret = "TALK_SUB_SET      "; else
	if(opc == 0x06) ret = "JMP               "; else
	if(opc == 0x0D) ret = "MSGA              "; else
	if(opc == 0x0E) ret = "MSG_CLR           "; else
	if(opc == 0x0F) ret = "RANGE_TEST        "; else
	if(opc == 0x13) ret = "MSGB              "; else
	if(opc == 0x1A) ret = "OBJ_SUB_SET       "; else
	if(opc == 0x1B) ret = "ITEM_CURRENT_BEQ  "; else
	if(opc == 0x1C) ret = "ITEM_REMOVE       "; else
	if(opc == 0x29) ret = "LOOP_PTR_SET      "; else
	if(opc == 0x2A) ret = "LOOP_JMP          "; else
	if(opc == 0x2B) ret = "ITEM_FLAG_SET     "; else
	if(opc == 0x2C) ret = "ITEM_FLAG_BEQ     "; else
	if(opc == 0x2D) ret = "ITEM_INSERT       "; else
	if(opc == 0x2F) ret = "STOP              "; else
	if(opc == 0x31) ret = "DOOR_OBJ_INSERT   "; else
	if(opc == 0x33) ret = "ITEM_OBJ_INSERT   "; else
	if(opc == 0x34) ret = "ITEM_OBJ_MOVE     "; else
	if(opc == 0x35) ret = "ITEM_WAIT         "; else
//	if(opc == 0x36) ret = "ITEM_             "; else
	if(opc == 0x39) ret = "ITEM_LOOKUP_BNE   "; else
	if(opc == 0x3D) ret = "SCORES_ADD        "; else
	if(opc == 0x3E) ret = "DAMAGE_ADD        "; else
	if(opc == 0x40) ret = "TALK_AS_LOOP_PTR  "; else
	if(opc == 0x41) ret = "LOOP_AS_TALK_SUB  "; else
	if(opc == 0x42) ret = "JSR               "; else
	if(opc == 0x43) ret = "RET               "; else
	if(opc == 0x44) ret = "OBJ_ROOM_SET      "; else
	if(opc == 0x46) ret = "OBJ_ROOM_BNE      "; else
	if(opc == 0x48) ret = "RAND_TEST_BCC     "; else
	if(opc == 0x49) ret = "ACC_SET           "; else
	if(opc == 0x4A) ret = "ACC_TEST_BCC      "; else
	if(opc == 0x4B) ret = "ACC_ADD           "; else
	if(opc == 0x4C) ret = "DOOR_LOCK_SUB_SET "; else
	if(opc == 0x4E) ret = "ITEM_DISABKE      "; else
	if(opc == 0x4F) ret = "ITEM_ENABLE       "; else
	if(opc == 0x51) ret = "COLLISION_SUB_SET "; else
	if(opc == 0x54) ret = "ITEM_OBJ_KILL     "; else
	if(opc == 0x55) ret = "NJMP              "; else
	if(opc == 0x58) ret = "DAMAGE_ADD_SE     "; else
               ret = form("CMD%02X             ", opc);
	return ret;
}

static scooby_fetch_arg(ea, idx, type) {
	auto ret = "", tmp0, tmp1, tmp2;
	auto argea = ea + 2 + (idx * 2);
	if(type == ARG_NUM) {
		tmp0 = Word(argea);
		ret = form("$%04X",tmp0);
	} else if(type == ARG_O94) {
		tmp0 = Word(argea);
		if(tmp0 == 0) {
			ret = "0";
		} else if(tmp0 == 0xFFFF) {
			ret = "-1";
		} else {
			tmp0 = tmp0 + 0x948000;
			add_dref(ea, tmp0, dr_O|XREF_USER);
			Wait();
			ret = Name(tmp0);
		}
	} else if(type == ARG_O82) {
		tmp0 = Word(argea) + 0x828010;
		add_dref(ea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	} else if(type == ARG_FAR) {
		tmp0 = Word(argea) + (Byte(argea + 2) << 16);
		add_dref(ea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	} else if(type == ARG_ITM) {
		tmp0 = Word(argea);
		ret = scooby_get_item_name(tmp0 & 0xFF);
	} else if(type == ARG_OBJ) {
		tmp0 = Word(argea);
		ret = scooby_get_obj_name(tmp0 & 0xFF);
	}
	return ret;
}

static scooby_make_opcode(ea, len, opc, arg0, arg1, arg2, arg3) {
//	MakeUnknown(ea, (len * 2) + 2, DOUNK_SIMPLE);
//	make_data_array(ea, (len * 2) + 2, "");
	if(arg0 != -1) opc = opc + scooby_fetch_arg(ea, 0, arg0);
	if(arg1 != -1) opc = opc + ", " + scooby_fetch_arg(ea, 1, arg1);
	if(arg2 != -1) opc = opc + ", " + scooby_fetch_arg(ea, 2, arg2);
	if(arg3 != -1) opc = opc + ", " + scooby_fetch_arg(ea, 3, arg3);
	SetManualInsn(ea, opc);
	return ea + (len * 2) + 2;
}

static scooby_decompile_opcode(ea, ret) {
	auto tmp0, tmp1, stop = 0;
	auto cmd = Byte(ea);
	auto len = Byte(ea + 1);
	if(len != 0xFF) {
		auto opcname = scooby_get_opc_name(cmd);
		if((cmd == 0x06)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_O94, -1, -1, -1);
		} else if((cmd == 0x04)||(cmd == 0x29)||(cmd == 0x42)||(cmd == 0x51)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_O94, -1, -1, -1);
		} else if((cmd == 0x0D)||(cmd == 0x55)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_FAR, -1, -1, -1);
		} else if((cmd == 0x11)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_NUM, ARG_NUM, ARG_OBJ, -1);
		} else if((cmd == 0x13)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_FAR, -1, ARG_OBJ, -1);
		} else if((cmd == 0x0F)||(cmd == 0x52)||(cmd == 0x53)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_OBJ, ARG_NUM, -1, -1);
		} else if((cmd == 0x10)||(cmd == 0x4C)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_NUM, ARG_NUM, ARG_O94, -1);
		} else if((cmd == 0x46)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_OBJ, ARG_NUM, ARG_O94, -1);
		} else if((cmd == 0x4A)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_NUM, ARG_O94, -1, -1);
		} else if((cmd == 0x1A)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_OBJ, ARG_O94, -1, -1);
		} else if((cmd == 0x1B)||(cmd == 0x2C)||(cmd == 0x39)||(cmd == 0x4E)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_ITM, ARG_O94, -1, -1);
		} else if((cmd == 0x48)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_O94, ARG_NUM, -1, -1);
		} else if((cmd == 0x0E)||(cmd == 0x2A)||(cmd == 0x2F)||(cmd == 0x40)||(cmd == 0x41)||(cmd == 0x43)) {
			ea = scooby_make_opcode(ea, len, opcname, -1, -1, -1, -1);
		} else if((cmd == 0x33)) {
			tmp0 = Word(ea + 2) + 0x828010;
			tmp1 = Word(tmp0 + 6);
			MakeNameEx(tmp0, form("_obj_res_%s",scooby_get_item_name(tmp1)), SN_NOCHECK|SN_NOWARN);
			ea = scooby_make_opcode(ea, len, opcname, ARG_O82, ARG_NUM, ARG_NUM, ARG_NUM);
		} else if((cmd == 0x34)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_ITM, ARG_NUM, ARG_NUM, ARG_NUM);
		} else if((cmd == 0x2B)||(cmd == 0x1C)||(cmd == 0x2D)||(cmd == 0x35)||(cmd == 0x36)||(cmd == 0x4F)||(cmd == 0x54)) {
			ea = scooby_make_opcode(ea, len, opcname, ARG_ITM, -1, -1, -1);
		} else {
			if(len == 1) ea = scooby_make_opcode(ea, 1, opcname, ARG_NUM, -1, -1, -1); else
			if(len == 2) ea = scooby_make_opcode(ea, 2, opcname, ARG_NUM, ARG_NUM, -1, -1); else
			if(len == 3) ea = scooby_make_opcode(ea, 3, opcname, ARG_NUM, ARG_NUM, ARG_NUM, -1); else
			if(len == 4) ea = scooby_make_opcode(ea, 4, opcname, ARG_NUM, ARG_NUM, ARG_NUM, ARG_NUM); else
			{
				Message("unimplemented arguments count at 0x%08X!\n", ea);
				ea = -1;
			}
		}
	}
	return ea;
}

static scooby_script_selection(void) {
	Jump(scooby_decompile_opcode(ScreenEA(), 0));
}

static scooby_script_auto(void) {
	auto ea;
	ea = 0x948000;
	while((ea < 0x94FC96) && (ea != -1)) {
		ea = scooby_decompile_opcode(ea, 0);
	}
	ea = 0x94FCA9;
	while((ea < 0x94FDAF && (ea != -1))) {
		ea = scooby_decompile_opcode(ea, 0);
	}
}

static make_string(ea) {
	auto tmp0, tmp1, ret = "";
	while(Byte(ea) != 0xFF) {
		tmp0 = ea;
		ret = ret + "_";
		while(Byte(tmp0) != 0x00) {
			while((tmp1 = Byte(tmp0)) != 0x00) {
				if((tmp1 >=0x41) && (tmp1 < (0x41+26)))
					ret = ret + form("%c",tmp1 + 0x20);
				else if(tmp1 == 0x20)
					ret = ret + "_";
				tmp0 = tmp0 + 1;
			}
			MakeStr(ea, tmp0 + 1);
			MakeName(ea, "");
		}
		ea = tmp0 + 1;
	}
	MakeByte(ea);
	Jump(ea + 1);
	return ret;
}

static scooby_msg_format() {
	auto ea = ScreenEA();
	auto tmp0 = ea, tmp1;
	MakeUnknown(ea, 6, DOUNK_SIMPLE);
	MakeWord(ea);
	MakeData(ea, FF_WORD, 6, 0);
	SetArrayFormat(ea, AP_IDXHEX, 8, 0);
	tmp0 = make_string(ea + 6);
	tmp1 = GetFlags(ea);
	if(isRef(tmp1))
		tmp1 = "";
	else
		tmp1 = "_unref";
	MakeNameEx(ea, form("%s_msg_%s",tmp1,tmp0), SN_NOCHECK|SN_NOWARN);
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "scooby_script_selection");
	DelHotkey("Shift-P");
	AddHotkey("Shift-P", "scooby_msg_format");

	scooby_script_auto();

/*
//                       RAM O  	     RAM B          ROM O          ROM B
	auto pat = "C2 30 A9 ?? ?? 85 32 A9 ?? 00 85 34 A9 ?? ?? 85 16 A2 ?? 00 22 9C FA 82 22 DD F9 82 C2 20 C2 10";
	auto instr = "RES_UNP %s, %s";
//              00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
	auto ea = -1, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x03) | (Byte(ea + 0x08) << 16);
		tmp2 = Word(ea + 0x0D) | (Byte(ea + 0x12) << 16);
//		MakeNameEx(tmp2, form("_res_%08X", tmp2), SN_CHECK|SN_NOWARN);
//		Wait();
		add_dref(ea, tmp0, dr_O|XREF_USER);
		add_dref(ea, tmp2, dr_O|XREF_USER);
		Wait();
		SetManualInsn(ea, form(instr, Name(tmp0), Name(tmp2)));
//		make_data_array(ea + 2, ((strlen(pat) + 1) / 3) - 2, "");
		SetManualInsn(ea + 2, "ENDM");
	}

	pat = "A9 ?? ?? 8D 16 21 A2 ?? ?? BF ?? ?? ?? 18 69 ?? ?? 8D 18 21 E8 E8 E0 ?? ?? D0 EE";
	instr = "VDP_CPY %s%s, $%04X, +$%04X, $%04X";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17 18 19 1A
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x01);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp2 = Word(ea + 0x0F);
		tmp3 = Word(ea + 0x17);
		tmp4 = Word(ea + 0x07);
		if(tmp4 == 0)
			tmp4 = "";
		else
			tmp4 = form("+$%04X",tmp4);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp4, tmp0, tmp2, tmp3));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}

	pat = "A9 ?? ?? 8D 16 21 A2 ?? ?? BF ?? ?? ?? 09 ?? ?? 8D 18 21 E8 E8 E0 ?? ?? D0 EF";
	instr = "VDP_CPY %s%s, $%04X, |$%04X, $%04X";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17 18 19 1A
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x01);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp2 = Word(ea + 0x0E);
		tmp3 = Word(ea + 0x16);
		tmp4 = Word(ea + 0x07);
		if(tmp4 == 0)
			tmp4 = "";
		else
			tmp4 = form("+$%04X",tmp4);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp4, tmp0, tmp2, tmp3));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}

	pat = "A9 ?? ?? 8D 16 21 A2 ?? ?? BF ?? ?? ?? 18 69 ?? ?? 09 ?? ?? 8D 18 21 E8 E8 E0 ?? ?? D0 EB";
	instr = "VDP_CPY %s%s, $%04X, +$%04X|$%04X, $%04X";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16 17 18 19 1A
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x01);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp2 = Word(ea + 0x0F);
		tmp3 = Word(ea + 0x1A);
		tmp5 = Word(ea + 0x12);
		tmp4 = Word(ea + 0x07);
		if(tmp4 == 0)
			tmp4 = "";
		else
			tmp4 = form("+$%04X",tmp4);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp4, tmp0, tmp2, tmp5, tmp3));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}

	pat = "A9 ?? ?? 8D 16 21 A2 ?? ?? BF ?? ?? ?? 8D 18 21 E8 E8 E0 ?? ?? D0 F2";
	instr = "VDP_CPY %s%s, $%04X, +0, $%04X";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x01);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp3 = Word(ea + 0x13);
		tmp4 = Word(ea + 0x07);
		if(tmp4 == 0)
			tmp4 = "";
		else
			tmp4 = form("+$%04X",tmp4);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp4, tmp0, tmp3));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}

	pat = "A2 00 00 A9 ?? ?? 8D 16 21 BF ?? ?? ?? 8D 18 21 E8 E8 E0 ?? ?? D0 F2";
	instr = "VDP_CPY %s, $%04X, +0, $%04X";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x04);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp3 = Word(ea + 0x13);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp0, tmp3));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}

	pat = "A9 ?? ?? 8D 16 21 A2 00 00 BF ?? ?? ?? 8D 18 21 E8 E8 E4 36 D0 F3";
	instr = "VDP_CPY %s, $%04X, +0, %s";
//         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13 14 15 16
	ea = -1;
	while((ea = FindBinary(ea + 1, SEARCH_DOWN, pat))!=BADADDR) {
		Message("found pattern at 0x%08x\n", ea);
		tmp0 = Word(ea + 0x01);
		tmp1 = Word(ea + 0x0A) | (Byte(ea + 0x0C) << 16);
		tmp3 = Word(ea + 0x13);
		SetManualInsn(ea, form(instr, Name(tmp1), tmp0, "word_7E0036"));
		Wait();
//		make_data_array(ea + 3, ((strlen(pat) + 1) / 3) - 3, "");
		SetManualInsn(ea + 3, "ENDM");
		Wait();
		add_dref(ea, tmp1, dr_O|XREF_USER);
		Wait();
	}
//*/
}
