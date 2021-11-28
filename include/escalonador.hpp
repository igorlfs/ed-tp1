#pragma once

#include "linkedqueue.hpp"

class Escalonador {
  public:
    void insertUrl(const URL &u);
    void listUrls(const Host &h) const;
    void listHosts() const;
    void clearAll();

  private:
    LinkedQueue siteQueue;
    bool isUrlForbidden(const string &u);
    const char *forbiddenMimes[6] = {".jpg", ".gif", ".mp3",
                                     ".avi", ".doc", ".pdf"};
};
