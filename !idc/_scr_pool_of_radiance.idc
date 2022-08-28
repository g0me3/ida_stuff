#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// POOL OF RADIANCE GAME SCRIPTS
// ---------------------------------

//#define ROMAJI

static pool_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0x00)			ret = "STOP%s            ";
	else if(cmd == 0x01)	ret = "JMP%s             ";
	else if(cmd == 0x02)	ret = "JSR%s             ";
	else if(cmd == 0x03)	ret = "CMP%s             ";
	else if(cmd == 0x04)	ret = "ADD%s             ";
	else if(cmd == 0x05)	ret = "SUB%s             ";
	else if(cmd == 0x06)	ret = "DIV%s             ";
	else if(cmd == 0x07)	ret = "MUL%s             ";
	else if(cmd == 0x08)	ret = "RANDOM%s          ";
	else if(cmd == 0x09)	ret = "MOVE%s            ";
	else if(cmd == 0x0A)	ret = "CHAR_DATA_LOAD%s  ";
	else if(cmd == 0x0B)	ret = "ENEMY_INSERT%s    ";
	else if(cmd == 0x0C)	ret = "DRAWA_START%s     ";
	else if(cmd == 0x0D)	ret = "DRAWA_CONT%s      ";
	else if(cmd == 0x0E)	ret = "DRAWB%s           ";
//	else if(cmd == 0x0F)	ret = "NOP2%s            ";		//	unused
//	else if(cmd == 0x10)	ret = "CMD10%s           ";		//	unused
	else if(cmd == 0x11)	ret = "MSG_CONT%s        ";
	else if(cmd == 0x12)	ret = "MSG_START%s       ";
	else if(cmd == 0x13)	ret = "RTS%s             ";
	else if(cmd == 0x14)	ret = "CMP_CMP%s         ";
//	else if(cmd == 0x15)	ret = "NOP_WITCH%s       ";		// unused
	else if(cmd == 0x16)	ret = "_EQ";
	else if(cmd == 0x17)	ret = "_NE";
	else if(cmd == 0x18)	ret = "_CC";
	else if(cmd == 0x19)	ret = "_GA";
	else if(cmd == 0x1A)	ret = "_LE";
	else if(cmd == 0x1B)	ret = "_CS";
	else if(cmd == 0x1C)	ret = "EVENT_INIT%s      ";
	else if(cmd == 0x1D)	ret = "POWER_CHECK%s     ";
	else if(cmd == 0x1E)	ret = "CMD1E%s           ";
	else if(cmd == 0x1F)	ret = "CMD1F%s           ";
	else if(cmd == 0x20)	ret = "SCRIPT_SET%s      ";
	else if(cmd == 0x21)	ret = "MAP_SET%s         ";
	else if(cmd == 0x22)	ret = "CMD22%s           ";
	else if(cmd == 0x23)	ret = "CMD23%s           ";
	else if(cmd == 0x24)	ret = "EVENT_BEGIN%s     ";
	else if(cmd == 0x25)	ret = "SWITCH             ";
	else if(cmd == 0x26)	ret = "SWITCH             ";
	else if(cmd == 0x27)	ret = "TREASURE_SET%s    ";
	else if(cmd == 0x28)	ret = "MONEY_ADJUST%s    ";
	else if(cmd == 0x29)	ret = "ACTION_SELECT%s   ";
	else if(cmd == 0x2A)	ret = "FETCH_ARRAY%s     ";
	else if(cmd == 0x2B)	ret = "SELECT             ";
	else if(cmd == 0x2C)	ret = "SPEAK_SELECT%s    ";
	else if(cmd == 0x2D)	ret = "NJSR%s            ";
	else if(cmd == 0x2E)	ret = "PARTY_DAMAGE%s    ";
	else if(cmd == 0x2F)	ret = "AND.B%s           ";
	else if(cmd == 0x30)	ret = "OR.B%s            ";
	else if(cmd == 0x31)	ret = "SPRITES_DISABLE%s ";
	else if(cmd == 0x32)	ret = "INVENTORY_SEARCH%s";
	else if(cmd == 0x33)	ret = "CMD33%s           ";
	else if(cmd == 0x34)	ret = "CMD34%s           ";
	else if(cmd == 0x35)	ret = "WRITE_ARRAY%s     ";
	else if(cmd == 0x36)	ret = "CMD36%s           ";
	else if(cmd == 0x37)	ret = "LOC_CHR_PAL_SET%s ";
	else if(cmd == 0x38)	ret = "MAIN_SUB_SET%s    ";
	else if(cmd == 0x39)	ret = "CHARACTER_SELECT%s";
	else if(cmd == 0x3A)	ret = "CMD3A%s           ";
	else if(cmd == 0x3B)	ret = "SPELL_SEARCH%s    ";
//	else if(cmd == 0x3C)	ret = "NOP1%s            ";		//	unused
	return ret;
}

#define ARG_NUM08 0
#define ARG_OFS8  1
#define ARG_NUM16 2
#define ARG_OFS16 3
#define ARG_MSG   0x80

static get_ofs_name(ea, bank) {
	auto base = -1, ret = "", tmp0 = Word(ea), tmp1, subs;
	if(bank == -1) {
		base = get_base_nes_common(ea, tmp0);
		if(base == -1) {
			bank = AskLong(1, form("Can't calc base of OFS at %08X (%04X)\nInput bank manually", ea, tmp0));
			base = MK_FP(AskSelector(bank + 1), 0);
		}
	} else
		base = MK_FP(AskSelector(bank + 1), 0);
	add_dref(ea, base + tmp0, dr_O|XREF_USER);
	Wait();
	ret = Name(base + tmp0);
	if(ret == "") {
		tmp1 = ItemHead(base + tmp0);
		if(isStruct(GetFlags(tmp1))) {
			MakeUnknown(ea, 2, DOUNK_SIMPLE);
			MakeWord(ea);
			OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
			Wait();
			ret = GetDisasm(ea);
			subs = strstr(ret,";");
			ret = substr(ret,6,subs);
//			Message("OFFSET REF 0x%08X, NAME '%s'\n", base + tmp0, ret);
		} else {
			base = base + tmp0 - tmp1;
			ret = form("%s+$%02X", Name(tmp1), base);
		}
		if(ret == "")
			ret = form("0x%08X", base + tmp0);
	}
	Wait();
	return ret;
}

static make_opcode(ea, len, opc) {
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	make_data_array(ea, len, "");
	SetManualInsn(ea, opc);
	return ea + len;
}

static pool_opcode_get_args(ea, count, bank) {
	auto i, nam;
	auto ret = "", argb, argw, msg = "", msg_crlf = 0;
	for(i = 0; i < count; i ++) {
		auto type = Byte(ea);
		ea = ea + 1;
		if(type == ARG_NUM08) {
			argb = Byte(ea);
			ea = ea + 1;
			ret = ret + form("$%02X", argb);
		} else if((type == ARG_OFS8)||(type == ARG_OFS16)) {
			nam = get_ofs_name(ea, bank);
			ea = ea + 2;
			ret = ret + form("%s", nam);
		} else if (type == ARG_NUM16) {
			argw = Word(ea);
			ea = ea + 2;
			ret = ret + form("$%04X", argw);
		} else if (type & ARG_MSG) {
			auto tmsg = type & 0x7F;
			if (tmsg == 0) {
				while ((argb = Byte(ea)) != 0xB5) {
					if(argb == 0xB3) {msg = msg + "{B3}\n        "; msg_crlf = 1; }
					else if(argb == 0xB6) {msg = msg + "\n        "; msg_crlf = 1; }
					else if(argb == 0xB8) {msg = msg + "{B8}\n        "; msg_crlf = 1; }
					else if(argb == 0xB7) msg = msg + "{NAME}";
					else if(argb == 0xBA) {msg = msg + "{BA}\n        "; msg_crlf = 1; }
					else if((argb & 0xF0) == 0xB0) {
						Message(">>UNKNOWN SPECIAL CODE AT 0x%08X\n", ea);
					} else {
						msg = msg + argb;
					}
					ea = ea + 1;
				}
				if(msg_crlf == 1) {
					msg = "\n       \"" + msg + "{B5}\"";
				} else {
					ret = ret + "\"" + msg + "{B5}\"";
					msg = "";
				}
				ea = ea + 1;
			} else if (tmsg == 1) {
				nam = get_ofs_name(ea, bank);
				ea = ea + 2;
				ret = ret + form("%s", nam);
			} else {
				Message(">>WRONG MSG ARG 0x%08X (%02X)\n", ea);
			}
		} else {
			Message(">>WRONG ARG TYPE AT 0x%08X (%02X)\n", ea, type);
		}
		if(i!=(count-1))
			ret = ret + ", ";
	}
	if(msg != "")
		ret = ret + msg;
	return ret;
}

static pool_opcode_get_args_size(ea, count) {
	auto i;
	auto ret = 0;
	for(i=0;i<count;i ++) {
		auto type = Byte(ea);
		ea = ea + 1;
		ret = ret + 1;
		if(type == ARG_NUM08) {
			ea = ea + 1;
			ret = ret + 1;
		} else if((type == ARG_OFS8)||(type == ARG_OFS16)||(type == ARG_NUM16)) {
			ea = ea + 2;
			ret = ret + 2;
		} else if (type & ARG_MSG) {
			auto tmsg = type & 0x7F;
			if (tmsg == 0) {
				while ((Byte(ea)) != 0xB5) {
					ret = ret + 1;
					ea = ea + 1;
				}
				ret = ret + 1;
				ea = ea + 1;
			} else if (tmsg == 1) {
				ea = ea + 2;
				ret = ret + 2;
			}
		} else {
			Message(">>WRONG ARG TYPE AT 0x%08X\n", ea);
		}
	}
	return ret;
}

static pool_opcode_get_args_count(ea, cmd) {
	auto ret = "";
	if((cmd == 0x00)||(cmd == 0x0D)||(cmd == 0x13)||(cmd == 0x15)||(cmd == 0x16)||(cmd == 0x17)||(cmd == 0x18)||(cmd == 0x19)||(cmd == 0x1A)||(cmd == 0x1B)||(cmd == 0x1C)||(cmd == 0x24)||(cmd == 0x31)||(cmd == 0x33)||(cmd == 0x3A))
		return 0;
	else if((cmd == 0x01)||(cmd == 0x02)||(cmd == 0x0A)||(cmd == 0x0E)||(cmd == 0x11)||(cmd == 0x12)||(cmd == 0x1D)||(cmd == 0x20)||(cmd == 0x2D)||(cmd == 0x32)||(cmd == 0x34)||(cmd == 0x38)||(cmd == 0x39))
		return 1;
	else if((cmd == 0x2B)||(cmd == 0x25)||(cmd == 0x26)||(cmd == 0x03)||(cmd == 0x08)||(cmd == 0x09)||(cmd == 0x0F)||(cmd == 0x10)||(cmd == 0x1F)||(cmd == 0x22)||(cmd == 0x36))
		return 2;
	else if((cmd == 0x04)||(cmd == 0x05)||(cmd == 0x06)||(cmd == 0x07)||(cmd == 0x0B)||(cmd == 0x0C)||(cmd == 0x21)||(cmd == 0x28)||(cmd == 0x2A)||(cmd == 0x2F)||(cmd == 0x30)||(cmd == 0x35)||(cmd == 0x37)||(cmd == 0x3B))
		return 3;
	else if((cmd == 0x14)||(cmd == 0x23))
		return 4;
	else if	(cmd == 0x2E)
		return 5;
	else if((cmd == 0x1E)||(cmd == 0x2C))
		return 6;
	else if((cmd == 0x27))
		return 8;
	else if((cmd == 0x29))
		return 0xE;
	Message(">>WRONG OPCODE %02X AT 0x%08X\n", cmd, ea);
	return -1;
}

static pool_opcode(ea, endea) {
	auto cmd_opc = "", arg_count, cmd_opc_mod, cmd, bank, tmp0, tmp1, tmp2, script_word, stop = 0, tbank, oldea;
	bank = GetReg(ea, "ds") - 1;
	while (ea < endea) { // (!stop) {
//		Message(" FETCH ea = 0x%08x\n", ea);
		cmd = Byte(ea);
		cmd_opc = pool_opcode_name(cmd);
		arg_count = pool_opcode_get_args_count(ea, cmd);
		cmd_opc_mod = "   ";
		tbank = -1;
		if((cmd == 0x2D)) {	// native calls
			if(Word(ea + 1 + 1) < 0xC000)
				tbank = 0x3B;
			else if(Word(ea + 1 + 1) < 0xE000)
				tbank = 0x3E;
			else
				tbank = 0x3F;
		}
		if(	(cmd==0x00)||(cmd==0x13)) {
			// NO ARG STOP OPCODE
			ea = make_opcode(ea, 1, form(cmd_opc, cmd_opc_mod));
//			stop = 1;
		} else if((cmd == 0x38)||(cmd == 0x20)) {
			// SPECIAL opcodes to SWITCH CONTEXTS
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, arg_count, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, arg_count) + 1, form(cmd_opc, cmd_opc_mod));
//			stop = 1;
		} else if(
			(cmd==0x0D)||
			(cmd==0x15)||
			(cmd==0x1C)||
			(cmd==0x24)||
			(cmd==0x31)||
			(cmd==0x33)||
			(cmd==0x3A)) {
			// NO ARGS OPCODES
			ea = make_opcode(ea, 1, form(cmd_opc, cmd_opc_mod));
		} else if((cmd >= 0x16)&&(cmd <= 0x1B)) {
			// CONDITIONAL PREFIXES
			cmd_opc_mod = cmd_opc;
			cmd = Byte(ea + 1);
			if((cmd == 0x2D)) {	// native calls
				if(Word(ea + 1 + 1) < 0xC000)
					tbank = 0x3B;
				else if(Word(ea + 1 + 1) < 0xE000)
					tbank = 0x3E;
				else
					tbank = 0x3F;
			}
			arg_count = pool_opcode_get_args_count(ea, cmd);
			if((cmd == 0x25)||(cmd == 0x2B)) {
				Message(">>UNSUPPRTED OPCODE FOR COND PREFIX 0x%08X\n", ea);
//				stop = 1;
			} else {
//				tmp0 = Word(ea + 1 + 1 + 1);
//				tmp0 = tmp0 + get_base_nes_common(ea, tmp0);
				cmd_opc = pool_opcode_name(cmd);
				cmd_opc = cmd_opc + pool_opcode_get_args(ea + 2, arg_count, tbank);
				ea = make_opcode(ea, pool_opcode_get_args_size(ea + 2, arg_count) + 2, form(cmd_opc, cmd_opc_mod));
//				if((cmd == 0x01)||(cmd == 0x02)) {
//					if(tmp0 >= ea)
//						pool_opcode(tmp0);
//				}
			}
		} else if((cmd == 0x25)) {
			// SWITCH CASE JUMP
//			oldea = ea;
			tmp0 = Byte(ea + 1 + 3 + 1);
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, arg_count, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, arg_count) + 1, form(cmd_opc, cmd_opc_mod));
//			Message("SWITCH with %d cases follows\n", tmp0);
			for(tmp1 = 0; tmp1 < tmp0; tmp1 ++) {
//				tmp2 = Word(ea + 1);
//				tmp2 = tmp2 + get_base_nes_common(ea, tmp2);
				ea = make_opcode(ea, pool_opcode_get_args_size(ea, 1), "      CASE_JUMP    " + pool_opcode_get_args(ea, 1, tbank));	// hacky hacky
//				if(tmp2 >= ea)
//					pool_opcode(tmp2);
			}
//			stop = 1;
//			ea = oldea;
		} else if((cmd == 0x26)) {
			// SWITCH CASE CALL
			tmp0 = Byte(ea + 1 + 3 + 1);
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, arg_count, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, arg_count) + 1, form(cmd_opc, cmd_opc_mod));
//			Message("SWITCH with %d cases follows\n", tmp0);
			for(tmp1 = 0; tmp1 < tmp0; tmp1 ++) {
//				tmp2 = Word(ea + 1);
//				tmp2 = tmp2 + get_base_nes_common(ea, tmp2);
				ea = make_opcode(ea, pool_opcode_get_args_size(ea, 1), "      CASE_CALL    " + pool_opcode_get_args(ea, 1, tbank));	// hacky hacky
//				pool_opcode(tmp2);
			}
		} else if((cmd == 0x2B)) {
			// SELECT CASE
			tmp0 = Byte(ea + 1 + 3 + 1);
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, arg_count, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, arg_count) + 1, form(cmd_opc, cmd_opc_mod));
			for(tmp1 = 0; tmp1 < tmp0; tmp1 ++) {
				ea = make_opcode(ea, pool_opcode_get_args_size(ea, 1), "      CASE         " + pool_opcode_get_args(ea, 1, tbank));	// hacky hacky
			}
		} else if((cmd == 0x01)) {	// JMP special case
//			oldea = ea;
//			tmp0 = Word(ea + 1 + 1);
//			tmp0 = tmp0 + get_base_nes_common(ea, tmp0);
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, 1, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, 1) + 1, form(cmd_opc, "   "));
//			if(tmp0 > ea)
//				ea = tmp0;
//			else {
//				stop = 1;
//				ea = oldea;
//			}
		} else if((cmd == 0x02)) {	// JSR special case
			tmp0 = Word(ea + 1 + 1);
			tmp0 = tmp0 + get_base_nes_common(ea, tmp0);
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, 1, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, 1) + 1, form(cmd_opc, "   "));
//			pool_opcode(tmp0);
		} else {
			// WITH ARGS OPCODES
			cmd_opc = cmd_opc + pool_opcode_get_args(ea + 1, arg_count, tbank);
			ea = make_opcode(ea, pool_opcode_get_args_size(ea + 1, arg_count) + 1, form(cmd_opc, cmd_opc_mod));
		}
	}
	return ea;
}

static pool_script_selection(void) {
	pool_opcode(ScreenEA(), ScreenEA() + 1);
}

static pool_script_auto(void) {
	auto md5 = GetInputMD5();
	Message("START DECOMPILE\n");
	if (md5=="2E859DA9E7BA7C69580F1AF8B459887A") { // US
		pool_opcode(0x06C000, 0x06D7F4);
		pool_opcode(0x06D900, 0x06FE20);
		pool_opcode(0x0D0000, 0x0D173D);
		pool_opcode(0x0D1800, 0x0D3B3C);
		pool_opcode(0x102000, 0x104160);
		pool_opcode(0x104200, 0x105ED3);
		pool_opcode(0x166000, 0x167CE3);
		pool_opcode(0x167E00, 0x169F06);
		pool_opcode(0x1FC000, 0x1FDD0F);
		pool_opcode(0x1FDF00, 0x1FE599);
			pool_opcode(0x1FE5B5, 0x1FED67);
			pool_opcode(0x1FED87, 0x1FEF8A);
		pool_opcode(0x22E000, 0x230308);
		pool_opcode(0x230400, 0x231CC5);
		pool_opcode(0x2C4000, 0x2C6410);
		pool_opcode(0x2C6600, 0x2C7ADD);
		pool_opcode(0x2F6000, 0x2F8388);
		pool_opcode(0x2F8400, 0x2F998C);
		pool_opcode(0x328000, 0x328B71);
		pool_opcode(0x328D00, 0x32B511);
		pool_opcode(0x35A000, 0x35ACCF);
		pool_opcode(0x35AD00, 0x35CFD1);
		pool_opcode(0x38C000, 0x38D301);
		pool_opcode(0x38D400, 0x38F920);
		pool_opcode(0x3BE000, 0x3BEED3);
		pool_opcode(0x3BF200, 0x3C13EF);
		pool_opcode(0x3F0000, 0x3F0D92);
		pool_opcode(0x3F1000, 0x3F2BB5);
		pool_opcode(0x3F2F00, 0x3F3C65);
		pool_opcode(0x422000, 0x423E56);
		pool_opcode(0x423F00, 0x425E83);
	} else {
	}
	Message("DONE DECOMPILE\n");
}

static main(void) {
	AddHotkey("Shift-O", "pool_script_selection");
	pool_script_auto();
}
