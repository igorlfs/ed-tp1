#pragma once

#include "linkedlist.hpp"

typedef std::string Host;

class Site {
  public:
    Site() {}
    Site(const URL &u) {
        this->host = u.getHost();
        this->urls.insertBeg(u);
    }

    Host getHost() const { return this->host; }
    LinkedList *getUrls() { return &this->urls; }

    void setHost(const URL &u) {
        this->host = u.getHost();
        this->urls.insertBeg(u);
    };

    void printHost(std::ostream &out) const { out << this->host << '\n'; }
    void printUrls(std::ostream &out) const { this->urls.print(out); }

  private:
    Host host;
    LinkedList urls;

    friend class LinkedQueue;
};
