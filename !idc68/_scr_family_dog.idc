#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// Family Dog SCRIPTS
// ---------------------------------

//#define DEBUG

#define ARG_NUM 1
#define ARG_FAR 4

static family_get_opc_name(opc) {
	auto ret = "";
	if(opc == 0x02) ret = "LOAD_ACC          "; else
	if(opc == 0x03) ret = "INC_ACC           "; else
	if(opc == 0x04) ret = "DEC_ACC           "; else
	if(opc == 0x05) ret = "SCR_SET_FLAGS     "; else
	if(opc == 0x06) ret = "FLAG80_TOGGLE     "; else
	if(opc == 0x07) ret = "FLAG40_TOGGLE     "; else
	if(opc == 0x08) ret = "BREAK             "; else
	if(opc == 0x0E) ret = "DELAY             "; else
	if(opc == 0x10) ret = "STOP              "; else
	if(opc == 0x13) ret = "NJMP              "; else
	if(opc == 0x1B) ret = "NULL              "; else
	if(opc == 0x27) ret = "NULL              "; else
	if(opc == 0x2A) ret = "JMP               "; else
               ret = form("CMD%02X             ", opc);
	return ret;
}

static family_fetch_arg(ea, idx, type) {
	auto ret = "", tmp0, tmp1, tmp2;
	auto argea = ea + 2 + (idx * 2);
	if(type == ARG_NUM) {
		tmp0 = Word(argea);
		ret = form("$%04X",tmp0);
	} else if(type == ARG_FAR) {
		tmp0 = Dword(argea);
		add_dref(ea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	}
	return ret;
}

static family_make_opcode(ea, len, opc, arg0, arg1, arg2, arg3) {
	MakeUnknown(ea, (len * 2) + 2, DOUNK_SIMPLE);
	make_data_array(ea, (len * 2) + 2, "");
	if(arg0 != -1) opc = opc + family_fetch_arg(ea, 0, arg0);
	if(arg1 != -1) opc = opc + ", " + family_fetch_arg(ea, 1, arg1);
	if(arg2 != -1) opc = opc + ", " + family_fetch_arg(ea, 2, arg2);
	if(arg3 != -1) opc = opc + ", " + family_fetch_arg(ea, 3, arg3);
	SetManualInsn(ea, opc);
	return ea + (len * 2) + 2;
}

static family_decompile_opcode(ea, ret) {
	auto tmp0, tmp1, stop = 0;
	auto cmd = Word(ea);
	auto opcname = family_get_opc_name(cmd);
	if((cmd == 0x03)||(cmd == 0x04)||(cmd == 0x08)||(cmd == 0x06)||(cmd == 0x07)||(cmd == 0x0A)||(cmd == 0x10)||(cmd == 0x11)||(cmd == 0x12)||(cmd == 0x19)||(cmd == 0x1B)||(cmd == 0x1D)||(cmd == 0x27)||(cmd == 0x28)||(cmd == 0x29)||(cmd == 0x2C)||(cmd == 0x2D)||(cmd == 0x2F)) {	// no args
		ea = family_make_opcode(ea, 0, opcname, -1, -1, -1, -1);
	} else if((cmd == 0x02)||(cmd == 0x09)||(cmd == 0x0C)||(cmd == 0x0D)||(cmd == 0x0E)||(cmd == 0x14)||(cmd == 0x15)||(cmd == 0x16)||(cmd == 0x17)||(cmd == 0x18)||(cmd == 0x1A)||(cmd == 0x1C)||(cmd == 0x1E)||(cmd == 0x1F)||(cmd == 0x24)||(cmd == 0x26)||(cmd == 0x2E)||(cmd == 0x31)) { // 1 arg
		ea = family_make_opcode(ea, 1, opcname, ARG_NUM, -1, -1, -1);
	} else if((cmd == 0x05)||(cmd == 0x0B)||(cmd == 0x0F)||(cmd == 0x20)||(cmd == 0x21)||(cmd == 0x22)||(cmd == 0x23)||(cmd == 0x25)||(cmd == 0x2B)||(cmd == 0x30)) { // 2 args
		ea = family_make_opcode(ea, 2, opcname, ARG_NUM, ARG_NUM, -1, -1);
	} else if((cmd == 0x01)) { // 3 arg
		ea = family_make_opcode(ea, 3, opcname, ARG_NUM, ARG_NUM, ARG_NUM, -1);
	} else if((cmd == 0x13)||(cmd == 0x2A)) { // OFS
		ea = family_make_opcode(ea, 2, opcname, ARG_FAR, -1, -1, -1);
	} else {
		Message("uncnown opcode 0x%08X!\n", ea);
		ea = -1;
	}
	return ea;
}

static family_script_selection(void) {
	Jump(family_decompile_opcode(ScreenEA(), 0));
}

static family_script_auto(void) {
	auto ea;
	ea = 0x838457;
	while((ea < 0x839977) && (ea != -1)) {
		ea = family_decompile_opcode(ea, 0);
	}
	ea = 0x94FCA9;
	while((ea < 0x94FDAF && (ea != -1))) {
		ea = family_decompile_opcode(ea, 0);
	}
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "family_script_selection");

//	family_script_auto();
}
