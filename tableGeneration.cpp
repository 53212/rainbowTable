#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "sha256.h"
#include "tableGeneration.h"

using namespace std;
//using namespace rainbow;

void generateOneLine(string password)
{
    vector<string> line;
    line.push_back(password);
    line.push_back(", ");
    string hash = sha256(password);
    line.push_back(hash);
    string hashReduction = reduce2(hash, 2, line.at(0).length());
    line.push_back(", ");
    line.push_back(hashReduction);
    for (int i = 0;i < 14; i++)
    {
        line.push_back(", ");
        if (i % 2 != 0)
        {
            hashReduction = reduce2(hash, 2, line.at(0).length());
            line.push_back(hashReduction);
        }
        else
        {
            hash = sha256(hash);
            line.push_back(hash);
        }
    }
    //return line;
    writeInFile(line);
}

ofstream generateFile()
{
    std::ofstream rainbowTable ("RainbowTable.txt");

    rainbowTable.close();

    char* path = realpath("RainbowTable", NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", "RainbowTable");
    } else{
        //printf("path[%s]\n", path);
        free(path);
    }
    return rainbowTable;
}

void writeInFile(/*ofstream rainbowTable,*/ vector<string> textToPutIn)
{
    ofstream rainbowTable = generateFile();
    rainbowTable.open("RainbowTable.txt");
    /*rainbowTable.seekp(sizeof(rainbowTable));
    for (unsigned i = 0; i < 10; i++)
    {
        rainbowTable << "valeur de i : " << i << endl; //fonction toString convertie int en string
    }*/
    rainbowTable << textToPutIn.at(0);
    for (unsigned i = 1; i < textToPutIn.size(); i++)
    {
        if (i % 2 == 0 && textToPutIn.at(i) != ", ")
        {
            rainbowTable << endl;
        }
        rainbowTable << textToPutIn.at(i);
    }
    //rainbowTable << endl;
    rainbowTable.close();
}
