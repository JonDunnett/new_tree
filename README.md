# new_tree
rework of COMP_375 project

This repository contains the code for a grammar defined generation of a tree 

Files:
* main.cpp - main function only 
* functions.cpp - contains helper functions 
* classes.cpp - contains class definitions and member function prototypes

NOTE: I know its proper to have .h and .cpp files. I'm keeping it small because the structure has been changing frequently and I'd rather not have to go through 6 or 7 files each time. I will eventually restructure and place code in the proper files with the proper extensions.

grammar format
 ```
 {\n
 [Non-terminal]:[production]\n
 [Non-terminal]:[production]\n
 [Non-terminal]:[production]|[production]|[production]\n
 ...
 }
 ```
 example (S ("start") rule is mandatory)
 ```
 {
 S:[XBB]
 B:[XBB]|[XB]
 X:+|-
 }
 ```
