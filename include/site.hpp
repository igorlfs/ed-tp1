#pragma once

#include "linkedlist.hpp"

typedef std::string Host;

class Site {
  public:
    Site() {}
    Site(const URL &u);

    Host getHost() const { return this->host; }
    LinkedList *getUrls() { return &this->urls; }

    void setHost(const URL &u);

    void printHost(std::ostream &out) const;
    void printUrls(std::ostream &out) const;

  private:
    Host host;
    LinkedList urls;

    friend class LinkedQueue;
};
