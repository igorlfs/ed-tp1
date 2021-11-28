#include "escalonador.hpp"

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
    for (int i = 0; i < 6; ++i)
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
        this->siteQueue.insertUrlInSite(urlHost, urlNoFrag);
    } else {
        this->siteQueue.line(urlNoFrag);
    }
}

// Pré condição: h é um host da lista (se não for apenas retorno)
void Escalonador::listUrls(const Host &h) const {
    if (!this->siteQueue.isHostInQueue(h)) return;
    this->siteQueue.getUrlsFromHost(h)->print();
}

void Escalonador::listHosts() const { this->siteQueue.printHosts(); }

void Escalonador::clearAll() { this->siteQueue.clear(); }
