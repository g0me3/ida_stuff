#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// PITFALL SCRIPTS
// ---------------------------------

//#define DEBUG
//#define AUTO

static pitfall_opcode_size(cmd) {
	auto ret = -1;
	if     (cmd == 0x00)	ret = 0;
	else if(cmd == 0x01)	ret = 0;
	else if(cmd == 0x02)	ret = 2;
	else if(cmd == 0x03)	ret = 2;
	else if(cmd == 0x04)	ret = 0;
	else if(cmd == 0x05)	ret = 0;
//	else if(cmd == 0x06)	ret = -1;
//	else if(cmd == 0x07)	ret = -1;
//	else if(cmd == 0x08)	ret = -1;
	else if(cmd == 0x09)	ret = 0;
	else if(cmd == 0x0A)	ret = 8;
	else if(cmd == 0x0B)	ret = 1;
	else if(cmd == 0x0C)	ret = 0;
	else if(cmd == 0x0D)	ret = 0;
//	else if(cmd == 0x0E)	ret = -1;
	else if(cmd == 0x0F)	ret = 0;
	else if(cmd == 0x10)	ret = 1;
	else if(cmd == 0x11)	ret = 1;
	else if(cmd == 0x12)	ret = 3;
	else if(cmd == 0x13)	ret = 0;
	else if(cmd == 0x14)	ret = 0;
	else if(cmd == 0x15)	ret = 0;
	else if(cmd == 0x16)	ret = 0;
	else if(cmd == 0x17)	ret = 2;
	else if(cmd == 0x18)	ret = 1;
	else if(cmd == 0x19)	ret = 1;
	else if(cmd == 0x1A)	ret = 2;
	else if(cmd == 0x1B)	ret = 0;
	else if(cmd == 0x1C)	ret = 2;
	else if(cmd == 0x1D)	ret = 1;
	else if(cmd == 0x1E)	ret = 1;
	else if(cmd == 0x1F)	ret = 2;
	else if(cmd == 0x20)	ret = 1;
	else if(cmd == 0x21)	ret = 1;
	else if(cmd == 0x22)	ret = 2;
	else if(cmd == 0x23)	ret = 2;
	else if(cmd == 0x24)	ret = 1;
	else if(cmd == 0x25)	ret = 1;
	else if(cmd == 0x26)	ret = 2;
	else if(cmd == 0x27)	ret = 2;
	else if(cmd == 0x28)	ret = 1;
	else if(cmd == 0x29)	ret = 1;
	else if(cmd == 0x2A)	ret = 2;
	else if(cmd == 0x2B)	ret = 2;
	else if(cmd == 0x2C)	ret = 1;
	else if(cmd == 0x2D)	ret = 1;
	else if(cmd == 0x2E)	ret = 2;
	else if(cmd == 0x2F)	ret = 2;
	else if(cmd == 0x30)	ret = 1;
	else if(cmd == 0x31)	ret = 1;
	else if(cmd == 0x32)	ret = 2;
	else if(cmd == 0x33)	ret = 3;
	else if(cmd == 0x34)	ret = 4;
	else if(cmd == 0x35)	ret = 2;
	else if(cmd == 0x36)	ret = 1;
	else if(cmd == 0x37)	ret = 1;
	else if(cmd == 0x38)	ret = 2;
	else if(cmd == 0x39)	ret = 2;
	else if(cmd == 0x3A)	ret = 1;
	else if(cmd == 0x3B)	ret = 1;
	else if(cmd == 0x3C)	ret = 2;
// ALERT! wrong opcodes
	else if(cmd == 0x3D)	ret = 0;
	else if(cmd == 0x3E)	ret = 0;
	else if(cmd == 0x3F)	ret = 0;
	else if(cmd == 0x40)	ret = 0;
//
	else if(cmd == 0x41)	ret = 2;
	else if(cmd == 0x42)	ret = 8;
	else if(cmd == 0x43)	ret = 8;
	else if(cmd == 0x44)	ret = 0;
	else if(cmd == 0x45)	ret = 0;
	else if(cmd == 0x46)	ret = 0;
	else if(cmd == 0x47)	ret = 0;
	else if(cmd == 0x48)	ret = 1;
	else if(cmd == 0x49)	ret = 2;
	else if(cmd == 0x4A)	ret = 1;
	else if(cmd == 0x4B)	ret = 1;
	else if(cmd == 0x4C)	ret = 2;
	else if(cmd == 0x4D)	ret = 2;
	else if(cmd == 0x4E)	ret = 2;
	else if(cmd == 0x4F)	ret = 2;
	else if(cmd == 0x50)	ret = 2;
	else if(cmd == 0x51)	ret = 2;
	else if(cmd == 0x52)	ret = 2;
	else if(cmd == 0x53)	ret = 1;
	else if(cmd == 0x54)	ret = 1;
	else if(cmd == 0x55)	ret = 1;
	else if(cmd == 0x56)	ret = 1;
	else if(cmd == 0x57)	ret = 3;
	else if(cmd == 0x58)	ret = 3;
	else if(cmd == 0x59)	ret = 3;
	else if(cmd == 0x5A)	ret = 4;
	else if(cmd == 0x5B)	ret = 0;
	else if(cmd == 0x5C)	ret = 0;
	else if(cmd == 0x5D)	ret = 2;
// ALERT! wrong opcodes
	else if(cmd == 0x5E)	ret = 0;
	else if(cmd == 0x5F)	ret = 0;
	else if(cmd == 0x60)	ret = 0;
	else if(cmd == 0x61)	ret = 0;
	else if(cmd == 0x62)	ret = 0;
	else if(cmd == 0x63)	ret = 0;
//
	else if(cmd == 0x64)	ret = 3;
	else if(cmd == 0x65)	ret = 2;
	else if(cmd == 0x66)	ret = 2;
	else if(cmd == 0x67)	ret = 2;
	else if(cmd == 0x68)	ret = 1;
	else if(cmd == 0x69)	ret = 3;
	else if(cmd == 0x6A)	ret = 2;
	else if(cmd == 0x6B)	ret = 2;
	else if(cmd == 0x6C)	ret = 1;
	else if(cmd == 0x6D)	ret = 1;
	else if(cmd == 0x6E)	ret = 1;
	else if(cmd == 0x6F)	ret = 1;
	else if(cmd == 0x70)	ret = 1;
	else if(cmd == 0x71)	ret = 2;
	else if(cmd == 0x72)	ret = 3;
	else if(cmd == 0x73)	ret = 4;
	else if(cmd == 0x74)	ret = 6;
	else if(cmd == 0x75)	ret = 1;
// ALERT! wrong opcodes
	else if(cmd == 0x76)	ret = 0;
	else if(cmd == 0x77)	ret = 0;
//
	else if(cmd == 0x78)	ret = 1;
	else if(cmd == 0x79)	ret = 0;
	else if(cmd == 0x7A)	ret = 2;
	else if(cmd == 0x7B)	ret = 1;
// ALERT! wrong opcodes
	else if(cmd == 0x7C)	ret = 0;
//
	else if(cmd == 0x7D)	ret = 0;
	else if(cmd == 0x7E)	ret = 0;
	else if(cmd == 0x7F)	ret = 0;
// ALERT! wrong opcodes
	else if(cmd == 0x80)	ret = 0;
//
	else if(cmd == 0x81)	ret = 2;
	else if(cmd == 0x82)	ret = 2;
	else if(cmd == 0x83)	ret = 0;
	else if(cmd == 0x84)	ret = 0;
	else if(cmd == 0x85)	ret = 0;
	else if(cmd == 0x86)	ret = 0;
	else if(cmd == 0x87)	ret = 0;
	else if(cmd == 0x88)	ret = 0;
	else if(cmd == 0x89)	ret = 1;
	else if(cmd == 0x8A)	ret = 0;
	else if(cmd == 0x8B)	ret = 0;
// ALERT! wrong opcodes
	else if(cmd == 0x8C)	ret = -1;
//
	else if(cmd == 0x8D)	ret = 0;
	else if(cmd == 0x8E)	ret = 0;
	else if(cmd == 0x8F)	ret = 0;
//	else if(cmd == 0x90)	ret = -1;
	else if(cmd == 0x91)	ret = 0;
	else if(cmd == 0x92)	ret = 0;
	else if(cmd == 0x93)	ret = 2;
	else if(cmd == 0x94)	ret = 1;
	else if(cmd == 0x95)	ret = 1;
	else if(cmd == 0x96)	ret = 2;
	else if(cmd == 0x97)	ret = 4;
	else if(cmd == 0x98)	ret = 0;
// ALERT! wrong opcodes
	else if(cmd == 0x99)	ret = 0;
	else if(cmd == 0x9A)	ret = 0;
	else if(cmd == 0x9B)	ret = 0;
//
	else if(cmd == 0x9C)	ret = 1;
	else if(cmd == 0x9D)	ret = 0;
	else if(cmd == 0x9E)	ret = 2;
	else if(cmd == 0x9F)	ret = 1;
	else if(cmd == 0xA0)	ret = 1;
	else if(cmd == 0xA1)	ret = 2;
	else if(cmd == 0xA2)	ret = 0;
	else if(cmd == 0xA3)	ret = 0;
	else if(cmd == 0xA4)	ret = 0;
	else if(cmd == 0xA5)	ret = 3;
	else if(cmd == 0xA6)	ret = 2;
	else if(cmd == 0xA7)	ret = 0;
	else if(cmd == 0xA8)	ret = 1;
	else if(cmd == 0xA9)	ret = 0;
	else if(cmd == 0xAA)	ret = 0;
	else if(cmd == 0xAB)	ret = 0;
	else if(cmd == 0xAC)	ret = 0;
	else if(cmd == 0xAD)	ret = 0;
	else if(cmd == 0xAE)	ret = 1;
	else if(cmd == 0xAF)	ret = 0;
	else if(cmd == 0xB0)	ret = 0;
	else if(cmd == 0xB1)	ret = 0;
	else if(cmd == 0xB2)	ret = 0;
	else if(cmd == 0xB3)	ret = 0;
	else if(cmd == 0xB4)	ret = 6;
	else if(cmd == 0xB5)	ret = 0;
	else if(cmd == 0xB6)	ret = 2;
	else if(cmd == 0xB7)	ret = 0;
	else if(cmd == 0xB8)	ret = 1;
	else if(cmd == 0xB9)	ret = 2;
	else if(cmd == 0xBA)	ret = 6;
	else if(cmd == 0xBB)	ret = 6;
	else if(cmd == 0xBC)	ret = 0;
	else if(cmd == 0xBD)	ret = 8;
	else if(cmd == 0xBE)	ret = 0;
	else if(cmd == 0xBF)	ret = 4;
	else if(cmd == 0xC0)	ret = 0;
	else if(cmd == 0xC1)	ret = 1;
	else if(cmd == 0xC2)	ret = 0;
	else if(cmd == 0xC3)	ret = 4;
	else if(cmd == 0xC4)	ret = 4;
	else if(cmd == 0xC5)	ret = 5;
	else if(cmd == 0xC6)	ret = 2;
	else if(cmd == 0xC7)	ret = 0;
	else if(cmd == 0xC8)	ret = 0;
	else if(cmd == 0xC9)	ret = 0;
	else if(cmd == 0xCA)	ret = 2;
	else if(cmd == 0xCB)	ret = 1;
	else if(cmd == 0xCC)	ret = 1;
	else if(cmd == 0xCD)	ret = 1;
	else if(cmd == 0xCE)	ret = 1;
	else if(cmd == 0xCF)	ret = 2;
	else if(cmd == 0xD0)	ret = 1;
	else if(cmd == 0xD1)	ret = 1;
	else if(cmd == 0xD2)	ret = 1;
	else if(cmd == 0xD3)	ret = 1;
	else if(cmd == 0xD4)	ret = 5;
	else if(cmd == 0xD5)	ret = 0;
	else if(cmd == 0xD6)	ret = 0;
	else if(cmd == 0xD7)	ret = 0;
	else if(cmd == 0xD8)	ret = 0;
	else if(cmd == 0xD9)	ret = 0;
	else if(cmd == 0xDA)	ret = 0;
	else if(cmd == 0xDB)	ret = 0;
	else if(cmd == 0xDC)	ret = 0;
	else if(cmd == 0xDD)	ret = 0;
	else if(cmd == 0xDE)	ret = 6;
	else if(cmd == 0xDF)	ret = 0;
	else					ret = -1;
	return ret;
}

static pitfall_opcode_name(cmd) {
	auto ret = "";
	if     (cmd == 0x00)	ret = "flush";
	else if(cmd == 0x01)	ret = "exit";
	else if(cmd == 0x02)	ret = "jmp";
	else if(cmd == 0x03)	ret = "jsr";
	else if(cmd == 0x04)	ret = "ret";
	else if(cmd == 0x09)	ret = "break";
	else if(cmd == 0x14)	ret = "input.a";
	else if(cmd == 0x15)	ret = "input.b";
	else if(cmd == 0x16)	ret = "input.c";
	else if(cmd == 0x17)	ret = "move.w acc, mem";
	else if(cmd == 0x18)	ret = "move.b acc, A";
	else if(cmd == 0x19)	ret = "move.b acc, B";
	else if(cmd == 0x1A)	ret = "move.w acc, imm";
	else if(cmd == 0x1C)	ret = "move.w mem, acc";
	else if(cmd == 0x4C)	ret = "cmp.w  acc, imm";
	else if(cmd == 0x4D)	ret = "beq.w";
	else if(cmd == 0x5B)	ret = "move.w scr, acc";
	else if(cmd == 0x64)	ret = "bits.w";
	else if(cmd == 0x7E)	ret = "sar.w  acc, 4";
	else if(cmd == 0x7E)	ret = "neg.w  acc";
	else if(cmd == 0x93)	ret = "move.w scr, _mem";
	else if(cmd == 0x94)	ret = "move.b scr, 0";
	else if(cmd == 0x95)	ret = "move.b scr, 1";
	else if(cmd == 0x96)	ret = "move.w scr, imm";
	else ret = form("cmd%02x",cmd);
	return ret;
}

static pitfall_opcode(ea, rec) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, cmd_size, stop = 0, tab, i, t0, t1;
#ifdef AUTO
	while(!stop) {
#endif
		if(ea != BADADDR) {
			cmd = Byte(ea);
			cmd_opc = pitfall_opcode_name(cmd);
			cmd_size = pitfall_opcode_size(cmd);

#ifdef DEBUG
			tab = ">";
			for(tmp0 = 0; tmp0 < rec; tmp0++)
				tab = form("%s>", tab);
			Message("%s .%02X:%04x: %s, args = %d rec=%d\n", tab, ea >> 16, ea & 0xFFFF, cmd_opc, cmd_size, rec);
#endif

			if(cmd_size != -1)
				ea = make_data_array(ea, 1, cmd_opc);
			else {
				Message("!!undefined opcode %02x at .%02X:%04x\n", cmd, ea >> 16, ea & 0xFFFF);
				stop = -1;
			}
			if (rec > 8) {
//				Message("!!too much calls, stop at .%02X:%04x\n", ea >> 16, ea & 0xFFFF);
				stop = -1;
			}

			if((cmd==0x3D)||(cmd==0x3E)||(cmd==0x3F)||(cmd==0x40)||(cmd==0x5E)||(cmd==0x5F)||(cmd==0x60)||(cmd==0x61)||(cmd==0x62)||(cmd==0x63)||(cmd==0x76)||(cmd==0x77)||(cmd==0x7C)||(cmd==0x80)||(cmd==0x8C)||(cmd==0x99)||(cmd==0x9A)||(cmd==0x9B)) {
				Message("!!warning, bad opcode %02x at .%02X:%04x\n", cmd, ea >> 16, ea & 0xFFFF);
				stop = -1;
			} else if((cmd==0x02)) {
				auto new_ea = Word(ea) + (ea & 0xFF0000);
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_loc");
#ifdef AUTO
				if (new_ea > ea)
					ea = new_ea;
				else {
					if(substr(NameEx(BADADDR, ea), 0, 8) != "_scr_loc") {
						stop = 1;
						ea = ea - 3;
					}
				}
#endif
			} else if((cmd==0x03)) {
#ifdef AUTO
				stop = auto_code_near(ea, rec, 1);
#endif
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_sub");
			} else if((cmd==0x04)||(cmd==0x05)||(cmd==0x09)||(cmd==0x47)||(cmd==0x8F)) {
				stop = 1;
			} else if((cmd==0x41)) {
				MakeCode(Word(ea) | (ea & 0xFF0000));
				AutoMark(Word(ea) | (ea & 0xFF0000), AU_CODE);
				ea = make_near_ofs16_snes(ea, ea >> 16, "_native_loc");
			} else if((cmd==0x0A)) {
				t0 = Byte(ea);
				ea = make_data_array(ea, 1, " arg0");
				for(i = 0; i < 3; i++) {
					t1 = t0 & 3;
					if((t1 == 0))
						ea = make_near_ofs16_snes(ea, 0x7E, "  argx");
					else if ((t1 == 1) || (t1 == 2))
						ea = make_data_array(ea, 1, "  argx");
					else if ((t1 == 3))
						ea = make_data_array(ea, 2, "  argx");
					t0 = t0 >> 2;
				}
			} else if((cmd==0x42)||(cmd==0x43)) {
				ea = make_data_array(ea, 1, " arg0");
				t0 = Byte(ea);
				ea = make_data_array(ea, 1, " arg1");
				for(i = 0; i < 3; i++) {
					t1 = t0 & 3;
					if((t1 == 0))
						ea = make_near_ofs16_snes(ea, 0x7E, "  argx");
					else if ((t1 == 1) || (t1 == 2))
						ea = make_data_array(ea, 1, "  argx");
					else if ((t1 == 3))
						ea = make_data_array(ea, 2, "  argx");
					t0 = t0 >> 2;
				}
			} else if((cmd==0xD4)||(cmd==0xC5)) {
				t0 = Byte(ea);
				ea = make_data_array(ea, 1, " arg0");
				for(i = 0; i < 2; i++) {
					t1 = t0 & 3;
					if((t1 == 0))
						ea = make_near_ofs16_snes(ea, 0x7E, "  argx");
					else if ((t1 == 1) || (t1 == 2))
						ea = make_data_array(ea, 1, "  argx");
					else if ((t1 == 3))
						ea = make_data_array(ea, 2, "  argx");
					t0 = t0 >> 2;
				}
			} else if ((cmd==0x4D)||(cmd==0x4E)||(cmd==0x4F)||(cmd==0x50)||(cmd==0x51)||(cmd==0x52)||(cmd==0x96)) {
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_loc");
			} else if((cmd==0x57)||(cmd==0x58)||(cmd==0x59)||(cmd==0xA5)||(cmd==0x72)) {
				ea = make_data_array(ea, 1, " arg0");
#ifdef AUTO
				stop = auto_code_near(ea, rec, 1);
#endif
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_sub");
			} else if((cmd==0x5A)||(cmd==0x73)) {
				ea = make_data_array(ea, 2, " arg0");
#ifdef AUTO
				stop = auto_code_near(ea, rec, 1);
#endif
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_sub");
			} else if((cmd==0x1A)||(cmd==0x4C)) {
				if(Word(ea)>=0x8000)
					ea = make_near_ofs16_snes(ea, ea >> 16, "_imm_loc");
				else
					ea = make_data_array(ea, 2, " arg0");
			} else if((cmd==0x17)||(cmd==0x1C)||(cmd==0x1F)||(cmd==0x23)||(cmd==0x27)||(cmd==0x2B)||(cmd==0x35)||(cmd==0x39)||(cmd==0x49)||(cmd==0x93)||(cmd==0x9E)) {
				ea = make_near_ofs16_snes(ea, 0x7E, " arg0");
			} else if((cmd==0x64)) {
				ea = make_near_ofs16_snes(ea, 0x7E, " arg0");
				ea = make_data_array(ea, 1, " arg1");
			} else if((cmd==0xC6)) {
				ea = make_near_ofs16_snes(ea, ea >> 16, "_scr_data");
			} else if (cmd_size > 0) {
				ea = make_data_array(ea, cmd_size, " arg0");
			}
		}
#ifdef AUTO
	}
#endif
	if(stop == -1)
		return -1;
	else
		return ea;
}

static pitfall_script_selection(void) {
	auto ea = ScreenEA();
	auto namex = substr(NameEx(BADADDR, ea), 0, 6);
	if((namex!="_scr_d")&&(namex!="_nativ")) {
		if (namex=="_scrip")
			ea = ea + 2;
		auto tmp = pitfall_opcode(ea, 0);
		if(tmp != -1)
			ea = tmp;
		else
			Message("!!script return error!\n");
	} else {
		Message("!!warning! data area ahead! (%s)\n", namex);
	}
	Jump(ea);
}

static pitfall_script_all(void) {
	auto stop = 0, ea = ScreenEA();
	auto tmp = ea, namex;

	Message("Auto decompile start\n");
	while((!stop)&&(ea!=BADADDR)) {
		namex = substr(NameEx(BADADDR, ea), 0, 6);
		if((namex!="_scr_d")&&(namex!="_nativ")) {
			if (namex=="_scrip")
				ea = ea + 2;
			tmp = pitfall_opcode(ea, 0);
			if(tmp != -1)
				ea = tmp;
			else
				stop = 1;
		} else {
			Message("!!warning! data area ahead! (%s)\n", namex);
			stop = 1;
		}
	}
	Jump(ea);
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "pitfall_script_selection");
	DelHotkey("Shift-P");
	AddHotkey("Shift-P", "pitfall_script_all");
}

static get_near_ea(ea) {
	return Word(ea) | (ea & 0xff0000);
}

static auto_code_near(ea, rec, force) {
	auto tmp0 = get_near_ea(ea), tmp1;
	if(force || (tmp0 > ea)) {
		tmp1 = pitfall_opcode(tmp0, rec + 1);
		if(tmp1 != -1)
			return 0;
		else
			return -1;
	} else
		return 1;
}
