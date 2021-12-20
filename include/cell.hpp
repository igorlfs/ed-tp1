#pragma once

template <typename T> class Cell {
  public:
    // Construtores
    Cell(const int &id) {
        this->next = nullptr;
        this->id = id;
    }

  private:
    T item;
    Cell *next;
    int id;

    friend class LinkedList;
    friend class LinkedQueue;
};
