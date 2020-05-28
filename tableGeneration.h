/**
 * This will create a password length ordered and hash-on alphabetically ordered rainbow text file
 */

#ifndef TABLEGENERATION_H
#define TABLEGENERATION_H
#include "iostream"
#include "stdio.h"
#include "vector"
#include <thread>
#include <fstream>
#include <filesystem>
#include <future>

#ifdef _WIN32
#include <chrono>
#endif

using namespace std;

namespace rainbow
{

    void generate100Hashes();

    /**
     * @brief fileSize
     * The size one of the 3 rainbow table files must not exceed
     */
    inline long fileSize = 11999995896;

    /**
     * @brief nbPassWordsInEveryLine
     * The number of cypherization and reduction contained
     * in a single line of the rainbow table
     */
    inline unsigned int nbPassWordsInEveryLine = 2000;

    /**
     * @brief nbLinesToDelete
     * Number of lines that will be deleted at once in the unsorted rainbow tale tex file
     */
    inline long nbLinesToDelete = 500000;

    /**
     * @brief noChar
     * If a method needs to create a text file, but without any hash char in the file name,
     * the method that calls it will give it this char
     */
    inline char noChar = '!';

    /**
     * @brief noNumber
     * If a method needs to create a text file, but without the number of the thread in the file name,
     * the method that calls it will give it this char
     */
    inline int noNumber = -1;

    /**
     * @brief nbThreadsThatGeneratesPasswords
     * This is the number of thread that will each generate a line
     * that contains a randow password and its (nbPassWordsInEveryLine)^th hash
     */
    inline unsigned int nbThreadsThatGeneratesPasswords = 15;

    /**
     * @brief generateOneLine
     * Generates one line of the rainbow table, from the 1st password to the 35th hash
     * @param password
     * The password from which the line has to be generated
     * @return a vector of 3 strings : the first password, a space and the 35th hash
     */
    vector<string> generateOneLine(string& password);

    /**
     * @brief generate3RainbowTableFiles
     * Generates 3 different files that each contains a different password length :
     * 6, 7 and 8 letters in the password
     */
    void generate3RainbowTableFiles();

    /**
     * @brief generateSortedRainbowTables
     * Generates a new text file that will contain
     * the passwords (of length passwordLength) and their hashes
     * They will be ordered on the password length
     * then alphabetically on the hash
     * @param passwordLength
     * The length of the passwords ocntained in the not sorted rainbow table text file
     */
    void generateSortedRainbowTables(unsigned int passwordLength);

    /**
     * @brief generatePasswordLengthDifferentRainbowTable
     * Generates rainbow tables depending on the password length
     * @param passwordLength
     * The length of the passwords the will e in the rainbow table generated
     */
    void generateUnsortedRainbowTables(unsigned int passwordLength);

    /**
     * @brief generateFinalRainbowTable
     * Generates the final rainbow table text file
     * that will contain every 1st password and every 35th hash.
     * They will be ordered on the password length
     * then alphabetically on the hash
     */
    void generateFinalRainbowTable();

    /**
     * @brief reduceTable
     * Creates a new rainbow table text file by ignoring every duplicate hash
     * @param oldFileName
     * The old rainbow table text file name
     * @param lastSortedLine
     * The last line that has been read to be sorted
     * @param passwordLength
     * The lengthe of the passwords contained in the rainbow table text file
     */
    void reduceTable(string& oldFileName, vector<string> lastSortedLine, unsigned int passwordLength);



    //vector<string> pushInLine(unsigned int passwordLength);
    void generateSortedRainbowTableCharPerChar(string& fileToWriteInName, string& fileToReadInName);
    void generateUnsortedRainbowTablePerCharAt(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName);
    void deleteReadLinesInFile(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName);
    void addSortedFilesToCorrespondingRainbowTable(unsigned int passwordLength);
    void createEachCharHashTextFile(unsigned int passwordLength);
    void sortEveryCharUnsortedTextFile(unsigned int passwordLength/*, char sortFilesThisChar, char sortFilesUntilThisChar*/);
    void sort(unsigned int passwordLength);
    void threadSorting();
    void putAllInFinalTable(unsigned int passwordLength);
}
#endif // TABLEGENERATION_H
