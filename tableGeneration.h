#ifndef TABLEGENERATION_H
#define TABLEGENERATION_H
#include "iostream"
#include "stdio.h"
#include "vector"

#ifdef _WIN32
#include <chrono>
#endif

using namespace std;

namespace rainbow
{

    inline int minLength;
    inline int maxLength;

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

    vector<string> generateOneLine(string password);

    void generateAllLines();
}
#endif // TABLEGENERATION_H
