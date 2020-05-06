/**
 * This will create a password length ordered and hash-on alphabetically ordered rainbow text file
 */

#ifndef TABLEGENERATION_H
#define TABLEGENERATION_H
#include "iostream"
#include "stdio.h"
#include "vector"

#ifdef _WIN32
#include <chrono>
#endif

using namespace std;

namespace rainbow
{

    void generate100Hashes();

    /**
     * @brief fileSize
     * the size one of the 3 rainbow table files must not exceed
     */
    inline long fileSize = 799999;//5896;
    inline long nbLinesToDelete = 500000;

    /**
     * @brief generateOneLine
     * Generates one line of the rainbow table, from the 1st password to the 35th hash
     * @param password
     * The password from which the line has to be generated
     * @return a vector of 3 strings : the first password, a space and the 35th hash
     */
    vector<string> generateOneLine(string password);

    /**
     * @brief generate3RainbowTableFiles
     * Generates 3 different files that each contains a different password length :
     * 6, 7 and 8 letters in the password
     */
    void generate3RainbowTableFiles();

    /**
     * @brief generateSortedRainbowTable
     * Generates an alphabetically sorted rainbow table text file
     */
    // I'll use this when I'll implement a for loop with the differents threads.
    //void generateSortedRainbowTable();

    /**
     * @brief generateSortedRainbowTableThread6
     * Generates a new text file that will contain
     * the 6-lettered password and their hashes
     * They will be ordered on the password length
     * then alphabetically on the hash
     */
    void generateSortedRainbowTableThread6();

    /**
     * @brief generateSortedRainbowTableThread6
     * Generates a new text file that will contain
     * the 7-lettered password and their hashes
     * They will be ordered on the password length
     * then alphabetically on the hash
     */
    void generateSortedRainbowTableThread7();

    /**
     * @brief generateSortedRainbowTableThread6
     * Generates a new text file that will contain
     * the 8-lettered password and their hashes
     * They will be ordered on the password length
     * then alphabetically on the hash
     */
    void generateSortedRainbowTableThread8();

    /**
     * @brief generateSortedRainbowTables
     * Generates a sorted  rainbow table text fil
     * with another not sorted rainbow table text file
     * @param passwordLength
     * The length of the passwords ocntained in the not sorted rainbow table text file
     */
    // I'll use this when I'll implement a for loop with the differents threads.
    void generateSortedRainbowTables(unsigned int passwordLength);

    /**
     * @brief thread6
     * generates a rainbow table text file
     * that the lines are generates with 6 letters passwords
     */
    void thread6();

    /**
     * @brief thread7
     * generates a rainbow table text file
     * that the lines are generates with 7 letters passwords
     */
    void thread7();

    /**
     * @brief thread8
     * generates a rainbow table text file
     * that the lines are generates with 8 letters passwords
     */
    void thread8();

    /**
     * @brief generateFinalRainbowTable
     * Generates the final rainbow table text file
     * that will contain every 1st password and every 35th hash.
     * They will be ordered on the password length
     * then alphabetically on the hash
     */
    void generateFinalRainbowTable();

    void reduceTable6(string oldFileName, vector<string> lastSortedLine);
    void reduceTable7(string oldFileName, vector<string> lastSortedLine);
    void reduceTable8(string oldFileName, vector<string> lastSortedLine);

    void passwords6(char firstCharOfHash);





    void generateSortedRainbowTableCharPerChar(string fileToWriteInName, string fileToReadInName);
    void generateUnsortedRainbowTablePerFirstChar(char firstCharOfHash, string fileToWriteInName, string fileToReadInName);
    void deleteReadLinesInFile(char firstCharOfHash, string fileToWriteInName, string fileToReadInName);
    void addSortedFilesToCorrespondingRainbowTable(unsigned int passwordLength);
    void createEachCharHashTextFile(unsigned int passwordLength);
    void sortEveryCharUnsortedTextFile(unsigned int passwordLength);
    void sort();
}
#endif // TABLEGENERATION_H
