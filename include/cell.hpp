#pragma once

template <typename T> class Cell {
  public:
    Cell() { this->next = nullptr; }

  private:
    T item;
    Cell *next;

    friend class LinkedList;
    friend class LinkedQueue;
    friend class Escalonador;
};
