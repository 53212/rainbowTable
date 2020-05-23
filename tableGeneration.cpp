#include <iostream>
#include <vector>
#include <string>
#include "passwd-utils.hpp"
#include "tableGeneration.h"

using namespace std;
using namespace rainbow;
namespace fs = std::filesystem;

/**
 * @brief generateOfstreamTextFile
 * Generates a text file to be able to write in it
 * @param fileName
 * The name of the file to create
 * @return the created ofstream file
 */
/*ofstream generateOfstreamTextFile(string fileName)
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
}*/

/**
 * @brief filesize
 * Checks the size of a file belonging its name
 * @param filename
 * the name of the file that it must check the size
 * @return the size of the file
 */
long int sizeOfFile(const char* filename)
{
    // opening the file in read mode
    FILE* fp = fopen(filename, "r");

    // checking if the file exist or not
    if (fp == nullptr)
    {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
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

/**
 * @brief createFileName
 * Creates a file name
 * @param baseName
 * The basic name of the file
 * @param passwordLength
 * The length of the password that will be or not in the file for which this function creates a name
 * @param threadNumber
 * The number of the thread that will be or notin the file for which this function creates a name
 * @param isSorted
 * Bool to let this function know if the name have to contain "SORTED"
 * @param isUnsorted
 * Bool to let this function know if the name have to contain "UNSORTED"
 * @param hashFirstChar
 * The first character of the hash that should maybe be in the name of the file if
 * the file is sorted on the first char of the hashes that it contains
 * @param hashSecondChar
 * The second character of the hash that should maybe be in the name of the file if
 * the file is sorted on the first and second char of the hashes that it contains
 * @param hashThirdChar
 * The third character of the hash that should maybe be in the name of the file if
 * the file is sorted on the first, second and third char of the hashes that it contains
 * @return
 */
string createFileName(string baseName, unsigned int passwordLength, int threadNumber, bool isSorted, bool isUnsorted, char hashFirstChar, char hashSecondChar, char hashThirdChar)
{
    string sorted = "SORTED";
    string unsorted = "UNSORTED";
    string forThread = "ForThread";
    string extension = ".txt";
    if (passwordLength != noNumber)
    {
        baseName += to_string(passwordLength);
        if (threadNumber != noNumber)
        {
            for (unsigned int i = 0; i < forThread.size(); i++)
            {
                baseName += forThread.at(i);
            }
            baseName += to_string(threadNumber);
        }
        else
        {
            if (isSorted)
            {
                for (unsigned int i = 0; i < sorted.size(); i++)
                {
                    baseName += sorted.at(i);
                }
            }
            else if (isUnsorted)
            {
                for (unsigned int i = 0; i < unsorted.size(); i++)
                {
                    baseName += unsorted.at(i);
                }
            }
            if (hashFirstChar != noChar)
            {
                baseName += hashFirstChar;
            }
            if (hashSecondChar != noChar)
            {
                baseName += hashSecondChar;
            }
            if (hashThirdChar != noChar)
            {
                baseName += hashThirdChar;
            }
        }
    }
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        baseName += extension.at(i);
    }
    return baseName;
}

vector<string> rainbow::generateOneLine(string& password)
{
    vector<string> line;
    line.push_back(password);
    string hash = sha256(password);
    string hashReduction;
    line.push_back(" ");
    for (unsigned int i = 0; i < nbPassWordsInEveryLine; i++)
    {
        hashReduction = reduce(hash, i, line.at(0).length());
        hash = sha256(hashReduction);
        if (i == nbPassWordsInEveryLine-1)
        {
            line.push_back(hash);
        }
    }
    return line;
}

void rainbow::generate100Hashes()
{
    string filePswdName = "Mots de passe.txt";
    string fileHashName = "HashToUncypher.txt";
    ofstream passwords("Mots de passe.txt");
    ofstream hashes("HashToUncypher.txt");
    //passwords = generateOfstreamTextFile(filePswdName);
    //hashes = generateOfstreamTextFile(fileHashName);
    //ifstream fichier(filePswdName.c_str(),ios::binary);
    //int size;
    passwords.open(filePswdName.c_str(), ios_base::app);
    hashes.open(fileHashName.c_str(), ios_base::app);
    bool first = true;
    int a = 0;
    while (a < nbPassWordsInEveryLine)
    {
        for (unsigned int i = 0; i < nbPassWordsInEveryLine/3; i++)
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
        for (unsigned int i = 0; i < nbPassWordsInEveryLine/3; i++)
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
        for (unsigned int i = 0; i < (nbPassWordsInEveryLine/3) + 1; i++)
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

void rainbow::generate3RainbowTableFiles()
{
    vector<thread> threadVector;
    for (unsigned int i = 6; i < 9; i++)
    {
        threadVector.push_back(thread([i]()
        {
            generateUnsortedRainbowTables(i);
        }));
    }
    for_each(threadVector.begin(), threadVector.end(), [](thread &t)
    {
        t.join();
    });
}

long int sizeToGeneratePerThread()
{
    return fileSize / nbThreadsThatGeneratesPasswords;
}

string workOfOneThread(unsigned int passwordLength, unsigned int threadNumber)
{
    string fileName = createFileName("RainbowTable", passwordLength, threadNumber, false, false, noChar, noChar, noChar);
    ofstream rainbowTable(fileName.c_str()/*, ios_base::app*/);
    vector<vector<string>> linesToAdd;
    bool first = true;
    while (sizeOfFile(fileName.c_str()) < sizeToGeneratePerThread()
           && (sizeOfFile(fileName.c_str()) + (linesToAdd.size()*72)) < sizeToGeneratePerThread())
    {
        string input = generate_passwd(passwordLength);
        linesToAdd.push_back(generateOneLine(input));
        if (linesToAdd.size() >= 1)
        {
            for (unsigned int i = 0; i < linesToAdd.size(); i++)
            {
                try
                {
                    if (!linesToAdd.at(i).empty())
                    {
                        if (first)
                        {
                            first = false;
                            rainbowTable << linesToAdd.at(i).at(0) << linesToAdd.at(i).at(1) << linesToAdd.at(i).at(2);
                        }
                        else
                        {
                            rainbowTable << endl;
                            rainbowTable << linesToAdd.at(i).at(0) << linesToAdd.at(i).at(1) << linesToAdd.at(i).at(2);
                        }
                    }
                    else
                    {
                        cout << "Vecteur vide" << endl;
                    }
                    if(!linesToAdd.empty())
                    {
                        linesToAdd.pop_back();
                    }
                }
                catch (exception e)
                {
                    cout << "problem : " << e.what() << endl;
                    // problème du mloc à régler
                }
            }
        }
        else if ((sizeOfFile(fileName.c_str()) + (linesToAdd.size()*72)) >= fileSize)
        {
            for (unsigned int i = 0; i < linesToAdd.size(); i++)
            {
                rainbowTable << endl;
                rainbowTable << linesToAdd.at(i).at(0) << linesToAdd.at(i).at(1) << linesToAdd.at(i).at(2);
            }
        }
    }
    return fileName;
}

/*vector<string> rainbow::pushInLine(unsigned int passwordLength)
{
    vector<string> lineToAdd;
    string input = generate_passwd(passwordLength);
    vector<string> textToPutIn = generateOneLine(input);
    lineToAdd.push_back(textToPutIn);
    return lineToAdd;
}*/

void rainbow::generateUnsortedRainbowTables(unsigned int passwordLength)
{
    // création du nom de fichier
    string fileName = createFileName("RainbowTable", passwordLength, noNumber, false, false, noChar, noChar, noChar);
    ofstream rainbowTable(fileName.c_str()/*, ios_base::app*/);
    vector<vector<string>> linesToAdd;
    //while (sizeOfFile(fileName.c_str()) < fileSize
    //     && (sizeOfFile(fileName.c_str()) + (linesToAdd.size()*72)) < fileSize) //taille du fichier + taille du vector<thread> * 72 car chaque ligne (mot de passe + hash) fait 72 octets
    //{
    vector<future<string>> threadVector;
    for (unsigned int i = 0; i < nbThreadsThatGeneratesPasswords; i++) // to generate 15 threads that creates a random password and it chain
    {
        threadVector.push_back(async(&workOfOneThread, passwordLength, i));
    }
    unsigned int finishedThread = 0;
    while(finishedThread < nbThreadsThatGeneratesPasswords) // = .join(), but .get locks the other possible threads
    {
        string threadFileName = threadVector.at(finishedThread).get();
        ifstream threadRainbowTable(threadFileName, ios_base::beg);
        rainbowTable << threadRainbowTable.rdbuf();
        finishedThread++;
        if (finishedThread != nbThreadsThatGeneratesPasswords)
        {
            rainbowTable << endl;
        }
        remove(threadFileName.c_str());
    }
    rainbowTable.close();
}

void rainbow::reduceTable(string& oldFileName, vector<string> lastSortedLine, unsigned int passwordLength)
{
    ofstream rainbowTable;
    /*string fileName = "RainbowTableBis";
    string extension = ".txt";
    fileName += to_string(passwordLength);
    for (unsigned int i = 0; i < extension.size(); i++)
    {
        fileName += extension.at(i);
    }*/
    string fileName = createFileName("RainbowTableBis", passwordLength, noNumber, false, false, noChar, noChar, noChar);
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
    string rainbowTable = createFileName("RainbowTable", passwordLength, noNumber, false, false, noChar, noChar, noChar);
    string sortedFileName = createFileName("RainbowTable", passwordLength, noNumber, true, false, noChar, noChar, noChar);
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

void rainbow::generateFinalRainbowTable()
{
    ifstream file1(createFileName("RainbowTable", 6, noNumber, false, false, noChar, noChar, noChar).c_str());
    ifstream file2(createFileName("RainbowTable", 7, noNumber, false, false, noChar, noChar, noChar).c_str());
    ifstream file3(createFileName("RainbowTable", 8, noNumber, false, false, noChar, noChar, noChar).c_str());
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

void rainbow::generateUnsortedRainbowTablePerCharAt(unsigned int charInHashPosition, char charOfHash, string& fileToWriteInName, string& fileToReadInName)
{
    ofstream bufferRainbowTable(fileToWriteInName.c_str());
    ifstream file(fileToReadInName.c_str());
    //bufferRainbowTable.clear();
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
            // To let the program do nothing instead of going out of the conditions.
            // Otherwise, it could generate an exception
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
    // I stop it at g because no hash seems to begin by a letter which position in the alphabet is g or later
    static const string char_policy = "0123456789abcdef";//ghijklmnopqrstuvwxyz";
    string rainbowTableFileName = createFileName("RainbowTable", passwordLength, noNumber, false, false, noChar, noChar, noChar);
    string temporaryRainbowTableFileName = createFileName("RainbowTableTemporaryForRT", passwordLength, noNumber, false, false, noChar, noChar, noChar);
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        string unsortedFileName = createFileName("RainbowTable", passwordLength, noNumber, false, true, char_policy.at(i), noChar, noChar);
        generateUnsortedRainbowTablePerCharAt(0, char_policy.at(i), unsortedFileName, rainbowTableFileName);
        //deleteReadLinesInFile(0, char_policy.at(i), temporaryRainbowTableFileName, rainbowTableFileName);
        //remove(temporaryRainbowTableFileName.c_str());
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            string unsortedSecondFileName = createFileName("RainbowTable", passwordLength, noNumber, false, true, char_policy.at(i), char_policy.at(j), noChar);
            string temporarySecondaryUnsortedRainbowTableFileName = createFileName("temporarySecondaryUnsortedRainbowTableFileName", passwordLength, noNumber, false, false, char_policy.at(i), char_policy.at(j), noChar);
            generateUnsortedRainbowTablePerCharAt(1, char_policy.at(j), unsortedSecondFileName, unsortedFileName);
            //deleteReadLinesInFile(1, char_policy.at(i), temporarySecondaryUnsortedRainbowTableFileName, unsortedFileName);               // Ceci fait perdre du temps. Simplement supprimer le fichier final sera peut-être suffisant
            //remove(temporarySecondaryUnsortedRainbowTableFileName.c_str());
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                string unsortedThirdFileName = createFileName("RainbowTable", passwordLength, noNumber, false, true, char_policy.at(i), char_policy.at(j), char_policy.at(k));
                string temporaryTertiaryUnsortedRainbowTableFileName = createFileName("RainbowTableTemporaryTertiaryForRT", passwordLength, noNumber, false, false, char_policy.at(i), char_policy.at(j), char_policy.at(k));
                generateUnsortedRainbowTablePerCharAt(2, char_policy.at(k), unsortedThirdFileName, unsortedSecondFileName);
                //deleteReadLinesInFile(1, char_policy.at(i), temporaryTertiaryUnsortedRainbowTableFileName, unsortedSecondFileName);               // Ceci fait perdre du temps. Simplement supprimer le fichier final sera peut-être suffisant
                //remove(temporaryTertiaryUnsortedRainbowTableFileName.c_str());
            }
            remove(unsortedSecondFileName.c_str());
        }
        remove(unsortedFileName.c_str());
    }
    remove(temporaryRainbowTableFileName.c_str());
}

void rainbow::sortEveryCharUnsortedTextFile(unsigned int passwordLength/*, char sortFilesFromThisChar, char sortFilesUntilThisChar*/)
{
    // I stop it at g because no hash seems to begin by a letter which position in the alphabet is g or later
    static const string char_policy = "0123456789abcdef";//ghijklmnopqrstuvwxyz";
    int fileToRead = 0;
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                cout << "fileToRead : " << fileToRead << endl;
                string unsortedFileName = createFileName("RainbowTable", passwordLength, noNumber, false, true, char_policy.at(i), char_policy.at(j), char_policy.at(k));
                string sortedFileName = createFileName("RainbowTable", passwordLength, noNumber, true, false, char_policy.at(i), char_policy.at(j), char_policy.at(k));
                generateSortedRainbowTableCharPerChar(sortedFileName, unsortedFileName);
                remove(unsortedFileName.c_str());
                fileToRead++;
            }
        }
    }
}

void rainbow::addSortedFilesToCorrespondingRainbowTable(unsigned int passwordLength)
{
    string finalFileName = createFileName("RainbowTable", passwordLength, noNumber, true, false, noChar, noChar, noChar);
    ofstream finalFile(finalFileName.c_str());
    int nbFilesRead = 0;
    // I stop it at g because no hash seems to begin by a letter which position in the alphabet is g or later
    static const string char_policy = "0123456789abcdef";//ghijklmnopqrstuvwxyz";
    for (unsigned int i = 0; i < char_policy.size(); i++)
    {
        for (unsigned int j = 0; j < char_policy.size(); j++)
        {
            for (unsigned int k = 0; k < char_policy.size(); k++)
            {
                string sortedFileName = createFileName("RainbowTable", passwordLength, noNumber, true, false, char_policy.at(i), char_policy.at(j), char_policy.at(k));
                ifstream charSortedFile(sortedFileName.c_str(), ios_base::binary);
                finalFile << charSortedFile.rdbuf();
                //cout << "finalFileName " << nbFilesRead << " : " << finalFileName << endl;
                //charSortedFile.open(sortedFileName.c_str(), ios_base::binary);
                /*string s;
                while(getline(charSortedFile, s))
                {
                    finalFile<<s<<endl;
                }*/
                remove(sortedFileName.c_str());
                nbFilesRead++;
            }
        }
    }
}

void rainbow::putAllInFinalTable(unsigned int passwordLength)
{
    string rainbowTable = createFileName("RainbowTable", noNumber, noNumber, false, false, noChar, noChar, noChar);
    cout << "rainbowTable : " << rainbowTable << endl;
    string rainbowTableName = createFileName("RainbowTable", passwordLength, noNumber, true, false, noChar, noChar, noChar);
    cout << "rainbowTableName : " << rainbowTableName << endl;
    ofstream finalFile(rainbowTable.c_str()/*, ios_base::app*/);
    ifstream tempFile(rainbowTableName.c_str());
    finalFile << tempFile.rdbuf();
}

void rainbow::sort()
{
    generate3RainbowTableFiles();
    for (unsigned int i = 6; i < 9; i++)
    {
        createEachCharHashTextFile(i);
        sortEveryCharUnsortedTextFile(i);
        addSortedFilesToCorrespondingRainbowTable(i);
        putAllInFinalTable(i);
    }
}
