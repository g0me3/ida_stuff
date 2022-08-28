
#include <idc.idc>
#include <functions.idc>

// ======main control flags=======
//#define DEBUG

#define MAKE_CODE
#define MAKE_OFFSETS
#define MAKE_NAMES
//	#define FORBID_OFFSETS_BC
//	#define FORBID_OFFSETS_DE
//	#define FORBID_OFFSETS_HL
//#define MAKE_CODE_UNK
//#define MAKE_CODE_UNK_BYTE
//#define MAKE_DATA_BYTE
//#define MARK_UNUSED
//#define CLEAR_UNUSED
#define MMC_PRG_SET_DETECT
#define MMC_PRG_PROC_DETECT
#define SWITCH_DETECT_A
#define SWITCH_DETECT_B
#define MMC_DEFAULT_BANK 1
#define MMC_DEFAULT_BANK_CALL 1

// ========MMC control values========
#define PRG_CMD_SIZE 10

//#define MMC_SET_OFS0 0x0D1D
//#define MMC_SET_OFS1 0x0189
//#define MMC_RESTORE0_OFS 0x0D17
//#define MMC_RESTORE1_OFS 0x0308

#define MMC_SET_OPC0 0xEF
//#define MMC_SET_OPC1 0xCF
#define MMC_RESTORE_OPC 0xF7

//#define MMC_PRG1_OPC 0xF7
//#define MMC_PRG2_OPC 0xC7
//#define MMC_PRG3_OPC 0xC7
//#define MMC_PRG4_OPC 0xC7
//#define MMC_PRG5_OPC 0xC7
//#define MMC_PRG6_OPC 0xC7
//#define MMC_PRG7_OPC 0xC7
//#define MMC_PRGF_OPC 0xCF

//#define MMC_PRG_INCREMENT 5
//#define MMC_PRG1_PROC 0x3FD9
//#define MMC_PRG2_PROC 0x0AAC //MMC_PRG1_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG3_PROC 0x3FEB //MMC_PRG2_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG4_PROC 0x3FAD //MMC_PRG3_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG5_PROC 0x3FA4 //MMC_PRG4_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG6_PROC 0x3F9B //MMC_PRG5_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG7_PROC 0x3F92 //MMC_PRG6_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG8_PROC MMC_PRG7_PROC+MMC_PRG_INCREMENT
//#define MMC_PRG9_PROC MMC_PRG8_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGA_PROC MMC_PRG9_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGB_PROC MMC_PRGA_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGC_PROC MMC_PRGB_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGD_PROC MMC_PRGC_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGE_PROC MMC_PRGD_PROC+MMC_PRG_INCREMENT
//#define MMC_PRGF_PROC MMC_PRGE_PROC+MMC_PRG_INCREMENT

// =======manual switch opcodes======
#define SWITCH_OPC 0xC7
//#define SWITCH_OFS 0x005C

//#define CUSTOM_TABLE_JUMP0 "21 ?? ?? C3 0D 02"
//#define CUSTOM_TABLE_JUMP_OFS0 1

//#define CUSTOM_TABLE_JUMP1 "21 ?? ?? C3 7C 03"
//#define CUSTOM_TABLE_JUMP_OFS1 1

//#define CUSTOM_TABLE_JUMP2 "21 ?? ?? CD DA 11 CD 9C 14"
//#define CUSTOM_TABLE_JUMP_OFS2 1

//#define CUSTOM_TABLE_JUMP3 "21 ?? ?? CD 78 01 CD 90 01"
//#define CUSTOM_TABLE_JUMP_OFS3 1

// ====manual farcall parameters=====
//#define FARCALL_OPCA 0xDF
//#define FARCALL_BOFSA -1
//#define FARCALL_WOFSA -2
//#define FARCALL_SIZEA 3
//#define FARCALL_PARAMA
//#define FARCALL_EXECA
//#define FARCALL_SYSA
//#define FARCALL_SYSOFSA 0x4001
//#define FARCALL_PARAM_SIZEA

//#define FARCALL_OPCB 0xE7
//#define FARCALL_BOFSB 5
//#define FARCALL_WOFSB 1
//#define FARCALL_SIZEB 5
//#define FARCALL_PARAMB
//#define FARCALL_EXECB
//#define FARCALL_SYSB
//#define FARCALL_SYSOFSB  0x4001

//#define FARCALL_OPCC 0xCF
//#define FARCALL_BOFSC 1
//#define FARCALL_WOFSC 1
//#define FARCALL_SIZEC 1
//#define FARCALL_PARAMC
//#define FARCALL_EXECC
//#define FARCALL_SYSC
//#define FARCALL_SYSOFSC  0x4001

//#define FARCALL_OFS0 0x0036
//#define FARCALL_BOFS0 -4
//#define FARCALL_WOFS0 -2
//#define FARCALL_SYS0
//#define FARCALL_SYSOFS0  0x4001
//#define FARCALL_SIZE0 3
//#define FARCALL_PARAM0
//#define FARCALL_PARAM_SIZE0

//#define FARCALL_OFS1 0x0CA2
//#define FARCALL_BOFS1 -4
//#define FARCALL_WOFS1 -2
//#define FARCALL_SYS1
//#define FARCALL_SYSOFS1  0x400F
//#define FARCALL_SIZE1 8
//#define FARCALL_PARAM1

//#define FARCALL_OFS1 0x0540
//#define FARCALL_BOFS1 5
//#define FARCALL_WOFS1 3
//#define FARCALL_SIZE1 3
//#define FARCALL_PARAM1

//#define FARCALL_BOFS -4
//#define FARCALL_BOFS_OPC 0x3E
//#define FARCALL_WOFS -2
//#define FARCALL_WOFS_OPC 0x21

//#define FARCALL_OFS0 0x0B27
//#define FARCALL_8BIT0
//#define FARCALL_BOFS0 -1
//#define FARCALL_WOFS_LO0 -5
//#define FARCALL_WOFS_HI0 -3

//#define FARCALL_OFS1 0x0B27
//#define FARCALL_8BIT1
//#define FARCALL_BOFS1 -1
//#define FARCALL_WOFS_LO1 -3
//#define FARCALL_WOFS_HI1 -5

// ====manual farofs parameters=====

///*
#define FPRN0	"21 ?? ?? 11 ?? ?? 3E ?? CD"
#define FPRN0_B 7
#define FPRN0_W 1
#define FPRN0_C 0

#define FPRN1	"3E ?? 21 ?? ?? 11 ?? ?? CD"
#define FPRN1_B	1
#define FPRN1_W	3
#define FPRN1_C	0

#define FPRN2	"3E ?? 01 ?? ?? 21 ?? ?? 11 ?? ?? CD"
#define FPRN2_B	1
#define FPRN2_W	6
#define FPRN2_C	0

#define FPRN3	"21 ?? ?? 11 ?? ?? 01 ?? ?? 3E ?? CD"
#define FPRN3_B	10
#define FPRN3_W	1
#define FPRN3_C	0
//*/

#define FPRN4	"11 ?? ?? CD C4 45"
#define FPRN4_B	-3
#define FPRN4_W	1
#define FPRN4_C	0

//#define FPRN5	"11 ?? ?? 21 ?? ?? 01 ?? ?? ?? DB 05"
//#define FPRN5_B	8
//#define FPRN5_W	4
//#define FPRN5_C	0

//#define FPRN6	"3E ?? 21 ?? ?? 11 ?? ?? 01 ?? ?? CD 1C 03"
//#define FPRN6_B	1
//#define FPRN6_W	3
//#define FPRN6_C	0

//#define FPRN7	"21 ?? ?? 06 ?? 0E ?? CD C8 18"
//#define FPRN7_B	-4
//#define FPRN7_W	1
//#define FPRN7_C	0

//#define FPRN8	"21 ?? ?? 11 ?? ?? 01 ?? ?? 3E ?? E0 ?? 3E ?? E0 ?? 3E ?? CD 39 0A"
//#define FPRN8_B	18
//#define FPRN8_W	1
//#define FPRN8_C	0

//#define FPRN9	"3E ?? E0 ?? 21 ?? ?? 11 ?? ?? 01 ?? ?? CD B3 0A"
//#define FPRN9_B	1
//#define FPRN9_W	5
//#define FPRN9_C	0

//#define FPRNA	"21 ?? ?? CD 98 29"
//#define FPRNA_B	-3
//#define FPRNA_W	1
//#define FPRNA_C	0

//#define FPRN0B	"21 C1 C0 3E ?? 22 36 ?? 3E ?? FF"
//#define FPRN0B_B	9
//#define FPRN0_WL	4
//#define FPRN0_WH	7

//#define FPRN0B	"3E ?? E0 ?? 3E ?? E0 93 3E ?? E0 94"
//#define FPRN0B_B	1
//#define FPRN0_WL	5
//#define FPRN0_WH	9

// ====custom farofs parameters=====c
//#define CUSTOM_PATTERN0	"3E ?? EA 14 C3 3E ?? EA 15 C3 3E ??"
//#define CUSTOM_PATTERN0_MODE 4
//#define CUSTOM_PATTERN0_B	-1
//#define CUSTOM_PATTERN0_W	-1
//#define CUSTOM_PATTERN0_ARG0 -1

//#define CUSTOM_PATTERN1	"3E ?? 21 ?? ?? ?? C0 0B"
//#define CUSTOM_PATTERN1_MODE 11
//#define CUSTOM_PATTERN1_B	 1
//#define CUSTOM_PATTERN1_W	 3
//#define CUSTOM_PATTERN1_ARG0 -1

// ========parametric patterns=======
//#define PARAMETRIC_OPC0 0xE7
//#define PARAMETRIC_SIZE0 1
//#define PARAMETRIC_OPC1 0xD7
//#define PARAMETRIC_SIZE1 4
//#define PARAMETRIC_OPC2 0xEF
//#define PARAMETRIC_SIZE2 4
//#define PARAMETRIC_OPC3 0xE7
//#define PARAMETRIC_SIZE3 4

//#define PARAMETRIC_OFS0 0x1213
//#define PARAMETRIC_OSIZE0 2
//#define PARAMETRIC_OFS1 0x2531
//#define PARAMETRIC_OSIZE1 1
//#define PARAMETRIC_OFS2 0x041F
//#define PARAMETRIC_OSIZE2 1
//#define PARAMETRIC_OFS3 0x13D8
//#define PARAMETRIC_OSIZE3 2
//#define PARAMETRIC_OFS4 0x7A18
//#define PARAMETRIC_OSIZE4 3
//#define PARAMETRIC_OFS5 0x796C
//#define PARAMETRIC_OSIZE5 3
//#define PARAMETRIC_OFS6 0x79E6
//#define PARAMETRIC_OSIZE6 1
//#define PARAMETRIC_OFS7 0x7986
//#define PARAMETRIC_OSIZE7 4

static make_new_comment(ea, cmnt) {
	auto curcmnt = CommentEx(ea, 0);
	if(curcmnt == "")
		MakeComm(ea, form("new %s", cmnt));
	else
		MakeComm(ea, cmnt);
}

static code_patterns(void) {
	auto cnt;

	find_pads("EA ?? ?? 3E 30 E0 00 FA ?? ?? ?? 79 A0 A8 EA"	,1,	8,	2,	15,	2);
	find_pads("F0 ?? A8 A0 E0 ?? 78 E0"							,1,	8,	1,	5,	1);
	find_pads("F0 ?? A9 A1 E0 ?? 79 E0"							,1,	8,	1,	5,	1);
	find_pads("F0 ?? A9 A1 E0 ?? ?? ?? ?? ?? 79 E0"				,1,	12,	1,	5,	1);
	find_pads("FA ?? ?? A0 A8 EA ?? ?? 78 EA"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? A8 A0 E0 ?? 78 EA"						,1,	9,	2,	6,	1);
	find_pads("FA ?? ?? A8 A0 EA ?? ?? 78 EA"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? A9 A1 EA ?? ?? 79 EA"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? 2F A1 EA ?? ?? 79 EA"					,1,	10,	2,	6,	2);
//	find_pads("F0 ?? A9 A1 E9 8B 79 E0 ?? E0"

	find_code("C5 3E 20 E0 00 F0 00 F0 00 2F E6 0F",				"_read_pad");
	find_code("3E 20 E0 00 F0 00 F0 00 2F E6 0F",					"_read_pad");
	find_code("3E 20 E0 00 F0 00 F0 00 F0 00 2F E6 0F",				"_read_pad");
	find_code("0E 00 3E 20 E2 F2 F2 F2 47 3E 10 E2",				"_read_pad");
	find_code("0E 00 3E 20 E2 F2 F2 E6 0F CB 37 47 3E 10 E2",		"_read_pad");
	find_code("F3 0E 00 3E 20 E2 F2 F2 2F",							"_read_pad");

	find_code("22 0D 20 FC 05 20 F9 C9",							"_memset");
	find_code("22 0D 20 FC C9",										"_memset");
	find_code("22 05 20 FC C9",										"_memset");
	find_code("22 1B BA 20 FB BB 20 F8 C9",							"_memset");
	find_code("22 57 0B 78 B1 7A 20 F8 C9",							"_memset");
	find_code("72 23 0B 78 B1 20 F9 C9",							"_memset");
	find_code("F5 D5 5F 73 23 0B 79 B0 20 F9 D1 F1 C9",				"_memset");

	find_code("2A 12 13 05 20 FA C9",								"_memcpy");
	find_code("2A 12 13 0B 78 B1 20 F8 C9",							"_memcpy");
	find_code("2A 12 13 0B 79 B0 20 F8 C9",							"_memcpy");
	find_code("2A 12 13 0D 20 FA C9",								"_memcpy");
	find_code("1A 22 13 05 20 FA C9",								"_memcpy");
	find_code("1A 22 13 0D 20 FA C9",								"_memcpy");
	find_code("1A 22 13 0B 78 B1 20 F8 C9",							"_memcpy");
	find_code("F5 2A 12 13 05 20 FA F1 C9",							"_memcpy");
	find_code("F5 2A 12 13 0B 79 B0 20 F8 F1 C9",					"_memcpy");

	find_code("3E 00 22 0B 79 B0 20 F8 C9",							"_zeromem");
	find_code("AF 22 05 20 FC C9",									"_zeromem");
	find_code("16 00 72 23 0B 78 B1 20 F9 C9",						"_zeromem");
	find_code("AF 12 13 05 20 FB C9",								"_zeromem");
	find_code("AF 22 0B 79 B0 20 F9 C9",							"_zeromem");
	find_code("AF 22 1B BA 20 FB BB 20 F8 C9",						"_zeromem");
	find_code("AF 22 0B 78 B1 20 F9 C9",							"_zeromem");
	find_code("AF F5 D5 5F 73 23 0B 79 B0 20 F9 D1 F1 C9",			"_zeromem");

	find_code("76 FA ?? ?? A7 28 F9 AF EA ?? ?? C9",				"_wait_for_nmi");
	find_code("AF EA ?? ?? 76 FA ?? ?? B7 28 F9 C9",				"_wait_for_nmi");

	find_code("81 4F D0 04 C9",										"_bc_add_a");
	find_code("83 5F D0 14 C9",										"_de_add_a");
	find_code("85 6F D0 24 C9",										"_hl_add_a");
	find_code("85 6F 8C 95 67 C9",									"_hl_add_a");
	find_code("85 6F 3E 00 8C 67 C9",								"_hl_add_a");
	find_code("87 5F 16 00 19 2A 66 6F C9",							"_hl_add_a");
	find_code("C5 06 00 4F 09 C1 C9",								"_hl_add_a");

	find_code("D5 5F 16 00 CB 23 CB 12 19 5E 23 56 62 6B D1 C9",	"_hl_add_a_mul2_get_ptr_hl");
	find_code("D5 5F 16 00 CB 23 CB 12 19 5E 23 66 6B D1 C9",		"_hl_add_a_mul2_get_ptr_hl");
	find_code("87 ?? 2A 66 6F C9",									"_hl_add_a_mul2_get_ptr_hl");
	find_code("87 85 6F 30 01 24 2A 66 6F C9",						"_hl_add_a_mul2_get_ptr_hl");
	find_code("87 85 6F 3E 00 8C 67 2A 66 6F C9",					"_hl_add_a_mul2_get_ptr_hl");
	find_code("4F 06 00 CB 21 CB 10 09 2A 66 6F C9",				"_hl_add_a_mul2_get_ptr_hl");

	find_code("21 ?? ?? CD ?? ?? CD ?? ?? F0 00",					"_sgb_detect");
	find_code("7E E6 07 C8 47 0E 00 C5 3E 00 E2 3E 30 E2 06 10",	"_sgb_cmd");
	find_code("11 58 1B 00 00 00 1B 7A B3 20 F8 C9",				"_sgb_delay1B58");
	find_code("11 D6 06 00 00 00 1B 7A B3 20 F8 0B 78 B1 20 F0 C9",	"_sgb_delay6D6");

	find_code("0E 80 06 0A 21 ?? ?? 2A E2 0C 05 20 FA C9",			"_ram_dma_sub_init");
	find_code("3E ?? E0 46 3E 28 3D 20 FD C9",						"_ram_dma_sub_data");

	find_code("F0 40 E6 80 28 0C F0 44 FE 91 20 FA F0 40 E6 7F E0 40 C9", "_render_off");
	find_code("F0 44 FE 91 20 FA F0 40 CB BF E0 40",                "_render_off");

	cnt = 0;

// custom 8-bit far offset for tamagotchi 3
//	cnt = find_far_8bit_offset_patterns("2E ?? 26 ?? 3E ?? CD E1 07",1,3,5,cnt);
// ren & stimpy veediots
//	cnt = find_far_8bit_offset_patterns("3E ?? E0 8E 3E ?? E0 8F 3E ?? E0 90",1,5,9,cnt);
//	cnt = find_far_8bit_offset_patterns("3E ?? E0 8F 3E ?? E0 90 3E ?? E0 91",1,5,9,cnt);
//	cnt = find_far_8bit_offset_patterns("3E ?? E0 A9 3E ?? E0 AA 21 ?? ??",1,5,10,cnt);
// real bout special
//	cnt = find_far_8bit_offset_patterns("19 36 ?? 23 36 ?? 23 36 ??",5,8,2,cnt);

#ifdef FPRN0
	cnt = find_far_offset_patterns(FPRN0, FPRN0_B, FPRN0_W, FPRN0_C, cnt);
#endif
#ifdef FPRN0B
	cnt = find_far_offset_patterns_8b(FPRN0B, FPRN0B_B, FPRN0_WL, FPRN0_WH, cnt);
#endif
#ifdef FPRN1
	cnt = find_far_offset_patterns(FPRN1, FPRN1_B, FPRN1_W, FPRN1_C, cnt);
#endif
#ifdef FPRN2
	cnt = find_far_offset_patterns(FPRN2, FPRN2_B, FPRN2_W, FPRN2_C, cnt);
#endif
#ifdef FPRN3
	cnt = find_far_offset_patterns(FPRN3, FPRN3_B, FPRN3_W, FPRN3_C, cnt);
#endif
#ifdef FPRN4
	cnt = find_far_offset_patterns(FPRN4, FPRN4_B, FPRN4_W, FPRN4_C, cnt);
#endif
#ifdef FPRN5
	cnt = find_far_offset_patterns(FPRN5, FPRN5_B, FPRN5_W, FPRN5_C, cnt);
#endif
#ifdef FPRN6
	cnt = find_far_offset_patterns(FPRN6, FPRN6_B, FPRN6_W, FPRN6_C, cnt);
#endif
#ifdef FPRN7
	cnt = find_far_offset_patterns(FPRN7, FPRN7_B, FPRN7_W, FPRN7_C, cnt);
#endif
#ifdef FPRN8
	cnt = find_far_offset_patterns(FPRN8, FPRN8_B, FPRN8_W, FPRN8_C, cnt);
#endif
#ifdef FPRN9
	cnt = find_far_offset_patterns(FPRN9, FPRN9_B, FPRN9_W, FPRN9_C, cnt);
#endif
#ifdef FPRNA
	cnt = find_far_offset_patterns(FPRNA, FPRNA_B, FPRNA_W, FPRNA_C, cnt);
#endif
#ifdef FPRNB
	cnt = find_far_offset_patterns(FPRNB, FPRNB_B, FPRNB_W, FPRNB_C, cnt);
#endif
#ifdef FPRNC
	cnt = find_far_offset_patterns(FPRNC, FPRNC_B, FPRNC_W, FPRNC_C, cnt);
#endif
#ifdef FPRND
	cnt = find_far_offset_patterns(FPRND, FPRND_B, FPRND_W, FPRND_C, cnt);
#endif
#ifdef FPRNE
	cnt = find_far_offset_patterns(FPRNE, FPRNE_B, FPRNE_W, FPRNE_C, cnt);
#endif
#ifdef FPRNF
	cnt = find_far_offset_patterns(FPRNF, FPRNF_B, FPRNF_W, FPRNF_C, cnt);
#endif
	if(cnt>0)
		Message("far offset patterns summary: %d has found\n",cnt);

#ifdef CUSTOM_PATTERN0
	find_custom_patterns(CUSTOM_PATTERN0, CUSTOM_PATTERN0_B, CUSTOM_PATTERN0_W, CUSTOM_PATTERN0_ARG0, CUSTOM_PATTERN0_MODE);
#endif

#ifdef CUSTOM_PATTERN1
	find_custom_patterns(CUSTOM_PATTERN1, CUSTOM_PATTERN1_B, CUSTOM_PATTERN1_W, CUSTOM_PATTERN1_ARG0, CUSTOM_PATTERN1_MODE);
#endif

#ifdef	CUSTOM_TABLE_JUMP0
	cnt = find_table_jumps(CUSTOM_TABLE_JUMP0,CUSTOM_TABLE_JUMP_OFS0,cnt);
#endif
#ifdef	CUSTOM_TABLE_JUMP1
	cnt = find_table_jumps(CUSTOM_TABLE_JUMP1,CUSTOM_TABLE_JUMP_OFS1,cnt);
#endif
#ifdef	CUSTOM_TABLE_JUMP2
	cnt = find_table_jumps(CUSTOM_TABLE_JUMP2,CUSTOM_TABLE_JUMP_OFS2,cnt);
#endif
#ifdef	CUSTOM_TABLE_JUMP3
	cnt = find_table_jumps(CUSTOM_TABLE_JUMP3,CUSTOM_TABLE_JUMP_OFS3,cnt);
#endif

#ifdef SWITCH_DETECT_A
	cnt = 0;

	cnt = find_table_jumps("01 ?? ?? 09 2A 66 6F E9",					1, cnt);
	cnt = find_table_jumps("01 ?? ?? F0 ?? 6F 26 00 29 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("06 00 21 ?? ?? 09 09 2A 66 6F E9", 			3, cnt);
//	cnt = find_table_jumps("06 00 4F CB 21 21 ?? ?? 09 2A 66 6F E9", 	6, cnt);
//	cnt = find_table_jumps("07 4F 06 00 21 ?? ?? 09 2A 66 6F E9",		5, cnt);
	cnt = find_table_jumps("11 ?? ?? 19 11 ?? ?? D5 2A 66 6F E9", 		1, cnt);
	cnt = find_table_jumps("11 ?? ?? 19 2A 66 6F E9",					1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 4F 09 09 2A 66 6F E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 4F CB 21 CB 10 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 FA ?? ?? 4F CB 21 CB 10 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 07 85 6F 30 01 24 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F 01 ?? ?? C5 E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F E9", 					1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F FA ?? ?? 4F 06 00 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 4E 23 46 69 60 E9",				1, cnt);
//	cnt = find_table_jumps("21 ?? ?? 09 54 5D 62 6B 2A 66 6F E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 7E 23 66 6F E9",				1, cnt);
	cnt = find_table_jumps("21 ?? ?? 16 00 87 5F 19 5E 23 66 6B D1 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 19 2A 47 7E 67 68 E9", 			1, cnt);
	cnt = find_table_jumps("21 ?? ?? 19 2A 66 6F 11 ?? ?? D5 E9",		1, cnt);
//	cnt = find_table_jumps("21 ?? ?? 19 2A 66 6F E9", 					1, cnt);		// portal runner use this pattern in a different way
	cnt = find_table_jumps("21 ?? ?? 85 6F 30 01 24 5E 23 56 D5 E1 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 87 4F 06 00 09 2A 66 6F E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 87 85 30 01 24 6F 2A 66 6F E9", 	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 87 85 6F 3E 00 8C 67 2A 66 6F E9", 1, cnt);
//	cnt = find_table_jumps("21 ?? ?? ?? 0F 3E",		                    1, cnt);	// Nanotone custom table jump
//	cnt = find_table_jumps("21 ?? ?? CF",		                        1, cnt);	// Evangelion
	cnt = find_table_jumps("21 ?? ?? FA ?? ?? 87 4F 06 00 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? FA ?? ?? CB 27 4F 06 00 09 2A 66 6F E9",    1, cnt);
//	cnt = find_table_jumps("4A CB 21 06 00 21 ?? ?? 09 2A 66 6F E9",	6, cnt);
	cnt = find_table_jumps("4F 06 00 21 ?? ?? 09 09 2A 66 6F C9",		4, cnt);
//	cnt = find_table_jumps("4F 06 00 21 ?? ?? 09 2A 66 6F E9", 			4, cnt);
	cnt = find_table_jumps("4F 21 ?? ?? 09 2A 66 6F 11 ?? ?? D5 E9",	2, cnt);
//	cnt = find_table_jumps("4F 21 ?? ?? 09 2A 66 6F E9",				2, cnt);
//	cnt = find_table_jumps("4F CB 21 06 00 21 ?? ?? 09 2A 66 6F E9", 	6, cnt);
	cnt = find_table_jumps("5F 16 00 21 ?? ?? 19 19 2A 66 6F E9",		4, cnt);
	cnt = find_table_jumps("5F 21 ?? ?? 19 2A 66 6F 01 ?? ?? C5 E9",	2, cnt);
	cnt = find_table_jumps("5F CB 23 16 00 21 ?? ?? 19 5E 23 56 D5 C9", 6, cnt);
	cnt = find_table_jumps("87 06 00 4F 21 ?? ?? 09 2A 66 6F E5 C9",	5, cnt);
	cnt = find_table_jumps("87 21 ?? ?? 5F 16 00 19 2A 66 6F E9", 		2, cnt);
	cnt = find_table_jumps("87 21 ?? ?? 85 30 01 24 6F 2A 66 6F E9", 	2, cnt);
	cnt = find_table_jumps("87 21 ?? ?? 85 6F 30 01 24 2A 66 6F E9", 	2, cnt);
	cnt = find_table_jumps("87 21 ?? ?? CD ?? ?? 2A 66 6F E9", 			2, cnt);
//	cnt = find_table_jumps("87 4F 06 00 21 ?? ?? 09 2A 66 6F E9", 		5, cnt);
	cnt = find_table_jumps("87 4F 06 00 21 ?? ?? 09 4E 23 46 C5 E1 E9",	5, cnt);
	cnt = find_table_jumps("87 5F 16 00 21 ?? ?? 19 2A 56 6F 62 E9",	5, cnt);
	cnt = find_table_jumps("87 5F 16 00 21 ?? ?? 19 5E 23 56 D5 E1 E9", 5, cnt);
	cnt = find_table_jumps("87 6F 26 00 01 ?? ?? 09 2A 66 6F ?? ?? ?? ?? E9", 	5, cnt);
//	cnt = find_table_jumps("87 6F 26 00 01 ?? ?? 09 2A 66 6F E9", 		5, cnt);
	cnt = find_table_jumps("87 6F 26 00 11 ?? ?? 19 2A 66 6F ?? ?? ?? ?? ?? E9", 		5, cnt);
//	cnt = find_table_jumps("87 6F 26 00 11 ?? ?? 19 2A 66 6F E9",		5, cnt);
	cnt = find_table_jumps("87 C5 4F 06 00 21 ?? ?? 09 C1 2A 66 6F E9", 6, cnt);
//	cnt = find_table_jumps("CB 21 21 ?? ?? 09 2A 66 6F E9",			    3, cnt);
//	cnt = find_table_jumps("CB 25 11 ?? ?? 19 2A 66 6F E9",				3, cnt);
	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 2A 47 7E 67 68 E9", 	6, cnt);
//	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 2A 66 6F E9",	6, cnt);
	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 4E 23 46 E1 C5 C9",	6, cnt);
//	cnt = find_table_jumps("CB 27 6F AF 67 01 ?? ?? 09 2A 66 6F E9",	6, cnt);
	cnt = find_table_jumps("E5 16 00 21 ?? ?? 19 5E 23 56 E1 D5 C9",	4, cnt);
	cnt = find_table_jumps("F5 21 ?? ?? 19 2A 66 6F F1 E9",				2, cnt);
	cnt = find_table_jumps("FA ?? ?? 21 ?? ?? 16 00 5F CB 23 CB 12 19 2A 66 6F E9",	4, cnt);

	cnt = find_table_jumps_8bit("C6 ?? 6F 7C CE ?? 67 2A 66 6F E9",1,5,cnt);
	cnt = find_table_jumps_8bit("C6 ?? 5F 7A CE ?? 57 62 6B 2A 66 6F E9",1,5,cnt);
	cnt = find_table_jumps_8bit("C6 ?? 4F 78 CE ?? 47 60 69 2A 66 6F E9",1,5,cnt);
	cnt = find_table_jumps_8bit("87 C6 ?? 6F 3E 00 CE ?? 67 2A 66 6F E9",2,7,cnt);
	cnt = find_table_jumps_8bit("C6 ?? 6F 3E ?? CE 00 67 2A 66 6F E9",1,4,cnt);
	cnt = find_table_jumps_8bit("87 C6 ?? 6F CE ?? 95 67 2A 66 6F E9",2,5,cnt);

	if(cnt>0)
		Message("table jumps summary: %d has found\n",cnt);
#endif
}

static main(void) {
	auto cdlFileName, cdlFile, cdlFileOpened, extPos, idbFileName = GetIdbPath();
	auto i, j, cd, seg = 0;
	auto segea, segeai, segorg, secondpass = 0;
	auto codelog = 0, datalog = 0, unusedlog = 0;
	auto opcode, optype, opvalue;
	auto banksnum = 0, curbank = -1, prebank = -1, preea = -1, bankflag = 0;
	auto ctype = Byte(0x0147);
	auto prgset = BADADDR, switchptr = BADADDR, switchopc = -1;
	auto farcall_cnt = 0, switch_cnt = 0, param_cnt = 0;
	auto farcall_s = 0, switch_es = 0, param_s = 0;
	auto farcall_cnt_prev = 0, switch_cnt_prev = 0, param_cnt_prev = 0, result = 0;
	auto ass0, ass1;

#ifdef MMC_DEFAULT_BANK
	curbank = MMC_DEFAULT_BANK;
#endif

#ifdef MMC_DEFAULT_BANK_CALL
	curbank = MMC_DEFAULT_BANK_CALL;
#endif

#ifdef MAKE_NAMES
	MakeNames();
#endif

	extPos = strstr(idbFileName, ".idb");
	cdlFileName = substr(idbFileName, 0, extPos) + ".cdl";
	cdlFile = fopen(cdlFileName, "rb");
	if( cdlFile == 0 ) {
		cdlFileName = AskFile(0,"*.cdl","Choose a CDL-file Manually");
		cdlFile = fopen(cdlFileName, "rb");
	}
	if (cdlFile != 0) {
		auto cdlSignature = "", cdlType = "", cdlFiles=0;
		fgetc(cdlFile);														// skip 0D
		for(i=0; i<13; i++) cdlSignature = cdlSignature + fgetc(cdlFile);	// read signature
		fgetc(cdlFile);														// skip 0F
		for(i=0; i<15; i++) cdlType = cdlType + fgetc(cdlFile);				// read type
		for(i=0; i<4; i++) cdlFiles = cdlFiles | (fgetc(cdlFile)<<(i*8));	// read files count
		if ((cdlSignature == "BIZHAWK-CDL-2")&&((cdlType == "GB             ")||(cdlType == "SNES           "))) {
			Message("CDL file opened succesfully.\n\tName:    \"%s\"\n\tVersion: \"%s\"\n\tType:    \"%s\"\n\tChunks:  %d\n", cdlFileName,cdlSignature,cdlType,cdlFiles);
			if(cdlType == "SNES           ")
				result=cdl_chunk_search(cdlFile, "SGB_CARTROM", cdlFiles);
			else
				result=cdl_chunk_search(cdlFile, "ROM", cdlFiles);
			if(result == -1) {
				Message("Can't find proper Data chunk\nStartig disassembly without CDL.\n", cdlFileName);
				cdlFileOpened = 0;
			} else
				cdlFileOpened = 1;
		} else {
			Message("CDL file not in GB format (%s, %s)!\nStartig disassembly without CDL.\n", cdlSignature, cdlType);
			cdlFileOpened = 0;
		}
	} else {
		Message("Can't open CDL file: \"%s\"\nStartig disassembly without CDL.\n", cdlFileName);
		cdlFileOpened = 0;
//		return -1;
	}

		while (SegByName(form("ROM%X",banksnum)) != -1) {banksnum++;}

		Message("Total Banks: %d\n", banksnum);

//		code_patterns();

#ifdef MMC_PRG_PROC_DETECT
		if(prgset == BADADDR) prgset = find_mmc_prg("EA ?? ?? EA ?? ?? C9",1, 4,	"_mmc_prg_set");
		if(prgset == BADADDR) prgset = find_mmc_prg("21 ?? ?? 77 C9",1, 1,			"_mmc_prg_set");
		if(prgset == BADADDR) prgset = find_mmc_prg("E0 ?? EA ?? ?? C9",3, 3,		"_mmc_prg_set");
#endif

#ifdef SWITCH_DETECT_B
		if(switchptr == BADADDR) switchptr = find_code("4C 87 5F 16 00 E1 19 2A 66 6F E5 61 C9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("5F 16 00 CB 23 CB 12 E1 19 5E 23 56 D5 E1 E9",	"_switch");
		if(switchptr == BADADDR) switchptr = find_code("6F 26 00 29 C1 09 18 04",						"_switch");
		if(switchptr == BADADDR) switchptr = find_code("6F 26 00 29 D1 19 5E 23 66 6B E9",				"_switch");
		if(switchptr == BADADDR) switchptr = find_code("6F 26 00 C1 29 09 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 5F 16 00 19 7E 23 66 6F E9",				"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 6F 26 00 C1 09 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 4F 06 00 E1 09 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 4F 06 00 09 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 5F 16 00 19 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 5F 16 00 19 5E 23 56 ?? ?? E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 85 6F 30 01 24 2A 66 6F E9",				"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 85 6F 7C CE 00 67 2A 66 6F E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 85 6F 3E 00 8C 67 7E 23 66 6F E9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 D5 5F 16 00 19 5E 23 56 D5 E1 D1 E9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 E1 D5 5F 16 00 19 5E 23 56 62 6B D1 E9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("CB 27 E1 D5 5F 16 00 19 5E 23 56 6B 62 D1 E9",	"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 06 00 4F CB 21 CB 10 09 2A 66 6F E9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 07 5F 16 00 19 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 5F 16 00 19 19 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 5F 16 00 CB 23 CB 12 19 2A 66 6F E9",		"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 4F 06 00 09 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 5F 16 00 19 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 5F 16 00 19 5E 23 56 D5 C9",				"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 85 6F 30 01 24 2A 66 6F E9",				"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 85 6F 3E 00 8C 67 2A 66 6F E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 85 6F 7C CE 00 67 2A 66 6F E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 ?? 2A 66 6F E9",							"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 87 CD ?? ?? 2A 66 6F E9",					"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 ?? 62 6B E9",								"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 D5 5F 16 00 19 19 D1 2A 66 6F E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 CB 27 4F AF 17 47 09 2A 66 6F E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E1 D5 87 5F 16 00 19 2A 66 6F D1 E9",			"_switch");
		if(switchptr == BADADDR) switchptr = find_code("E5 D5 F8 04 5E 23 56 6F 26 00 29 19 5E 23 56 F8 04 73 23 72 D1 E1 C9","_switch");
		if(switchptr == BADADDR) switchptr = find_code("87 6F 26 00 D1 19 2A 66 6F E9",					"_switch");

		if((switchptr!=BADADDR)&&(switchptr<0x40)&&((switchptr&7)==0)){
			switchopc=0xC7|switchptr;
			Message(" _switch is RST instruction!\n");
		}
#endif

		while (SegByName(form("ROM%X",seg)) != -1) {
			segea = SegByBase(seg);

			if(seg == 0)
				segorg = 0x0000;
			else
				segorg = 0x4000;
			if(secondpass==0)
				Message("Seg %02x start pass %d", seg, secondpass);
			else
				Message(" %d", secondpass);
			i = 0;
//	work here
			do {
				segeai = segea + i;
				auto F = GetFlags(segeai);
				if(secondpass == 0) {
					// FIRST PASS START
					if(cdlFileOpened == 1)
						cd = fgetc(cdlFile);
					else
						cd = 0;
#ifdef CLEAR_UNUSED
					MakeComm(segeai, "");
#endif
					if((cd & 7) == 4) {
#ifdef CLEAR_UNUSED

						MakeComm(segeai, "");
#endif
						if(isCode(F)) {
#ifdef MAKE_CODE_UNK
							MakeUnknown(segeai, 1, DOUNK_SIMPLE);
#endif
#ifdef MAKE_CODE_UNK_BYTE
							MakeByte(segeai);
#endif
						} else if(!isData(F)) {
#ifdef MAKE_DATA_BYTE
							MakeByte(segeai);
#endif
						}
						make_new_comment(segeai, "data");
						datalog++;
					} else if(cd & 1) {
#ifdef CLEAR_UNUSED
						MakeComm(segeai, "");
#endif
//						Message("mark code at 0x%08X\n",segeai);
					    if(cd & 4) {
							make_new_comment(segeai, "code and data");
						} else {
							make_new_comment(segeai, "code");
						}

//						if(segeai>START_MAKE_CODE_EA) { // damn emulators with real firmware execution!
							if(isData(F))
								MakeUnknown(segeai, 3, DOUNK_SIMPLE);
#ifdef MAKE_CODE
						MakeCode(segeai);
#endif
//						}
						codelog++;
					} else {
						unusedlog++;
#ifdef MARK_UNUSED
						MakeComm(segeai, "-unused-");
#endif
					}
					// FIRST PASS END
				} else {
					//SECOND PASS START
					opcode = Byte(segeai);
					for(j=0;j<2;j++) {
						optype = GetOpType(segeai,j);
#ifdef DEBUG
								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
#endif
						if(optype==1) {
							// bank switch autodetect for bank 0
#ifdef MMC_PRG_SET_DETECT
							if((opcode==0x3E)||(opcode==0x06)){
								prebank=Byte(segeai+1);
//								prebank = ((Byte(segeai + 1) >> 1) & 0xF) | (((Byte(segeai + 1) & 1) ^ 1) << 4);
								preea=segeai;
//#ifdef DEBUG
//								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
//#endif
							} else if(opcode==0xEA) {
								auto tmp0 = Word(segeai+1);
								if((ctype < 4)||(ctype==0xFF)||(ctype==0x19)||(ctype==0x1B)) {	// MBC 1
									if((tmp0>=0x2000)&&(tmp0<0x4000)) {
										if((segeai-preea)<PRG_CMD_SIZE) {
											curbank = prebank & (banksnum - 1);
											prebank = -1;
											preea = -1;
											bankflag = 1;
										}
									}
								} else {
									if(((tmp0>=0x2100)&&(tmp0<0x2200))||(tmp0==0x3FFF)) {	// WTF? docs are wrong?
										if((segeai-preea)<PRG_CMD_SIZE) {
											curbank = prebank & (banksnum - 1);
											prebank = -1;
											preea = -1;
											bankflag = 1;
										}
									}
								}
//#ifdef DEBUG
//								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
//#endif
							} else if (((opcode==0xF0)||(opcode==0xF1))&&((curbank==-1)||(prebank!=-1))){	// protect from redefinition of A between preea and MMC operation opcode.
#ifdef MMC_DEFAULT_BANK
								curbank = MMC_DEFAULT_BANK;
#else
								curbank = -1;
#endif
								prebank = -1;
								preea = -1;
//#ifdef DEBUG
//								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
//#endif
							}
#endif
						} else if(optype==8) {
//							if(((opcode==0xC9)||(opcode==0xC3))&&(curbank!=-1)){
							if((opcode==0x18)&&(curbank!=-1)){
#ifdef MMC_DEFAULT_BANK_CALL
								curbank = MMC_DEFAULT_BANK_CALL;
#else
								curbank = -1;
#endif
								prebank = -1;
								preea = -1;
//#ifdef DEBUG
//								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
//#endif
							}
						} else if(optype == 7){
							if((opcode&0xC0) == 0xC0){
								opvalue = Word(segeai + 1);
#ifdef MAKE_OFFSETS

	#ifdef MMC_DEFAULT_BANK_CALL
								if (curbank == -1)
									curbank = MMC_DEFAULT_BANK_CALL;
	#endif
								if(opvalue!=-1)
									makeOffsetCall(segeai,opvalue,seg,j,banksnum,curbank);
#endif
#ifdef DEBUG
								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
#endif
							}
							if((opcode==0xCD)||(opcode==0xC3)) {
								auto tmp1 = Word(segeai+1);
#ifdef MMC_SET_OFS0
								if(tmp1 == MMC_SET_OFS0) {
									if(preea == -1) {
#ifdef MMC_DEFAULT_BANK
										curbank = MMC_DEFAULT_BANK;
#else
										curbank = -1;
#endif
									} else if((segeai-preea)<PRG_CMD_SIZE) {
										curbank = prebank & (banksnum - 1);
										prebank = -1;
										preea = -1;
										bankflag = 1;
									}
								}
#endif
#ifdef DEBUG
								make_new_comment(segeai, form("debug [prebank=%d,curbank=%d]",prebank,curbank));
#endif
#ifdef MMC_SET_OFS1
								if(tmp1 == MMC_SET_OFS1) {
									if(preea == -1) {
#ifdef MMC_DEFAULT_BANK
										curbank = MMC_DEFAULT_BANK;
#else
										curbank = -1;
#endif
									} else if((segeai-preea)<PRG_CMD_SIZE) {
										curbank = prebank & (banksnum - 1);
										prebank = -1;
										preea = -1;
										bankflag = 1;
									}
								}
#endif
#ifdef SWITCH_OFS
								if(tmp1 == SWITCH_OFS) {
									if(opcode!=0xC3) {
										switch_cnt++;
//										ptr_table(segeai+3,1);
										ptr_table_far(segeai+3,curbank,1);
									} else {
										if((segeai<0x40)&&((segeai&7)==0)){
											switchopc=0xC7|segeai;
										}
									}
								}
#endif
								if((switchptr!=BADADDR)&&(tmp1==switchptr)) {
									if(opcode!=0xC3){
										switch_cnt++;
//										ptr_table(segeai+3,1);
										ptr_table_far(segeai+3,curbank,1);
									} else {
										if((segeai<0x40)&&((segeai&7)==0)){
											switchopc=0xC7|segeai;
										}
									}
								}

								if(prgset!=BADADDR) {
									if(tmp1 == prgset) {
										if((segeai-preea)<PRG_CMD_SIZE) {
											curbank = prebank & (banksnum - 1);
											prebank = -1;
											preea = -1;
											bankflag = 1;
										}
									}
								}
#ifdef FARCALL_OFS0
								if((tmp1 == FARCALL_OFS0)) {
									farcall_cnt++;
	#ifdef FARCALL_PARAM0
			#ifdef FARCALL_SYS0
/* Unexpected Development Sys Far Calls
									MakeUnknown(segeai+FARCALL_WOFS0, 4, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFS0);
									MakeWord(segeai+FARCALL_WOFS0+2);
									ass0 = MK_FP(AskSelector(3), 0);
									OpOffEx(segeai+FARCALL_WOFS0, 0, REF_OFF16, -1, ass0, 0);
									make_code(segeai+FARCALL_WOFS0+4);
//*/
///* CUSTOM FARCALL
									MakeUnknown(segeai+3, 6, DOUNK_SIMPLE);
									MakeData(segeai+3, FF_BYTE, 10, 0);
									SetArrayFormat(segeai+3, AP_IDXHEX, 10, 0);
									MakeWord(segeai+FARCALL_WOFS0);
									far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 0, 0);
									make_code(segeai+15);
//*/
			#else
///* REGULAR FARCALL
									MakeUnknown(segeai+3, FARCALL_SIZE0, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFS0);
									MakeByte(segeai+FARCALL_BOFS0);
									far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 0, 0);
									make_code(segeai+FARCALL_SIZE0+3);
//*/
			#endif
	#else
		#ifdef FARCALL_8BIT0
									auto temp0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFS0)), 0);
									auto temp1 = Byte(segeai + FARCALL_WOFS_LO0)|(Byte(segeai + FARCALL_WOFS_HI0) << 8);
									OpOffEx(segeai + FARCALL_WOFS_LO0 - 1, 1, REF_LOW8, temp0 + temp1, temp0, 0);
									OpOffEx(segeai + FARCALL_WOFS_HI0 - 1, 1, REF_HIGH8, temp0 + temp1, temp0, 0);
									make_code(temp0 + temp1);
									Wait();
		#else
			#ifdef FARCALL_SYS0
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFS0)), 0);
									ass1 = ass0 + (Byte(segeai + FARCALL_WOFS0)) + FARCALL_SYSOFS0;
									MakeUnknown(ass1, 2, DOUNK_SIMPLE);
									MakeWord(ass1);
									OpOffEx(ass1, 0, REF_OFF16, -1, ass0, 0);
									Wait();
									ass0 = ass0 + Word(ass1);
									SetManualInsn(segeai, form("FPTR    %s", Name(ass0)));
									OpNumber(segeai - 3, 1);
									add_dref(segeai, ass0, dr_O|XREF_USER);
//									ass0 = MK_FP(AskSelector(5), 0);
//									OpOffEx(segeai + FARCALL_WOFS0, 1, REF_OFF16, -1, ass0, 0);

			#else
//									if((Byte(segeai+FARCALL_BOFS-1)==FARCALL_BOFS_OPC)&&(Word(segeai+FARCALL_WOFS-1)==FARCALL_WOFS_OPC)) {
										far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 1, -1);
			#endif
//									}
		#endif
	#endif
								}
#endif
#ifdef FARCALL_OFS1
								if((tmp1 == FARCALL_OFS1)) {
									farcall_cnt++;
	#ifdef FARCALL_PARAM1
									MakeUnknown(segeai+3, FARCALL_SIZE1, DOUNK_SIMPLE);
//									make_data_array(segeai+3,FARCALL_SIZE1-2,"");
									MakeWord(segeai+FARCALL_WOFS1);
									MakeByte(segeai+FARCALL_BOFS1);
									far_ptr_code(segeai, FARCALL_BOFS1, FARCALL_WOFS1, 0, 0);
									make_code(segeai+FARCALL_SIZE1+3);
	#else
		#ifdef FARCALL_8BIT1
									auto temp0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFS1)), 0);
									auto temp1 = Byte(segeai + FARCALL_WOFS_LO1)|(Byte(segeai + FARCALL_WOFS_HI1) << 8);
									OpOffEx(segeai + FARCALL_WOFS_LO1 - 1, 1, REF_LOW8, temp0 + temp1, temp0, 0);
									OpOffEx(segeai + FARCALL_WOFS_HI1 - 1, 1, REF_HIGH8, temp0 + temp1, temp0, 0);
									make_code(temp0 + temp1);
									Wait();
		#else
			#ifdef FARCALL_SYS1
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFS1)), 0);
									ass0 = ass0 + Word(ass0 + (Byte(segeai + FARCALL_WOFS1) << 1) + FARCALL_SYSOFS1);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									OpNumber(segeai - 3, 1);
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
									make_code(ass0);
			#else
//									if((Byte(segeai+FARCALL_BOFS-1)==FARCALL_BOFS_OPC)&&(Word(segeai+FARCALL_WOFS-1)==FARCALL_WOFS_OPC)) {
										far_ptr_code(segeai, FARCALL_BOFS1, FARCALL_WOFS1, 1, -1);
//									}
			#endif
		#endif
	#endif
								}
#endif

#ifdef MMC_PRG1_PROC
								if(tmp1 == MMC_PRG1_PROC) {curbank = 1;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG2_PROC
								if(tmp1 == MMC_PRG2_PROC) {curbank = 2;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG3_PROC
								if(tmp1 == MMC_PRG3_PROC) {curbank = 3;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG4_PROC
								if(tmp1 == MMC_PRG4_PROC) {curbank = 4;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG5_PROC
								if(tmp1 == MMC_PRG5_PROC) {curbank = 5;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG6_PROC
								if(tmp1 == MMC_PRG6_PROC) {curbank = 6;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG7_PROC
								if(tmp1 == MMC_PRG7_PROC) {curbank = 7;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG8_PROC
								if(tmp1 == MMC_PRG8_PROC) {curbank = 8;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG9_PROC
								if(tmp1 == MMC_PRG9_PROC) {curbank = 9;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGA_PROC
								if(tmp1 == MMC_PRGA_PROC) {curbank = 0xA;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGB_PROC
								if(tmp1 == MMC_PRGB_PROC) {curbank = 0xB;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGC_PROC
								if(tmp1 == MMC_PRGC_PROC) {curbank = 0xC;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGD_PROC
								if(tmp1 == MMC_PRGD_PROC) {curbank = 0xD;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGE_PROC
								if(tmp1 == MMC_PRGE_PROC) {curbank = 0xE;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGF_PROC
								if(tmp1 == MMC_PRGF_PROC) {curbank = 0xF;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef PARAMETRIC_OFS0
								if(tmp1 == PARAMETRIC_OFS0) {
									param_cnt++;
									///* CUSTOM
									if(PARAMETRIC_OSIZE0==4) {
										MakeUnknown(segeai+3, 4, DOUNK_SIMPLE);
										MakeWord(segeai+3);
										MakeWord(segeai+5);
										OpOffEx(segeai+3, 0, REF_OFF32, -1, MK_FP(AskSelector(3), 0), 0);
									} else //*/
										make_data_array(segeai+3,PARAMETRIC_OSIZE0,"");
									make_code(segeai+3+PARAMETRIC_OSIZE0);
								}
#endif
#ifdef PARAMETRIC_OFS1
								if(tmp1 == PARAMETRIC_OFS1) {
									param_cnt++;
									///* CUSTOM
									if(PARAMETRIC_OSIZE1==4) {
										MakeUnknown(segeai+3, 4, DOUNK_SIMPLE);
										MakeWord(segeai+3);
										MakeWord(segeai+5);
										OpOffEx(segeai+3, 0, REF_OFF32, -1, MK_FP(AskSelector(4), 0), 0);
									} else //*/
										make_data_array(segeai+3,PARAMETRIC_OSIZE1,"");
									make_code(segeai+3+PARAMETRIC_OSIZE1);
								}
#endif
#ifdef PARAMETRIC_OFS2
								if(tmp1 == PARAMETRIC_OFS2) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE2,"");
									make_code(segeai+3+PARAMETRIC_OSIZE2);
								}
#endif
#ifdef PARAMETRIC_OFS3
								if(tmp1 == PARAMETRIC_OFS3) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE3,"");
									make_code(segeai+3+PARAMETRIC_OSIZE3);
								}
#endif
#ifdef PARAMETRIC_OFS4
								if(tmp1 == PARAMETRIC_OFS4) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE4,"");
									make_code(segeai+3+PARAMETRIC_OSIZE4);
								}
#endif
#ifdef PARAMETRIC_OFS5
								if(tmp1 == PARAMETRIC_OFS5) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE5,"");
									make_code(segeai+3+PARAMETRIC_OSIZE5);
								}
#endif
#ifdef PARAMETRIC_OFS6
								if(tmp1 == PARAMETRIC_OFS6) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE6,"");
									make_code(segeai+3+PARAMETRIC_OSIZE6);
								}
#endif
#ifdef PARAMETRIC_OFS7
								if(tmp1 == PARAMETRIC_OFS7) {
									param_cnt++;
									make_data_array(segeai+3,PARAMETRIC_OSIZE7,"");
									make_code(segeai+3+PARAMETRIC_OSIZE7);
								}
#endif
#ifdef MMC_RESTORE0_OFS
								if((tmp1==MMC_RESTORE0_OFS)&&(curbank!=-1)) {
#ifdef MMC_DEFAULT_BANK
									curbank = MMC_DEFAULT_BANK;
#else
									curbank = -1;
#endif
									prebank = -1;
									preea = -1;
								}
#endif
#ifdef MMC_RESTORE1_OFS
								if((tmp1==MMC_RESTORE1_OFS)&&(curbank!=-1)) {
#ifdef MMC_DEFAULT_BANK
									curbank = MMC_DEFAULT_BANK;
#else
									curbank = -1;
#endif
									prebank = -1;
									preea = -1;
								}
#endif
								if((opcode==0xC3)&&(curbank!=-1)){
#ifdef MMC_DEFAULT_BANK_CALL
									curbank = MMC_DEFAULT_BANK_CALL;
#else
									curbank = -1;
#endif
									prebank = -1;
									preea = -1;
								}
							}
						} else if((optype==2)||(optype==5)){
							//   01 11 21 31            EA FA                  E0 F0                  RST
							if(((opcode&0xCF)==0x01)||((opcode&0xEF)==0xEA)||((opcode&0xEF)==0xE0)||((opcode&0xC7)==0xC7)||(opcode==0x08)){
								opvalue = GetOperandValue(segeai,j);

#ifdef FARCALL_OPCA
								if(opcode==FARCALL_OPCA) {
									farcall_cnt++;
	#ifdef FARCALL_PARAMA
		#ifdef FARCALL_SYSA
/* Unexpected Development Sys Far Calls
									MakeUnknown(segeai + 1, 2, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFSA);
									ass1 = Word(segeai+FARCALL_WOFSA);
									if(ass1<0x4000) {
										ass0 = MK_FP(AskSelector(0), 0) + ass1;
									} else if(Word(segeai+FARCALL_WOFSA)<0x8000) {
										ass0 = MK_FP(AskSelector(1), 0) + ass1;
									} else {
										ass1 = ass1 - 0x4000;
										ass0 = MK_FP(AskSelector(2), 0) + ass1;
									}
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									SetManualInsn(segeai + 1, "ENDM");
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
									make_code(segeai+FARCALL_WOFSA+2);
//*/
									MakeUnknown(segeai + 1, 2, DOUNK_SIMPLE);
									MakeWord(segeai + 1);
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSA)), 0);
									ass1 = Word(ass0 + (Byte(segeai + FARCALL_WOFSA) << 1) + FARCALL_SYSOFSA);
									if (ass1 < 0x4000)
										ass0 = ass1;
									else
										ass0 = ass0 + ass1;
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
//									Message("0x%08X\n",segeai);
//									if(Byte(segeai + 3)==0xC9)
//										MakeNameAuto(segeai, form("_j%s", Name(ass0)),0);
									SetManualInsn(segeai + 1, "ENDM");
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
		#else
			#ifdef FARCALL_PARAM_SIZEA
									MakeUnknown(segeai + 1, Byte(segeai + FARCALL_BOFSA), DOUNK_SIMPLE);
									MakeByte(segeai + FARCALL_BOFSA);
									make_data_array(segeai + FARCALL_WOFSA, Byte(segeai + FARCALL_BOFSA), "");
			#else
									MakeUnknown(segeai+1, FARCALL_SIZEA, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFSA);
				#ifdef FARCALL_EXECA
									far_ptr_code(segeai, FARCALL_BOFSA, FARCALL_WOFSA, 0, 0);
				#else
									far_ptr(segeai, FARCALL_BOFSA, FARCALL_WOFSA, 0, 0);
				#endif
									MakeByte(segeai+FARCALL_BOFSA);
			#endif
		#endif
		#ifndef FARCALL_PARAM_SIZEA
									make_code(segeai+1+FARCALL_SIZEA);
									Wait();
		#endif
	#else
		#ifdef FARCALL_SYSA
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSA)), 0);
									ass1 = ass0 + (Byte(segeai + FARCALL_WOFSA) << 1) + FARCALL_SYSOFSA;
									MakeUnknown(ass1, 2, DOUNK_SIMPLE);
									MakeWord(ass1);
									OpOffEx(ass1, 0, REF_OFF16, -1, ass0, 0);
									Wait();
									ass0 = ass0 + Word(ass1);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									OpNumber(segeai - 3, 1);
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
		#else
									far_ptr_code(segeai, FARCALL_BOFSA, FARCALL_WOFSA, 1, -1);
		#endif
	#endif
								}
#endif

#ifdef FARCALL_OPCB
								if(opcode==FARCALL_OPCB) {
									farcall_cnt++;
	#ifdef FARCALL_PARAMB
		#ifdef FARCALL_SYSB
									MakeUnknown(segeai+1, 2, DOUNK_SIMPLE);
									MakeWord(segeai+1);
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSB)), 0);
									ass0 = ass0 + Word(ass0 + (Byte(segeai + FARCALL_WOFSB) << 1) + FARCALL_SYSOFSB);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									if(Byte(segeai + 3)==0xC9)
										MakeNameAuto(segeai, form("_j%s", Name(ass0)),0);
									SetManualInsn(segeai+1, "ENDM");
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
		#else
									MakeUnknown(segeai+1, FARCALL_SIZEB, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFSB);
			#ifdef FARCALL_EXECB
									far_ptr_code(segeai, FARCALL_BOFSB, FARCALL_WOFSB, 0, 0);
			#else
									far_ptr(segeai, FARCALL_BOFSB, FARCALL_WOFSB, 0, 0);
			#endif
									MakeByte(segeai+FARCALL_BOFSB);
		#endif
									make_code(segeai+1+FARCALL_SIZEB);
									Wait();
	#else
		#ifdef FARCALL_SYSB
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSB)), 0);
									ass0 = ass0 + Word(ass0 + (Byte(segeai + FARCALL_WOFSB) << 1) + FARCALL_SYSOFSB);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									OpNumber(segeai - 3, 1);
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
		#else
									far_ptr_code(segeai, FARCALL_BOFSB, FARCALL_WOFSB, 1, -1);
		#endif
	#endif
								}
#endif

#ifdef FARCALL_OPCC
								if(opcode==FARCALL_OPCC) {
									farcall_cnt++;
	#ifdef FARCALL_PARAMC
		#ifdef FARCALL_SYSC
///*
									MakeUnknown(segeai+1, 1, DOUNK_SIMPLE);
									MakeByte(segeai+1);
									ass0 = Byte(segeai + 1);
									if(ass0 < 0x4B) {
										ass0 = Word(0x1E0 + (ass0 << 1));
										if(ass0 >= 0x4000)
											ass0 = ass0 + MK_FP(AskSelector(0x1E), 0);
									} else {
										if(ass0 & 0x80)
											ass0 = MK_FP(AskSelector(0x1F), 0) + Word(MK_FP(AskSelector(0x1F), 0) + FARCALL_SYSOFSC + ((ass0 & 0x7F) << 1));
										else
											ass0 = MK_FP(AskSelector(0x1E), 0) + Word(MK_FP(AskSelector(0x1E), 0) + FARCALL_SYSOFSC + (ass0 << 1));
									}
									SetManualInsn(segeai, form("SYS    %s", Name(ass0)));
									SetManualInsn(segeai+1, "ENDM");
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
//*/
/*
									MakeUnknown(segeai+1, 2, DOUNK_SIMPLE);
									MakeWord(segeai+1);
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSC)), 0);
									ass0 = ass0 + Word(ass0 + (Byte(segeai + FARCALL_WOFSC) << 1) + 0x4000);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									if(Byte(segeai + 3)==0xC9)
										MakeNameAuto(segeai, form("_j%s", Name(ass0)),0);
									SetManualInsn(segeai+1, "ENDM");
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
//*/
		#else
									MakeUnknown(segeai+1, FARCALL_SIZEC, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFSC);
			#ifdef FARCALL_EXECC
									far_ptr_code(segeai, FARCALL_BOFSC, FARCALL_WOFSC, 0, 0);
			#else
									far_ptr(segeai, FARCALL_BOFSC, FARCALL_WOFSC, 0, 0);
			#endif
									MakeByte(segeai+FARCALL_BOFSC);
		#endif
									make_code(segeai+1+FARCALL_SIZEC);
									Wait();
	#else
		#ifdef FARCALL_SYSC
									ass0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFSC)), 0);
									ass0 = ass0 + Word(ass0 + (Byte(segeai + FARCALL_WOFSC) << 1) + FARCALL_SYSOFSC);
									SetManualInsn(segeai, form("FJSR    %s", Name(ass0)));
									OpNumber(segeai - 3, 1);
									AddCodeXref(segeai, ass0, fl_CF|XREF_USER);
		#else
									far_ptr_code(segeai, FARCALL_BOFSC, FARCALL_WOFSC, 1, -1);
		#endif
	#endif
								}
#endif

#ifdef MAKE_OFFSETS
								if(opvalue!=-1) {
									auto forbid = 0;
// manual prevent from doing a garbage offsets usually at DE/BC

#ifdef FORBID_OFFSETS_BC
									if((opcode == 0x01) && (opvalue < 0x8000)) forbid = 1;
#endif
#ifdef FORBID_OFFSETS_DE
									if((opcode == 0x11) && (opvalue < 0x8000)) forbid = 1;
#endif
#ifdef FORBID_OFFSETS_HL
									if((opcode == 0x21) && (opvalue < 0x8000)) forbid = 1;
#endif
									if((opcode == 0xEA) && (opvalue < 0x8000)) forbid = 1;

									if((forbid == 0) && (opvalue >= 0))
										makeOffset(segeai,opvalue,seg,j,banksnum,curbank);
								}
#endif
#ifdef MMC_SET_OPC0
								if(opcode==MMC_SET_OPC0) {
									if(preea == -1) {
#ifdef MMC_DEFAULT_BANK
										curbank = MMC_DEFAULT_BANK;
#else
										curbank = -1;
#endif
									} else if((segeai-preea)<PRG_CMD_SIZE) {
										curbank = prebank & (banksnum - 1);
										prebank = -1;
										preea = -1;
										bankflag = 1;
									}
								}
#endif
#ifdef MMC_SET_OPC1
								if(opcode==MMC_SET_OPC1) {
									if(preea == -1) {
#ifdef MMC_DEFAULT_BANK
										curbank = MMC_DEFAULT_BANK;
#else
										curbank = -1;
#endif
									} else if((segeai-preea)<PRG_CMD_SIZE) {
										curbank = prebank & (banksnum - 1);
										prebank = -1;
										preea = -1;
										bankflag = 1;
									}
								}
#endif
#ifdef MMC_PRG1_OPC
								if(opcode == MMC_PRG1_OPC) {curbank = 1;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG2_OPC
								if(opcode == MMC_PRG2_OPC) {curbank = 2;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG3_OPC
								if(opcode == MMC_PRG3_OPC) {curbank = 3;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG4_OPC
								if(opcode == MMC_PRG4_OPC) {curbank = 4;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG5_OPC
								if(opcode == MMC_PRG5_OPC) {curbank = 5;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG6_OPC
								if(opcode == MMC_PRG6_OPC) {curbank = 6;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRG7_OPC
								if(opcode == MMC_PRG7_OPC) {curbank = 7;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef MMC_PRGF_OPC
								if(opcode == MMC_PRGF_OPC) {curbank = 0xf;bankflag = 1;prebank = -1;preea = -1;}
#endif
#ifdef SWITCH_OPC
								if(opcode == SWITCH_OPC) {
									switch_cnt++;
//									ptr_table(segeai+1,1);
									ptr_table_far(segeai+1,curbank,1);
								}
#endif
								if((switchopc!=-1)&&(opcode == switchopc)) {
										switch_cnt++;
//										ptr_table(segeai+1,1);
										ptr_table_far(segeai+1,curbank,1);
								}

#ifdef PARAMETRIC_OPC0
								if(opcode == PARAMETRIC_OPC0) {
									param_cnt++;
/* SPECIAL CASE FOR SHORT FARCALLS IN GBKISS
									auto tmp_byte = Byte(segeai+1);
									auto tmp_base, tmp_ofs, tmp_ea, tmp_name;
									if(tmp_byte > 0x4A) {
										make_data_array(segeai+1,PARAMETRIC_SIZE0,"");
										make_code(segeai+1+PARAMETRIC_SIZE0);
										if(tmp_byte & 0x80)
											tmp_base = MK_FP(AskSelector(Byte(0xC)), 0);
										else
											tmp_base = MK_FP(AskSelector(Byte(0xB)), 0);
										tmp_ofs = (tmp_byte & 0x7F)<<1;
										tmp_ofs = tmp_ofs + 0x4000;
										tmp_ea = tmp_base + tmp_ofs;
										tmp_ofs = Word(tmp_ea);
										tmp_ea = tmp_base + tmp_ofs;
									} else {
										make_data_array(segeai+1,PARAMETRIC_SIZE0,"");
										if(tmp_byte != 6)
											make_code(segeai+1+PARAMETRIC_SIZE0);
										tmp_ea = (tmp_byte<<1) + 0x01E0;
										tmp_ofs = Word(tmp_ea);
										if(tmp_ofs < 0x4000)
											tmp_base = MK_FP(AskSelector(0), 0);
										else
											tmp_base = MK_FP(AskSelector(Byte(0xE)), 0);
										tmp_ea = tmp_base + tmp_ofs;
									}
									tmp_name = NameEx(BADADDR, tmp_ea);
									if(tmp_name == "") {
										MakeComm(segeai + 1, "");
										MakeComm(segeai + 1, form("0x%08x", tmp_ea));
									} else {
										MakeComm(segeai + 1, "");
										MakeComm(segeai + 1, form("%s", tmp_name));
									}
									AddCodeXref(segeai, tmp_ea, fl_CF);
									Wait();
// SPECIAL CASE FOR SHORT FARCALLS IN GBKISS*/
/* SPECIAL CASE FOR FARCALLS IN GETAWAY
									auto tmp_base, tmp_ea, tmp_name, tmp_ofs = Word(segeai+1);
									make_data_array(segeai+1,PARAMETRIC_SIZE0,"");
									MakeWord(segeai+1);
									if(tmp_ofs & 0x8000) {
										tmp_base = MK_FP(AskSelector(2), 0);
										OpOffEx(segeai+1, 0, REF_OFF32, -1, tmp_base, 0x4000);
									} else {
										if(tmp_ofs & 0x4000)
											tmp_base = MK_FP(AskSelector(1), 0);
										else
											tmp_base = MK_FP(AskSelector(0), 0);
										OpOffEx(segeai+1, 0, REF_OFF16, -1, tmp_base, 0);
									}
									Wait();
// SPECIAL CASE FOR FARCALLS IN GETAWAY*/
/* CUSTOM
//									auto tmp_byte=Byte(segeai+1);
//									make_data_array(segeai+1,tmp_byte+1,"");
//									make_code(segeai+1+tmp_byte+1);
									MakeUnknown(segeai+1, 5, DOUNK_SIMPLE);
									MakeWord(segeai+1);
									MakeWord(segeai+1+2);
									far_ptr(segeai, 5, 1, 0, 0);
									MakeByte(segeai+5);
									make_code(segeai+6);
// CUSTOM */
/* CUSTOM
									auto tmp_byte;
									segeai = segeai + 1;
									while ((tmp_byte = Byte(segeai)) != 0xFF) {
										auto tmp_bank = GetReg(segeai,"ds");
										auto tmp_base = MK_FP(AskSelector(tmp_bank), 0);
										auto tmp_byte2 = tmp_byte;
										tmp_byte = tmp_byte & 0x1F;
										MakeUnknown(segeai, 1, DOUNK_SIMPLE);
										MakeByte(segeai);
										segeai = segeai + 1;
										if((tmp_byte == 0x09)||(tmp_byte == 0x0A)) {	// 2B ARG
											MakeUnknown(segeai, 2, DOUNK_SIMPLE);
											MakeWord(segeai);
											makeOffset(segeai,Word(segeai),seg,0,banksnum,curbank);
											segeai = segeai + 2;
											if(tmp_byte2 & 0x80) {
												MakeUnknown(segeai, 1, DOUNK_SIMPLE);
												MakeByte(segeai);
												segeai = segeai + 1;
											}
										} else if((tmp_byte == 0x01)||(tmp_byte == 0x03)||(tmp_byte == 0x08)) {	// 4B ARG
											MakeUnknown(segeai, 4, DOUNK_SIMPLE);
											MakeWord(segeai);
											makeOffset(segeai,Word(segeai),seg,0,banksnum,curbank);
											MakeWord(segeai + 2);
											segeai = segeai + 4;
										} else if((tmp_byte == 0x02)) {	// 6B ARG
											MakeUnknown(segeai, 6, DOUNK_SIMPLE);
											MakeWord(segeai);
											makeOffset(segeai,Word(segeai),seg,0,banksnum,curbank);
											MakeWord(segeai + 2);
											makeOffset(segeai + 2,Word(segeai + 2),seg,0,banksnum,curbank);
											MakeWord(segeai + 4);
											segeai = segeai + 6;
										} else {
//											Message("wrong opc at 0x%08x\n", segeai);
										}
									}
									MakeUnknown(segeai, 1, DOUNK_SIMPLE);
									MakeByte(segeai);
									make_code(segeai + 1);
// CUSTOM */
/* CUSTOM
									auto tmp_byte, tmp_stop = 0;
									segeai = segeai + 1;
									tmp_byte = segeai;
									while (tmp_stop == 0) {
										if((Byte(segeai) == 0xFF)&&(Byte(segeai + 1) == 0xFF)&&(Byte(segeai + 2) == 0))
											tmp_stop = 1;
										segeai = segeai + 1;
									}
									make_data_array(tmp_byte,segeai - tmp_byte + 2,"");
									SetArrayFormat(tmp_byte, AP_IDXHEX, 16, 0);
// CUSTOM */
///* REGULAR
									if(PARAMETRIC_SIZE0 == 0xFFFF) { // STOP BYTE FF
										auto size = FindBinary(segeai + 1, SEARCH_DOWN|SEARCH_CASE, "FF FF 00");
										MakeUnknown(segeai + 1, size - segeai + 2, DOUNK_SIMPLE);
										MakeData(segeai + 1, FF_BYTE, size - segeai + 2, 0);
										SetArrayFormat(segeai + 1, AP_IDXHEX, 16, 0);
										Wait();
									} else {
										make_data_array(segeai + 1, PARAMETRIC_SIZE0, "");
										make_code(segeai + 1 + PARAMETRIC_SIZE0);
									}
//									if(PARAMETRIC_SIZE0==2) {
//										auto tmb, tm0 = Word(segeai+1);
//										if (tm0<0x4000)
//											tmb = MK_FP(AskSelector(0), 0);
//										else
//											tmb = MK_FP(AskSelector(GetSegmentAttr(segeai, SEGATTR_SEL)), 0);
//										MakeWord(segeai+1);
//										OpOffEx(segeai+1, 0, REF_OFF16, -1, tmb, 0);
//									}
// REGULAR*/
								}
#endif
#ifdef PARAMETRIC_OPC1
								if(opcode == PARAMETRIC_OPC1) {
									param_cnt++;
									make_data_array(segeai+1,PARAMETRIC_SIZE1,"");
									make_code(segeai+1+PARAMETRIC_SIZE1);
								}
#endif
#ifdef PARAMETRIC_OPC2
								if(opcode == PARAMETRIC_OPC2) {
									param_cnt++;
									make_data_array(segeai+1,PARAMETRIC_SIZE2,"");
									make_code(segeai+1+PARAMETRIC_SIZE2);
								}
#endif
#ifdef PARAMETRIC_OPC3
								if(opcode == PARAMETRIC_OPC3) {
									param_cnt++;
									make_data_array(segeai+1,PARAMETRIC_SIZE3,"");
									make_code(segeai+1+PARAMETRIC_SIZE3);
								}
#endif
#ifdef MMC_RESTORE_OPC
								if((opcode == MMC_RESTORE_OPC)&&(curbank!=-1)) {
#ifdef MMC_DEFAULT_BANK
									curbank = MMC_DEFAULT_BANK;
#else
									curbank = -1;
#endif
									prebank = -1;
									preea = -1;
								}
#endif
							}
						}
					}
					// SECOND PASS END
				}
				i++;
			} while (i < 0x4000);

//	end work here

			if(secondpass == 0) {
				secondpass = 1;
				farcall_cnt_prev = 0;
				switch_cnt_prev = 0;
				param_cnt_prev = 0;
			} else {
				if((farcall_cnt_prev==farcall_cnt)&&(switch_cnt_prev==switch_cnt)&&(param_cnt_prev==param_cnt)) {
					farcall_s = farcall_s + farcall_cnt;
					switch_es = switch_es + switch_cnt;
					param_s = param_s + param_cnt;
					secondpass = 0;
					seg++;
					Message("\n");
				} else {
					farcall_cnt_prev = farcall_cnt;
					switch_cnt_prev = switch_cnt;
					param_cnt_prev = param_cnt;
					farcall_cnt = 0;
					switch_cnt = 0;
					param_cnt = 0;
					secondpass++;
					Wait();
				}
			}

		}	// while (SegByName(form("ROM%X",seg) != -1)

		MakeComm(0x147, "");
		if(ctype==0)
			MakeComm(0x147, "NO MBC");
		else if(ctype==1)
			MakeComm(0x147, "MBC 1");
		else if(ctype==2)
			MakeComm(0x147, "MBC 1 + RAM");
		else if(ctype==3)
			MakeComm(0x147, "MBC 1 + BATTERY RAM");
		else if(ctype==5)
			MakeComm(0x147, "MBC 2");
		else if(ctype==6)
			MakeComm(0x147, "MBC 2 + BATTERY RAM");
		else
			MakeComm(0x147, "UNSUPPORTED MBC");

		Message("\n");
		if (bankflag) {
			Message("mmc prg bank set operations detected!\n");
		}

		code_patterns();

		if(farcall_s>0)
			Message("far calls summary: %d has found\n",farcall_s);

		if(switch_es>0)
			Message("switch calls summary: %d has found\n",switch_es);

		if(param_s>0)
			Message("parametric calls summary: %d has found\n",param_s);

		garbage_collector();

		Message("\nScript completed, summary:\n");
		Message("\tCODE bytes:\t0x%x\n",codelog);
		Message("\tDATA bytes:\t0x%x\n",datalog);
		Message("\tUNUSED bytes:\t0x%x\n",unusedlog);

		if(cdlFileOpened == 1)
			fclose(cdlFile);
}

static MakeNameAuto(ea,name,force) {
	if(isRef(GetFlags(ea))||force) {
		if(MakeNameEx(ea,name,SN_CHECK|SN_NOWARN)==0) {
			auto res, nname, nc = 0;
			do {
				nname = form("%s_%d",name,nc);
				nc++;
				res = MakeNameEx(ea,nname,SN_CHECK|SN_NOWARN);
			} while ((res == 0)&&(nc<10));
		}
	}
}

static makeDataDup(sname, ofs, len, name, cmnt) {
	auto seg, segea, ea;
	seg = SegByName(sname);
	segea = SegByBase(seg);
	ea = segea + ofs;
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	MakeData(ea, FF_BYTE, len, 0);
	SetArrayFormat(ea, AP_IDXHEX|AP_ALLOWDUPS, 0x10, 0);
//	if(NameEx(BADADDR, ea)=="")
	MakeNameAuto(ea,name,1);
	MakeRptCmt(ea,cmnt);
}

static makeVector(ea, name) {
	auto opcode = Byte(ea), offset;
	if((opcode != 0x00) && (opcode != 0xFF)) {
		MakeCode(ea);
		AutoMark(ea, AU_CODE);
		Wait();
	}
	if(name != "") {
		if(opcode == 0xFB) {
			ea++;
			opcode = Byte(ea);
		}
		if((opcode == 0xC3)||(opcode == 0xCD))
			offset = Word(ea+1);
		else if (opcode == 0x18)
			offset = ea + Byte(ea + 1) + 2;
		else
			offset = -1;
		MakeNameAuto(ea,form("_%s",name),1);
		if(offset != -1) {
//			makeOffset(ea,offset,0,1,0,1);
			MakeNameAuto(getBase(offset)+offset,name,1);
		}
	}
}

static MakeNames() {
	makeDataDup("ROM0",   0x0104, 0x30, "_LOGO", "");
	makeDataDup("ROM0",   0x0134, 0x10, "_TITLE", "");
	MakeStr(0x0134, 0x0144);
	makeDataDup("ROM0",   0x0144, 0x03, "", "");
	makeDataDup("ROM0",   0x0147, 0x01, "_CART", "");
	makeDataDup("ROM0",   0x0148, 0x01, "_ROM", "");
	makeDataDup("ROM0",   0x0149, 0x01, "_RAM", "");
	makeDataDup("ROM0",   0x014A, 0x01, "_LANG", "");
	makeDataDup("ROM0",   0x014B, 0x01, "_MAKER", "");
	makeDataDup("ROM0",   0x014C, 0x01, "_VER", "");
	makeDataDup("ROM0",   0x014D, 0x01, "_CHECK", "");
	makeDataDup("ROM0",   0x014E, 0x02, "_SUM", "");

	makeDataDup("HWREGS", 0x00, 0x01, "_PAD", "");
	makeDataDup("HWREGS", 0x01, 0x01, "_SIODATA", "");
	makeDataDup("HWREGS", 0x02, 0x01, "_SIOCONT", "");
	makeDataDup("HWREGS", 0x04, 0x01, "_COUNTER", "");
	makeDataDup("HWREGS", 0x05, 0x01, "_TIMER", "");
	makeDataDup("HWREGS", 0x06, 0x01, "_TIMERDIV", "");
	makeDataDup("HWREGS", 0x07, 0x01, "_TIMERCONT", "Bit2    Start/Stop timer                      | COUNTING      | STOPPED\nBit1-0  Timer clock select:\n  00 - 4096Hz    01 - 262144Hz    10 - 65536Hz    11 - 16384Hz");
	makeDataDup("HWREGS", 0x0F, 0x01, "_IFLAGS", "Bit4  Transition High->Low on pins P10-P13    | OCCURED       | NO\nBit3  End of serial I/O transfer              | OCCURED       | NO \nBit2  Timer overflow                          | OCCURED       | NO\nBit1  LCD controller interrupt [see LCDSTAT]  | OCCURED       | NO\nBit0  LCD vertical blanking impulse           | OCCURED       | NO");

	makeDataDup("HWREGS", 0x10, 0x01, "_APU_C0_SWEEP", "");
	makeDataDup("HWREGS", 0x11, 0x01, "_APU_C0_LEN", "");
	makeDataDup("HWREGS", 0x12, 0x01, "_APU_C0_ENV", "");
	makeDataDup("HWREGS", 0x13, 0x01, "_APU_C0_FREQL", "");
	makeDataDup("HWREGS", 0x14, 0x01, "_APU_C0_FREQH", "");
	makeDataDup("HWREGS", 0x16, 0x01, "_APU_C1_LEN", "");
	makeDataDup("HWREGS", 0x17, 0x01, "_APU_C1_ENV", "");
	makeDataDup("HWREGS", 0x18, 0x01, "_APU_C1_FREQL", "");
	makeDataDup("HWREGS", 0x19, 0x01, "_APU_C1_FREQH", "");
	makeDataDup("HWREGS", 0x1A, 0x01, "_APU_C2_ON", "");
	makeDataDup("HWREGS", 0x1B, 0x01, "_APU_C2_LEN", "");
	makeDataDup("HWREGS", 0x1C, 0x01, "_APU_C2_LEVEL", "");
	makeDataDup("HWREGS", 0x1D, 0x01, "_APU_C2_FREQL", "");
	makeDataDup("HWREGS", 0x1E, 0x01, "_APU_C2_FREQH", "");
	makeDataDup("HWREGS", 0x20, 0x01, "_APU_C3_LEN", "");
	makeDataDup("HWREGS", 0x21, 0x01, "_APU_C3_ENV", "");
	makeDataDup("HWREGS", 0x22, 0x01, "_APU_C3_CNT", "");
	makeDataDup("HWREGS", 0x23, 0x01, "_APU_C3_CTRL", "");
	makeDataDup("HWREGS", 0x24, 0x01, "_APU_VOL", "");
	makeDataDup("HWREGS", 0x25, 0x01, "_APU_OUT", "");
	makeDataDup("HWREGS", 0x26, 0x01, "_APU_ON", "");
	makeDataDup("HWREGS", 0x30, 0x10, "_APU_WAVE", "");

	makeDataDup("HWREGS", 0x40, 0x01, "_LCDCONT", "Bit7  LCD operation                           | ON            | OFF\nBit6  Window Tile Table address               | 9C00-9FFF     | 9800-9BFF\nBit5  Window display                          | ON            | OFF\nBit4  Tile Pattern Table address              | 8000-8FFF     | 8800-97FF\nBit3  Background Tile Table address           | 9C00-9FFF     | 9800-9BFF\nBit2  Sprite size                             | 8x16          | 8x8\nBit1  Color #0 transparency in the window     | SOLID         | TRANSPARENT\nBit0  Background display                      | ON            | OFF");
	makeDataDup("HWREGS", 0x41, 0x01, "_LCDSTAT", "Bit6    Interrupt on scanline coincidence     | ON            | OFF\nBit5    Interrupt on controller mode 10       | ON            | OFF\nBit4    Interrupt on controller mode 01       | ON            | OFF\nBit3    Interrupt on controller mode 00       | ON            | OFF\nBit2    Scanline coincidence flag             | COINCIDENCE   | NO COINCIDENCE\nBit1-0  LCD Controller mode:\n  00 - Horizontal blanking impulse [VRAM 8000-9FFF can be accessed by CPU]\n  01 - Vertical blanking impulse [VRAM 8000-9FFF can be accessed by CPU]\n  10 - OAM FE00-FE90 is accessed by LCD controller\n  11 - Both OAM FE00-FE90 and VRAM 8000-9FFF are accessed by LCD controller");
	makeDataDup("HWREGS", 0x42, 0x01, "_SCROLLY", "");
	makeDataDup("HWREGS", 0x43, 0x01, "_SCROLLX", "");
	makeDataDup("HWREGS", 0x44, 0x01, "_CURLINE", "");
	makeDataDup("HWREGS", 0x45, 0x01, "_CMPLINE", "");
	makeDataDup("HWREGS", 0x46, 0x01, "_DMACONT", "");
	makeDataDup("HWREGS", 0x47, 0x01, "_BGPAL", "");
	makeDataDup("HWREGS", 0x48, 0x01, "_OBJ0PAL", "");
	makeDataDup("HWREGS", 0x49, 0x01, "_OBJ1PAL", "");
	makeDataDup("HWREGS", 0x4A, 0x01, "_WNDPOSY", "");
	makeDataDup("HWREGS", 0x4B, 0x01, "_WNDPOSX", "");

	makeDataDup("HWREGS", 0x4D, 0x14, "_GBC_SPEED", "");
	makeDataDup("HWREGS", 0x4F, 0x14, "_GBC_VRAM_BANK", "");
	makeDataDup("HWREGS", 0x51, 0x14, "_GBC_DMA_SRCH", "");
	makeDataDup("HWREGS", 0x52, 0x14, "_GBC_DMA_SRCL", "");
	makeDataDup("HWREGS", 0x53, 0x14, "_GBC_DMA_DSTH", "");
	makeDataDup("HWREGS", 0x54, 0x14, "_GBC_DMA_DSTL", "");
	makeDataDup("HWREGS", 0x55, 0x14, "_GBC_DMA_LEN", "");
	makeDataDup("HWREGS", 0x53, 0x14, "_GBC_DMA_DSTH", "");
	makeDataDup("HWREGS", 0x56, 0x14, "_GBC_IR_CTRL", "");
	makeDataDup("HWREGS", 0x68, 0x14, "_GBC_BG_PAL_IDX", "");
	makeDataDup("HWREGS", 0x69, 0x14, "_GBC_BG_PAL_VAL", "");
	makeDataDup("HWREGS", 0x6A, 0x14, "_GBC_SPR_PAL_IDX", "");
	makeDataDup("HWREGS", 0x6B, 0x14, "_GBC_SPR_PAL_VAL", "");
	makeDataDup("HWREGS", 0x70, 0x01, "_GBC_WRAM_BANK", "");

	makeDataDup("IENABLE", 0x0, 0x01, "_IENABLE", "Bit4  Transition High->Low on pins P10-P13    | ENABLED       | DISABLED\nBit3  End of serial I/O transfer              | ENABLED       | DISABLED\nBit2  Timer overflow                          | ENABLED       | DISABLED\nBit1  LCD controller interrupt [see LCDSTAT]  | ENABLED       | DISABLED\nBit0  LCD vertical blanking impulse           | ENABLED       | DISABLED");

	makeVector(0x00,"");
	makeVector(0x08,"");
	makeVector(0x10,"");
	makeVector(0x18,"");
	makeVector(0x20,"");
	makeVector(0x28,"");
	makeVector(0x30,"");
	makeVector(0x38,"");
	makeVector(0x40,"_NMI");
	makeVector(0x48,"_VDP_IRQ");
	makeVector(0x50,"_TIMER_IRQ");
	makeVector(0x58,"_IO_IRQ");
	makeVector(0x60,"_PAD_IRQ");
	makeVector(0x101,"_ENTRY");
}

static getBase(val) {
	auto base = 0;
	if((val >= 0x0000) && (val < 0x4000))
		base = 0;
	else if((val >=0x4000) && (val < 0x8000))
		base = MK_FP(AskSelector(1),0);
	else if((val >=0x8000) && (val < 0x9800))
		base = MK_FP(AskSelector(SegByName("CHRRAM")),0);
	else if((val >=0x9800) && (val < 0x9C00))
		base = MK_FP(AskSelector(SegByName("BGMAP1")),0);
	else if((val >=0x9C00) && (val < 0xA000))
		base = MK_FP(AskSelector(SegByName("BGMAP2")),0);
	else if((val >=0xA000) && (val < 0xC000))
		base = MK_FP(AskSelector(SegByName("CRAM")),0);
	else if((val >=0xC000) && (val < 0xD000))
		base = MK_FP(AskSelector(SegByName("RAM0")),0);
	else if((val >=0xD000) && (val < 0xE000))
		base = MK_FP(AskSelector(SegByName("RAMB")),0);
	else if((val >=0xFE00) && (val < 0xFEA0))
		base = MK_FP(AskSelector(SegByName("OAM")),0);
	else if((val >=0xFF00) && (val < 0xFF80))
		base = MK_FP(AskSelector(SegByName("HWREGS")),0);
	else if((val >=0xFF80) && (val < 0xFFFF))
		base = MK_FP(AskSelector(SegByName("ZRAM")),0);
	else if(val ==0xFFFF)
		base = MK_FP(AskSelector(SegByName("IENABLE")),0);
	return base;
}

static makeOpOff(ea,opnum,sel,ofs) { // EXPERIMENTOL!!!!
	auto flags_tmp = GetFlags(ofs);
	if (((isTail(flags_tmp)) || (isCode(flags_tmp) && (!isRef(flags_tmp))))) {
	} else {
		OpOff(ea,opnum,sel);
	}
}

static makeOffset(ea,val,s,opnum,bnum,cbank) {
	if((val >= 0x0000) && (val < 0x4000)) {
		makeOpOff(ea, opnum, 0, val);
	} else if((val >=0x4000) && (val < 0x8000)) {
		auto base_tmp = -1;
		if(s == 0) {
			if(bnum == 2)
				base_tmp = MK_FP(AskSelector(1), 0);
			else if(cbank!=-1)
				base_tmp = MK_FP(AskSelector(cbank), 0);
		} else
			base_tmp = MK_FP(AskSelector(s),0);
		makeOpOff(ea, opnum, base_tmp, base_tmp + val);
	} else if((val >=0x8000) && (val < 0x9800))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CHRRAM")),0));
	else if((val >=0x9800) && (val < 0x9C00))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP1")),0));
	else if((val >=0x9C00) && (val < 0xA000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP2")),0));
	else if((val >=0xA000) && (val < 0xC000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CRAM")),0));
	else if((val >=0xC000) && (val < 0xD000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAM0")),0));
	else if((val >=0xD000) && (val < 0xE000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAMB")),0));
	else if((val >=0xFE00) && (val < 0xFEA0))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("OAM")),0));
	else if((val >=0xFF00) && (val < 0xFF80))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("HWREGS")),0));
	else if((val >=0xFF80) && (val < 0xFFFF))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("ZRAM")),0));
	else if(val ==0xFFFF)
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("IENABLE")),0));
}

static makeOffsetCall(ea,val,s,opnum,bnum,cbank) {
	if((val >= 0x0000) && (val < 0x4000)) {
		OpOff(ea, opnum, 0);
	} else if((val >=0x4000) && (val < 0x8000)) {
		auto base_tmp = -1;
		if(s == 0) {
			if(bnum == 2)
				base_tmp = MK_FP(AskSelector(1), 0);
			else if(cbank!=-1)
				base_tmp = MK_FP(AskSelector(cbank), 0);
		} else
			base_tmp = MK_FP(AskSelector(s),0);
		OpOff(ea, opnum, base_tmp);
	} else if((val >=0x8000) && (val < 0x9800))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CHRRAM")),0));
	else if((val >=0x9800) && (val < 0x9C00))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP1")),0));
	else if((val >=0x9C00) && (val < 0xA000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("BGMAP2")),0));
	else if((val >=0xA000) && (val < 0xC000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("CRAM")),0));
	else if((val >=0xC000) && (val < 0xD000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAM0")),0));
	else if((val >=0xD000) && (val < 0xE000))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("RAMB")),0));
	else if((val >=0xFE00) && (val < 0xFEA0))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("OAM")),0));
	else if((val >=0xFF00) && (val < 0xFF80))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("HWREGS")),0));
	else if((val >=0xFF80) && (val < 0xFFFF))
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("ZRAM")),0));
	else if(val ==0xFFFF)
		OpOff(ea,opnum,MK_FP(AskSelector(SegByName("IENABLE")),0));
}

static find_pads(str, h0, h1, hs, p0, ps) {
	auto ea = FindBinary(0, SEARCH_DOWN, str);
	auto held0, pres0, held1;
	if(ea != BADADDR) {
		if(hs==1){
			held0 = Byte(ea+h0)|0xFF00;
			held1 = Byte(ea+h1)|0xFF00;
		} else {
			held0 = Word(ea+h0);
			held1 = Word(ea+h1);
		}
		if(held0==held1) {
			if(hs==1) {
				makeDataDup("ZRAM",held0&0x7F,1,"_pad_held","");
			} else {
				if(held0 >= 0xFF00)
					makeDataDup("ZRAM",held0&0x7F,1,"_pad_held","");
				else if(held0 >= 0xD000)
					makeDataDup("RAMB",held0&0xFFF,1,"_pad_held","");
				else
					makeDataDup("RAM0",held0&0xFFF,1,"_pad_held","");
			}
			if(ps==1){
				pres0 = Byte(ea+p0)|0xFF00;
				makeDataDup("ZRAM",pres0&0x7F,1,"_pad_press","");
			} else {
				pres0 = Word(ea+p0);
				if(pres0 >= 0xFF00)
					makeDataDup("ZRAM",pres0&0x7F,1,"_pad_press","");
				else if(pres0 >= 0xD000)
					makeDataDup("RAMB",pres0&0xFFF,1,"_pad_press","");
				else
					makeDataDup("RAM0",pres0&0xFFF,1,"_pad_press","");
			}
			Message("pad vars %04X, %04X detected at 0x%08x\n", held0, pres0, ea);
		}
	}
}

static find_code(str, name) {
	auto ea = -1, ret = BADADDR;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		if(NameEx(BADADDR, ea)=="")
			MakeNameAuto(ea,name,0);
			Message("code pattern for %s detected at %04X\n", name, ea);
			if(ret==-1)
				ret = ea;
	}
	return ret;
}

static find_mmc_prg(str,w0o,w1o,name) {
	auto ea=-1,det=0,ret=BADADDR;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
		auto ctype = Byte(0x0147),bmc0,bmc1;
		auto w0=Word(ea+w0o), w1=Word(ea+w1o);
		if((ctype < 4)||(ctype==0xFF)) {	// MBC 1 (OR HUDSON GBKISS CARTS)
			bmc0=0x2000;
			bmc1=0x4000;
		} else {
			bmc0=0x2100;
			bmc1=0x2200;
		}
//		Message("detected %04x %04x %04x %04x\n",w0,w1,bmc0,bmc1);
		if((w0>=bmc0)&&(w0<bmc1)) {
			if(w1<0xD000)
				makeDataDup("RAM0",w1&0xFFF,1,"_cur_prg_bank","");
			else
				makeDataDup("RAMB",w1&0xFFF,1,"_cur_prg_bank","");
//			Message("mmc prg bank setup detected at 0x%08x (%04x)\n",ea,w1);
			MakeNameAuto(ea,name,0);
			det++;
			ret=ea;
		} else if((w1>=bmc0)&&(w1<bmc1)) {
			if(w0<0xD000)
				makeDataDup("RAM0",w0&0xFFF,1,"_cur_prg_bank","");
			else
				makeDataDup("RAMB",w0&0xFFF,1,"_cur_prg_bank","");
//			Message("mmc prg bank setup detected at 0x%08x (%04x)\n",ea,w0);
			MakeNameAuto(ea,name,0);
			det++;
			ret=ea;
		}
	}
	if(det==1) {
		Message("mmc prg bank setup function detected\n");
	} else if(det>1) {
		Message("multiple mmc prg bank setup functions detected! use manual settings instead.\n");
		return BADADDR;
	}
	return ret;
}

static find_table_jumps(str,wo,cnt) {
	auto ea=-1;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
		auto bank = GetReg(ea,"ds");
		auto base = MK_FP(AskSelector(bank), 0);
		auto ww = Word(ea + wo);
//		Message("table jump pattern \"%s\" found at %08X\n",str,ea);
		ptr_table_far(base + ww, bank, 1);
		cnt++;
	}
	return cnt;
}

static find_far_8bit_offset_patterns(str,lo,hi,bofs,cnt) {
	auto ea=-1;
	auto exc=1;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message(">8-bit far call at 0x%08x\n",ea);
		auto b0 = Byte(ea+lo);
		auto b1 = Byte(ea+hi);
		auto ww = (b1<<8)|b0;
		auto base,ofs;
		if(bofs==-1)
			base  = MK_FP(AskSelector(GetReg(ea,"ds")), 0);
		else
			base  = MK_FP(AskSelector(Byte(ea+bofs)), 0);
		ofs=base+ww;
//		MakeUnknown(ea,(strlen(str)+1)/3, DOUNK_SIMPLE);
//		MakeUnknown(ea,6, DOUNK_SIMPLE);
//		MakeCode(ea);
//		AutoMark(ea, AU_CODE);
		Wait();
		if(exc){
			OpOffEx(ea+lo-1, 1, REF_LOW8, ofs, base, 0);
			OpOffEx(ea+hi-1, 1, REF_HIGH8, ofs, base, 0);
//			MakeCode(ofs);
//			AutoMark(ofs, AU_CODE);
//			Wait();
		}
		cnt++;
	}
	return cnt;
}

static find_table_jumps_8bit(str,lo,hi,cnt) {
	auto ea=-1;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message("tbl bit at 0x%08x\n",ea);
		auto b0 = Byte(ea+lo);
		auto b1 = Byte(ea+hi);
		auto ww = (b1<<8)|b0;
		auto base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
		OpOffEx(ea+lo-1, 1, REF_LOW8, base+ww, base, 0);
		OpOffEx(ea+hi-1, 1, REF_HIGH8, base+ww, base, 0);
		ptr_table(base+ww,1);
		cnt++;
	}
	return cnt;
}

static find_custom_patterns(str,bofs,wofs,arg,mode) {
	auto ea=-1, base, command;
//	Message("farcall pattern \"%s\" start to find!\n",str);
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message("\t->found at: 0x%08x\n",ea);
		make_code(ea);
		if(wofs!=-1)
			far_ptr(ea, bofs, wofs, 1, -1);
		if(bofs==-1)
			base  = MK_FP(AskSelector(GetReg(ea,"ds")), 0);
		else
			base  = MK_FP(AskSelector(Byte(ea+bofs)), 0);
		if(wofs!=-1) {
			if(arg==-1)
				command = form("auto_far_ptr_ex(%d,%d,%d)",base+Word(ea+wofs),mode,-1);
			else
				command = form("auto_far_ptr_ex(%d,%d,%d)",base+Word(ea+wofs),mode,Byte(ea+arg));
		} else {
				command = form("auto_far_ptr_ex(%d,%d,%d)",ea,mode,-1);
		}
		ExecIDC(command);
	}
}

static find_far_offset_patterns(str,bofs,wofs,docode,cnt) {
	auto ea=-1;
//	Message("farcall pattern \"%s\" start to find!\n",str);
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message("\t->found at: 0x%08x\n",ea);
		make_code(ea);
		if(docode)
			far_ptr_code(ea, bofs, wofs, 1, -1);
		else
			far_ptr(ea, bofs, wofs, 1, -1);
		cnt++;
	}
	return cnt;
}

static find_far_offset_patterns_8b(str,bofs,wofsl,wofsh,cnt) {
	auto ea=-1;
	Message("farcall pattern \"%s\" start!\n",str);
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message("\t->found at: 0x%08x\n",ea);
		make_code(ea);
		auto ba = Byte(ea+bofs) & 0x7F;
		auto b0 = Byte(ea+wofsl);
		auto b1 = Byte(ea+wofsh);
		auto ww = (b1<<8)|b0;
		if(ww < 0x4000) ba = 0;
		auto base = MK_FP(AskSelector(ba), 0);
		OpOffEx(ea+wofsl-1, 1, REF_LOW8, base+ww, base, 0);
		OpOffEx(ea+wofsh-1, 1, REF_HIGH8, base+ww, base, 0);

//		MakeUnknown(ea+bofs-2, 3, DOUNK_SIMPLE);
//		MakeCode(ea+bofs-2);

//		MakeCode(base+ww);
//		AutoMark(base+ww, AU_CODE);
//		Wait();

		cnt++;
	}
	return cnt;
}

static cdl_chunk_search(cdl, chunk, max) {
	auto name, size, len, i, ret = 0;

	while(ret==0) {
		name="";
		size=0;
		len=fgetc(cdl);									// get chunk name len
		for(i=0; i<len; i++) name = name + fgetc(cdl);	// read chunk name
		if(name!=chunk) {
			for(i=0; i<4; i++) size = size | (fgetc(cdl)<<(i*8));
														// read file size
			for(i=0; i<size; i++) fgetc(cdl);			// read skip file
			max--;
			if(max==0)
				ret = -1;
//			Message("\tSkip:   \"%s\" (size %08x)\n\n",name, size);
		} else {
			for(i=0; i<4; i++) size = size | (fgetc(cdl)<<(i*8));
			Message("\tFound:   \"%s\" (size %08x)\n\n",name, size);
			ret = size;
		}
	}
	return ret;
}

static ptr_table_far(ea, farbank, docode) {
	auto i = 0, w0, stop = 0;
	auto base, eabank = GetSegmentAttr(ea, SEGATTR_SEL);
	do {
		if(((i&1)==0)&&(!stop)){
			MakeUnknown(ea+i, 2, DOUNK_SIMPLE);
			MakeWord(ea+i);
			w0=Word(ea+i);
			if(w0<0x4000) {
				base = MK_FP(AskSelector(0), 0);
			} else if(w0<0x8000) {
				if((eabank>0)||(farbank==-1))
					base = MK_FP(AskSelector(eabank), 0);
				else
					base = MK_FP(AskSelector(farbank), 0);
			}
			OpOffEx(ea+i, 0, REF_OFF16, -1, base, 0);
			if(docode) {
				MakeCode(base+w0);
				AutoMark(base+w0, AU_CODE);
				Wait();
			}
			Wait();
		}
		i = i + 2;
		stop = isRef(GetFlags(ea + i)) | isRef(GetFlags(ea + i + 1));
	} while (!stop && (i < 0x10000));
}
