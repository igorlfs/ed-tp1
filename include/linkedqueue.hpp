#pragma once

#include "list.hpp"
#include "site.hpp"

class LinkedQueue : public List {
  public:
    LinkedQueue();
    ~LinkedQueue();

    void line(const URL &u);
    Site unline();

    bool isHostInQueue(const Host &h) const;
    LinkedList *getUrlsFromHost(const Host &h) const;

    void printHosts() const;

    void clear() override;

  private:
    Cell<Site> *first;
    Cell<Site> *last;

    friend class Escalonador;
};
