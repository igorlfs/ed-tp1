#pragma once

#include <ostream>
#include <string>

using std::string;

class URL {
  public:
    // Construtores
    // Construtor default para poder usar como célula
    URL() {}
    URL(string s);

    // Getters
    string getProtocol() const { return this->protocol; }
    string getHost() const { return this->host; }
    int getDepth() const { return this->depth; }
    string getUrl() const;
    string getUrlNoFrag() const;

    // Operações
    void print(std::ostream &out) const;

  private:
    string protocol;
    string host;
    string path;
    string query;
    string fragment;
    unsigned depth;
};
