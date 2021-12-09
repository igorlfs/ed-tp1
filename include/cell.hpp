#pragma once

template <typename T> class Cell {
  public:
    // Construtores
    Cell() { this->next = nullptr; }

  private:
    T item;
    Cell *next;

    friend class LinkedList;
    friend class LinkedQueue;
};
