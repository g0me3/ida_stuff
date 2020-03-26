/*
 *      Interactive disassembler (IDA)
 *      Copyright (c) 1990-98 by Ilfak Guilfanov.
 *                        E-mail: ig@datarescue.com
 *      GB loader
 *      Copyright (c) 2016    by CaH4e3.
 *                        E-mail: cah4e3@gmail.com
 *      ALL RIGHTS RESERVED.
 *
 */

/*
        L O A D E R  for Game Boy files for GBx emulators
*/

#include "idaldr.h"
#include "gb.h"

//--------------------------------------------------------------------------
//
//      check input file format. if recognized, then return 1
//      and fill 'fileformatname'.
//      otherwise return 0
//
int idaapi accept_file(linput_t *li, char fileformatname[MAX_FILE_FORMAT_NAME], int n) {
	unsigned short sign;
	if(n) return(0);
	qlseek(li, 0x100, SEEK_SET);
	if(qlread(li, &sign, sizeof(sign)) != sizeof(sign)) return(0);
	if ((sign == 0xC300) || (sign == 0xC3F3)) {
		qstrncpy(fileformatname, "Game Boy / Game Boy Color ROM file", MAX_FILE_FORMAT_NAME);
		return(1);
	} else
		return(0);
}

//--------------------------------------------------------------------------
void load_bank(linput_t *li, int curea, int size, int sel) {
	char name[MAX_NAME];
	qsnprintf(name, MAX_NAME, "ROM%01X", sel);
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
	
	set_processor_type("GB", SETPROC_ALL|SETPROC_FATAL);

	_prg = _prg / 16384;

	create_filename_cmt();
	add_pgm_cmt("16k Banks   : %d", _prg);

//	if (_prg == 2) {
//		size = 0x8000;
//
//		set_selector(sel, curea >> 4);
//		load_bank(li, curea, size, sel);
//	}
//	else {
		size = 0x4000;

		set_selector(sel, curea >> 4);
		load_bank(li, curea, size, sel);
		sel++;
		curea += 0x10000;

		for (i = 1; i < _prg; i++)
		{
			set_selector(sel, curea >> 4);
			curea += 0x4000;
			load_bank(li, curea, size, sel);
			sel++;
			curea += 0x10000;
		}
//	}

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

//		$FFFF Interrupt Enable Flag
//		$FF80 - $FFFE Zero Page - 127 bytes
//		$FF00 - $FF7F Hardware I / O Registers
//		$FEA0 - $FEFF Unusable Memory
//		$FE00 - $FE9F OAM - Object Attribute Memory
//		$E000 - $FDFF Echo RAM - Reserved, Do Not Use
//		$D000 - $DFFF Internal RAM - Bank 1 - 7 (switchable - CGB only)
//		$C000 - $CFFF Internal RAM - Bank 0 (fixed)
//		$A000 - $BFFF Cartridge RAM(If Available)
//		$9C00 - $9FFF BG Map Data 2
//		$9800 - $9BFF BG Map Data 1
//		$8000 - $97FF Character RAM
//		$4000 - $7FFF Cartridge ROM - Switchable Banks 1 - xx
//		$0150 - $3FFF Cartridge ROM - Bank 0 (fixed)
//		$0100 - $014F Cartridge Header Area
//		$0000 - $00FF Restart and Interrupt Vectors


	set_selector(sel, curea >> 4); curea += 0x8000;  add_segm(sel++, curea, curea + 0x1800, "CHRRAM", CLASS_DATA); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0x9800;  add_segm(sel++, curea, curea + 0x0400, "BGMAP1", CLASS_DATA); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0x9C00;  add_segm(sel++, curea, curea + 0x0400, "BGMAP2", CLASS_DATA); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xA000;  add_segm(sel++, curea, curea + 0x2000, "CRAM", CLASS_CODE); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xC000;  add_segm(sel++, curea, curea + 0x1000, "RAM0", CLASS_CODE); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xD000;  add_segm(sel++, curea, curea + 0x1000, "RAMB", CLASS_CODE); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xFE00;  add_segm(sel++, curea, curea + 0x00A0, "OAM", CLASS_DATA); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xFF00;  add_segm(sel++, curea, curea + 0x0080, "HWREGS", CLASS_DATA);
	doByte(curea + 0x0000, 1); set_name(curea + 0x0000, "PAD");
	doByte(curea + 0x0010, 0x30); set_name(curea + 0x0010, "SOUND");
	doByte(curea + 0x0040, 0x20); set_name(curea + 0x0040, "VDP");
	curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xFF80;  add_segm(sel++, curea, curea + 0x007F, "ZRAM", CLASS_DATA); curea += 0x10000;
	set_selector(sel, curea >> 4); curea += 0xFFFF;  add_segm(sel++, curea, curea + 0x0001, "IENABLE", CLASS_DATA); curea += 0x10000;

	add_entry(1, 0x100, "_ENTRY_POINT", true);
}

//----------------------------------------------------------------------
bool idaapi init_loader_options(linput_t*)
{
	set_processor_type("GB", SETPROC_ALL|SETPROC_FATAL);
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
