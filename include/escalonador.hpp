#pragma once

#include "linkedqueue.hpp"
#include <fstream>

class Escalonador {
  public:
    Escalonador(const string &outFile) { this->outputFile.open(outFile); }
    ~Escalonador() { this->outputFile.close(); }

    void insertUrl(const URL &u);
    void escalonaTudo();
    void escalonaN(const int &n);
    void escalonaHost(const Host &h, const int &n);
    void listUrls(const Host &h);
    void listHosts();
    void clearHost(const Host &h);
    void clearAll();

    void addUrls(const int &n, std::ifstream &ist);

  private:
    std::ofstream outputFile;
    LinkedQueue siteQueue;
    bool isUrlForbidden(const string &u);
};
