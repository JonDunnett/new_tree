# new_tree
rework of COMP_375 project

This repository contains the code for a grammar defined generation of a tree 

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
