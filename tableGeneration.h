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

    /**
     * @brief fileSize
     * the size one of the 3 rainbow table files must not exceed
     */
    inline long fileSize = 3999995896;

    class tableGeneration
    {

        private :
            /**
             * @brief line_
             */
            vector<string> line_;
    };

    //int randomBetweenMinAndMax(int a, int b);

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
     * @brief hashesToUncypher
     * generates 100 hashes to uncypher to test our program
     */
    //void hashesToUncypher();

    /**
     * @brief goToLine
     * Goes to a specific line belonging a file
     * @param file
     * The file in which a line has to be found
     * @param num
     * The number of the line to find in the file
     * @return a vector of 3 strings (the found line) :
     * the first password, a space and the 35th hash
     */
    //vector<string> goToLine(fstream& file, unsigned int num);

    /**
     * @brief goToLine
     * Goes to a specific line belonging a file
     * @param file
     * The file in which a line has to be found
     * @param num
     * The number of the line to find in the file
     * @return a vector of 3 strings (the found line) :
     * the first password, a space and the 35th hash
     */
    //std::fstream& GotoLine(std::fstream& file, unsigned int num);

    /**
     * @brief putLineAtRightPlace
     * Puts a line at the right place in the rainbow table text file
     * to make the text file ordered alphabetically
     * @param line the line to insert
     */
    //void putLineAtRightPlace(vector<string> line);

    /**
     * @brief generateSortedRainbowTable
     * Generates an alphabetically sorted rainbow table text file
     */
    //void generateSortedRainbowTable();

    /**
     * @brief generateSortedRainbowTables
     * Generates a sorted  rainbow table text fil
     * with another not sorted rainbow table text file
     * @param passwordLength
     * The length of the passwords ocntained in the not sorted rainbow table text file
     */
    void generateSortedRainbowTables(unsigned int passwordLength);

    /**
     * @brief thread6
     * generates a rainbow table text file
     * that the lines are generates with 6 letters passwords
     */
    void thread6(/*unsigned int passwordLength*/);

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
     * @brief lastLineOfFile
     * Looks for the last line of a rainbow table text file
     * @return a vector of 3 strings (the last line of the rainbow table text file) :
     * the first password, a space and the 35th hash
     */
    vector<string> lastLineOfFile();

    void generateFinalRainbowTable();
}
#endif // TABLEGENERATION_H
