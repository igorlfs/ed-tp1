#pragma once

#include "linkedlist.hpp"
#include "list.hpp"

class LinkedQueue : public List {
  public:
    LinkedQueue();
    ~LinkedQueue();

    void line(const LinkedList &L);
    LinkedList unline();
    void clear() override;

  private:
    Cell<LinkedList> *first;
    Cell<LinkedList> *last;
};
