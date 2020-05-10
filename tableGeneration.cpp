#include <iostream>
#include <vector>
#include <string>
#include "passwd-utils.hpp"
#include "tableGeneration.h"
#include <fstream>

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

/**
 * @brief getLastLineOfFile
 * Gets the  last line of a text file
 * @param fileName the name of the file in which we have to look for the last line
 * @return a string that contains each character of the last line
 */
string getLastLineOfFile(string fileName)
{
    ifstream fin;
    string lastLine;
    fin.open(fileName);
    if(fin.is_open())
    {
        fin.seekg(-1,ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while(keepLooping)
        {
            char ch;
            fin.get(ch);                            // Get current byte's data

            if((int)fin.tellg() <= 1)
            {                                       // If the data was at or before the 0th byte
                fin.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n')
            {                                       // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else
            {                                       // If the data was neither a newline nor at the 0 byte
                fin.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
        getline(fin,lastLine);                      // Read the current line

        fin.close();
    }
    return lastLine;
}

vector<string> rainbow::generateOneLine(string& password)
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

void rainbow::generateUnsortedRainbowTables(unsigned int passwordLength)
{
    //passwordLength += 5;
    ofstream rainbowTable;
    string fileName = "RainbowTable";
    string extension = ".txt";
    fileName += to_string(passwordLength);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    rainbowTable = generateOfstreamTextFile(fileName);
    //ifstream fichier(fileName.c_str(),ios::binary);
    //int size;
    rainbowTable.open(fileName.c_str(), ios_base::app);
    bool first = true;
    while (filesize(fileName.c_str()) < fileSize)
    {
        string input = generate_passwd(passwordLength);
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

/*void rainbow::thread7()
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
    //ifstream fichier(fileName.c_str(),ios::binary);
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
    //ifstream fichier(fileName.c_str(),ios::binary);
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
}*/

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

void rainbow::reduceTable(string& oldFileName, vector<string> lastSortedLine, unsigned int passwordLength)
{
    ofstream rainbowTable;
    string fileName = "RainbowTableBis";
    string extension = ".txt";
    fileName += to_string(passwordLength);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }
    ofstream bufferRainbowTable(fileName.c_str());
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
    rename(fileName.c_str(), oldFileName.c_str());
}

void rainbow::generateSortedRainbowTables(unsigned int passwordLength)
{
    bool keepSorting=true;
    string s;
    string rainbowTable = "RainbowTable";
    string sortedFileName = "RainbowTableSorted";
    string extension = ".txt";
    rainbowTable += to_string(passwordLength);
    sortedFileName += to_string(passwordLength);
    string sorted = "SORTED";
    for (unsigned int l = 0; l < sorted.size(); l++)
    {
        sortedFileName += sorted.at(l);
    }
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        rainbowTable += extension.at(i);
        sortedFileName += extension.at(i);
    }
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    ifstream file(rainbowTable.c_str());
    ofstream file2(sortedFileName.c_str());
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
                reduceTable(rainbowTable, buffer, passwordLength);
                count = 0;
                file.open(rainbowTable.c_str(), ios_base::beg);
                file2.open(sortedFileName.c_str(), ios_base::app);
            }
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}

/*void rainbow::reduceTable7(string& oldFileName, vector<string> lastSortedLine)
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
}*/

/*void rainbow::generateSortedRainbowTableThread7()
{
    bool keepSorting=true;
    string s;
    string rainbowTable = "RainbowTable7.txt";
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
                reduceTable8(rainbowTable, buffer);
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
}*/

/*void rainbow::reduceTable8(string& oldFileName, vector<string> lastSortedLine)
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
}*/

/*void rainbow::generateSortedRainbowTableThread8()
{
    bool keepSorting=true;
    string s;
    string rainbowTable = "RainbowTable8.txt";
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
                reduceTable8(rainbowTable, buffer);
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
}*/

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
    fileFinal.close();
}











void rainbow::generateSortedRainbowTableCharPerChar(string& fileToWriteInName, string& fileToReadInName)
{
    bool keepSorting=true;
    string s;
    vector<string> line;
    vector<string> buffer;
    vector<string> bufferMin;
    ifstream file(fileToReadInName);
    ofstream file2(fileToWriteInName);
    //int count = 0;
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
            if (s == "")
            {
                return;
            }
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
            buffer.pop_back();
            buffer.pop_back();
            file.seekg(0,ios_base::beg);
        }
        file.close();
        file2.close();
    }
}

void rainbow::generateUnsortedRainbowTablePerFirstChar(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName)
{
    ofstream bufferRainbowTable(fileToWriteInName.c_str());
    ifstream file(fileToReadInName.c_str());
    bufferRainbowTable.clear();
    string password;
    string hash;
    if(file)
    {
        while (!file.eof())
        {
            file >> password;
            file >> hash;
            if (hash == "")
            {
                return;
            }
            else if (hash.at(charInHashPosition) == charOfHash)
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
            else if (hash.at(0) != charOfHash && !file.eof()){ }
        }
    }
    file.close();
    bufferRainbowTable.close();
}

void rainbow::deleteReadLinesInFile(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName)
{
    ofstream bufferRainbowTable(fileToWriteInName.c_str()/*, ios_base::app*/);
    ifstream file(fileToReadInName.c_str());

    string password;
    string hash;
    string line;
    line += password;
    line += ' ';
    line += hash;
    if(file)
    {
        while (!file.eof())
        {
            file >> password;
            file >> hash;
            if (hash == "")
            {
                return;
            }
            else if (hash.at(charInHashPosition) != charOfHash)
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
    remove(fileToReadInName.c_str());
    rename(fileToReadInName.c_str(), fileToWriteInName.c_str());                    // peut-être faut-il échanger l'ancien et le nouveau fichier
}

void rainbow::createEachCharHashTextFile(unsigned int passwordLength)
{
    string rainbowTableFileName = "RainbowTable";
    string temporaryRainbowTableFileName = "RainbowTableTemporaryForRT";
    string unsorted = "UNSORTED";
    string extension = ".txt";
    rainbowTableFileName += to_string(passwordLength);
    temporaryRainbowTableFileName += to_string(passwordLength);
    for (unsigned int j = 0; j < extension.size(); j++)
    {
        rainbowTableFileName += extension.at(j);
        temporaryRainbowTableFileName += extension.at(j);
    }
    static const string char_policy = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        string unsortedFileName = "RainbowTable";
        unsortedFileName += to_string(passwordLength);
        for (unsigned int j = 0; j < unsorted.size(); j++)
        {
            unsortedFileName += unsorted.at(j);
        }
        unsortedFileName += char_policy.at(i);
        for (unsigned int j = 0; j < extension.size(); j++)
        {
            unsortedFileName += extension.at(j);
        }
        generateUnsortedRainbowTablePerFirstChar(0, char_policy.at(i), unsortedFileName, rainbowTableFileName);
        deleteReadLinesInFile(0, char_policy.at(i), temporaryRainbowTableFileName, rainbowTableFileName);
        remove(temporaryRainbowTableFileName.c_str());
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            string unsortedSecondFileName = "RainbowTable";
            string temporarySecondaryUnsortedRainbowTableFileName = "RainbowTableTemporarySecondaryForRT";
            temporarySecondaryUnsortedRainbowTableFileName += to_string(passwordLength);
            unsortedSecondFileName += to_string(passwordLength);
            for (unsigned int k = 0; k < unsorted.size(); k++)
            {
                unsortedSecondFileName += unsorted.at(k);
            }
            unsortedSecondFileName += char_policy.at(i);
            unsortedSecondFileName += char_policy.at(j);
            temporarySecondaryUnsortedRainbowTableFileName += char_policy.at(i);
            temporarySecondaryUnsortedRainbowTableFileName += char_policy.at(j);
            for (unsigned int k = 0; k < extension.size(); k++)
            {
                unsortedSecondFileName += extension.at(k);
                temporarySecondaryUnsortedRainbowTableFileName += extension.at(k);
            }
            generateUnsortedRainbowTablePerFirstChar(1, char_policy.at(j), unsortedSecondFileName, unsortedFileName);
            //deleteReadLinesInFile(1, char_policy.at(i), temporarySecondaryUnsortedRainbowTableFileName, unsortedFileName);               // Ceci fait perdre du temps. Simplement supprimer le fichier final sera peut-être suffisant
            remove(temporarySecondaryUnsortedRainbowTableFileName.c_str());
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                string unsortedThirdFileName = "RainbowTable";
                string temporaryTertiaryUnsortedRainbowTableFileName = "RainbowTableTemporaryTertiaryForRT";
                unsortedThirdFileName += to_string(passwordLength);
                for (unsigned int l = 0; l < unsorted.size(); l++)
                {
                    unsortedThirdFileName += unsorted.at(l);
                }
                unsortedThirdFileName += char_policy.at(i);
                unsortedThirdFileName += char_policy.at(j);
                unsortedThirdFileName += char_policy.at(k);
                temporaryTertiaryUnsortedRainbowTableFileName += char_policy.at(i);
                temporaryTertiaryUnsortedRainbowTableFileName += char_policy.at(j);
                temporaryTertiaryUnsortedRainbowTableFileName += char_policy.at(k);
                for (unsigned int l = 0; l < extension.size(); l++)
                {
                    unsortedThirdFileName += extension.at(l);
                    temporaryTertiaryUnsortedRainbowTableFileName += extension.at(l);
                }
                generateUnsortedRainbowTablePerFirstChar(2, char_policy.at(k), unsortedThirdFileName, unsortedSecondFileName);
                //deleteReadLinesInFile(1, char_policy.at(i), temporaryTertiaryUnsortedRainbowTableFileName, unsortedSecondFileName);               // Ceci fait perdre du temps. Simplement supprimer le fichier final sera peut-être suffisant
                remove(temporaryTertiaryUnsortedRainbowTableFileName.c_str());
            }
            remove(unsortedSecondFileName.c_str());
        }
        remove(unsortedFileName.c_str());
    }
}

void rainbow::sortEveryCharUnsortedTextFile(unsigned int passwordLength)
{
    static const string char_policy = "0123456789abcdefghijklmnopqrstuvwxyz";
    string extension = ".txt";
    string sorted = "SORTED";
    string unsorted = "UNSORTED";
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                string unsortedFileName = "RainbowTable";
                unsortedFileName += to_string(passwordLength);
                for (unsigned int l = 0; l < unsorted.size(); l++)
                {
                    unsortedFileName += unsorted.at(l);
                }
                string sortedFileName = "RainbowTable";
                sortedFileName += to_string(passwordLength);
                for (unsigned int l = 0; l < sorted.size(); l++)
                {
                    sortedFileName += sorted.at(l);
                }
                unsortedFileName += char_policy.at(i);
                unsortedFileName += char_policy.at(j);
                unsortedFileName += char_policy.at(k);
                sortedFileName += char_policy.at(i);
                sortedFileName += char_policy.at(j);
                sortedFileName += char_policy.at(k);
                for (unsigned int l = 0; l < extension.size(); l++)
                {
                    unsortedFileName += extension.at(l);
                    sortedFileName += extension.at(l);
                }
                generateSortedRainbowTableCharPerChar(sortedFileName, unsortedFileName);
                remove(unsortedFileName.c_str());
            }
        }
    }
}

void rainbow::addSortedFilesToCorrespondingRainbowTable(unsigned int passwordLength)
{
    string finalFileName = "RainbowTableSorted";
    string extension = ".txt";
    string sorted = "SORTED";
    finalFileName += to_string(passwordLength);
    for (unsigned int j = 0; j < extension.size(); j++)
    {
        finalFileName += extension.at(j);
    }
    ofstream finalFile(finalFileName.c_str());
    static const string char_policy = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                ifstream charSortedFile;
                string sortedFileName = "RainbowTable";
                sortedFileName += to_string(passwordLength);
                for (unsigned int l = 0; l < sorted.size(); l++)
                {
                    sortedFileName += sorted.at(l);
                }
                sortedFileName += char_policy.at(i);
                sortedFileName += char_policy.at(j);
                sortedFileName += char_policy.at(k);
                for (unsigned int l = 0; l < extension.size(); l++)
                {
                    sortedFileName += extension.at(l);
                }
                charSortedFile.open(sortedFileName.c_str(), ios_base::binary);
                string s;
                while(getline(charSortedFile, s))
                {
                    finalFile<<s<<endl;
                }
                remove(sortedFileName.c_str());
            }
        }
    }
}

void rainbow::sort()
{
    for (unsigned int i = 6; i < 7; i++)
    {
        createEachCharHashTextFile(i);
        sortEveryCharUnsortedTextFile(i);
        addSortedFilesToCorrespondingRainbowTable(i);
    }
}

void rainbow::putAllInFinalTable()
{
    for (unsigned int i = 6; i < 9; i++)
    {
        string rainbowTable = "RainbowTable";
        string rainbowTableName = "RainbowTable";
        string extension = ".txt";
        rainbowTableName += to_string(i);
        for (unsigned int j = 0; j < extension.size(); j++)
        {
            rainbowTableName += extension.at(j);
            rainbowTable += extension.at(j);
        }
        cout << rainbowTable << endl;
        ofstream finalFile(rainbowTable.c_str(), ios_base::app);
        ifstream tempFile(rainbowTableName.c_str());
        //while(tempFile.eof())
        {
            finalFile << tempFile.rdbuf();
        }
    }
}
