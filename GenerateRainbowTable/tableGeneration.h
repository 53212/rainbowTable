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

#ifndef _WIN32
#include <chrono>
#endif

using namespace std;

namespace rainbow
{
    //chrono::seconds duration;

    // I stop it at 'g' because no hash seems to contain a letter which position in the alphabet is 'g' or later
    inline const string char_policy = "0123456789abcdef";//ghijklmnopqrstuvwxyz";

    /**
     * @brief startGen
     * Begin a timer. It will be helpful to knwo when to stop generating
     * unsorted files to let the program have the time to sort the unsorte files
     */
    inline auto startGen = chrono::high_resolution_clock::now();

    /**
     * @brief timeForGenerationInSeconds
     * Not to exceed 8 hours for the generation of the table
     */
    inline int timeForGenerationInSeconds = 28800;

    /**
     * @brief timeSupposedToSortOneLine
     * the supposed time taken to sort only one line as microseconds
     */
    inline double timeSupposedToSortOneLine = 0.001828073659838;

    /**
     * @brief oneLineSize
     * The size in octets of a single line
     */
    inline int oneLineSize = 72;

    /**
     * @brief fileSize
     * The size one of the 3 rainbow table files must not exceed
     */
    inline long fileSize = 10000000/*11999995896*/;

    /**
     * @brief nbPassWordsInEveryLine
     * The number of cypherization and reduction contained
     * in a single line of the rainbow table
     */
    inline unsigned int nbPasswordsInEveryLineForGeneration = 2000;

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
     * @brief generate100Hashes
     * Generates a text file that contains only the 2000th hashes
     */
    void generate100Hashes();

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
     * @brief generatePasswordLengthDifferentRainbowTable
     * Generates rainbow tables depending on the password length
     * @param passwordLength
     * The length of the passwords the will e in the rainbow table generated
     */
    void generateUnsortedRainbowTables(unsigned int passwordLength);

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

    /**
     * @brief sortUnsortedFiles
     * Sort every little unsorted file
     * @param fileToWriteInName
     * The file that will be sorted
     * @param fileToReadInName
     * The file that is unsorted
     */
    void sortUnsortedFiles(string& fileToWriteInName, string& fileToReadInName);

    /**
     * @brief generateUnsortedRainbowTablePerCharAt
     * Divide a file that contains lines with same password length
     * into more little files
     * @param charInHashPosition
     * The position of the char in the hash that will make the file contain only these lines
     * @param charOfHash
     * The hash belonging which the file will contain only the lines in which the hash begin with this hash
     * @param fileToWriteInName
     * The file that contains all the lines
     * @param fileToReadInName
     * The file that is unsorted
     */
    void generateUnsortedRainbowTablePerCharAt(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName);

    /**
     * @brief deleteReadLinesInFile
     * Delete the lines already read in the file to sort/divide
     * @param charInHashPosition
     * The position of the char in the hash that will make the file contain only these lines
     * @param charOfHash
     * The hash belonging which the file will contain only the lines in which the hash begin with this hash
     * @param fileToWriteInName
     * The file that contains all the lines
     * @param fileToReadInName
     * The file that is unsorted
     */
    void deleteReadLinesInFile(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName);

    /**
     * @brief addSortedFilesToCorrespondingRainbowTable
     * Adds all the little sorted files in the corresponding rainbow table that contains
     * all the lines with a same password length
     * @param passwordLength
     * The password length in all the little files and the output file
     */
    void addSortedFilesToCorrespondingRainbowTable(unsigned int passwordLength);

    /**
     * @brief createEachCharHashTextFile
     * Divide the rainbow table that contains lines of only one password size
     * into lots of little unsorted files
     * @param passwordLength
     * The length of the passwords contained in the big file
     */
    void createEachCharHashTextFile(unsigned int passwordLength);

    /**
     * @brief sortEveryCharUnsortedTextFile
     * Sorts every little unsorted text file
     * first on the numbers and then on the charcaters
     * @param passwordLength
     * The length of the passwords contained in all the little text files
     */
    void sortEveryCharUnsortedTextFile(unsigned int passwordLength);

    /**
     * @brief generate3SortedRainbowTables
     * Generates 3 sorted files.
     * Each file has passwords with same lengths
     * @param passwordLength
     * The password lengths
     */
    void generate3SortedRainbowTables(unsigned int passwordLength);

    /**
     * @brief generateRainbowTable
     * Generates the sorted final rainbow table
     */
    void generateRainbowTable();

    /**
     * @brief putAllInFinalTable
     * Merges the 3 rainbow table (those that were generated belonging the password length)
     * into a big one
     * @param passwordLength
     * The password length of each of the 3 rainbow tables
     */
    void putAllInFinalTable(unsigned int passwordLength);
}
#endif // TABLEGENERATION_H
