#pragma once

#include "linkedlist.hpp"

typedef std::string Host;

class Site {
  public:
    Site(){};
    Site(const URL &u);

    Host getHost() const { return this->host; }
    LinkedList *getUrls() { return &this->urls; }

    void setHost(const URL &u);
    void printHost() const;

  private:
    Host host;
    LinkedList urls;

    friend class LinkedQueue;
};
