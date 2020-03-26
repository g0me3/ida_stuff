#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// MARY SHELLY'S FRANKENSTEIN (BIT MASTERS)
// ---------------------------------

static franken_opcode_size(cmd) {
	auto ret = -1;
	if     (cmd == 0x8001)	ret = 0;
	else if(cmd == 0x8003)	ret = 1000;	//	variable size
	else if(cmd == 0x8004)	ret = 7;	//      ; dat
	else if(cmd == 0x8005)	ret = 3;	//      ; dat
	else if(cmd == 0x8006)	ret = 3;	//      ; dat
	else if(cmd == 0x8007)	ret = 0;	//      ; dat
	else if(cmd == 0x8008)	ret = 0;	//      ; dat
	else if(cmd == 0x8009)	ret = 0;	//      ; dat
	else if(cmd == 0x800A)	ret = 3;	//      ; dat
	else if(cmd == 0x800B)	ret = 3;	//
	else if(cmd == 0x800C)	ret = 0;	//      ; dat
	else if(cmd == 0x800D)	ret = 14;	//      ; dat
	else if(cmd == 0x800E)	ret = 0;	//      ; dat
	else if(cmd == 0x8010)	ret = 0;	//      ; dat
	else if(cmd == 0x8011)	ret = 2;	//      ; dat
	else if(cmd == 0x8012)	ret = 0;	//      ; dat
	else if(cmd == 0x8013)	ret = 2;	//      ; dat
	else if(cmd == 0x8014)	ret = 0;	//
	else if(cmd == 0x8015)	ret = 0;	//
	else if(cmd == 0x8016)	ret = 1;	//      ; dat
	else if(cmd == 0x8017)	ret = 1;	//
	else if(cmd == 0x8018)	ret = 1;	//      ; dat
	else if(cmd == 0x8019)	ret = 1;	//      ; dat
	else if(cmd == 0x801A)	ret = 1;	//      ; dat
	else if(cmd == 0x801C)	ret = 5;	//      ; dat
	else if(cmd == 0x801D)	ret = 5;	//      ; dat
	else if(cmd == 0x8021)	ret = 2;	//      ; dat
	else if(cmd == 0x8022)	ret = 2;	//      ; dat
	else if(cmd == 0x8024)	ret = 3;	//      ; dat
	else if(cmd == 0x8025)	ret = 3;	//      ; dat
	else if(cmd == 0x8026)	ret = 3;	//      ; dat
	else if(cmd == 0x802C)	ret = 4;	//
	else if(cmd == 0x802D)	ret = 4;	//      ; dat
	else if(cmd == 0x802E)	ret = 4;	//      ; dat
	else if(cmd == 0x8034)	ret = 4;	//      ; dat
	else if(cmd == 0x8035)	ret = 4;	//      ; dat
	else if(cmd == 0x8036)	ret = 4;	//      ; dat
	else if(cmd == 0x8040)	ret = 6;	//      ; dat
	else if(cmd == 0x8041)	ret = 6;	//      ; dat
	else if(cmd == 0x8042)	ret = 6;	//      ; dat
	else if(cmd == 0x8043)	ret = 6;	//      ; dat
	else if(cmd == 0x8044)	ret = 6;	//      ; dat
	else if(cmd == 0x8045)	ret = 6;	//      ; dat
	else if(cmd == 0x8048)	ret = 6;	//      ; dat
	else if(cmd == 0x8049)	ret = 6;	//
	else if(cmd == 0x804A)	ret = 7;	//
	else if(cmd == 0x804B)	ret = 7;	//
	else if(cmd == 0x8050)	ret = 7;	//      ; dat
	else if(cmd == 0x8051)	ret = 7;	//      ; dat
	else if(cmd == 0x8060)	ret = 3;	//      ; dat
	else if(cmd == 0x8061)	ret = 3;	//      ; dat
	else if(cmd == 0x8062)	ret = 3;	//      ; dat
	else if(cmd == 0x8064)	ret = 3;	//      ; dat
	else if(cmd == 0x8065)	ret = 0;	//      ; dat
	else if(cmd == 0x8066)	ret = 0;	//      ; dat
	else if(cmd == 0x8068)	ret = 3;	//      ; dat
	else if(cmd == 0x806C)	ret = 1;	//      ; dat
	else if(cmd == 0x806D)	ret = 1;	//      ; dat
	else if(cmd == 0x8071)	ret = 11;	//      ; dat
	else if(cmd == 0x8072)	ret = 11;	//
	else if(cmd == 0x8073)	ret = 11;	//
	else if(cmd == 0x8080)	ret = 2;	//      ; dat
	else if(cmd == 0x8081)	ret = 3;	//      ; dat
	else if(cmd == 0x8082)	ret = 5;	//      ; dat
	else if(cmd == 0x8085)	ret = 3;	//      ; dat
	else if(cmd == 0x8086)	ret = 3;	//      ; dat
	else if(cmd == 0x8089)	ret = 3;	//      ; dat
	else if(cmd == 0x808C)	ret = 2;	//      ; dat
	else if(cmd == 0x808D)	ret = 2;	//      ; dat
	else if(cmd == 0x808E)	ret = 2;	//
	else if(cmd == 0x8095)	ret = 4;	//      ; dat
	else if(cmd == 0x809D)	ret = 4;	//      ; dat
	else if(cmd == 0x80A3)	ret = 6;	//
	else if(cmd == 0x80A4)	ret = 7;	//      ; dat
	else if(cmd == 0x80A5)	ret = 7;	//      ; dat
	else if(cmd == 0x80A6)	ret = 7;	//      ; dat
	else if(cmd == 0x80A7)	ret = 7;	//      ; dat
	else if(cmd == 0x80B2)	ret = 5;	//      ; dat
	else if(cmd == 0x80B4)	ret = 6;	//      ; dat
	else if(cmd == 0x80B5)	ret = 6;	//      ; dat
	else if(cmd == 0x80B6)	ret = 6;	//      ; dat
	else if(cmd == 0x80B7)	ret = 6;	//      ; dat
	else if(cmd == 0x80BC)	ret = 5;	//      ; dat
	else if(cmd == 0x80BD)	ret = 5;	//      ; dat
	else if(cmd == 0x80BE)	ret = 5;	//      ; dat
	else if(cmd == 0x80BF)	ret = 5;	//      ; dat
	else if(cmd == 0x80C4)	ret = 7;	//      ; dat
	else if(cmd == 0x80C5)	ret = 7;	//      ; dat
	else if(cmd == 0x80C6)	ret = 7;	//      ; dat
	else if(cmd == 0x80C7)	ret = 7;	//      ; dat
	else if(cmd == 0x80D1)	ret = 3;	//      ; dat
	else if(cmd == 0x80DD)	ret = 2;	//      ; dat
	else if(cmd == 0x80E1)	ret = 3;	//      ; dat
	else if(cmd == 0x80ED)	ret = 2;	//      ; dat
	else if(cmd == 0x80F1)	ret = 4;	//
	else if(cmd == 0x80F5)	ret = 4;	//      ; dat
	else if(cmd == 0x80F9)	ret = 4;	//
	else if(cmd == 0x80FD)	ret = 4;	//      ; dat
	else if(cmd == 0x8100)	ret = 4;	//
	else if(cmd == 0x8101)	ret = 4;	//      ; dat
	else if(cmd == 0x8105)	ret = 3;	//
	else if(cmd == 0x8109)	ret = 3;	//
	else if(cmd == 0x810A)	ret = 3;	//      ; dat
	else if(cmd == 0x8121)	ret = 3;	//      ; dat
	else if(cmd == 0x8125)	ret = 3;	//      ; dat
	else if(cmd == 0x8130)	ret = 1;	//      ; dat
	else if(cmd == 0x8131)	ret = 1;	//
	else if(cmd == 0x8134)	ret = 2;	//      ; dat
	else if(cmd == 0x8135)	ret = 2;	//      ; dat
	else if(cmd == 0x8154)	ret = 3;	//      ; dat
	else if(cmd == 0x8155)	ret = 3;	//      ; dat
	else if(cmd == 0x8160)	ret = 4;	//      ; dat
	else					ret = -1;
	return ret;
}

static get_ea(ea) {
	return Word(ea) | (Byte(ea + 2) << 16);
}

static auto_code(ea, rec, force) {
	auto tmp0 = get_ea(ea);
	if(force || (tmp0 > ea)) {
		franken_opcode(tmp0, rec++);
		return 0;
	} else
		return 1;
}

//#define DEBUG
//#define AUTO

static franken_opcode(ea, rec) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, cmd_size, stop = 0, tab = ">";
#ifdef AUTO
	while(!stop) {
#endif
		if(ea != BADADDR) {
			cmd = Word(ea);
			cmd_opc = franken_opcode_name(cmd);
			cmd_size = franken_opcode_size(cmd);

#ifdef DEBUG
			for(tmp0 = 0; tmp0 < rec; tmp0++)
				tab = tab + ">";
			Message("%s0x%08x: %s, args = %d\n", tab, ea, cmd_opc, cmd_size);
#endif

			if(cmd & 0x8000) {
				if(cmd_size != -1)
					ea = make_data_array(ea, 2, cmd_opc);
				else {
					Message(" undefined opcode size 0x%08x = %04x\n", ea, cmd);
					stop = 1;
				}
				if(cmd == 0xBADC0DE) {
					// DUMMY
				} else if((cmd==0x8003)) {									// n * arg5 + far code
					tmp0 = Byte(ea);
					ea = make_data_array(ea, 1, "");
					for(tmp1 = 0; tmp1 < tmp0; tmp1++) {
						ea = make_data_array(ea, 5, "");
#ifdef AUTO
						auto_code(ea, rec, 0);
#endif
						ea = make_far_ofs16_snes(ea, 0, 2, 3, "_obj_loc");
					}
				} else if((cmd==0x8005)||(cmd==0x8006)) {	// far
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_obj_res");
				} else if((cmd==0x8004)) {									// far + arg4
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_obj_res");
					ea = make_data_array(ea, 4, "");
				} else if((cmd==0x801C)||(cmd==0x801D)||(cmd==0x80BC)||(cmd==0x80BD)||(cmd==0x80BE)||(cmd==0x80BF)) {	// arg2 + far code
					ea = make_data_array(ea, 2, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8102)) {	// arg2 + far code
					ea = make_data_array(ea, 2, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
					ea = make_data_array(ea, 1, "");
				} else if((cmd==0x80B5)||(cmd==0x80B6)||(cmd==0x80B7)||(cmd==0x80A3)) {	// arg3 + far code
					ea = make_data_array(ea, 3, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8040)||(cmd==0x8041)||(cmd==0x8044)||(cmd==0x8045)||(cmd==0x8048)||(cmd==0x8049)||(cmd==0x80B4)) {	// arg3 + far code
					ea = make_data_array(ea, 3, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8042)||(cmd==0x8043)) {					// ram + word + far code stop
					ea = make_near_ofs16_snes(ea, 0x7E, "");
					ea = make_data_array(ea, 2, "");
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8061)||(cmd==0x8062)) {					// thread forced
#ifdef AUTO
					auto_code(ea, rec, 1);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_thrd");
				} else if((cmd==0x800A)||(cmd==0x800B)||(cmd==0x8064)||(cmd==0x8068)) {	// thread checked
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_thrd");
				} else if((cmd==0x8060)) {									// jmp
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8071)||(cmd==0x8072)||(cmd==0x8073)) {									// arg5 + far code + far code
					ea = make_data_array(ea, 5, "");
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x804A)||(cmd==0x804B)||(cmd==0x8050)||(cmd==0x8051)||(cmd==0x80A4)||(cmd==0x80A5)||(cmd==0x80A6)||(cmd==0x80A7)) {	// arg4 + far code
					ea = make_data_array(ea, 4, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8082)) {									// byte + far code + byte
					ea = make_data_array(ea, 1, "");
#ifdef AUTO
					auto_code(ea, rec, 1);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
					ea = make_data_array(ea, 1, "");
				} else if((cmd==0x80B2)) {									// word + far code
					ea = make_data_array(ea, 2, "");
#ifdef AUTO
					auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x80C4)||(cmd==0x80C5)||(cmd==0x80C6)||(cmd==0x80C7)) {									// ram + const + far code
					ea = make_near_ofs16_snes(ea, 0x7E, "");
					ea = make_near_ofs16_snes(ea, 0x7E, "");
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if((cmd==0x8160)) {									// arg1 + far code
					ea = make_data_array(ea, 1, "");
#ifdef AUTO
					stop = auto_code(ea, rec, 0);
#endif
					ea = make_far_ofs16_snes(ea, 0, 2, 3, "_scr_loc");
				} else if(cmd_size > 0) {
					ea = make_data_array(ea, cmd_size, "");
				}
			} else {
				if(Word(ea) != 0x0000)
					ea = make_data_array(ea, 2, cmd_opc);
				else
					stop = 1;
			}
		}
#ifdef AUTO
	}
#endif
	return ea;
}

static franken_script_selection(void) {
	auto tmp_ea = ScreenEA();
	if(substr(NameEx(BADADDR, tmp_ea), 0, 8) != "_obj_res")
		Jump(franken_opcode(tmp_ea, 0));
//	franken_opcode(ScreenEA(), 0);
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "franken_script_selection");
}

static franken_opcode_name(cmd) {
	auto ret = "";
	if     (cmd == 0x8001)	ret = "cmd001";
	else if(cmd == 0x8002)	ret = "cmd002";
	else if(cmd == 0x8003)	ret = "cmd003";	//      ; dat
	else if(cmd == 0x8004)	ret = "cmd004";	//      ; dat
	else if(cmd == 0x8005)	ret = "cmd005";	//      ; dat
	else if(cmd == 0x8006)	ret = "cmd006";	//      ; dat
	else if(cmd == 0x8007)	ret = "cmd007";	//      ; dat
	else if(cmd == 0x8008)	ret = "cmd008";	//      ; dat
	else if(cmd == 0x8009)	ret = "cmd009";	//      ; dat
	else if(cmd == 0x800A)	ret = "cmd00A";	//      ; dat
	else if(cmd == 0x800B)	ret = "cmd00B";	//
	else if(cmd == 0x800C)	ret = "cmd00C";	//      ; dat
	else if(cmd == 0x800D)	ret = "cmd00D";	//      ; dat
	else if(cmd == 0x800E)	ret = "cmd00E";	//      ; dat
	else if(cmd == 0x8010)	ret = "cmd010";	//      ; dat
	else if(cmd == 0x8011)	ret = "cmd011";	//      ; dat
	else if(cmd == 0x8012)	ret = "cmd012";	//      ; dat
	else if(cmd == 0x8013)	ret = "cmd013";	//      ; dat
	else if(cmd == 0x8014)	ret = "cmd014";	//
	else if(cmd == 0x8015)	ret = "cmd015";	//
	else if(cmd == 0x8016)	ret = "cmd016";	//      ; dat
	else if(cmd == 0x8017)	ret = "cmd017";	//
	else if(cmd == 0x8018)	ret = "cmd018";	//      ; dat
	else if(cmd == 0x8019)	ret = "cmd019";	//      ; dat
	else if(cmd == 0x801A)	ret = "cmd01A";	//      ; dat
	else if(cmd == 0x801B)	ret = "cmd01B";	//
	else if(cmd == 0x801C)	ret = "cmd01C";	//      ; dat
	else if(cmd == 0x801D)	ret = "cmd01D";	//      ; dat
	else if(cmd == 0x8020)	ret = "cmd020";	//
	else if(cmd == 0x8021)	ret = "cmd021";	//      ; dat
	else if(cmd == 0x8022)	ret = "cmd022";	//      ; dat
	else if(cmd == 0x8024)	ret = "cmd024";	//      ; dat
	else if(cmd == 0x8025)	ret = "cmd025";	//      ; dat
	else if(cmd == 0x8026)	ret = "cmd026";	//      ; dat
	else if(cmd == 0x8028)	ret = "cmd028";	//
	else if(cmd == 0x8029)	ret = "cmd029";	//
	else if(cmd == 0x802A)	ret = "cmd02A";	//
	else if(cmd == 0x802C)	ret = "cmd02C";	//
	else if(cmd == 0x802D)	ret = "cmd02D";	//      ; dat
	else if(cmd == 0x802E)	ret = "cmd02E";	//      ; dat
	else if(cmd == 0x8030)	ret = "cmd030";	//
	else if(cmd == 0x8031)	ret = "cmd031";	//
	else if(cmd == 0x8032)	ret = "cmd032";	//
	else if(cmd == 0x8034)	ret = "cmd034";	//      ; dat
	else if(cmd == 0x8035)	ret = "cmd035";	//      ; dat
	else if(cmd == 0x8036)	ret = "cmd036";	//      ; dat
	else if(cmd == 0x8040)	ret = "cmd040";	//      ; dat
	else if(cmd == 0x8041)	ret = "cmd041";	//      ; dat
	else if(cmd == 0x8042)	ret = "cmd042";	//      ; dat
	else if(cmd == 0x8043)	ret = "cmd043";	//      ; dat
	else if(cmd == 0x8044)	ret = "cmd044";	//      ; dat
	else if(cmd == 0x8045)	ret = "cmd045";	//      ; dat
	else if(cmd == 0x8048)	ret = "cmd048";	//      ; dat
	else if(cmd == 0x8049)	ret = "cmd049";	//
	else if(cmd == 0x804A)	ret = "cmd04A";	//
	else if(cmd == 0x804B)	ret = "cmd04B";	//
	else if(cmd == 0x8050)	ret = "cmd050";	//      ; dat
	else if(cmd == 0x8051)	ret = "cmd051";	//      ; dat
	else if(cmd == 0x8060)	ret = "jmp";	//      ; dat
	else if(cmd == 0x8061)	ret = "cmd061";	//      ; dat
	else if(cmd == 0x8062)	ret = "cmd062";	//      ; dat
	else if(cmd == 0x8064)	ret = "cmd064";	//      ; dat
	else if(cmd == 0x8065)	ret = "cmd065";	//      ; dat
	else if(cmd == 0x8066)	ret = "cmd066";	//      ; dat
	else if(cmd == 0x8068)	ret = "cmd068";	//      ; dat
	else if(cmd == 0x8069)	ret = "cmd069";	//
	else if(cmd == 0x806A)	ret = "cmd06A";	//
	else if(cmd == 0x806C)	ret = "cmd06C";	//      ; dat
	else if(cmd == 0x806D)	ret = "cmd06D";	//      ; dat
	else if(cmd == 0x806E)	ret = "cmd06E";	//
	else if(cmd == 0x8070)	ret = "cmd070";	//
	else if(cmd == 0x8071)	ret = "cmd071";	//      ; dat
	else if(cmd == 0x8072)	ret = "cmd072";	//
	else if(cmd == 0x8073)	ret = "cmd073";	//
	else if(cmd == 0x8074)	ret = "cmd074";	//
	else if(cmd == 0x8075)	ret = "cmd075";	//
	else if(cmd == 0x8076)	ret = "cmd076";	//
	else if(cmd == 0x8080)	ret = "cmd080";	//      ; dat
	else if(cmd == 0x8081)	ret = "cmd081";	//      ; dat
	else if(cmd == 0x8082)	ret = "cmd082";	//      ; dat
	else if(cmd == 0x8084)	ret = "cmd084";	//
	else if(cmd == 0x8085)	ret = "cmd085";	//      ; dat
	else if(cmd == 0x8086)	ret = "cmd086";	//      ; dat
	else if(cmd == 0x8088)	ret = "cmd088";	//
	else if(cmd == 0x8089)	ret = "cmd089";	//      ; dat
	else if(cmd == 0x808A)	ret = "cmd08A";	//
	else if(cmd == 0x808C)	ret = "cmd08C";	//      ; dat
	else if(cmd == 0x808D)	ret = "cmd08D";	//      ; dat
	else if(cmd == 0x808E)	ret = "cmd08E";	//
	else if(cmd == 0x8090)	ret = "cmd090";	//
	else if(cmd == 0x8091)	ret = "cmd091";	//
	else if(cmd == 0x8092)	ret = "cmd092";	//
	else if(cmd == 0x8094)	ret = "cmd094";	//
	else if(cmd == 0x8095)	ret = "cmd095";	//      ; dat
	else if(cmd == 0x8096)	ret = "cmd096";	//
	else if(cmd == 0x8098)	ret = "cmd098";	//
	else if(cmd == 0x8099)	ret = "cmd099";	//
	else if(cmd == 0x809A)	ret = "cmd09A";	//
	else if(cmd == 0x809C)	ret = "cmd09C";	//
	else if(cmd == 0x809D)	ret = "cmd09D";	//      ; dat
	else if(cmd == 0x809E)	ret = "cmd09E";	//
	else if(cmd == 0x80A0)	ret = "cmd0A0";	//
	else if(cmd == 0x80A1)	ret = "cmd0A1";	//
	else if(cmd == 0x80A2)	ret = "cmd0A2";	//
	else if(cmd == 0x80A3)	ret = "cmd0A3";	//
	else if(cmd == 0x80A4)	ret = "cmd0A4";	//      ; dat
	else if(cmd == 0x80A5)	ret = "cmd0A5";	//      ; dat
	else if(cmd == 0x80A6)	ret = "cmd0A6";	//      ; dat
	else if(cmd == 0x80A7)	ret = "cmd0A7";	//      ; dat
	else if(cmd == 0x80A8)	ret = "cmd0A8";	//
	else if(cmd == 0x80A9)	ret = "cmd0A9";	//
	else if(cmd == 0x80AA)	ret = "cmd0AA";	//
	else if(cmd == 0x80AB)	ret = "cmd0AB";	//
	else if(cmd == 0x80AC)	ret = "cmd0AC";	//
	else if(cmd == 0x80AD)	ret = "cmd0AD";	//
	else if(cmd == 0x80AE)	ret = "cmd0AE";	//
	else if(cmd == 0x80AF)	ret = "cmd0AF";	//
	else if(cmd == 0x80B0)	ret = "cmd0B0";	//
	else if(cmd == 0x80B1)	ret = "cmd0B1";	//
	else if(cmd == 0x80B2)	ret = "cmd0B2";	//      ; dat
	else if(cmd == 0x80B3)	ret = "cmd0B3";	//
	else if(cmd == 0x80B4)	ret = "cmd0B4";	//      ; dat
	else if(cmd == 0x80B5)	ret = "cmd0B5";	//      ; dat
	else if(cmd == 0x80B6)	ret = "cmd0B6";	//      ; dat
	else if(cmd == 0x80B7)	ret = "cmd0B7";	//      ; dat
	else if(cmd == 0x80B8)	ret = "cmd0B8";	//
	else if(cmd == 0x80B9)	ret = "cmd0B9";	//
	else if(cmd == 0x80BA)	ret = "cmd0BA";	//
	else if(cmd == 0x80BB)	ret = "cmd0BB";	//
	else if(cmd == 0x80BC)	ret = "cmd0BC";	//      ; dat
	else if(cmd == 0x80BD)	ret = "cmd0BD";	//      ; dat
	else if(cmd == 0x80BE)	ret = "cmd0BE";	//      ; dat
	else if(cmd == 0x80BF)	ret = "cmd0BF";	//      ; dat
	else if(cmd == 0x80C0)	ret = "cmd0C0";	//
	else if(cmd == 0x80C1)	ret = "cmd0C1";	//
	else if(cmd == 0x80C2)	ret = "cmd0C2";	//
	else if(cmd == 0x80C3)	ret = "cmd0C3";	//
	else if(cmd == 0x80C4)	ret = "cmd0C4";	//      ; dat
	else if(cmd == 0x80C5)	ret = "cmd0C5";	//      ; dat
	else if(cmd == 0x80C6)	ret = "cmd0C6";	//      ; dat
	else if(cmd == 0x80C7)	ret = "cmd0C7";	//      ; dat
	else if(cmd == 0x80D0)	ret = "cmd0D0";	//
	else if(cmd == 0x80D1)	ret = "cmd0D1";	//      ; dat
	else if(cmd == 0x80D2)	ret = "cmd0D2";	//
	else if(cmd == 0x80D4)	ret = "cmd0D4";	//
	else if(cmd == 0x80D5)	ret = "cmd0D5";	//
	else if(cmd == 0x80D6)	ret = "cmd0D6";	//
	else if(cmd == 0x80D8)	ret = "cmd0D8";	//
	else if(cmd == 0x80D9)	ret = "cmd0D9";	//
	else if(cmd == 0x80DA)	ret = "cmd0DA";	//
	else if(cmd == 0x80DC)	ret = "cmd0DC";	//
	else if(cmd == 0x80DD)	ret = "cmd0DD";	//      ; dat
	else if(cmd == 0x80DE)	ret = "cmd0DE";	//
	else if(cmd == 0x80E0)	ret = "cmd0E0";	//
	else if(cmd == 0x80E1)	ret = "cmd0E1";	//      ; dat
	else if(cmd == 0x80E2)	ret = "cmd0E2";	//
	else if(cmd == 0x80E4)	ret = "cmd0E4";	//
	else if(cmd == 0x80E5)	ret = "cmd0E5";	//
	else if(cmd == 0x80E6)	ret = "cmd0E6";	//
	else if(cmd == 0x80E8)	ret = "cmd0E8";	//
	else if(cmd == 0x80E9)	ret = "cmd0E9";	//
	else if(cmd == 0x80EA)	ret = "cmd0EA";	//
	else if(cmd == 0x80EC)	ret = "cmd0EC";	//
	else if(cmd == 0x80ED)	ret = "cmd0ED";	//      ; dat
	else if(cmd == 0x80EE)	ret = "cmd0EE";	//
	else if(cmd == 0x80F0)	ret = "cmd0F0";	//
	else if(cmd == 0x80F1)	ret = "cmd0F1";	//
	else if(cmd == 0x80F2)	ret = "cmd0F2";	//
	else if(cmd == 0x80F4)	ret = "cmd0F4";	//
	else if(cmd == 0x80F5)	ret = "cmd0F5";	//      ; dat
	else if(cmd == 0x80F6)	ret = "cmd0F6";	//
	else if(cmd == 0x80F8)	ret = "cmd0F8";	//
	else if(cmd == 0x80F9)	ret = "cmd0F9";	//
	else if(cmd == 0x80FA)	ret = "cmd0FA";	//
	else if(cmd == 0x80FC)	ret = "cmd0FC";	//
	else if(cmd == 0x80FD)	ret = "cmd0FD";	//      ; dat
	else if(cmd == 0x80FE)	ret = "cmd0FE";	//
	else if(cmd == 0x8100)	ret = "cmd100";	//
	else if(cmd == 0x8101)	ret = "cmd101";	//      ; dat
	else if(cmd == 0x8103)	ret = "cmd103";	//
	else if(cmd == 0x8105)	ret = "cmd105";	//
	else if(cmd == 0x8106)	ret = "cmd106";	//      ; dat
	else if(cmd == 0x8107)	ret = "cmd107";	//
	else if(cmd == 0x8109)	ret = "cmd109";	//
	else if(cmd == 0x810A)	ret = "cmd10A";	//      ; dat
	else if(cmd == 0x810B)	ret = "cmd10B";	//      ; dat
	else if(cmd == 0x810C)	ret = "cmd10C";	//
	else if(cmd == 0x810D)	ret = "cmd10D";	//
	else if(cmd == 0x810E)	ret = "cmd10E";	//
	else if(cmd == 0x8120)	ret = "cmd120";	//
	else if(cmd == 0x8121)	ret = "cmd121";	//      ; dat
	else if(cmd == 0x8122)	ret = "cmd122";	//
	else if(cmd == 0x8124)	ret = "cmd124";	//
	else if(cmd == 0x8125)	ret = "cmd125";	//      ; dat
	else if(cmd == 0x8126)	ret = "cmd126";	//
	else if(cmd == 0x8130)	ret = "cmd130";	//      ; dat
	else if(cmd == 0x8131)	ret = "cmd131";	//
	else if(cmd == 0x8134)	ret = "cmd134";	//      ; dat
	else if(cmd == 0x8135)	ret = "cmd135";	//      ; dat
	else if(cmd == 0x8138)	ret = "cmd138";	//
	else if(cmd == 0x8139)	ret = "cmd139";	//
	else if(cmd == 0x813C)	ret = "cmd13C";	//
	else if(cmd == 0x813D)	ret = "cmd13D";	//
	else if(cmd == 0x8140)	ret = "cmd140";	//
	else if(cmd == 0x8141)	ret = "cmd141";	//
	else if(cmd == 0x8142)	ret = "cmd142";	//
	else if(cmd == 0x8144)	ret = "cmd144";	//
	else if(cmd == 0x8145)	ret = "cmd145";	//
	else if(cmd == 0x8146)	ret = "cmd146";	//
	else if(cmd == 0x8148)	ret = "cmd148";	//
	else if(cmd == 0x8149)	ret = "cmd149";	//
	else if(cmd == 0x814A)	ret = "cmd14A";	//
	else if(cmd == 0x814C)	ret = "cmd14C";	//
	else if(cmd == 0x814D)	ret = "cmd14D";	//
	else if(cmd == 0x814E)	ret = "cmd14E";	//
	else if(cmd == 0x8150)	ret = "cmd150";	//
	else if(cmd == 0x8151)	ret = "cmd151";	//
	else if(cmd == 0x8152)	ret = "cmd152";	//
	else if(cmd == 0x8154)	ret = "cmd154";	//      ; dat
	else if(cmd == 0x8155)	ret = "cmd155";	//      ; dat
	else if(cmd == 0x8156)	ret = "cmd156";	//
	else if(cmd == 0x8160)	ret = "cmd160";	//      ; dat
	else if(cmd == 0x8161)	ret = "cmd161";	//
	else ret = form("spr%04x",cmd);
	return ret;
}
