#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <memory>
#include "sha256.h"
#include "tableGeneration.h"
#include "uncypher.h"
#include "thread"
#include <chrono>

#include <string>

/**
 * This project has been made by Jérôme De Groote (42503) & Léopold Mols (53212)
 */
using namespace std;
using namespace rainbow;

int main(int argc, char *argv[])
{
    //To detect how much cores the CPU has
    //const auto processor_count = std::thread::hardware_concurrency();
    //cout << processor_count;


    // I'll use this when I'll implement a for loop with the differents threads.
    /*string tName = "t";
    string threadName = "thread";
    for (unsigned int i = 6; i < 9; i++)
    {
        tName += to_string(i);
        threadName += to_string(i);
        thread tName(threadName);
    }*/

    //thread t1(rainbow::thread6);
    //thread t2(rainbow::thread7);
    //thread t3(rainbow::thread8);

    //t1.join();
    //t2.join();
    //t3.join();

    // I'll use this when I'll implement a for loop with the differents threads.
    /*for (unsigned int i = 6; i < 9; i++)
    {
        generateSortedRainbowTables(i);
    }*/

    //QTime myTimer;
    //myTimer.start();
    // do something..
    //int nMilliseconds = myTimer.elapsed();

    /*auto start = chrono::high_resolution_clock::now();
    thread t4(rainbow::generateSortedRainbowTableThread6);
    thread t5(rainbow::generateSortedRainbowTableThread7);
    thread t6(rainbow::generateSortedRainbowTableThread8);
    t4.join();
    t5.join();
    t6.join();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Suppression de " << nbLinesToDelete << " à la fois : " << duration.count() << " microsecondes nécessaires à des RT de " << fileSize << " octets" << endl;*/

    //rainbow::generateFinalRainbowTable();

    //rainbow::findAllPsw();

    /*vector<string> test;
    test.push_back("U1fggJ");
    test.push_back("0047bfec28ba699ecfd116d3387e6ede28c8392613f872535243937a2f22222d");
    reduceTable("RainbowTableSorted6.txt", test);*/
    //rename("ResultTable2.txt", "Teeeeest.txt");

    //generate100Hashes();

    auto start = chrono::high_resolution_clock::now();
    sort();
    //createEachCharHashTextFile();
    //sortEveryCharUnsortedTextFile();
    //addSortedFilesToCorrespondingRainbowTable();
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Suppression de " << nbLinesToDelete << " à la fois : " << duration.count() << " microsecondes nécessaires à des RT de " << fileSize << " octets" << endl;
    //generateUnsortedRainbowTablePerFirstChar('0', "RainbowTableTemporaryForRT6UNSORTED0.txt", "RainbowTable6.txt");
    //deleteReadLinesInFile('b', "RainbowTableBIS6.txt", "RainbowTable6.txt");

    return 0;
}
