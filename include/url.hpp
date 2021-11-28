#pragma once

#include <string>

using std::string;

class URL {
  public:
    URL() {}
    URL(string s);

    string getProtocol() const { return this->protocol; }
    string getHost() const { return this->host; }
    int getDepth() const { return this->depth; }
    string getUrl() const;
    string getUrlNoFrag() const;

    void print() const;

  private:
    string protocol;
    string host;
    string path;
    string query;
    string fragment;
    unsigned depth;
};
