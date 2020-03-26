#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// MAKE SOFTWARE SCRIPTING ENGINE
// ---------------------------------
// MILON'S SECRET CASTLE GB

// GetReg(ea,"ds")

static milon_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0x00) {
		ret = "stop";
	} else if(cmd == 0x1) {
		ret = "flush_pc";
	} else if(cmd == 0x2) {
		ret = "delay";
	} else if(cmd == 0x3) {
		ret = "ejsrA";
	} else if(cmd == 0x4) {
		ret = "set_main_sub";
	} else if(cmd == 0x5) {
		ret = "new_thread";
	} else if(cmd == 0x6) {
		ret = "ejsrB";
	} else if(cmd == 0x7) {
		ret = "jmp";
	} else if(cmd == 0x8) {
		ret = "jsr";
	} else if(cmd == 0x9) {
		ret = "ret";
	} else if(cmd == 0xA) {
		ret = "break";
	} else if(cmd == 0xB) {
		ret = "loopA_init";
	} else if(cmd == 0xC) {
		ret = "loopB_init";
	} else if(cmd == 0xD) {
		ret = "do_loopA";
	} else if(cmd == 0xE) {
		ret = "do_loopB";
	} else if(cmd == 0xF) {
		ret = "beq";
	} else if(cmd == 0x10) {
		ret = "bcs";
	} else if(cmd == 0x11) {
		ret = "jmp_if_pad_test";
	} else if(cmd == 0x12) {
		ret = "switch";
	} else if(cmd == 0x13) {
		ret = "set_default_branch";
	} else if(cmd == 0x14) {
		ret = "memset";
	} else if(cmd == 0x15) {
		ret = "mmc_prg";
	} else if(cmd == 0x1B) {
		ret = "thread_on";
	} else if(cmd == 0x1C) {
		ret = "thread_off";
	} else if(cmd == 0x38) {
		ret = "printf";
	} else if(cmd == 0x39) {
		ret = "rect";
	} else if(cmd == 0x3E) {
		ret = "pad_read_LR";
	} else if(cmd == 0x3F) {
		ret = "pad_read_UD";
	} else {
		ret = "unk";
	}
	return ret;
}

static make_offset_gb_custom(ea, bank, exec) {
	auto def_bank = 1;
	auto tmp1 = Word(ea), ret;
	if(exec) {
		if(tmp1>=0xFF80)
			ret = make_offset_gb_code(ea, 0x10);
		else if(tmp1>=0xFF00)
			ret = make_offset_gb(ea, 0xF);
		else if(tmp1>=0xD000)
			ret = make_offset_gb_code(ea, 0xD);
		else if(tmp1>=0xC000)
			ret = make_offset_gb_code(ea, 0xC);
		else if(tmp1>=0x4000) {
			if(ea>=0x4000)
				ret = make_offset_gb_code(ea, bank);
			else
				ret = make_offset_gb_code(ea, def_bank);
		} else
			ret = make_offset_gb_code(ea, 0);
	}
	else {
		if(tmp1>=0xFF80)
			ret = make_offset_gb(ea, 0x10);
		else if(tmp1>=0xFF00)
			ret = make_offset_gb(ea, 0xF);
		else if(tmp1>=0xD000)
			ret = make_offset_gb(ea, 0xD);
		else if(tmp1>=0xC000)
			ret = make_offset_gb(ea, 0xC);
		else if(tmp1>=0x4000) {
			if(ea>=0x4000)
				ret = make_offset_gb(ea, bank);
			else
				ret = make_offset_gb(ea, def_bank);
			}
		else
			ret = make_offset_gb(ea, 0);
	}
	return ret;
}

static make_rect_res(ea, bank) {
	auto ofs = Word(ea), cmd, base, ptr, w_, h_;
	if(ofs<0x4000) {
		base = 0;
		ptr = ofs;
	} else {
		base = MK_FP(AskSelector(bank), 0);
		ptr = base+ofs;
	}
	w_ = Byte(ptr);
	h_ = Byte(ptr+1);
	ptr = make_data_array(ptr, 2, "");
	if(w_&0x80) w_=1;
	if(h_&0x80) {
		ptr = make_data_array(ptr, w_, "");
	} else {
		while(h_!=0) {
			ptr = make_data_array(ptr, w_, "");
			h_ = h_ - 1;
		}
	}
}

static milon_opcode(ea) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2;
	bank = GetReg(ea,"ds");
	if(ea != BADADDR) {
//		Message(" start at ea = 0x%08x!\n", ea);
		cmd = Byte(ea);

		cmd_opc = milon_opcode_name(cmd);

		if((cmd == 0x00)||(cmd == 0x09)) {	// ret/exit
			make_data_array(ea, 1, cmd_opc);
			// stop here
		} else if((cmd==0x01)||(cmd==0xB)||(cmd==0xC)||(cmd==0x17)||(cmd==0x18)||(cmd==0x19)||(cmd==0x1A)||(cmd==0x1B)||(cmd==0x1C)||(cmd==0x1D)||(cmd==0x21)||(cmd==0x22)||(cmd==0x23)||(cmd==0x24)||(cmd==0x25)||(cmd==0x26)||(cmd==0x2D)||(cmd==0x2E)||(cmd==0x2F)||(cmd==0x30)||(cmd==0x48)) {	// no args
			ea = make_data_array(ea, 1, cmd_opc);
		} else if((cmd==0x02)||(cmd==0x15)||(cmd==0x16)||(cmd==0x1E)||(cmd==0x1F)||(cmd==0x20)||(cmd==0x29)||(cmd==0x2A)||(cmd==0x2B)||(cmd==0x2C)||(cmd==0x31)||(cmd==0x32)||(cmd==0x33)||(cmd==0x35)||(cmd==0x36)||(cmd==0x3E)||(cmd==0x3F)) {	// 1b arg
			ea = make_data_array(ea, 2, cmd_opc);
		} else if((cmd==0x03)||(cmd==0x06)) {	// ofs exec
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 1);
		} else if((cmd==0x04)) {	// 1b arg
			make_data_array(ea, 2, cmd_opc);
			// stop here
		} else if((cmd==0x07)||(cmd==0x08)||(cmd==0x0A)||(cmd==0x0F)||(cmd==0x10)||(cmd==0x13)||(cmd==0x38)||(cmd==0x49)) {	// ofs no exec
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 0);
		} else if((cmd==0x12)) {	// switch no exec
			ea = make_data_array(ea, 3, cmd_opc);
			make_offset_gb_custom(ea, bank, 0);
			// stop here
		} else if((cmd==0x05)||(cmd==0x0D)||(cmd==0x0E)) {	// 1b arg, ofs no exec
			ea = make_data_array(ea, 2, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 0);
		} else if((cmd==0x11)||(cmd==0x14)) {	// 2b args, ofs no exec
			ea = make_data_array(ea, 3, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 0);
		} else if((cmd==0x47)) {	// 3b args, ofs no exec
			ea = make_data_array(ea, 4, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 0);
		} else if((cmd==0x39)) {	// ofs rect res
			ea = make_data_array(ea, 3, cmd_opc);
			make_rect_res(ea, bank);
			ea = make_offset_gb_custom(ea, bank, 0);
		} else if((cmd==0x3B)) {	// ofs input res
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_gb_custom(ea, bank, 0);	// no exec
		} else if((cmd==0x27)||(cmd==0x28)||(cmd==0x34)||(cmd==0x45)||(cmd==0x46)) {	// 2b arg
			ea = make_data_array(ea, 3, cmd_opc);
		} else {
			Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
		}
		return ea;
	}
}

static milon_script_selection(void) {
	Jump(milon_opcode(ScreenEA()));
}

static main(void) {
	AddHotkey("Shift-O", "milon_script_selection");
}
