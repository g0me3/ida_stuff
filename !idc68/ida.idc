//
//      This file is automatically executed when IDA is started.
//      You can define your own IDC functions and assign hotkeys to them.
//
//      You may add your frequently used functions here and they will
//      be always available.
//
//
#include <idc.idc>
#include <functions.idc>
#include <cdl_autorun.idc>

//-----------------------------------------------------------------------
static main(void)
{
	DelHotkey("Shift-F1");
	AddHotkey("Shift-F1", "cdl_script_execute");			//

	DelHotkey("Shift-Q");
	AddHotkey("Shift-Q", "auto_ofs16i_snes");
	DelHotkey("Shift-A");
	AddHotkey("Shift-A", "auto_far_ofs16i_snes");

	DelHotkey("Shift-3");
	AddHotkey("Shift-3", "make_8bit_ofs_selection3");
	DelHotkey("Shift-4");
	AddHotkey("Shift-4", "make_8bit_ofs_selection4");
	DelHotkey("Shift-5");
	AddHotkey("Shift-5", "make_8bit_ofs_selection5");
	DelHotkey("Shift-6");
	AddHotkey("Shift-6", "make_8bit_ofs_selection6");
	DelHotkey("Shift-7");
	AddHotkey("Shift-7", "make_8bit_ofs_selection7");

	DelHotkey("Shift-Z");
	AddHotkey("Shift-Z", "auto_array");						// auto convert unexplored area to byte array, auto search of next area from cursor
	DelHotkey("Shift-X");
	AddHotkey("Shift-X", "auto_tbl16");
	DelHotkey("Shift-C");
	AddHotkey("Shift-C", "auto_custom_array");
	DelHotkey("Shift-V");
	AddHotkey("Shift-V", "auto_far_ofs16_snes");
	DelHotkey("Shift-B");
	AddHotkey("Shift-B", "auto_tbl32_gen");

	DelHotkey("Shift-1");
	AddHotkey("Shift-1", "auto_snes_registers");

	DelHotkey("Shift-9");
	AddHotkey("Shift-9", "auto_rename");

	DelHotkey("Shift-0");
	AddHotkey("Shift-0", "garbage_collector");
}
