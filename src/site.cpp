#include "site.hpp"

Site::Site(const URL &u) {
    this->host = u.getHost();
    this->urls.insertBeg(u);
}

void Site::setHost(const URL &u) {
    this->host = u.getHost();
    this->urls.insertBeg(u);
}

void Site::printHost(std::ostream &out) const { out << this->host << '\n'; }

void Site::printUrls(std::ostream &out) const { this->urls.print(out); }
