#include <idc.idc>
#include <functions.idc>

// early ARC SYSTEM WORKS engine?
//
// == known games with the same engine (sequence tables may be different though!) ==
//
// All-Pro Basketball / Zenbei!! Pro Basket
// Amagon / Totsuzen! Machoman
// Batsu & Terii
// Chuugoku Senseijutsu
// Daisenryaku
// Dokuganryuu Masamune
// Flying Hero
// Hoops / Moero!! Junior Basket - Two on Two
// Seiryaku Simulation - Inbou no Wakusei - Shancara
// Taito Basketball / Ultimate Basketball
// Takeshi no Sengoku Fuuunji
//
// == same engine and script language, but different data format ==
//
// Meiji Ishin (different track header)
//
// == same same data format but little bit different script commands (E1/E3) ==
//
// Chitei Senkuu Vazolder / WURM - Journey to the Center of the Earth
//  also here are many unreferenced SE tracks at:
// 	0x10976
//	0x1098D
//	0x109B0
//	0x109D3
//	0x109E6
//	0x109F7
//	0x10A1A
//	0x10A28
//	0x10AEA
//	0x10AFC
//	0x10B1D
//	0x10B2F
//	0x10B3D
//	0x10B66
//	0x10B8B
//	0x10B9F
//	0x10BB9
//	0x10BCB
//  these tracks are from Amagon / Totsuzen! Machoman where they are used, but since
//  the script language has changed, some of tunes does not play or sounds differently.
//
// == known games with engines based on this but slightly modified ==
//
// Armadillo
// Battle Baseball
// Chiyonofuji no Ooichou
// Columbus - Ougon no Yoake
// Great Battle Cyber
// Hissatsu Shigoto Nin
// Kyouryuu Sentai Zyuranger
// Mappy Kids
// Pizza Pop!
// Rolling Thunder
// SD Sengoku Bushou Retsuden: Rekka no Gotoku Tenka o Tore!
// Shufflepuck Cafe
// Times of Lore
//

// ----------------------------
// TAKESHI NO SENGOKU (TAITO) sound script parser
// ----------------------------

static take_snd_script_opcode_name(cmd) {
	auto ret = "";
	if(cmd == 0xE0) 		ret = "NOP";
	else if(cmd == 0xE1) 	ret = "LOAD   _v2, %02x";
	else if(cmd == 0xE2) 	ret = "LOAD   _v8, %02x";
	else if(cmd == 0xE3) 	ret = "STOP   %02x";
	else if(cmd == 0xE4) 	ret = "LOAD   _v5, %02x";
	else if(cmd == 0xE5) 	ret = "JMP    %s";
	else if(cmd == 0xE6) 	ret = "ADD    _v3, %02x";
	else if(cmd == 0xE7) 	ret = "LOOP   _v%x, %02x, %s";
	else if(cmd == 0xE8) 	ret = "SET    _v0.b5";
	else if(cmd == 0xE9) 	ret = "RES    _v0.b5";
	else if(cmd == 0xEA) 	ret = "SET    _v0.b3";
	else if(cmd == 0xEB) 	ret = "RES    _v0.b3";
	else if(cmd == 0xEC) 	ret = "JSR    %s";
	else if(cmd == 0xED) 	ret = "RTS";
//	else if(cmd == 0xEE) 	ret = "";
	else if(cmd == 0xEF) 	ret = "SET    _v0.b1";
	else if(cmd == 0xF0) 	ret = "RES    _v0.b1";
	else if(cmd == 0xF1) 	ret = "LOAD   _v4, %02x";
	else if(cmd == 0xF2) 	ret = "LOAD   _vN, %02x";
	else if(cmd == 0xF3)	ret = "LOAD   %02x, %02x, %02x";	// used in other games
	return ret;
}

static get_offset_name(ea, bank) {
	auto tmp0,tmp1;
	tmp0 = Word(ea);
	tmp0 = tmp0 + MK_FP(AskSelector(bank + 1), 0);
	tmp1 = Name(tmp0);
	if(tmp1=="") tmp1=form("0x%08X",tmp0);
	return tmp1;
}

static get_address_name(ea, bank) {
	auto tmp0,tmp1;
	tmp0 = ea + MK_FP(AskSelector(bank + 1), 0);
	tmp1 = Name(tmp0);
	if(tmp1=="") tmp1=form("0x%08X",tmp0);
	return tmp1;
}

static take_snd_script_exec_cmd(ea) {
	auto cmd, stop = 0;
	auto jmp_ptr, jmp_base, tmpname, tmparg;
	auto seg = GetReg(ea,"ds") - 1;
	cmd = Byte(ea);
	if(cmd < 0xE0) {
		ea = make_data_array(ea,1,"data0");
	} else {
		if((cmd==0xED)) {// RTS
			ea = make_data_array(ea,1,take_snd_script_opcode_name(cmd));
			stop = 1;
		} else if((cmd == 0xE0)||(cmd == 0xE8)||(cmd == 0xE9)||(cmd == 0xEA)||(cmd == 0xEB)||(cmd == 0xEF)||(cmd == 0xF0)) {// no args
			ea = make_data_array(ea,1,take_snd_script_opcode_name(cmd));
		} else if((cmd == 0xE3)) {	// STOP
			tmparg = Byte(ea + 1);
			ea = make_data_array(ea,2,form(take_snd_script_opcode_name(cmd),tmparg));
			stop = 1;
		} else if((cmd == 0xE1)||(cmd == 0xE2)||(cmd == 0xE4)||(cmd == 0xE6)||(cmd == 0xF1)||(cmd == 0xF2)) {	// 1 byte arg
			tmparg = Byte(ea + 1);
			ea = make_data_array(ea,2,form(take_snd_script_opcode_name(cmd),tmparg));
		} else if((cmd == 0xF3)) {
			tmparg = Byte(ea + 1);
			auto tmpa0 = Byte(ea + 2);
			auto tmpa1 = Byte(ea + 3);
			ea = make_data_array(ea,4,form(take_snd_script_opcode_name(cmd),tmparg, tmpa0, tmpa1));
		} else if((cmd == 0xE7)) {	// LOOP
			tmparg = Byte(ea + 1);
			auto tmparg1 = Byte(ea + 2);
			make_name(ea + 3, seg, "_apu_loop");
			tmpname = get_offset_name(ea + 3, seg);
			ea = make_data_array(ea,3,form(take_snd_script_opcode_name(cmd),tmparg,tmparg1,tmpname));
			ea = make_offset_ex(ea,seg,0,1);
		} else if((cmd == 0xE5)) {	// JMP
			jmp_ptr = Word(ea + 1);
			jmp_base = MK_FP(AskSelector(seg + 1), 0);
			tmpname = get_offset_name(ea + 1, seg);
			ea = make_data_array(ea,1,form(take_snd_script_opcode_name(cmd),tmpname));
			ea = make_offset_ex(ea,seg,0,1);
			if((jmp_base + jmp_ptr) > ea)
				ea = jmp_base + jmp_ptr;
			else
				stop = 1;
		} else if((cmd == 0xEC)) {	// JSR
			jmp_ptr = Word(ea + 1);
			jmp_base = MK_FP(AskSelector(seg + 1), 0);
			make_name(ea + 1, seg, "_apu_jsr");
			tmpname = get_offset_name(ea + 1, seg);
			ea = make_data_array(ea,1,form(take_snd_script_opcode_name(cmd),tmpname));
			ea = make_offset_ex(ea,seg,0,1);
			take_snd_script_exec(jmp_base + jmp_ptr);
		} else {
			Message(" unk_cmd at 0x%08x\n",ea);
			stop = 1;
		}
	}
	return ea | (stop << 31);
}

static take_snd_script_exec(ea) {
	auto stop = 0;
	do {
		stop = take_snd_script_exec_cmd(ea);
		ea = stop & 0x7FFFFFFF;
		stop = stop >> 31;
	} while (!stop);
	return ea;
}


static take_snd_lib_parse(void) {
	auto ea = ScreenEA();
	auto i, ptr_ea, ptr_ofs;
	auto seg = GetReg(ea,"ds") - 1;
	auto base = MK_FP(AskSelector(seg + 1), 0);
	if(ea != BADADDR) {
//		ptr_ea = Word(ea) + base;	// for ptr table
//		auto tmpname = get_offset_name(ea, seg);
		ptr_ea = ea;				// for RAW
		auto tmpname = get_address_name(ea, seg);
		auto cnt = Byte(ptr_ea);
		ptr_ea = make_data_array(ptr_ea,1,"");
		auto chnl = 0;
		while (chnl < cnt) {
			ptr_ea = make_data_array(ptr_ea,3,"");
			ptr_ofs = Word(ptr_ea)+base;
			auto new_name = form("_%s_ch%d",tmpname,chnl);
			MakeName(ptr_ofs,new_name);
			take_snd_script_exec(ptr_ofs);
			ptr_ea = make_offset_ex(ptr_ea,seg,0,1);
			ptr_ea = make_data_array(ptr_ea,4,"");
			chnl++;
		};
	}
	Jump(ea + 2);
}

static take_snd_script_parse(void) {
	auto ea = ScreenEA();
	ea = take_snd_script_exec_cmd(ea);
	Jump(ea);
}

static main(void) {
	AddHotkey("Shift-O", "take_snd_script_parse");
	AddHotkey("Shift-L", "take_snd_lib_parse");
}
