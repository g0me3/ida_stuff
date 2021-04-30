#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// NONTAN TO ISSHO APU SCRIPT
// ---------------------------------

static issho_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0xF0) {
		ret = "CMD00";
	} else if(cmd == 0xF1) {
		ret = "CDM01";
	} else if(cmd == 0xF2) {
		ret = "CDM02";
	} else if(cmd == 0xF3) {
		ret = "CDM03";
	} else if(cmd == 0xF4) {
		ret = "LOOP_BEGIN";
	} else if(cmd == 0xF5) {
		ret = "LOOP_END";
	} else if(cmd == 0xF6) {
		ret = "JSR";
	} else if(cmd == 0xF7) {
		ret = "RTS";
	} else if(cmd == 0xF8) {
		ret = "JMP";
	} else if(cmd == 0xF9) {
		ret = "CDM09";
	} else if(cmd == 0xFA) {
		ret = "CDM0A";
	} else if(cmd == 0xFB) {
		ret = "CDM0B";
	} else if(cmd == 0xFC) {
		ret = "CDM0C";
	} else if(cmd == 0xFD) {
		ret = "CDM0D";
	} else if(cmd == 0xFE) {
		ret = "CDM0E";
	} else if(cmd == 0xFF) {
		ret = "STOP";
	} else {
		ret = "unk";
	}
	return ret;
}

static MakeNameAuto(ea,name) {
	if(MakeNameEx(ea,name,SN_CHECK|SN_NOWARN)==0) {
		auto res, nname, nc = 0;
		do {
			nname = form("%s_%d",name,nc);
			nc++;
			res = MakeNameEx(ea,nname,SN_CHECK|SN_NOWARN);
		} while ((res == 0)&&(nc<10));
	}
}

static issho_opcode(ea) {
	auto cmd_opc = "", cmd, bank, base, ptr, tmp0, tmp1, tmp2, stop = 0;
	bank = GetReg(ea,"ds");
	base = MK_FP(AskSelector(bank), 0);
	while (!stop) {
		cmd = Byte(ea);

		if((cmd & 0xF0) == 0xF0) {

			cmd_opc = issho_opcode_name(cmd);

			if((cmd == 0xF7)||(cmd == 0xFF)) {	// ret/exit
				make_data_array(ea, 1, cmd_opc);
				// stop here
				stop = 1;
			} else if((cmd==0xF5)||(cmd==0xFB)||(cmd==0xFD)||(cmd==0xFE)) {	// no arg
				ea = make_data_array(ea, 1, cmd_opc);
			} else if((cmd==0xF0)||(cmd==0xF1)||(cmd==0xF2)||(cmd==0xF3)||(cmd==0xF4)||(cmd==0xF9)||(cmd==0xFA)) {	// 1 arg
				ea = make_data_array(ea, 2, cmd_opc);
			} else if((cmd==0xFC)) {	// 2 arg
				ea = make_data_array(ea, 3, cmd_opc);
			} else if((cmd==0xF6)) {	// jsr
				ea = make_data_array(ea, 1, cmd_opc);
				ptr = base + Word(ea);
				MakeNameAuto(ptr, form("_sub_%08x", ptr));
				ea = make_offset_gb(ea, bank);
				issho_opcode(ptr);
			} else if((cmd==0xF8)) {	// jmp
				ea = make_data_array(ea, 1, cmd_opc);
				ptr = base + Word(ea);
				MakeNameAuto(ptr, form("_jmp_%08x", ptr));
				make_offset_gb(ea, bank);
				if(ptr > ea)
					ea = ptr;
				else
					stop = 1;
			} else {
				Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
				stop = 1;
			}

		} else {
			ea = make_data_array(ea, 1, "data");
		}
	}
}

static issho_script_selection(void) {
	auto ea = ScreenEA(), ptr;
	auto bank = GetReg(ea,"ds");
	auto base = MK_FP(AskSelector(bank), 0);
	auto base_name = Name(ea);
	auto cmd, next_ea;
	next_ea = ea + 2;
	ea = base + Word(ea);
	while((cmd = Byte(ea)) != 0xFF) {
		MakeUnknown(ea, 3, DOUNK_SIMPLE);
		MakeData(ea, FF_BYTE, 1, 0);
		MakeData(ea + 1, FF_WORD, 1, 0);
		ptr = base + Word(ea + 1) + 1;
		Message("apu chnl name='%s' %d at ea = 0x%08x start\n", base_name, cmd, ptr);
		MakeNameAuto(ptr, form("_%s_chnl%d", base_name, cmd));
		OpOffEx(ea + 1, 0, REF_OFF16, -1, base, -1);
		issho_opcode(ptr);
		ea = ea + 3;
	}
	MakeUnknown(ea, 1, DOUNK_SIMPLE);
	MakeData(ea, FF_BYTE, 1, 0);
	Jump(next_ea);
}

static main(void) {
	AddHotkey("Shift-O", "issho_script_selection");
}
