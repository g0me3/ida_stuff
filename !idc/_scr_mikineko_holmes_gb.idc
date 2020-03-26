#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// MIKINEKO HOLMES GB SCRIPTS
// ---------------------------------

static make_offset_customW(ea) {
	auto base_ea = 0x3980, ofs, bank, base;
	MakeUnknown(ea, 2, DOUNK_SIMPLE);
	MakeData(ea, FF_WORD, 1, 0);
	ofs = base_ea + Word(ea);
	bank = ofs / 0x4000;
	base = MK_FP(AskSelector(bank), 0);
	if(bank>0)
		OpOffEx(ea, 0, REF_OFF32, -1, base, (0x4000 * (bank - 1)) - base_ea);
	else
		OpOffEx(ea, 0, REF_OFF32, -1, base, - base_ea);
	MakeComm(ea, "");
	return ea + 2;
}

static get_offset_custom(ea, mode) {
	auto base_ea = 0x3980, ofs, bank, base, result_ea, name;
	if (mode==1)
		ofs = Word(ea) + (Byte(ea + 2)<<16);
	else if(mode==0)
		ofs = base_ea + Word(ea);
	bank = ofs / 0x4000;
	base = MK_FP(AskSelector(bank), 0);
	if(bank>0)
		result_ea = base + 0x4000 + (ofs-(bank * 0x4000));
	else
		result_ea = base + ofs;
	if(mode==1) {
		add_dref(ea,result_ea,dr_O|XREF_USER);
		Wait();
	}
	name = Name(result_ea);
	if(name=="")
		name = form("0x%08X",result_ea);
	return name;
}

static mneko_opcode_name(cmd) {
	auto ret = "", mask = cmd & 0xF0, tmp0;
	if(cmd == 0x00) {
		ret = "STOP";
	} else {
		if(cmd&0x80) {
			if(mask == 0xF0) {
				tmp0 = cmd&0xF;
				if((tmp0>=0)&&(tmp0<=7)) {
					ret = "MOVI      A,";
				} else if((tmp0==9)) {
					ret = "MOVS8     A,";
				} else if((tmp0==0xA)) {
					ret = "MOVU16    A,";
				} else if((tmp0==0xB)) {
					ret = "MOVU24    A,";
				} else if((tmp0==0xD)) {
					ret = "TEST      FLAG,";
				} else if((tmp0==0xE)) {
					ret = "MOVA8     VAR8,";
				} else if((tmp0==0xD)) {
					ret = "MOVA16    VAR16,";
				} else {
					ret = form("CMD%02X     ",cmd);
				}
			} else if (mask == 0xE0) {
				if((cmd&3)==1) {
					ret = "POPATEST  A,";
				} else if((cmd&3)==2) {
					ret = "POPA      VAR8,";
				} else if((cmd&3)==3) {
					ret = "POPA      VAR16,";
				} else {
					ret = form("CMD%02X     ",cmd);
				}
			} else if (mask == 0xD0) {
				ret = form("CMD%02X     ",cmd);
			} else {
				if (cmd == 0x81) {
					ret = "ADDW      A,STACK";
				} else if(cmd == 0x82) {
					ret = "SUBW      A,STACK";
				} else if(cmd == 0x86) {
					ret = "ANDW      A,STACK";
				} else if((cmd == 0x88)||(cmd == 0x8F)) {
					ret = "ORW       A,STACK";
				} else if((cmd == 0x89)||(cmd == 0x90)) {
					ret = "CMPGT     A,STACK";
				} else if(cmd == 0x8A) {
					ret = "CMPLE     A,STACK";
				} else if(cmd == 0x91) {
					ret = "TEST      STACK";
				} else {
					ret = form("CMD%02X     ",cmd);
				}
			}
		} else {
			tmp0 = cmd&0x3F;
			if((tmp0==0x0F)) {
				ret = form("CMD%02X     ",cmd);
			} else if(tmp0==0x01) {
				ret = "JMP       ";
			} else if(tmp0==0x02) {
				ret = "BRAF      PARAM8,";
			} else if(tmp0==0x03) {
				ret = "BRAF      PARAM16,";
			} else if(tmp0==0x04) {
				ret = "JSR       ";
			} else if(tmp0==0x05) {
				ret = "RTS";
			} else if(tmp0==0x06) {
				ret = "PUSH      PARAMS";
			} else if(tmp0==0x0B) {
				ret = "SET       FLAG,";
			} else if(tmp0==0x0C) {
				ret = "CLEAR     FLAG,";
			} else if(tmp0==0x0A) {
				ret = "MSGI      ";
			} else if(tmp0==0x0E) {
				ret = "MSG       PARAM";
			} else if(tmp0==0x10) {
				ret = "CHR       PARAM";
			} else if(tmp0==0x14) {
				ret = "CLR       FLAGS,";
			} else if(tmp0==0x16) {
				ret = "MSGP      PARAM";
			} else if(tmp0==0x18) {
				ret = "APUS      ";
			} else if(tmp0==0x1A) {
				ret = "PASSPRINT ";
			} else if(tmp0==0x1B) {
				ret = "PASSINPUT ";
			} else if(tmp0==0x1D) {
				ret = "TITLE     ";
			} else {
				ret = form("CMD%02X     ",cmd);
			}
		}
	}
	return ret;
}

static mneko_opcode(ea) {
	auto cmd_opc = "", cmd, cmd_mask, tmp0, tmp1, tmp2;
	if(ea != BADADDR) {
//		Message(" start at ea = 0x%08x!\n", ea);
		cmd = Byte(ea);
		cmd_opc = mneko_opcode_name(cmd);
		cmd_mask = cmd & 0xF0;

		if(cmd == 0) {		// stop
			ea = make_data_array(ea, 1, cmd_opc);
		} else {
			if(cmd&0x80) {
				if(cmd_mask==0xF0) {
					tmp0=cmd&0xF;
					if((tmp0>=0)&&(tmp0<=7)) {
						ea = make_data_array(ea, 1, form("%s%1X",cmd_opc,cmd&7));
					} else if((tmp0==0xA)) {
						ea = make_data_array(ea, 3, form("%s0x%02x%02x",cmd_opc,Byte(ea+2),Byte(ea+1)));
//						ea = make_data_array(ea, 1, form("%s%s",cmd_opc,get_offset_custom(ea+1,0)));
//						ea = make_data_array(ea, 2, "");
					} else if((tmp0==0xB)) {
//						ea = make_data_array(ea, 1, form("%s0x%02x%02x%02x",cmd_opc,Byte(ea+3),Byte(ea+2),Byte(ea+1)));
						ea = make_data_array(ea, 4, form("%s%s",cmd_opc,get_offset_custom(ea+1,1)));
//						ea = make_data_array(ea, 3, "");
					} else if((tmp0==0xC)) {
						ea = make_data_array(ea, 1, cmd_opc);
					} else if((tmp0==9)||(tmp0==0xD)||(tmp0==0xE)||(tmp0==0xF)) {
						ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
					} else {
						Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
						ea = BADADDR;
					}
				} else if (cmd_mask == 0xE0) {
						ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
				} else if (cmd_mask == 0xD0) {
						ea = make_data_array(ea, 1, form("%s$%1X",cmd_opc,cmd&0xF));
				} else {
					if ((cmd == 0x81)||(cmd == 0x82)||(cmd == 0x86)||(cmd == 0x88)||(cmd == 0x89)||(cmd == 0x8A)||(cmd == 0x8F)||(cmd == 0x90)||(cmd == 0x91)) {
						ea = make_data_array(ea, 1, cmd_opc);
					} else {
						Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
						ea = BADADDR;
					}
				}
			} else {
				tmp0 = cmd&0x3F;
				if((tmp0==0x0F)||(tmp0==0x05)||(tmp0==0x06)||(tmp0==0x0A)||(tmp0==0x0E)||(tmp0==0x0D)||(tmp0==0x10)||(tmp0==0x11)||(tmp0==0x13)||(tmp0==0x16)||(tmp0==0x17)||(tmp0==0x18)||(tmp0==0x19)||(tmp0==0x1A)||(tmp0==0x1B)||(tmp0==0x1C)||(tmp0==0x1D)||(tmp0==0x20)||(tmp0==0x21)) {
					ea = make_data_array(ea, 1, cmd_opc);
				} else if((tmp0==0x0B)||(tmp0==0x0C)) {
					ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
				} else if((tmp0==0x12)) {
//						ea = make_data_array(ea, 1, form("%s0x%02x%02x%02x",cmd_opc,Byte(ea+3),Byte(ea+2),Byte(ea+1)));
						ea = make_data_array(ea, 1, form("%s%s",cmd_opc,get_offset_custom(ea+1,1)));
						ea = make_data_array(ea, 3, "");
				} else if((tmp0==0x14)) {
					ea = make_data_array(ea, 3, form("%s$%02X,$%02X",cmd_opc,Byte(ea+1),Byte(ea+2)));
				} else if((tmp0==0x01)||(tmp0==0x02)||(tmp0==0x03)||(tmp0==0x08)) {
//					ea = make_data_array(ea, 1, cmd_opc);
					ea = make_data_array(ea, 1, form("%s%s",cmd_opc,get_offset_custom(ea+1,0)));
					ea = make_offset_customW(ea);
				} else if((tmp0==0x04)||(tmp0==0x09)) {
//					ea = make_data_array(ea, 1, cmd_opc);
					ea = make_data_array(ea, 1, form("%s%s",cmd_opc,get_offset_custom(ea+1,0)));
					ea = make_offset_customW(ea);
				} else {
					Message(" unknown opcode at 0x%08x = %02x\n", ea, cmd);
					ea = BADADDR;
				}
			}
		}
		return ea;
	}
}

static mneko_script_selection(void) {
	Jump(mneko_opcode(ScreenEA()));
}

static mneko_script_range(start_ea, end_ea) {
	auto ea = start_ea;
	Message("auto decompile start... at 0x%08X\n",start_ea);
	while ((ea<end_ea)&&(ea!=BADADDR)) {ea = mneko_opcode(ea);}
	Message("auto decompile complete at 0x%08X\n",ea);
}

static main(void) {

	mneko_script_range(0x03980, 0x03FFE);
	mneko_script_range(0x14003, 0x17930);

	AddHotkey("Shift-M", "mneko_script_selection");
}
