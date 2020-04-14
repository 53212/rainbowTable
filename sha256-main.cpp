#include <iostream>
#include "sha256.h"
#include "tableGeneration.h"
 
using std::string;
using std::cout;
using std::endl;
using namespace rainbow;
 
int main(int argc, char *argv[])
{
    string input = "leopold";
    string output1 = sha256(input);
    vector<string> line = tableGeneration::generateOneLine(input);
    cout << "sha256('"<< input << "'):" << output1 << endl;
    for (unsigned i = 0; i < sizeof (line); i++)
    {
        cout << line.at(i) << endl;
    }
    return 0;
}
