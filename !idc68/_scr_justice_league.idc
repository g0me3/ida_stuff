#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// Justice League SCRIPTS
// ---------------------------------

//#define DEBUG

#define ARG_BYTE 1
#define ARG_WORD 2
#define ARG_OFS  3
#define ARG_MEM  4
#define ARG_PARAM 5
#define ARG_SCRA 6
#define ARG_SCRB 7

static league_get_opc_name(opc) {
	auto ret = "";
	if(opc == 0x00) { ret = "break             "; } else
	if(opc == 0x01) { ret = "nop               "; } else
	if(opc == 0x02) { ret = "jmp               "; } else
	if(opc == 0x03) { ret = "call              "; } else
	if(opc == 0x04) { ret = "ret               "; } else
	if(opc == 0x05) { ret = "stop              "; } else
//	if(opc == 0x07) { ret = "loop              "; } else
//	if(opc == 0x08) { ret = "loop              "; } else
	if(opc == 0x17) { ret = "mem_to_acc        "; } else
	if(opc == 0x18) { ret = "scr_to_acc        "; } else
	if(opc == 0x19) { ret = "vars10_to_acc     "; } else
	if(opc == 0x1A) { ret = "imm_to_acc        "; } else
	if(opc == 0x1C) { ret = "acc_to_mem        "; } else
	if(opc == 0x1D) { ret = "acc_to_scr        "; } else
	if(opc == 0x1E) { ret = "acc_to_vars10     "; } else
	if(opc == 0x1F) { ret = "acc_add_mem       "; } else
	if(opc == 0x20) { ret = "acc_add_scr       "; } else
	if(opc == 0x21) { ret = "acc_add_vars10    "; } else
	if(opc == 0x22) { ret = "acc_add_imm       "; } else
	if(opc == 0x23) { ret = "acc_sub_mem       "; } else
	if(opc == 0x24) { ret = "acc_sub_scr       "; } else
	if(opc == 0x25) { ret = "acc_sub_vars10    "; } else
	if(opc == 0x26) { ret = "imm_sub_acc       "; } else
	if(opc == 0x27) { ret = "imm_and_acc       "; } else
	if(opc == 0x28) { ret = "scr_add_acc       "; } else
	if(opc == 0x2A) { ret = "imm_and_acc       "; } else
	if(opc == 0x2B) { ret = "mem_ora_acc       "; } else
	if(opc == 0x2E) { ret = "imm_ora_acc       "; } else
	if(opc == 0x2F) { ret = "mem_eor_acc       "; } else
	if(opc == 0x32) { ret = "imm_eor_acc       "; } else
	if(opc == 0x35) { ret = "acc_cond_mem      "; } else
	if(opc == 0x36) { ret = "acc_cond_scr      "; } else
	if(opc == 0x37) { ret = "acc_cond_vars10   "; } else
	if(opc == 0x38) { ret = "imm_cond_acc      "; } else
	if(opc == 0x39) { ret = "acc_cond_mem      "; } else
	if(opc == 0x3A) { ret = "acc_cond_scr      "; } else
	if(opc == 0x3B) { ret = "acc_cond_vars10   "; } else
	if(opc == 0x3C) { ret = "acc_cond_imm      "; } else
	if(opc == 0x41) { ret = "njsr              "; } else
	if(opc == 0x46) { ret = "far_ptr_exec      "; } else
	if(opc == 0x47) { ret = "nop               "; } else
	if(opc == 0x49) { ret = "acc_cmp_mem       "; } else
	if(opc == 0x4A) { ret = "acc_cmp_scr       "; } else
	if(opc == 0x4B) { ret = "acc_cmp_vars10    "; } else
	if(opc == 0x4C) { ret = "imm_cmp_acc       "; } else
	if(opc == 0x4D) { ret = "beq               "; } else
	if(opc == 0x4E) { ret = "bne               "; } else
	if(opc == 0x4F) { ret = "bge               "; } else
	if(opc == 0x50) { ret = "bla               "; } else
	if(opc == 0x51) { ret = "bcs               "; } else
	if(opc == 0x52) { ret = "bcc               "; } else
	if(opc == 0x5B) { ret = "far_ptr_load      "; } else
	if(opc == 0x64) { ret = "mem_test          "; } else
	if(opc == 0x65) { ret = "scr_test          "; } else
	if(opc == 0x66) { ret = "vars10_test       "; } else
	if(opc == 0x67) { ret = "imm_test          "; } else
	if(opc == 0x68) { ret = "acc_test          "; } else
	if(opc == 0x69) { ret = "mem_bit           "; } else
	if(opc == 0x6A) { ret = "scr_bit           "; } else
	if(opc == 0x6B) { ret = "vars10_bit        "; } else
	if(opc == 0x81) { ret = "stop              "; } else
	if(opc == 0x85) { ret = "far_switch        "; } else
	if(opc == 0x8A) { ret = "apuA              "; } else
	if(opc == 0x8C) { ret = "printf_libA       "; } else
	if(opc == 0x8D) { ret = "acc_digit_draw    "; } else
	if(opc == 0x8F) { ret = "apuB              "; } else
	if(opc == 0x99) { ret = "acc_dec_draw      "; } else
	if(opc == 0x9A) { ret = "acc_decimal_draw  "; } else
	if(opc == 0xA0) { ret = "printf_libB       "; } else
                      ret = form("cmd%02X             ", opc);
	return ret;
}

static arg(opcea, argea, type, idx) {
	auto ret = "", tmp0, tmp1, tmp2, tmp3;
	if(type == ARG_BYTE) {
		tmp0 = Byte(argea);
		ret = form("$%02X",tmp0);
	} else if(type == ARG_WORD) {
		tmp0 = Word(argea);
		ret = form("$%04X",tmp0);
	} else if(type == ARG_SCRA) {
		tmp0 = Byte(argea);
		ret = form("SA_%02X",tmp0);
	} else if(type == ARG_SCRB) {
		tmp0 = Byte(argea);
		ret = form("SB_%02X",tmp0);
	} else if(type == ARG_OFS) {
		tmp0 = Word(argea) | (opcea & 0x00FF0000);
		add_dref(opcea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	} else if(type == ARG_MEM) {
		tmp0 = Word(argea) | 0x007E0000;
		add_dref(opcea, tmp0, dr_O|XREF_USER);
		Wait();
		ret = Name(tmp0);
		Wait();
	} else if(type == ARG_PARAM) {
		ret = "P[";
		tmp2 = Byte(argea);
		argea++;
		for(tmp3 = 0; tmp3 < idx; tmp3++) {
			tmp1 = tmp2 & 3;
			if(tmp1 == 0) {
				tmp0 = Word(argea) | 0x007E0000;
				add_dref(opcea, tmp0, dr_O|XREF_USER);
				Wait();
				ret = ret + Name(tmp0);
				Wait();
				argea = argea + 2;
			} else if(tmp1 == 1) {
				tmp0 = Byte(argea);
				ret = ret + form("SA%02X",tmp0);
				argea++;
			} else if(tmp1 == 2) {
				tmp0 = Byte(argea);
				ret = ret + form("SB%02X",tmp0);
				argea++;
			} else if(tmp1 == 3) {
				tmp0 = Word(argea);
				ret = ret + form("$%04X",tmp0);
				argea = argea + 2;
			}
			tmp2 = tmp2 >> 2;
			if(tmp3 != (idx - 1))
				ret = ret + ", ";
		}
		ret = ret + "]";
	}
	return ret;
}

static asize(argea, type, idx) {
	auto ret = 0, tmp0, tmp1, tmp2;
	if((type == ARG_BYTE)||(type == ARG_SCRA)||(type == ARG_SCRB)) {
		ret = 1;
	} else if((type == ARG_WORD)||(type == ARG_OFS)||(type == ARG_MEM)) {
		ret = 2;
	} else if(type == ARG_PARAM) {
		tmp2 = Byte(argea);
		ret = 1;
		for(tmp0 = 0; tmp0 < idx; tmp0++) {
			tmp1 = tmp2 & 3;
			if((tmp1 == 0)||(tmp1 == 3)) {
				ret = ret + 2;
			} else if((tmp1 == 1)||(tmp1 == 2)) {
				ret++;
			}
			tmp2 = tmp2 >> 2;
		}
	}
	return ret;
}

static opcode(ea, opc, args, size) {
	MakeUnknown(ea, size, DOUNK_SIMPLE);
	make_data_array(ea, size, "");
	SetManualInsn(ea, opc + args);
	return ea + size;
}

static league_decompile_opcode(ea, ret) {
	auto tmp0, tmp1, stop = 0;
	auto c = Byte(ea);
	auto opcname = league_get_opc_name(c), opcargs = "", opcsize = 0;
	if((c==0x00)||(c==0x01)||(c==0x04)||(c==0x05)||(c==0x09)||(c==0x0C)||(c==0x12)||(c==0x13)||(c==0x14)||(c==0x15)||(c==0x16)||(c==0x1B)||(c==0x44)||(c==0x45)||(c==0x46)||(c==0x47)||(c==0x5C)||(c==0x79)||(c==0x7D)||(c==0x81)||(c==0x82)||(c==0x86)||(c==0x8A)||(c==0x8C)||(c==0x8D)||(c==0x8E)||(c==0x8F)||(c==0x90)||(c==0x91)||(c==0x94)||(c==0x95)||(c==0x96)||(c==0x97)||(c==0x98)||(c==0x99)||(c==0x9A)||(c==0x9B)||(c==0x9C)||(c==0x9D)||(c==0x9E)||(c==0xA0)||(c==0xA1)) {	// no args
		opcargs = "";
		opcsize = 0;
//		if((c==0x04)||(c==0x81))
//			stop = 1;
	} else if((c == 0x0F)||(c == 0x10)||(c == 0x11)||(c == 0x29)||(c == 0x2C)||(c == 0x2D)||(c == 0x30)||(c == 0x31)||(c == 0x48)||(c == 0x53)||(c == 0x54)||(c == 0x55)||(c == 0x56)||(c == 0x68)||(c==0x6C)||(c==0x6D)||(c==0x6E)||(c==0x6F)||(c==0x70)||(c == 0x75)||(c == 0x7F)) { // byte arg
		opcargs = arg(ea, ea + 1, ARG_BYTE, -1);
		opcsize = asize(ea + 1, ARG_BYTE, -1);
	} else if((c == 0x06)||(c == 0x07)||(c == 0x08)||(c == 0x0D)||(c == 0x0E)) { // byte arg stop byte
		opcargs = "";
		opcsize = 0;
		stop = 1;
	} else if((c == 0x18)||(c == 0x1D)||(c == 0x20)||(c == 0x24)||(c == 0x28)||(c == 0x36)||(c == 0x3A)||(c == 0x4A)||(c == 0x6A)) { // script refA
		opcargs = arg(ea, ea + 1, ARG_SCRA, -1);
		opcsize = asize(ea + 1, ARG_SCRA, -1);
	} else if((c == 0x19)||(c == 0x1E)||(c == 0x21)||(c == 0x25)||(c == 0x37)||(c == 0x3B)||(c == 0x4B)||(c == 0x6B)) { // script refB
		opcargs = arg(ea, ea + 1, ARG_SCRB, -1);
		opcsize = asize(ea + 1, ARG_SCRB, -1);
	} else if((c == 0x1A)||(c == 0x22)||(c == 0x26)||(c == 0x27)||(c == 0x2A)||(c == 0x2E)||(c == 0x32)||(c == 0x38)||(c == 0x3C)||(c == 0x4C)||(c == 0x67)||(c == 0x57)||(c == 0x58)||(c == 0x59)||(c == 0x5D)||(c == 0x7B)||(c == 0x7E)) { // word immediate
		opcargs = arg(ea, ea + 1, ARG_WORD, -1);
		opcsize = asize(ea + 1, ARG_WORD, -1);
	} else if((c == 0x5A)) { // word ofs args
		opcargs = arg(ea, ea + 1, ARG_WORD, -1);
		opcsize = asize(ea + 1, ARG_WORD, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 1 + opcsize, ARG_OFS, -1);
		opcsize = opcsize + asize(ea + 1 + opcsize, ARG_OFS, -1);
	} else if((c == 0x73)||(c == 0x83)||(c == 0x84)) { // word word args
		opcargs = arg(ea, ea + 1, ARG_WORD, -1);
		opcsize = asize(ea + 1, ARG_WORD, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 1 + opcsize, ARG_WORD, -1);
		opcsize = opcsize + asize(ea + 1 + opcsize, ARG_WORD, -1);
	} else if((c==0x17)||(c==0x1C)||(c==0x1F)||(c==0x23)||(c==0x2B)||(c==0x2F)||(c==0x35)||(c==0x39)||(c==0x49)) { // mem offset
		opcargs = arg(ea, ea + 1, ARG_MEM, -1);
		opcsize = asize(ea + 1, ARG_MEM, -1);
	} else if((c == 0x5B)) { // special case
		if (Byte(ea - 3) == 0x1A) {
			tmp0 = Word(ea - 2) | (Word(ea + 1) << 16); // HACKY HACKY
			add_dref(ea, tmp0, dr_O|XREF_USER);
			Wait();
			opcargs = Name(tmp0);
			Wait();
			opcsize = 2;
		} else {
			opcargs = arg(ea, ea + 1, ARG_WORD, -1);
			opcsize = asize(ea + 1, ARG_WORD, -1);
		}
	} else if((c == 0x02)||(c == 0x03)||(c == 0x41)||(c == 0x4D)||(c == 0x4E)||(c == 0x4F)||(c == 0x50)||(c == 0x51)||(c == 0x52)||(c == 0x7A)||(c == 0x7B)||(c == 0x8B)) { // rom offset
		opcargs = arg(ea, ea + 1, ARG_OFS, -1);
		opcsize = asize(ea + 1, ARG_OFS, -1);
	} else if((c == 0x3D)||(c == 0x3E)||(c == 0x3F)||(c == 0x40)||(c == 0x77)||(c == 0x80)||(c == 0x87)||(c == 0x88)||(c == 0x89)||(c == 0x92)||(c == 0x93)||(c == 0x9F)) { // 2 params
		opcargs = arg(ea, ea + 1, ARG_PARAM, 2);
		opcsize = asize(ea + 1, ARG_PARAM, 2);
	} else if((c == 0x0A)) { // 3 params
		opcargs = arg(ea, ea + 1, ARG_PARAM, 3);
		opcsize = asize(ea + 1, ARG_PARAM, 3);
	} else if((c == 0x33)||(c == 0x34)||(c == 0x74)) { // byte params 2 byte
		opcargs = arg(ea, ea + 1 + opcsize, ARG_PARAM, 2);
		opcsize = asize(ea + 1 + opcsize, ARG_PARAM, 2);
		opcargs = opcargs + ", " + arg(ea, ea + 1 + opcsize, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 1 + opcsize, ARG_BYTE, -1);
	} else if((c == 0x42)||(c == 0x43)) { // byte byte params 4 byte param 1
		opcargs = arg(ea, ea + 1, ARG_BYTE, -1);
		opcsize = asize(ea + 1, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 1 + opcsize, ARG_PARAM, 4);
		opcsize = opcsize + asize(ea + 1 + opcsize, ARG_PARAM, 4);
		opcargs = opcargs + ", " + arg(ea, ea + 1 + opcsize, ARG_PARAM, 1);
		opcsize = opcsize + asize(ea + 1 + opcsize, ARG_PARAM, 1);
	} else if((c == 0x0B)||(c == 0x72)) { // byte, ofs
		opcargs = arg(ea, ea + 1, ARG_BYTE, -1);
		opcsize = asize(ea + 1, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 2, ARG_OFS, -1);
		opcsize = opcsize + asize(ea + 2, ARG_OFS, -1);
	} else if((c == 0x64)||(c == 0x69)) { // word, byte args
		opcargs = arg(ea, ea + 1, ARG_MEM, -1);
		opcsize = asize(ea + 1, ARG_MEM, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 3, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 3, ARG_BYTE, -1);
	} else if((c == 0x85)) { // ofs, word args
		opcargs = arg(ea, ea + 1, ARG_OFS, -1);
		opcsize = asize(ea + 1, ARG_OFS, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 3, ARG_WORD, -1);
		opcsize = opcsize + asize(ea + 3, ARG_WORD, -1);
	} else if((c == 0x71)||(c == 0x65)||(c == 0x66)) { // byte byte
		opcargs = arg(ea, ea + 1, ARG_BYTE, -1);
		opcsize = asize(ea + 1, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 2, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 2, ARG_BYTE, -1);
	} else if((c == 0x78)||(c == 0x7C)) { // byte, byte, byte, byte args
		opcargs = arg(ea, ea + 1, ARG_BYTE, -1);
		opcsize = asize(ea + 1, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 2, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 2, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 3, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 3, ARG_BYTE, -1);
		opcargs = opcargs + ", " + arg(ea, ea + 4, ARG_BYTE, -1);
		opcsize = opcsize + asize(ea + 4, ARG_BYTE, -1);
	} else {
		Message("unknown opcode %02X at 0x%08X!\n", c, ea);
		stop = 2;
	}
	if(stop != 2)
		tmp0 = opcode(ea, opcname, opcargs, opcsize + 1);
	if(stop == 0) {
		ea = tmp0;
	} else ea = -1;
	return ea;
}

static league_script_selection(void) {
	Jump(league_decompile_opcode(ScreenEA(), 0));
}

static league_script_auto(void) {
	auto ea;
	ea = 0x838457;
	while((ea < 0x839977) && (ea != -1)) {
		ea = league_decompile_opcode(ea, 0);
	}
	ea = 0x94FCA9;
	while((ea < 0x94FDAF && (ea != -1))) {
		ea = league_decompile_opcode(ea, 0);
	}
}

static main(void) {
	DelHotkey("Shift-O");
	AddHotkey("Shift-O", "league_script_selection");

//	league_script_auto();
}
