/*
 *      Interactive disassembler (IDA)
 *      Copyright (c) 1990-98 by Ilfak Guilfanov.
 *                        E-mail: ig@datarescue.com
 *      iNES loader.
 *      Copyright (c) 2008    by CaH4e3.
 *                        E-mail: cah4e3@gmail.com
 *      ALL RIGHTS RESERVED.
 *
 */

/*
        L O A D E R  for iNES files for Famicom/NES emulators
*/

#include "idaldr.h"
#include "ines.h"

static ines_hdr _hdr;
static ines_vect _vect;

static unsigned char fds_block_idx;
static fds_disk_hdr fds_disk;
static fds_file_amount fds_files;
static fds_file_header fds_file;
static unsigned char *fds_data;

//--------------------------------------------------------------------------
//
//      check input file format. if recognized, then return 1
//      and fill 'fileformatname'.
//      otherwise return 0
//
int idaapi accept_file(linput_t *li, char fileformatname[MAX_FILE_FORMAT_NAME], int n) {
	if(n) return(0);
	qlseek(li, 0, SEEK_SET);
	if(qlread(li, &_hdr, sizeof(_hdr)) != sizeof(_hdr)) return(0);
	if(_hdr.signature == 0x1A53454E) {
		qstrncpy(fileformatname, "Famicom/NES emulator iNES ROM file", MAX_FILE_FORMAT_NAME);
		return(1);
	} else if(_hdr.signature == 0x1A534446) {
		qstrncpy(fileformatname, "Famicom/NES emulator FDS image file", MAX_FILE_FORMAT_NAME);
		return(1);
	} else
		return(0);
}

//--------------------------------------------------------------------------
void load_bank(linput_t *li, int curea, int size, int sel) {
	char name[MAX_NAME];
	qsnprintf(name, MAX_NAME, "BANK%01X", sel - 1);
	if(!add_segm(sel, curea, curea + size, name, CLASS_CODE)) loader_failure();
	file2base(li, qltell(li), curea, curea + size, FILEREG_PATCHABLE);
}

//--------------------------------------------------------------------------
int fsize(FILE *f)
{
   int temp;
   fseek(f,0,SEEK_END);
   temp = ftell(f);
   fseek(f,0,SEEK_SET);
   return temp;
}

static unsigned char *_cdl = NULL;
static FILE *cdl_file = NULL;

//--------------------------------------------------------------------------
bool cdl_load() {
	char f_name[1024];
	int f_name_size;
	int f_size;
	get_input_file_path(f_name, sizeof(f_name));
	f_name_size = strlen(f_name);
	f_name[f_name_size - 1] = 'l';
	f_name[f_name_size - 2] = 'd';
	f_name[f_name_size - 3] = 'c';
	if((cdl_file = fopen(f_name, "rb")) != NULL) {
		add_pgm_cmt("CDL file    : present, processing");
		f_size = fsize(cdl_file);
		_cdl = (unsigned char*)malloc(f_size);
		fread(_cdl, f_size, 1, cdl_file);
		fclose(cdl_file);
		return 1;
	} else
		return 0;
}

int cdl_get_bank_org(int n_bank, int s_bank, int d_bank) {
	int seg[5] = {0, 0, 0, 0, 0}, start = n_bank * s_bank, stop = start + s_bank, i, res_n = 0, res_i = 0;
	if(_cdl != NULL) {
		for(i = start; i < stop; i++)
			if(_cdl[i] & 1) {
				if(_cdl[i] & 0x80)
					seg[0]++;
				else
					seg[((_cdl[i] >> 2) & 3) + 1]++;
			}
		if(seg[0] | seg[1] | seg[2] | seg[3] | seg[4]) {
			res_n = seg[0];
			res_i = 0;
			if(res_n < seg[1]) {
				res_n = seg[1];
				res_i = 1;
			}
			if(res_n < seg[2]) {
				res_n = seg[2];
				res_i = 2;
			}
			if(res_n < seg[3]) {
				res_n = seg[3];
				res_i = 3;
			}
			if(res_n < seg[4]) {
				res_n = seg[4];
				res_i = 4;
			}
			return (0x6000 + (res_i << 13)) & ~(s_bank - 1);
		}
	}
	return d_bank;
}
		
void cdl_free() {
	if(_cdl != NULL) {
		free(_cdl);
		_cdl = NULL;
	}
}

unsigned char char_trim(unsigned char c) {
	if ( (c < 0x30) || ((c > 0x39) && (c < 0x41)) || ((c > 0x5A) && (c < 0x61)) || (c > 0x7A) )
		return '_';
	else
		return c;
}

//--------------------------------------------------------------------------
//
//      load file into the database.
//
void idaapi load_file(linput_t *li, ushort /*neflag*/, const char * /*fileformatname*/)
{
	unsigned int curea, ofs, size, i;
	unsigned int mapper, _prg;
	unsigned char hex[17] = "0123456789ABCDEF";
	char nam[32], files_count = 0;
	sel_t sel = 1;

	qlseek(li, 0, SEEK_SET);
	if(qlread(li, &_hdr, sizeof(_hdr)) != sizeof(_hdr)) loader_failure();

	set_processor_type("M6502", SETPROC_ALL|SETPROC_FATAL);

	if(_hdr.signature == 0x1A534446) { // FDS

		create_filename_cmt();
		set_selector(0, 0);
		if(!add_segm(0, 0x0000, 0x6000, "RAM", CLASS_CODE)) loader_failure();
		if(!add_segm(0, 0x6000, 0xE000, "MAIN", CLASS_CODE)) loader_failure();
		if(!add_segm(0, 0xE000, 0x10000, "BIOS", CLASS_CODE)) loader_failure();

		curea = 0x10000;
		sel = 3;

		while( qlread(li, &fds_block_idx, sizeof(fds_block_idx)) == sizeof(fds_block_idx) ) {
			switch(fds_block_idx) {
			case 1: {
					if(qlread(li, &fds_disk, sizeof(fds_disk_hdr)) != sizeof(fds_disk_hdr)) loader_failure("1");
					nam[0] = fds_disk.name[0];
					nam[1] = fds_disk.name[1];
					nam[2] = fds_disk.name[2];
					nam[3] = fds_disk.name[3];
					nam[4] = 0;
					add_pgm_cmt("Disc  %d  Side: %d Name \"%-04s\" Boot %02X Manu %02X", fds_disk.disk_num, fds_disk.side_num, nam, fds_disk.boot_read, fds_disk.manufacturer);
//					msg("Disc  %d  Side: %d Name \"%-04s\" Boot %02X Manu %02X\n", fds_disk.disk_num, fds_disk.side_num, nam, fds_disk.boot_read, fds_disk.manufacturer);
//					info("1");
					break;
					}
			case 2: {
					if(qlread(li, &fds_files, sizeof(fds_file_amount)) != sizeof(fds_file_amount)) loader_failure("2");
					add_pgm_cmt("Files %02X", fds_files.amount);
//					msg("Files %02X\n", fds_files.amount);
//					info("2");
					break;
					}
			case 3: {
					if(qlread(li, &fds_file, sizeof(fds_file_header)) != sizeof(fds_file_header)) loader_failure("3");
					nam[0] = fds_file.name[0];
					nam[1] = fds_file.name[1];
					nam[2] = fds_file.name[2];
					nam[3] = fds_file.name[3];
					nam[4] = fds_file.name[4];
					nam[5] = fds_file.name[5];
					nam[6] = fds_file.name[6];
					nam[7] = fds_file.name[7];
					nam[8] = 0;
					add_pgm_cmt("      %02X %02X \"%-08s\" addr %04X size %04X [%s]", fds_file.num, fds_file.code, nam, fds_file.addr, fds_file.size,(fds_file.type==0)?"PROG":((fds_file.type==1)?"CHAR":"NT"));
//					msg("      %02X %02X \"%-08s\" addr %04X size %04X [%s]\n", fds_file.num, fds_file.code, nam, fds_file.addr, fds_file.size,(fds_file.type==0)?"PROG":((fds_file.type==1)?"CHAR":"NT"));
//					info("3");
					files_count++;
					break;
					}
			case 4: {
					if(fds_file.type == 0) {
						if((fds_file.code > 0) && (fds_file.code <= fds_disk.boot_read) && (fds_disk.side_num == 0)) {
							file2base(li, qltell(li), fds_file.addr, fds_file.addr + fds_file.size, FILEREG_PATCHABLE);
						} else {
							set_selector(sel, curea >> 4);
							nam[0] = (fds_disk.disk_num == 0) ? 'A':'B';
							nam[1] = '-';
							nam[2] = hex[(fds_file.num >> 4) & 0xF];
							nam[3] = hex[(fds_file.num >> 0) & 0xF];
							nam[4] = '-';
							nam[5] = hex[(fds_file.code >> 4) & 0xF];
							nam[6] = hex[(fds_file.code >> 0) & 0xF];
							nam[7] = '-';
							nam[8] = char_trim(fds_file.name[0]);
							nam[9] = char_trim(fds_file.name[1]);
							nam[10] = char_trim(fds_file.name[2]);
							nam[11] = char_trim(fds_file.name[3]);
							nam[12] = char_trim(fds_file.name[4]);
							nam[13] = char_trim(fds_file.name[5]);
							nam[14] = char_trim(fds_file.name[6]);
							nam[15] = char_trim(fds_file.name[7]);
							nam[16] = 0;
							if(!add_segm(sel, curea + fds_file.addr, curea + fds_file.addr + fds_file.size, nam, CLASS_CODE)) loader_failure();
//							msg("     seg name %s (%c%c%c%c%c%c%c%c)\n", nam, fds_file.name[0],fds_file.name[1],fds_file.name[2],fds_file.name[3],fds_file.name[4],fds_file.name[5],fds_file.name[6],fds_file.name[7]);
//							info("4");
							file2base(li, qltell(li), curea + fds_file.addr, curea + fds_file.addr + fds_file.size, FILEREG_PATCHABLE);
							curea += 0x10000;
							sel++;
						}
					} else {
						fds_data = (unsigned char*)malloc(fds_file.size);
						if(qlread(li, (void*)fds_data, fds_file.size) != fds_file.size) loader_failure("4");
						free(fds_data);
					}
					break;
					}
			default: {
					if(files_count < fds_files.amount)
						loader_failure("disc error at %08X", qltell(li));
					if(qltell(li) < (65500 + 16))
						qlseek(li, (65500 + 16), SEEK_SET);
					else if(qltell(li) < ((65500 * 2) + 16))
						qlseek(li, ((65500 * 2) + 16), SEEK_SET);
					else if(qltell(li) < ((65500 * 3) + 16))
						qlseek(li, ((65500 * 3) + 16), SEEK_SET);
					break;
					}
			}
		}	

		add_entry(1, toEA(0, get_16bit(0xDFF6)), "_FDS_NMI0", true);
		add_entry(2, toEA(0, get_16bit(0xDFF8)), "_FDS_NMI1", true);
		add_entry(3, toEA(0, get_16bit(0xDFFA)), "_FDS_NMI2", true);
		add_entry(4, toEA(0, get_16bit(0xDFFC)), "_FDS_RESET", true);
		add_entry(5, toEA(0, get_16bit(0xDFFE)), "_FDS_IRQ", true);

	} else if(_hdr.signature == 0x1A53454E) { // NES

		if(!add_segm(0, 0x0000, 0x8000, "RAM", CLASS_CODE)) loader_failure();

		mapper = ((_hdr.map_byte0&0xF0)>>4)|(_hdr.map_byte1&0xF0);
		_prg = _hdr.prg_banks;
		if(_prg == 0)
			_prg = 256;

		cdl_load();
		create_filename_cmt();
		add_pgm_cmt("Mapper      : %d", mapper);
		add_pgm_cmt("16k Banks   : %d", _prg);

		curea = 0;
		if(_prg == 1) {
			size = 0x4000;
			set_selector(sel, curea >> 4);
			curea = cdl_get_bank_org(0, size, 0xC000);
			if(!add_segm(sel, curea, curea + size, "ROM", CLASS_CODE)) loader_failure();
			file2base(li, qltell(li), curea, curea + size, FILEREG_PATCHABLE);
		} else if (_prg == 2) {
			size = 0x8000;
			set_selector(sel, curea >> 4);
			curea = 0x8000;
			if(!add_segm(sel, curea, curea + size, "ROM", CLASS_CODE)) loader_failure();
			file2base(li, qltell(li), curea, curea + size, FILEREG_PATCHABLE);
		} else {
			switch(mapper) {
			case 1:
			case 2:
			case 10:
			case 16:
			case 68:
			case 71:
			case 153:
			case 156:
			case 157:
			case 159: 
			case 182: {
				size = 0x4000;
				for(i=0; i<_prg-1; i++)
				{
					set_selector(sel, curea >> 4);
					curea += cdl_get_bank_org(i, size, 0x8000);
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
				}
				set_selector(sel, curea >> 4);
				curea += 0xC000;
				load_bank(li, curea, size, sel);
				break;
			}
			case 186: {
				size = 0x4000;
				set_selector(sel, curea >> 4);
				curea = 0xC000;
				load_bank(li, curea, size, sel);
				sel++;
				curea += 0x10000;
				for (i = 0; i<_prg - 1; i++)
				{
					set_selector(sel, curea >> 4);
					curea += 0x8000;
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
				}
				break;
			}
			case 4:
			case 5:
			case 6:
			case 9:
			case 12:
			case 14:
			case 15:
			case 23:
			case 83:
			case 121: {
				_prg <<= 1;
				ofs = 0x8000;
				size = 0x2000;
				for(i=0; i<_prg-2; i++)
				{
					set_selector(sel, curea >> 4);
					curea += cdl_get_bank_org(i, size, ofs);
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
					ofs ^= 0x2000;
				}
				set_selector(sel, curea >> 4);
				curea += cdl_get_bank_org(i, size, 0xC000);
				load_bank(li, curea, size, sel);
				sel++;
				curea += 0x10000;
				set_selector(sel, curea >> 4);
				curea += 0xE000;
				load_bank(li, curea, size, sel);
				break;
			}
			case 42: {
				_prg <<= 1;
				size = 0x2000;
				for(i=0; i<_prg-4; i++)
				{
					set_selector(sel, curea >> 4);
					curea += 0x6000;
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
				}
				size = 0x8000;
				set_selector(sel, curea >> 4);
				curea += 0x8000;
				load_bank(li, curea, size, sel);
				break;
			}
			case 17:
			case 18:
			case 19:
			case 80:
			case 82:
			default: {
				_prg <<= 1;
				size = 0x2000;
				for(i=0; i<_prg-1; i++)
				{
					set_selector(sel, curea >> 4);
					curea += cdl_get_bank_org(i, size, 0x8000);
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
				}
				set_selector(sel, curea >> 4);
				curea += 0xE000;
				load_bank(li, curea, size, sel);
				break;
			}
			case 7:
			case 11:
			case 13:
			case 34:
			case 216: {
				_prg >>= 1;
				ofs = 0x8000;
				size = 0x8000;
				for(i=0; i<_prg; i++)
				{
					set_selector(sel, curea >> 4);
					curea += ofs;
					load_bank(li, curea, size, sel);
					sel++;
					curea += 0x10000;
				}
			}
			}
		}

		qlseek(li, (_hdr.prg_banks << 14) + sizeof(_hdr) - sizeof(_vect), SEEK_SET);
		if(qlread(li, &_vect, sizeof(_vect)) != sizeof(_vect)) loader_failure();

		add_entry(1, toEA(ask_selector(sel), _vect.nmi_vect), "NMI", true);
		add_entry(2, toEA(ask_selector(sel), _vect.res_vect), "RESET", true);
		add_entry(3, toEA(ask_selector(sel), _vect.irq_vect), "IRQ", true);
	
		cdl_free();
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
}

//----------------------------------------------------------------------
bool idaapi init_loader_options(linput_t*)
{
	set_processor_type("M6502", SETPROC_ALL|SETPROC_FATAL);
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
	0,                            // loader flags
//
//      check input file format. if recognized, then return 1
//      and fill 'fileformatname'.
//      otherwise return 0
//
	accept_file,
//
//      load file into the database.
//
	load_file,
//
//	create output file from the database.
//	this function may be absent.
//
	NULL,
//      take care of a moved segment (fix up relocations, for example)
	NULL,
//      initialize user configurable options based on the input file.
	init_loader_options,
};
