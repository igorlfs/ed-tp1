#include "linkedlist.hpp"

LinkedList::LinkedList() : List() {
    this->head = nullptr;
    this->tail = this->head;
}

LinkedList::~LinkedList() {
    clear();
    delete this->head;
}

Cell<URL> *LinkedList::setPos(const int &pos,
                              const bool &before = false) const {
    // Lidar com exceção:
    // if (pos > this->size || pos <= 0)

    Cell<URL> *p = this->head;
    for (int i = 0; i < pos; ++i)
        p = p->next;

    if (!before) p = p->next;

    return p;
}

URL LinkedList::getItem(const int &pos) const {
    Cell<URL> *p = setPos(pos);
    return p->item;
}

void LinkedList::setItem(const URL &u, const int &pos) {
    Cell<URL> *p = setPos(pos);
    p->item = u;
}

void LinkedList::insertBeg(const URL &u) {
    // Lidar com exceção
    Cell<URL> *newCell = new Cell<URL>;
    newCell->item = u;
    newCell->next = this->head->next;
    this->head->next = newCell;
    this->size++;

    if (newCell->next == nullptr) this->tail = newCell;
}

void LinkedList::insertEnd(const URL &u) {
    // Lidar com exceção
    Cell<URL> *newCell = new Cell<URL>;
    newCell->item = u;
    this->tail->next = newCell;
    this->tail = newCell;
    this->size++;
}

void LinkedList::insertPos(const URL &u, const int &pos) {
    // Lidar com exceção
    Cell<URL> *newCell = new Cell<URL>;
    Cell<URL> *p = setPos(pos, true);
    newCell->item = u;
    newCell->next = p->next;
    p->next = newCell;
    this->size++;

    if (newCell->next == nullptr) this->tail = newCell;
}

URL LinkedList::removeBeg() {
    // Lidar com exceção:
    // if (this->size == 0)

    Cell<URL> *p = this->head->next;
    this->head->next = p->next;
    this->size--;

    if (this->head->next == nullptr) this->tail = this->head;

    URL aux = p->item;
    delete p;

    return aux;
}

URL LinkedList::removeEnd() {
    // Lidar com exceção:
    // if (this->size == 0)

    Cell<URL> *p = setPos(this->size, true);
    p->next = nullptr;
    this->size--;

    URL aux = this->tail->item;
    delete this->tail;
    this->tail = p;

    return aux;
}

URL LinkedList::removePos(const int &pos) {
    // Lidar com exceção:
    // if (this->size == 0)

    Cell<URL> *p = setPos(pos, true);
    Cell<URL> *q = p->next;
    p->next = q->next;
    this->size--;

    URL aux = q->item;
    delete q;

    if (p->next == nullptr) this->tail = p;

    return aux;
}

void LinkedList::clear() {
    for (Cell<URL> *p = this->head->next; p != nullptr; p = p->next) {
        this->head->next = p->next;
        delete p;
    }
    this->tail = this->head;
    this->size = 0;
}
