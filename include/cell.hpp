#pragma once

#include "url.hpp"

class Celula {
  public:
    // @brief inicia célula
    // @return célula
    Celula() { this->prox = nullptr; };

  private:
    URL url;
    Celula *prox;
};
