/**
 * This should find a maximum password thanks to a text file that contains hashes to uncypher
 */

#ifndef UNCYPHER_H
#define UNCYPHER_H
#include "iostream"
#include "vector"
#include <thread>
#include <mutex>
#include <future>

using namespace std;

namespace rainbow
{
    /**
     * @brief readHashToUncypher
     * This will load every hash to uncypher in memory
     * @return a vector of strings.
     * Every string is a hash to uncypher
     *
     * //va juste recuperer tout les hash a dechiffrer et le mettre en memeoir
     */
    vector<string> readHashToUncypher();

    const int nbPasswordsPerThread = 10;

    //std::mutex mutex;

    /**
     * @brief findCorrectChain
     * Tries to find the line of the rainbow table text file that contains the hash to uncypher.
     * getHashesChain() will provide a possible hash and
     * will compare it to every line hash of the rainbow table text file
     * The rainbow table text file is firstly ordered on the password length
     * and secondly alphabetically on the hashes, so that the program will break as soon as the
     * password length is exceeded. That means the program doesn't need to go through
     * the whole rainbow table text file.
     * The same is done on the hash length.
     * @param hashToCompare
     * the hash to uncypher
     * @param length
     * the password length
     * @return the right rainbow table text file line that should contain the password to find
     */
    vector<string> findCorrectChain(string& hashToCompare, int length);

    /**
     * @brief findPsw
     * For each password length, this funciton will get the last hash
     * of every rainbow table text file line that contains the hash to decypher (CORRECT?).
     * Then, findCorrectChain() will help to compare every rainbow table has to those ones
     * @param hashToUncypher
     * the hash to uncypher
     * @return "not found"
     * if the password hasn't been found in the rainbow table text file
     */
    string findPsw(unsigned int passwordLength, string& hashToUncypher);

    /**
     * @brief putHashesInDifferentVectors
     * This will divide the hashes to uncypher in differents vectors.
     * Every vector will contain 10 hashes to uncypher
     * @param HashesToUncypher
     * All the hashes to uncypher. They are caught in the text file "HashesToUncypher.txt"
     * @return
     */
    vector<vector<string>> putHashesInDifferentVectors(vector<string> &hashesToUncypher);

    /**
     * @brief findAllPsw
     * This will look for the password from every hash to uncypher
     */
    void findAllPsw();

    /**
     * @brief getHashesChain
     * Tries to find every hash that could be contained in a rainbow table text file line.
     * @param hashToUncypher
     * the hash to uncypher
     * @param length
     * the length of the password contained in the rainbow table text file line
     * @return every last rainbow table text file line hash that is contained in a line
     * that could contain the hash to uncypher and the password length that is "lenght" (received as parameter)
     * for a single hash to uncypher. This hash should of course be contained in the concerned line
     */
    string getHashesChain(string& hashToUncypher, int length,int numberOfReduceDone);

    /**
     * @brief puttingResultInFile
     * Puts the result int the result text file
     * @param password
     */
    void puttingResultsInFile(string& password);

    /**
     * @brief getCorrectPswOfChain
     * This function will get the password of the asked hash
     * @param firstPsw
     * The first password of the rainbow table text file line
     * @param collumn
     * the number of reductions done
     * @return the corretc password found
     */
    string getCorrectPswOfChain(string& firstPsw, unsigned int collumn);

    string findPswS(string& hashToUncypher);
}
#endif // UNCYPHER_H
