#pragma once

#include "linkedqueue.hpp"
#include <fstream>

class Escalonador {
  public:
    Escalonador(const string &outFile);
    ~Escalonador();

    void insertUrl(const URL &u);
    void escalonaTudo();
    void escalonaN(const int &n);
    void escalonaHost(const Host &h, int &n);
    void listUrls(const Host &h);
    void clearHost(const Host &h);
    void listHosts();
    void clearAll();

    void addUrls(const int &n, std::ifstream &ist);

    void readFile(std::ifstream &inputFile);

  private:
    std::ofstream outputFile;
    LinkedQueue siteQueue;

    bool isUrlForbidden(const string &u);
};
