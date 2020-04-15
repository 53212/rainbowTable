#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <memory>
#include "sha256.h"
#include "tableGeneration.h"
//#include "passwd-utils.hpp"

/*using std::string;
using std::cout;
using std::endl;
using std::ofstream;*/
using namespace std;
using namespace rainbow;

int main(int argc, char *argv[])
{
    generateAllLines();
    /*int passwordRandomLength = randomBetweenMinAndMax(6, 9);
    string input = "azerty";//generate_passwd(passwordRandomLength);
    string output1 = sha256(input);
    generateOneLine(input);
    cout << "sha256('"<< input << "'):" << output1 << endl;
    */

    /*for (unsigned i = 0; i < line.size(); i++)
    {
        cout << line.at(i) << endl;
    }*/
    //c_str output1Adress = &output1;
    //string * output1Adress = std::addressof(output1);
    //cout << &output1 << endl;
    //cout << output1 << endl;

    /*
    string output2 = reduce2(output1, 1, input.length());
    cout << endl << output2 << endl;
    */

    //writeInFile(output2);
    return 0;
}
