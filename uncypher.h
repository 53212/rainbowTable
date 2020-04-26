/**
 * This should find a maximum password thanks to a text file that contains hashes to uncypher
 */

#ifndef UNCYPHER_H
#define UNCYPHER_H
#include "iostream"
#include "vector"

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
     *
     * // va essayer de retrouver la chaine qui contient le hash a dechiffrer
//il va recuperer un hash possible d'une chaine via getHashesChain()
// et va le comparer un a un au dernier hash de chaque chaine de la RT
// vu que la RT est trié par longueur de MDP et ensuite sur ordre alphabetique sur le hash,
// dés qu'on depasse la longueur demander on break car elle ne se trouve alors pas dans la RT
// et des que pour une certaine longueur on depasse les hash au niveau alphabetique on break egalement
     */
    vector<string> findCorrectChain(string hashToCompare, int length);

    /**
     * @brief findPsw
     * For each password length, this funciton will get the last hash
     * of every rainbow table text file line that contains the hash to decypher (CORRECT?).
     * Then, findCorrectChain() will help to compare every rainbow table has to those ones
     * @param hashToUncypher
     * the hash to uncypher
     * @return "not found"
     * if the password hasn't been found in the rainbow table text file
     *
     * // va pour chaque longueur de mdp possible recupere tout les dernier hash
//de toutes les chaines contenant le hash a dechfrer via getHashesChain()
// il va ensuite verrifier chaqun de ces hash dans la RT via findCorrectChain()
     */
    string findPsw(string hashToUncypher);

    /**
     * @brief findAllPsw
     * This will look for the password from every hash to uncypher
     *
     * // va effectuer la recherche du mdp de touts les hashs a dechiffre
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
     *
     * //essaie de trouver tout les hash qui pourrait etre dans une chaine
//il va retourner pour un hash a dechiffrer tout les dernier hash des chaines
//qui pourrais contenir le hash a dechiffrer et dont le MDP est de longueur "length"
//et dont le hash hash a dechiffre en fait parti(de la chaine)
     */
    vector<string> getHashesChain(string hashToUncypher, int length);

    /**
     * @brief generateResultTableFile
     * Generates a text file that will contain the passwords found
     * @return the file
     */
    ofstream generateResultTableFile();

    /**
     * @brief puttingResultInFile
     * Puts the result int the result text file
     * @param password
     */
    void puttingResultsInFile(string password);

    /**
     * @brief getCorrectPswOfChain
     * This function will get the password of the asked hash
     * @param firstPsw
     * The first password of the rainbow table text file line
     * @param collumn
     * the number of reductions done
     * @return
     *
     * // va recuperer le mdp du hash demander dans la chaine recu
     */
    string getCorrectPswOfChain(string firstPsw, int collumn);
}
#endif // UNCYPHER_H
