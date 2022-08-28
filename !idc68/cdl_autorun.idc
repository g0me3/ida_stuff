
static cdl_script_execute() {
	auto err;
	Message("CDL Autorun start.\n");
	if (SegByName("ppu")!=BADADDR) {
		Message("CDL type: SNES\n");
		if((err = CompileEx("D:\\work\\tools\\ida68\\idc\\cdl_snes.idc",1)) == 0)
			main();
		else
			Message("Compilation error: \"%s\"\n",err);
	} else if (SegByName("Z80")!=BADADDR) {
		Message("CDL type: SMD\n");
		if((err = CompileEx("D:\\work\\tools\\ida68\\idc\\cdl_smd.idc",1)) == 0)
			main();
		else
			Message("Compilation error: \"%s\"\n",err);
	} else
		Message("Unknown ROM type!\n");
}
