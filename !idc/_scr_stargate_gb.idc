#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// STARGATE CUTSCENE SCRIPT
// ---------------------------------

static stargate_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0x00) {		ret = "tlm_drawB        %02X";
	} else if(cmd == 0x01) {ret = "loop_begin       %02X";
	} else if(cmd == 0x03) {ret = "apu_mus_load     %02X";
	} else if(cmd == 0x04) {ret = "apu_se_load      %02X";
	} else if(cmd == 0x05) {ret = "do_loop          %04X, %04X";
	} else if(cmd == 0x06) {ret = "delay            %02X";
	} else if(cmd == 0x07) {ret = "wait_for_input   %02X";
	} else if(cmd == 0x08) {ret = "stop";
	} else if(cmd == 0x09) {ret = "tlm_drawA        %02X";
	} else if(cmd == 0x0F) {ret = "set_pal          %02X";
	} else if(cmd == 0x11) {ret = "cmd11            %04X";
	} else if(cmd == 0x16) {ret = "cmd16            %02X";
	} else if(cmd == 0x18) {ret = "cmd18";
	} else if(cmd == 0x19) {ret = "cmd19            %02X";
	} else if(cmd == 0x1A) {ret = "cmd1A";
	} else if(cmd == 0x1C) {ret = "tlm_drawD        %02X";
	} else if(cmd == 0x1D) {ret = "msg              %s";

	}
	return ret;
}

static stargate_manual_instr(ea, size, instr) {
	SetManualInsn(ea, instr);
	ea = make_data_array(ea, size, "");
	return ea;
}

static stargate_opcode(ea) {
	auto cmd_opc = "", cmd, tmp0, tmp1, tmp2;
	if(ea != BADADDR) {
//		Message(" start at ea = 0x%08x!\n", ea);
		cmd = Byte(ea);
		cmd_opc = stargate_opcode_name(cmd);

		if(cmd==8) {											// break, no args
			stargate_manual_instr(ea, 1, cmd_opc);
		} else if((cmd==0x08)||(cmd==0x18)||(cmd==0x1A)) {		// no args
			ea = stargate_manual_instr(ea, 1, cmd_opc);
		} else if((cmd==0x00)||(cmd==0x01)||(cmd==0x03)||(cmd==0x04)||(cmd==0x06)||(cmd==0x07)||(cmd==0x09)||(cmd==0x0F)||(cmd==0x16)||(cmd==0x19)||(cmd==0x1C)) {
																// arg1
			ea = stargate_manual_instr(ea, 2, form(cmd_opc,Byte(ea+1)));
		} else if((cmd==0x05)) {								// arg2 arg2
			ea = stargate_manual_instr(ea, 5, form(cmd_opc,Word(ea+1),Word(ea+3)));
		} else if((cmd==0x11)) {								// arg2
			ea = stargate_manual_instr(ea, 3, form(cmd_opc,Word(ea+1)));
		} else if((cmd==0x1D)) {								// arg1 arg2
			auto ofs = MK_FP(AskSelector(GetReg(ea,"ds")), 0) + Word(ea + 2);
			AddCodeXref(ea, ofs, dr_O|XREF_USER);
			ea = stargate_manual_instr(ea, 4, form(cmd_opc,Name(ofs)));
		} else {
			Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
		}
		return ea;
	}
}

static stargate_script_selection(void) {
	Jump(stargate_opcode(ScreenEA()));
}

static main(void) {
	DelHotkey("Shift-P");
	AddHotkey("Shift-P", "stargate_script_selection");
}
