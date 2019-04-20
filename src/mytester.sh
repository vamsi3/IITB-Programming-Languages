./sclp < test.c -d -icode > prof.txt
make && ./yoursclp < test.c -d -icode > ours.txt
diff prof.txt ours.txt
