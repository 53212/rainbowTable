#include "uncypher.h"
#include <iostream>
#include <fstream>
#include "sha256.h"

vector<string> rainbow::readHashToUncypher()
{
    vector<string> hashes;
    ifstream file("HashesToUncypher.txt");
    if(file)
    {
        //cout << "file.is_open() : " << file.is_open() << endl;
        string line;
        while(getline(file, line))
        {
            hashes.push_back(line);
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir HashesToUncypher.txt" << endl;
    }
    return hashes;
}

string rainbow::getHashesChain(string& hashToUncypher, int length, int numberOfReduceDone)
{
    string hash = hashToUncypher;
    for(int j = numberOfReduceDone; j < nbPassWordsInEveryLineForUncyphering; j++)
    {
        hash = sha256(reduce(hash, j, length));
    }
    return hash;
}

vector<string> rainbow::findCorrectChain(string& hashToCompare,int length)
{
    vector<string> hashes;
    string hash;
    string psw;
    ifstream file("RainbowTable.txt");
    if(file)
    {
        while(!file.eof())
        {
            file >> psw;
            file >> hash;
            if(psw.size()==length)
            {
                if(hash == hashToCompare)
                {
                    hashes.push_back(psw);
                    hashes.push_back(hash);
                    break;
                }
                if(hash > hashToCompare)
                {
                    break;
                }
            }
            if(psw.size() > length)
            {
                break;
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir RainbowTable.txt" << endl;
    }
    return hashes;
}

string rainbow::findPswS(string& hashToUncypher)
{
    vector<thread> threadVector;
    vector<string> passwords;
    for (unsigned int i = 6; i < 9; i++)
    {
        threadVector.push_back(thread([&passwords, i, &hashToUncypher]()
        {
            passwords.push_back(findPsw(i, hashToUncypher));
        }));
    }
    for_each(threadVector.begin(), threadVector.end(), [](thread &t)
    {
        t.join();
    });
    for(string s : passwords)
    {
        if (s != "notFound")
        {
            return s;
        }
    }
    return "notFound";
}

string rainbow::findPsw(unsigned int passwordLength, string& hashToUncypher)
{
    // Mettre un thread pour chaque longueur de mot de passe, mais si un thread trouve le mot de passe, il doit break les 2 autres threads
    string possibleHash = hashToUncypher;
    vector<string> pswFound = rainbow::findCorrectChain(possibleHash,passwordLength);
    unsigned count = nbPassWordsInEveryLineForUncyphering - 1;
    if(!pswFound.empty())
    {
        return rainbow::getCorrectPswOfChain(pswFound[0],count);
    }
    count--;
    for (int i = nbPassWordsInEveryLineForUncyphering - 2; i >= 0; i--)
    {
        string possibleHash = getHashesChain(hashToUncypher,passwordLength , i);
        vector<string> pswFound = findCorrectChain(possibleHash,passwordLength);
        if(!pswFound.empty())
        {
            return rainbow::getCorrectPswOfChain(pswFound[0],count);
        }
        else
        {
            count--;
        }
    }
    return "notFound";
}

vector<vector<string>> rainbow::putHashesInDifferentVectors(vector<string> &hashesToUncypher)
{
    vector<vector<string>> reducedHashToUncypher;
    unsigned int cpt1 = 0;
    unsigned int cpt2 = 0;
    unsigned int cpt3 = 0;
    cpt3 = hashesToUncypher.size() % nbPasswordsPerThread;
    cpt1 = hashesToUncypher.size() / nbPasswordsPerThread;
    for (unsigned int i = 0; i < cpt1; i++)
    {
        vector<string> tenHashes;
        for (unsigned int j = 0; j < nbPasswordsPerThread; j++)
        {
            tenHashes.push_back(hashesToUncypher.at(cpt2 + j));
        }
        cpt2 += nbPasswordsPerThread;
        reducedHashToUncypher.push_back(tenHashes);
    }
    vector<string> hashRest;
    for (unsigned int k = 0; k < cpt3; k++)
    {
        hashRest.push_back(hashesToUncypher.at(cpt2 + k));
    }
    if (!hashRest.empty())
    {
        reducedHashToUncypher.push_back(hashRest);
    }
    return reducedHashToUncypher;
}

vector<string> findAllPasswordsForThreads(vector<string> hashesToUncypher)
{
    vector<string> uncypheredHashes;
    for(string hashToUncypher : hashesToUncypher)
    {
        cout << endl << "hashToUncypher : " << hashToUncypher << endl;
        uncypheredHashes.push_back(rainbow::findPswS(hashToUncypher));
    }
    return uncypheredHashes;
}

void rainbow::findAllPasswords()
{
    vector<string> hashesToUncypher = rainbow::readHashToUncypher();
    ofstream stream("ResultTable.txt", ios_base::beg);
    vector<vector<string>> parsedHashes = putHashesInDifferentVectors(hashesToUncypher);
    vector<vector<string>> uncypheredHashesVector;
    vector<thread> threadsVector;
    const int allPasswordsSize = parsedHashes.size();
    future<vector<string>> allPasswords[allPasswordsSize];
    int threadCount = 0;
    for (vector<string> vectorHash : parsedHashes)
    {
        allPasswords[threadCount] = async(&findAllPasswordsForThreads, vectorHash);
        threadCount++;
    }
    vector<vector<string>> resultPassword;
    int finishedThread = 0;
    while(finishedThread < allPasswordsSize) // = .join(), but .get locks the other possible threads
    {
        for (unsigned int i = 0; i < allPasswordsSize; i++)
        {
            resultPassword.push_back(allPasswords[i].get());
            finishedThread++;
        }
    }
    for (vector<string> passwords : resultPassword)
    {
        for (string password : passwords)
        {
            stream << password << endl;
        }
    }
    stream.close();
}

string rainbow::getCorrectPswOfChain(string& firstPsw, unsigned int collumn)
{
    string psw = firstPsw;
    for (unsigned int i = 0; i < collumn; i++)
    {
        string hashReduction = reduce(sha256(psw), i, firstPsw.length());
        psw = hashReduction;
    }
    return psw;
}
