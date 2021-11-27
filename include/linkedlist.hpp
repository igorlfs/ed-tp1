#pragma once

#include "list.hpp"
#include "url.hpp"

class LinkedList : public List {
  public:
    LinkedList();
    ~LinkedList();

    URL getItem(const int &pos) const;
    void setItem(const URL &u, const int &pos);

    void insertBeg(const URL &u);
    void insertEnd(const URL &u);
    void insertPos(const URL &u, const int &pos);

    URL removeBeg();
    URL removeEnd();
    URL removePos(const int &pos);

    // TODO: search,print?

    void clear() override;

  private:
    Cell<URL> *head;
    Cell<URL> *tail;
    Cell<URL> *setPos(const int &pos, const bool &before) const;
};
