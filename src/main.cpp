#include "escalonador.hpp"
#include <iostream>
#include <sstream>

static const unsigned NUM_COM = 8;
static const string COMMANDS[NUM_COM] = {
    "ADD_URLS", "ESCALONA_TUDO", "ESCALONA",   "ESCALONA_HOST",
    "VER_HOST", "LISTA_HOSTS",   "LIMPA_HOST", "LIMPA_TUDO"};

int main(int argc, char *argv[]) {
    if (argc == 1) abort();
    Escalonador E("out");
    std::ifstream inputFile;
    inputFile.open(argv[1]);
    string line;
    int x;
    do {
        std::getline(inputFile, line);
        std::stringstream ss(line);
        if (line.find(COMMANDS[0]) != string::npos) {
            string str;
            ss >> str >> x;
            E.addUrls(x, inputFile);
        } else if (line.find(COMMANDS[1]) != string::npos) {
            E.escalonaTudo();
        } else if (line.find(COMMANDS[3]) != string::npos) {
            Host h;
            string str;
            ss >> str >> h >> x;
            E.escalonaHost(h, x);
        } else if (line.find(COMMANDS[2]) != string::npos) {
            string str;
            ss >> str >> x;
            E.escalonaN(x);
        } else if (line.find(COMMANDS[4]) != string::npos) {
            Host h;
            string str;
            ss >> str >> h;
            E.listUrls(h);
        } else if (line.find(COMMANDS[5]) != string::npos) {
            E.listHosts();
        } else if (line.find(COMMANDS[6]) != string::npos) {
            Host h;
            string str;
            ss >> str >> h;
            E.clearHost(str);
        } else if (line.find(COMMANDS[7]) != string::npos)
            E.clearAll();

        if (inputFile.eof()) break;
    } while (true);
    inputFile.close();
    return 0;
}
