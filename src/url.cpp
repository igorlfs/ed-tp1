#include "url.hpp"
#include <iostream>

typedef unsigned long delim;

// @brief constrói uma URL com base em uma string
// @param string s
// @return URL construída
URL::URL(string &s) {
    if (s[s.size() - 1] == '/') s.pop_back();

    delim prot = s.find("://");
    this->protocol = s.substr(0, prot);

    // Encontre o primeiro ponto (e remova até ele).
    // Assim, vamos exluir o 'www' (e afins)
    delim dot = s.find('.');
    s.erase(0, dot + 1);

    delim host = s.find('/');
    if (host != string::npos) {
        this->host = s.substr(0, host);
        s.erase(0, host + 1);

        // Estou considerando que não é possível ter fragment sem query
        delim path = s.find('?');
        if (path == string::npos)
            this->path = s;
        else {
            this->path = s.substr(0, path);
            s.erase(0, path + 1);
            delim quer = s.find('#');
            if (quer == string::npos)
                this->query = s;
            else {
                this->query = s.substr(0, quer);
                s.erase(0, quer + 1);
                this->fragment = s;
            }
        }
    } else
        this->host = s;
}

// @brief imprime a URL na saída padrão
// @return URL impressa na saída padrão
void URL::print() const {
    std::cout << this->protocol << "://" << this->host;
    if (!this->path.empty()) std::cout << '/' << this->path;
    if (!this->query.empty()) std::cout << '?' << this->query;
    if (!this->fragment.empty()) std::cout << '#' << this->fragment;
    std::cout << '\n';
}
