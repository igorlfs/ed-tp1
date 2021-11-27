#pragma once

#include "url.hpp"

template <typename T> class Cell {
  public:
    // @brief inicia célula
    // @return célula
    Cell() { this->prox = nullptr; };

  private:
    T item;
    Cell *next;

    friend class LinkedList;
    friend class LinkedQueue;
};
