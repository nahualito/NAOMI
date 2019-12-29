# NAOMI
I finally realized I needed to upload and share my SH4 / NAOMI documentation, maybe this way some traction will appear and maybe I'll even find msyefl more interested in it again.

## Updates
A working IDA Pro loader I created for d0tslash, there are 2 versions:
- naomi_loader_v0.1.py : Loads code into small segments and setups for the code, default SH4 segments are missing so this might make some pointers invalid (but still code loads withou problem)
- naomi_full_loader_v0.1.py : Loads code into the correct SH4 segments, Full SH4 segments are defined and used, it is a SLOOW loader but creates ROM and RAM segments correctly, ROM is treated as data as of now.

## Notes
Wondering how to use these? and what is this? [My blog](https://exploit.ninja/) has the information.
What is in here? most documents (I will be constantly uploading more documents as I dig them over the ridiculous amount of information and code I have lying around and pictures.

What can you find here
----------------------

- SH4 Chipset Manual
- SH-4 Programming Manual
- SuperH Dreamcast Manual
- SH-4 Dissassembler (zip and unpacked)

Setup a more organized folder structure

Any requests .. add a ticket? :)
