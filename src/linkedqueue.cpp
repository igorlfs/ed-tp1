#include "linkedqueue.hpp"

LinkedQueue::LinkedQueue() : List() {
    // Lidar com exceção
    this->front = new Cell<Site>;
    this->rear = this->front;
}

LinkedQueue::~LinkedQueue() {
    clear();
    delete this->front;
}

void LinkedQueue::line(const URL &u) {
    // Lidar com exceção
    Cell<Site> *newCell = new Cell<Site>;
    newCell->item.setHost(u);
    this->rear->next = newCell;
    this->rear = newCell;
    this->size++;
}

void LinkedQueue::unline() {
    // Lidar com exceção
    // if (this->size == 0)
    // Lidar com exceção
    Cell<Site> *p = this->front;
    this->front = this->front->next;
    if (this->front == nullptr) this->rear = this->front;
    delete p;

    this->size--;
}

bool LinkedQueue::isHostInQueue(const Host &h) const {
    if (empty()) return false;
    Cell<Site> *p = this->front->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return true;
        p = p->next;
    }
    return false;
}

LinkedList *LinkedQueue::getUrlsFromHost(const Host &h) const {
    Cell<Site> *p = this->front->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return p->item.getUrls();
        p = p->next;
    }
    // Não deve chegar aqui
    return this->front->item.getUrls();
}

void LinkedQueue::printHosts() const {
    Cell<Site> *p = this->front->next;
    while (p != nullptr) {
        p->item.printHost();
        p = p->next;
    }
}

void LinkedQueue::clear() {
    for (Cell<Site> *p = this->front->next; p != nullptr;
         p = this->front->next) {
        this->front->next = p->next;
        delete p;
    }
    this->size = 0;
    this->rear = this->front;
}
