#include "linkedlist.hpp"
#include "msgassert.hpp"

// @brief Constrói lista inicializando cabeça e cauda
LinkedList::LinkedList() : LinearList() {
    this->head = new (std::nothrow) Cell<URL>;
    erroAssert(this->head, "Falha ao alocar dinamicamente a célula.");
    this->tail = this->head;
}

// @brief Destrói lista liberando células e cabeça
LinkedList::~LinkedList() {
    clear();
    delete this->head;
}

// @brief Retorna a célula (antes) na posição pos
// @param pos, before (se quero a posição antes, assume-se falso)
Cell<URL> *LinkedList::setPos(const int &pos,
                              const bool &before = false) const {
    erroAssert(pos <= this->size + 1 && pos >= 1,
               "Posição de lista ligada inesperada. " << pos);

    Cell<URL> *p = this->head;
    for (int i = 1; i < pos; ++i)
        p = p->next;

    if (!before) p = p->next;

    return p;
}

// @brief insere uma nova célula no começo da lista
// @param u, URL a ser inserida
void LinkedList::insertBeg(const URL &u) {
    Cell<URL> *newCell = new (std::nothrow) Cell<URL>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula.");

    newCell->item = u;
    newCell->next = this->head->next;
    this->head->next = newCell;
    this->tail = newCell;
    this->size++;
}

// @brief insere uma nova célula numa dada posição da lista
// @param u, URL a ser inserida, pos, posição de inserção
void LinkedList::insertPos(const URL &u, const int &pos) {
    Cell<URL> *newCell = new (std::nothrow) Cell<URL>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula.");

    Cell<URL> *p = setPos(pos, true);

    newCell->item = u;
    newCell->next = p->next;
    p->next = newCell;
    this->size++;

    if (newCell->next == nullptr) this->tail = newCell;
}

// @brief remove a célula no começo da lista
// @return URL removida
URL LinkedList::removeBeg() {
    erroAssert(!empty(), "Falha ao remover item da lista: lista vazia");

    Cell<URL> *p = this->head->next;
    this->head->next = p->next;
    this->size--;

    if (this->head->next == nullptr) this->tail = this->head;

    URL aux = p->item;
    delete p;

    return aux;
}

// @brief desaloca células da lista, faz cauda=cabeça, coloca tamanho 0
void LinkedList::clear() {
    Cell<URL> *p = this->head->next;

    while (p != nullptr) {
        this->head->next = p->next;
        delete p;
        p = this->head->next;
    }

    this->tail = this->head;
    this->size = 0;
}

// @brief remove n células do começo, as imprimindo na saída out
// @param out (saída), n
void LinkedList::escalona(std::ostream &out, const int &n) {
    for (int i = 0; i < n; ++i)
        removeBeg().print(out);
}

// @brief remove todas as células da lista (em ordem),
// as imprimindo na saída out
// @param out (saída)
void LinkedList::escalonaTudo(std::ostream &out) {
    while (!empty())
        removeBeg().print(out);
}

// @brief verifica se a lista contém a URL
// @param str, URL procurada
// @return true se URL está na lista e false caso contraŕio
bool LinkedList::containsURL(const string &str) const {
    Cell<URL> *p = this->head->next;

    while (p != nullptr) {
        if (p->item.getUrl() == str) return true;
        p = p->next;
    }

    return false;
}

// @brief encontra a posição da primeira URL da lista cuja
// profundidade é maior que a dada
// @param dep
// @return posição em questão ou final da lista
int LinkedList::searchDepth(const int &dep) const {
    Cell<URL> *p = this->head->next;
    int aux = 1;

    while (p != nullptr) {
        if (p->item.getDepth() > dep) return aux;
        aux++;
        p = p->next;
    }

    return aux;
}

// @brief imprime a lista na saída out
// @param out
void LinkedList::print(std::ostream &out) const {
    Cell<URL> *p = this->head->next;

    while (p != nullptr) {
        p->item.print(out);
        p = p->next;
    }
}
