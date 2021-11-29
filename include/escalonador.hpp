#pragma once

#include "linkedqueue.hpp"

class Escalonador {
  public:
    void insertUrl(const URL &u);
    void escalonaTudo();
    void escalonaN(const int &n);
    void escalonaHost(const Host &h, const int &n);
    void listUrls(const Host &h) const;
    void listHosts() const;
    void clearHost(const Host &h);
    void clearAll();

  private:
    LinkedQueue siteQueue;
    bool isUrlForbidden(const string &u);
    const char *forbiddenMimes[6] = {".jpg", ".gif", ".mp3",
                                     ".avi", ".doc", ".pdf"};
};
