#include "uncypher.h"
#include <iostream>
#include <fstream>
#include "sha256.h"

vector<string> rainbow::readHashToUncypher()
{
    vector<string> hashes;
    ifstream file("HashToUncypher.txt");
    if(file)
    {
        string line;
        while(getline(file, line))
        {
            hashes.push_back(line);
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir HashToUncypher.txt" << endl;
    }
    return hashes;
}

string rainbow::getHashesChain(string& hashToUncypher, int length, int numberOfReduceDone)
{
    string hash;
        for( int j = numberOfReduceDone; j < 10000; j++)
        {
            hash = sha256(reduce(hash, j, length));
        }
    //cout << "size of hashes : "<< hashes.size() << endl;
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
            file>> psw;
            file>> hash;
            //cout << "hashToCompare : " << hashToCompare << " ; hash : " << hash  << " ; hash == hashToCompare : " << (hash == hashToCompare)<< " ; password length : " << length  << endl;
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
            if(psw.size()>length)
                break;
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
    //cout << "hashToUncypher : " << hashToUncypher << endl;
    // Mettre un thread pour chaque longueur de mot de passe, mais si un thread trouve le mot de passe, il doit break les 2 autres threads
    string possibleHash = hashToUncypher;
    vector<string> pswFound = rainbow::findCorrectChain(possibleHash,passwordLength);
    unsigned count = 9999;
    if(!pswFound.empty())
    {
        return rainbow::getCorrectPswOfChain(pswFound[0],count);
    }
    count --;
    for (int i = 9998; i >= 0; i--)
    {
        string possibleHash = rainbow::getHashesChain(hashToUncypher,passwordLength , i);
        vector<string> pswFound = rainbow::findCorrectChain(possibleHash,passwordLength);
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

/**
 * @brief putHashesInDifferentVectors
 * This will divide the hashes to uncypher in differents vectors.
 * Every vector will contain 10 hashes to uncypher
 * @param HashesToUncypher
 * All the hashes to uncypher. They are caught in the text file "HashesToUncypher.txt"
 * @return
 */
vector<vector<string>> putHashesInDifferentVectors(vector<string> &hashesToUncypher)
{
    int nbThreadsLookingForNbPasswords = 10;
    vector<vector<string>> reducedHashToUncypher;
    unsigned int cpt1 = 0;
    unsigned int cpt2 = 0;
    unsigned int cpt3 = 0;
    cpt3 = hashesToUncypher.size() % nbThreadsLookingForNbPasswords;
    //for (string hashToUncypher : hashesToUncypher)
    cpt1 = hashesToUncypher.size() / nbThreadsLookingForNbPasswords;
    for (unsigned int i = 0; i < cpt1; i++)
    {
        vector<string> tenHashes;
        for (unsigned int j = 0; j < nbThreadsLookingForNbPasswords; j++)
        {
            tenHashes.push_back(hashesToUncypher.at(cpt2 + j));
        }
        cpt2 += nbThreadsLookingForNbPasswords;
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

void findAllPasswordsForThreads(vector<string> hashesToUncypher, promise<vector<string>> &&hashesUncyphered)
{
    vector<string> bufferUncyphered;
    for(string hashToUncypher : hashesToUncypher)
    {
        bufferUncyphered.push_back(rainbow::findPswS(hashToUncypher));
    }
    hashesUncyphered.set_value(bufferUncyphered);
}

void rainbow::findAllPsw()
{
    vector<string> hashesToUncypher = rainbow::readHashToUncypher();
    ofstream stream("ResultTable.txt", ios_base::beg);

    // 10 threads pour trouver 10 mots de passe à la fois, et dès qu'un threads est libre, il doit prendre le suivant
    // Dès qu'un thread a fini, il diminue le compteur et
    vector<vector<string>> parsedHashes = putHashesInDifferentVectors(hashesToUncypher);
    vector<vector<string>> uncypheredHashesVector;
    vector<thread> threadsVector;
    for (vector<string> vectorHash : parsedHashes)
    {
        promise<vector<string>> uncyphered;
        auto f = uncyphered.get_future();
        threadsVector.push_back(thread(&findAllPasswordsForThreads, vectorHash, std::move(uncyphered)));
        //thread t(&findAllPasswordsForThreads, vectorHash, std::move(uncyphered));
        vector<string> uncypheredHash = f.get();
        uncypheredHashesVector.push_back(uncypheredHash);
        //vectors.push_back(t);
        //vector<string> uncypheredV;
        /*promise<vector<string>> uncyphered;
        std::function<void(promise<vector<string>>)> fun = [uncypheredVector, &vectorHash](promise<vector<string>> uncyphered2)
        {
            promise<vector<string>> uncyphered;
            auto f = uncyphered.get_future();
            //thread t(&findAllPasswordsForThreads, std::ref(vectorHash), &uncyphered2);
            uncypheredV2 = f.get();
            uncypheredVector.push_back(uncypheredV);
            return uncypheredV;
        };*/
        //promise<vector<string>> uncyphered;
        /*auto f = uncyphered.get_future();
        //vectors.push_back(thread (&fun, std::move(uncyphered)));
        vector<string> uncypheredV = f.get();
        uncypheredVector.push_back(uncypheredV);
        //vectors.push_back(t);
        //vectors.push_back(thread(fun));*/
    }
    /*for (auto && t : vectors)
    {
        cout << "hhhh" << endl;
        t.join();
        cout << "iiii" << endl;
    }*/
    for_each(threadsVector.begin(), threadsVector.end(), [](thread &t)
    {
        t.join();
    });
    for (unsigned int i = 0; i < uncypheredHashesVector.size(); i++)
    {
        vector<string> resultsParsed = uncypheredHashesVector.at(i);
        for (string result : resultsParsed)
        {
            stream << result << endl;
        }
    }
    stream.close();
}

string rainbow::getCorrectPswOfChain(string& firstPsw, int collumn)
{
    string psw = firstPsw;
    for (int i = 0; i < collumn; i++)
    {
        string hashReduction = reduce(sha256(psw), i, firstPsw.length());
        psw = hashReduction;
    }
    return psw;
}
