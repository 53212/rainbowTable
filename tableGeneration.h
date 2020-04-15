#ifndef TABLEGENERATION_H
#define TABLEGENERATION_H
#include "iostream"
#include "stdio.h"
#include "vector"

#ifdef _WIN32
#include <chrono>
#endif

using namespace std;

//namespace rainbow
//{
    class tableGeneration
    {

        private :

            vector<string> lines_;

        public :

            inline vector<string> getLine() const
            {
                return lines_;
            }
    };

    int randomBetweenMinAndMax(int a, int b);

    void generateOneLine(string password);

    //ofstream generateFile();

    void writeInFile(/*ofstream rainbowTable,*/ vector<string> textToPutIn);
//}
#endif // TABLEGENERATION_H
