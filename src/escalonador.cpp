#include "escalonador.hpp"
#include "msgassert.hpp"

static constexpr int numFM = 6;
static const char *forbiddenMimes[numFM] = {".jpg", ".gif", ".mp3",
                                            ".avi", ".doc", ".pdf"};
static const char *allowedProtocol = "http";

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

Escalonador::Escalonador(const string &outFile) {
    this->outputFile.open(outFile);
    erroAssert(this->outputFile.is_open(), "Erro ao abrir arquivo de saída");
}

Escalonador::~Escalonador() {
    this->outputFile.close();
    erroAssert(!this->outputFile.is_open(), "Erro ao fechar arquivo de saída");
}

// Se válida, insere a URL no lugar certo
void Escalonador::insertUrl(const URL &u) {
    if (u.getProtocol() != allowedProtocol) return;

    string urlWithFrag = u.getUrl();
    if (isUrlForbidden(urlWithFrag)) return;

    string urlNoFrag = u.getUrlNoFrag();
    string urlHost = u.getHost();

    // Se o Host está presente, insira a Url em sua lista
    // Caso contrário, crie uma nova célula na fila
    (this->siteQueue.isHostInQueue(urlHost))
        ? this->siteQueue.getUrlsFromHost(urlHost)->insertMid(urlNoFrag)
        : this->siteQueue.line(urlNoFrag);
}

// Imprime N URLs ou o máximo que o escalonador contém
void Escalonador::escalonaN(const int &n) {
    this->siteQueue.printNUrls(n, this->outputFile);
    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// Escalona toda a fila, removendo-a
void Escalonador::escalonaTudo() {
    while (!this->siteQueue.empty()) {
        this->siteQueue.getFront()->item.printUrls(this->outputFile);
        this->siteQueue.unline();
    }
    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// Escalona n URLs do Host, ou o Host todo,
// mantendo sua URL na fila
void Escalonador::escalonaHost(const Host &h, int &n) {
    URL u;
    LinkedList *p = this->siteQueue.getUrlsFromHost(h);
    if (n > p->getSize()) n = p->getSize();

    for (int i = 0; i < n; ++i) {
        u = p->removeBeg();
        u.print(this->outputFile);
    }
    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// Se o Host estiver presente, lista suas URLs, caso contrário faz nada
void Escalonador::listUrls(const Host &h) {
    if (!this->siteQueue.isHostInQueue(h)) return;
    this->siteQueue.getUrlsFromHost(h)->print(this->outputFile);
    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// Se o Host estiver presente, limpa-o, caso contrário faz nada
void Escalonador::clearHost(const Host &h) {
    if (!this->siteQueue.isHostInQueue(h)) return;
    this->siteQueue.getUrlsFromHost(h)->clear();
}

// Se a lista estiver vazia, faz nada, caso contrário imprime Hosts
void Escalonador::listHosts() {
    this->siteQueue.printHosts(this->outputFile);
    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

void Escalonador::clearAll() { this->siteQueue.clear(); }

void Escalonador::addUrls(const int &n, std::ifstream &ist) {
    string str;
    for (int i = 0; i < n; ++i) {
        std::getline(ist, str);
        if (ist.eof()) break;
        if (str.find("://") != string::npos) insertUrl(str);
    }
}
