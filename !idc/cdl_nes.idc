
#include <idc.idc>
#include <functions.idc>

//#define DO_DATA_OFFSET
#define DO_CODE_OFFSETS
//#define DO_DATA
#define DO_CODE
#define DO_ALT_MESSAGES
//#define DO_CMT_CLEAR

//#define FDS_ADJUST

static main(void) {
	auto cdlFileName, cdlFile, cdlOpen;
	cdlFileName = getCdlFilename();

	MakeNames();

	cdlFile = fopen(cdlFileName, "rb");
	if( cdlFile == 0 ) {
		cdlFileName = AskFile(0,"*.cdl","Choose a CDL-file Manually");
		cdlFile = fopen(cdlFileName, "rb");
	}
	if( cdlFile != 0 ) {
		Message("CDL file \"%s\" opened succesfull!\n", cdlFileName);
		cdlOpen = 1;
	} else {
		cdlOpen = 0;
	}

	if (1)
	{
		auto cd, ncd, secondpass = 0;
		auto seg = 1;

		Message("SEG analyze start\n");

		auto segcount = 1, onesingleseg = 0, onesingleorg = 0, miltisingleorg = 0;
		auto segs6 = 0, seg6 = 0;
		auto segs8 = 0, seg8 = 0;
		auto segsA = 0, segA = 0;
		auto segsC = 0, segC = 0;
		auto segsE = 0, segE = 0;
		auto segsmask = 0;

		while (SegByBase(segcount) != BADADDR) {
			auto sgo = getSegOrg(segcount);
			if(sgo == 0x6000) {
				segs6++;
				seg6 = segcount;
			} else if(sgo == 0x8000) {
				segs8++;
				seg8 = segcount;
			} else if(sgo == 0xA000) {
				segsA++;
				segA = segcount;
			} else if(sgo == 0xC000) {
				segsC++;
				segC = segcount;
			} else if(sgo == 0xE000) {
				segsE++;
				segE = segcount;
			}
			segcount++;
		}

		if(segs6 == 1) {
			miltisingleorg++;
			onesingleseg = seg6;
			onesingleorg = 0x6000;
			segsmask = segsmask | 1;
		}
		if(segs8 == 1) {
			miltisingleorg++;
			onesingleseg = seg8;
			onesingleorg = 0x8000;
			segsmask = segsmask | 2;
		}
		if(segsA == 1) {
			miltisingleorg++;
			onesingleseg = segA;
			onesingleorg = 0xA000;
			segsmask = segsmask | 4;
		}
		if(segsC == 1) {
			miltisingleorg++;
			onesingleseg = segC;
			onesingleorg = 0xC000;
			segsmask = segsmask | 8;
		}
		if(segsE == 1) {
			miltisingleorg++;
			onesingleseg = segE;
			onesingleorg = 0xE000;
			segsmask = segsmask | 16;
		}

		if(miltisingleorg == 0) {
			Message(" No single segments found!\n");
		} else if(miltisingleorg > 1) {
			Message(" Multiple single segments found: ");
			if(segs6 == 1) Message("segment %d ORG = 0x6000, ", seg6);
			if(segs8 == 1) Message("segment %d ORG = 0x8000, ", seg8);
			if(segsA == 1) Message("segment %d ORG = 0xA000, ", segA);
			if(segsC == 1) Message("segment %d ORG = 0xC000, ", segC);
			if(segsE == 1) Message("segment %d ORG = 0xE000", segE);
			Message("\n");
		} else {
			Message(" Single segment %d ORG = %04x!\n", onesingleseg, onesingleorg );
		}

		Message("SEG analyze is over\n");

		auto segea, segea_orig, segsize, segorg, segorgmask, segbase, stop, segorg_backup;

//		if(cdlOpen == 0) {
			segea_orig = FirstSeg();
			segorg = SegStart(segea_orig) - MK_FP(AskSelector(SegByName(SegName(segea_orig))),0);
			segsize = SegEnd(segea_orig) - segea_orig;
			segorgmask = 0xFFFF;
//		}

		auto codelog = 0, datalog = 0, pcmlog = 0, unusedlog = 0;
		do {
			auto i = 0, segeai, optype, opvalue, opsize = 0, lastop = 0, lastopaddr = 0, lastopaddrbit = 0, ofst, byteread = 0, firstoffset = 0xffff, segname, segidx;

			if(secondpass == 0) {
//				if(cdlOpen == 1) {
//					segea_orig = SegByBase(seg);
//					segbase = MK_FP(AskSelector(SegByName(SegName(segea_orig))),0);
//					segorg = getSegOrg(seg);
//					segsize = getSegSize(seg);
//					segorgmask = ~(segsize - 1);
//				} else {
					segea_orig = NextSeg(segea_orig);
					segname = SegName(segea_orig);
					segidx = SegByName(segname);
					if(segidx == -1) {
//						Message(">error ");
						if(substr(segname,0,4) == "BANK") {
							segidx = xtol(substr(segname,4,-1)) + 1;
//							Message(form("bank name is %s, bank idx is %02x\n",segname, segidx - 1));
						}
					}
					segbase = MK_FP(AskSelector(segidx),0);
					segorg = SegStart(segea_orig) - segbase;
					segsize = SegEnd(segea_orig) - segea_orig;
					if((segsize & 0x1FFF) != 0)
						segorgmask = 0xFFFF;
					else
						segorgmask = ~(segsize - 1);
//				}
				Message("Seg EA=%08x, BASE=%08x ORG=%04x SIZE=%04x MASK=%04x\n>first pass\n", segea_orig, segbase, segorg, segsize, segorgmask);
			} else {
				Message(">second pass\n");
			}

			segea = segea_orig;

			do {
				segeai = segea + i;

#ifdef FDS_ADJUST
/*
				if((segea == 0x6000) && (i == 0x600)) {
					i = 0;
					segea = 0x16600;
					segsize = 0x7a00;
					segbase = 0x10000;
					segorg = 0x6600;
					segorgmask = 0xFFFF;
					Message(" > Seg EA=%08x, ORG=%04x SIZE=%04x MASK=%04x\n>first pass\n", segea, segorg, segsize, segorgmask);
				} //*/

				if((segea == 0x6000) && (i == 0x4140)) {
					i = 0;
/*					segea = 0x28140;
					segsize = 0x3eb0;
					segbase = 0x1E000; //*/
					segea = 0x36140;
					segsize = 0x22c0;
					segbase = 0x2C000;

					segorg = 0xA140;
					segorgmask = 0xFFFF;
					Message(" > Seg EA=%08x, ORG=%04x SIZE=%04x MASK=%04x\n>first pass\n", segea, segorg, segsize, segorgmask);
				} //*/

#endif

				if(secondpass == 0) {
					if(!ncd) {
						if(cdlOpen == 1) {
							cd = fgetc(cdlFile);
//							if(cd == -1)
//								cd = 0;
						} else
//							cd = 0;
							cd = -1;
					} else
						ncd = 0;

//					Message("segeai = %08x, cdl = %02x\n", segeai, cd);

					if(cd != -1) {

#ifdef DO_CMT_CLEAR
					MakeComm(segeai, "");
					MakeComm(segeai+1, "");
#endif

					if((cd & 3) == 2) {
						if(cd & 0x40) {
#ifdef DO_ALT_MESSAGES
							MakeComm(segeai, form("*%1xp ",((cd&0xc)>>1)+8));
#else
							MakeComm(segeai, "pcm");
#endif

#ifdef DO_DATA
							MakeByte(segeai);
#endif
							pcmlog++;
							if(byteread > 0)
								byteread--;
						} else {
							if(cd & 0x80) {
								if (cd & 0x20)
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, "*6d ");
#else
									MakeComm(segeai, "[data] used at 6000");
#endif
								else
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, "*6d ");
#else
									MakeComm(segeai, "data used at 6000");
#endif
							} else {
								if (cd & 0x20)
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, form("*%1xd ",((cd&0xc)>>1)+8));
#else
									MakeComm(segeai, form("[data] used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
								else
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, form("*%1xd ",((cd&0xc)>>1)+8));
#else
									MakeComm(segeai, form("data used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
							}
							if(byteread == 0) {
								ofst = Byte(segeai);
								byteread++;
							}
							if(cdlOpen == 1) {
								cd = fgetc(cdlFile);
								if(cd == -1)
									cd = 0;
							} else
								cd = 0;
							ncd = 1;
							ofst = ofst | (Byte(segeai + 1) << 8);
							byteread++;
							if(((cd & 3) == 2) && lastop && (lastopaddrbit == (i & 1)) && ((ofst >= segorg) && (ofst < (segorg + segsize))/*(ofst & segorgmask) == segorg)*/)) {
								if(cd & 0x80) {
									if (cd & 0x20)
#ifdef DO_ALT_MESSAGES
										MakeComm(segeai+1, "*6d ");
#else
										MakeComm(segeai+1, "[data] used at 6000");
#endif
									else
#ifdef DO_ALT_MESSAGES
										MakeComm(segeai+1, "*6d ");
#else
										MakeComm(segeai+1, "data used at 6000");
#endif
								} else {
									if (cd & 0x20)
#ifdef DO_ALT_MESSAGES
										MakeComm(segeai+1, form("*%1xd ",((cd&0xc)>>1)+8));
#else
										MakeComm(segeai+1, form("[data] used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
									else
#ifdef DO_ALT_MESSAGES
										MakeComm(segeai+1, form("*%1xd ",((cd&0xc)>>1)+8));
#else
										MakeComm(segeai+1, form("data used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
								}
#ifdef DO_DATA
								if(isCode(GetFlags(segeai))) {
									MakeUnknown(segeai, 1, DOUNK_SIMPLE);
									MakeWord(segeai);
								} else if(!isData(GetFlags(segeai))) {
									MakeWord(segeai);
								}
#endif
								if((lastopaddr == i) || ((ofst & (segsize - 1)) < firstoffset))
									firstoffset = ofst & (segsize - 1);
#ifdef DO_DATA_OFFSETS
								OpOff(segeai,0,segbase);
#endif
								ncd = 0;
								i++;
								datalog++;
								byteread--;
								byteread--;
							} else {
#ifdef DO_DATA
								if(isCode(GetFlags(segeai))) {
									MakeUnknown(segeai, 1, DOUNK_SIMPLE);
									MakeByte(segeai);
								} else if(!isData(GetFlags(segeai))) {
									MakeByte(segeai);
								}
#endif
								byteread--;
								ofst = (ofst >> 8) & 0xFF;
							}
						}
						datalog++;
					} else if((cd & 3) == 0) {
#ifdef DO_ALT_MESSAGES
						MakeComm(segeai, "*-- ");
#else
						MakeComm(segeai, "");
#endif
						if(lastop && (lastopaddrbit == (i & 1)) && (i < firstoffset) && (!isCode(GetFlags(segeai)))) {
							if(byteread == 0) {
								ofst = Byte(segeai);
								byteread++;
							}
							if(cdlOpen == 1) {
								cd = fgetc(cdlFile);
								if(cd == -1)
									cd = 0;
							} else
								cd = 0;
							ncd = 1;
#ifdef DO_ALT_MESSAGES
							MakeComm(segeai+1, "*-- ");
#endif
							if((cd & 3) == 0) {
								ofst = ofst | (Byte(segeai + 1) << 8);
								byteread++;
								if((ofst >= segorg) && (ofst < (segorg + segsize))/*(ofst & segorgmask) == segorg*/) {
#ifdef DO_DATA
									MakeUnknown(segeai, 2, DOUNK_SIMPLE);
									MakeWord(segeai);
#endif
									if((lastopaddr == i) || ((ofst & segorgmask) < firstoffset))
										firstoffset = (ofst & segorgmask);
#ifdef DO_DATA_OFFSETS
									OpOff(segeai,0,segbase);
#endif
								}
								ncd = 0;
								i++;
								unusedlog++;
								byteread--;
								byteread--;
							}
						} else {
							if(byteread > 0)
								byteread--;
						}
						unusedlog++;
					} else {
						if(byteread > 0)
							byteread--;
						if(opsize < 2) {
#ifdef DO_CODE
							if(isData(GetFlags(segeai)))
								MakeUnknown(segeai, 3, DOUNK_SIMPLE);
							if((opsize = MakeCode(segeai)) == 0) {
								MakeUnknown(segeai, 3, DOUNK_SIMPLE);
								opsize = MakeCode(segeai);
							}
#endif
							lastop = Byte(segeai);
							lastop = (lastop == 0x20); // || (lastop == 0x6C);
							lastopaddr = (i + 3);
							lastopaddrbit = ((i + 3) & 1);
							firstoffset = 0xffff;
						}
						else
							opsize--;

						MakeComm(segeai, "");
						if((cd & 3) == 1) {
							if(cd & 0x80) {
								if(cd & 0x10)
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, "*6c ");
#else
									MakeComm(segeai, "[code] used at 6000");
#endif
								else
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, "*6c ");
#else
									MakeComm(segeai, "code used at 6000");
#endif
							} else {
								if(cd & 0x10)
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, form("*%1xc ",((cd&0xc)>>1)+8));
#else
									MakeComm(segeai, form("[code] used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
								else
#ifdef DO_ALT_MESSAGES
									MakeComm(segeai, form("*%1xc ",((cd&0xc)>>1)+8));
#else
									MakeComm(segeai, form("code used at %4x", ((cd & 0x0c) << 11) + 0x8000));
#endif
							}

						} else {
#ifdef DO_ALT_MESSAGES
							if(cd & 0x80)
								MakeComm(segeai, "*6c ");
							else
								MakeComm(segeai, form("*%1xc ",((cd&0xc)>>1)+8));
#else
							if(cd & 0x80) {
								if((cd & 0x30)==0x00) MakeComm(segeai, "code used as data at 6000");
								else if((cd & 0x30)==0x10) MakeComm(segeai, "[code] used as data at 6000");
								else if((cd & 0x30)==0x20) MakeComm(segeai, "code used as [data] at 6000");
								else if((cd & 0x30)==0x30) MakeComm(segeai, "[code] used as [data] at 6000");
							}
							else {
								if((cd & 0x30)==0x00) MakeComm(segeai, form("code used as data at %4x", ((cd & 0x0c) << 11) + 0x8000));
								else if((cd & 0x30)==0x10) MakeComm(segeai, form("[code] used as data at %4x", ((cd & 0x0c) << 11) + 0x8000));
								else if((cd & 0x30)==0x20) MakeComm(segeai, form("code used as [data] at %4x", ((cd & 0x0c) << 11) + 0x8000));
								else if((cd & 0x30)==0x30) MakeComm(segeai, form("[code] used as [data] at %4x", ((cd & 0x0c) << 11) + 0x8000));
							}
#endif
							datalog++;
						}
						codelog++;
					}
					} // if(op != -1)
				} else {
					auto opmasked;
					optype = GetOpType(segeai,0);
					if( (optype == 2) || (optype == 3) || (optype == 4)) {
						opvalue = GetOperandValue(segeai,0);
						opmasked = (opvalue & segorgmask);
#ifdef DO_CODE_OFFSETS
						if(opmasked < 0x6000) {
							OpOff(segeai,0,0);
						} else if((opmasked >= segorg) && (opmasked < (segorg + segsize))/*opmasked == segorg*/) {
							OpOff(segeai,0,segbase);
//							Message("op at segeai = 0x%08X, opvalue = %04X, opmasked = %04X, segbase = %08X\n",segeai, opvalue, opmasked, segbase);
						} else if(miltisingleorg > 1)
							makeOffsetMulti(opmasked, segeai, seg6, seg8, segA, segC, segE, segsmask);
						else if((miltisingleorg == 1)&&(opmasked == onesingleorg))
							OpOff(segeai,0,MK_FP(AskSelector(onesingleseg),0));
						else if((opmasked < 0x8000) && (seg6 == 0))
							OpOff(segeai,0,0);
#endif
					} else if(optype == 7) {
						auto opcode = Byte(segeai);
						if((opcode == 0x20) || (opcode == 0x4C)) {
							opvalue = Word(segeai + 1);
							opmasked = (opvalue & segorgmask);
#ifdef DO_CODE_OFFSETS
							if(opmasked < 0x6000)
								OpOff(segeai,0,0);
							else if((opmasked >= segorg) && (opmasked < (segorg + segsize))/*opmasked == segorg*/) {
								OpOff(segeai,0,segbase);
//								Message("op at segeai = 0x%08X, opvalue = %04X, opmasked = %04X, segbase = %08X\n",segeai, opvalue, opmasked, segbase);
							} else if(miltisingleorg > 1)
								makeOffsetMulti(opmasked, segeai, seg6, seg8, segA, segC, segE, segsmask);
							else if((miltisingleorg == 1)&&(opmasked == onesingleorg))
								OpOff(segeai,0,MK_FP(AskSelector(onesingleseg),0));
							else if((opmasked < 0x8000) && (seg6 == 0))
								OpOff(segeai,0,0);
#endif
						}
					}
				}
				i++;
			} while (i < segsize);
			if(secondpass == 1) {
				secondpass = 0;
				stop = NextSeg(segea_orig);
				seg++;
			} else {
				secondpass = 1;
				Wait();
			}
//		} while (SegByBase(seg) != BADADDR);
		} while (stop != BADADDR);

//		garbage_collector();

//		segea = SegByBase(seg - 1) + segsize;
//		MakeUnknown(segea - 6, 6, DOUNK_SIMPLE);
//		MakeWord(segea - 6);
//		if(!OpOff(segea - 6,0,MK_FP(AskSelector(seg - 1),0)))
//			OpOff(segea - 6,0,MK_FP(AskSelector(seg - 2),0));
//		MakeWord(segea - 4);
//		if(!OpOff(segea - 4,0,MK_FP(AskSelector(seg - 1),0)))
//			OpOff(segea - 4,0,MK_FP(AskSelector(seg - 2),0));
//		MakeWord(segea - 2);
//		if(!OpOff(segea - 2,0,MK_FP(AskSelector(seg - 1),0)))
//			OpOff(segea - 2,0,MK_FP(AskSelector(seg - 2),0));

		Message("CDL file has been processed successfully.\n");
		Message("	CODE bytes:   0x%x\n",codelog);
		Message("	DATA bytes:   0x%x (including PCM data bytes: 0x%x)\n",datalog,pcmlog);
		Message("	UNUSED bytes: 0x%x\n",unusedlog);
	} else {
		Message("Can't open CDL file: \"%s\"\n", cdlFileName);
		return -1;
	}
}

static getCdlFilename() {
	auto extPos, idbFileName = GetIdbPath();
	extPos = strstr(idbFileName, ".idb");
	return substr(idbFileName, 0, extPos) + ".cdl";
}

static MakeNames() {
	MakeName(0x2000,"_PPU_CTRL");
	MakeName(0x2001,"_PPU_MASK");
	MakeName(0x2002,"_PPU_STATUS");
	MakeName(0x2003,"_PPU_OAM_ADDR");
	MakeName(0x2004,"_PPU_OAM_DATA");
	MakeName(0x2005,"_PPU_SCROLL");
	MakeName(0x2006,"_PPU_ADDR");
	MakeName(0x2007,"_PPU_DATA");

	MakeName(0x4000,"_APU_PULSE1_ENV");
	MakeName(0x4001,"_APU_PULSE1_SWEEP");
	MakeName(0x4002,"_APU_PULSE1_TIME");
	MakeName(0x4003,"_APU_PULSE1_LEN");
	MakeName(0x4004,"_APU_PULSE2_ENV");
	MakeName(0x4005,"_APU_PULSE2_SWEEP");
	MakeName(0x4006,"_APU_PULSE2_TIME");
	MakeName(0x4007,"_APU_PULSE2_LEN");
	MakeName(0x4008,"_APU_TRI_COUNT");
	MakeName(0x4009,"_APU_TRI_UNUSED");
	MakeName(0x400a,"_APU_TRI_TIME");
	MakeName(0x400b,"_APU_TRI_LEN");
	MakeName(0x400c,"_APU_NOISE_ENV");
	MakeName(0x400d,"_APU_NOISE_UNUSED");
	MakeName(0x400e,"_APU_NOISE_LOOP");
	MakeName(0x400f,"_APU_NOISE_LEN");
	MakeName(0x4010,"_APU_DMC_FREQ");
	MakeName(0x4011,"_APU_DMC_LOAD");
	MakeName(0x4012,"_APU_DMC_ADDR");
	MakeName(0x4013,"_APU_DMC_LEN");
	MakeName(0x4014,"_PPU_OAM_DMA");
	MakeName(0x4015,"_APU_STATUS");
	MakeName(0x4016,"_PAD0_REG");
	MakeName(0x4017,"_PAD1_REG");
}

static makeOffsetMulti(opmasked, segeai, seg6, seg8, segA, segC, segE, segsmask) {
	if(opmasked < 0x6000)
		OpOff(segeai,0,0);
	else if((segsmask & 1) && (opmasked == 0x6000))
		OpOff(segeai,0,MK_FP(AskSelector(seg6),0));
	else if((segsmask & 2) && (opmasked == 0x8000))
		OpOff(segeai,0,MK_FP(AskSelector(seg8),0));
	else if((segsmask & 4) && (opmasked == 0xA000))
		OpOff(segeai,0,MK_FP(AskSelector(segA),0));
	else if((segsmask & 8) && (opmasked == 0xC000))
		OpOff(segeai,0,MK_FP(AskSelector(segC),0));
	else if((segsmask & 16) && (opmasked == 0xE000))
		OpOff(segeai,0,MK_FP(AskSelector(segE),0));
	else if((opmasked < 0x8000) && (seg6 == 0))
		OpOff(segeai,0,0);
}
