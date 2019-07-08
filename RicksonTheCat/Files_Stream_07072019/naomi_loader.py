#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Nahualito <nahualito@exploit.ninja>
#

"""NAOMI header parser, this will help to create an SH4 IDA Loader with correct table.

This weridly enough uses python2 (You can run it on 3 but the output will be all cut and weird)
and honestly I don't feel like changing it much XD, will probably do later on.

This has heavy comments because I want people to be able to use this and grow it.

So it looks like the entire interrupt table + headers finishes around 0x500h, interrupt table
starts at 0x360h (This actually is for the BIOS too? WTF? really? REALLY?)
"""

from ctypes import *
import struct
import os
import sys
from pprint import pformat

class NAOMIHeader(LittleEndianStructure):
    """ SEGA usually puts the last 3 region headers as SAMPLE:
        Ricksons-MacBook-Air:NAOMI TheCatThatHacks$ hexdump -C CosmicSmash.bin | head -n 30
        00000000  4e 41 4f 4d 49 20 20 20  20 20 20 20 20 20 20 20  |NAOMI           |
        00000010  53 45 47 41 20 43 4f 52  50 4f 52 41 54 49 4f 4e  |SEGA CORPORATION|
        00000020  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000030  43 4f 53 4d 49 43 20 53  4d 41 53 48 20 49 4e 20  |COSMIC SMASH IN |
        00000040  4a 41 50 41 4e 20 20 20  20 20 20 20 20 20 20 20  |JAPAN           |
        00000050  43 4f 53 4d 49 43 20 53  4d 41 53 48 20 49 4e 20  |COSMIC SMASH IN |
        00000060  55 53 41 20 20 20 20 20  20 20 20 20 20 20 20 20  |USA             |
        00000070  43 4f 53 4d 49 43 20 53  4d 41 53 48 20 49 4e 20  |COSMIC SMASH IN |
        00000080  45 58 50 4f 52 54 20 20  20 20 20 20 20 20 20 20  |EXPORT          |
        00000090  43 4f 53 4d 49 43 20 53  4d 41 53 48 20 49 4e 20  |COSMIC SMASH IN |
        000000a0  4b 4f 52 45 41 20 20 20  20 20 20 20 20 20 20 20  |KOREA           |
        000000b0  43 4f 53 4d 49 43 20 53  4d 41 53 48 20 49 4e 20  |COSMIC SMASH IN |
        000000c0  41 55 53 54 52 41 4c 49  41 20 20 20 20 20 20 20  |AUSTRALIA       |
        000000d0  53 41 4d 50 4c 45 20 20  20 20 20 20 20 20 20 20  |SAMPLE          |
        000000e0  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        000000f0  53 41 4d 50 4c 45 20 20  20 20 20 20 20 20 20 20  |SAMPLE          |
        00000100  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000110  53 41 4d 50 4c 45 20 20  20 20 20 20 20 20 20 20  |SAMPLE          |
        00000120  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
                
        Other companies actually just put the title and sometimes no region:
        Ricksons-MacBook-Air:NAOMI TheCatThatHacks$ hexdump -C ZeroGunner2.bin | head -n 30
        00000000  4e 41 4f 4d 49 20 20 20  20 20 20 20 20 20 20 20  |NAOMI           |
        00000010  50 53 49 4b 59 4f 20 43  4f 2e 2c 4c 54 44 2e 20  |PSIKYO CO.,LTD. |
        00000020  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000030  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        00000040  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000050  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        00000060  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000070  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        00000080  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000090  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        000000a0  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        000000b0  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        000000c0  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        000000d0  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        000000e0  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        000000f0  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        00000100  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
        00000110  5a 45 52 4f 20 47 55 4e  4e 45 52 20 32 20 20 20  |ZERO GUNNER 2   |
        00000120  20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20  |                |
    """
    _pack_ = 1

    _fields_ = [('platform', c_char * 0x10), # SHOULD be always NAOMI
                ('dev company', c_char * 0x20),
                ('title_region1', c_char * 0x20),
                ('title_region2', c_char * 0x20),
                ('title_region3', c_char * 0x20),
                ('title_region4', c_char * 0x20),
                ('title_region5', c_char * 0x20),
                ('title_region6', c_char * 0x20), 
                ('title_region7', c_char * 0x20),
                ('title_region8', c_char * 0x20),]

    def __init__(self, file):
        if file.readinto(self) != sizeof(self):
            raise EOFError("Not enough bytes in buffer to parse header!")
    
    def dict_export(self):
        d = dict()
        for (varkey, vartype) in self._fields_:
            # We use rstrip to remove the spaces, looks nicer
            d[varkey] = getattr(self, varkey).rstrip() 
        return d

    def __repr__(self):
        d = self.dict_export()
        return pformat(d, indent=4, width=1)

class SH4InterruptTable(LittleEndianStructure):
    """ Interrupt table for SH4, taken from manuals (where else?)

    From Zero Gunner:

    00000130  d1 07 04 01 42 44 43 30  01 00 00 00 00 00 00 00  |....BDC0........|
    00000140  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
    00000150  00 00 00 00 00 00 00 00  00 00 00 00 03 00 00 00  |................|
    00000160  00 00 04 00 5f 9d 61 df  04 00 17 80 2e d2 04 00  |...._.a.........|
    00000170  3d 8b 46 48 04 00 d0 b5  0e d9 04 00 53 be 0c b7  |=.FH........S...|
    00000180  04 00 fe a5 57 75 04 00  55 09 73 7c 04 00 02 94  |....Wu..U.s|....|
    00000190  9d 39 04 00 13 97 45 47  04 00 4b 09 14 3f ff ff  |.9....EG..K..?..|
    000001a0  00 00 11 11 ff ff 00 00  11 11 ff ff 00 00 11 11  |................|
    000001b0  ff ff 00 00 11 11 ff ff  00 00 11 11 ff ff 00 00  |................|
    000001c0  11 11 ff ff 00 00 11 11  ff ff 00 00 11 11 ff ff  |................|
    000001d0  bf a6 d4 df ff ff 34 12  76 98 ff ff 78 56 32 54  |......4.v...xV2T|
    000001e0  00 02 00 01 00 00 00 00  01 01 01 01 01 01 01 01  |................|

    So we do a quick operation:
    0x1e0 - 0x130 = 0xb0 (176)
    Interrupt vectors are 32bit (cause Renesas, that's why!)
    176 / 8 = 22

    Means at least a 22 vector interrupt table, which validates SH-4 documentation
    """
    _pack_ = 1

    """ I almost feel like I should add all the user interrupts BUT I don't know yet if they are only
    in the game or also in the NetDimm BIOS (which loads the same)

    Default VBR is 0x00000000 which obviously is not the case here, this is because we have the "config"
    attached into the beggning of the file (kinda like DJI on the SDR modems :-P) So we need to remove the
    size of the config before we can randomly apply the stuff right on the correct size.

    Normal header for the data KNOWN for NAOMI is 160h (352 decimal) which is a VERY awkward number
    """ 
    _fields_ = [('PC', c_uint),
                ('SP', c_uint),
                ('Reserved1', c_uint),
                ('Reserved2', c_uint),
                ('Illegal Instruction', c_uint),
                ('Reserved3', c_uint),
                ('Slot Illegal Instruction', c_uint),
                ('Reserved4', c_uint),
                ('Reserved5', c_uint),
                ('CPU Address Error', c_uint),
                ('DMAC Address Error', c_uint),
                ('NMI Interrupt', c_uint),
                ('User Break Interrupt', c_uint),
                ('FPU Exception', c_uint),
                ('Reserved6', c_uint),
                ('Bank Overflow', c_uint),
                ('Bank Underflow', c_uint),
                ('Integer Division by Zero', c_uint),
                ('Integer Division overflow', c_uint)] #There are more but testing only with this for now

    def __init__(self, file):
        file.seek(0x360)
        if file.readinto(self) != sizeof(self):
            raise EOFError("Not enough bytes in buffer to parse Interrupt table!")
    
    def dict_export(self):
        d = dict()
        for (varkey, vartype) in self._fields_:
            d[varkey] = "0x{:08x}".format(getattr(self, varkey)) # We use rstrip to remove the spaces, looks nicer
        return d

    def __repr__(self):
        d = self.dict_export()
        return pformat(d, indent=4, width=1)  

if __name__ == "__main__":
    filer = open(sys.argv[1], "rb")
    print("-----------------------------------")
    print("[ - ] Reading the game header")
    print("-----------------------------------")
    header = NAOMIHeader(filer)
    print(header)
    print("-----------------------------------")
    print("[ - ] Reading the Interrupt Table")
    print("-----------------------------------")
    table = SH4InterruptTable(filer)
    print(table)

