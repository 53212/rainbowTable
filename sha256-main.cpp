#include <iostream>
#include <stdlib.h>
#include <memory>
#include "tableGeneration.h"
#include "uncypher.h"
#include <fstream>
#include <thread>

/**
 * This project has been made by Jérôme De Groote (42503) & Léopold Mols (53212)
 */
using namespace std;
using namespace rainbow;

int main(int argc, char *argv[])
{
    //lastLineOfFile();
    //generateSortedRainbowTable();

    //ofstream rainbowTable;
    //rainbowTable = generateTextFile("RainbowTable.txt");


    //may return 0 when not able to detect
    //const auto processor_count = std::thread::hardware_concurrency();
    //cout << processor_count;

    /*for (unsigned int i = 6; i < 9; i++)
    {
        generate3RainbowTableFiles(i);
    }*/

    /*string tName = "t";
    string threadName = "thread";
    for (unsigned int i = 6; i < 9; i++)
    {
        tName += to_string(i);
        threadName += to_string(i);
        thread tName(threadName);
    }*/

    //generate3RainbowTableFiles();

    /*thread t1(thread6);
    thread t2(thread7);
    thread t3(thread8);

    t1.join();
    t2.join();
    t3.join();*/

    for (unsigned int i = 6; i < 9; i++)
    {
        generateSortedRainbowTables(i);
    }

    //generateFinalRainbowTable();

    return 0;
}
