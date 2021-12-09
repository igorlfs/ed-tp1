#pragma once

#include "cell.hpp"
#include "linearlist.hpp"
#include "url.hpp"

class LinkedList : public LinearList {
  public:
    // Construtores
    LinkedList();
    // Destrutor
    ~LinkedList();

    // Modificadores
    void insertBeg(const URL &u);
    void insertMid(const URL &u);
    URL removeBeg();
    void clear() override;
    void escalona(std::ostream &out, const int &n);
    void escalonaTudo(std::ostream &out);

    // Lookup
    bool containsURL(const string &str) const;

    // Operações
    int searchDepth(const int &dep) const;
    void print(std::ostream &out) const;

  private:
    Cell<URL> *head;
    Cell<URL> *tail;

    Cell<URL> *setPos(const int &pos, const bool &before) const;
    void insertEnd(const URL &u);
    void insertPos(const URL &u, const int &pos);
};
