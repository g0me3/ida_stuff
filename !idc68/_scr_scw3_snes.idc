#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// scw3 SCRIPTS
// ---------------------------------

//#define DEBUG

static scw3_make_struct(ea, size, opc) {
	MakeUnknown(ea, size, DOUNK_SIMPLE);
	if( MakeStructEx(ea, -1, opc) == 1)
		ea = ea + size;
	else {
		Message("CAN'T MAKE STRUCTURE! at 0x%08X\n", ea);
		ea = -1;
	}
	return ea;
}

static scw3_opcode_struct(ea, ret) {
	auto cmd, str = "", i, stop, var;

	for(i = 0; i < ret; i++)
		str = str + " ";

#ifdef DEBUG
	Message("%sSUB START 0x%08X\n", str, ea);
#endif

	while (ea != -1) {
		cmd = Byte(ea);
		if     (cmd == 0x01) ea = scw3_make_struct(ea, 0x02, "_cmd01");
		else if(cmd == 0x02) ea = scw3_make_struct(ea, 0x02, "_cmd02");
		else if(cmd == 0x09) {
			if (Byte(ea + 2) != 0xFF) {
				auto a0 = Byte(ea + 0x0C);
				auto a1 = Byte(ea + 0x0F);
				auto a2 = Byte(ea + 0x12);
				auto a3 = Byte(ea + 0x15);
				if(((a0!=0x92)&&(a0>0)) ||
				   ((a1!=0x92)&&(a1>0)) ||
				   ((a2!=0x92)&&(a2>0)) ||
				   ((a3!=0x92)&&(a3>0))) {
					Message("UNSUPPORTED CMD BANK at 0x%08X!\n", ea);
					stop = ea;
					ea = -1;
			   } else
					ea = scw3_make_struct(ea, 0x16, "_cmd09");
			}
			else
				ea = scw3_make_struct(ea, 0x03, "_cmd09_FF");
	 	}
		else if(cmd == 0x0A) ea = scw3_make_struct(ea, 0x02, "_cmd0A");
		else if(cmd == 0x0B) ea = scw3_make_struct(ea, 0x04, "_cmd0B");
		else if(cmd == 0x0C) ea = scw3_make_struct(ea, 0x02, "_cmd0C_MSG_LIB");
		else if(cmd == 0x0D) ea = scw3_make_struct(ea, 0x03, "_cmd0D_MSG");
		else if(cmd == 0x0E) ea = scw3_make_struct(ea, 0x03, "_cmd0E");
		else if(cmd == 0x0F) {
			auto byte = Byte(ea + 3);
			if(byte == 0x92)
				ea = scw3_make_struct(ea, 0x04, "_cmd0F_92");
			else if(byte == 0x82)
				ea = scw3_make_struct(ea, 0x04, "_cmd0F_82");
			else if(byte == 0x8E)
				ea = scw3_make_struct(ea, 0x04, "_cmd0F_8E");
			else {
				Message("UNSUPPORTED CMD BANK at 0x%08X!\n", ea);
				stop = ea;
				ea = -1;
			}
		}
		else if(cmd == 0x10) {
			auto ofs = Word(ea + 4) + (Byte(ea + 6) << 16);
			var = Word(ea + 2);
			if(ofs > ea)	// preventing the infinite loops
				scw3_opcode_struct(ofs, ret + 1);	// recursive call conditional branch
			if(var == 0x0BA9) {
				Message("UNIMPLEMENTER CONDITION at 0x%08X!\n", ea);
				stop = ea;
				ea = -1;
			} else if(var == 0x0BD0) {
				ea = scw3_make_struct(ea, 0x07, "_cmd10_BITMASK");
			} else if((var == 0x0C51)||(var == 0x0BCC)||(var == 0x0BCD)) {
				ea = scw3_make_struct(ea, 0x07, "_cmd10_BEQ_OR_LE");
			} else if(var == 0x0BCF) {
				ea = scw3_make_struct(ea, 0x07, "_cmd10_BEQ");
			} else {
				ea = scw3_make_struct(ea, 0x07, "_cmd10_TEST");
			}
//			ea = scw3_make_struct(ea, 0x07, "_cmd10_COND");
		}
		else if(cmd == 0x11) {
			var = Word(ea + 2);
			if((var == 0x0B74)||(var == 0x0B75)) {
				ea = scw3_make_struct(ea, 0x05, "_cmd11_STORE");
			} else {
				ea = scw3_make_struct(ea, 0x05, "_cmd11_OR");
			}
//			ea = scw3_make_struct(ea, 0x05, "_cmd11_STORE_OR");
		}
		else if(cmd == 0x12) ea = scw3_make_struct(ea, 0x05, "_cmd12_STORE");
		else if(cmd == 0xFF) { ea = scw3_make_struct(ea, 0x01, "_cmdFF_STOP"); stop = ea; ea = -1; }
		else {
			Message("UNKNOWN COMMAND at 0x%08X!\n", ea);
			stop = ea;
			ea = -1;
		}
	}
	return stop;
#ifdef DEBUG
	Message("%s    STOP 0x%08X\n", str, stop);
#endif
}

static scw3_script_selection(void) {
	auto ea = ScreenEA();
	ea = scw3_opcode_struct(ea, 0);
	Jump(ea);
}

static scw3_script_auto(void) {
	auto ea;
	ea = 0x929755;
	while(ea < 0x92C161) {
		ea = scw3_opcode_struct(ea, 0);
	}
	ea = 0x92C2E3;
	while(ea < 0x92D6E7) {
		ea = scw3_opcode_struct(ea, 0);
	}
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "scw3_script_selection");
	DelHotkey("Shift-P");
	AddHotkey("Shift-P", "scw3_script_auto");
}
