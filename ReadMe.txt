Hi,

Welcome to the search of passwords belonging hashes.
This project has been made by Jérôme de Groote (42503) and Léopold Mols (53212)



GENERATING THE TABLE : 
1. Open your commands terminal
2. Go and enter the right directory ("RainbowTable")
3. Enter the command "./scriptRTGeneration.sh"
4. Wait
5. The rainbow table should be generated as a text file named "RainbowTable.txt"


UNCYPHER 100 HASHES :
1. Open your commands terminal
2. Go and enter the right directory ("RainbowTable")
3. Open the file "HashesToUncypher.txt" to put in, line by line, every hash you want to decypher. There should be only one hash by line, no line between 2 hashes, and the file should finish with a hash and not with a space, a character, a line return or whatever else than a hash.
4. Save the file.
5. Wait
7. You should find the results in the text file named "ResultTable.txt"



There you go !

Clarification :
- The rainbow table is ordered belonging the passwords length first, then, on the hashes : on the numbers firstly and secondly on the letters.
- As threads are used to uncypher several hashes at once, the results will all be written in the file "ResultTable.txt" at once to avoid several threads writing in the file at the same time and get 2 different results. So you need to wait the end of the program to see all the results in the file "ResultTable.txt"