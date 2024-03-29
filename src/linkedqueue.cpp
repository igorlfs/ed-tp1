#include "linkedqueue.hpp"
#include "msgassert.hpp"

// @brief constrói fila inicializando cabeça e cauda
LinkedQueue::LinkedQueue() : LinearList() {
    this->front = new (std::nothrow) Cell<Site>;
    erroAssert(this->front, "Falha ao alocar dinamicamente a célula."); 
    this->rear = this->front;
}

// @brief destrói fila liberando células e cabeça
LinkedQueue::~LinkedQueue() {
    clear();
    delete this->front;
}

// @brief enfileira Site na fila
// @param u (URL do Site)
void LinkedQueue::line(const URL &u) {
    Cell<Site> *newCell = new (std::nothrow) Cell<Site>;
    erroAssert(newCell, "Falha ao alocar dinamicamente a célula."); 

    newCell->item.setHost(u);
    this->rear->next = newCell;
    this->rear = newCell;
    this->size++;
}

// @brief escalona toda a fila, Site por Site
// @param out (saída do escalonamento)
void LinkedQueue::escalonaTudo(std::ostream &out) {
    Cell<Site> *p = this->front->next;

    for (; p != nullptr; p = p->next)
        p->item.getUrls()->escalonaTudo(out);
}

// @brief checa se um dado host está na fila
// @param h (Host)
// @return lista de URLs se presente, nullptr caso contrário
LinkedList *LinkedQueue::getUrlsFromHost(const Host &h) const {

    Cell<Site> *p = this->front->next;

    while (p != nullptr) {
        if (p->item.getHost() == h) return p->item.getUrls();
        p = p->next;
    }

    return nullptr;
}

// @brief desaloca células da fila, faz cauda=cabeça, coloca tamanho 0
void LinkedQueue::clear() {
    Cell<Site> *p = this->front->next;

    for (; p != nullptr; p = this->front->next) {
        this->front->next = p->next;
        delete p;
    }

    this->size = 0;
    this->rear = this->front;
}

// @brief imprime na saída out, no máximo, n URLs que estão nas listas da fila
// @param n (quantidade de URLs), out (saída)
void LinkedQueue::escalonaNUrls(const int &n, std::ostream &out) const {
    if (empty()) return;

    Cell<Site> *p = this->front->next;
    int m = 0;

    while (m < n) {

        LinkedList *q = p->item.getUrls();
        int sizeL = q->getSize();

        for (int i = 0; i < sizeL; ++i, ++m) {
            q->removeBeg().print(out);
            if (m == n) return;
        }

        if (p->next == nullptr) return;

        p = p->next;
    }
}

// @brief imprime hosts da fila na saída out
// @param out
void LinkedQueue::printHosts(std::ostream &out) const {
    Cell<Site> *p = this->front->next;

    while (p != nullptr) {
        p->item.printHost(out);
        p = p->next;
    }
}
