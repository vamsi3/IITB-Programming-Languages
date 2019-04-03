make && ./yoursclp < test.c -d > ours.txt
./sclp < test.c -d > prof.txt
diff prof.txt ours.txt