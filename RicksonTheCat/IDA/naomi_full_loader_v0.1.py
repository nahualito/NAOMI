# -*- coding: utf-8 -*-
"""IDA Pro NAOMI/NAOMI2 game loader

naomi_full_loader_v0.1.py - Loading the code into smaller segments and running strings on it to be able to view and check some code.

WARNING:: This IS a work in progress, the loads and strings window WILL be slow, mostly because all segments are created and some big ones marked as CODE.

This comes without WARRANTY and is for educational and security research purposes, use at your own risk!
"""
import binascii
import struct
from pprint import pformat
try:
    from idautils import *
    from idc import *
    import ida_name
    import idaapi
except ImportError:
    pass

_NAOMI_SIGNATURE     = "NAOMI"
_NAOMI_FORMAT_NAME   = "NAOMI (Arcade Game loader with ROM and RAM setup)"

class JasperThe2kCat:
    """The Games and even the NetDimm software for network boot have the same structure
    |Platform|Developer|Title Region 1|Title Region 2|...|Title Region 8|
    So we create that as a class and apply it, since is a lazy way of doing it, we name it
    based on a scrub like DSP.
    
    For more details on the structure read the previous block, for more details on DSP .. nothing I could do! *SNORT*
    
    "At least I'm not a 2,000 USD cat" --Rickson <TheCatThatHacks>
    """
    
    def __init__(self):
        """We set stuff to 0x00000000 as is ROM, we will then copy to RAM per game entries"""
        self.start_address = 0x00000000
        self.end_address = 0x00000000
        self.headers = [ {'Platform' : 0x10 },
                        {'Developer' : 0x20},
                        {'Region_1' : 0x20},
                        {'Region_2' : 0x20},
                        {'Region_3' : 0x20},
                        {'Region_4' : 0x20},
                        {'Region_5' : 0x20},
                        {'Region_6' : 0x20},
                        {'Region_7' : 0x20},
                        {'Region_8' : 0x20}
                      ]
        
    
    def AnotateHeader(self, binary_file=None, address=0x00000000):
        """We anotate the game header to make sure is correctly referenced

        Args:
            binary_file (file handler): file handler sent by the IDA Pro loader
            address (int): Base address for the ROM section of the game
        """
        start_address = address
        end_address = address
        for header in self.headers:
            for k in header:
                end_address = start_address + header[k]
                print(k)
                MakeStr(start_address, end_address)
                ida_name.set_name(start_address, k, 0)
                start_address += header[k]

    def MakeStrings(self, binary_file=None):
        """Taken from the EmbeddedToolkit"""
        ################### USER DEFINED VALUES ###################
        min_length = 5          # Minimum number of characters needed to define a string       
        string_end = [0x00]		# Possible "ending characters" for strings. A string will not be defined if it does not end with one of these characters
        ###########################################################

        start_addr = MinEA()
        end_addr = MaxEA()

        if ((start_addr is not None and end_addr is not None) and (start_addr != BADADDR and end_addr != BADADDR) and start_addr < end_addr):
            string_start = start_addr
            print "[make_strings.py] STARTING. Attempting to make strings with a minimum length of %d on data in range 0x%x to 0x%x" % (min_length, start_addr, end_addr)
            num_strings = 0;
            while string_start < end_addr:
                num_chars = 0
                curr_addr = string_start
                while curr_addr < end_addr:
                    byte = Byte(curr_addr)
                    if ((byte < 0x7F and byte > 0x1F) or byte in (0x9, 0xD, 0xA)):		# Determine if a byte is a "character" based on this ASCII range
                        num_chars += 1
                        curr_addr += 1			
                    else:
                        if ((byte in string_end) and (num_chars >= min_length)):
                            MakeUnknown(string_start, curr_addr - string_start, DOUNK_SIMPLE)
                            if (MakeStr(string_start, curr_addr) == 1):
                                print "[make_strings.py] String created at 0x%x to 0x%x" % (string_start, curr_addr)
                                num_strings += 1
                                string_start = curr_addr
                                break
                            else:
                                print "[make_strings.py] String create FAILED at 0x%x to 0x%x" % (string_start, curr_addr)
                                break
                        else:		
                            # String does not end with one of the defined "ending characters", does not meet the minimum string length, or is not an ASCII character
                            break
                string_start += 1
            print "[make_strings.py] FINISHED. Created %d strings in range 0x%x to 0x%x" % (num_strings, start_addr, end_addr)
        else:
            print "[make_strings.py] QUITTING. Entered address values not valid."
                

class gameEntries:
    """Entries defined in the ROM to be created for RAM as CODE segments.
    
    The ROM contains the addresses entries for the game memory segments and entry point for the game, this is by default on the 0x360 address in the format:

    | Offset from ROM | RAM Address | Size of data/Segment |    

    Exceptions are caught with the 'I did everything right, and did nothing wrong' license ala DSP.

    Attributes:
        entries (array):
        PC (int):
        PC2 (int):
    """
    def __init__(self):
        """Init the variable to be able to read all the entries into a dictionary to then just parse the dictionary"""
        self.entries = []
        self.PC = None
        self.PC2 = None #Feeling like I don't know the purpose, might delete later *insert meme pose*
    
    def readGameLoops(self, binary_file=None, loop_address=0x360):
        """Reads the entries and returns an array with the dictionary consisting of ROM offset, RAM address and size of data
        
        Args:
            binary_file (file handle):
            loop_address (int):

        Returns:
            An array of dictionary entries consisting of ROM offset, RAM address and size of data
        """
        anotate_addy = loop_address
        tmp_rom_file = binary_file
        binary_file.seek(0) 
        binary_file.seek(loop_address) 
        while (1):
            # Anotating
            for i in range(3):
                MakeDword(anotate_addy)
                ida_name.set_name(anotate_addy, "entry_%s"  % anotate_addy, 0)
                anotate_addy += 4
            # More .. "pythonic" (Aka looks cool is kinda unreadable)
            (bin_offset, bin_ram, bin_size) = struct.unpack('iii', binary_file.read(12))
            if bin_size == 0 or bin_offset < 0:
                break
            self.entries.append({'ROM_Offset':bin_offset, 'RAM_Address':bin_ram, 'Segment_Size':bin_size})
            # Let's create the Segments here O_O
            binary_file.seek(bin_offset, 0)
            ##self._AddSegment(("RAM_%s" % bin_offset), bin_ram, binary_file.read(bin_size))
            self._AddData(("RAM_%s" % bin_offset), bin_ram, binary_file.read(bin_size))
            print("offset from ROM: %#x RAM Address is %#x Loop/Segment size: %#x" % (bin_offset,bin_ram, bin_size))
            binary_file.seek(anotate_addy)
        """We get the entry address (there are 2 pointers, Maybe PC and another? will read both)"""
        if self.PC == None:
            binary_file.seek(0x420)
            MakeDword(0x420)
            ida_name.set_name(0x420, "Entry_Point", 0)
            MakeDword(0x424)
            ida_name.set_name(0x424, "RESET_Entry_Point", 0)
            (self.PC, self.PC2) = struct.unpack('ii', binary_file.read(8))
        return 0
    
    def getEntryPoint(self):
        """Returns current value of self.PC if not set it will return None"""
        return self.PC
    
    def getEntryPoint2(self):
        return self.PC2
    
    def cleanEntries(self):
        """Clean the entries array to allow to have either another binary or have another offset"""
        del self.entries[:]
        self.PC = self.PC2 = None
        return True
    
    def __repr__(self):
        return pformat(self.entries, indent=4, width=1)
    
    def _AddSegment(self, name, base_address, data=None):
        """Add a segment to the IDB with some basic options set for convenience."""
        s = idaapi.segment_t()

        s.startEA = base_address
        s.endEA = base_address + len(data)
        s.bitness = 1 # 32-bit
        s.align = idaapi.saRelByte
        s.comb = idaapi.scPub
        s.sel = idaapi.setup_selector(0)

        # We mark the segments as code, as we know these are loops in memory
        idaapi.add_segm_ex(s, name, "CODE", idaapi.ADDSEG_NOSREG | idaapi.ADDSEG_OR_DIE)
        idaapi.mem2base(data, base_address)

    def _AddData(self, name, base_address, data=None):
        idaapi.mem2base(data, base_address)

    def AddDefaultSH4Segments(self):
        """Add a segment to the IDB with some basic options set for convenience."""
        base_address = 0x0C000000
        # Create segments on the range of 0x04000000 bytes
        for segment in range(5):
            name = "Area_%d" % (segment + 3)
            s = idaapi.segment_t()
            s.startEA = base_address
            s.endEA = base_address + 0x04000000
            s.bitness = 1 # 32-bit
            s.align = idaapi.saRelByte
            s.comb = idaapi.scPub
            s.sel = idaapi.setup_selector(0)
            # We mark the segments as code, as we know these are loops in memory
            idaapi.add_segm_ex(s, name, 'CODE', idaapi.ADDSEG_NOSREG | idaapi.ADDSEG_OR_DIE)
            base_address += 0x04000000
        
        # Second set of segments (now is the privileged ones)
        base_address = 0x80000000
        # Create segments on the range of 0x04000000 bytes
        for segment in range(4):
            name = "Priv_%d" % (segment + 1)
            s = idaapi.segment_t()
            s.startEA = base_address
            if base_address == 0xE0000000:
                s.endEA = base_address + 0x10000000
            else:
                s.endEA = base_address + 0x20000000
            s.bitness = 1 # 32-bit
            s.align = idaapi.saRelByte
            s.comb = idaapi.scPub
            s.sel = idaapi.setup_selector(0)
            # We mark the segments as code, as we know these are loops in memory
            idaapi.add_segm_ex(s, name, None, idaapi.ADDSEG_NOSREG | idaapi.ADDSEG_OR_DIE)
            base_address += 0x20000000
        
    
    def CreateSegments(self, binary_file=None):
        if len(self.entries):
            return False
        
        for entry in self.entries:
            binary_file.seek(entry['ROM_Offset'])
            data = binary_file.read(entry['Segment_Size'])
            self._AddSegment("RAM_%s" % entry['RAM_Address'], entry['RAM_Address'], data)

    def addIDA_entry(self):
        idaapi.add_entry(self.PC, self.PC, '_start', 1)

    def makeDWordTables(self, start_address=0x130, end_address=0x260):
        """Making the data within the addresses DWords (32 bit addies)"""
        current_addr = start_address
        while current_addr < end_address:
            MakeDword(current_addr)
            current_addr += 4

            
def accept_file(li, n):
    """
    Check if the file is of supported format
    @param li: a file-like object which can be used to access the input data
    @param n : format number. The function will be called with incrementing 
               number until it returns zero
    @return: 0 - no more supported formats
             string "name" - format name to display in the chooser dialog
             dictionary { 'format': "name", 'options': integer }
               options: should be 1, possibly ORed with ACCEPT_FIRST (0x8000)
               to indicate preferred format
    """

    # check the NAOMI signature
    li.seek(0)
    if li.read(5) == _NAOMI_SIGNATURE:
        # accept the file
        return {"format": "NAOMI Game Dump", "processor": "sh4", "options":1|idaapi.ACCEPT_FIRST}
    
    # unrecognized format
    return 0

def load_file(li, neflags, format):
    """
    Load the file into database
    @param li: a file-like object which can be used to access the input data
    @param neflags: options selected by the user, see loader.hpp
    @return: 0-failure, 1-ok
    """


    idaapi.set_processor_type("sh4", SETPROC_ALL|SETPROC_FATAL)

    li.seek(0, idaapi.SEEK_END)
    size = li.tell()    
    li.seek(0)
    rom_data = li.read(size)
    
    s = idaapi.segment_t()
    s.startEA = 0
    s.endEA = size
    s.bitness = 1 # 32-bit
    s.align = idaapi.saRelByte
    s.comb = idaapi.scPub
    s.sel = idaapi.setup_selector(0)

    idaapi.add_segm_ex(s, "ROM", "DATA", idaapi.ADDSEG_NOSREG | idaapi.ADDSEG_OR_DIE)
    idaapi.mem2base(rom_data, 0)


    headr = JasperThe2kCat()
    headr.AnotateHeader(binary_file=li)
    headr.MakeStrings(binary_file=li)
    gentries = gameEntries()
    gentries.AddDefaultSH4Segments()
    
    gentries.readGameLoops(binary_file=li)
    #gentries.CreateSegments(binary_file=li)
    gentries.makeDWordTables()
    gentries.makeDWordTables(start_address=0x2a0, end_address=0x1000)
    gentries.addIDA_entry()

    print("load ok")
    return 1
    
    