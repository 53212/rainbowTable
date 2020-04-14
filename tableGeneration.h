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
    class tableGeneration
    {

        private :

            string password_;
            vector<string> lines_;

        public :

            static vector<string> generateOneLine(string password);

            void generateFile();

            inline vector<string> getLine() const
            {
                return lines_;
            }
    };
}
#endif // TABLEGENERATION_H
