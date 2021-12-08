#include "linkedlist.hpp"
#include "msgassert.hpp"

LinkedList::LinkedList() : LinearList() {
    this->head = new (std::nothrow) Cell<URL>;
    erroAssert(this->head, "Falha ao alocar dinamicamente a célula.");
    this->tail = this->head;
}

LinkedList::~LinkedList() {
    clear();
    delete this->head;
}

Cell<URL> *LinkedList::setPos(const int &pos,
                              const bool &before = false) const {
    erroAssert(pos <= this->size && pos >= 1,
               "Posição de lista ligada inesperada.");

    Cell<URL> *p = this->head;
    for (int i = 1; i < pos; ++i)
        p = p->next;

    if (!before) p = p->next;

    return p;
}

void LinkedList::insertBeg(const URL &u) {
    Cell<URL> *newCell = new (std::nothrow) Cell<URL>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula.");

    newCell->item = u;
    newCell->next = this->head->next;
    this->head->next = newCell;
    this->tail = newCell;
    this->size++;
}

void LinkedList::insertMid(const URL &u) {
    int depth = u.getDepth();
    int pos = searchDepth(depth);

    if (pos == INVALID_POS)
        insertEnd(u);
    else if (!containsURL(u.getUrl()))
        insertPos(u, pos + 1);
}

void LinkedList::insertEnd(const URL &u) {
    Cell<URL> *newCell = new (std::nothrow) Cell<URL>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula.");

    newCell->item = u;
    this->tail->next = newCell;
    this->tail = newCell;
    this->size++;
}

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

int LinkedList::searchDepth(const int &dep) const {
    // Só chamo searchDepth se não for a primeira inserção
    // Então o tamanho nunca é nulo

    Cell<URL> *p = this->head->next;
    int aux = 0;

    while (p != nullptr) {
        if (p->item.getDepth() > dep) return aux;
        aux++;
        p = p->next;
    }

    return INVALID_POS;
}

bool LinkedList::containsURL(const string &str) const {
    if (empty()) return false;

    Cell<URL> *p = this->head->next;
    while (p != nullptr) {
        if (p->item.getUrl() == str) return true;
        p = p->next;
    }

    return false;
}

void LinkedList::print(std::ostream &out) const {
    if (empty()) return;

    Cell<URL> *p = this->head->next;
    while (p != nullptr) {
        p->item.print(out);
        p = p->next;
    }
}

void LinkedList::escalona(std::ostream &out, const int &n) {
    for (int i = 0; i < n; ++i) {
        removeBeg().print(out);
    }
}

void LinkedList::escalonaTudo(std::ostream &out) {
    while (!empty()) {
        removeBeg().print(out);
    }
}

void LinkedList::clear() {
    if (empty()) return;

    Cell<URL> *p = this->head->next;
    while (p != nullptr) {
        this->head->next = p->next;
        delete p;
        p = this->head->next;
    }

    this->tail = this->head;
    this->size = 0;
}
