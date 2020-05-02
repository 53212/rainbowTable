#include <iostream>
#include <vector>
#include <string>
#include "passwd-utils.hpp"
#include "tableGeneration.h"
#include <fstream>
#include <thread>

using namespace std;
using namespace rainbow;

/**
 * @brief generateOfstreamTextFile
 * Generates a text file to be able to write in it
 * @param fileName
 * The name of the file to create
 * @return the created ofstream file
 */
ofstream generateOfstreamTextFile(string fileName)
{
    ofstream rainbowTable (fileName);
    rainbowTable.close();

    char* path = realpath(fileName.c_str(), NULL);
    if(path == NULL)
    {
        printf("cannot find file with name[%s]\n", fileName.c_str());
    }
    else
    {
        free(path);
    }
    return rainbowTable;
}

/**
 * @brief filesize
 * Checks the size of a file belonging its name
 * @param filename
 * the name of the file that it must check the size
 * @return the size of the file
 */
ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
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
    return line;
}

void rainbow::generate100Hashes()
{
    ofstream passwords;
    ofstream hashes;
    string filePswdName = "Mots de passe.txt";
    string fileHashName = "HashToUncypher.txt";
    passwords = generateOfstreamTextFile(filePswdName);
    hashes = generateOfstreamTextFile(fileHashName);
    //ifstream fichier(filePswdName.c_str(),ios::binary);
    //int size;
    passwords.open(filePswdName.c_str(), ios_base::app);
    hashes.open(fileHashName.c_str(), ios_base::app);
    bool first = true;
    int a = 0;
    //while (a < 100)
    {
        for (int i = 0; i < 33; i++)
        {
            string input = generate_passwd(6);
            vector<string> textToPutIn = generateOneLine(input);

            if (first)
            {
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
                first = false;
            }
            else
            {
                passwords << endl;
                hashes << endl;
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
            }
        }
        hashes << endl;
        passwords << endl;
        first = true;
        for (int i = 0; i < 33; i++)
        {
            string input = generate_passwd(7);
            vector<string> textToPutIn = generateOneLine(input);

            if (first)
            {
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
                first = false;
            }
            else
            {
                passwords << endl;
                hashes << endl;
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
            }
        }
        hashes << endl;
        passwords << endl;
        first = true;
        for (int i = 0; i < 34; i++)
        {
            string input = generate_passwd(8);
            vector<string> textToPutIn = generateOneLine(input);

            if (first)
            {
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
                first = false;
            }
            else
            {
                passwords << endl;
                hashes << endl;
                passwords << textToPutIn.at(0);
                hashes << textToPutIn.at(2);
            }
        }
        a++;
    }
    passwords.close();
    hashes.close();
}

// I'll use this when I'll implement a for loop with the differents threads.
void rainbow::generate3RainbowTableFiles()
{
    /*string tName;
    vector<string> threadsNames;
    vector<thread> threads;
    for (unsigned int i = 6; i < 9; i++)
    {
        tName = "t";
        tName += to_string(i);
        threadsNames.push_back(tName);
    }
    for (unsigned int i = 6; i < 9; i++)
    {
        tName = threadsNames.at(i);
        thread tName(thread6, i);
        threads.push_back(tName);
    }
    for (unsigned int i = 6; i < 9; i++)
    {
        threads.at(i).join();
    }*/

    /*ofstream rainbowTable;
    string fileName = "RainbowTable";
    string extension = ".txt";
    fileName += to_string(passwordLength);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    rainbowTable = generateTextFile(fileName);
    ifstream fichier(fileName.c_str(),ios::binary);
    //int size;
    rainbowTable.open(fileName.c_str(), ios_base::app);
    while (filesize(fileName.c_str()) < 3999995896)
    {
        string input = generate_passwd(passwordLength);
        vector<string> textToPutIn = generateOneLine(input);


        for (unsigned i = 0; i < textToPutIn.size(); i++)
        {
            fichier.seekg(0,ios_base::end);
            size= fichier.tellg();
            fichier.seekg(0,ios_base::beg);
            //cout << "size= " << size << endl;
            //putLineAtRightPlace(textToPutIn);
            rainbowTable << textToPutIn.at(i);
        }
    }
    rainbowTable.close();*/
}

void rainbow::thread6()
{
    ofstream rainbowTable;
    string fileName = "RainbowTable";
    string extension = ".txt";
    fileName += to_string(6/*passwordLength*/);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    rainbowTable = generateOfstreamTextFile(fileName);
    ifstream fichier(fileName.c_str(),ios::binary);
    //int size;
    rainbowTable.open(fileName.c_str(), ios_base::app);
    bool first = true;
    while (filesize(fileName.c_str()) < fileSize)
    {
        string input = generate_passwd(6);
        vector<string> textToPutIn = generateOneLine(input);

        if (first)
        {
            rainbowTable << textToPutIn.at(0) << textToPutIn.at(1) << textToPutIn.at(2);
            first = false;
        }
        else
        {
            rainbowTable << endl;
            for (unsigned i = 0; i < textToPutIn.size(); i++)
            {
                rainbowTable << textToPutIn.at(i);
            }
        }
    }
    rainbowTable.close();
}

void rainbow::thread7()
{
    ofstream rainbowTable;
    string fileName = "RainbowTable";
    string extension = ".txt";
    fileName += to_string(7);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    rainbowTable = generateOfstreamTextFile(fileName);
    ifstream fichier(fileName.c_str(),ios::binary);
    //int size;
    rainbowTable.open(fileName.c_str(), ios_base::app);
    bool first = true;
    while (filesize(fileName.c_str()) < fileSize)
    {
        string input = generate_passwd(7);
        vector<string> textToPutIn = generateOneLine(input);

        if (first)
        {
            rainbowTable << textToPutIn.at(0) << textToPutIn.at(1) << textToPutIn.at(2);
            first = false;
        }
        else
        {
            rainbowTable << endl;
            for (unsigned i = 0; i < textToPutIn.size(); i++)
            {
                rainbowTable << textToPutIn.at(i);
            }
        }
    }
    rainbowTable.close();
}

void rainbow::thread8()
{
    ofstream rainbowTable;
    string fileName = "RainbowTable";
    string extension = ".txt";
    fileName += to_string(8);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    rainbowTable = generateOfstreamTextFile(fileName);
    ifstream fichier(fileName.c_str(),ios::binary);
    //int size;
    rainbowTable.open(fileName.c_str(), ios_base::app);
    bool first = true;
    while (filesize(fileName.c_str()) < fileSize)
    {
        string input = generate_passwd(8);
        vector<string> textToPutIn = generateOneLine(input);

        if (first)
        {
            rainbowTable << textToPutIn.at(0) << textToPutIn.at(1) << textToPutIn.at(2);
            first = false;
        }
        else
        {
            rainbowTable << endl;
            for (unsigned i = 0; i < textToPutIn.size(); i++)
            {
                rainbowTable << textToPutIn.at(i);
            }
        }
    }
    rainbowTable.close();
}

/*void rainbow::generateSortedRainbowTables(unsigned int passwordLength)
{
    bool keepSorting=true;
    string s;
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    string fileUnsortedName = "RainbowTable";
    string fileSortedName = "RainbowTableSorted";
    string extension = ".txt";
    fileUnsortedName += to_string(passwordLength);
    fileSortedName += to_string(passwordLength);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileUnsortedName += extension.at(i);
    }
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileSortedName += extension.at(i);
    }
    ifstream file(fileUnsortedName.c_str());
    ofstream file2(fileSortedName.c_str());
    if(file)
    {
        while(keepSorting){
            if(!line.empty()){
                line.pop_back();
                line.pop_back();
            }
            file>>s;
            line.push_back(s);
            file>>s;
            line.push_back(s);
            if(!bufferMin.empty()){
                while(!file.eof() && bufferMin.at(1)>=line.at(1)){
                    line.pop_back();
                    line.pop_back();
                    file>>s;
                    line.push_back(s);
                    file>>s;
                    line.push_back(s);
                }
                if(file.eof()){
                    keepSorting=false;
                }
            }
            buffer.push_back(line.at(0));
            buffer.push_back(line.at(1));
            while(!file.eof()){
                line.pop_back();
                line.pop_back();
                file>>s;
                line.push_back(s);
                file>>s;
                line.push_back(s);
                if(bufferMin.empty()){
                    if(line.at(1) < buffer.at(1)){
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
                if(!bufferMin.empty()){
                    if(line.at(1) < buffer.at(1) && line.at(1) > bufferMin.at(1)){
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
            }
            if(!bufferMin.empty()){
                bufferMin.pop_back();
                bufferMin.pop_back();
            }
            bufferMin.push_back(buffer.at(0));
            bufferMin.push_back(buffer.at(1));
            if(keepSorting){
                file2<<buffer.at(0)<<" "<<buffer.at(1)<<endl;
            }
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}*/

void rainbow::reduceTable6(string oldFileName, vector<string> lastSortedLine)
{
    ofstream bufferRainbowTable("RainbowTableBis6.txt");
    ifstream file(oldFileName.c_str());
    vector<string> buffer;
    string password;
    string hash;
    string line;
    if(file)
    {
        while (!file.eof())
        {
            file >> password;
            file >> hash;
            if (hash > lastSortedLine.at(1) && !file.eof())
            {
                if (bufferRainbowTable.tellp() == 0)
                {
                    bufferRainbowTable << password << " ";
                    bufferRainbowTable << hash;
                }
                else
                {
                    bufferRainbowTable << endl << password << " ";
                    bufferRainbowTable << hash;
                }
            }
        }
    }
    file.close();
    bufferRainbowTable.close();
    remove(oldFileName.c_str());
    rename("RainbowTableBis6.txt", oldFileName.c_str());
}

void rainbow::generateSortedRainbowTableThread6()
{
    bool keepSorting=true;
    string s;
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    ifstream file("RainbowTable6.txt");
    ofstream file2("RainbowTableSorted6.txt");
    int count = 0;
    if(file)
    {
        while(keepSorting)
        {
            if(!line.empty())
            {
                line.pop_back();
                line.pop_back();
            }
            file>>s;
            line.push_back(s);
            file>>s;
            line.push_back(s);
            if(!bufferMin.empty())
            {
                while(!file.eof() && bufferMin.at(1) >= line.at(1))
                {
                    line.pop_back();
                    line.pop_back();
                    file>>s;
                    line.push_back(s);
                    file>>s;
                    line.push_back(s);
                }
                if(file.eof())
                {
                    if(bufferMin.at(1) < line.at(1))
                    {
                        file2<<line.at(0)<<" "<<line.at(1)<<endl;
                    }
                    keepSorting=false;
                }
            }
            buffer.push_back(line.at(0));
            buffer.push_back(line.at(1));
            while(!file.eof())
            {
                line.pop_back();
                line.pop_back();
                file>>s;
                line.push_back(s);
                file>>s;
                line.push_back(s);
                if(bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
                if(!bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1) && line.at(1) > bufferMin.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
            }
            if(!bufferMin.empty())
            {
                bufferMin.pop_back();
                bufferMin.pop_back();
            }
            bufferMin.push_back(buffer.at(0));
            bufferMin.push_back(buffer.at(1));
            if(keepSorting)
            {
                file2<<buffer.at(0)<<" "<<buffer.at(1)<<endl;
            }
            count++;
            if (keepSorting
                    && count <= nbLinesToDelete)
            {
                file.close();
                file2.close();
                reduceTable6("RainbowTable6.txt", buffer);
                count = 0;
                file.open("RainbowTable6.txt", ios_base::beg);
                file2.open("RainbowTableSorted6.txt", ios_base::app);
            }
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}

void rainbow::reduceTable7(string oldFileName, vector<string> lastSortedLine)
{
    ofstream bufferRainbowTable("RainbowTableBis7.txt");
    ifstream file(oldFileName.c_str());
    vector<string> buffer;
    string password;
    string hash;
    string line;
    if(file)
    {
        while (!file.eof())
        {
            file >> password;
            file >> hash;
            if (hash > lastSortedLine.at(1) && !file.eof())
            {
                if (bufferRainbowTable.tellp() == 0)
                {
                    bufferRainbowTable << password << " ";
                    bufferRainbowTable << hash;
                }
                else
                {
                    bufferRainbowTable << endl << password << " ";
                    bufferRainbowTable << hash;
                }
            }
        }
    }
    file.close();
    bufferRainbowTable.close();
    remove(oldFileName.c_str());
    rename("RainbowTableBis7.txt", oldFileName.c_str());
}

void rainbow::generateSortedRainbowTableThread7()
{
    bool keepSorting=true;
    string s;
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    ifstream file("RainbowTable7.txt");
    ofstream file2("RainbowTableSorted7.txt");
    int count = 0;
    if(file)
    {
        while(keepSorting)
        {
            if(!line.empty())
            {
                line.pop_back();
                line.pop_back();
            }
            file>>s;
            line.push_back(s);
            file>>s;
            line.push_back(s);
            if(!bufferMin.empty())
            {
                while(!file.eof() && bufferMin.at(1) >= line.at(1))
                {
                    line.pop_back();
                    line.pop_back();
                    file>>s;
                    line.push_back(s);
                    file>>s;
                    line.push_back(s);
                }
                if(file.eof())
                {
                    if(bufferMin.at(1) < line.at(1))
                    {
                        file2<<line.at(0)<<" "<<line.at(1)<<endl;
                    }
                    keepSorting=false;
                }
            }
            buffer.push_back(line.at(0));
            buffer.push_back(line.at(1));
            while(!file.eof())
            {
                line.pop_back();
                line.pop_back();
                file>>s;
                line.push_back(s);
                file>>s;
                line.push_back(s);
                if(bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
                if(!bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1) && line.at(1) > bufferMin.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
            }
            if(!bufferMin.empty())
            {
                bufferMin.pop_back();
                bufferMin.pop_back();
            }
            bufferMin.push_back(buffer.at(0));
            bufferMin.push_back(buffer.at(1));
            if(keepSorting)
            {
                file2<<buffer.at(0)<<" "<<buffer.at(1)<<endl;
            }
            count++;
            if (keepSorting
                    && count <= nbLinesToDelete)
            {
                file.close();
                file2.close();
                reduceTable7("RainbowTable7.txt", buffer);
                count = 0;
                file.open("RainbowTable7.txt", ios_base::beg);
                file2.open("RainbowTableSorted7.txt", ios_base::app);
            }
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}

void rainbow::reduceTable8(string oldFileName, vector<string> lastSortedLine)
{
    ofstream bufferRainbowTable("RainbowTableBis8.txt");
    ifstream file(oldFileName.c_str());
    vector<string> buffer;
    string password;
    string hash;
    string line;
    if(file)
    {
        while (!file.eof())
        {
            file >> password;
            file >> hash;
            if (hash > lastSortedLine.at(1) && !file.eof())
            {
                if (bufferRainbowTable.tellp() == 0)
                {
                    bufferRainbowTable << password << " ";
                    bufferRainbowTable << hash;
                }
                else
                {
                    bufferRainbowTable << endl << password << " ";
                    bufferRainbowTable << hash;
                }
            }
        }
    }
    file.close();
    bufferRainbowTable.close();
    remove(oldFileName.c_str());
    rename("RainbowTableBis8.txt", oldFileName.c_str());
}

void rainbow::generateSortedRainbowTableThread8()
{
    bool keepSorting=true;
    string s;
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    ifstream file("RainbowTable8.txt");
    ofstream file2("RainbowTableSorted8.txt");
    int count = 0;
    if(file)
    {
        while(keepSorting)
        {
            if(!line.empty())
            {
                line.pop_back();
                line.pop_back();
            }
            file>>s;
            line.push_back(s);
            file>>s;
            line.push_back(s);
            if(!bufferMin.empty())
            {
                while(!file.eof() && bufferMin.at(1) >= line.at(1))
                {
                    line.pop_back();
                    line.pop_back();
                    file>>s;
                    line.push_back(s);
                    file>>s;
                    line.push_back(s);
                }
                if(file.eof())
                {
                    if(bufferMin.at(1) < line.at(1))
                    {
                        file2<<line.at(0)<<" "<<line.at(1)<<endl;
                    }
                    keepSorting=false;
                }
            }
            buffer.push_back(line.at(0));
            buffer.push_back(line.at(1));
            while(!file.eof())
            {
                line.pop_back();
                line.pop_back();
                file>>s;
                line.push_back(s);
                file>>s;
                line.push_back(s);
                if(bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
                if(!bufferMin.empty())
                {
                    if(line.at(1) < buffer.at(1) && line.at(1) > bufferMin.at(1))
                    {
                        buffer.pop_back();
                        buffer.pop_back();
                        buffer.push_back(line.at(0));
                        buffer.push_back(line.at(1));
                    }
                }
            }
            if(!bufferMin.empty())
            {
                bufferMin.pop_back();
                bufferMin.pop_back();
            }
            bufferMin.push_back(buffer.at(0));
            bufferMin.push_back(buffer.at(1));
            if(keepSorting)
            {
                file2<<buffer.at(0)<<" "<<buffer.at(1)<<endl;
            }
            count++;
            if (keepSorting
                    && count <= nbLinesToDelete)
            {
                file.close();
                file2.close();
                reduceTable8("RainbowTable8.txt", buffer);
                count = 0;
                file.open("RainbowTable8.txt", ios_base::beg);
                file2.open("RainbowTableSorted8.txt", ios_base::app);
            }
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}

void rainbow::generateFinalRainbowTable()
{
    ifstream file1("RainbowTableSorted6.txt");
    ifstream file2("RainbowTableSorted7.txt");
    ifstream file3("RainbowTableSorted8.txt");
    ofstream fileFinal("RainbowTable.txt");

    string s;
    while(getline(file1, s))
    {
        fileFinal<<s<<endl;
    }
    while(getline(file2, s))
    {
        fileFinal<<s<<endl;
    }
    while(getline(file3, s))
    {
        fileFinal<<s<<endl;
    }
}
