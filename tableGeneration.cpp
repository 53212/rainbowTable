#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "passwd-utils.hpp"
#include "sha256.h"
#include "tableGeneration.h"

using namespace std;
using namespace rainbow;

// b is excluded
int rainbow::randomBetweenMinAndMax(int a, int b)
{
    return rand() % (b - a) + a;
}

vector<string> rainbow::generateOneLine(string password)
{
    vector<string> line;
    line.push_back(password);
    string hash = sha256(password);
    string hashReduction;
    line.push_back(" ");
    for (int i = 0; i < 35; i++)
    {
        hashReduction = reduce(hash, i, line.at(0).length());
        hash = sha256(hashReduction);
        if (i == 34)
        {
            line.push_back(hash);
        }

    }
    line.push_back("\n");
    return line;
}

ofstream generateRainbowTableFile()
{
    ofstream rainbowTable ("RainbowTable.txt");
    rainbowTable.close();

    char* path = realpath("RainbowTable", NULL);
    if(path == NULL)
    {
        printf("cannot find file with name[%s]\n", "RainbowTable");
    }
    else
    {
        free(path);
    }
    return rainbowTable;
}

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}

void rainbow::generateAllLines()
{
    int passwordRandomLength;
    ofstream stream = generateRainbowTableFile();
    stream.open("RainbowTable.txt", ios_base::app);
    while (filesize("RainbowTable") < 120)
    {
        passwordRandomLength = randomBetweenMinAndMax(minLength, maxLength);
        string input = generate_passwd(passwordRandomLength);
        vector<string> textToPutIn = generateOneLine(input);

        for (unsigned i = 0; i < textToPutIn.size(); i++)
        {
            stream << textToPutIn.at(i);
        }
    }
    stream.close();
}

ofstream generateResultTableFile()
{
    ofstream rainbowTable ("ResultTable.txt");
    rainbowTable.close();

    char* path = realpath("ResultTable", NULL);
    if(path == NULL)
    {
        printf("cannot find file with name[%s]\n", "ResultTable");
    }
    else
    {
        free(path);
    }
    return rainbowTable;
}

void puttingResultsInFile(string password)
{
    ofstream stream = generateRainbowTableFile();
    stream.open("ResultTable.txt", ios_base::app);
    stream << password << endl;
    stream.close;
}
