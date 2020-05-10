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
        cout << "ERREUR: Impossible d'ouvrir hashToUncypher.txt" << endl;
    }
    return hashes;
}

vector<string> rainbow::getHashesChain(string& hashToUncypher, int length)
{
    {
        vector<string> hashes;
        string hash;
        hashes.push_back(hashToUncypher);
        for (int i = 33; i >= 0; i--)
        {
            for( int j=i; j<35; j++)
            {
                hash = sha256(reduce(hash, j, length));
                if(j == 34)
                {
                    hashes.push_back(hash);
                    hash = hashToUncypher;
                }
            }
        }
        return hashes;
    }
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
        cout << "ERREUR: Impossible d'ouvrir hashToUncypher.txt" << endl;
    }
    return hashes;
}

string rainbow::findPsw(string& hashToUncypher)
{
    for(int length = 6; length < 9; length++)
    {
        vector<string> possibleHashes = rainbow::getHashesChain(hashToUncypher,length);
        unsigned count = 34;
        for(string possibleHash : possibleHashes)
        {
            vector<string> pswFound = rainbow::findCorrectChain(possibleHash,length);
            if(!pswFound.empty())
            {
                return rainbow::getCorrectPswOfChain(pswFound[0],count);
            }
            else
            {
                count--;
            }
        }
    }
    return "notFound";
}

void rainbow::findAllPsw()
{
    rainbow::generateResultTableFile();
    vector<string> hashesToUncypher = rainbow::readHashToUncypher();
    ofstream stream = rainbow::generateResultTableFile();
    stream.open("ResultTable.txt", ios_base::app);
    for(string hashToUncypher : hashesToUncypher)
    {
        stream << findPsw(hashToUncypher) << endl;
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

ofstream rainbow::generateResultTableFile()
{
    ofstream rainbowTable ("ResultTable.txt");
    rainbowTable.close();

    /*char* path = realpath("ResultTable", NULL);
    if(path == NULL)
    {
        printf("cannot find file with name[%s]\n", "ResultTable");
    }
    else
    {
        free(path);
    }*/
    return rainbowTable;
}
