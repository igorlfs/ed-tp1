#pragma once

#include "linearlist.hpp"
#include "site.hpp"

class LinkedQueue : public LinearList {
  public:
    LinkedQueue();
    ~LinkedQueue();

    Cell<Site> *getFront() { return this->front->next; }

    void line(const URL &u);
    void unline();

    bool isHostInQueue(const Host &h) const;
    LinkedList *getUrlsFromHost(const Host &h) const;

    void printNUrls(const int &n, std::ostream &out);
    void printHosts(std::ostream &out) const;

    void clear() override;

  private:
    Cell<Site> *front;
    Cell<Site> *rear;

    friend class Escalonador;
};
