#!/bin/sh
echo "\nMMAP - File1\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_mmap a.txt
echo "\nMMAP - File2\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_mmap b.txt
echo "\nMMAPe-eFile3\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_mmap c.txt
echo "FOPEN - File1\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_read a.txt
echo "\nFOPEN - File2\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_read b.txt
echo "\nFOPEN - File3\n"
time -f "time:\t%E real,\t%U user,\t%S sys" ./p1_read c.txt

