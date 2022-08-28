#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// MAKE SOFTWARE SCRIPTING ENGINE
// ---------------------------------
// DARKWING DUCK GB
// DUCK TALES 2 GB
// SUPER MOMOTAROU DENTETSU II GB

//#define DDGB
//#define DT2
#define SMD2

#define ARG_BYTE 1
#define ARG_OFS  3

static dd_opcode_name(cmd) {
	auto ret = "";
	if     (cmd == 0x00) ret = "stop              ";
	else if(cmd == 0x01) ret = "flush_pc          ";
	else if(cmd == 0x02) ret = "delay             ";
	else if(cmd == 0x03) ret = "njmp              ";
	else if(cmd == 0x04) ret = "set_main_sub      ";
	else if(cmd == 0x05) ret = "new_thread        ";
	else if(cmd == 0x06) ret = "njsr              ";
	else if(cmd == 0x07) ret = "jmp               ";
	else if(cmd == 0x08) ret = "jsr               ";
	else if(cmd == 0x09) ret = "ret               ";
	else if(cmd == 0x0A) ret = "break             ";
	else if(cmd == 0x0B) ret = "loopA_reset       ";
	else if(cmd == 0x0C) ret = "loopB_reset       ";
	else if(cmd == 0x0D) ret = "do_loopA          ";
	else if(cmd == 0x0E) ret = "do_loopB          ";
	else if(cmd == 0x0F) ret = "beq               ";
	else if(cmd == 0x10) ret = "bcs               ";
	else if(cmd == 0x11) ret = "bpad              ";
	else if(cmd == 0x12) ret = "switch            ";
	else if(cmd == 0x13) ret = "set_default_branch";		// NOP in other engines
	else if(cmd == 0x14) ret = "thread_restart    ";		// RESTART in other engines
	else if(cmd == 0x15) ret = "memset            ";
#ifdef SMD2
	else if(cmd == 0x16) ret = "mcmp              ";		// 1B + OFS
	else if(cmd == 0x17) ret = "memcpys           ";		// 1B + OFS + OFS
	else if(cmd == 0x18) ret = "memcpyl           ";		// 2B + OFS + OFS
	else if(cmd == 0x19) ret = "mmc_prg_set       ";		// 1B
	else if(cmd == 0x1A) ret = "sys               ";		// 1B
	else if(cmd == 0x1B) ret = "thread_off        ";		// NO ARGS
	else if(cmd == 0x1C) ret = "thread_on         ";		// NO ARGS
	else if(cmd == 0x3B) ret = "wnd_frame         ";
#endif
	else if(cmd == 0x39) ret = "printf_res        ";
	else if(cmd == 0x3A) ret = "rect              ";
	else if(cmd == 0x3C) ret = "cursor_display    ";
	else if(cmd == 0x3E) ret = "pad_read_LR       ";
	else if(cmd == 0x3F) ret = "pad_read_UD       ";
	else if(cmd == 0x40) ret = "pad_test_AB       ";
	else if(cmd == 0x48) ret = "type_set          ";
	else if(cmd == 0x49) ret = "type_wait         ";
	else 		   ret =  form("cmd%02X             ",cmd);
	return ret;
}

static get_base_gb_common_ex(ea, bank, addr) {
	auto base = -1;
	if(bank == -1)
		bank = GetReg(ea,"ds");
	if(addr < 0x4000)
		base = MK_FP(AskSelector(0), 0);
	else if((addr >= 0x4000) && (addr < 0x8000)) {
		if(bank > 0)
			base = MK_FP(AskSelector(bank), 0);
		else
			base = MK_FP(AskSelector(AskLong(0, "Enter Bank Nunber")), 0);
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
	else if (addr == 0xFFFF)
		base = MK_FP(AskSelector(SegByName("IENABLE")),0);
	return base;
}

static get_offset_gb_custom(ea, bank, exec) {
	auto tmp1 = Word(ea);
	auto base = get_base_gb_common_ex(ea, bank, tmp1);
	if ((base == -1) && (bank != -1))
		base = MK_FP(AskSelector(bank), 0);
	if (exec) {
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
	}
	return base + tmp1;
}

/*
static make_offset_gb_custom(ea, bank, exec) {
	auto tmp1 = Word(ea);
	auto base = get_base_gb_common_ex(ea, bank, tmp1);
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeWord(ea);
	if ((base == -1) && (bank != -1))
		base = MK_FP(AskSelector(bank), 0);
	if (base!=-1) {
		OpOffEx(ea, 0, REF_OFF16, -1, base, 0);
	}
	if (exec) {
		MakeCode(base + tmp1);
		AutoMark(base + tmp1, AU_CODE);
	}
	return ea + 2;
}
*/

static arg(opcea, bank, argea, type, exec) {
	auto ret = "", tmp0, tmp1, tmp2, tmp3;
	if(type == ARG_BYTE) {
		tmp0 = Byte(argea);
		ret = form("$%02X",tmp0);
	} else if(type == ARG_OFS) {
		tmp0 = get_offset_gb_custom(argea, bank, exec);
		add_dref(opcea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	}
	return ret;
}

static opcode(ea, opc, args, size) {
	MakeUnknown(ea, size, DOUNK_SIMPLE);
	make_data_array(ea, size, "");
	SetManualInsn(ea, opc + args);
	return ea + size;
}

static make_txt_res(ea, bank) {
	auto ofs = Word(ea), cmd, base, ptr, len;
	if(ofs<0x4000) {
		base = 0;
		ptr = ofs;
	} else {
		base = MK_FP(AskSelector(bank), 0);
		ptr = base+ofs;
	}
	while((cmd=Byte(ptr))!=0xFF) {
		len = Byte(ptr+2);
		ptr = make_data_array(ptr, 3+len, "");
	}
	make_data_array(ptr,1,"");
}

static make_rect_res(ea, bank) {
	auto ofs = Word(ea), cmd, base, ptr, w_, h_;
	if(ofs<0x4000) {
		base = 0;
		ptr = ofs;
	} else {
		if(bank == -1)
			base = MK_FP(AskSelector(AskLong(0, "Enter Bank Nunber")), 0);
		else
			base = MK_FP(AskSelector(bank), 0);
		ptr = base + ofs;
	}
	w_ = Byte(ptr);
	h_ = Byte(ptr+1);
	ptr = make_data_array(ptr, 2, "");
	if(w_&0x80) w_=1;
	if(h_&0x80) {
		ptr = make_data_array_custom(ptr, w_, w_, "");
	} else {
		while(h_!=0) {
			ptr = make_data_array_custom(ptr, w_, w_, "");
			h_ = h_ - 1;
		}
	}
}

static make_type_res(ea, bank) {
	auto ofs = Word(ea), cmd, base, ptr, i;
	if(ofs<0x4000) {
		base = 0;
		ptr = ofs;
	} else {
		base = MK_FP(AskSelector(bank), 0);
		ptr = base+ofs;
	}
	i = 0;
	do {
		cmd = Byte(ptr+i);
		i=i+1;
		if(cmd==0x7E) {
			ptr = make_data_array_custom(ptr, i, i, "");
			i=0;
		}
	} while(cmd!=0x7F);
	ptr = make_data_array_custom(ptr, i, i, "");
}

static dd_opcode(ea, bank) {
	auto cmd_opc = "", cmd, tmp0, tmp1, tmp2, opcargs, opcsize, stop = 0;
	if(bank == -1)
		bank = GetReg(ea,"ds");
	if(ea != BADADDR) {
//		Message(" start at ea = 0x%08x!\n", ea);
		cmd = Byte(ea);

#ifdef DT2
// FOR DUCK TALES 2
		if(cmd>=0x14)
			cmd++;
#endif
		cmd_opc = dd_opcode_name(cmd);

//		Message("OPC%02X bank = %d\n",cmd,bank);

		if((cmd == 0)||(cmd == 0x9)) {	// ret/exit
			ea = opcode(ea, cmd_opc, "", 1);
//			ea = ea - 1;
			stop = 1;
#ifdef SMD2
		} else if((cmd==1)||(cmd==0xB)||(cmd==0xC)||(cmd==0x14)||(cmd==0x1B)||(cmd==0x1C)||(cmd==0x1D)||(cmd==0x1E)||(cmd==0x1F)||(cmd==0x20)||(cmd==0x21)||(cmd==0x24)||(cmd==0x25)||(cmd==0x26)||(cmd==0x27)||(cmd==0x2E)||(cmd==0x2F)||(cmd==0x30)||(cmd==0x31)||(cmd==0x40)||(cmd==0x44)||(cmd==0x45)||(cmd==0x49)) {	// no args
			ea = opcode(ea, cmd_opc, "", 1);
		} else if((cmd==2)||(cmd==0x1A)||(cmd==0x22)||(cmd==0x23)||(cmd==0x2A)||(cmd==0x2B)||(cmd==0x2C)||(cmd==0x2D)||(cmd==0x32)||(cmd==0x33)||(cmd==0x34)||(cmd==0x36)||(cmd==0x37)||(cmd==0x3E)||(cmd==0x3F)) {	// 1b arg
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0), 2);
		} else if((cmd==0x19)) {	// 1b arg MMC CODE
			tmp0 = Byte(ea + 1);
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0), 2);
			ea = dd_opcode(ea, tmp0);
		} else if((cmd==3)||(cmd==6)) {	// call extarnal ofs
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_OFS, 1), 3);
		} else if((cmd==4)) {	// main sub switch
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0), 2);
//			ea = ea - 2;
			stop = 1;
		} else if((cmd==7)||(cmd==0x8)||(cmd==0xA)||(cmd==0xF)||(cmd==0x10)||(cmd==0x13)||(cmd==0x3C)) {	// ofs
			tmp0 = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_OFS, 1), 3);
//			if(cmd != 7)
//				ea = tmp0;
			ea = tmp0;
		} else if((cmd==0x12)) {	// switch
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_OFS, 0), 3);
			ea = ea - 3;
			stop = 1;
		} else if((cmd==0xD)||(cmd==0xE)||(cmd==0x5)||(cmd==0x16)) {	// B O
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_OFS, 0), 4);
		} else if((cmd==0x15)||(cmd==0x11)) {							// B B O
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_BYTE, 0) + ", "+ arg(ea, bank, ea + 3, ARG_OFS, 0), 5);
		} else if((cmd==0x39)) {										// O
//			make_txt_res(ea + 1, bank);
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_OFS, 0), 3);
		} else if((cmd==0x3A)) {										// O O
//			make_rect_res(ea + 2, bank);
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_OFS, 0) + ", " + arg(ea, bank, ea + 3, ARG_OFS, 0), 5);
		} else if((cmd==0x28)||(cmd==0x29)||(cmd==0x35)||(cmd==0x41)||(cmd==0x43)||(cmd==0x47)||(cmd==0x4B)) {	// B B
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_BYTE, 0), 3);
		} else if((cmd==0x17)||(cmd==0x42)||(cmd==0x38)) {				// B O O
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_OFS, 0) + ", " + arg(ea, bank, ea + 4, ARG_OFS, 0), 6);
		} else if((cmd==0x3B)||(cmd==0x18)) {							// B B O O
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 3, ARG_OFS, 0) + ", " + arg(ea, bank, ea + 5, ARG_OFS, 0), 7);
		} else if((cmd==0x48)) {										// B B B O
//			make_type_res(ea + 4, bank);
			ea = opcode(ea, cmd_opc, arg(ea, bank, ea + 1, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 2, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 3, ARG_BYTE, 0) + ", " + arg(ea, bank, ea + 4, ARG_OFS, 0), 6);
		} else {
			Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
		}
/*#else
		} else if((cmd==1)||(cmd==0xB)||(cmd==0xC)||(cmd==0x14)||(cmd==0x18)||(cmd==0x19)||(cmd==0x1A)||(cmd==0x1B)||(cmd==0x1C)||(cmd==0x22)||(cmd==0x23)||(cmd==0x24)||(cmd==0x25)||(cmd==0x26)||(cmd==0x27)||(cmd==0x2E)||(cmd==0x2F)||(cmd==0x30)||(cmd==0x31)||(cmd==0x40)||(cmd==0x43)||(cmd==0x44)||(cmd==0x45)||(cmd==0x49)) {	// no args
			ea = make_data_array(ea, 1, cmd_opc);
		} else if((cmd==2)||(cmd==0x17)||(cmd==0x1F)||(cmd==0x20)||(cmd==0x21)||(cmd==0x2A)||(cmd==0x2B)||(cmd==0x2C)||(cmd==0x2D)||(cmd==0x32)||(cmd==0x34)||(cmd==0x36)||(cmd==0x37)||(cmd==0x3E)||(cmd==0x3F)) {	// 1b arg
			ea = make_data_array(ea, 2, cmd_opc);
		} else if((cmd==3)||(cmd==6)) {	// call extarnal ofs
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_gb_custom(ea, 1);	// with exec
		} else if((cmd==4)) {	// main sub switch
			make_data_array(ea, 2, cmd_opc);
			// stop here
		} else if((cmd==7)||(cmd==0x8)||(cmd==0xA)||(cmd==0xF)||(cmd==0x10)||(cmd==0x13)||(cmd==0x3C)) {	// ofs
			ea = make_data_array(ea, 1, cmd_opc);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else if((cmd==0x12)) {	// switch
			ea = make_data_array(ea, 1, cmd_opc);
			make_offset_gb_custom(ea, 0);	// no exec
			// stop here
		} else if((cmd==0xD)||(cmd==0xE)||(cmd==0x5)) {	// 2b args, ofs
			ea = make_data_array(ea, 2, cmd_opc);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else if((cmd==0x15)||(cmd==0x11)) {	// 3b args, ofs
			ea = make_data_array(ea, 3, cmd_opc);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else if((cmd==0x39)) {	// printf arg ofs
			ea = make_data_array(ea, 1, cmd_opc);
			make_txt_res(ea, bank);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else if((cmd==0x3A)) {	// regt ofs ofs
			ea = make_data_array(ea, 3, cmd_opc);
			make_rect_res(ea, bank);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else if((cmd==0x47)||(cmd==0x28)||(cmd==0x29)||(cmd==0x35)||(cmd==0x4B)) {	// 2b arg
			ea = make_data_array(ea, 3, cmd_opc);
		} else if((cmd==0x48)) {	// type setup
			ea = make_data_array(ea, 4, cmd_opc);
			make_type_res(ea, bank);
			ea = make_offset_gb_custom(ea, 0);	// no exec
		} else {
			Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
		}*/
#endif
		return ea;
	}
}

static dd_script_selection(void) {
	Jump(dd_opcode(ScreenEA(),-1));
}

static main(void) {
	AddHotkey("Shift-O", "dd_script_selection");
}
