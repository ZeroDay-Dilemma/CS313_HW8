AUTHORING: a list of who the writers of the code are, their affiliation (UMBC/class including time/date)
PURPOSE OF SOFTWARE: 
FILES: a short description of the purpose of each of the files, e.g. includes, source files, make file
BUILD INSTRUCTIONS: 
TESTING METHODOLOGY: 
ADDITIONAL INFORMATION: relevant and not mentioned above



Created and Written Solely by William C.
programmed with love <3
for UMBC CMSC 313 Homework assignment #8
due 4/19/2025

Both c_matrixTools.c and matrixTools.cpp provice custom implementations of some basic matrix mathmatics, including addition, multliplacaiton, and transposing. it exists under the WMatrix.

c_matrixTools.c = The full C implementation of the WMatrix + testing. it includes only standard library headers found in libc implemations, those being:
stdio.h, stdlib.h stdarg.h, and string.h 
matrixTools.h & matrixTools.cpp = the full C implementation of the WMatrix. includes both WMatrix, and WMatrix_utils, the class containing the math functions!
matrixTesterCPP.cpp is the c++ file that runs a bunch of tests on the WMatrix c++ implementation

in order to build, simply use the makefile (make all), or using gcc
gcc -std=c99 -m32 -O0 c_matrixTools.c -o c_matrixTools && ./c_matrixTools && g++ matrixTesterCPP.cpp matrixTools.cpp matrixTools.h -o matrixTools
for testing, i proformed a handful of test operations on each WMatrix, compared the mathmatical output to the true output found with my calculator, and then used a comparision function to ensure they were the same internally! Additionally, i watched for memory leaks using valgrind to ensure correct code.

``
