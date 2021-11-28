#include "linkedqueue.hpp"

LinkedQueue::LinkedQueue() : List() {
    // Lidar com exceção
    this->first = new Cell<Site>;
    this->last = this->first;
}

LinkedQueue::~LinkedQueue() {
    clear();
    delete this->first;
}

void LinkedQueue::line(const URL &u) {
    // Lidar com exceção
    Cell<Site> *newCell  = new Cell<Site>;
    newCell->item.setHost(u);
    this->last->next = newCell;
    this->last = newCell;
    this->size++;
}

Site LinkedQueue::unline() {
    // Lidar com exceção
    // if (this->size == 0)
    // Lidar com exceção
    Cell<Site> *p = this->first;
    Site aux = this->first->item;

    this->first = this->first->next;
    delete p;

    this->size--;
    return aux;
}

bool LinkedQueue::isHostInQueue(const Host &h) const {
    if (empty()) return false;
    Cell<Site> *p = this->first->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return true;
        p = p->next;
    }
    return false;
}

LinkedList *LinkedQueue::getUrlsFromHost(const Host &h) const {
    Cell<Site> *p = this->first->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return p->item.getUrls();
        p = p->next;
    }
    // Não deve chegar aqui
    return this->first->item.getUrls();
}

void LinkedQueue::printHosts() const {
    Cell<Site> *p = this->first->next;
    while (p != nullptr) {
        p->item.printHost();
        p = p->next;
    }
}

void LinkedQueue::clear() {
    for (Cell<Site> *p = this->first->next; p != nullptr;
         p = this->first->next) {
        p->item.urls.clear();
        this->first->next = p->next;
        delete p;
    }
    this->size = 0;
    this->last = this->first;
}
