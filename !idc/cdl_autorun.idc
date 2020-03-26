
static cdl_script_execute() {
	auto err;
	Message("CDL Autorun start.\n");
	if (SegByName("BANK0")!=BADADDR) {
		Message("CDL type: NES\n");
		if((err = CompileEx("C:\\ida\\idc\\cdl_nes.idc",1)) == 0)
			main();
		else
			Message("Compilation error: \"%s\"\n",err);
	} else if (SegByName("ROM0")!=BADADDR) {
		Message("CDL type: GB\n");
		Message("GB\n");
		if((err = CompileEx("C:\\ida\\idc\\cdl_gb.idc",1)) == 0)
			main();
		else
			Message("Compilation error: \"%s\"\n",err);
	} else
		Message("Unknown ROM type!\n");
}
