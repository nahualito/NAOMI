Copyright 1999 by Metrowerks Corp.

                             CodeWarrior
                            for Dreamcast
                                  R1
                              
                        Update 1 Release Notes
                            
                               99.5.3rw

                              
This text file lists both the additional features and the bug fixes 
contained in Update 1 for CodeWarrior for Dreamcast R1.

   CONTENTS
  
1. New Features

   1.1 MSL C++ library improved
   1.2 ALIGNALL(0xnn) linker directive
   1.3 Inline assembler supports mixed lower and upper-case
   1.4 Floating point constants in inline assembler
    
2. Bug Fixes

   2.1 Compiler Fixes
      2.1.1 SWITCH statements inside loops
      2.1.2 Struct assignment
      2.1.3 Passing aggregates to C++ constructors
      
   2.2 Assembler Fixes
      2.2.1 IF directive fixed
      2.2.2 FUNCTION directive fixed

   2.3 Library Fixes
      2.3.1 Runtime library supports C++ exception propagation

-------------------------------------------------
1. New Features

   Update 1 adds several new features to CodeWarrior for Dreamcast R1. 

1.1 MSL C++ library improved
    
    To mimic "cout" and send a character stream to the debugger
    console window, use the following code as an example:
    
         ostringstream sout;
         sout << "hello";
         string s = sout.str();
         write(1, (char*)s.c_str(), (int)s.size());
    
    This will print the output
        
         hello
         
    to the debugger console window.
             
1.2 ALIGNALL(0xnn) linker directive

    The ALIGNALL directive makes it easier to generate code with
    SHC-style alignments. Instead of individually specifying the
    alignment for a set of files, you can now set a global alignment
    for an entire section.
    
    For example, to align all the files in a .data section on an 8-byte 
    boundary, use ALIGNALL in the linker command file as follows:
    
         ALIGNALL(0x08)
         *(.data)

1.3 Inline assembler supports mixed lower and upper-case

    Opcodes and operands are no longer required to be written with
    upper-case characters. 

1.4 Floating point constants in inline assembler

    Floating point constants can now be loaded directly into registers.
    You can also pass them to inline assembly functions as parameters.

-------------------------------------------------    
2. Bug Fixes

Update 1 fixes some bugs that affected a portion of users.

2.1 Compiler Fixes

2.1.1 SWITCH statements inside loops

      The compiler now generates the correct code to test for the value 
      of the expression when using the 

           switch (expression)

      statement inside of a loop. Previously, the wrong code was
      generated at optimization level 1 or higher.

2.1.2 Struct assignment

      Sometimes a compiler error would be raised during a struct 
      assignment such as s1=s2=s3 (where s1, s2, and s3 are structs).
      This bug has been fixed.

2.1.3 Passing aggregates to C++ constructors

      A register error regarding aggregates and constructors was
      fixed. The compiler now correctly passes aggregates to the
      constructor.

2.2 Assembler Fixes

2.2.1 IF directive fixed

      The .IF conditional directive now works as outlined in the "SH 
      Assembler Reference" manual.

2.2.2 FUNCTION directive fixed

      The .FUNCTION debugging directive now works as outlined in the
      "SH Assembler Reference" manual.

2.3 Library Fixes

2.3.1 Runtime library supports C++ exception propagation

      A few changes were made to the runtime library to correct some
      problems related to the propagation of C++ exceptions.