Hi,

Welcome to the search of passwords belonging hashes.
This project has been made by Jérôme de Groote (42503) and Léopold Mols (53212)

To launch the program, you have to follow these steps one by one :


1. Open your commands terminal
2. Go and enter the right directory ("RainbowTable")
3. Open the file "HashToUncypher.txt" to put in, line by line, every hash you want to decypher. There should be only one hash by line, no line between 2 hashes, and the file should finish with a hash and not with a space, a character, a line return or whatever else than a hash.
4. Save the file.
5. Enter the command "g++ sha256-main.cpp sha256.cpp tableGeneration.cpp uncypher.cpp -o sha256-main -std=c++17"
6. Wait
7. Wait
8. Wait (a long time)
9. You should find the results in the text file named "ResultTable.txt"

There you go !

Clarification :
- The rainbow table is ordered belonging the hashes first on the numbers and secondly on the letters.
- As threads are used to uncypher several hashes at once, the results will all be written in the file "ResultTable.txt" at once to avoid several threads writing in the file at the same time and Gege 2 different results. So you need to wait the end of the program.