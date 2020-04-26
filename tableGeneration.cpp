#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "passwd-utils.hpp"
#include "tableGeneration.h"
#include <fstream>
#include <sys/stat.h>
#include <thread>

using namespace std;
using namespace rainbow;

// b is excluded
/*int rainbow::randomBetweenMinAndMax(int a, int b)
{
    return rand() % (b - a) + a;
}*/

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
    line.push_back("\n");
    return line;
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

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

void rainbow::thread6(/*unsigned int passwordLength*/)
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
    while (filesize(fileName.c_str()) < 400/*9995896*/)
    {
        string input = generate_passwd(6/*passwordLength*/);
        vector<string> textToPutIn = generateOneLine(input);

        for (unsigned i = 0; i < textToPutIn.size(); i++)
        {
            /*fichier.seekg(0,ios_base::end);
            size= fichier.tellg();
            fichier.seekg(0,ios_base::beg);*/
            //cout << "size= " << size << endl;
            //putLineAtRightPlace(textToPutIn);
            rainbowTable << textToPutIn.at(i);
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
    while (filesize(fileName.c_str()) < 400/*9995896*/)
    {
        string input = generate_passwd(7);
        vector<string> textToPutIn = generateOneLine(input);

        for (unsigned i = 0; i < textToPutIn.size(); i++)
        {
            /*fichier.seekg(0,ios_base::end);
            size= fichier.tellg();
            fichier.seekg(0,ios_base::beg);*/
            //cout << "size= " << size << endl;
            //putLineAtRightPlace(textToPutIn);
            rainbowTable << textToPutIn.at(i);
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
    while (filesize(fileName.c_str()) < 400/*9995896*/)
    {
        string input = generate_passwd(8);
        vector<string> textToPutIn = generateOneLine(input);

        for (unsigned i = 0; i < textToPutIn.size(); i++)
        {
            /*fichier.seekg(0,ios_base::end);
            size= fichier.tellg();
            fichier.seekg(0,ios_base::beg);*/
            //cout << "size= " << size << endl;
            //putLineAtRightPlace(textToPutIn);
            rainbowTable << textToPutIn.at(i);
        }
    }
    rainbowTable.close();
}

void rainbow::generateSortedRainbowTables(unsigned int passwordLength)
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
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileUnsortedName += extension.at(i);
    }
    fileSortedName += to_string(passwordLength);
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

vector<string> rainbow::lastLineOfFile()
{
    ifstream file("RainbowTable.txt",ios::binary);
    char s;
    vector<string> line;
    string buff;
    file.seekg(-1,ios_base::end);
    file.get(s);
    while(s!='\n')
    {
        if(file.tellg() <= 1)
        {
            file.seekg(-1,ios_base::cur);
            break;
        }
        file.seekg(-2,ios_base::cur);
        file.get(s);
    }
    file>>buff;
    line.push_back(buff);
    file>>buff;
    line.push_back(buff);
    return line;
}

void /*rainbow::*/generateSortedRainbowTable()
{
    ofstream rainbowTableSorted;
    rainbowTableSorted = generateOfstreamTextFile("RainbowTableSorted.txt");
    ifstream fichier("RainbowTable.txt",ios::binary);
    int size;
    rainbowTableSorted.open("RainbowTable.txt",ios::binary);
    fichier.seekg(0,ios_base::end);
    size = fichier.tellg();
    fichier.close();
    while(size>0)
    {
        vector<string> buffer;
        ifstream file("RainbowTable.txt");
        if(file)
        {

            int cpt = 0;
            int cptBuffer = cpt;
            vector<string> line;
            while(getline(file, line[0]))
            {
                cpt++;
                getline(file, line[1]);
                if( line[0].size() < buffer[0].size())
                {
                    buffer[0]=line[0];
                    buffer[1]=line[1];
                }else if(line[0].size() == buffer[0].size())
                {
                    if(line[1] < buffer[1]){
                        buffer[0]=line[0];
                        buffer[1]=line[1];
                        cptBuffer=cpt;
                    }
                }
            }
            file.close();

            ofstream fileb("RainbowTable.txt");
            //delete la ligne numero 'cptBuffer'
            fileb.close();

            file.open("RainbowTable.txt",ios_base::app);
            fichier.seekg(0,ios_base::end);
            size= fichier.tellg();
            fichier.close();

            ifstream file2("RainbowTableSorted.txt");
            file2.seekg(0,ios_base::end);
            lastLineOfFile();                //lire la derniere ligne
            vector<string> lastLine;
            if(lastLine[0] == buffer[0] && lastLine[1] == buffer[1])
            {
                return;
            }
            file2.close();

            ofstream file2b("RainbowTableSorted.txt");
            file2.seekg(0,ios_base::end);
            file2b<<buffer[0]<<" "<<buffer[1]<<endl;
            file2b.close();

        }
    }
    rainbowTableSorted.close();
}

vector<string> /*rainbow::*/goToLine(fstream& file, unsigned int num)
{
    //file.seekg(2);
    int i = 0;
    //for(int i=0; i < num - 1; ++i)
    //{

    vector<string> chaine;
    int countLine = 0;
    //cout << num << endl;
    ifstream file2("RainbowTable.txt");
    static const std::string char_policy = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
    while(i != num)
    {
        file2.ignore(numeric_limits<streamsize>::max(),'\n');
        //file2.is_open();
        cout << countLine << endl;
        countLine++;
        i++;
    }
    return chaine;
    //}
    string line;
    string psw;
    unsigned count=0;
    while(file >> line)
    {
        if(count == 0)
        {
            psw = line;
        }
        else
        {
            chaine.push_back(psw);
            chaine.push_back(" ");
            chaine.push_back(line);
        }
        count++;
        count%=2;
    }


    return chaine;
    //return file.read();
}

void /*rainbow::*/putLineAtRightPlace(vector<string> line)
{
    vector<string> chainToInsert;
    vector<string> chainToCompare;
    vector<string> chainToCompare2;
    fstream rainbowTable;
    rainbowTable.open("RainbowTable.txt");
    int size; // size of the file ( nbre de ligne)
    int count = size/2;
    count++;
    unsigned int rest = count;
    while(true){
        cout << count;
        chainToCompare = goToLine(rainbowTable, count);//trouver une maniere de prendre une ligne precisement
        if(chainToInsert[0] == chainToCompare[0]  && chainToInsert[1] == chainToCompare[1])
        {
            break;
        }
        else if(chainToInsert[1] < chainToCompare[1]){
            if(count == 1){
                for (unsigned i = 0; i < line.size(); i++)
                {
                    rainbowTable << line.at(i);
                }
                //insere la chain a la premiere ligne et decaler le reste
                break;
            }
            else{
                chainToCompare2 = goToLine(rainbowTable, count);//trouver une maniere de prendre une ligne precisement
                if(chainToInsert[1] < chainToCompare[1]){
                    count/=2;
                    count++;
                }
                else if(chainToInsert[1] > chainToCompare[1]){
                    for (unsigned i = 0; i < line.size(); i++)
                    {
                        rainbowTable << line.at(i);
                    }
                    //insere la chaine a la ligne count-1 et decaler le reste;
                    break;
                }
            }
        }else if(chainToInsert[1] > chainToCompare[1]){
            if(count == size){
                for (unsigned i = 0; i < line.size(); i++)
                {
                    rainbowTable << line.at(i);
                }
                //insere la chain a la derniere ligne
                break;
            }
            else{
                //chainToCompare2 = file.getline(count+1);//trouver une maniere de prendre une ligne precisement
                if(chainToInsert[1] > chainToCompare[1]){
                    rest/=2;
                    rest++;
                    count+=rest;
                }
                else if(chainToInsert[1] < chainToCompare[1]){
                    for (unsigned i = 0; i < line.size(); i++)
                    {
                        rainbowTable << line.at(i);
                    }
                    //insere la chaine a la ligne count+1 et decaler le reste;
                    break;
                }
            }
        }
    }
    rainbowTable.close();
}
