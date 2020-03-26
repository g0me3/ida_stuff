#include <idc.idc>
#include <functions.idc>

// ---------------------------------
// NEW GHOSTBUSTERS II
// ---------------------------------

#define AUTO
//#define MANUAL
//#define VERBOSE1
//#define VERBOSE2
//#define VERBOSE3

#define REGION_US	01
#define REGION_EU	02
#define REGION_JP	03
#define KIRBY_US_0	10
#define UCHUBITAI	11

#define REGION REGION_JP
//#define REGION REGION_EU
//#define REGION REGION_US
//#define REGION KIRBY_US_0
//#define REGION UCHUBITAI

static ngb2_get_native_sub_args(addr) {
	auto ret = -1;
#if REGION==REGION_JP
	if	   (
			(addr==0x826F)||
			(addr==0xE61D)||
			(addr==0xE73D)||
			(addr==0xE85D)||
			(addr==0xE8D1)||
			(addr==0xEB1E)||
			(addr==0xEBB1)||
			(0)
			)					ret = 0;	// 2b args
	else if(
			(addr==0xEB7E)||
			(0)
			)					ret = 1;	// ofs, 1b args
	else if(
			(addr==0x853A)||
			(addr==0x8ADF)||
			(addr==0x92BB)||
			(addr==0x92CC)||
			(addr==0x92D8)||
			(addr==0x92E4)||
			(addr==0xE63C)||
			(addr==0xE661)||
			(addr==0xE683)||
			(addr==0xE691)||
			(addr==0xE6A4)||
			(addr==0xE6F1)||
			(addr==0xE710)||
			(addr==0xE75B)||
			(addr==0xE775)||
			(addr==0xE787)||
			(addr==0xE78D)||
			(addr==0xE879)||
			(addr==0xEAEC)||
			(addr==0xEB2A)||
			(addr==0xEB60)||
			(addr==0xEB68)||
			(addr==0xEBD0)||
			(0)

			)					ret = 2;	// 1b arg
	else if(
			(addr==0x91BF)||
			(addr==0xA31D)||
			(addr==0xE6CD)||
			(addr==0xE6D9)||
			(addr==0xE6E5)||
			(addr==0xE7EE)||
			(addr==0xEB70)||
			(addr==0xEAA7)||
			(addr==0xED12)||
			(0)
			)					ret = 3;	// ofs arg
	else if(
			(addr==0xE799)||
			(0)
			)					ret = 4;	// 5b args
	else if(
			(addr==0x80D2)||
			(addr==0x83E7)||
			(addr==0x8481)||
			(addr==0x890E)||
			(addr==0x8952)||
			(addr==0x8AF6)||
			(addr==0x8B1B)||
			(addr==0x8B4F)||
			(addr==0x8BAA)||
			(addr==0x8BC8)||
			(addr==0x8C5B)||
			(addr==0x8DDD)||
			(addr==0x8DE6)||
			(addr==0x8DF3)||
			(addr==0x8DFC)||
			(addr==0x8FAF)||
			(addr==0x8FB5)||
			(addr==0x8FC2)||
			(addr==0x8FED)||
			(addr==0x9025)||
			(addr==0x90E6)||
			(addr==0x9199)||
			(addr==0x919F)||
			(addr==0x91A6)||
			(addr==0x91A8)||
			(addr==0x91AF)||
			(addr==0x91B1)||
			(addr==0x91F2)||
			(addr==0x9215)||
			(addr==0x9229)||
			(addr==0x923D)||
			(addr==0x9257)||
			(addr==0x926C)||
			(addr==0x9282)||
			(addr==0x941F)||
			(addr==0x9474)||
			(addr==0x9492)||
			(addr==0x9498)||
			(addr==0x94CF)||
			(addr==0x94DA)||
			(addr==0x9848)||
			(addr==0x9A70)||
			(addr==0x9A7D)||
			(addr==0x9DA9)||
			(addr==0x9E3B)||
			(addr==0x9E4A)||
			(addr==0x9E67)||
			(addr==0x9F3D)||
			(addr==0xA036)||
			(addr==0xA196)||
			(addr==0xA1F3)||
			(addr==0xA213)||
			(addr==0xA242)||
			(addr==0xA316)||
			(addr==0xA33C)||
			(addr==0xA3A4)||
			(addr==0xA3FE)||
			(addr==0xA444)||
			(addr==0xA449)||
			(addr==0xA44F)||
			(addr==0xA4DE)||
			(addr==0xA4E7)||
			(addr==0xA53B)||
			(addr==0xA55A)||
			(addr==0xA583)||
			(addr==0xA602)||
			(addr==0xA60B)||
			(addr==0xA63E)||
			(addr==0xA649)||
			(addr==0xA67D)||
			(addr==0xA688)||
			(addr==0xA6C4)||
			(addr==0xA6CF)||
			(addr==0xA70B)||
			(addr==0xA736)||
			(addr==0xA741)||
			(addr==0xA74D)||
			(addr==0xA787)||
			(addr==0xA792)||
			(addr==0xA797)||
			(addr==0xA7A8)||
			(addr==0xA7AC)||
			(addr==0xA81A)||
			(addr==0xA823)||
			(addr==0xA855)||
			(addr==0xA85E)||
			(addr==0xA894)||
			(addr==0xA89F)||
			(addr==0xA913)||
			(addr==0xA91C)||
			(addr==0xA984)||
			(addr==0xB2B1)||
			(addr==0xBAF9)||
			(addr==0xBBF3)||
			(addr==0xC3A2)||
			(addr==0xC3A9)||
			(addr==0xC4CD)||
			(addr==0xC5E8)||
			(addr==0xC623)||
			(addr==0xCCE0)||
			(addr==0xCD27)||
			(addr==0xCEF1)||
			(addr==0xD0B9)||
			(addr==0xD347)||
			(addr==0xD3C5)||
			(addr==0xD3F1)||
			(addr==0xD3F7)||
			(addr==0xD3FC)||
			(addr==0xD41A)||
			(addr==0xD421)||
			(addr==0xD429)||
			(addr==0xDD7B)||
			(addr==0xE560)||
			(addr==0xE589)||
			(addr==0xE77B)||
			(addr==0xE780)||
			(addr==0xE7FB)||
			(addr==0xEAB6)||
			(addr==0xEABE)||
			(addr==0xEB40)||
			(addr==0xEB4F)||
			(addr==0xEB95)||
			(addr==0xEBA9)||
			(addr==0xEBE5)||
			(addr==0xEBFD)||
			(addr==0xEC0B)||
			(addr==0xEC1E)||
			(addr==0xEC39)||
			(addr==0xEC49)||
			(addr==0xEC7A)||
			(addr==0xECB0)||
			(addr==0xECBA)||
			(addr==0xECC4)||
			(addr==0xECD3)||
			(addr==0xECE8)||
			(addr==0xECF3)||
			(0)
			)					ret = 5;	// no args
	else if(
			(addr==0x8A9E)||
			(0)
			)					ret = 6;	// ofs, 2b args
	else if(
			(addr==0xE6B7)||
			(0)
			)					ret = 7;	// 1b, ofs args
	else if(
			(addr==0xE9CF)||
			(0)
			)					ret = 8;	// 1b + 3bxN args
	else if(
			(addr==0xE8FA)||
			(0)
			)					ret = 9;	// 3b args
	else if(
			(addr==0xE94B)||
			(0)
			)					ret = 10;	// 1b + 4bxN args
	else if(
			(addr==0xE885)||
			(0)
			)					ret = 11;	// 1b + 4bxN args
	else						ret = -1;
#endif
#if REGION==REGION_EU
	if	   (
			(addr==0x826F)||
			(addr==0xE61E)||
			(addr==0xE73E)||
			(addr==0xE85E)||
			(addr==0xE8D2)||
			(addr==0xEB1F)||
			(addr==0xEBB2)||
			(0)
			)					ret = 0;	// 2b args
	else if(
			(addr==0xEB7F)||
			(0)
			)					ret = 1;	// ofs, 1b args
	else if(
			(addr==0x853A)||
			(addr==0x8ADF)||
			(addr==0x92BB)||
			(addr==0x92CC)||
			(addr==0x92D8)||
			(addr==0x92E4)||
			(addr==0xE63D)||
			(addr==0xE662)||
			(addr==0xE684)||
			(addr==0xE692)||
			(addr==0xE6A5)||
			(addr==0xE6F2)||
			(addr==0xE711)||
			(addr==0xE75C)||
			(addr==0xE776)||
			(addr==0xE788)||
			(addr==0xE78E)||
			(addr==0xE87A)||
			(addr==0xEAED)||
			(addr==0xEB2B)||
			(addr==0xEB61)||
			(addr==0xEB69)||
			(addr==0xEBD1)||
			(0)

			)					ret = 2;	// 1b arg
	else if(
			(addr==0x91BF)||
			(addr==0xA30D)||
			(addr==0xE6CE)||
			(addr==0xE6DA)||
			(addr==0xE6E6)||
			(addr==0xE7EF)||
			(addr==0xEB71)||
			(addr==0xEAA8)||
			(addr==0xED13)||
			(0)
			)					ret = 3;	// ofs arg
	else if(
			(addr==0xE79A)||
			(0)
			)					ret = 4;	// 5b args
	else if(
			(addr==0x80D2)||
			(addr==0x83E7)||
			(addr==0x8481)||
			(addr==0x890E)||
			(addr==0x8952)||
			(addr==0x8AF6)||
			(addr==0x8B1B)||
			(addr==0x8B4F)||
			(addr==0x8BAA)||
			(addr==0x8BC8)||
			(addr==0x8C5B)||
			(addr==0x8DDD)||
			(addr==0x8DE6)||
			(addr==0x8DF3)||
			(addr==0x8DFC)||
			(addr==0x8FAF)||
			(addr==0x8FB5)||
			(addr==0x8FC2)||
			(addr==0x8FED)||
			(addr==0x9025)||
			(addr==0x90E6)||
			(addr==0x9199)||
			(addr==0x919F)||
			(addr==0x91A6)||
			(addr==0x91A8)||
			(addr==0x91AF)||
			(addr==0x91B1)||
			(addr==0x91F2)||
			(addr==0x9215)||
			(addr==0x9229)||
			(addr==0x923D)||
			(addr==0x9257)||
			(addr==0x926C)||
			(addr==0x9282)||
			(addr==0x941F)||
			(addr==0x9474)||
			(addr==0x9492)||
			(addr==0x9498)||
			(addr==0x94CF)||
			(addr==0x94DA)||
			(addr==0x9848)||
			(addr==0x9A70)||
			(addr==0x9A7D)||
			(addr==0x9DA9)||
			(addr==0x9E2B)||
			(addr==0x9E3A)||
			(addr==0x9E57)||
			(addr==0x9F3D)||
			(addr==0xA026)||
			(addr==0xA186)||
			(addr==0xA1E3)||
			(addr==0xA203)||
			(addr==0xA242)||
			(addr==0xA316)||
			(addr==0xA32C)||
			(addr==0xA394)||
			(addr==0xA3FE)||
			(addr==0xA434)||
			(addr==0xA449)||
			(addr==0xA43F)||
			(addr==0xA4CE)||
			(addr==0xA4D7)||
			(addr==0xA53B)||
			(addr==0xA54A)||
			(addr==0xA573)||
			(addr==0xA5F2)||
			(addr==0xA5FB)||
			(addr==0xA62E)||
			(addr==0xA639)||
			(addr==0xA66D)||
			(addr==0xA678)||
			(addr==0xA6B4)||
			(addr==0xA6BF)||
			(addr==0xA6FB)||
			(addr==0xA726)||
			(addr==0xA731)||
			(addr==0xA74D)||
			(addr==0xA777)||
			(addr==0xA792)||
			(addr==0xA797)||
			(addr==0xA7A8)||
			(addr==0xA79C)||
			(addr==0xA80A)||
			(addr==0xA813)||
			(addr==0xA845)||
			(addr==0xA84E)||
			(addr==0xA884)||
			(addr==0xA88F)||
			(addr==0xA903)||
			(addr==0xA90C)||
			(addr==0xA974)||
			(addr==0xB2B1)||
			(addr==0xBAF9)||
			(addr==0xBBF3)||
			(addr==0xC3A3)||
			(addr==0xC3AA)||
			(addr==0xC4CE)||
			(addr==0xC5E9)||
			(addr==0xC624)||
			(addr==0xCCE1)||
			(addr==0xCD28)||
			(addr==0xCEF2)||
			(addr==0xD0BA)||
			(addr==0xD348)||
			(addr==0xD3C6)||
			(addr==0xD3F2)||
			(addr==0xD3F8)||
			(addr==0xD3FD)||
			(addr==0xD41B)||
			(addr==0xD422)||
			(addr==0xD42A)||
			(addr==0xDD7C)||
			(addr==0xE561)||
			(addr==0xE58A)||
			(addr==0xE77C)||
			(addr==0xE781)||
			(addr==0xE7FC)||
			(addr==0xEAB7)||
			(addr==0xEABF)||
			(addr==0xEB41)||
			(addr==0xEB50)||
			(addr==0xEB96)||
			(addr==0xEBAA)||
			(addr==0xEBE6)||
			(addr==0xEBFE)||
			(addr==0xEC0C)||
			(addr==0xEC1F)||
			(addr==0xEC3A)||
			(addr==0xEC4A)||
			(addr==0xEC7B)||
			(addr==0xECB1)||
			(addr==0xECBB)||
			(addr==0xECC5)||
			(addr==0xECD4)||
			(addr==0xECE9)||
			(addr==0xECF4)||
			(0)
			)					ret = 5;	// no args
	else if(
			(addr==0x8A9E)||
			(0)
			)					ret = 6;	// ofs, 2b args
	else if(
			(addr==0xE6B8)||
			(0)
			)					ret = 7;	// 1b, ofs args
	else if(
			(addr==0xE9D0)||
			(0)
			)					ret = 8;	// 1b + 3bxN args
	else if(
			(addr==0xE8FB)||
			(0)
			)					ret = 9;	// 3b args
	else if(
			(addr==0xE94C)||
			(0)
			)					ret = 10;	// 1b + 4bxN args
	else if(
			(addr==0xE886)||
			(0)
			)					ret = 11;	// 1b + 4bxN args
	else						ret = -1;
#endif
#if REGION==REGION_US
	if	   (
			(addr==0x826F)||
			(addr==0xE618)||
			(addr==0xE738)||
			(addr==0xE858)||
			(addr==0xE8CC)||
			(addr==0xEB19)||
			(addr==0xEBAC)||
			(0)
			)					ret = 0;	// 2b args
	else if(
			(addr==0xEB79)||
			(0)
			)					ret = 1;	// ofs, 1b args
	else if(
			(addr==0x853A)||
			(addr==0x8ADF)||
			(addr==0x92BB)||
			(addr==0x92CC)||
			(addr==0x92D8)||
			(addr==0x92E4)||
			(addr==0xE637)||
			(addr==0xE65C)||
			(addr==0xE67E)||
			(addr==0xE68C)||
			(addr==0xE69F)||
			(addr==0xE6EC)||
			(addr==0xE70B)||
			(addr==0xE756)||
			(addr==0xE770)||
			(addr==0xE782)||
			(addr==0xE788)||
			(addr==0xE874)||
			(addr==0xEAE7)||
			(addr==0xEB25)||
			(addr==0xEB5B)||
			(addr==0xEB63)||
			(addr==0xEBCB)||
			(0)

			)					ret = 2;	// 1b arg
	else if(
			(addr==0x91BF)||
			(addr==0xA30D)||
			(addr==0xE6C8)||
			(addr==0xE6D4)||
			(addr==0xE6E0)||
			(addr==0xE7E9)||
			(addr==0xEB6B)||
			(addr==0xEAA2)||
			(addr==0xED0D)||
			(0)
			)					ret = 3;	// ofs arg
	else if(
			(addr==0xE794)||
			(0)
			)					ret = 4;	// 5b args
	else if(
			(addr==0x80D2)||
			(addr==0x83E7)||
			(addr==0x8481)||
			(addr==0x890E)||
			(addr==0x8952)||
			(addr==0x8AF6)||
			(addr==0x8B1B)||
			(addr==0x8B4F)||
			(addr==0x8BAA)||
			(addr==0x8BC8)||
			(addr==0x8C5B)||
			(addr==0x8DDD)||
			(addr==0x8DE6)||
			(addr==0x8DF3)||
			(addr==0x8DFC)||
			(addr==0x8FAF)||
			(addr==0x8FB5)||
			(addr==0x8FC2)||
			(addr==0x8FED)||
			(addr==0x9025)||
			(addr==0x90E6)||
			(addr==0x9199)||
			(addr==0x919F)||
			(addr==0x91A6)||
			(addr==0x91A8)||
			(addr==0x91AF)||
			(addr==0x91B1)||
			(addr==0x91F2)||
			(addr==0x9215)||
			(addr==0x9229)||
			(addr==0x923D)||
			(addr==0x9257)||
			(addr==0x926C)||
			(addr==0x9282)||
			(addr==0x941F)||
			(addr==0x9474)||
			(addr==0x9492)||
			(addr==0x9498)||
			(addr==0x94CF)||
			(addr==0x94DA)||
			(addr==0x9848)||
			(addr==0x9A70)||
			(addr==0x9A7D)||
			(addr==0x9DA9)||
			(addr==0x9E2B)||
			(addr==0x9E3A)||
			(addr==0x9E57)||
			(addr==0x9F3D)||
			(addr==0xA026)||
			(addr==0xA186)||
			(addr==0xA1E3)||
			(addr==0xA203)||
			(addr==0xA242)||
			(addr==0xA318)||
			(addr==0xA32C)||
			(addr==0xA394)||
			(addr==0xA3FE)||
			(addr==0xA434)||
			(addr==0xA449)||
			(addr==0xA43F)||
			(addr==0xA4CE)||
			(addr==0xA4D7)||
			(addr==0xA53B)||
			(addr==0xA54A)||
			(addr==0xA573)||
			(addr==0xA5F2)||
			(addr==0xA5FB)||
			(addr==0xA62E)||
			(addr==0xA639)||
			(addr==0xA66D)||
			(addr==0xA678)||
			(addr==0xA6B4)||
			(addr==0xA6BF)||
			(addr==0xA6FB)||
			(addr==0xA726)||
			(addr==0xA731)||
			(addr==0xA74D)||
			(addr==0xA777)||
			(addr==0xA794)||
			(addr==0xA797)||
			(addr==0xA7A8)||
			(addr==0xA79C)||
			(addr==0xA80A)||
			(addr==0xA813)||
			(addr==0xA845)||
			(addr==0xA84E)||
			(addr==0xA884)||
			(addr==0xA88F)||
			(addr==0xA903)||
			(addr==0xA90C)||
			(addr==0xA974)||
			(addr==0xB2B1)||
			(addr==0xBAF9)||
			(addr==0xBBF3)||
			(addr==0xC3A2)||
			(addr==0xC3A9)||
			(addr==0xC4CD)||
			(addr==0xC5E8)||
			(addr==0xC623)||
			(addr==0xCCE0)||
			(addr==0xCD27)||
			(addr==0xCEEC)||
			(addr==0xD0B4)||
			(addr==0xD342)||
			(addr==0xD3C0)||
			(addr==0xD3EC)||
			(addr==0xD3F2)||
			(addr==0xD3F7)||
			(addr==0xD415)||
			(addr==0xD41C)||
			(addr==0xD424)||
			(addr==0xDD76)||
			(addr==0xE55B)||
			(addr==0xE584)||
			(addr==0xE776)||
			(addr==0xE77B)||
			(addr==0xE7F6)||
			(addr==0xEAB1)||
			(addr==0xEAB9)||
			(addr==0xEB3B)||
			(addr==0xEB4A)||
			(addr==0xEB90)||
			(addr==0xEBA4)||
			(addr==0xEBE0)||
			(addr==0xEBF8)||
			(addr==0xEC06)||
			(addr==0xEC19)||
			(addr==0xEC34)||
			(addr==0xEC44)||
			(addr==0xEC75)||
			(addr==0xECAB)||
			(addr==0xECB5)||
			(addr==0xECBF)||
			(addr==0xECCE)||
			(addr==0xECE3)||
			(addr==0xECEE)||
			(0)
			)					ret = 5;	// no args
	else if(
			(addr==0x8A9E)||
			(0)
			)					ret = 6;	// ofs, 2b args
	else if(
			(addr==0xE6B2)||
			(0)
			)					ret = 7;	// 1b, ofs args
	else if(
			(addr==0xE9CA)||
			(0)
			)					ret = 8;	// 1b + 3bxN args
	else if(
			(addr==0xE8F5)||
			(0)
			)					ret = 9;	// 3b args
	else if(
			(addr==0xE946)||
			(0)
			)					ret = 10;	// 1b + 4bxN args
	else if(
			(addr==0xE880)||
			(0)
			)					ret = 11;	// 1b + 4bxN args
	else						ret = -1;
#endif
	return ret;
}

static make_offset_custom(ea, exec, cmt) {
	auto ofs = Word(ea), bank = GetReg(ea,"ds")-1;
	MakeComm(ea, "");
	MakeComm(ea, cmt);
	if(ofs<0x8000)
		ea = make_offset_ex(ea, 0, exec, 1);
	else if(ofs>=0xC000) {
		ea = make_offset_ex(ea, 7, exec, 1);
	} else {
		if((bank==7)&&(ofs<0xC000)) {
			ea = make_offset_ex(ea, AskLong(0, "Enter Bank Nunber"), exec, 1);
		} else
			ea = make_offset_ex(ea, bank, exec, 1);
	}
	return ea;
}

static make_offset_custom_b(ea, bank, exec, cmt) {
	auto ofs = Word(ea);
	MakeComm(ea, "");
	MakeComm(ea, cmt);
	if(ofs<0x8000)
		ea = make_offset_ex(ea, 0, exec, 1);
	else if(ofs>=0xC000) {
		ea = make_offset_ex(ea, 7, exec, 1);
	} else {
		ea = make_offset_ex(ea, bank, exec, 1);
	}
	return ea;
}

static ngb2_opcode_name(cmd) {
	auto ret = "";
	if(cmd==0x00) {		  ret = "SSTOP           ";	// no args
	} else if(cmd==0x01) {ret = "SLOOP_BEGIN     ";	// 1b arg
	} else if(cmd==0x02) {ret = "SLOOP_END       ";	// no args
	} else if(cmd==0x03) {ret = "SJMP            ";	// ofs arg, no exec
	} else if(cmd==0x04) {ret = "SJSR            ";	// ofs arg, no exec
	} else if(cmd==0x05) {ret = "SRET            ";	// no args
	} else if(cmd==0x06) {ret = "SDELAY          ";	// 1b arg
	} else if(cmd==0x07) {ret = "NJSR            ";	// ofs arg
	} else if(cmd==0x08) {ret = "SRUN            ";	// 1b, ofs, no exec
	} else if(cmd==0x09) {ret = "NBG_HNDL_SET    ";	// ofs, no exec
	} else if(cmd==0x0A) {ret = "SUSPEND         ";	// no args
	} else if(cmd==0x0B) {ret = "SBCS            ";	// ofs, no exec
	} else if(cmd==0x0C) {ret = "SBCC            ";	// ofs, no exec
	} else if(cmd==0x0D) {ret = "SDISABLE_SELF   ";	// no args
	} else if(cmd==0x0E) {ret = "SMEM_ALU        ";	// ofs, 2b args [ofs, cmd, arg], no exec
	} else if(cmd==0x0F) {ret = "SARG_SET        ";	// 1b, 1b args [arg idx, imm]
	} else if(cmd==0x10) {ret = "NBG_HNDL_RESET  ";	// no args
	} else if(cmd==0x11) {ret = "SJMP_SW         ";	// 1b arg [tbl size], ofs tbl x size, no exec
	} else if(cmd==0x12) {ret = "SJSR_SW         ";	// 1b arg [tbl size], ofs tbl x size, no exec
	} else if(cmd==0x13) {ret = "STORE8          ";	// ofs, 1b arg
	} else if(cmd==0x14) {ret = "SDISABLE        ";	// 1b arg
	} else if(cmd==0x15) {ret = "SARG_ALU        ";	// 3b args
	} else if(cmd==0x16) {ret = "STORE16         ";	// ofs, 2b arg
	} else if(cmd==0x17) {ret = "SBCS_BREAK      ";	// ofs arg, no exec
	} else if(cmd==0x18) {ret = "SBCC_BREAK      ";	// ofs arg, no exec UNUSED
	} else if(cmd==0x19) {ret = "NJSR_SW         ";	// 1b arg [tbl size]
// ..
	} else if(cmd==0x20) {ret = "SPR_IDX_SET     ";	// 1b arg
	} else if(cmd==0x21) {ret = "POS_X_SET       ";	// 2b args
	} else if(cmd==0x22) {ret = "POS_Y_SET       ";	// 2b args
	} else if(cmd==0x23) {ret = "POS_X_MOVE      ";	// 1b arg
	} else if(cmd==0x24) {ret = "POS_Y_MOVE      ";	// 1b arg
	} else if(cmd==0x25) {ret = "POS_X_DELTA_SET ";	// 2b args
	} else if(cmd==0x26) {ret = "POS_Y_DELTA_SET ";	// 2b args
	} else if(cmd==0x27) {ret = "POS_X_DELTA_ADD ";	// 2b args
	} else if(cmd==0x28) {ret = "POS_Y_DELTA_ADD ";	// 2b args
	} else if(cmd==0x29) {ret = "SCRL_X_SET      ";	// 2b args UNUSED
	} else if(cmd==0x2A) {ret = "SCRL_Y_SET      ";	// 2b args
	} else if(cmd==0x2B) {ret = "SCRL_X_MOVE_SET ";	// 2b args UNUSED
	} else if(cmd==0x2C) {ret = "SCRL_Y_MOVE_SET ";	// 2b args
	} else if(cmd==0x2D) {ret = "SCRL_X_MOVE_ADD ";	// 2b args UNUSED
	} else if(cmd==0x2E) {ret = "SCRL_Y_MOVE_ADD ";	// 2b args UNUSED
	} else if(cmd==0x2F) {ret = "SPR_IDX_INC     ";	// no args
	} else if(cmd==0x30) {ret = "SPR_IDX_DEC     ";	// no args
	} else if(cmd==0x31) {ret = "SPR_IDX_ADD_IMM ";	// 1b arg
	} else if(cmd==0x32) {ret = "BYTE_D5_ADD     ";	// 1b arg  UNUSED
	} else if(cmd==0x33) {ret = "BYTE_D6_ADD     ";	// 1b arg  UNUSED
	} else if(cmd==0x34) {ret = "POS_MOVE_STOP   ";	// no args
	} else if(cmd==0x35) {ret = "SCRL_MOVE_STOP  ";	// no args
	} else 			 ret = form("UNK%02X         ",cmd);

	return ret;
}

static ngb2_select_name(tmp0,def0,def1,ren) {
	if((Name(tmp0)=="")||(strstr(Name(tmp0),def0)==0)||(strstr(Name(tmp0),def1)==0)) {
		MakeNameEx(tmp0,form(ren,tmp0),SN_CHECK|SN_NOWARN);
	} else
	return Name(tmp0);
}

static ngb2_get_alu_name(code) {
	if(code==0)
		return "AND";
	else if(code==1)
		return "ORA";
	else if(code==2)
		return "ADC";
	else
		return "-UNSUPPORTED ALU-";
}

static ngb2_get_address_name(ea,bank) {
	auto tmp0,tmp1;
	tmp0 = Word(ea);
	if(tmp0 < 0x8000)
		tmp0 = tmp0+MK_FP(AskSelector(0), 0);
	else if(tmp0 < 0xC000)
		tmp0 = tmp0+MK_FP(AskSelector(bank+1), 0);
	else
		tmp0 = tmp0+MK_FP(AskSelector(7+1), 0);
	tmp1 = Name(tmp0);
	if(tmp1=="") tmp1=form("0x%08X",tmp0);
	return tmp1;
}

static ngb2_opcode(ea,tab,lvl_bank) {
	auto cmd_opc = "", delay_opc, cmd, bank, tmp0, tmp1, tmp2, tmp3, tmp4, stop, error;
	bank = GetReg(ea,"ds")-1;

	stop = 0; error = 0;

#ifdef VERBOSE1
	Message("%sblock BEGINS at 0x%08x\n", tab, ea);
#endif

#ifndef MANUAL
	while(stop==0)
#endif
	{
		if(ea != BADADDR) {
			cmd = Byte(ea);

#ifdef VERBOSE2
	Message("%s*trace 0x%08x\n", tab, ea);
#endif
			if(cmd>=0x20) {
				delay_opc = cmd&7;
				cmd = 0x20|((cmd-0x20)>>3);
			} else
				delay_opc = -1;

			cmd_opc = ngb2_opcode_name(cmd);

			if(delay_opc != -1) {
				if((cmd==0x2F)||(cmd==0x30)||(cmd==0x34)||(cmd==0x35))
					cmd_opc = form("%s%d",cmd_opc,delay_opc);
				else
					cmd_opc = form("%s%d,",cmd_opc,delay_opc);
			}

			if((cmd==0x00)||(cmd==0x05)||(cmd==0x0A)||(cmd==0x0D)) {	// ret/exit/stop/suspend/disable_self
				make_data_array(ea, 1, cmd_opc);
				stop = 1;
			} else if((cmd==0x02)||(cmd==0x10)||(cmd==0x2F)||(cmd==0x30)||(cmd==0x34)||(cmd==0x35)) {	// no args
				ea = make_data_array(ea, 1, cmd_opc);
			} else if((cmd==0x01)||(cmd==0x06)||(cmd==0x14)||(cmd==0x20)||(cmd==0x23)||(cmd==0x24)||(cmd==0x31)||(cmd==0x32)||(cmd==0x33)) {	// 1b arg
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
			} else if((cmd==0x0F)||(cmd==0x21)||(cmd==0x22)||(cmd==0x25)||(cmd==0x26)||(cmd==0x27)||(cmd==0x28)||(cmd==0x29)||(cmd==0x2A)||(cmd==0x2B)||(cmd==0x2C)||(cmd==0x2D)||(cmd==0x2E)) {	// 2b args
				ea = make_data_array(ea, 3, form("%s$%02X,$%02X",cmd_opc,Byte(ea+1),Byte(ea+2)));
			} else if((cmd==0x15)) {	// 3b arg, ALU
				ea = make_data_array(ea, 4, form("%s$%02X,%s,$%02X",cmd_opc,Byte(ea+1),ngb2_get_alu_name(Byte(ea+2)),Byte(ea+3)));
			} else if((cmd==0x0E)) {	// ofs arg, 2b args, ALU
				tmp1 = ngb2_get_address_name(ea+1,bank);
				ea = make_data_array(ea, 1, form("%s%s,%s,$%02X",cmd_opc,tmp1,ngb2_get_alu_name(Byte(ea+3)),Byte(ea+4)));
				ea = make_offset_custom(ea, 0, ""); 				// no exec
				ea = make_data_array(ea, 2, "");
			} else if((cmd==0x16)) {	// ofs arg, 2b args
				tmp0 = Word(ea+1);
				tmp1 = ngb2_get_address_name(ea+1,bank);
#if REGION==REGION_EU
				if((tmp0==0xE7)||(tmp0==0xE5)||(tmp0==0xEB)) {
#else
				if((tmp0==0xE6)||(tmp0==0xE4)||(tmp0==0xEA)) {
#endif
					tmp2 = ngb2_get_address_name(ea+3,lvl_bank);
#ifdef VERBOSE3
					Message("%s#ptr%02X set to bank %d at 0x%08x\n", tab, tmp0, lvl_bank, ea);
#endif
				}
				else
					tmp2 = ngb2_get_address_name(ea+3,bank);
				ea = make_data_array(ea, 1, form("%s%s,%s",cmd_opc,tmp1,tmp2));
				ea = make_offset_custom(ea, 0, ""); 				// no exec
#if REGION==REGION_EU
				if((tmp0==0xE7)||(tmp0==0xE5)||(tmp0==0xEB))
#else
				if((tmp0==0xE6)||(tmp0==0xE4)||(tmp0==0xEA))
#endif
					ea = make_offset_custom_b(ea, lvl_bank, 0, ""); // no exec
				else
					ea = make_offset_custom(ea, 0, ""); 			// no exec
			} else if((cmd==0x13)) {	// ofs arg, 1b args
				if(Word(ea+1)==0x0027) {
					lvl_bank = Byte(ea+3);
#ifdef VERBOSE3
					Message("%s#lvl_bank set to %d at 0x%08x\n", tab, lvl_bank, ea);
#endif
				}
				tmp1 = ngb2_get_address_name(ea+1,bank);
				ea = make_data_array(ea, 1, form("%s%s,$%02X",cmd_opc,tmp1,Byte(ea+3)));
				ea = make_offset_custom(ea, 0, ""); 				// no exec
				ea = make_data_array(ea, 1, "");
			} else if((cmd==0x11)) {	// script jmp switch
#if REGION==REGION_JP
				if(ea==0x15732)	// bugfix for switch with incorrect number of elements
#else
				if(ea==0x2172A)	// bugfix for switch with incorrect number of elements
#endif
					tmp1 = 1;
				else
					tmp1 = Byte(ea+1);
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,tmp1));
				tmp2=0;
				while((tmp2<tmp1)&&!stop) {
					tmp0 = Word(ea)+MK_FP(AskSelector(bank+1), 0);
					tmp3 = ngb2_select_name(tmp0, "byte_","unk_","_sjmp_case_%X");
					ea = make_offset_custom(ea, 0, form("SCASE    %s",tmp3));
// -------- recursive exec!!
					if(tmp0>=ea) {
						if((lvl_bank=ngb2_opcode(tmp0,tab+" ",lvl_bank))==0xBADC0DE)
							error = 1;
					}
					else {
#ifdef VERBOSE1
						Message("%s >skip JMP_SW UP at 0x%08x\n", tab, ea);
#endif
					}
// --------
					tmp2++;
				}
// WARNING! some SJMP_SW opcodes has default options at the end of opcode! some doesn't
				stop = 1;
			} else if((cmd==0x12)) {	// script jsr switch
				tmp1 = Byte(ea+1);
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,tmp1));
				tmp2=0;
				while((tmp2<tmp1)&&!stop) {
					tmp0 = Word(ea)+MK_FP(AskSelector(bank+1), 0);
					tmp3 = ngb2_select_name(tmp0, "byte_","unk_","_sjsr_case_%X");
					ea = make_offset_custom(ea, 0, form("SCASE    %s",tmp3));
// -------- recursive exec!!
					if((lvl_bank=ngb2_opcode(tmp0,tab+" ",lvl_bank))==0xBADC0DE) {
						stop = 1;
						error = 1;
					}
// --------
					tmp2++;
				}
			} else if((cmd==0x19)) {	// native switch
				tmp1 = Byte(ea+1);
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,tmp1));
				tmp2=0;
				while(tmp2<tmp1) {
					tmp0 = Word(ea)+MK_FP(AskSelector(bank+1), 0);
					tmp3 = ngb2_select_name(tmp0, "loc_","sub_","_ncase_%X");
					ea = make_offset_custom(ea, 1, form("SCASE    %s",tmp3));
					tmp2++;
				}
			} else if((cmd==0x08)) {	// 1b arg, ofs
				tmp2 = Word(ea+2);
				if(tmp2 < 0xC000)
					tmp0 = tmp2+MK_FP(AskSelector(bank+1), 0);
				else
					tmp0 = tmp2+MK_FP(AskSelector(7+1), 0);
				tmp1 = ngb2_select_name(tmp0, "byte_","unk_","_scr_%X");
				ea = make_data_array(ea, 2, form("%s$%02X,%s",cmd_opc,Byte(ea+1),tmp1));
				ea = make_offset_custom(ea, 0, "");	// no exec
// -------- recursive exec!!
				if((lvl_bank=ngb2_opcode(tmp0,tab+" ",lvl_bank))==0xBADC0DE) {
					stop = 1;
					error = 1;
				}
// --------
			} else if((cmd==0x03)||(cmd==0x0B)||(cmd==0x0C)||(cmd==0x17)||(cmd==0x18)) {	// ofs, no exec
				tmp2 = Word(ea+1);
				if(tmp2 < 0xC000)
					tmp0 = tmp2+MK_FP(AskSelector(bank+1), 0);
				else
					tmp0 = tmp2+MK_FP(AskSelector(7+1), 0);
				tmp1 = ngb2_select_name(tmp0, "byte_","unk_","_sloc_%X");
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp1));
				ea = make_offset_custom(ea, 0, ""); 				// no exec
				if(cmd==0x03) {
// -------- recursive exec!!
					if(tmp0>ea) {
						if((lvl_bank=ngb2_opcode(tmp0,tab+" ",lvl_bank))==0xBADC0DE)
							error = 1;
					}
					else {
#ifdef VERBOSE1
						Message("%s >skip JUMP UP at 0x%08x\n", tab, ea);
#endif
					}
// --------
					stop = 1;
					ea=ea-3;
				}
			} else if((cmd==0x04)) {	// ofs, no exec
				tmp2 = Word(ea+1);
				if(tmp2 < 0xC000)
					tmp0 = tmp2+MK_FP(AskSelector(bank+1), 0);
				else
					tmp0 = tmp2+MK_FP(AskSelector(7+1), 0);
				tmp1 = ngb2_select_name(tmp0, "byte_","unk_","_ssub_%X");
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp1));
				ea = make_offset_custom(ea, 0, ""); 				// no exec
// -------- recursive exec!!
				if((lvl_bank=ngb2_opcode(tmp0,tab+" ",lvl_bank))==0xBADC0DE) {
					stop = 1;
					error = 1;
					ea=ea-3;
				}
// --------
			} else if((cmd==0x09)) {	// ofs, exec
				tmp2 = Word(ea+1);
				if(tmp2 < 0xC000)
					tmp0 = Word(ea+1)+MK_FP(AskSelector(bank+1), 0);
				else
					tmp0 = Word(ea+1)+MK_FP(AskSelector(7+1), 0);
				tmp1 = ngb2_select_name(tmp0, "loc_","sub_","_nbgsub_%X");
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp1));
				ea = make_offset_custom(ea, 1, ""); 				// exec
			} else if((cmd==0x07)) {	// ofs, exec
				tmp2 = Word(ea+1);
				tmp3 = ngb2_get_native_sub_args(tmp2);
				if(tmp3==0) {
					tmp4 = form(",$%02X,$%02X",Byte(ea+3),Byte(ea+4));
				} else if(tmp3==1) {
					tmp1 = ngb2_get_address_name(ea+3,bank);
					tmp4 = form(",%s,$%02X",tmp1,Byte(ea+5));
				} else if((tmp3==2)||(tmp3==8)||(tmp3==10)) {
					tmp4 = form(",$%02X",Byte(ea+3));
				} else if(tmp3==3) {
					tmp1 = ngb2_get_address_name(ea+3,bank);
					tmp4 = form(",%s",tmp1);
				} else if(tmp3==4) {
					tmp4 = form(",$%02X,$%02X,$%02X,$%02X,$%02X",Byte(ea+3),Byte(ea+4),Byte(ea+5),Byte(ea+6),Byte(ea+7));
				} else if((tmp3==5)||(tmp3==11)) {
					tmp4 = "";
				} else if(tmp3==6) {
					tmp1 = ngb2_get_address_name(ea+3,bank);
					tmp4 = form(",%s,$%02X,$%02X",tmp1,Byte(ea+5),Byte(ea+6));
				} else if(tmp3==7) {
					tmp1 = ngb2_get_address_name(ea+4,bank);
					tmp4 = form(",$%02X,%s",Byte(ea+3),tmp1);
				} else if(tmp3==9) {
					tmp4 = form(",$%02X,$%02X,$%02X",Byte(ea+3),Byte(ea+4),Byte(ea+5));
				} else
					tmp4 = ",UNKNOWN";
				if(tmp2 < 0xC000)
					tmp0 = tmp2+MK_FP(AskSelector(bank+1), 0);
				else
					tmp0 = tmp2+MK_FP(AskSelector(7+1), 0);
				tmp1 = ngb2_select_name(tmp0, "loc_","sub_","_nsub_%X");
				ea = make_data_array(ea, 1, form("%s%s%s",cmd_opc,tmp1,tmp4));
				ea = make_offset_custom(ea, 1, ""); 				// exec
				if(tmp3==0) {
					ea = make_data_array(ea, 2, "");
				} else if(tmp3==1) {
					ea = make_offset_custom(ea, 0, "");
					ea = make_data_array(ea, 1, "");
				} else if(tmp3==2) {
					ea = make_data_array(ea, 1, "");
				} else if(tmp3==3) {
					// special case for scrip resource
#if REGION==REGION_JP
					if(Word(ea-2)==0xA31D) {
#else
					if(Word(ea-2)==0xA30D) {
#endif
//						Message("test at 0x%08x\n",ea);
						tmp0=Word(ea);
						if(tmp0 < 0xC000)
							tmp0 = tmp0+MK_FP(AskSelector(bank+1), 0);
						else
							tmp0 = tmp0+MK_FP(AskSelector(7+1), 0);
//						Message("  make data\n");
						while(Byte(tmp0)!=0xFF) {
//							Message("    record 0x%08x %02x %02x %02x %02x %02x %04x\n",tmp0,Byte(tmp0),Byte(tmp0+1),Byte(tmp0+2),Byte(tmp0+3),Byte(tmp0+4),Word(tmp0+5));
							tmp0 = make_data_array(tmp0, 5, "");
							tmp0 = make_offset_custom(tmp0, 0, "");
						}
//						Message("  stop\n");
						MakeByte(tmp0);
					}
					ea = make_offset_custom(ea, 0, "");
				} else if(tmp3==4) {
					ea = make_data_array(ea, 5, "");
				} else if(tmp3==5) {
				} else if(tmp3==6) {
					ea = make_offset_custom(ea, 0, "");
					ea = make_data_array(ea, 2, "");
				} else if(tmp3==7) {
					ea = make_data_array(ea, 1, "");
					ea = make_offset_custom(ea, 0, "");
				} else if(tmp3==8) {
					tmp1 = Byte(ea);
					ea = make_data_array(ea, 1, "");
					for(tmp0=0; tmp0<tmp1; tmp0++) {
						ea = make_data_array(ea, 3, form("NARGB    $%02X,$%02X,$%02X",Byte(ea),Byte(ea+1),Byte(ea+2)));
					}
				} else if(tmp3==9) {
					ea = make_data_array(ea, 3, "");
				} else if(tmp3==10) {
					tmp1 = Byte(ea);
					ea = make_data_array(ea, 1, "");
					for(tmp0=0; tmp0<tmp1; tmp0++) {
						ea = make_data_array(ea, 4, form("NARGB    $%02X,$%02X,$%02X,$%02X",Byte(ea),Byte(ea+1),Byte(ea+2),Byte(ea+3)));
					}
				} else if(tmp3==11) {
					tmp1 = ngb2_get_address_name(ea,lvl_bank);
					ea = make_offset_custom_b(ea, lvl_bank, 0, form("NARGB    %s",tmp1));
					tmp1 = ngb2_get_address_name(ea,lvl_bank);
					ea = make_offset_custom_b(ea, lvl_bank, 0, form("NARGB    %s",tmp1));
					tmp1 = ngb2_get_address_name(ea,lvl_bank);
					ea = make_offset_custom_b(ea, lvl_bank, 0, form("NARGB    %s",tmp1));
					tmp1 = ngb2_get_address_name(ea,lvl_bank);
					ea = make_offset_custom_b(ea, lvl_bank, 0, form("NARGB    %s",tmp1));
					tmp1 = ngb2_get_address_name(ea,lvl_bank);
					ea = make_offset_custom_b(ea, lvl_bank, 0, form("NARGB    %s",tmp1));
				} else {
					Message("%s >unknown NATIVE SUB $%04X at 0x%08x \n", tab, tmp2, ea);
					ea=ea-3;
					stop = 1;
					error = 1;
				}
			} else {
				Message("%s >unknown OPCODE %02x at 0x%08x \n", tab, cmd, ea);
				stop = 1;
				error = 1;
			}
		} // NO BAD ARRD
	} // WHILE
#ifdef VERBOSE1
	Message("%sblock ENDS at 0x%08x\n", tab, ea);
#endif
#ifdef MANUAL
	return ea;
#else
	if(error)
		return 0xBADC0DE;
	else
		return lvl_bank;
#endif
}

static ngb2_script_selection(void) {
	auto ea;
#ifdef MANUAL
	Jump(ngb2_opcode(ScreenEA(),"",-2));
#else
	Message("MANUAL DECOMPILATION START at 0x%08x\n", ea);
	ea = ngb2_opcode(ScreenEA(),"",-2);
	Message("MANUAL DECOMPILATION END at 0x%08x\n", ea);
#endif
}

///*
static ngb2_apu_auto(mus_tbl_ea, music_tbl_len, mode) {
	auto i, j, mus_ea, chnl_ea, chnl_cnt, mus_pref, mus_num;
	auto base = MK_FP(AskSelector(GetReg(mus_tbl_ea,"ds")), 0);

	for(i=0;i<music_tbl_len;i++) {
		auto tmp0 = mus_tbl_ea+(i<<1);
		make_offset_custom(tmp0, 0, "");
		mus_ea = Word(tmp0)+base;
		if(mode==0) {
			mus_num = 0x0D;
			if(i<mus_num)
				MakeNameEx(mus_ea, form("_mus%X", i), SN_CHECK|SN_NOWARN);
			else
				MakeNameEx(mus_ea, form("_snd%02X", i-mus_num), SN_CHECK|SN_NOWARN);
			mus_pref = Name(mus_ea);
			chnl_cnt = Byte(mus_ea);
			mus_ea = make_data_array(mus_ea, 1, "");
			for(j=0;j<chnl_cnt;j++) {
				chnl_ea = Word(mus_ea)+base;
				MakeNameEx(chnl_ea, form("%s_%c", mus_pref, 0x41+j), SN_CHECK|SN_NOWARN);
				ngb2_apu(chnl_ea);
				mus_ea = make_offset_custom(mus_ea, 0, "");
				mus_ea = make_data_array(mus_ea, 1, "");
				Wait();
			}
		} else if (mode==1) {
			MakeNameEx(mus_ea, form("_sample%02X", i), SN_CHECK|SN_NOWARN);
			ngb2_apu(mus_ea);
		}
	}
}

static kirby_apu_auto(meal, meah, meab, mlen, name, mode) {
	auto i, j, mus_ea, chnl_ea, chnl_cnt, mus_pref, mus_num, tmp0;
	auto baseA = MK_FP(AskSelector(GetReg(meal,"ds")), 0), baseB;

	for(i=0;i<mlen;i++) {
		if(mode==0) {
			tmp0 = Byte(meal+i)|(Byte(meah+i)<<8);
			if(meab==-1) {
				baseB = baseA;
			} else {
				baseB = MK_FP(AskSelector(Byte(meab+i)+1), 0);
//				Message("bank %02X, ofs %04X, base %08X, full 0x%08X\n", Byte(meab+i), tmp0, baseB, tmp0+baseB);
			}
			mus_ea = tmp0+baseB;
			MakeNameEx(mus_ea, form(name, i), SN_CHECK|SN_NOWARN);
			mus_pref = Name(mus_ea);
			chnl_cnt = Byte(mus_ea);
			mus_ea = make_data_array(mus_ea, 1, "");
			for(j=0;j<chnl_cnt;j++) {
				chnl_ea = Word(mus_ea)+baseB;
				MakeNameEx(chnl_ea, form("%s_%c", mus_pref, 0x41+j), SN_CHECK|SN_NOWARN);
				//ngb2_apu(chnl_ea);
				mus_ea = make_offset_custom(mus_ea, 0, "");
				mus_ea = make_data_array(mus_ea, 1, "");
			}
		} else if (mode==1) {
			tmp0 = meal+(i<<1);
			make_offset_custom(tmp0, 0, "");
			mus_ea = Word(tmp0)+baseA;
			MakeNameEx(mus_ea, form(name, i), SN_CHECK|SN_NOWARN);
			//ngb2_apu(mus_ea);
		}
	}
}

static ngb2_apu_selection(void) {
	Jump(ngb2_apu(ScreenEA()));
}

static ngb2_apu_name(cmd) {
	auto ret = "";
	if(cmd==0xFF) {			ret = "ASTOP       ";	// no
	} else if(cmd==0xE0) {	ret = "ACMDE0      ";	// 2b
	} else if(cmd==0xE1) {	ret = "ACMDE1      ";	// 1b
	} else if(cmd==0xE2) {	ret = "ACMDE2      ";	// 2b
	} else if(cmd==0xE3) {	ret = "ACMDE3      ";	// 1b

	} else if(cmd==0xF0) {	ret = "ACMDF0      ";	// 1b
	} else if(cmd==0xF1) {	ret = "ACMDF1      ";	// 1b
	} else if(cmd==0xF2) {	ret = "ACMDF2      ";	// 1b
	} else if(cmd==0xF3) {	ret = "ACMDF3      ";	// 1b
	} else if(cmd==0xF4) {	ret = "ACMDF4      ";	// 1b
	} else if(cmd==0xF5) {	ret = "ACMDF5      ";	// 1b
	} else if(cmd==0xF6) {	ret = "ACMDF6      ";	// 1b
	} else if(cmd==0xF7) {	ret = "ACMDF7      ";	// 1b

	} else if(cmd==0xF8) {	ret = "AJMP        ";	// ofs
	} else if(cmd==0xFA) {	ret = "AJSR        ";	// ofs
	} else if(cmd==0xFB) {	ret = "ARET        ";	// no

	} else if(cmd==0xFC) {	ret = "ALOOP_START ";	// 1b
	} else if(cmd==0xFD) {	ret = "ALOOP_END   ";	// no
	} else if(cmd==0xFE) {	ret = "ANOP        ";	// 1b
		ret = form("UNK%02X",cmd);
	}
	return ret;
}

static ngb2_apu(ea) {
	auto cmd_opc = "", cmd, bank, tmp0, tmp1, tmp2, stop = 0;
	bank = GetReg(ea,"ds")-1;
	tmp2 = ea;
	do {
		if(ea != BADADDR) {
			while((cmd = Byte(ea)) < 0xE0) {
				if((cmd&0xE0)==0xC0) {
					ea = make_data_array(ea, 2, form("ADATAEX     $%02X,$%02X",Byte(ea),Byte(ea+1)));
				} else {
					ea = make_data_array(ea, 1, form("ADATA       $%02X",Byte(ea)));
				}
			}
			cmd_opc = ngb2_apu_name(cmd);
			if((cmd==0xFB)||(cmd==0xFF)) {	// RET/SSTOP
				ea = make_data_array(ea, 1, cmd_opc);
				stop = 1;
				// stop here
			} else if(cmd == 0xFD) {	// no args
				ea = make_data_array(ea, 1, cmd_opc);
			} else if((cmd==0xE1)||(cmd==0xE3)||((cmd>=0xF0)&&(cmd<=0xF7))||(cmd==0xFC)||(cmd==0xFE)) {	// 1b arg
				ea = make_data_array(ea, 2, form("%s$%02X",cmd_opc,Byte(ea+1)));
			} else if((cmd==0xE0)||(cmd==0xE2)) {	// 2b args
				ea = make_data_array(ea, 3, form("%s$%02X,$%02X",cmd_opc,Byte(ea+1),Byte(ea+2)));
			} else if((cmd==0xF8)||(cmd==0xFA)) {	// ofs
//				tmp1 = ngb2_get_address_name(ea+1,bank);
				tmp0 = Word(ea+1)+MK_FP(AskSelector(bank+1), 0);
				if(cmd==0xF8)
					MakeNameEx(tmp0, form("_aloc_%X", tmp0), SN_CHECK|SN_NOWARN);
				else
					MakeNameEx(tmp0, form("_asub_%X", tmp0), SN_CHECK|SN_NOWARN);
				tmp1 = Name(tmp0);
				ea = make_data_array(ea, 1, form("%s%s",cmd_opc,tmp1));
				ea = make_offset_custom(ea, 0, "");	// no exec
				if(cmd==0xF8) {
					if(tmp0>ea) {
						ngb2_apu(tmp0);
						stop=1;
					} else
						stop=1;
				} else
					ngb2_apu(tmp0);
			} else {
				Message(" unknown apu opcode at 0x%08x = %02x\n", ea, cmd);
			}
//			return ea;
		}
	} while (!stop);
//	return tmp2;
	return ea;
}

//*/

static ngb2_enemy_data_parse(void) {
	auto ea = ScreenEA(), cmd, tmp0, size = 0, stop=0;
	auto bank = GetReg(ea,"ds")-1;
	auto flags_ea = -1;
#if REGION==REGION_JP
	flags_ea = 0x63B85;
#endif
#if REGION==REGION_EU
	flags_ea = 0xB7B58;
#endif
#if REGION==REGION_US
	flags_ea = 0xB7B77;
#endif
	while (!stop) {
		cmd=Byte(ea);
		if(cmd&0x80) {
			tmp0=Byte(ea+1);
			size = 2;
			if(tmp0==1)
				size++;
			if(tmp0==0)
				stop=1;
		} else {
			size = 5;
			tmp0=Byte(flags_ea+cmd);
			if(tmp0&0x80)
				size++;
			if(tmp0&0x40)
				size++;
			if(tmp0&0x20)
				size++;
		}
		ea = make_data_array(ea, size, "");
	}
}

static main(void) {
#ifdef AUTO
	Message("AUTO DECOMPILATION START\n");

#if REGION==REGION_JP
	ngb2_opcode(0x00008000,"",-2);	// _scr0
	ngb2_opcode(0x0000801F,"",-2);	// _scr0/SW A
	ngb2_opcode(0x00008140,"",-2);	// _scr0/select buster
	ngb2_opcode(0x00008146,"",-2);	// _scr0/secret menu
	ngb2_opcode(0x00008A7B,"",-2);	// _scr0/unref
	ngb2_opcode(0x00008D29,"",-2);	// _scr0/unreachable sloc -1
	ngb2_opcode(0x00008D88,"",-2);	// _scr0/unreachable sloc A
	ngb2_opcode(0x00008DA0,"",-2);	// _scr0/unreachable sloc B
	ngb2_opcode(0x00008E4F,"",-2);	// _scr0/unreachable sloc Ba
	ngb2_opcode(0x00008E55,"",-2);	// _scr0/unreachable sloc C
	ngb2_opcode(0x00008F6A,"",-2);	// _scr0/skip to title
	ngb2_opcode(0x00009287,"",-2);	// _scr7
	ngb2_opcode(0x000092BA,"",-2);	// _scr7/SW A
	ngb2_opcode(0x0000935F,"",-2);	// _scr_935F

	ngb2_opcode(0x00014000,"",-2);	// _scr1
	ngb2_opcode(0x0001422B,"",-2);	// _scr1/SW back A
	ngb2_opcode(0x0001437F,"",-2);	// _scr2
	ngb2_opcode(0x00014811,"",-2);	// _scr3
	ngb2_opcode(0x00015180,"",-2);	// _scr4
	ngb2_opcode(0x00015573,"",-2);	// _scr5
	ngb2_opcode(0x00015D44,"",-2);	// _scr6
	ngb2_opcode(0x00015F56,"",-2);	// _scr_15F56
	ngb2_opcode(0x00016111,"",-2);	// _scr_16111
	ngb2_opcode(0x00016162,"",-2);	// _scr_16111/unreachable sloc A
	ngb2_opcode(0x00016257,"",-2);	// _scrC
	ngb2_opcode(0x00016945,"",-2);	// _scrD

	ngb2_opcode(0x0002C000,"",-2);	// _scr1A
	ngb2_opcode(0x0002C009,"",-2);	// _scr1A/unreachable sloc A
	ngb2_opcode(0x0002C014,"",-2);	// _scr1A/unreachable sloc B
	ngb2_opcode(0x0002C06C,"",-2);	// _scr_2C06C
	ngb2_opcode(0x0002C089,"",-2);	// _scr_2C089
	ngb2_opcode(0x0002C0BF,"",-2);	// _scr_2C0BF
	ngb2_opcode(0x0002C0C5,"",-2);	// _scr_2C0C5
	ngb2_opcode(0x0002C160,"",-2);	// _scr_/SW UP A
	ngb2_opcode(0x0002C17C,"",-2);	// _scr_/SW UP B
	ngb2_opcode(0x0002C198,"",-2);	// _scr_/SW UP C
	ngb2_opcode(0x0002C1CE,"",-2);	// _scr_2C1CE
	ngb2_opcode(0x0002C228,"",-2);	// _scr_/unreachable SW
	ngb2_opcode(0x0002C233,"",-2);	// _scr_2C233
	ngb2_opcode(0x0002C649,"",-2);	// _scr22
	ngb2_opcode(0x0002C658,"",-2);	// _scr22/SW UP A
	ngb2_opcode(0x0002C698,"",-2);	// _scr_2C698
	ngb2_opcode(0x0002C6D0,"",-2);	// _scr_2C6D0
	ngb2_opcode(0x0002C6D9,"",-2);	// _scr_2C6D9
	ngb2_opcode(0x0002C982,"",-2);	// _scr2E
	ngb2_opcode(0x0002C98D,"",-2);	// _scr2E/unreachable SW
	ngb2_opcode(0x0002CA40,"",-2);	// _scr_2CA40
	ngb2_opcode(0x0002CA66,"",-2);	// _scr_2CA40/unreachable sloc A
	ngb2_opcode(0x0002CA9B,"",-2);	// _scr_2CA9B
	ngb2_opcode(0x0002CAA1,"",-2);	// _scr_2CAA1
	ngb2_opcode(0x0002CF0B,"",-2);	// _scr_2CAA1/unreachable SW A
	ngb2_opcode(0x0002CF6B,"",-2);	// _scr_2CAA1/unreachable SW B
	ngb2_opcode(0x0002CF89,"",-2);	// _scr_2CAA1/unreachable sloc A
	ngb2_opcode(0x0002CFD9,"",-2);	// _scr_2CAA1/unreachable sloc B
	ngb2_opcode(0x0002CFE3,"",-2);	// _scr_2CAA1/unreachable sloc C
	ngb2_opcode(0x0002D002,"",-2);	// _scr_2CAA1/unreachable sloc D
	ngb2_opcode(0x0002D02E,"",-2);	// _scr_2CAA1/unreachable sloc E
	ngb2_opcode(0x0002D05C,"",-2);	// _scr_2CAA1/unreachable sloc F
	ngb2_opcode(0x0002D08A,"",-2);	// _scr_2CAA1/unreachable sloc G
	ngb2_opcode(0x0002D0B8,"",-2);	// _scr_2CAA1/unreachable sloc H
	ngb2_opcode(0x0002D103,"",-2);	// _scr_2CAA1/unreachable sloc I
	ngb2_opcode(0x0002D0D6,"",-2);	// _scr_2D0D6
	ngb2_opcode(0x0002D122,"",-2);	// _scr_2D122
	ngb2_opcode(0x0002D139,"",-2);	// _scr_2D139
	ngb2_opcode(0x0002CEFC,"",-2);	// _scr2F
	ngb2_opcode(0x0002D8C8,"",-2);	// _scr30
	ngb2_opcode(0x0002D8D7,"",-2);	// _scr30/unreachable SW A
	ngb2_opcode(0x0002D9A1,"",-2);	// _scr30/unreachable SW B
	ngb2_opcode(0x0002D9BC,"",-2);	// _scr_2D9BC

	ngb2_opcode(0x00038000,"",-2);	// _scr13
	ngb2_opcode(0x00038068,"",-2);	// _scr_38068
	ngb2_opcode(0x00038096,"",-2);	// _scr_38096
	ngb2_opcode(0x0003809C,"",-2);	// _scr_3809C
	ngb2_opcode(0x00038237,"",-2);	// _scr14
	ngb2_opcode(0x00038282,"",-2);	// _scr_38382
	ngb2_opcode(0x000382C3,"",-2);	// _scr15
	ngb2_opcode(0x000382CC,"",-2);	// _scr15/unreachable SW A
	ngb2_opcode(0x000382EB,"",-2);	// _scr_382EB
	ngb2_opcode(0x00038353,"",-2);	// _scr16
	ngb2_opcode(0x0003835C,"",-2);	// _scr16/unreachable SW A
	ngb2_opcode(0x00038381,"",-2);	// _scr_38381
	ngb2_opcode(0x00038435,"",-2);	// _scr1B
	ngb2_opcode(0x000385B2,"",-2);	// _scr1D
	ngb2_opcode(0x000385D4,"",-2);	// _scr_385D4
	ngb2_opcode(0x000385F6,"",-2);	// _scr_385F6
	ngb2_opcode(0x000385FC,"",-2);	// _scr_385FC
	ngb2_opcode(0x000386DF,"",-2);	// _scr1E
	ngb2_opcode(0x0003873C,"",-2);	// _scr_3873C
	ngb2_opcode(0x00038966,"",-2);	// _scr1F
	ngb2_opcode(0x000389C3,"",-2);	// _scr_389C3
	ngb2_opcode(0x00038C2D,"",-2);	// _scrE
	ngb2_opcode(0x00038C46,"",-2);	// _scrE/unreachable sloc A
	ngb2_opcode(0x00038D13,"",-2);	// _scr20
	ngb2_opcode(0x00038D2C,"",-2);	// _scr20/unreachable sloc A
	ngb2_opcode(0x00038D3D,"",-2);	// _scr_38D4B/SW UP
	ngb2_opcode(0x00038D4B,"",-2);	// _scr_38D4B
	ngb2_opcode(0x00038ED9,"",-2);	// _scr21
	ngb2_opcode(0x00038EE2,"",-2);	// _scr21/unreachable SW
	ngb2_opcode(0x00038F51,"",-2);	// _scr_38F51
	ngb2_opcode(0x00038F79,"",-2);	// _scr_38F79
	ngb2_opcode(0x00038F7F,"",-2);	// _scr_38F7F
	ngb2_opcode(0x000390FD,"",-2);	// _scr2B
	ngb2_opcode(0x00039106,"",-2);	// _scr2B/unreachable SW A
	ngb2_opcode(0x00039132,"",-2);	// _scr_39132
	ngb2_opcode(0x0003925F,"",-2);	// _scr2C
	ngb2_opcode(0x00039268,"",-2);	// _scr2C/unreachable SW A
	ngb2_opcode(0x000392BE,"",-2);	// _scr_392BE
	ngb2_opcode(0x00039452,"",-2);	// _scr23
	ngb2_opcode(0x000394A8,"",-2);	// _scr_394A8
	ngb2_opcode(0x000396E2,"",-2);	// _scr24
	ngb2_opcode(0x0003974F,"",-2);	// _scr24/unreachable SW A
	ngb2_opcode(0x000399D1,"",-2);	// _scr25
	ngb2_opcode(0x000399DA,"",-2);	// _scr25/unreachable SW A
	ngb2_opcode(0x00039A04,"",-2);	// _scr_39A04
	ngb2_opcode(0x00039CCE,"",-2);	// _scr26
	ngb2_opcode(0x00039D43,"",-2);	// _scr_39D43
	ngb2_opcode(0x00039F96,"",-2);	// _scr27
	ngb2_opcode(0x00039F9F,"",-2);	// _scr27/unreachable SW A
	ngb2_opcode(0x00039FEE,"",-2);	// _scr_39FEE
	ngb2_opcode(0x0003A155,"",-2);	// _scr28
	ngb2_opcode(0x0003A1E4,"",-2);	// _scr_3A1E4
	ngb2_opcode(0x0003A2D0,"",-2);	// _scr29
	ngb2_opcode(0x0003A2D9,"",-2);	// _scr29/unreachable SW A
	ngb2_opcode(0x0003A32B,"",-2);	// _scr29/SW UP A
	ngb2_opcode(0x0003A340,"",-2);	// _scr_3A340
	ngb2_opcode(0x0003A362,"",-2);	// _scr_3A362
	ngb2_opcode(0x0003A386,"",-2);	// _scr_3A386
	ngb2_opcode(0x0003A38C,"",-2);	// _scr_3A38C
	ngb2_opcode(0x0003A392,"",-2);	// _scr_3A392
	ngb2_opcode(0x0003A398,"",-2);	// _scr_3A398
	ngb2_opcode(0x0003A551,"",-2);	// _scr2D
	ngb2_opcode(0x0003A720,"",-2);	// _scrF
	ngb2_opcode(0x0003A729,"",-2);	// _scrF/unreachable SW A
	ngb2_opcode(0x0003A777,"",-2);	// _scr10
	ngb2_opcode(0x0003A8FF,"",-2);	// _scr17
	ngb2_opcode(0x0003A909,"",-2);	// _scr_3A909
	ngb2_opcode(0x0003A918,"",-2);	// _scr_3A909/unreachable SW A
	ngb2_opcode(0x0003A978,"",-2);	// _scr_3A978
	ngb2_opcode(0x0003A9AD,"",-2);	// _scr_3A9AD
	ngb2_opcode(0x0003A9A7,"",-2);	// _scr_3A9A7
	ngb2_opcode(0x0003A5B5,"",-2);	// _scr_3A5B5
	ngb2_opcode(0x0003A5D7,"",-2);	// _scr_3A5D7
	ngb2_opcode(0x0003A5DD,"",-2);	// _scr_3A5DD
	ngb2_opcode(0x0003AC39,"",-2);	// _scr18
	ngb2_opcode(0x0003ACB4,"",-2);	// _scr_3ACB4
	ngb2_opcode(0x0003ACDE,"",-2);	// _scr_3ACDE
	ngb2_opcode(0x0003ACE4,"",-2);	// _scr_3ACE4
	ngb2_opcode(0x0003AFDB,"",-2);	// _scr19
	ngb2_opcode(0x0003B01D,"",-2);	// _scr_3B01D
	ngb2_opcode(0x0003B03F,"",-2);	// _scr_3B03F
	ngb2_opcode(0x0003B045,"",-2);	// _scr_3B045
	ngb2_opcode(0x0003B204,"",-2);	// _scr2A
	ngb2_opcode(0x0003B20D,"",-2);	// _scr2A/unreachable SW A
	ngb2_opcode(0x0003B255,"",-2);	// _scr_3B255
	ngb2_opcode(0x0003B275,"",-2);	// _scr_3B275
	ngb2_opcode(0x0003B27B,"",-2);	// _scr_3B27B
	ngb2_opcode(0x0003B600,"",-2);	// _scr1C
	ngb2_opcode(0x0003B60D,"",-2);	// _scr1C/unreachable SW A
	ngb2_opcode(0x0003B65D,"",-2);	// _scr_3B65D
	ngb2_opcode(0x0003B687,"",-2);	// _scr_3B687
	ngb2_opcode(0x0003B68D,"",-2);	// _scr_3B68D
	ngb2_opcode(0x0003B693,"",-2);	// _scr_3B693
	ngb2_opcode(0x0003B755,"",-2);	// _scr_3B755
	ngb2_opcode(0x0003BA93,"",-2);	// _scr_3BA93
	ngb2_opcode(0x0003BABD,"",-2);	// _scr_3BABD
	ngb2_opcode(0x0003BAC3,"",-2);	// _scr_3BAC3
	ngb2_opcode(0x0003BB89,"",-2);	// _scr11
	ngb2_opcode(0x0003BB94,"",-2);	// _scr11/unreachable SW A

	ngb2_opcode(0x000601F7,"",-2);	// _scr12
	ngb2_opcode(0x0006027E,"",-2);	// _scr8
	ngb2_opcode(0x0006029B,"",-2);	// _scr8/unreachable sloc A
	ngb2_opcode(0x0006029F,"",-2);	// _scr_hit_anim
	ngb2_opcode(0x000602CB,"",-2);	// _scr_602CB
	ngb2_opcode(0x000602DB,"",-2);	// _scr_602DB
	ngb2_opcode(0x000602EE,"",-2);	// _scr_602EE
	ngb2_opcode(0x00060306,"",-2);	// _scr_60306
	ngb2_opcode(0x00060C82,"",-2);	// _scr9
	ngb2_opcode(0x00060C91,"",-2);	// _scr_60C91
	ngb2_opcode(0x00060FB3,"",-2);	// _scrA
	ngb2_opcode(0x00060FCB,"",-2);	// _scr_60FCB
	ngb2_opcode(0x00060FDB,"",-2);	// _scr_60FDB
	ngb2_opcode(0x00060FEE,"",-2);	// _scr_60FEE
	ngb2_opcode(0x0006134E,"",-2);	// _scrB
	ngb2_opcode(0x00061365,"",-2);	// _scr_61365
#endif

#if REGION==REGION_EU
	ngb2_opcode(0x00008000,"",-2);	// _scr0
	ngb2_opcode(0x0000801F,"",-2);	// _scr0/SW A
	ngb2_opcode(0x00008140,"",-2);	// _scr0/select buster
	ngb2_opcode(0x00008146,"",-2);	// _scr0/secret menu
	ngb2_opcode(0x00008A7B,"",-2);	// _scr0/unref
	ngb2_opcode(0x00008D29,"",-2);	// _scr0/unreachable sloc -1
	ngb2_opcode(0x00008D88,"",-2);	// _scr0/unreachable sloc A
	ngb2_opcode(0x00008DA0,"",-2);	// _scr0/unreachable sloc B
	ngb2_opcode(0x00008E4F,"",-2);	// _scr0/unreachable sloc Ba
	ngb2_opcode(0x00008E55,"",-2);	// _scr0/unreachable sloc C
	ngb2_opcode(0x00008F6A,"",-2);	// _scr0/skip to title
	ngb2_opcode(0x00009287,"",-2);	// _scr7
	ngb2_opcode(0x000092BA,"",-2);	// _scr7/SW A
	ngb2_opcode(0x0000935F,"",-2);	// _scr_935F

	ngb2_opcode(0x00020000,"",-2);	// _scr1
	ngb2_opcode(0x00020229,"",-2);	// _scr1/SW back A
	ngb2_opcode(0x0002037D,"",-2);	// _scr2
	ngb2_opcode(0x0002080F,"",-2);	// _scr3
	ngb2_opcode(0x0002117E,"",-2);	// _scr4
	ngb2_opcode(0x0002156F,"",-2);	// _scr5
	ngb2_opcode(0x00021D34,"",-2);	// _scr6
	ngb2_opcode(0x00021F46,"",-2);	// _scr_15F56
	ngb2_opcode(0x00022101,"",-2);	// _scr_16111
	ngb2_opcode(0x00022152,"",-2);	// _scr_16111/unreachable sloc A
	ngb2_opcode(0x00022247,"",-2);	// _scrC
	ngb2_opcode(0x00022935,"",-2);	// _scrD

	ngb2_opcode(0x00050000,"",-2);	// _scr1A
	ngb2_opcode(0x00050009,"",-2);	// _scr1A/unreachable sloc A
	ngb2_opcode(0x00050014,"",-2);	// _scr1A/unreachable sloc B
	ngb2_opcode(0x0005006C,"",-2);	// _scr_2C06C
	ngb2_opcode(0x00050089,"",-2);	// _scr_2C089
	ngb2_opcode(0x000500BF,"",-2);	// _scr_2C0BF
	ngb2_opcode(0x000500C5,"",-2);	// _scr_2C0C5
	ngb2_opcode(0x00050160,"",-2);	// _scr_/SW UP A
	ngb2_opcode(0x0005017C,"",-2);	// _scr_/SW UP B
	ngb2_opcode(0x00050198,"",-2);	// _scr_/SW UP C
	ngb2_opcode(0x000501CE,"",-2);	// _scr_2C1CE
	ngb2_opcode(0x00050228,"",-2);	// _scr_/unreachable SW
	ngb2_opcode(0x00050233,"",-2);	// _scr_2C233
	ngb2_opcode(0x00050649,"",-2);	// _scr22
	ngb2_opcode(0x00050658,"",-2);	// _scr22/SW UP A
	ngb2_opcode(0x00050698,"",-2);	// _scr_2C698
	ngb2_opcode(0x000506D0,"",-2);	// _scr_2C6D0
	ngb2_opcode(0x000506D9,"",-2);	// _scr_2C6D9
	ngb2_opcode(0x00050982,"",-2);	// _scr2E
	ngb2_opcode(0x0005098D,"",-2);	// _scr2E/unreachable SW
	ngb2_opcode(0x00050A40,"",-2);	// _scr_2CA40
	ngb2_opcode(0x00050A66,"",-2);	// _scr_2CA40/unreachable sloc A
	ngb2_opcode(0x00050A9B,"",-2);	// _scr_2CA9B
	ngb2_opcode(0x00050AA1,"",-2);	// _scr_2CAA1
	ngb2_opcode(0x00050F0B,"",-2);	// _scr_2CAA1/unreachable SW A
	ngb2_opcode(0x00050F6B,"",-2);	// _scr_2CAA1/unreachable SW B
	ngb2_opcode(0x00050F89,"",-2);	// _scr_2CAA1/unreachable sloc A
	ngb2_opcode(0x00050FD9,"",-2);	// _scr_2CAA1/unreachable sloc B
	ngb2_opcode(0x00050FE3,"",-2);	// _scr_2CAA1/unreachable sloc C
	ngb2_opcode(0x00051002,"",-2);	// _scr_2CAA1/unreachable sloc D
	ngb2_opcode(0x0005102E,"",-2);	// _scr_2CAA1/unreachable sloc E
	ngb2_opcode(0x0005105C,"",-2);	// _scr_2CAA1/unreachable sloc F
	ngb2_opcode(0x0005108A,"",-2);	// _scr_2CAA1/unreachable sloc G
	ngb2_opcode(0x000510B8,"",-2);	// _scr_2CAA1/unreachable sloc H
	ngb2_opcode(0x00051103,"",-2);	// _scr_2CAA1/unreachable sloc I
	ngb2_opcode(0x000510D6,"",-2);	// _scr_2D0D6
	ngb2_opcode(0x00051122,"",-2);	// _scr_2D122
	ngb2_opcode(0x00051139,"",-2);	// _scr_2D139
	ngb2_opcode(0x00050EFC,"",-2);	// _scr2F
	ngb2_opcode(0x000518C8,"",-2);	// _scr30
	ngb2_opcode(0x000518D7,"",-2);	// _scr30/unreachable SW A
	ngb2_opcode(0x000519A1,"",-2);	// _scr30/unreachable SW B
	ngb2_opcode(0x000519BC,"",-2);	// _scr_2D9BC

	ngb2_opcode(0x00068000,"",-2);	// _scr13
	ngb2_opcode(0x00068068,"",-2);	// _scr_38068
	ngb2_opcode(0x00068096,"",-2);	// _scr_38096
	ngb2_opcode(0x0006809C,"",-2);	// _scr_3809C
	ngb2_opcode(0x00068237,"",-2);	// _scr14
	ngb2_opcode(0x00068282,"",-2);	// _scr_38382
	ngb2_opcode(0x000682C3,"",-2);	// _scr15
	ngb2_opcode(0x000682CC,"",-2);	// _scr15/unreachable SW A
	ngb2_opcode(0x000682EB,"",-2);	// _scr_382EB
	ngb2_opcode(0x00068353,"",-2);	// _scr16
	ngb2_opcode(0x0006835C,"",-2);	// _scr16/unreachable SW A
	ngb2_opcode(0x00068381,"",-2);	// _scr_38381
	ngb2_opcode(0x00068435,"",-2);	// _scr1B
	ngb2_opcode(0x000685B2,"",-2);	// _scr1D
	ngb2_opcode(0x000685D4,"",-2);	// _scr_385D4
	ngb2_opcode(0x000685F6,"",-2);	// _scr_385F6
	ngb2_opcode(0x000685FC,"",-2);	// _scr_385FC
	ngb2_opcode(0x000686DF,"",-2);	// _scr1E
	ngb2_opcode(0x0006873C,"",-2);	// _scr_3873C
	ngb2_opcode(0x00068966,"",-2);	// _scr1F
	ngb2_opcode(0x000689C3,"",-2);	// _scr_389C3
	ngb2_opcode(0x00068C2D,"",-2);	// _scrE
	ngb2_opcode(0x00068C46,"",-2);	// _scrE/unreachable sloc A
	ngb2_opcode(0x00068D13,"",-2);	// _scr20
	ngb2_opcode(0x00068D2C,"",-2);	// _scr20/unreachable sloc A
	ngb2_opcode(0x00068D3D,"",-2);	// _scr_38D4B/SW UP
	ngb2_opcode(0x00068D4B,"",-2);	// _scr_38D4B
	ngb2_opcode(0x00068ED9,"",-2);	// _scr21
	ngb2_opcode(0x00068EE2,"",-2);	// _scr21/unreachable SW
	ngb2_opcode(0x00068F51,"",-2);	// _scr_38F51
	ngb2_opcode(0x00068F79,"",-2);	// _scr_38F79
	ngb2_opcode(0x00068F7F,"",-2);	// _scr_38F7F
	ngb2_opcode(0x000690FD,"",-2);	// _scr2B
	ngb2_opcode(0x00069106,"",-2);	// _scr2B/unreachable SW A
	ngb2_opcode(0x00069132,"",-2);	// _scr_39132
	ngb2_opcode(0x0006925F,"",-2);	// _scr2C
	ngb2_opcode(0x00069268,"",-2);	// _scr2C/unreachable SW A
	ngb2_opcode(0x000692BE,"",-2);	// _scr_392BE
	ngb2_opcode(0x00069452,"",-2);	// _scr23
	ngb2_opcode(0x000694A8,"",-2);	// _scr_394A8
	ngb2_opcode(0x000696E2,"",-2);	// _scr24
	ngb2_opcode(0x0006974F,"",-2);	// _scr24/unreachable SW A
	ngb2_opcode(0x000699D1,"",-2);	// _scr25
	ngb2_opcode(0x000699DA,"",-2);	// _scr25/unreachable SW A
	ngb2_opcode(0x00069A04,"",-2);	// _scr_39A04
	ngb2_opcode(0x00069CCE,"",-2);	// _scr26
	ngb2_opcode(0x00069D43,"",-2);	// _scr_39D43
	ngb2_opcode(0x00069F96,"",-2);	// _scr27
	ngb2_opcode(0x00069F9F,"",-2);	// _scr27/unreachable SW A
	ngb2_opcode(0x00069FEE,"",-2);	// _scr_39FEE
	ngb2_opcode(0x0006A155,"",-2);	// _scr28
	ngb2_opcode(0x0006A1E4,"",-2);	// _scr_3A1E4
	ngb2_opcode(0x0006A2D0,"",-2);	// _scr29
	ngb2_opcode(0x0006A2D9,"",-2);	// _scr29/unreachable SW A
	ngb2_opcode(0x0006A32B,"",-2);	// _scr29/SW UP A
	ngb2_opcode(0x0006A340,"",-2);	// _scr_3A340
	ngb2_opcode(0x0006A362,"",-2);	// _scr_3A362
	ngb2_opcode(0x0006A386,"",-2);	// _scr_3A386
	ngb2_opcode(0x0006A38C,"",-2);	// _scr_3A38C
	ngb2_opcode(0x0006A392,"",-2);	// _scr_3A392
	ngb2_opcode(0x0006A398,"",-2);	// _scr_3A398
	ngb2_opcode(0x0006A551,"",-2);	// _scr2D
	ngb2_opcode(0x0006A720,"",-2);	// _scrF
	ngb2_opcode(0x0006A729,"",-2);	// _scrF/unreachable SW A
	ngb2_opcode(0x0006A777,"",-2);	// _scr10
	ngb2_opcode(0x0006A8FF,"",-2);	// _scr17
	ngb2_opcode(0x0006A909,"",-2);	// _scr_3A909
	ngb2_opcode(0x0006A918,"",-2);	// _scr_3A909/unreachable SW A
	ngb2_opcode(0x0006A978,"",-2);	// _scr_3A978
	ngb2_opcode(0x0006A9AD,"",-2);	// _scr_3A9AD
	ngb2_opcode(0x0006A9A7,"",-2);	// _scr_3A9A7
	ngb2_opcode(0x0006A5B5,"",-2);	// _scr_3A5B5
	ngb2_opcode(0x0006A5D7,"",-2);	// _scr_3A5D7
	ngb2_opcode(0x0006A5DD,"",-2);	// _scr_3A5DD
	ngb2_opcode(0x0006AC39,"",-2);	// _scr18
	ngb2_opcode(0x0006ACB4,"",-2);	// _scr_3ACB4
	ngb2_opcode(0x0006ACDE,"",-2);	// _scr_3ACDE
	ngb2_opcode(0x0006ACE4,"",-2);	// _scr_3ACE4
	ngb2_opcode(0x0006AFDB,"",-2);	// _scr19
	ngb2_opcode(0x0006B01D,"",-2);	// _scr_3B01D
	ngb2_opcode(0x0006B03F,"",-2);	// _scr_3B03F
	ngb2_opcode(0x0006B045,"",-2);	// _scr_3B045
	ngb2_opcode(0x0006B204,"",-2);	// _scr2A
	ngb2_opcode(0x0006B20D,"",-2);	// _scr2A/unreachable SW A
	ngb2_opcode(0x0006B255,"",-2);	// _scr_3B255
	ngb2_opcode(0x0006B275,"",-2);	// _scr_3B275
	ngb2_opcode(0x0006B27B,"",-2);	// _scr_3B27B
	ngb2_opcode(0x0006B600,"",-2);	// _scr1C
	ngb2_opcode(0x0006B60D,"",-2);	// _scr1C/unreachable SW A
	ngb2_opcode(0x0006B65D,"",-2);	// _scr_3B65D
	ngb2_opcode(0x0006B687,"",-2);	// _scr_3B687
	ngb2_opcode(0x0006B68D,"",-2);	// _scr_3B68D
	ngb2_opcode(0x0006B693,"",-2);	// _scr_3B693
	ngb2_opcode(0x0006B755,"",-2);	// _scr_3B755
	ngb2_opcode(0x0006BA93,"",-2);	// _scr_3BA93
	ngb2_opcode(0x0006BABD,"",-2);	// _scr_3BABD
	ngb2_opcode(0x0006BAC3,"",-2);	// _scr_3BAC3
	ngb2_opcode(0x0006BB89,"",-2);	// _scr11
	ngb2_opcode(0x0006BB94,"",-2);	// _scr11/unreachable SW A

	ngb2_opcode(0x000B41F8,"",-2);	// _scr12
	ngb2_opcode(0x000B427F,"",-2);	// _scr8
	ngb2_opcode(0x000B429C,"",-2);	// _scr8/unreachable sloc A
	ngb2_opcode(0x000B42A0,"",-2);	// _scr_hit_anim
	ngb2_opcode(0x000B42CC,"",-2);	// _scr_602CB
	ngb2_opcode(0x000B42DC,"",-2);	// _scr_602DB
	ngb2_opcode(0x000B42EF,"",-2);	// _scr_602EE
	ngb2_opcode(0x000B4307,"",-2);	// _scr_60306
	ngb2_opcode(0x000B4C83,"",-2);	// _scr9
	ngb2_opcode(0x000B4C92,"",-2);	// _scr_60C91
	ngb2_opcode(0x000B4FB4,"",-2);	// _scrA
	ngb2_opcode(0x000B4FCC,"",-2);	// _scr_60FCB
	ngb2_opcode(0x000B4FDC,"",-2);	// _scr_60FDB
	ngb2_opcode(0x000B4FEF,"",-2);	// _scr_60FEE
	ngb2_opcode(0x000B534F,"",-2);	// _scrB
	ngb2_opcode(0x000B5366,"",-2);	// _scr_61365
#endif

#if REGION==REGION_US
	ngb2_opcode(0x00008000,"",-2);	// _scr0
	ngb2_opcode(0x0000801F,"",-2);	// _scr0/SW A
	ngb2_opcode(0x00008140,"",-2);	// _scr0/select buster
	ngb2_opcode(0x00008146,"",-2);	// _scr0/secret menu
	ngb2_opcode(0x00008A7B,"",-2);	// _scr0/unref
	ngb2_opcode(0x00008D29,"",-2);	// _scr0/unreachable sloc -1
	ngb2_opcode(0x00008D88,"",-2);	// _scr0/unreachable sloc A
	ngb2_opcode(0x00008DA0,"",-2);	// _scr0/unreachable sloc B
	ngb2_opcode(0x00008E4F,"",-2);	// _scr0/unreachable sloc Ba
	ngb2_opcode(0x00008E55,"",-2);	// _scr0/unreachable sloc C
	ngb2_opcode(0x00008F6A,"",-2);	// _scr0/skip to title

	ngb2_opcode(0x00009287,"",-2);	// _scr7
	ngb2_opcode(0x000092BA,"",-2);	// _scr7/SW A
	ngb2_opcode(0x0000935F,"",-2);	// _scr_935F

	ngb2_opcode(0x00020000,"",-2);	// _scr1
	ngb2_opcode(0x00020229,"",-2);	// _scr1/SW back A
	ngb2_opcode(0x0002037D,"",-2);	// _scr2
	ngb2_opcode(0x0002080F,"",-2);	// _scr3
	ngb2_opcode(0x0002117E,"",-2);	// _scr4
	ngb2_opcode(0x0002156F,"",-2);	// _scr5
	ngb2_opcode(0x00021D34,"",-2);	// _scr6
	ngb2_opcode(0x00021F46,"",-2);	// _scr_15F56
	ngb2_opcode(0x00022101,"",-2);	// _scr_16111
	ngb2_opcode(0x00022152,"",-2);	// _scr_16111/unreachable sloc A
	ngb2_opcode(0x00022247,"",-2);	// _scrC
	ngb2_opcode(0x00022935,"",-2);	// _scrD

	ngb2_opcode(0x00050000,"",-2);	// _scr1A
	ngb2_opcode(0x00050009,"",-2);	// _scr1A/unreachable sloc A
	ngb2_opcode(0x00050014,"",-2);	// _scr1A/unreachable sloc B
	ngb2_opcode(0x0005006C,"",-2);	// _scr_2C06C
	ngb2_opcode(0x00050089,"",-2);	// _scr_2C089
	ngb2_opcode(0x000500BF,"",-2);	// _scr_2C0BF
	ngb2_opcode(0x000500C5,"",-2);	// _scr_2C0C5
	ngb2_opcode(0x00050160,"",-2);	// _scr_/SW UP A
	ngb2_opcode(0x0005017C,"",-2);	// _scr_/SW UP B
	ngb2_opcode(0x00050198,"",-2);	// _scr_/SW UP C
	ngb2_opcode(0x000501CE,"",-2);	// _scr_2C1CE
	ngb2_opcode(0x00050228,"",-2);	// _scr_/unreachable SW
	ngb2_opcode(0x00050233,"",-2);	// _scr_2C233
	ngb2_opcode(0x00050649,"",-2);	// _scr22
	ngb2_opcode(0x00050658,"",-2);	// _scr22/SW UP A
	ngb2_opcode(0x00050698,"",-2);	// _scr_2C698
	ngb2_opcode(0x000506D0,"",-2);	// _scr_2C6D0
	ngb2_opcode(0x000506D9,"",-2);	// _scr_2C6D9
	ngb2_opcode(0x00050982,"",-2);	// _scr2E
	ngb2_opcode(0x0005098D,"",-2);	// _scr2E/unreachable SW
	ngb2_opcode(0x00050A40,"",-2);	// _scr_2CA40
	ngb2_opcode(0x00050A66,"",-2);	// _scr_2CA40/unreachable sloc A
	ngb2_opcode(0x00050A9B,"",-2);	// _scr_2CA9B
	ngb2_opcode(0x00050AA1,"",-2);	// _scr_2CAA1
	ngb2_opcode(0x00050F0B,"",-2);	// _scr_2CAA1/unreachable SW A
	ngb2_opcode(0x00050F6B,"",-2);	// _scr_2CAA1/unreachable SW B
	ngb2_opcode(0x00050F89,"",-2);	// _scr_2CAA1/unreachable sloc A
	ngb2_opcode(0x00050FD9,"",-2);	// _scr_2CAA1/unreachable sloc B
	ngb2_opcode(0x00050FE3,"",-2);	// _scr_2CAA1/unreachable sloc C
	ngb2_opcode(0x00051002,"",-2);	// _scr_2CAA1/unreachable sloc D
	ngb2_opcode(0x0005102E,"",-2);	// _scr_2CAA1/unreachable sloc E
	ngb2_opcode(0x0005105C,"",-2);	// _scr_2CAA1/unreachable sloc F
	ngb2_opcode(0x0005108A,"",-2);	// _scr_2CAA1/unreachable sloc G
	ngb2_opcode(0x000510B8,"",-2);	// _scr_2CAA1/unreachable sloc H
	ngb2_opcode(0x00051103,"",-2);	// _scr_2CAA1/unreachable sloc I
	ngb2_opcode(0x000510D6,"",-2);	// _scr_2D0D6
	ngb2_opcode(0x00051122,"",-2);	// _scr_2D122
	ngb2_opcode(0x00051139,"",-2);	// _scr_2D139
	ngb2_opcode(0x00050EFC,"",-2);	// _scr2F
	ngb2_opcode(0x000518C8,"",-2);	// _scr30
	ngb2_opcode(0x000518D7,"",-2);	// _scr30/unreachable SW A
	ngb2_opcode(0x000519A1,"",-2);	// _scr30/unreachable SW B
	ngb2_opcode(0x000519BC,"",-2);	// _scr_2D9BC

	ngb2_opcode(0x00068000,"",-2);	// _scr13
	ngb2_opcode(0x00068068,"",-2);	// _scr_38068
	ngb2_opcode(0x00068096,"",-2);	// _scr_38096
	ngb2_opcode(0x0006809C,"",-2);	// _scr_3809C
	ngb2_opcode(0x00068237,"",-2);	// _scr14
	ngb2_opcode(0x00068282,"",-2);	// _scr_38382
	ngb2_opcode(0x000682C3,"",-2);	// _scr15
	ngb2_opcode(0x000682CC,"",-2);	// _scr15/unreachable SW A
	ngb2_opcode(0x000682EB,"",-2);	// _scr_382EB
	ngb2_opcode(0x00068353,"",-2);	// _scr16
	ngb2_opcode(0x0006835C,"",-2);	// _scr16/unreachable SW A
	ngb2_opcode(0x00068381,"",-2);	// _scr_38381
	ngb2_opcode(0x00068435,"",-2);	// _scr1B
	ngb2_opcode(0x000685B2,"",-2);	// _scr1D
	ngb2_opcode(0x000685D4,"",-2);	// _scr_385D4
	ngb2_opcode(0x000685F6,"",-2);	// _scr_385F6
	ngb2_opcode(0x000685FC,"",-2);	// _scr_385FC
	ngb2_opcode(0x000686DF,"",-2);	// _scr1E
	ngb2_opcode(0x0006873C,"",-2);	// _scr_3873C
	ngb2_opcode(0x00068966,"",-2);	// _scr1F
	ngb2_opcode(0x000689C3,"",-2);	// _scr_389C3
	ngb2_opcode(0x00068C2D,"",-2);	// _scrE
	ngb2_opcode(0x00068C46,"",-2);	// _scrE/unreachable sloc A
	ngb2_opcode(0x00068D13,"",-2);	// _scr20
	ngb2_opcode(0x00068D2C,"",-2);	// _scr20/unreachable sloc A
	ngb2_opcode(0x00068D3D,"",-2);	// _scr_38D4B/SW UP
	ngb2_opcode(0x00068D4B,"",-2);	// _scr_38D4B
	ngb2_opcode(0x00068ED9,"",-2);	// _scr21
	ngb2_opcode(0x00068EE2,"",-2);	// _scr21/unreachable SW
	ngb2_opcode(0x00068F51,"",-2);	// _scr_38F51
	ngb2_opcode(0x00068F79,"",-2);	// _scr_38F79
	ngb2_opcode(0x00068F7F,"",-2);	// _scr_38F7F
	ngb2_opcode(0x000690FD,"",-2);	// _scr2B
	ngb2_opcode(0x00069106,"",-2);	// _scr2B/unreachable SW A
	ngb2_opcode(0x00069132,"",-2);	// _scr_39132
	ngb2_opcode(0x0006925F,"",-2);	// _scr2C
	ngb2_opcode(0x00069268,"",-2);	// _scr2C/unreachable SW A
	ngb2_opcode(0x000692BE,"",-2);	// _scr_392BE
	ngb2_opcode(0x00069452,"",-2);	// _scr23
	ngb2_opcode(0x000694A8,"",-2);	// _scr_394A8
	ngb2_opcode(0x000696E2,"",-2);	// _scr24
	ngb2_opcode(0x0006974F,"",-2);	// _scr24/unreachable SW A
	ngb2_opcode(0x000699D1,"",-2);	// _scr25
	ngb2_opcode(0x000699DA,"",-2);	// _scr25/unreachable SW A
	ngb2_opcode(0x00069A04,"",-2);	// _scr_39A04
	ngb2_opcode(0x00069CCE,"",-2);	// _scr26
	ngb2_opcode(0x00069D43,"",-2);	// _scr_39D43
	ngb2_opcode(0x00069F96,"",-2);	// _scr27
	ngb2_opcode(0x00069F9F,"",-2);	// _scr27/unreachable SW A
	ngb2_opcode(0x00069FEE,"",-2);	// _scr_39FEE
	ngb2_opcode(0x0006A155,"",-2);	// _scr28
	ngb2_opcode(0x0006A1E4,"",-2);	// _scr_3A1E4
	ngb2_opcode(0x0006A2D0,"",-2);	// _scr29
	ngb2_opcode(0x0006A2D9,"",-2);	// _scr29/unreachable SW A
	ngb2_opcode(0x0006A32B,"",-2);	// _scr29/SW UP A
	ngb2_opcode(0x0006A340,"",-2);	// _scr_3A340
	ngb2_opcode(0x0006A362,"",-2);	// _scr_3A362
	ngb2_opcode(0x0006A386,"",-2);	// _scr_3A386
	ngb2_opcode(0x0006A38C,"",-2);	// _scr_3A38C
	ngb2_opcode(0x0006A392,"",-2);	// _scr_3A392
	ngb2_opcode(0x0006A398,"",-2);	// _scr_3A398
	ngb2_opcode(0x0006A551,"",-2);	// _scr2D
	ngb2_opcode(0x0006A720,"",-2);	// _scrF
	ngb2_opcode(0x0006A729,"",-2);	// _scrF/unreachable SW A
	ngb2_opcode(0x0006A777,"",-2);	// _scr10
	ngb2_opcode(0x0006A8FF,"",-2);	// _scr17
	ngb2_opcode(0x0006A909,"",-2);	// _scr_3A909
	ngb2_opcode(0x0006A918,"",-2);	// _scr_3A909/unreachable SW A
	ngb2_opcode(0x0006A978,"",-2);	// _scr_3A978
	ngb2_opcode(0x0006A9AD,"",-2);	// _scr_3A9AD
	ngb2_opcode(0x0006A9A7,"",-2);	// _scr_3A9A7
	ngb2_opcode(0x0006A5B5,"",-2);	// _scr_3A5B5
	ngb2_opcode(0x0006A5D7,"",-2);	// _scr_3A5D7
	ngb2_opcode(0x0006A5DD,"",-2);	// _scr_3A5DD
	ngb2_opcode(0x0006AC39,"",-2);	// _scr18
	ngb2_opcode(0x0006ACB4,"",-2);	// _scr_3ACB4
	ngb2_opcode(0x0006ACDE,"",-2);	// _scr_3ACDE
	ngb2_opcode(0x0006ACE4,"",-2);	// _scr_3ACE4
	ngb2_opcode(0x0006AFDB,"",-2);	// _scr19
	ngb2_opcode(0x0006B01D,"",-2);	// _scr_3B01D
	ngb2_opcode(0x0006B03F,"",-2);	// _scr_3B03F
	ngb2_opcode(0x0006B045,"",-2);	// _scr_3B045
	ngb2_opcode(0x0006B204,"",-2);	// _scr2A
	ngb2_opcode(0x0006B20D,"",-2);	// _scr2A/unreachable SW A
	ngb2_opcode(0x0006B255,"",-2);	// _scr_3B255
	ngb2_opcode(0x0006B275,"",-2);	// _scr_3B275
	ngb2_opcode(0x0006B27B,"",-2);	// _scr_3B27B
	ngb2_opcode(0x0006B600,"",-2);	// _scr1C
	ngb2_opcode(0x0006B60D,"",-2);	// _scr1C/unreachable SW A
	ngb2_opcode(0x0006B65D,"",-2);	// _scr_3B65D
	ngb2_opcode(0x0006B687,"",-2);	// _scr_3B687
	ngb2_opcode(0x0006B68D,"",-2);	// _scr_3B68D
	ngb2_opcode(0x0006B693,"",-2);	// _scr_3B693
	ngb2_opcode(0x0006B755,"",-2);	// _scr_3B755
	ngb2_opcode(0x0006BA93,"",-2);	// _scr_3BA93
	ngb2_opcode(0x0006BABD,"",-2);	// _scr_3BABD
	ngb2_opcode(0x0006BAC3,"",-2);	// _scr_3BAC3
	ngb2_opcode(0x0006BB89,"",-2);	// _scr11
	ngb2_opcode(0x0006BB94,"",-2);	// _scr11/unreachable SW A

	ngb2_opcode(0x000B41F7,"",-2);	// _scr12
	ngb2_opcode(0x000B427E,"",-2);	// _scr8
	ngb2_opcode(0x000B429B,"",-2);	// _scr8/unreachable sloc A
	ngb2_opcode(0x000B429F,"",-2);	// _scr_hit_anim
	ngb2_opcode(0x000B42CB,"",-2);	// _scr_602CB
	ngb2_opcode(0x000B42DB,"",-2);	// _scr_602DB
	ngb2_opcode(0x000B42EE,"",-2);	// _scr_602EE
	ngb2_opcode(0x000B4306,"",-2);	// _scr_60306
	ngb2_opcode(0x000B4C82,"",-2);	// _scr9
	ngb2_opcode(0x000B4C91,"",-2);	// _scr_60C91
	ngb2_opcode(0x000B4FAE,"",-2);	// _scrA
	ngb2_opcode(0x000B4FC6,"",-2);	// _scr_60FCB
	ngb2_opcode(0x000B4FD6,"",-2);	// _scr_60FDB
	ngb2_opcode(0x000B4FE9,"",-2);	// _scr_60FEE
	ngb2_opcode(0x000B5349,"",-2);	// _scrB
	ngb2_opcode(0x000B5360,"",-2);	// _scr_61365
#endif

	Message("AUTO DECOMPILATION END\n");
#else
	AddHotkey("Shift-O", "ngb2_script_selection");
#endif

#ifdef AUTO
#if REGION==REGION_JP
	ngb2_apu_auto(0x5342D,49,0);
	ngb2_apu_auto(0x53345,92,1);
#endif
#if REGION==REGION_EU
	ngb2_apu_auto(0x9B4B0,49,0);
	ngb2_apu_auto(0x9B398,92,1);
#endif
#if REGION==REGION_US
	ngb2_apu_auto(0x9B42D,49,0);
	ngb2_apu_auto(0x9B345,92,1);
#endif
#if REGION==KIRBY_US_0
	kirby_apu_auto(0x2E2991,0x2E29CB,0x2E2A05,58,"_mus%02X",0);
	kirby_apu_auto(0x2E2A3F,0x2E2A97,-1,88,"_snd%02X",0);
	kirby_apu_auto(0x2E28B1,-1,-1,82,"_sample%02X",1);
#endif
#endif

	AddHotkey("Shift-I", "ngb2_apu_selection");
//	AddHotkey("Shift-I", "ngb2_enemy_data_parse");
}
