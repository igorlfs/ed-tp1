#include "linkedqueue.hpp"

LinkedQueue::LinkedQueue() : List() {
    // Lidar com exceção
    this->first = new Cell<LinkedList>;
    this->last = this->first;
}

LinkedQueue::~LinkedQueue() {
    clear();
    delete this->first;
}

void LinkedQueue::line(const LinkedList &L) {
    // Lidar com exceção
    Cell<LinkedList> *newCell = new Cell<LinkedList>;
    newCell->item = L;
    this->last->next = newCell;
    this->last = newCell;
    this->size++;
}

LinkedList LinkedQueue::unline() {
    // Lidar com exceção
    // if (this->size == 0)
    // Lidar com exceção
    Cell<LinkedList> *p = this->first;
    LinkedList aux = this->first->item;

    this->first = this->first->next;
    delete p;

    this->size--;
    return aux;
}

void LinkedQueue::clear() {
    for (Cell<LinkedList> *p = this->first->next; p != nullptr;
         p = this->first->next) {
        this->first->next = p->next;
        delete p;
    }
    this->size = 0;
    this->last = this->first;
}
