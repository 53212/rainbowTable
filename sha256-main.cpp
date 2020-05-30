#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <memory>
#include "sha256.h"
#include "tableGeneration.h"
#include "uncypher.h"
#include <vector>
#include <thread>
#include <chrono>
#include <math.h>

/**
 * This project has been made by Jérôme De Groote (42503) & Léopold Mols (53212)
 */
using namespace std;
using namespace rainbow;

int main(int argc, char *argv[])
{
    time_t start, end;
    time(&start);

    //auto startProgram = chrono::high_resolution_clock::now();

    /*vector<thread> threads;
    for (unsigned int i = 0; i < 3; i++)
    {
        //thread t = thread(displayThread, bools);
        threads.push_back(thread(displayThread, i));
    }
    for_each(threads.begin(), threads.end(), [](thread &t)
    {
        t.join();
    });
    for (unsigned int i = 0; i < bools.size(); i++)
    {
        cout << "bools at i: " << bools.at(i) << endl;
    }*/

    //To detect how much cores the CPU has
    //const auto processor_count = std::thread::hardware_concurrency();
    //cout << processor_count;

    /*while (count > 0)
    {
      vector<thread *> threads(min(CORES, count));
      for (size_t i = 0; i < threads.size(); ++i)
      { // Start appropriate number of threads
        threads[i] = new thread(thread6, i);
      }
      for (size_t i = 0; i < threads.size(); ++i)
      { // Wait for all threads to finish
        threads[i]->join();
        delete threads[i];
        --count;
      }
    }*/
    //thread t1(rainbow::generatePasswordLengthDifferentRainbowTable, 6);
    //thread t2(rainbow::generatePasswordLengthDifferentRainbowTable, 7);
    //thread t3(rainbow::generatePasswordLengthDifferentRainbowTable, 8);

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




    /*vector<string> test;
    test.push_back("U1fggJ");
    test.push_back("0047bfec28ba699ecfd116d3387e6ede28c8392613f872535243937a2f22222d");
    reduceTable("RainbowTableSorted6.txt", test);*/
    //rename("ResultTable2.txt", "Teeeeest.txt");

    //generate100Hashes();




    //findAllPasswords();

    generateRainbowTable();
    //createEachCharHashTextFile();
    //sortEveryCharUnsortedTextFile();
    //addSortedFilesToCorrespondingRainbowTable();

    time(&end);
    double time_taken = double(end - start);
    if ((int)time_taken % 60 == 0)
    {
        cout << "Time taken by program is : " << fixed << time_taken << setprecision(150) << " sec " << endl;
    }
    cout << "TOTAL Time taken by program is : " << fixed << time_taken << setprecision(150);
    cout << " sec " << endl;
    //auto stopProgram = chrono::high_resolution_clock::now();

    //auto durationProgram = chrono::duration_cast<chrono::microseconds>(stopProgram - startProgram);

    //cout << "Suppression de " << nbLinesToDelete << " à la fois : " << durationProgram.count() << " microsecondes nécessaires à des RT de " << fileSize << " octets" << endl;
    //generateUnsortedRainbowTablePerFirstChar('0', "RainbowTableTemporaryForRT6UNSORTED0.txt", "RainbowTable6.txt");
    //deleteReadLinesInFile('b', "RainbowTableBIS6.txt", "RainbowTable6.txt");

    return 0;
}
