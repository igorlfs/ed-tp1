#pragma once

#include "cell.hpp"
#include "linearlist.hpp"
#include "url.hpp"

class LinkedList : public LinearList {
  public:
    LinkedList();
    ~LinkedList();

    void insertBeg(const URL &u);
    void insertMid(const URL &u);

    URL removeBeg();

    int searchDepth(const int &dep) const;
    bool containsURL(const string &str) const;

    void print(std::ostream &out) const;

    void clear() override;

  private:
    Cell<URL> *head;
    Cell<URL> *tail;

    static constexpr int INVALID_POS = -1;

    Cell<URL> *setPos(const int &pos, const bool &before) const;
    void insertEnd(const URL &u);
    void insertPos(const URL &u, const int &pos);
};
