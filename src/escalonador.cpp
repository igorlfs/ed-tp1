#include "escalonador.hpp"
#include <iostream>

static constexpr int numFM = 6;
static const char *forbiddenMimes[numFM] = {".jpg", ".gif", ".mp3",
                                            ".avi", ".doc", ".pdf"};

bool endsWith(const string &str, const string &end) {
    if (end.length() > str.length())
        return false;
    else {
        unsigned strL = str.length();
        unsigned endL = end.length();
        return (0 == str.compare(strL - endL, endL, end));
    }
}

bool Escalonador::isUrlForbidden(const string &u) {
    for (int i = 0; i < numFM; ++i)
        if (endsWith(u, forbiddenMimes[i])) return true;

    return false;
}

void Escalonador::insertUrl(const URL &u) {
    if (u.getProtocol() != "http") return;
    string urlWithFrag = u.getUrl();
    if (isUrlForbidden(urlWithFrag)) return;

    string urlNoFrag = u.getUrlNoFrag();
    string urlHost = u.getHost();
    if (this->siteQueue.isHostInQueue(urlHost)) {
        this->siteQueue.getUrlsFromHost(urlHost)->insertMid(urlNoFrag);
    } else {
        this->siteQueue.line(urlNoFrag);
    }
}

void Escalonador::escalonaN(const int &n) {
    this->siteQueue.printNUrls(n, this->outputFile);
}

void Escalonador::escalonaTudo() {
    while (!this->siteQueue.empty()) {
        this->siteQueue.getFront()->item.printUrls(this->outputFile);
        this->siteQueue.unline();
    }
}

void Escalonador::escalonaHost(const Host &h, const int &n) {
    // assert 1 <= n <= size
    // se n > size imprima n
    LinkedList *p = this->siteQueue.getUrlsFromHost(h);
    URL u;
    for (int i = 0; i < n; ++i) {
        u = p->removeBeg();
        u.print(this->outputFile);
    }
}

// Pré condição: h é um host da lista (se não for apenas retorno)
void Escalonador::listUrls(const Host &h) {
    if (!this->siteQueue.isHostInQueue(h)) return;
    this->siteQueue.getUrlsFromHost(h)->print(this->outputFile);
}

void Escalonador::listHosts() { this->siteQueue.printHosts(this->outputFile); }

void Escalonador::clearHost(const Host &h) {
    this->siteQueue.getUrlsFromHost(h)->clear();
}

void Escalonador::clearAll() { this->siteQueue.clear(); }

void Escalonador::addUrls(const int &n, std::ifstream &ist) {
    string str;
    for (int i = 0; i < n; ++i) {
        std::getline(ist, str);
        if (str.find("://") != string::npos) insertUrl(str);
    }
}
