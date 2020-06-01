#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <memory>
#include "uncypher.h"

/**
 * This project has been made by Jérôme De Groote (42503) & Léopold Mols (53212)
 */
using namespace std;
using namespace rainbow;

int main(int argc, char *argv[])
{
    cout << "La recherche a commencé !" << endl;
    time_t start, end;
    time(&start);

    //generate100Hashes();

    findAllPasswords();

    time(&end);
    double time_taken = double(end - start);
    cout << "TOTAL Time taken by program is : " << fixed << time_taken << setprecision(50);
    cout << " sec " << endl;

    return 0;
}
