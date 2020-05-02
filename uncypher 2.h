#ifndef UNCYPHER_H
#define UNCYPHER_H
#include "iostream"
#include "vector"

using namespace std;

namespace rainbow
{
vector<string> readHashToUncypher();
vector<string> findCorrectChain(string hashToCompare);
string findPsw(string hashToUncypher);
void findAllPsw();
vector<string> getHashesChain(string hashToUncypher, int length);
ofstream generateResultTableFile();
void puttingResultInFile(string password);
string getCorrectPswOfChain(string firstPsw, int collumn);
}
#endif // UNCYPHER_H
