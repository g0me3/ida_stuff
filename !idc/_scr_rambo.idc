#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// RAMBO GAME SCRIPTS
// ---------------------------------

//#define ROMAJI

#define ARG_NUM08 1
#define ARG_NUM16 2
#define ARG_OFS   3
#define ARG_FLAG  4
#define ARG_ROOM  5

static rambo_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0x00)			ret = "sprite_draw_up    %s";
	else if(cmd == 0x01)	ret = "sprite_draw_down  %s";
	else if(cmd == 0x02)	ret = "msg_draw_up       // %s";
	else if(cmd == 0x03)	ret = "msg_draw_down     // %s";
	else if(cmd == 0x04)	ret = "frame_draw_up     %s";
	else if(cmd == 0x05)	ret = "frame_draw_down   %s";
	else if(cmd == 0x06)	ret = "frame_draw_custom $%02x%02x, $%02x, $%02x";
	else if(cmd == 0x07)	ret = "msg_input_handler ";
	else if(cmd == 0x08)	ret = "input_2_options   ";
//	else if(cmd == 0x09)	ret = "input_3_options   ";	// UNUSED
//	else if(cmd == 0x0A)	ret = "input_4_options   ";	// UNUSED
	else if(cmd == 0x0B)	ret = "ptr_load          %s";
	else if(cmd == 0x0C)	ret = "msg_printf        $%04x // %s";
	else if(cmd == 0x0D)	ret = "game_flags_set    %s";
	else if(cmd == 0x0E)	ret = "game_flags_clear  %s";
	else if(cmd == 0x0F)	ret = "jmp_flags_not_set %s, %s";
	else if(cmd == 0x10)	ret = "jmpne_option      $%02x, %s";
	else if(cmd == 0x11)	ret = "jmp_branch        %s";	// 2b opcode
	else if(cmd == 0x12)	ret = "------------------";	// 2b opcode
	else if(cmd == 0x13)	ret = "jump              %s";
	else if(cmd == 0x14)	ret = "stop              ";
	else if(cmd == 0x15)	ret = "set_room_idx      $%02x"; // TODO: room names
	else if(cmd == 0x16)	ret = "anim_scene_set    $%02x";
	else if(cmd == 0x17)	ret = "player_pos_set    $%02x, $%02x";
//	else if(cmd == 0x18)	ret = "mem_write         %s, $%02x"; // UNUSED
	else if(cmd == 0x19)	ret = "pass_input        ";
	else if(cmd == 0x1A)	ret = "game_stats_draw   ";
	else if(cmd == 0x1B)	ret = "life_restore      ";
	else if(cmd == 0x1C)	ret = "add_10_knifes     ";
	else if(cmd == 0x21)	ret = "add_5_potions     ";
//	else if(cmd == 0x22)	ret = "inc_exp_level     ";	// UNUSED
	else if(cmd == 0x23)	ret = "game_hours_set    $%02x";
	else if(cmd == 0x24)	ret = "checkpoint_restore";
	else if(cmd == 0x25)	ret = "checkpoint_reset  ";
	else if(cmd == 0x26)	ret = "checkpoint_set    ";
	else if(cmd == 0x27)	ret = "continue_cur_draw ";
	else if(cmd == 0x28)	ret = "ending_anim       ";
	else if(cmd == 0x29)	ret = "scroller          ";

	else ret = form("cmd%02x",cmd);
	return ret;
}

static get_ofs_name(ea,loc_name,loc_idx) {
	auto ret = "", tmp0;
	auto bank = GetReg(ea,"ds") - 1;
	tmp0 = Word(ea) + MK_FP(AskSelector(bank + 1), 0);
	add_dref(ea, tmp0, dr_O|XREF_USER);
	Wait();
	ret = Name(tmp0);
	if(loc_name != "") {
		if(substr(ret,0,4) == "_msg") {
			auto new_name = form("%s_msg%02x",loc_name,loc_idx);
			MakeName(tmp0, new_name);
			ret = new_name;
			Wait();
		}
	}
	Wait();
	return ret;
}

static get_next_branch(ea) {
	auto ret = "", tmp0, tmp1 = ea, stop = 0;
	while(!stop) {
		tmp0 = Word(ea);
		if((tmp0==0x1111)||(tmp0==0x1212)){
			ea = ea + 1;
			stop = 1;
		}
		ea = ea + 1;
	}
	add_dref(tmp1, ea, dr_O|XREF_USER);
	Wait();
	ret = Name(ea);
	Wait();
	return ret;
}

static make_opcode(ea, len, opc) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	make_data_array(ea, len, "");
	SetManualInsn(ea, opc);
	return ea + len;
}

static get_flag_name(val) {
	auto ret = "";
	if(val == 0x00) ret = "_FLAG00_SYS"; else
	if(val == 0x01) ret = "_FLAG01_SYS"; else
	if(val == 0x02) ret = "_FLAG02_KID_SAVED"; else
	if(val == 0x03) ret = "_FLAG03_LAMP_ITEM"; else
	if(val == 0x04) ret = "_FLAG04_KID_TAKEN"; else
	if(val == 0x05) ret = "_FLAG05_PHOTO_ITEM"; else
	if(val == 0x06) ret = "_FLAG06_POW_TAKEN"; else
	if(val == 0x07) ret = "_FLAG07_DRESS_ITEM"; else
	if(val == 0x08) ret = "_FLAG08_SYS"; else
	if(val == 0x09) ret = "_FLAG09_CO_TAKEN"; else
	if(val == 0x0A) ret = "_FLAG0A_MISSION_TIME_OVER"; else
//	if(val == 0x0B) ret = "_FLAG0B_SYS"; else
	if(val == 0x0C) ret = "_FLAG0C_SYS"; else
	if(val == 0x0D) ret = "_FLAG0D_SYS"; else
	if(val == 0x0E) ret = "_FLAG0E_BOAT"; else
//	if(val == 0x0F) ret = "_FLAG0F_SYS"; else
	if(val == 0x10) ret = "_FLAG10_HELI_KEY"; else
	if(val == 0x11) ret = "_FLAG11_PEDANT"; else
	if(val == 0x12) ret = "_FLAG12_BANDANA"; else
	if(val == 0x13) ret = "_FLAG13_SYS"; else
	if(val == 0x14) ret = "_FLAG14_FLY_FORTRESS_DEAD"; else
	           ret = form("OBJ%02X",val);
	return ret;
}

static get_spr_name(val) {
	auto ret = "";
	if(val == 0x00) ret = "_PORTRAIT00_RAMBO"; else
	if(val == 0x09) ret = "_PORTRAIT01_RAMBO_ANGRY"; else
	if(val == 0x12) ret = "_PORTRAIT02_RAMBO_HAPPY"; else
	if(val == 0x1B) ret = "_PORTRAIT03_CO"; else
	if(val == 0x24) ret = "_PORTRAIT04_CO_HAPPY"; else
	if(val == 0x2D) ret = "_PORTRAIT05_CO_SAD"; else
	if(val == 0x36) ret = "_PORTRAIT06_CO_DEAD"; else
	if(val == 0x3F) ret = "_PORTRAIT07_BANKS_POW"; else
	if(val == 0x48) ret = "_PORTRAIT08_TRAUMAN1"; else
	if(val == 0x51) ret = "_PORTRAIT09_MURDOCK"; else
	if(val == 0x5A) ret = "_PORTRAIT0A_MURDOCK_ANGRY"; else
	if(val == 0x63) ret = "_PORTRAIT0B_MURDOCK_SAD"; else
	if(val == 0x6C) ret = "_PORTRAIT0C_TRAUMAN2"; else
	if(val == 0x75) ret = "_PORTRAIT0D_ERICSON"; else
	if(val == 0x7E) ret = "_PORTRAIT0E_PADOVSKY"; else
	if(val == 0x87) ret = "_PORTRAIT0F_YUSIN"; else
	if(val == 0x90) ret = "_PORTRAIT10_SOLDIER1"; else
	if(val == 0x99) ret = "_PORTRAIT11_SOLDIER2"; else
	if(val == 0xA2) ret = "_PORTRAIT12_VILLAGER1"; else
	if(val == 0xAB) ret = "_PORTRAIT13_VILLAGER2"; else
	if(val == 0xB4) ret = "_PORTRAIT14_PIRATE"; else
	if(val == 0xBD) ret = "_PORTRAIT15_KID"; else

	if(val == 0xC6) ret = "_SPR_PACK_IN_TIME"; else
	if(val == 0xC8) ret = "_SPR_TITLE_SCREEN"; else
	if(val == 0xD8) ret = "_PORTRAIT_CLEAR"; else
	   		   ret = form("_PORTRAIT%02X",val/9);
	return ret;
}


static make_string(ea, bank) {
	auto base = MK_FP(AskSelector(bank + 1), 0);
	auto ofs = ea + base, _char;
	auto ret ="", stop = 0, i = 0, start_ofs = ofs;
	auto md5 = GetInputMD5();

	if (md5=="D062A77BBB9DA0D3C302F2B3F7BA3331") {
	while(!stop){
		_char=Byte(ofs);
		ofs = ofs + 1;
		i = i + 1;

		if((_char>=0x50)&&(_char<=0x59)) {	// US
			ret = ret + form("%c",_char-0x20);
		} else if((_char>=0x5A)&&(_char<=0x73)) {
			ret = ret + form("%c",_char-0x19);
		} else if((_char>=0x74)&&(_char<=0x8D)) {
			ret = ret + form("%c",_char-0x13);
		} else if(_char==0x8E) {
			ret = ret + "?";
		} else if(_char==0x8F) {
			ret = ret + "!";
		} else if(_char==0x8E) {
			ret = ret + "?";
		} else if(_char==0x8F) {
			ret = ret + "!";
		} else if(_char==0x90) {
			ret = ret + "'";
		} else if(_char==0xEE) {
			ret = ret + ".";
		} else if(_char==0xE4) {
			ret = ret + ".";
		} else if(_char==0xE5) {
			ret = ret + ",";
		} else if(_char==0xE7) {
			ret = ret + "-";
		} else if(_char==0xEF) {
			ret = ret + "(";
		} else if(_char==0xF0) {
			ret = ret + ")";
		} else if(_char==0xF1) {
			ret = ret + " ";
		} else if(_char==0xFF) {
			if (Byte(ofs)==0xFF) {
				stop = 1;
				make_data_array(start_ofs, i + 1, "");
			} else {
				ret = ret + "\\";
				make_data_array(start_ofs, i, "");
				i = 0;
				start_ofs = ofs;
			}
		} else {
			ret = ret + "_";
		}
	}
	} else {
	while(!stop){
		auto _pchar=Byte(ofs-1);
		_char=Byte(ofs);
		auto _nchar=Byte(ofs+1);
		ofs = ofs + 1;
		i = i + 1;

		if((_char>=0xD8)&&(_char<=0xE1)) {	// JP
			ret = ret + form("%c",_char-0xA8);
		} else if((_char>=0x50)&&(_char<=0x69)) {
			ret = ret + form("%c",_char-0x0F);
#ifdef ROMAJI
		} else if(_char==0x6A) { ret = ret + "a";
		} else if(_char==0x6B) { ret = ret + "i";
		} else if(_char==0x6C) { ret = ret + "u";
		} else if(_char==0x6D) { ret = ret + "e";
		} else if(_char==0x6E) { ret = ret + "o";

		} else if(_char==0x6F) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"g":"") + "ga"):(((_pchar==0xA0)?"k":"") + "ka"));
		} else if(_char==0x70) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"g":"") + "gi"):(((_pchar==0xA0)?"k":"") + "ki"));
		} else if(_char==0x71) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"g":"") + "gu"):(((_pchar==0xA0)?"k":"") + "ku"));
		} else if(_char==0x72) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"g":"") + "ge"):(((_pchar==0xA0)?"k":"") + "ke"));
		} else if(_char==0x73) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"g":"") + "go"):(((_pchar==0xA0)?"k":"") + "ko"));
		} else if(_char==0x74) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"z":"") + "za"):(((_pchar==0xA0)?"s":"") + "sa"));
		} else if(_char==0x75) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"z":"") + "zi"):(((_pchar==0xA0)?"s":"") + "si"));
		} else if(_char==0x76) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"z":"") + "zu"):(((_pchar==0xA0)?"s":"") + "su"));
		} else if(_char==0x77) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"z":"") + "ze"):(((_pchar==0xA0)?"s":"") + "se"));
		} else if(_char==0x78) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"z":"") + "zo"):(((_pchar==0xA0)?"s":"") + "so"));
		} else if(_char==0x79) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"d":"") + "da"):(((_pchar==0xA0)?"t":"") + "ta"));
		} else if(_char==0x7A) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"d":"") + "di"):(((_pchar==0xA0)?"t":"") + "ti"));
		} else if(_char==0x7B) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"d":"") + "du"):(((_pchar==0xA0)?"t":"") + "tu"));
		} else if(_char==0x7C) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"d":"") + "de"):(((_pchar==0xA0)?"t":"") + "te"));
		} else if(_char==0x7D) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"d":"") + "do"):(((_pchar==0xA0)?"t":"") + "to"));

		} else if(_char==0x7E) { ret = ret + ((_pchar==0xA0)?"n":"") + "na";
		} else if(_char==0x7F) { ret = ret + ((_pchar==0xA0)?"n":"") + "ni";
		} else if(_char==0x80) { ret = ret + ((_pchar==0xA0)?"n":"") + "nu";
		} else if(_char==0x81) { ret = ret + ((_pchar==0xA0)?"n":"") + "ne";
		} else if(_char==0x82) { ret = ret + ((_pchar==0xA0)?"n":"") + "no";

		} else if(_char==0x83) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"b":"") + "ba"):((_nchar==0xF6)?(((_pchar==0xA0)?"p":"") + "pa"):(((_pchar==0xA0)?"h":"") + "ha")));
		} else if(_char==0x84) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"b":"") + "bi"):((_nchar==0xF6)?(((_pchar==0xA0)?"p":"") + "pi"):(((_pchar==0xA0)?"h":"") + "hi")));
		} else if(_char==0x85) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"b":"") + "bu"):((_nchar==0xF6)?(((_pchar==0xA0)?"p":"") + "pu"):(((_pchar==0xA0)?"h":"") + "hu")));
		} else if(_char==0x86) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"b":"") + "be"):((_nchar==0xF6)?(((_pchar==0xA0)?"p":"") + "pe"):(((_pchar==0xA0)?"h":"") + "he")));
		} else if(_char==0x87) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xA0)?"b":"") + "bo"):((_nchar==0xF6)?(((_pchar==0xA0)?"p":"") + "po"):(((_pchar==0xA0)?"h":"") + "ho")));

		} else if(_char==0x88) { ret = ret + "ma";
		} else if(_char==0x89) { ret = ret + "mi";
		} else if(_char==0x8A) { ret = ret + "mu";
		} else if(_char==0x8B) { ret = ret + "me";
		} else if(_char==0x8C) { ret = ret + "mo";
		} else if(_char==0x8D) { ret = ret + "ya";
		} else if(_char==0x8E) { ret = ret + "yu";
		} else if(_char==0x8F) { ret = ret + "yo";

		} else if(_char==0x90) { ret = ret + "ra";
		} else if(_char==0x91) { ret = ret + "ri";
		} else if(_char==0x92) { ret = ret + "ru";
		} else if(_char==0x93) { ret = ret + "re";
		} else if(_char==0x94) { ret = ret + "ro";
		} else if(_char==0x95) { ret = ret + "wa";
		} else if(_char==0x96) { ret = ret + "n";
		} else if(_char==0x97) { ret = ret + "wo";
//		} else if(_char==0x98) { ret = ret + "[aa]";
//		} else if(_char==0x99) { ret = ret + "[ii]";
//		} else if(_char==0x9A) { ret = ret + "[uu]";
//		} else if(_char==0x9B) { ret = ret + "[ee]";
//		} else if(_char==0x9C) { ret = ret + "[oo]";
		} else if(_char==0x9D) { ret = ret + "ya";
		} else if(_char==0x9E) { ret = ret + "yu";
		} else if(_char==0x9F) { ret = ret + "yo";

		} else if(_char==0xA0) { // ret = ret + "[tt]";
		} else if(_char==0xA1) { ret = ret + "A";
		} else if(_char==0xA2) { ret = ret + "I";
		} else if(_char==0xA3) { ret = ret + "U";
		} else if(_char==0xA4) { ret = ret + "E";
		} else if(_char==0xA5) { ret = ret + "O";

		} else if(_char==0xA6) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"G":"")+"GA"):(((_pchar==0xD7)?"K":"")+"KA"));
		} else if(_char==0xA7) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"G":"")+"GI"):(((_pchar==0xD7)?"K":"")+"KI"));
		} else if(_char==0xA8) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"G":"")+"GU"):(((_pchar==0xD7)?"K":"")+"KU"));
		} else if(_char==0xA9) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"G":"")+"GE"):(((_pchar==0xD7)?"K":"")+"KE"));
		} else if(_char==0xAA) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"G":"")+"GO"):(((_pchar==0xD7)?"K":"")+"KO"));
		} else if(_char==0xAB) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"Z":"")+"ZA"):(((_pchar==0xD7)?"S":"")+"SA"));
		} else if(_char==0xAC) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"Z":"")+"ZI"):(((_pchar==0xD7)?"S":"")+"SI"));
		} else if(_char==0xAD) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"Z":"")+"ZU"):(((_pchar==0xD7)?"S":"")+"SU"));
		} else if(_char==0xAE) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"Z":"")+"ZE"):(((_pchar==0xD7)?"S":"")+"SE"));
		} else if(_char==0xAF) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"Z":"")+"ZO"):(((_pchar==0xD7)?"S":"")+"SO"));
		} else if(_char==0xB0) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"D":"")+"DA"):(((_pchar==0xD7)?"T":"")+"TA"));
		} else if(_char==0xB1) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"D":"")+"DI"):(((_pchar==0xD7)?"T":"")+"TI"));
		} else if(_char==0xB2) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"D":"")+"DU"):(((_pchar==0xD7)?"T":"")+"TU"));
		} else if(_char==0xB3) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"D":"")+"DE"):(((_pchar==0xD7)?"T":"")+"TE"));
		} else if(_char==0xB4) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"D":"")+"DO"):(((_pchar==0xD7)?"T":"")+"TO"));

		} else if(_char==0xB5) { ret = ret + "NA";
		} else if(_char==0xB6) { ret = ret + "NI";
		} else if(_char==0xB7) { ret = ret + "NU";
		} else if(_char==0xB8) { ret = ret + "NE";
		} else if(_char==0xB9) { ret = ret + "NO";

		} else if(_char==0xBA) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"B":"")+"BA"):((_nchar==0xF6)?(((_pchar==0xD7)?"P":"")+"PA"):(((_pchar==0xD7)?"H":"")+"HA")));
		} else if(_char==0xBB) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"B":"")+"BI"):((_nchar==0xF6)?(((_pchar==0xD7)?"P":"")+"PI"):(((_pchar==0xD7)?"H":"")+"HI")));
		} else if(_char==0xBC) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"B":"")+"BU"):((_nchar==0xF6)?(((_pchar==0xD7)?"P":"")+"PU"):(((_pchar==0xD7)?"H":"")+"HU")));
		} else if(_char==0xBD) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"B":"")+"BE"):((_nchar==0xF6)?(((_pchar==0xD7)?"P":"")+"PE"):(((_pchar==0xD7)?"H":"")+"HE")));
		} else if(_char==0xBE) { ret = ret + ((_nchar==0xF5)?(((_pchar==0xD7)?"B":"")+"BO"):((_nchar==0xF6)?(((_pchar==0xD7)?"P":"")+"PO"):(((_pchar==0xD7)?"H":"")+"HO")));

		} else if(_char==0xBF) { ret = ret + "MA";
		} else if(_char==0xC0) { ret = ret + "MI";
		} else if(_char==0xC1) { ret = ret + "MU";
		} else if(_char==0xC2) { ret = ret + "ME";
		} else if(_char==0xC3) { ret = ret + "MO";
		} else if(_char==0xC4) { ret = ret + "YA";
		} else if(_char==0xC5) { ret = ret + "YU";
		} else if(_char==0xC6) { ret = ret + "YO";
		} else if(_char==0xC7) { ret = ret + "RA";
		} else if(_char==0xC8) { ret = ret + "RI";
		} else if(_char==0xC9) { ret = ret + "RU";
		} else if(_char==0xCA) { ret = ret + "RE";
		} else if(_char==0xCB) { ret = ret + "RO";
		} else if(_char==0xCC) { ret = ret + "WA";
		} else if(_char==0xCD) { ret = ret + "N";
		} else if(_char==0xCE) { ret = ret + "WO";
//		} else if(_char==0xCF) { ret = ret + "[AA]";

//		} else if(_char==0xD0) { ret = ret + "[II]";
//		} else if(_char==0xD1) { ret = ret + "[UU]";
//		} else if(_char==0xD2) { ret = ret + "[EE]";
//		} else if(_char==0xD3) { ret = ret + "[OO]";
		} else if(_char==0xD4) { ret = ret + "YA";
		} else if(_char==0xD5) { ret = ret + "YU";
		} else if(_char==0xD6) { ret = ret + "YO";
		} else if(_char==0xD7) { // ret = ret + "[TT]";

		} else if(_char==0xE4) { ret = ret + ".";
		} else if(_char==0xE5) { ret = ret + ",";
		} else if(_char==0xE7) { ret = ret + "-";
		} else if(_char==0xE8) { ret = ret + "?";
		} else if(_char==0xE9) { ret = ret + "!";
		} else if(_char==0xEA) { ret = ret + ".";
		} else if(_char==0xEB) { ret = ret + "{";
		} else if(_char==0xEC) { ret = ret + "}";
		} else if(_char==0xED) { ret = ret + ",";
		} else if(_char==0xEE) { ret = ret + ".";
		} else if(_char==0xEF) { ret = ret + "(";
		} else if(_char==0xF0) { ret = ret + ")";
		} else if(_char==0xF1) { ret = ret + " ";
		} else if(_char==0xF5) { // ret = ret + "\"";
		} else if(_char==0xF6) { // ret = ret + "*";
#else
		} else if(_char==0x6A) { ret = ret + "あ";
		} else if(_char==0x6B) { ret = ret + "い";
		} else if(_char==0x6C) { ret = ret + "う";
		} else if(_char==0x6D) { ret = ret + "え";
		} else if(_char==0x6E) { ret = ret + "お";

		} else if(_char==0x6F) { ret = ret + ((_nchar==0xF5)?("が"):("か"));
		} else if(_char==0x70) { ret = ret + ((_nchar==0xF5)?("ぎ"):("き"));
		} else if(_char==0x71) { ret = ret + ((_nchar==0xF5)?("ぐ"):("く"));
		} else if(_char==0x72) { ret = ret + ((_nchar==0xF5)?("げ"):("け"));
		} else if(_char==0x73) { ret = ret + ((_nchar==0xF5)?("ご"):("こ"));
		} else if(_char==0x74) { ret = ret + ((_nchar==0xF5)?("ざ"):("さ"));
		} else if(_char==0x75) { ret = ret + ((_nchar==0xF5)?("じ"):("し"));
		} else if(_char==0x76) { ret = ret + ((_nchar==0xF5)?("ず"):("す"));
		} else if(_char==0x77) { ret = ret + ((_nchar==0xF5)?("ぜ"):("せ"));
		} else if(_char==0x78) { ret = ret + ((_nchar==0xF5)?("ぞ"):("そ"));
		} else if(_char==0x79) { ret = ret + ((_nchar==0xF5)?("だ"):("た"));
		} else if(_char==0x7A) { ret = ret + ((_nchar==0xF5)?("ぢ"):("ち"));
		} else if(_char==0x7B) { ret = ret + ((_nchar==0xF5)?("づ"):("つ"));
		} else if(_char==0x7C) { ret = ret + ((_nchar==0xF5)?("で"):("て"));
		} else if(_char==0x7D) { ret = ret + ((_nchar==0xF5)?("ど"):("と"));

		} else if(_char==0x7E) { ret = ret + "な";
		} else if(_char==0x7F) { ret = ret + "に";
		} else if(_char==0x80) { ret = ret + "ぬ";
		} else if(_char==0x81) { ret = ret + "ね";
		} else if(_char==0x82) { ret = ret + "の";

		} else if(_char==0x83) { ret = ret + ((_nchar==0xF5)?("ば"):((_nchar==0xF6)?("ぱ"):("は")));
		} else if(_char==0x84) { ret = ret + ((_nchar==0xF5)?("び"):((_nchar==0xF6)?("ぴ"):("ひ")));
		} else if(_char==0x85) { ret = ret + ((_nchar==0xF5)?("ぶ"):((_nchar==0xF6)?("ぷ"):("ふ")));
		} else if(_char==0x86) { ret = ret + ((_nchar==0xF5)?("べ"):((_nchar==0xF6)?("ぺ"):("へ")));
		} else if(_char==0x87) { ret = ret + ((_nchar==0xF5)?("ぼ"):((_nchar==0xF6)?("ぽ"):("ほ")));

		} else if(_char==0x88) { ret = ret + "ま";
		} else if(_char==0x89) { ret = ret + "み";
		} else if(_char==0x8A) { ret = ret + "む";
		} else if(_char==0x8B) { ret = ret + "め";
		} else if(_char==0x8C) { ret = ret + "も";
		} else if(_char==0x8D) { ret = ret + "や";
		} else if(_char==0x8E) { ret = ret + "ゆ";
		} else if(_char==0x8F) { ret = ret + "よ";

		} else if(_char==0x90) { ret = ret + "ら";
		} else if(_char==0x91) { ret = ret + "り";
		} else if(_char==0x92) { ret = ret + "る";
		} else if(_char==0x93) { ret = ret + "れ";
		} else if(_char==0x94) { ret = ret + "ろ";
		} else if(_char==0x95) { ret = ret + "わ";
		} else if(_char==0x96) { ret = ret + "ん";
		} else if(_char==0x97) { ret = ret + "を";
//		} else if(_char==0x98) { ret = ret + "[aa]";
//		} else if(_char==0x99) { ret = ret + "[ii]";
//		} else if(_char==0x9A) { ret = ret + "[uu]";
//		} else if(_char==0x9B) { ret = ret + "[ee]";
//		} else if(_char==0x9C) { ret = ret + "[oo]";
		} else if(_char==0x9D) { ret = ret + "ゃ";
		} else if(_char==0x9E) { ret = ret + "ゅ";
		} else if(_char==0x9F) { ret = ret + "ょ";

		} else if(_char==0xA0) { ret = ret + "っ";
		} else if(_char==0xA1) { ret = ret + "ア";
		} else if(_char==0xA2) { ret = ret + "イ";
		} else if(_char==0xA3) { ret = ret + "ウ";
		} else if(_char==0xA4) { ret = ret + "エ";
		} else if(_char==0xA5) { ret = ret + "オ";

		} else if(_char==0xA6) { ret = ret + ((_nchar==0xF5)?("ガ"):("カ"));
		} else if(_char==0xA7) { ret = ret + ((_nchar==0xF5)?("ギ"):("キ"));
		} else if(_char==0xA8) { ret = ret + ((_nchar==0xF5)?("グ"):("ク"));
		} else if(_char==0xA9) { ret = ret + ((_nchar==0xF5)?("ゲ"):("ケ"));
		} else if(_char==0xAA) { ret = ret + ((_nchar==0xF5)?("ゴ"):("コ"));
		} else if(_char==0xAB) { ret = ret + ((_nchar==0xF5)?("ザ"):("サ"));
		} else if(_char==0xAC) { ret = ret + ((_nchar==0xF5)?("ジ"):("シ"));
		} else if(_char==0xAD) { ret = ret + ((_nchar==0xF5)?("ズ"):("ス"));
		} else if(_char==0xAE) { ret = ret + ((_nchar==0xF5)?("ゼ"):("セ"));
		} else if(_char==0xAF) { ret = ret + ((_nchar==0xF5)?("ゾ"):("ソ"));
		} else if(_char==0xB0) { ret = ret + ((_nchar==0xF5)?("ダ"):("タ"));
		} else if(_char==0xB1) { ret = ret + ((_nchar==0xF5)?("ヂ"):("チ"));
		} else if(_char==0xB2) { ret = ret + ((_nchar==0xF5)?("ヅ"):("ツ"));
		} else if(_char==0xB3) { ret = ret + ((_nchar==0xF5)?("デ"):("テ"));
		} else if(_char==0xB4) { ret = ret + ((_nchar==0xF5)?("ド"):("ト"));

		} else if(_char==0xB5) { ret = ret + "ナ";
		} else if(_char==0xB6) { ret = ret + "ニ";
		} else if(_char==0xB7) { ret = ret + "ヌ";
		} else if(_char==0xB8) { ret = ret + "ネ";
		} else if(_char==0xB9) { ret = ret + "ノ";

		} else if(_char==0xBA) { ret = ret + ((_nchar==0xF5)?("バ"):((_nchar==0xF6)?("パ"):("ハ")));
		} else if(_char==0xBB) { ret = ret + ((_nchar==0xF5)?("ビ"):((_nchar==0xF6)?("ピ"):("ヒ")));
		} else if(_char==0xBC) { ret = ret + ((_nchar==0xF5)?("ブ"):((_nchar==0xF6)?("プ"):("フ")));
		} else if(_char==0xBD) { ret = ret + ((_nchar==0xF5)?("ベ"):((_nchar==0xF6)?("ペ"):("ヘ")));
		} else if(_char==0xBE) { ret = ret + ((_nchar==0xF5)?("ボ"):((_nchar==0xF6)?("ポ"):("ホ")));

		} else if(_char==0xBF) { ret = ret + "マ";
		} else if(_char==0xC0) { ret = ret + "ミ";
		} else if(_char==0xC1) { ret = ret + "ム";
		} else if(_char==0xC2) { ret = ret + "メ";
		} else if(_char==0xC3) { ret = ret + "モ";
		} else if(_char==0xC4) { ret = ret + "ヤ";
		} else if(_char==0xC5) { ret = ret + "ユ";
		} else if(_char==0xC6) { ret = ret + "ヨ";
		} else if(_char==0xC7) { ret = ret + "ラ";
		} else if(_char==0xC8) { ret = ret + "リ";
		} else if(_char==0xC9) { ret = ret + "ル";
		} else if(_char==0xCA) { ret = ret + "レ";
		} else if(_char==0xCB) { ret = ret + "ロ";
		} else if(_char==0xCC) { ret = ret + "ワ";
		} else if(_char==0xCD) { ret = ret + "ン";
		} else if(_char==0xCE) { ret = ret + "ヲ";
//		} else if(_char==0xCF) { ret = ret + "[AA]";

//		} else if(_char==0xD0) { ret = ret + "[II]";
//		} else if(_char==0xD1) { ret = ret + "[UU]";
//		} else if(_char==0xD2) { ret = ret + "[EE]";
//		} else if(_char==0xD3) { ret = ret + "[OO]";
		} else if(_char==0xD4) { ret = ret + "ャ";
		} else if(_char==0xD5) { ret = ret + "ュ";
		} else if(_char==0xD6) { ret = ret + "ョ";
		} else if(_char==0xD7) { ret = ret + "ッ";

		} else if(_char==0xE4) { ret = ret + ".";
		} else if(_char==0xE5) { ret = ret + ",";
		} else if(_char==0xE7) { ret = ret + "-";
		} else if(_char==0xE8) { ret = ret + "?";
		} else if(_char==0xE9) { ret = ret + "!";
		} else if(_char==0xEA) { ret = ret + "。";
		} else if(_char==0xEB) { ret = ret + "「";
		} else if(_char==0xEC) { ret = ret + "」";
		} else if(_char==0xED) { ret = ret + "、";
		} else if(_char==0xEE) { ret = ret + "・";
		} else if(_char==0xEF) { ret = ret + "(";
		} else if(_char==0xF0) { ret = ret + ")";
		} else if(_char==0xF1) { ret = ret + " ";
		} else if(_char==0xF5) { // ret = ret + "\"";
		} else if(_char==0xF6) { // ret = ret + "*";
#endif
		} else if(_char==0xFF) {
			if (Byte(ofs)==0xFF) {
				stop = 1;
				make_data_array(start_ofs, i + 1, "");
			} else {
				ret = ret + "\\";
				make_data_array(start_ofs, i, "");
				i = 0;
				start_ofs = ofs;
			}
		} else {
			ret = ret + "_";
		}
	}
	}
	return ret;
}

static string_to_name(str) {

}

static rambo_opcode(ea, endea) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, script_word, /*stop = 0,*/ tmp_name, loc_name, msg_idx = 0, loc_idx = 0;
	bank = GetReg(ea,"ds") - 1;

	while (ea < endea) { //(!stop) {
//		Message(" start at ea = 0x%08x!\n", ea);
		cmd = Byte(ea);
		cmd_opc = rambo_opcode_name(cmd);
		tmp_name = Name(ea);

		if(tmp_name != "") {
//			Message("name = \"%s\" subsr(0,4) = \"%s\"\n",tmp_name,substr(tmp_name,0,4));
			if(substr(tmp_name,0,7) == "_script") {
				loc_name = tmp_name;
				msg_idx = 0;
				loc_idx = 0;
			} else if(substr(tmp_name,0,5) == "byte_") {
//				Message("0x%08x: \"%s\" -> \"%s\"\n", ea, tmp_name, form("%s_loc%02x",loc_name,loc_idx));
				MakeName(ea, form("%s_loc%02x",loc_name,loc_idx));
				loc_idx = loc_idx + 1;
			}
		}

		if((cmd==0x14)) {
		// STOP
			ea = make_opcode(ea, 1, cmd_opc);
//			stop = 1;
		} else if(
			(cmd==0x07)||
			(cmd==0x08)||
			(cmd==0x09)||
			(cmd==0x0A)||
			(cmd==0x14)||
			(cmd==0x19)||
			(cmd==0x1A)||
			(cmd==0x1B)||
			(cmd==0x1C)||
			(cmd==0x21)||
			(cmd==0x22)||
			(cmd==0x24)||
			(cmd==0x25)||
			(cmd==0x26)||
			(cmd==0x27)||
			(cmd==0x28)||
			(cmd==0x29)) {
		// no args
			ea = make_opcode(ea, 1, cmd_opc);
		} else if(
			(cmd==0x02)||
			(cmd==0x03)) {
		// no args
			make_opcode(ea, 1, form(cmd_opc,"["+make_string(script_word, bank)+"]"));
			ea = ea + 1;
		} else if(
			(cmd==0x00)||
			(cmd==0x01)||
			(cmd==0x04)||
			(cmd==0x05)) {
		// 1b arg PORTRAIT INSERT
			ea = make_opcode(ea, 2, form(cmd_opc,get_spr_name(Byte(ea + 1))));
		} else if(
			(cmd==0x12)||
			(cmd==0x15)||
			(cmd==0x16)||
			(cmd==0x23)) {
		// 1b arg
			ea = make_opcode(ea, 2, form(cmd_opc,Byte(ea + 1)));
		} else if(
			(cmd==0x0D)||
			(cmd==0x0E)) {
		// 1b arg flags
			ea = make_opcode(ea, 2, form(cmd_opc,get_flag_name(Byte(ea + 1))));
		} else if(
			(cmd==0x0F)) {
		// 1b arg next branch flags
			ea = make_opcode(ea, 2, form(cmd_opc,get_flag_name(Byte(ea + 1)),get_next_branch(ea + 2)));
		} else if(
			(cmd==0x10)) {
		// 1b arg next branch
			ea = make_opcode(ea, 2, form(cmd_opc,Byte(ea + 1),get_next_branch(ea + 2)));
		} else if(
			(cmd==0x11)) {
		// no args, 2b opcode, next branch
			ea = make_opcode(ea, 2, form(cmd_opc,get_next_branch(ea + 2)));
		} else if(
			(cmd==0x0B)) {
		// 1w arg ptr
			script_word = Word(ea + 1);
			ea = make_opcode(ea, 3, form(cmd_opc,get_ofs_name(ea + 1, loc_name, msg_idx)));
			msg_idx = msg_idx + 1;
		} else if(
			(cmd==0x13)) {
		// 1w arg jmp
			ea = make_opcode(ea, 3, form(cmd_opc,get_ofs_name(ea + 1, loc_name, msg_idx)));
		} else if(
			(cmd==0x0C)) {
		// 2b arg MSG
			ea = make_opcode(ea, 3, form(cmd_opc,Word(ea + 1),"["+make_string(script_word, bank)+"]"));
		} else if(
			(cmd==0x17)) {
		// 3b arg
			ea = make_opcode(ea, 3, form(cmd_opc,Byte(ea + 1),Byte(ea + 2)));
		} else if(
			(cmd==0x18)) {
		// 1w ofs, 1b ofs
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_ex(ea, bank, 0, 1);
			ea = make_data_array(ea, 1, "");
		} else if(
			(cmd==0x06)) {
		// 4b arg
			ea = make_opcode(ea, 5, form(cmd_opc,Byte(ea + 1),Byte(ea + 2),Byte(ea + 3),Byte(ea + 4)));
		} else {
			Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
//			stop = 1;
		}
	}
	return ea;
}

static rambo_script_selection(void) {
	auto ea;
	auto md5 = GetInputMD5();

	if (md5=="D062A77BBB9DA0D3C302F2B3F7BA3331") {
		Message("US version PRG0 detected\n");
		ea = 0x4535E;	// US
		ea = rambo_opcode(ea,0x45BAC);
	} else {
		Message("JP version detected\n");
		ea = 0x8136A;	// JP
		ea = rambo_opcode(ea,0x81c31);
	}
}

static main(void) {
	AddHotkey("Shift-O", "rambo_script_selection");
	rambo_script_selection();
}
