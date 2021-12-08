#include "linkedqueue.hpp"
#include "msgassert.hpp"

LinkedQueue::LinkedQueue() : LinearList() {
    this->front = new (std::nothrow) Cell<Site>;
    erroAssert(this->front, "Falha ao alocar dinamicamente a célula."); 
    this->rear = this->front;
}

LinkedQueue::~LinkedQueue() {
    clear();
    delete this->front;
}

void LinkedQueue::line(const URL &u) {
    Cell<Site> *newCell = new (std::nothrow) Cell<Site>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula."); 

    newCell->item.setHost(u);
    this->rear->next = newCell;
    this->rear = newCell;
    this->size++;
}

void LinkedQueue::unline() {
    erroAssert(!empty(), "Falha ao remover item da fila: fila vazia.");

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
    // Não precisamos checar se está vazia,
    // pois verificamos que a fila tem pelo
    // menos um elemento (que tem Host h)

    Cell<Site> *p = this->front->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return p->item.getUrls();
        p = p->next;
    }

    // Não deve chegar aqui, 
    // pois verifircamos que o host está na fila
    // antes de chamar a função
    throw "Erro: Host não está na fila";
}

void LinkedQueue::printNUrls(const int &n, std::ostream &out) {
    if (empty()) return;

    Cell<Site> *p = this->front->next;
    int m = 0;
    URL u;

    while (m < n) {

        LinkedList *q = p->item.getUrls();
        int sizeL = q->getSize();

        for (int i = 0; i < sizeL && m != n; ++i, ++m) {
            u = q->removeBeg();
            u.print(out);
        }

        if (p->next == nullptr) return;

        p = p->next;
    }
}

void LinkedQueue::printHosts(std::ostream &out) const {
    if (empty()) return;

    Cell<Site> *p = this->front->next;

    while (p != nullptr) {
        p->item.printHost(out);
        p = p->next;
    }
}

void LinkedQueue::clear() {
    if (empty()) return;

    for (Cell<Site> *p = this->front->next; p != nullptr;
         p = this->front->next) {
        this->front->next = p->next;
        delete p;
    }

    this->size = 0;
    this->rear = this->front;
}
