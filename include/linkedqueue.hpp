#pragma once

#include "linearlist.hpp"
#include "site.hpp"

class LinkedQueue : public LinearList {
  public:
    // Construtores
    LinkedQueue();
    // Destrutor
    ~LinkedQueue();

    // Getters
    LinkedList *getUrlsFromHost(const Host &h) const;
    LinkedList *getBestHost() const;

    // Modificadores
    void line(const URL &u);
    void escalonaTudo(std::ostream &out);
    void clear() override;

    // Operações
    void escalonaNUrls(const int &n, std::ostream &out) const;
    void printHosts(std::ostream &out) const;

  private:
    Cell<Site> *front;
    Cell<Site> *rear;
};
