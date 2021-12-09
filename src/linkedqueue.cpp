#include "linkedqueue.hpp"
#include "msgassert.hpp"
#include <cassert>

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

// @brief retorna a lista de URLs de um dado Host
// @param h (Host)
LinkedList *LinkedQueue::getUrlsFromHost(const Host &h) const {
    // Não precisamos checar se está vazia,
    // pois verificamos que a fila tem pelo
    // menos um elemento (que tem Host h)
    assert(!empty());

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
    if (empty()) return;

    Cell<Site> *p = this->front->next;
    for (int i = 0; i < getSize(); ++i, p = p->next) {
        p->item.getUrls()->escalonaTudo(out);
    }
}

// @brief checa se um dado host está na fila
// @param h (Host)
// @return true se está presente, false caso contrário
bool LinkedQueue::isHostInQueue(const Host &h) const {
    if (empty()) return false;

    Cell<Site> *p = this->front->next;
    while (p != nullptr) {
        if (p->item.getHost() == h) return true;
        p = p->next;
    }

    return false;
}

// @brief desaloca células da fila, faz cauda=cabeça, coloca tamanho 0
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

// @brief imprime na saída out, no máximo,
// n URLs que estão nas listas da fila
// @param n (quantidade de URLs), out (saída)
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

// @brief imprime hosts da fila na saída out
// @param out
void LinkedQueue::printHosts(std::ostream &out) const {
    if (empty()) return;

    Cell<Site> *p = this->front->next;

    while (p != nullptr) {
        p->item.printHost(out);
        p = p->next;
    }
}
