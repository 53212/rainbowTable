#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "sha256.h"
#include "tableGeneration.h"

using namespace std;
using namespace rainbow;

vector<string> tableGeneration::generateOneLine(string password)
{
    vector<string> line;
    line.push_back(password);
    line.push_back(",");
    string hash = sha256(password);
    line.push_back(hash);
    string hashReduction = reduce(hash);
    line.push_back(",");
    line.push_back(hashReduction);
    for (unsigned i = 0;i < 20; i++)
    {
        hash = sha256(hash);
        line.push_back(",");
        hashReduction = reduce2(hash/*, 62*/);
        line.push_back(hash);
        line.push_back(",");
        line.push_back(hashReduction);
    }
    return line;
}

void tableGeneration::generateFile()
{
    FILE* fichier = NULL;
    /*char actualpath[PATH_MAX + 1];
    char *ptr = malloc(256 * sizeof(char));

    char *absolute_path = src;
    ptr = realpath(absolute_path, actualpath);*/
    fichier = fopen("/mon_chemin_d'acces/test.txt", "w");
}
