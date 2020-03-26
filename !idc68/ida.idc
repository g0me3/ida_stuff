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

	DelHotkey("Shift-Z");
	AddHotkey("Shift-Z", "auto_array");						// auto convert unexplored area to byte array, auto search of next area from cursor
	DelHotkey("Shift-X");
	AddHotkey("Shift-X", "auto_tbl16_snes");
	DelHotkey("Shift-C");
	AddHotkey("Shift-C", "auto_custom_array_snes");
	DelHotkey("Shift-V");
	AddHotkey("Shift-V", "auto_far_ofs16_snes");

	DelHotkey("Shift-9");
	AddHotkey("Shift-9", "auto_rename_snes");

	DelHotkey("Shift-0");
	AddHotkey("Shift-0", "garbage_collector");
}
