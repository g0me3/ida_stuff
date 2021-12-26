/*
 *      Interactive disassembler (IDA)
 *      Copyright (c) 1990-98 by Ilfak Guilfanov.
 *                        E-mail: ig@datarescue.com
 *      GB loader
 *      Copyright (c) 2021    by CaH4e3.
 *                        E-mail: cah4e3@gmail.com
 *      ALL RIGHTS RESERVED.
 *
 */

/*
        L O A D E R  for SMS/GG files
*/

#include "idaldr.h"
#include "sms.h"

//--------------------------------------------------------------------------
//
//      check input file format. if recognized, then return 1
//      and fill 'fileformatname'.
//      otherwise return 0
//
int idaapi accept_file(linput_t *li, char fileformatname[MAX_FILE_FORMAT_NAME], int n) {
	unsigned long sign0, sign1;
	if(n) return(0);
	qlseek(li, 0x7FF0, SEEK_SET);
	if(qlread(li, &sign0, sizeof(sign0)) != sizeof(sign0)) return(0);
	if(qlread(li, &sign1, sizeof(sign1)) != sizeof(sign1)) return(0);
	if ((sign0 == 0x20524D54)&& (sign1 == 0x41474553)) {
		qstrncpy(fileformatname, "Game Gear / Sega Master System ROM file", MAX_FILE_FORMAT_NAME);
		return(1);
	} else
		return(0);
}

//--------------------------------------------------------------------------
void load_bank(linput_t *li, int curea, int size, int sel) {
	char name[MAX_NAME];
	qsnprintf(name, MAX_NAME, "CART%01X", sel);
	if(!add_segm(sel, curea, curea + size, name, CLASS_CODE)) loader_failure();
	file2base(li, qltell(li), curea, curea + size, FILEREG_PATCHABLE);
}

//--------------------------------------------------------------------------
//
//      load file into the database.
//
void idaapi load_file(linput_t *li, ushort, const char *)
{
	unsigned int curea = 0, size, i;
	unsigned int _prg;
	sel_t sel = 0;

	qlseek(li, 0, SEEK_END);
	_prg = qltell(li);
	qlseek(li, 0, SEEK_SET);

	set_processor_type("Z80", SETPROC_ALL|SETPROC_FATAL);

	create_filename_cmt();
	add_pgm_cmt("ROM Size   : %d", _prg);

	set_selector(sel, curea >> 4);
	load_bank(li, curea, 0x8000, sel);
	sel++;
	sel++;
	curea += 0x10000;

	_prg = _prg / 0x4000;
	for (i = 2; i < _prg; i++)
	{
		set_selector(sel, curea >> 4);
		curea += 0x8000;
		load_bank(li, curea, 0x4000, sel);
		curea += 0x10000;
		sel++;
	}

	inf.af =
	 AF_FIXUP     | //   0x0001          // Create offsets and segments using fixup info
	 AF_MARKCODE  | //   0x0002          // Mark typical code sequences as code
	 AF_UNK       | //   0x0004          // Delete instructions with no xrefs
	 AF_CODE      | //   0x0008          // Trace execution flow
	 AF_PROC      | //   0x0010          // Create functions if call is present
	 AF_USED      | //   0x0020          // Analyze and create all xrefs
	 AF_FLIRT     | //   0x0040          // Use flirt signatures
	 AF_PROCPTR   | //   0x0080          // Create function if data xref data->code32 exists
	 AF_NULLSUB   | //   0x0200          // Rename empty functions as nullsub_...
	 AF_IMMOFF    | //   0x2000          // Convert 32bit instruction operand to offset
	 AF_DREFOFF   ; //   0x4000          // Create offset if data xref to seg32 exists
	inf.af2 = 0;

	set_selector(sel, curea >> 4);  curea += 0xC000; add_segm(sel++, curea, curea + 0x4000, "RAM", CLASS_DATA);

	doByte(curea + 0x3FFC, 1); set_name(curea + 0x3FFC, "MMC_CTRL");
	doByte(curea + 0x3FFD, 1); set_name(curea + 0x3FFD, "MMC_BANK0");
	doByte(curea + 0x3FFE, 1); set_name(curea + 0x3FFE, "MMC_BANK1");
	doByte(curea + 0x3FFF, 1); set_name(curea + 0x3FFF, "MMC_BANK2");

	add_entry(1, 0x00, "_RST00", true);
	add_entry(1, 0x08, "_RST08", true);
	add_entry(1, 0x10, "_RST10", true);
	add_entry(1, 0x18, "_RST18", true);
	add_entry(1, 0x20, "_RST20", true);
	add_entry(1, 0x28, "_RST28", true);
	add_entry(1, 0x30, "_RST30", true);
	add_entry(1, 0x38, "_RST38", true);
}

//----------------------------------------------------------------------
bool idaapi init_loader_options(linput_t*)
{
	set_processor_type("Z80", SETPROC_ALL|SETPROC_FATAL);
	return true;
}

//----------------------------------------------------------------------
//
//      LOADER DESCRIPTION BLOCK
//
//----------------------------------------------------------------------
loader_t LDSC =
{
	IDP_INTERFACE_VERSION,
//		loader flags
	0,
//      check input file format. if recognized, then return 1
//      and fill 'fileformatname'.
//      otherwise return 0
	accept_file,
//      load file into the database.
	load_file,
//		create output file from the database.
//		this function may be absent.
	NULL,
//      take care of a moved segment (fix up relocations, for example)
	NULL,
//      initialize user configurable options based on the input file.
	init_loader_options,
};
