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

void rainbow::generateOneLine(string password)
{
    vector<string> line;
    line.push_back(password);
    cout << password << ", ";
    //line.push_back(", ");
    string hash = sha256(password);
    //line.push_back(hash);
    cout << hash << endl; // << ", ";
    string hashReduction; // = reduce2(hash, 2, line.at(0).length());
    line.push_back(", ");
    //line.push_back(hashReduction);
    //cout << hashReduction << ", ";
    for (int i = 0; i < 14; i++)
    {
        //line.push_back(", ");
        cout << ", ";
        hashReduction = reduce2(hash, 2, line.at(0).length());
        if (i % 2 == 0)
        {
            //line.push_back(hashReduction);
            cout << hashReduction;
        }
        else
        {
            hash = sha256(hashReduction);
            if (i == 13)
            {
                line.push_back(hash);
            }
            //line.push_back(hash);
            cout << hash << endl;
        }
    }
    //return line;
    line.push_back("\n");
    cout << endl;
    writeInFile(line);
}

void rainbow::generateAllLines()
{
    int i = 0;
    while (i != 4)
    {
        int passwordRandomLength = randomBetweenMinAndMax(6, 9);
        string input = generate_passwd(passwordRandomLength);
        generateOneLine(input);
        //sort
        i++;
    }
}

ofstream generateFile()
{
    std::ofstream rainbowTable ("RainbowTable.txt");

    rainbowTable.close();

    char* path = realpath("RainbowTable", NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", "RainbowTable");
    }
    else
    {
        //printf("path[%s]\n", path);
        free(path);
    }
    return rainbowTable;
}

void rainbow::writeInFile(/*ofstream rainbowTable,*/ vector<string> textToPutIn)
{
    ofstream rainbowTable = generateFile();
    rainbowTable.open("RainbowTable.txt");
    rainbowTable.seekp(sizeof(rainbowTable) + 1);
    for (unsigned i = 0; i < 10; i++)
    {
        if (i % 2 != 0 && textToPutIn.at(i) != ", ")
        {
            rainbowTable << endl;
        }
        rainbowTable << textToPutIn.at(i);
        //rainbowTable << "valeur de i : " << i << endl; //fonction toString convertie int en string
    }
    //rainbowTable << textToPutIn.at(0);
    /*
    for (unsigned i = 1; i < textToPutIn.size(); i++)
    {
        if (i % 2 != 0 && textToPutIn.at(i) != ", ")
        {
            rainbowTable << endl;
        }
        rainbowTable << textToPutIn.at(i);
    }*/
    //rainbowTable << endl;
    rainbowTable.close();
}
