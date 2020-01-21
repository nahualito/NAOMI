# NAOMI
I finally realized I needed to upload and share my SH4 / NAOMI documentation, maybe this way some traction will appear and maybe I'll even find myself more interested in it again.

# Notebooks
I've been using jupyter notebook to try and explain what I did to figure out how to reverse this header, the [game header](NAOMI%20Game%20Header.ipynb) is still (maybe?) a bit of a mess where I'm slowly explaining what did I do to figure out stuff if anyone is interested enough, the [IDA loader](jupyter/NAOMI%20IDA%20Pro%20Loaders.ipynb) is pretty much done and has the instructions to create the loader, the notebooks are in python 3, the loaders are python 2, because IDA Pro that's why.


## Updates
### 20/01/2020
- Commit of better loader, still you have 2 loaders:
1. [Full Segment Loader](RicksonTheCat/IDA/naomi_full_loader_v0.1.py) which will create all the segments not only for the SH4 chipset documentation but also the memory segments and load the code.
2. [Only code in memory Loader](RicksonTheCat/IDA/naomi_loader_v0.1.py) this will only create enough memory segments exactly where is to be copied, this will be WAY quicker to load BUT any references to undefined memory will be marked as red (Fair warning)

I might be bored enough at one time to play with GHidra's loaders and get one going for this, if at any point make one and want it linked here (why would you? nobody hits this anyway LOL) let me know aka open a ticket.

### First Updates:
A working IDA Pro loader I created for d0tslash, there are 2 versions:
- naomi_loader_v0.1.py : Loads code into small segments and setups for the code, default SH4 segments are missing so this might make some pointers invalid (but still code loads withou problem)
- naomi_full_loader_v0.1.py : Loads code into the correct SH4 segments, Full SH4 segments are defined and used, it is a SLOOW loader but creates ROM and RAM segments correctly, ROM is treated as data as of now.

## Notes
Wondering how to use these? and what is this? [My blog](https://exploit.ninja/) has the information for the first codes.
What is in here? most documents (I will be constantly uploading more documents as I dig them over the ridiculous amount of information and code I have lying around and pictures.

What can you find here
----------------------

- SH4 Chipset Manual
- SH-4 Programming Manual
- SuperH Dreamcast Manual
- SH-4 Dissassembler ([zip](SH4%20Disassemblers%20and%20bin%20utils.zip) and [unpacked](SH4%20Disassemblers%20and%20bin%20utils))
- Other code that is scaterred around the internet backed up [here](code)

Setup a more organized folder structure

Any requests .. add a ticket? :)
