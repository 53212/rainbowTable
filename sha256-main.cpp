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

    //generate100Hashes();




    //findAllPasswords();

    generateRainbowTable();

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

    return 0;
}
