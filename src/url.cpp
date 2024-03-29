#include "url.hpp"
#include <iostream>

typedef unsigned long delim;

// @brief contar quantos c existem em str
// @param str, c
// @return número de ocorrências de c em str
unsigned countCharStr(const std::string &str, const char c) {
    unsigned n = 0;
    for (char i : str)
        if (c == i) n++;
    return n;
}

// @brief constrói uma URL com base em uma string
// @param string s (pré condição: s está correta)
// @return URL construída
URL::URL(string s) {
    if (s[s.size() - 1] == '/') s.pop_back();

    // Na hora de inserir, assumimos que "://" está presente
    delim prot = s.find("://");
    this->protocol = s.substr(0, prot);

    // Se "www." sucedeer "://", remova até ele.
    // Se não, apenas exclua até o "://"
    delim www = s.find("www.");
    (www == prot + 3) ? s.erase(0, www + 4) : s.erase(0, prot + 3);

    delim host = s.find('/');
    if (host != string::npos) {
        this->host = s.substr(0, host);
        s.erase(0, host + 1);

        delim path = s.find('?');
        if (path == string::npos) {
            delim frag = s.find('#');
            if (frag == string::npos)
                this->path = s;
            else {
                this->path = s.substr(0, frag);
                s.erase(0, frag + 1);
                this->fragment = s;
            }
        } else {
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
        this->depth = countCharStr(this->path, '/') + 1;
    } else {
        this->host = s;
        this->depth = 0;
    }
}

// @brief imprime a URL na saída out
// @param saída out
void URL::print(std::ostream &out) const {
    out << this->protocol << "://" << this->host;
    if (!this->path.empty()) out << '/' << this->path;
    if (!this->query.empty()) out << '?' << this->query;
    if (!this->fragment.empty()) out << '#' << this->fragment;
    out << '\n';
}

// @brief retorna url completa
string URL::getUrl() const {
    string s = getUrlNoFrag();
    if (!this->fragment.empty()) s += '#' + this->fragment;
    return s;
}

// @brief retorna url, mas sem o fragment
string URL::getUrlNoFrag() const {
    string s = protocol + "://" + host;
    if (!this->path.empty()) s += '/' + this->path;
    if (!this->query.empty()) s += '?' + this->query;
    return s;
}
