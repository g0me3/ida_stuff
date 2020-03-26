#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// NINJA GAIDEN CUTSCENE SCRIPT
// ---------------------------------

#define _ORIGINAL	1
#define _POOL_HACK	2

//#define MODE	_POOL_HACK
#define MODE	_ORIGINAL

static make_offset_custom(ea, exec) {
	auto ofs = Word(ea), bank = GetReg(ea,"ds")-1;
	if(ofs<0x800)
		ea = make_offset_ex(ea, 0, exec, 1);
	else if(ofs>=0xC000) {
		ea = make_offset_ex(ea, 7, exec, 1);
	} else {
#if MODE==_ORIGINAL
		if((bank==7)&&(ofs<0xC000)) {
#else
		if((bank==0x1F)&&(ofs<0xC000)) {
#endif
			ea = make_offset_ex(ea, AskLong(0, "Enter Bank Nunber"), exec, 1);
		} else
			ea = make_offset_ex(ea, bank, exec, 1);
	}
	return ea;
}

static ng_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0x01) {
		ret = "NT_INIT    ";		// no args
	} else if(cmd == 0x02) {
		ret = "WAIT_FOR_NMI";		// no args
	} else if(cmd == 0x03) {		// arg = 0, reset split params, arg > 0 load data
		ret = "SPLIT_LOAD ";		// 1b arg
	} else if(cmd == 0x04) {
		ret = "PAL_FADE   ";		// 1b arg
	} else if(cmd == 0x05) {
		ret = "PPU_MODE   ";		// 1b arg
	} else if(cmd == 0x06) {
		ret = "APU_LOAD   ";		// 1b arg
	} else if(cmd == 0x07) {
		ret = "TLM_RAW    ";		// ofs, 2b args
	} else if(cmd == 0x08) {		// arg & $80, set _cut_split_chr_bank1 = arg & $1f, else _chr_bank1 = arg,
		ret = "CHR_BANK   ";		// 1b arg
	} else if(cmd == 0x09) {
		ret = "SPR_ANIM   ";		// 2b arg
	} else if(cmd == 0x0A) {
		ret = "SPR_MODE   ";		// 2b arg
	} else if(cmd == 0x0B) {
		ret = "SPLIT_ANIM ";		// 1b arg
	} else if(cmd == 0x0C) {
		ret = "PAL_LOAD   ";		// 1b+n
	} else if(cmd == 0x0D) {
		ret = "SCROLL_INIT ";		// 1b arg
	} else if(cmd == 0x0E) {
		ret = "PAL_OFF    ";		// 1b arg
#if MODE==_POOL_HACK
	} else if(cmd == 0x10) {
		ret = "POOL_CMD10 ";		// 1b arg
	} else if(cmd == 0x11) {
		ret = "POOL_CMD11 ";		// 1b arg
	} else if(cmd == 0x12) {
		ret = "POOL_CMD12 ";		// 1b arg
	} else if(cmd == 0x13) {
		ret = "POOL_CMD13 ";		// 1b arg
	} else if(cmd == 0x14) {
		ret = "POOL_CMD14 ";		// 1b arg
	} else if(cmd == 0x15) {
		ret = "POOL_CMD15 ";		// 1b arg
#endif
	} else if(cmd == 0x40) {
		ret = "PPU_CLEAR  ";		// no args
	} else if((cmd > 0x40)&(cmd < 0x80)) {
   ret = form("TLM_LOAD   $%02X",cmd&0x3F);	// 4b+2*(cmd&$3F)
	} else if(cmd == 0x80) {
		ret = "SPR_RESET  ";			// no args
	} else if((cmd > 0x80)&(cmd < 0xC0)) {
   ret = form("SPR_LOAD    $%02X",cmd&0x3F);	// 4b+5*(cmd&$3F)
	} else if((cmd >= 0xC0)&(cmd < 0xFF)) {
   ret = form("MSG_INIT    $%02X,",cmd&0x3F);	// 1b arg
	} else if(cmd == 0xFF) {
		ret = "DELAY";
	} else {
		ret = form("UNK%02X",cmd);
	}
	return ret;
}

static ng_opcode(ea, header) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, stop;
	bank = GetReg(ea,"ds");

//	if(isCode(ea)) ea = BADADDR;

	if(header == 1) {
		MakeUnknown(ea, 2, DOUNK_SIMPLE);
		MakeWord(ea);
		MakeComm(ea, "");
		MakeComm(ea, form("DURATION   $%04X",Word(ea)));
		ea = ea + 2;
	}

	stop = 0;

	while(stop == 0) {
		if(ea != BADADDR) {
			cmd = Byte(ea);
			cmd_opc = ng_opcode_name(cmd);

			if((cmd==0xFF)) {									// stop
				ea = make_data_array(ea, 1, cmd_opc);
				if(Word(ea)==0xFFFF) {
					MakeUnknown(ea, 2, DOUNK_SIMPLE);
					MakeWord(ea);
					MakeComm(ea, "");
					MakeComm(ea, "STOP");
					ea = ea + 2;
					stop = 1;
				} else {
					MakeUnknown(ea, 2, DOUNK_SIMPLE);
					MakeWord(ea);
					MakeComm(ea, "");
					MakeComm(ea, form("DURATION   $%04X",Word(ea)));
					ea = ea + 2;
				}
			} else if((cmd==0x01)||(cmd==0x02)||(cmd==0x40)||(cmd==0x80)) {	// no args
				ea = make_data_array(ea, 1, cmd_opc);
			} else if((cmd==0x03)||(cmd==0x04)||(cmd==0x05)||(cmd==0x06)||(cmd==0x08)||(cmd==0x0B)||(cmd==0x0D)||(cmd==0x0E)||((cmd>=0xC0)&&(cmd<0xFF))) {	// 1b arg
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
#if MODE==_POOL_HACK
			} else if((cmd>=0x10)&&(cmd<=0x15)) {	// 1b arg pool hack
				ea = make_data_array(ea, 2, cmd_opc);
#endif
			} else if((cmd==0x09)||(cmd==0x0A)) {				// 2b arg
				ea = make_data_array(ea, 3, form("%s$%02X,$%02X",cmd_opc,Byte(ea+1),Byte(ea+2)));
			} else if(cmd==0x07) {								// ofs, 2b args
				tmp0 = Word(ea+1)+MK_FP(AskSelector(bank), 0);
				tmp1 = Name(tmp0);
				ea = make_data_array(ea, 1, form("%s$%04X,%s",cmd_opc,Word(ea+3),tmp1));
				ea = make_offset_custom(ea, 0); 				// no exec
				ea = make_data_array(ea, 2, "");
			} else if(cmd==0x0C) {								// 1b+n
				tmp0 = Byte(ea+1);
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,tmp0));
				tmp1=0;
				tmp2="";
				while(tmp1<(tmp0-1)) {
					tmp2=tmp2+form("$%02X,",Byte(ea+tmp1));
					tmp1++;
				}
				tmp2=tmp2+form("$%02X",Byte(ea+tmp1));
				ea = make_data_array(ea, tmp0&0x0F, form("    PAL    %s",tmp2));
			} else if((cmd>0x40)&&(cmd<0x80)) {	// 4b+2*(cmd&$3F)
				ea = make_data_array(ea, 1, cmd_opc);
				ea = make_data_array(ea, 4, form("    PAL    $%02X,$%02X,$%02X,$%02X",Byte(ea),Byte(ea+1),Byte(ea+2),Byte(ea+3)));
				tmp0 = 0;
				tmp1 = cmd&0x3F;
				while(tmp0<tmp1) {
					ea = make_data_array(ea, 2, form("    TLM    $%02X,$%02X",Byte(ea),Byte(ea+1)));
					tmp0++;
				}
			} else if((cmd>0x80)&&(cmd<0xC0)) {	// 4b+5*(cmd&$3F)
				ea = make_data_array(ea, 1, cmd_opc);
				ea = make_data_array(ea, 4, form("    PAL    $%02X,$%02X,$%02X,$%02X",Byte(ea),Byte(ea+1),Byte(ea+2),Byte(ea+3)));
				tmp0 = 0;
				tmp1 = cmd&0x3F;
				while(tmp0<tmp1) {
					ea = make_data_array(ea, 5, form("    SPR    $%02X,$%02X,$%02X,$%02X,$%02X",Byte(ea),Byte(ea+1),Byte(ea+2),Byte(ea+3),Byte(ea+4)));
					tmp0++;
				}
			} else {
				Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
				stop = 1;
			}
		}
	}
}

static ng_apu_name(cmd) {
	auto ret = "";
	if       (cmd == 0xE0) {ret = "AWAV   ";
	} else if(cmd == 0xE1) {ret = "ANOP";
	} else if(cmd == 0xE8) {ret = "AJMP   ";
	} else if(cmd == 0xE9) {ret = "AJSR   ";
	} else if(cmd == 0xEA) {ret = "ARET";
	} else if(cmd == 0xEB) {ret = "ALOOP_BEGIN ";
	} else if(cmd == 0xEC) {ret = "ALOOP_END";
	} else if(cmd == 0xF8) {ret = "ADPCM_ALLOW";
	} else if(cmd == 0xF9) {ret = "ADPCM_FORBID";
	} else if(cmd == 0xFA) {ret = "ADPCMA ";
	} else if(cmd == 0xFB) {ret = "ADPCMB ";
	} else if(cmd == 0xFF) {ret = "ASTOP";
	} else if(cmd <  0xE0) {
		ret = form("ALEN   $%02X",cmd&0x7F);
	} else {
		ret = form("ACMD%02X  ",cmd);
	}
	return ret;
}

static ng_apu(ea) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, jmp_ptr, stop = 0, tbl_ea;
	bank = GetReg(ea,"ds");
	tmp2 = ea;
	do {
		if(ea != BADADDR) {
			tmp0 = 0;
			tmp1 = ea;
			tmp2 = "";
			while(((cmd=Byte(ea))<0x80)&&(Byte(ea+1)<0x80)) {
				tmp0++;
				if(tmp0==0x10) {
					tmp2 = tmp2+form("$%02X",cmd);
					ea = make_data_array(tmp1, 0x10, form("NOTES  %s",tmp2));
					tmp2 = "";
					tmp1 = ea;
					tmp0 = 0;
				} else {
					tmp2 = tmp2+form("$%02X,",cmd);
					ea++;
				}
			}
			if(cmd<0x80) {
				tmp0++;
				if(tmp0==0x10) {
					tmp2 = tmp2+form("$%02X",cmd);
					ea = make_data_array(tmp1, 0x10, form("NOTES  %s",tmp2));
					tmp2 = "";
					tmp1 = ea;
					tmp0 = 0;
				} else {
					tmp2 = tmp2+form("$%02X",cmd);
					ea++;
				}
			}
			if(tmp0>0) {
				ea = make_data_array(tmp1, tmp0, form("NOTES  %s",tmp2));
				cmd = Byte(ea);
			}
//			Message(" cmd == %04x\n", cmd);
			cmd_opc = ng_apu_name(cmd);
			if (cmd<0xE0) {
				if(bank==8) {
					tbl_ea = 0xB0870;
					ea = make_data_array(ea, 1, form("POOL_%s ; $%02X",cmd_opc,Byte(tbl_ea+(cmd&0x7F))));
				} else {
					tbl_ea = 0x50586;
					ea = make_data_array(ea, 1, form("%s ; $%02X",cmd_opc,Byte(tbl_ea+(cmd&0x3F))));
				}
			} else if((cmd == 0xEA)||(cmd == 0xFF)) {	// RET/STOP
				ea = make_data_array(ea, 1, cmd_opc);
				stop = 1;
				// stop here
			} else if((cmd==0xE1)||(cmd==0xEC)||(cmd==0xED)||(cmd==0xEF)||(cmd==0xF8)||(cmd==0xF9)) {	// no args
				ea = make_data_array(ea, 1, cmd_opc);
			} else if((cmd==0xE0)||(cmd==0xE2)||(cmd==0xE3)||(cmd==0xE4)||(cmd==0xE5)||(cmd==0xEB)||(cmd==0xFE)) {	// 1b arg
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
			} else if(cmd==0xE8) {	// ofs
				jmp_ptr = Word(ea+1)+MK_FP(AskSelector(bank), 0);
				if(strstr(Name(jmp_ptr),"_apu_mus")==-1)
					MakeNameEx(jmp_ptr,form("_aloop_%X",jmp_ptr),SN_CHECK|SN_NOWARN);
				tmp0 = Name(jmp_ptr);
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp0));
				ea = make_offset_custom(ea, 0); // no exec
				if(jmp_ptr>ea)
					ng_apu(jmp_ptr);
				else
					stop = 1;
				// stop here
			} else if(cmd==0xE9) {	// ofs
				jmp_ptr = Word(ea+1)+MK_FP(AskSelector(bank), 0);
				MakeNameEx(jmp_ptr,form("_asub_%X",jmp_ptr),SN_CHECK|SN_NOWARN);
				tmp0 = Name(jmp_ptr);
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp0));
				ea = make_offset_custom(ea, 0); // no exec
				ng_apu(jmp_ptr);
			} else if((cmd==0xFA)||(cmd==0xFB)) {	// 3b arg
				if(bank==8)
					ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
				else
					ea = make_data_array(ea, 4, form("%s$%02X,$%02X,$%02X",cmd_opc,Byte(ea+1),Byte(ea+2),Byte(ea+3)));
			} else {
				Message(" unknown apu opcode at 0x%08x = %02x\n", ea, cmd);
				stop = 1;
			}
		}
	} while (!stop);
	return ea;
}

static ng_script_selection(void) {
	ng_opcode(ScreenEA(),0);
}

static ng_apu_selection(void) {
	ng_apu(ScreenEA());
}

static ng_apu_table(void) {
	auto start_ea = 0x5077d;
	auto bank = GetReg(start_ea,"ds"), ofs, idx;
	auto mus_ea, chnl_ea, i = 0, j, name;

	do {
		ofs = Word(start_ea+(i<<1));
		if(ofs&0x4000) {
			mus_ea = (ofs&0xBFFF)+MK_FP(AskSelector(7 + 1), 0);
		} else {
			mus_ea = ofs+MK_FP(AskSelector(bank), 0);
		}
		j = 0;

//		name = form("_apu_mus%02X",i+1);
//		Message("idx %02x old name '%s', new name '%s'\n",i,Name(mus_ea),name);
//		MakeNameEx(mus_ea,name,SN_CHECK|SN_NOWARN);
		name = Name(mus_ea);
		while ((idx = Byte(mus_ea+j))!=0xFF) {
			make_data_array(mus_ea+j, 1, "");
			j=j+1;
			ofs = Word(mus_ea+j);
			if(ofs&0x4000) {
				chnl_ea = (ofs&0xBFFF)+MK_FP(AskSelector(7 + 1), 0);
			} else {
				make_offset_custom(mus_ea+j, 0); // no exec
				chnl_ea = ofs+MK_FP(AskSelector(bank), 0);
			}
			MakeNameEx(chnl_ea,form("%s_%c",name,(j/3)+'A'),SN_CHECK|SN_NOWARN);
			ng_apu(chnl_ea);
			j=j+2;
		}
		make_data_array(mus_ea+j, 1, "");
		i=i+1;
	} while (i<0x55);
}

static pool_ofs_tbl_restore(tbl_ea) {
	auto banks_ea = 0x20000, ea;
	auto ofs, bank, i, delta, base;
	i=0;
	while(i<64) {
		bank = Byte(banks_ea+i);
		ea = tbl_ea+(i<<1);
		ofs = Word(ea);
		if(bank&1)
			delta = 0;
		else
			delta = 0x2000;
		bank = bank>>1;
		base = MK_FP(AskSelector(bank + 1), 0);
		OpOffEx(ea, 0, REF_OFF32, -1, base, delta);
		i++;
	}
}

static main(void) {

	ng_apu_table();
//	garbage_collector();

//#if MODE==_POOL_HACK
//	pool_ofs_tbl_restore(0x20040);
//	pool_ofs_tbl_restore(0x200C0);
//	pool_ofs_tbl_restore(0x20140);
//#endif

///*
#if MODE==_POOL_HACK
// POOL HACK
	ng_opcode(0x6B5E5,1);
	ng_opcode(0x6B5E5,1);
	ng_opcode(0x6A890,1);
	ng_opcode(0x6BDD6,1);
	ng_opcode(0x6A340,1);
	ng_opcode(0x6A380,1);
	ng_opcode(0x6B8C0,1);
	ng_opcode(0x68F06,1);
	ng_opcode(0x68FA2,1);	// 106.6 ver
#else
// NINJA GAIDEN
	ng_opcode(0x6A78F,1);
	ng_opcode(0x6A7BB,1);
	ng_opcode(0x68EFC,1);

//	ng_opcode(0x9A2A2,0);	// unused copy
//	ng_opcode(0x9A78F,1);
//	ng_opcode(0x9A7BB,1);
#endif

//* COMMON
	ng_opcode(0x691D7,1);
	ng_opcode(0x693B1,1);
	ng_opcode(0x69606,1);
	ng_opcode(0x699E7,1);
	ng_opcode(0x69A21,1);
	ng_opcode(0x69C40,1);
	ng_opcode(0x69CE8,1);
	ng_opcode(0x69D52,1);
	ng_opcode(0x69F5B,1);
	ng_opcode(0x6A14F,1);
	ng_opcode(0x6A254,1);
//*/

//	AddHotkey("Shift-O", "ng_script_selection");
	AddHotkey("Shift-O", "ng_apu_selection");
}
