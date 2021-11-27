#pragma once

#include "cell.hpp"

class List {
  public:
    List() { this->size = 0; }

    // @brief retorna o tamanho da fila
    // @return tamanho da fila
    int getSize() const { return this->size; };

    // @brief determina se a fila está vazia
    // @return true se vazia; false caso contrário
    bool empty() const { return (this->size == 0); }

    virtual void clear() = 0;

  protected:
    int size;
};
