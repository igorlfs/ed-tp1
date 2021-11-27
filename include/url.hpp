#pragma once

#include <string>

using std::string;

class URL {
  public:
    // @brief construtor padrão
    // @return URL construída
    URL() = default;
    URL(string &s);
    void print() const;

  private:
    string protocol;
    string host;
    string path;
    string query;
    string fragment;
};
