
#include <idc.idc>
#include <functions.idc>

// ======main control flags=======
//#define START_MAKE_CODE_EA 0x100

//#define MAKE_OFFSETS
//#define MAKE_CODE_UNK
//#define MAKE_CODE_UNK_BYTE
//#define MAKE_DATA_BYTE
//#define MARK_UNUSED
//#define CLEAR_UNUSED
#define MMC_PRG_SET_DETECT
#define MMC_PRG_PROC_DETECT
//#define SWITCH_DETECT_A
#define SWITCH_DETECT_B
//#define MMC_DEFAULT_BANK 1

// ========MMC control values========
#define PRG_CMD_SIZE 10

#define MMC_SET_OFS0 0x0457
//#define MMC_SET_OFS1 0x0a5a
#define MMC_RESTORE_OFS 0x3F22

//#define MMC_SET_OPC0 0xC7
//#define MMC_SET_OPC1 0xEF
//#define MMC_RESTORE_OPC 0xCF

//#define MMC_PRG1_OPC 0xF7
//#define MMC_PRG2_OPC 0xC7
//#define MMC_PRG3_OPC 0xC7
//#define MMC_PRG4_OPC 0xC7
//#define MMC_PRG5_OPC 0xC7
//#define MMC_PRG6_OPC 0xC7
//#define MMC_PRG7_OPC 0xC7
//#define MMC_PRGF_OPC 0xCF

//#define MMC_PRG1_PROC 0x0334
//#define MMC_PRG2_PROC 0x341
#define MMC_PRG3_PROC 0x627
//#define MMC_PRG4_PROC MMC_PRG3_PROC+5
//#define MMC_PRG5_PROC MMC_PRG4_PROC+5
//#define MMC_PRG6_PROC MMC_PRG5_PROC+5
//#define MMC_PRG7_PROC MMC_PRG6_PROC+5

#define MMC_PRG8_PROC 0x62C
#define MMC_PRG9_PROC 0x631
//#define MMC_PRGA_PROC 0x631
//#define MMC_PRGB_PROC MMC_PRGA_PROC+5
#define MMC_PRGC_PROC 0x636
#define MMC_PRGD_PROC 0x63B
#define MMC_PRGE_PROC 0x640
//#define MMC_PRGF_PROC MMC_PRGE_PROC+5

// =======manual switch opcodes======
//#define SWITCH_OPC 0xC7
//#define SWITCH_OFS 0x06C1

//#define CUSTOM_TABLE_JUMP0 "21 ?? ?? CD 5B 07"
//#define CUSTOM_TABLE_JUMP_OFS0 1

//#define CUSTOM_TABLE_JUMP1 "CB 27 21 ?? ?? CD ?? ?? 2A 66 6F E9"
//#define CUSTOM_TABLE_JUMP_OFS1 3

//#define CUSTOM_TABLE_JUMP2 "21 ?? ?? CD DA 11 CD 9C 14"
//#define CUSTOM_TABLE_JUMP_OFS2 1

//#define CUSTOM_TABLE_JUMP3 "21 ?? ?? CD 78 01 CD 90 01"
//#define CUSTOM_TABLE_JUMP_OFS3 1

// ====manual farcall parameters=====
//#define FARCALL_OPC 0xC7
//#define FARCALL_BOFS 3
//#define FARCALL_WOFS 1
//#define FARCALL_SIZE 3
//#define FARCALL_PARAM
//#define FARCALL_EXEC

//#define FARCALL_OFS0 0x056B
//#define FARCALL_BOFS0 5
//#define FARCALL_WOFS0 3
//#define FARCALL_SIZE0 3
//#define FARCALL_PARAM0

//#define FARCALL_OFS1 0x0803
//#define FARCALL_BOFS1 5
//#define FARCALL_WOFS1 3
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

//#define FARCALL_8BIT0
//#define FARCALL_BOFS0 -1
//#define FARCALL_WOFS_LO0 -3
//#define FARCALL_WOFS_HI0 -5

//#define FARCALL_8BIT1
//#define FARCALL_BOFS1 -1
//#define FARCALL_WOFS_LO1 -3
//#define FARCALL_WOFS_HI1 -5

// ====manual farofs parameters=====
//#define FPRN0	"21 ?? ?? 0E ?? CD EA 0A"
//#define FPRN0_B	4
//#define FPRN0_W	1
//#define FPRN0_C 1

//#define FPRN1	"3E ?? EA ?? ?? 21 ?? ?? Cd 21 35"
//#define FPRN1_B	1
//#define FPRN1_W	6
//#define FPRN1_C	1

//#define FPRN2	"21 ?? ?? 0E ?? CD EC 29"
//#define FPRN2_B	4
//#define FPRN2_W	1
//#define FPRN2_C	1

//#define FPRN3	"3E ?? 21 ?? ??"
//#define FPRN3_B	1
//#define FPRN3_W	3
//#define FPRN3_C	0

//#define FPRN4	"06 ?? 21 ?? ??"
//#define FPRN4_B	1
//#define FPRN4_W	3
//#define FPRN4_C	0

//#define FPRN5	"16 ?? 21 ?? ??"
//#define FPRN5_B	1
//#define FPRN5_W	3
//#define FPRN5_C	0

//#define FPRN6	"06 ?? 21 ?? ?? 0E ?? 11 ?? ?? ?? 5E 05"
//#define FPRN6_B	1
//#define FPRN6_W	3
//#define FPRN6_C	0

//#define FPRN7	"21 ?? ?? 3E ?? ?? ?? E1 F1"
//#define FPRN7_B	4
//#define FPRN7_W	1
//#define FPRN7_C	1

//#define FPRN0B	"3E ?? EA 28 C9 3E ?? EA 29 C9 3E ?? EA 2A C9"
//#define FPRN0B_B	11
//#define FPRN0_WL	1
//#define FPRN0_WH	6

// ====custom farofs parameters=====
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
//#define PARAMETRIC_OPC0 0xEF
//#define PARAMETRIC_SIZE0 1
//#define PARAMETRIC_OPC1 0xEF
//#define PARAMETRIC_SIZE1 1
//#define PARAMETRIC_OPC2 0xE7
//#define PARAMETRIC_SIZE2 1
//#define PARAMETRIC_OPC3 0xE7
//#define PARAMETRIC_SIZE3 1

//#define PARAMETRIC_OFS0 0x09B7
//#define PARAMETRIC_OSIZE0 3
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

static code_patterns(void) {
	auto cnt;

	find_pads("EA ?? ?? 3E 30 E0 00 FA ?? ?? ?? 79 A0 A8 EA ?? ??"	,1,	8,	2,	15,	2);
	find_pads("F0 ?? A8 A0 E0 ?? 78 E0 ??"							,1,	8,	1,	5,	1);
	find_pads("F0 ?? A9 A1 E0 ?? 79 E0 ??"							,1,	8,	1,	5,	1);
	find_pads("F0 ?? A9 A1 E0 ?? ?? ?? ?? ?? 79 E0 ??"				,1,	12,	1,	5,	1);
	find_pads("FA ?? ?? A0 A8 EA ?? ?? 78 EA ?? ??"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? A8 A0 E0 ?? 78 EA ?? ??"					,1,	9,	2,	6,	1);
	find_pads("FA ?? ?? A8 A0 EA ?? ?? 78 EA ?? ??"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? A9 A1 EA ?? ?? 79 EA ?? ??"					,1,	10,	2,	6,	2);
	find_pads("FA ?? ?? 2F A1 EA ?? ?? 79 EA ?? ??"					,1,	10,	2,	6,	2);

	find_code("C5 3E 20 E0 00 F0 00 F0 00 2F E6 0F",				"_read_pad");
	find_code("3E 20 E0 00 F0 00 F0 00 2F E6 0F",					"_read_pad");
	find_code("3E 20 E0 00 F0 00 F0 00 F0 00 2F E6 0F",				"_read_pad");
	find_code("0E 00 3E 20 E2 F2 F2 F2 47 3E 10 E2",				"_read_pad");
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

	find_code("21 ?? ?? CD ?? ?? CD ?? ?? F0 00",					"_sgb_detect");
	find_code("7E E6 07 C8 47 0E 00 C5 3E 00 E2 3E 30 E2 06 10",	"_sgb_cmd");
	find_code("11 58 1B 00 00 00 1B 7A B3 20 F8 C9",				"_sgb_delay1B58");
	find_code("11 D6 06 00 00 00 1B 7A B3 20 F8 0B 78 B1 20 F0 C9",	"_sgb_delay6D6");

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
	if(cnt>0)
		Message("far offset patterns summary: %d has found\n",cnt);

#ifdef CUSTOM_PATTERN0
	find_custom_patterns(CUSTOM_PATTERN0, CUSTOM_PATTERN0_B, CUSTOM_PATTERN0_W, CUSTOM_PATTERN0_ARG0, CUSTOM_PATTERN0_MODE);
#endif

#ifdef CUSTOM_PATTERN1
	find_custom_patterns(CUSTOM_PATTERN1, CUSTOM_PATTERN1_B, CUSTOM_PATTERN1_W, CUSTOM_PATTERN1_ARG0, CUSTOM_PATTERN1_MODE);
#endif

#ifdef SWITCH_DETECT_A
	cnt = 0;
	cnt = find_table_jumps("06 00 21 ?? ?? 09 09 2A 66 6F E9", 			3, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F E9", 					1, cnt);
//	cnt = find_table_jumps("06 00 4F CB 21 21 ?? ?? 09 2A 66 6F E9", 	6, cnt);
//	cnt = find_table_jumps("07 4F 06 00 21 ?? ?? 09 2A 66 6F E9",		5, cnt);
	cnt = find_table_jumps("11 ?? ?? 19 11 ?? ?? D5 2A 66 6F E9", 		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 FA ?? ?? 4F CB 21 CB 10 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 4F CB 21 CB 10 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("FA ?? ?? 21 ?? ?? 16 00 5F CB 23 CB 12 19 2A 66 6F E9",	4, cnt);
	cnt = find_table_jumps("21 ?? ?? 07 85 6F 30 01 24 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 06 00 4F 09 09 2A 66 6F E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F 01 ?? ?? C5 E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 2A 66 6F FA ?? ?? 4F 06 00 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 4E 23 46 69 60 E9",				1, cnt);
	cnt = find_table_jumps("21 ?? ?? 09 7E 23 66 6F E9",				1, cnt);
	cnt = find_table_jumps("21 ?? ?? 16 00 87 5F 19 5E 23 66 6B D1 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 85 6F 30 01 24 5E 23 56 D5 E1 E9",	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 19 2A 47 7E 67 68 E9", 			1, cnt);
	cnt = find_table_jumps("21 ?? ?? 19 2A 66 6F 11 ?? ?? D5 E9",		1, cnt);
//	cnt = find_table_jumps("21 ?? ?? 19 2A 66 6F E9", 					1, cnt);		// portal runner use this pattern in a different way
	cnt = find_table_jumps("21 ?? ?? 87 4F 06 00 09 2A 66 6F E9",		1, cnt);
	cnt = find_table_jumps("21 ?? ?? 87 85 30 01 24 6F 2A 66 6F E9", 	1, cnt);
	cnt = find_table_jumps("21 ?? ?? 87 85 6F 3E 00 8C 67 2A 66 6F E9", 1, cnt);
	cnt = find_table_jumps("21 ?? ?? FA ?? ?? 87 4F 06 00 09 2A 66 6F E9",	1, cnt);
	cnt = find_table_jumps("01 ?? ?? 09 2A 66 6F E9",					1, cnt);
//	cnt = find_table_jumps("CB 27 6F AF 67 01 ?? ?? 09 2A 66 6F E9",	6, cnt);
	cnt = find_table_jumps("11 ?? ?? 19 2A 66 6F E9",					1, cnt);
//	cnt = find_table_jumps("CB 25 11 ?? ?? 19 2A 66 6F E9",				3, cnt);
//	cnt = find_table_jumps("4A CB 21 06 00 21 ?? ?? 09 2A 66 6F E9",	6, cnt);
//	cnt = find_table_jumps("4F 06 00 21 ?? ?? 09 2A 66 6F E9", 			4, cnt);
	cnt = find_table_jumps("4F 06 00 21 ?? ?? 09 09 2A 66 6F C9",		4, cnt);
	cnt = find_table_jumps("4F 21 ?? ?? 09 2A 66 6F 11 ?? ?? D5 E9",	2, cnt);
//	cnt = find_table_jumps("4F 21 ?? ?? 09 2A 66 6F E9",				2, cnt);
//	cnt = find_table_jumps("4F CB 21 06 00 21 ?? ?? 09 2A 66 6F E9", 	6, cnt);
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
	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 2A 47 7E 67 68 E9", 	6, cnt);
//	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 2A 66 6F E9",	6, cnt);
	cnt = find_table_jumps("CB 27 4F 06 00 21 ?? ?? 09 4E 23 46 E1 C5 C9",	6, cnt);
	cnt = find_table_jumps("E5 16 00 21 ?? ?? 19 5E 23 56 E1 D5 C9",	4, cnt);
	cnt = find_table_jumps("F5 21 ?? ?? 19 2A 66 6F F1 E9",				2, cnt);
	cnt = find_table_jumps("5F 16 00 21 ?? ?? 19 19 2A 66 6F E9",		4, cnt);
	cnt = find_table_jumps("01 ?? ?? F0 ?? 6F 26 00 29 09 2A 66 6F E9",	1, cnt);
//	cnt = find_table_jumps("21 ?? ?? 09 54 5D 62 6B 2A 66 6F E9",		1, cnt);
//	cnt = find_table_jumps("21 ?? ?? ?? 0F 3E",		                    1, cnt);	// Nanotone custom table jump
//	cnt = find_table_jumps("21 ?? ?? CF",		                        1, cnt);	// Evangelion

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

#ifdef MMC_DEFAULT_BANK
	curbank = MMC_DEFAULT_BANK;
#endif

	MakeNames();

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

		code_patterns();

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
						if(isCode(GetFlags(segeai))) {
#ifdef MAKE_CODE_UNK
							MakeUnknown(segeai, 1, DOUNK_SIMPLE);
#endif
#ifdef MAKE_CODE_UNK_BYTE
							MakeByte(segeai);
#endif
						} else if(!isData(GetFlags(segeai))) {
#ifdef MAKE_DATA_BYTE
							MakeByte(segeai);
#endif
						}
						MakeComm(segeai, "data");
						datalog++;
					} else if(cd & 1) {
#ifdef CLEAR_UNUSED
						MakeComm(segeai, "");
#endif
					    if(cd & 4) {
							MakeComm(segeai, "code and data");
						} else {
							MakeComm(segeai, "code");
						}

//						if(segeai>START_MAKE_CODE_EA) { // damn emulators with real firmware execution!
							if(isData(GetFlags(segeai)))
								MakeUnknown(segeai, 3, DOUNK_SIMPLE);
							MakeCode(segeai);
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
						if(optype==1) {
							// bank switch autodetect for bank 0
#ifdef MMC_PRG_SET_DETECT
							if((opcode==0x3E)||(opcode==0x06)){
								prebank=Byte(segeai+1);
								preea=segeai;
							} else if(opcode==0xEA) {
								auto tmp0 = Word(segeai+1);
								if((ctype < 4)||(ctype==0xFF)||(ctype==0x19)||(ctype==0x1B)) {	// MBC 1
									if((tmp0>=0x2000)&&(tmp0<0x4000)) {
										if((segeai-preea)<PRG_CMD_SIZE) {
											curbank = prebank;
											prebank = -1;
											preea = -1;
											bankflag = 1;
										}
									}
								} else {
									if(((tmp0>=0x2100)&&(tmp0<0x2200))||(tmp0==0x3FFF)) {	// WTF? docs are wrong?
										if((segeai-preea)<PRG_CMD_SIZE) {
											curbank = prebank;
											prebank = -1;
											preea = -1;
											bankflag = 1;
										}
									}
								}
							} else if (((opcode==0xF0)||(opcode==0xF1))&&(prebank!=-1)){	// protect from redefinition of A between preea and MMC operation opcode.
#ifdef MMC_DEFAULT_BANK
								curbank = MMC_DEFAULT_BANK;
#else
								curbank = -1;
#endif
								prebank = -1;
								preea = -1;
							}
#endif
						} else if(optype==8) {
//							if(((opcode==0xC9)||(opcode==0xC3))&&(curbank!=-1)){
							if((opcode==0x18)&&(curbank!=-1)){
#ifdef MMC_DEFAULT_BANK
								curbank = MMC_DEFAULT_BANK;
#else
								curbank = -1;
#endif
								prebank = -1;
								preea = -1;
							}
						} else if(optype==7){
							if((opcode&0xC0)==0xC0){
								opvalue=Word(segeai+1);
#ifdef MAKE_OFFSETS
								if(opvalue!=-1)
									makeOffset(segeai,opvalue,seg,j,banksnum,curbank);
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
										curbank = prebank;
										prebank = -1;
										preea = -1;
										bankflag = 1;
									}
								}
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
										curbank = prebank;
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
											curbank = prebank;
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
/* CUSTOM FARCALL
									MakeUnknown(segeai+3, 6, DOUNK_SIMPLE);
									MakeData(segeai+3, FF_BYTE, 10, 0);
									SetArrayFormat(segeai+3, AP_IDXHEX, 10, 0);
									MakeWord(segeai+FARCALL_WOFS0);
									far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 0, 0);
									make_code(segeai+15);
//*/
//* REGULAR FARCALL
									MakeUnknown(segeai+3, FARCALL_SIZE0, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFS0);
									MakeByte(segeai+FARCALL_BOFS0);
									far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 0, 0);
									make_code(segeai+FARCALL_SIZE0+3);
//*/
	#else
		#ifdef FARCALL_8BIT0
									auto temp0 = MK_FP(AskSelector(Byte(segeai + FARCALL_BOFS0)), 0);
									auto temp1 = Byte(segeai + FARCALL_WOFS_LO0)|(Byte(segeai + FARCALL_WOFS_HI0) << 8);
									OpOffEx(segeai + FARCALL_WOFS_LO0 - 1, 1, REF_LOW8, temp0 + temp1, temp0, 0);
									OpOffEx(segeai + FARCALL_WOFS_HI0 - 1, 1, REF_HIGH8, temp0 + temp1, temp0, 0);
									make_code(temp0 + temp1);
									Wait();
		#else
//									if((Byte(segeai+FARCALL_BOFS-1)==FARCALL_BOFS_OPC)&&(Word(segeai+FARCALL_WOFS-1)==FARCALL_WOFS_OPC)) {
										far_ptr_code(segeai, FARCALL_BOFS0, FARCALL_WOFS0, 1, -1);
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
//									if((Byte(segeai+FARCALL_BOFS-1)==FARCALL_BOFS_OPC)&&(Word(segeai+FARCALL_WOFS-1)==FARCALL_WOFS_OPC)) {
										far_ptr_code(segeai, FARCALL_BOFS1, FARCALL_WOFS1, 1, -1);
//									}
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
									make_data_array(segeai+3,PARAMETRIC_OSIZE0,"");
									make_code(segeai+3+PARAMETRIC_OSIZE0);
								}
#endif
#ifdef PARAMETRIC_OFS1
								if(tmp1 == PARAMETRIC_OFS1) {
									param_cnt++;
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
#ifdef MMC_RESTORE_OFS
								if((tmp1==MMC_RESTORE_OFS)&&(curbank!=-1)) {
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
#ifdef MMC_DEFAULT_BANK
									curbank = MMC_DEFAULT_BANK;
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
#ifdef FARCALL_OPC
								if(opcode==FARCALL_OPC) {
									farcall_cnt++;
#ifdef FARCALL_PARAM
/* CUSTOM FARCALL
									MakeUnknown(segeai+1, 5, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFS);
									MakeWord(segeai+FARCALL_WOFS+2);
									far_ptr_code(segeai, FARCALL_BOFS, FARCALL_WOFS, 0, 0);
									MakeByte(segeai+FARCALL_BOFS);
									make_code(segeai+6);
									Wait();
//*/
//* REGULAR FARCALL
									MakeUnknown(segeai+1, FARCALL_SIZE, DOUNK_SIMPLE);
									MakeWord(segeai+FARCALL_WOFS);
#ifdef FARCALL_EXEC
									far_ptr_code(segeai, FARCALL_BOFS, FARCALL_WOFS, 0, 0);
#else
									far_ptr(segeai, FARCALL_BOFS, FARCALL_WOFS, 0, 0);
#endif
									MakeByte(segeai+FARCALL_BOFS);
									make_code(segeai+1+FARCALL_SIZE);
									Wait();
//*/
#else
									far_ptr_code(segeai, FARCALL_BOFS, FARCALL_WOFS, 1, -1);
#endif
								}
#endif

#ifdef MAKE_OFFSETS
								if(opvalue!=-1)
									makeOffset(segeai,opvalue,seg,j,banksnum,curbank);
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
										curbank = prebank;
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
										curbank = prebank;
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
//* REGULAR
									make_data_array(segeai+1,PARAMETRIC_SIZE0,"");
//									if(PARAMETRIC_SIZE0==2) {
//										auto tmb, tm0 = Word(segeai+1);
//										if (tm0<0x4000)
//											tmb = MK_FP(AskSelector(0), 0);
//										else
//											tmb = MK_FP(AskSelector(GetSegmentAttr(segeai, SEGATTR_SEL)), 0);
//										MakeWord(segeai+1);
//										OpOffEx(segeai+1, 0, REF_OFF16, -1, tmb, 0);
//									}
									make_code(segeai+1+PARAMETRIC_SIZE0);
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

//		code_patterns();

		if(farcall_s>0)
			Message("far calls summary: %d has found\n",farcall_s);

		if(switch_es>0)
			Message("switch calls summary: %d has found\n",switch_es);

		if(param_s>0)
			Message("parametric calls summary: %d has found\n",param_s);

		Message("\nScript completed, summary:\n");
		Message("\tCODE bytes:\t0x%x\n",codelog);
		Message("\tDATA bytes:\t0x%x\n",datalog);
		Message("\tUNUSED bytes:\t0x%x\n",unusedlog);

//		garbage_collector();

		if(cdlFileOpened == 1)
			fclose(cdlFile);
}

static MakeNameAuto(ea,name) {
	if(MakeNameEx(ea,name,SN_CHECK|SN_NOWARN)==0) {
		auto res, nname, nc = 0;
		do {
			nname = form("%s_%d",name,nc);
			nc++;
			res = MakeNameEx(ea,nname,SN_CHECK|SN_NOWARN);
		} while ((res == 0)&&(nc<10));
	}
}

static makeDataDup(sname, ofs, len, name) {
	auto seg, segea, ea;
	seg = SegByName(sname);
	segea = SegByBase(seg);
	ea = segea + ofs;
	MakeUnknown(ea, len, DOUNK_SIMPLE);
	MakeData(ea, FF_BYTE, len, 0);
	SetArrayFormat(ea, AP_IDXHEX|AP_ALLOWDUPS, 0x10, 0);
//	if(NameEx(BADADDR, ea)=="")
		MakeNameAuto(ea,name);
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
		if(offset != -1) {
//			makeOffset(ea,offset,0,1,0,1);
			MakeNameAuto(getBase(offset),name);
		}
	}
}

static MakeNames() {
//	makeDataDup("ROM0",   0x2000, 0x01, "MMC_PRG");
	makeDataDup("ROM0",   0x0104, 0x30, "GB_LOGO");
	makeDataDup("ROM0",   0x0134, 0x10, "GB_TITLE");
	MakeStr(0x0134, 0x0144);
	makeDataDup("ROM0",   0x0144, 0x03, "");
	makeDataDup("ROM0",   0x0147, 0x01, "GB_CART");
	makeDataDup("ROM0",   0x0148, 0x01, "GB_ROM");
	makeDataDup("ROM0",   0x0149, 0x01, "GB_RAM");
	makeDataDup("ROM0",   0x014A, 0x01, "GB_LANG");
	makeDataDup("ROM0",   0x014B, 0x01, "GB_MAKER");
	makeDataDup("ROM0",   0x014C, 0x01, "GB_VER");
	makeDataDup("ROM0",   0x014D, 0x01, "GB_CHECK");
	makeDataDup("ROM0",   0x014E, 0x02, "GB_SUM");
	makeDataDup("HWREGS", 0x00, 0x01, "PAD");
	makeDataDup("HWREGS", 0x01, 0x01, "SIODATA");
	makeDataDup("HWREGS", 0x02, 0x01, "SIOCONT");
	makeDataDup("HWREGS", 0x04, 0x01, "COUNTER");
	makeDataDup("HWREGS", 0x05, 0x01, "TIMER");
	makeDataDup("HWREGS", 0x06, 0x01, "TIMERDIV");
	makeDataDup("HWREGS", 0x07, 0x01, "TIMERCONT");
	makeDataDup("HWREGS", 0x0F, 0x01, "IFLAGS");
	makeDataDup("HWREGS", 0x10, 0x30, "SOUND");
	makeDataDup("HWREGS", 0x40, 0x01, "LCDCONT");
	makeDataDup("HWREGS", 0x41, 0x01, "LCDSTAT");
	makeDataDup("HWREGS", 0x42, 0x01, "SCROLLY");
	makeDataDup("HWREGS", 0x43, 0x01, "SCROLLX");
	makeDataDup("HWREGS", 0x44, 0x01, "CURLINE");
	makeDataDup("HWREGS", 0x45, 0x01, "CMPLINE");
	makeDataDup("HWREGS", 0x46, 0x01, "DMACONT");
	makeDataDup("HWREGS", 0x47, 0x01, "BGPAL");
	makeDataDup("HWREGS", 0x48, 0x01, "OBJ0PAL");
	makeDataDup("HWREGS", 0x49, 0x01, "OBJ1PAL");
	makeDataDup("HWREGS", 0x4A, 0x01, "WNDPOSY");
	makeDataDup("HWREGS", 0x4B, 0x01, "WNDPOSX");
	makeDataDup("HWREGS", 0x4C, 0x14, "UNK_VIDEO");
	makeDataDup("HWREGS", 0x70, 0x01, "GBC_WRAM_BANK");
	makeDataDup("IENABLE", 0x0, 0x01, "_IENABLE");
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

static makeOffset(ea,val,s,opnum,bnum,cbank) {
	if((val >= 0x0) && (val < 0x4000))
		OpOff(ea,opnum,0);
	else if((val >=0x4000) && (val < 0x8000)) {
		if(s == 0) {
			if(bnum == 2)
				OpOff(ea,opnum,MK_FP(AskSelector(1),0));
			else if(cbank!=-1)
				OpOff(ea,opnum,MK_FP(AskSelector(cbank),0));
		} else
			OpOff(ea,opnum,MK_FP(AskSelector(s),0));
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
				makeDataDup("ZRAM",held0&0x7F,1,"_pad_held");
			} else {
				if(held0 >= 0xFF00)
					makeDataDup("ZRAM",held0&0x7F,1,"_pad_held");
				else if(held0 >= 0xD000)
					makeDataDup("RAMB",held0&0xFFF,1,"_pad_held");
				else
					makeDataDup("RAM0",held0&0xFFF,1,"_pad_held");
			}
			if(ps==1){
				pres0 = Byte(ea+p0)|0xFF00;
				makeDataDup("ZRAM",pres0&0x7F,1,"_pad_press");
			} else {
				pres0 = Word(ea+p0);
				if(pres0 >= 0xFF00)
					makeDataDup("ZRAM",pres0&0x7F,1,"_pad_press");
				else if(pres0 >= 0xD000)
					makeDataDup("RAMB",pres0&0xFFF,1,"_pad_press");
				else
					makeDataDup("RAM0",pres0&0xFFF,1,"_pad_press");
			}
			Message("pad vars %04X, %04X detected at 0x%08x\n", held0, pres0, ea);
		}
	}
}

static find_code(str, name) {
	auto ea = -1, ret = BADADDR;
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		if(NameEx(BADADDR, ea)=="")
			MakeNameAuto(ea,name);
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
				makeDataDup("RAM0",w1&0xFFF,1,"_prg_bank");
			else
				makeDataDup("RAMB",w1&0xFFF,1,"_prg_bank");
//			Message("mmc prg bank setup detected at 0x%08x (%04x)\n",ea,w1);
			MakeNameAuto(ea,name);
			det++;
			ret=ea;
		} else if((w1>=bmc0)&&(w1<bmc1)) {
			if(w0<0xD000)
				makeDataDup("RAM0",w0&0xFFF,1,"_prg_bank");
			else
				makeDataDup("RAMB",w0&0xFFF,1,"_prg_bank");
//			Message("mmc prg bank setup detected at 0x%08x (%04x)\n",ea,w0);
			MakeNameAuto(ea,name);
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
		auto ww = Word(ea+wo);
		auto base = MK_FP(AskSelector(GetSegmentAttr(ea, SEGATTR_SEL)), 0);
#ifdef MMC_DEFAULT_BANK
		ptr_table_far(base + ww,MMC_DEFAULT_BANK,1);
#else
		ptr_table_far(base + ww,-1,1);
#endif
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
//	Message("farcall pattern \"%s\" start to find!\n",str);
	while((ea=FindBinary(ea+1, SEARCH_DOWN, str))!=BADADDR) {
//		Message("\t->found at: 0x%08x\n",ea);
		make_code(ea);
		auto ba = Byte(ea+bofs);
		auto b0 = Byte(ea+wofsl);
		auto b1 = Byte(ea+wofsh);
		auto ww = (b1<<8)|b0;
		auto base = MK_FP(AskSelector(ba), 0);
		OpOffEx(ea+wofsl-1, 1, REF_LOW8, base+ww, base, 0);
		OpOffEx(ea+wofsh-1, 1, REF_HIGH8, base+ww, base, 0);

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
