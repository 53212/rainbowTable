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

vector<string> rainbow::getHashesChain(string& hashToUncypher, int length)
{
    vector<string> hashes;
    string hash;
    hashes.push_back(hashToUncypher);
    //cout << "hashToUncypher : " << hashToUncypher << " length  : " << length << endl;
    for (int i = 9998; i >= 0; i--)
    {
        for( int j = i; j < 10000; j++)
        {
            hash = sha256(reduce(hash, j, length));
            if(j == 9999)
            {
                hashes.push_back(hash);
                hash = hashToUncypher;
            }
        }
    }
    cout << "size of hashes : "<< hashes.size() << endl;
    return hashes;
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
            cout << "hashToCompare : " << hashToCompare << " ; hash : " << hash  << " ; hash == hashToCompare : " << (hash == hashToCompare) <<endl;
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
            cout << "cacacac1" << " i : " << i << endl;
            passwords.push_back(findPsw(i, hashToUncypher));
        }));
        cout << "cacacac2" << " i : " << i << endl;
    }
    for_each(threadVector.begin(), threadVector.end(), [](thread &t)
    {
        t.join();
    });
    cout << passwords.at(0) << " " << passwords.at(1) << " " << passwords.at(2) << endl;
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
    cout << "AZERTYU" << endl;
    // Mettre un thread pour chaque longueur de mot de passe, mais si un thread trouve le mot de passe, il doit break les 2 autres threads
    vector<string> possibleHashes = rainbow::getHashesChain(hashToUncypher,passwordLength);
    unsigned count = 9999;
    cout << "QSDFGH" << endl;
    for(string possibleHash : possibleHashes)
    {
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
    vector<vector<string>> reducedHashToUncypher;
    unsigned int cpt1 = 0;
    unsigned int cpt2 = 0;
    unsigned int cpt3 = 0;
    cpt3 = hashesToUncypher.size() % 10;
    //for (string hashToUncypher : hashesToUncypher)
    cpt1 = hashesToUncypher.size() / 10;
    cout << "hashesToUncypher : " << hashesToUncypher.size() << endl;
    cout << "1111" << endl;
    for (unsigned int i = 0; i < cpt1; i++)
    {
        cout << "2222" << endl;
        vector<string> tenHashes;
        for (unsigned int j = 0; j < 10; j++)
        {
            cout << "3333" << endl;
            tenHashes.push_back(hashesToUncypher.at(cpt2 + j));
        }
        cpt2 += 10;
        cout << "4444" << endl;
        reducedHashToUncypher.push_back(tenHashes);
        cout << "5555" << endl;
    }
    vector<string> hashRest;
    for (unsigned int k = 0; k < cpt3; k++)
    {
        cout << "6666" << endl;
        hashRest.push_back(hashesToUncypher.at(cpt2 + k));
    }
    if (!hashRest.empty())
    {
        cout << "7777" << endl;
        reducedHashToUncypher.push_back(hashRest);
    }
    return reducedHashToUncypher;
}

void findAllPasswordsForThreads(vector<string> hashesToUncypher, promise<vector<string>> &&hashesUncyphered)
{
    vector<string> bufferUncyphered;
    for(string hashToUncypher : hashesToUncypher)
    {
        cout << "hashToUncypher : " << hashToUncypher << endl;
        bufferUncyphered.push_back(rainbow::findPswS(hashToUncypher));
    }
    hashesUncyphered.set_value(bufferUncyphered);
    for (string s: bufferUncyphered)
    {
        cout << "s1 : " << s << endl;
    }
}

void rainbow::findAllPsw()
{
    vector<string> hashesToUncypher = rainbow::readHashToUncypher();
    ofstream stream("ResultTable.txt", ios_base::app);

    // 10 threads pour trouver 10 mots de passe à la fois, et dès qu'un threads est libre, il doit prendre le suivant
    // Dès qu'un thread a fini, il diminue le compteur et
    cout << "start 1" << endl;
    vector<vector<string>> parsedHashes = putHashesInDifferentVectors(hashesToUncypher);
    cout << "start 2" << endl;
    vector<vector<string>> uncypheredVector;
    vector<thread> vectors;
    for (vector<string> vectorHash : parsedHashes)
    {
        promise<vector<string>> uncyphered;
        auto f = uncyphered.get_future();
        vectors.push_back(thread(&findAllPasswordsForThreads, vectorHash, std::move(uncyphered)));
        //thread t(&findAllPasswordsForThreads, vectorHash, std::move(uncyphered));
        vector<string> uncypheredV = f.get();
        uncypheredVector.push_back(uncypheredV);
        //vectors.push_back(t);
        cout << "aaaa" << endl;
        //vector<string> uncypheredV;
        /*promise<vector<string>> uncyphered;
        std::function<void(promise<vector<string>>)> fun = [uncypheredVector, &vectorHash](promise<vector<string>> uncyphered2)
        {
            /*cout << "bbbb" << endl;
            promise<vector<string>> uncyphered;
            cout << "cccc" << endl;
            auto f = uncyphered.get_future();
            cout << "dddd" << endl;*/
            //thread t(&findAllPasswordsForThreads, std::ref(vectorHash), &uncyphered2);
            /*cout << "eeee" << endl;
            uncypheredV2 = f.get();
            cout << endl << "ffff" << endl;
            for (string s : uncypheredV2)
            {
                cout << "s2 : " << s << endl;
            }*/
            /*cout << "uncypheredVector.size : " << uncypheredVector.size() << endl;
            //uncypheredVector.push_back(uncypheredV);
            //return uncypheredV;
        };*/
        cout << "gggg111" << endl;
        //promise<vector<string>> uncyphered;
        /*auto f = uncyphered.get_future();
        //vectors.push_back(thread (&fun, std::move(uncyphered)));
        vector<string> uncypheredV = f.get();
        uncypheredVector.push_back(uncypheredV);
        //vectors.push_back(t);
        //vectors.push_back(thread(fun));
        cout << "gggg222" << endl;*/
    }
    /*for (auto && t : vectors)
    {
        cout << "hhhh" << endl;
        t.join();
        cout << "iiii" << endl;
    }*/
    for_each(vectors.begin(), vectors.end(), [](thread &t)
    {
        cout << "hhhh" << endl;
        t.join();
        cout << "iiii" << endl;
    });
    for (unsigned int i = 0; i < uncypheredVector.size(); i++)
    {
        cout << "jjjj size uncypheredVector : " << uncypheredVector.size() << endl;
        vector<string> resultsParsed = uncypheredVector.at(i);
        cout << "aaaa size resultPrased : " << resultsParsed.size() << endl;
        for (string result : resultsParsed)
        {
            cout << "kkkk result : " << result << endl;
            stream << result << endl;
            cout << "llll" << endl;
        }
        cout << "mmmm" << endl;
    }
    cout << "nnnn" << endl;
    stream.close();
    cout << "oooo" << endl;
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
