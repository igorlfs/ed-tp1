#pragma once

#include "linkedlist.hpp"

typedef std::string Host;

class Site {
  public:
    // Construtores
    // Construtor default para poder usar como célula
    Site() {}
    // @brief inicia o host e insere a URL na 1ª posição da lista
    // @param URL
    Site(const URL &u) {
        this->host = u.getHost();
        this->urls.insertBeg(u);
    }

    // Getters
    Host getHost() const { return this->host; }
    LinkedList *getUrls() { return &this->urls; }

    // Setters
    // @brief inicia o host e insere a URL na 1ª posição da lista
    // @param URL
    void setHost(const URL &u) {
        // Em princípio, eu deveria limpar a lista, mas esse método nunca
        // É usado para sobrepor uma lista antiga
        this->host = u.getHost();
        this->urls.insertBeg(u);
    };

    // Operadores
    // @brief imprime o Host do site na saida out
    // @param out
    void printHost(std::ostream &out) const { out << this->host << '\n'; }
    // @brief imprime as URLs do site na saída out, em ordem
    // @param out
    void printUrls(std::ostream &out) const { this->urls.print(out); }

  private:
    Host host;
    LinkedList urls;

    friend class LinkedQueue;
};
