#include "site.hpp"
#include <iostream>

Site::Site(const URL &u) {
    this->host = u.getHost();
    this->urls.insertBeg(u);
}

void Site::setHost(const URL &u) {
    this->host = u.getHost();
    this->urls.insertBeg(u);
}

void Site::printHost() const { std::cout << this->host << '\n'; }

void Site::printUrls() const { this->urls.print(); }
