#pragma once

#include "list.hpp"
#include "site.hpp"

class LinkedQueue : public List {
  public:
    LinkedQueue();
    ~LinkedQueue();

    Cell<Site> *getFront() { return this->front->next; }

    void line(const URL &u);
    void unline();

    bool isHostInQueue(const Host &h) const;
    LinkedList *getUrlsFromHost(const Host &h) const;

    void printHosts() const;

    void clear() override;

  private:
    Cell<Site> *front;
    Cell<Site> *rear;

    friend class Escalonador;
};
