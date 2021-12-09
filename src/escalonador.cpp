#include "escalonador.hpp"
#include "msgassert.hpp"
#include <sstream>

static constexpr int NUM_FM = 6;
static const char *forbiddenMimes[NUM_FM] = {".jpg", ".gif", ".mp3",
                                             ".avi", ".doc", ".pdf"};
static const char *PROTOCOL = "http";
static constexpr unsigned NUM_COM = 8;
static const string COMMANDS[NUM_COM] = {
    "ADD_URLS", "ESCALONA_TUDO", "ESCALONA",   "ESCALONA_HOST",
    "VER_HOST", "LISTA_HOSTS",   "LIMPA_HOST", "LIMPA_TUDO"};

// @brief verifica se str termina em end
// @param str, end
// @return true se sim, false caso contrário
bool endsWith(const string &str, const string &end) {
    if (end.length() > str.length())
        return false;
    else {
        unsigned strL = str.length();
        unsigned endL = end.length();

        return (0 == str.compare(strL - endL, endL, end));
    }
}

// @brief verifica se a URL u termina em uma extensão proibida
// @param u (URL)
// @return true se sim, false caso contrário
bool Escalonador::isUrlForbidden(const string &u) {
    for (int i = 0; i < NUM_FM; ++i)
        if (endsWith(u, forbiddenMimes[i])) return true;

    return false;
}

// @brief abre arquivo de saída do escalonador
// @param outFile (nome do arquivo)
Escalonador::Escalonador(const string &outFile) {
    this->outputFile.open(outFile);

    erroAssert(this->outputFile.is_open(), "Erro ao abrir arquivo de saída");
}

// @brief fecha arquivo de saída do escalonador
Escalonador::~Escalonador() {
    this->outputFile.close();

    erroAssert(!this->outputFile.is_open(), "Erro ao fechar arquivo de saída");
}

// @brief se válida, insere a URL no lugar certo
// @param u (URL)
void Escalonador::insertUrl(const URL &u) {
    if (u.getProtocol() != PROTOCOL) return;

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

// @brief imprime n URLs ou o máximo que o escalonador contém
// @param n (quantidade de URLs a imprimir)
void Escalonador::escalonaN(const int &n) {
    this->siteQueue.printNUrls(n, this->outputFile);

    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// @brief escalona toda a fila, removendo as URLs, mantendo os Sites
// Se a fila estiver vazia, faz nada
void Escalonador::escalonaTudo() {
    this->siteQueue.escalonaTudo(this->outputFile);

    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// @brief escalona n URLs do Host, ou o Host todo, mantendo o Site na fila
// @param h (Host), n (quantidade de URLs a escalonar)
// Se o Host estiver ausente, faz nada
void Escalonador::escalonaHost(const Host &h, int &n) {
    if (!this->siteQueue.isHostInQueue(h)) return;

    LinkedList *p = this->siteQueue.getUrlsFromHost(h);
    if (n > p->getSize()) n = p->getSize();
    p->escalona(this->outputFile, n);

    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// @brief lista as URLs do Host
// @param h (Host)
// Se o Host estiver ausente, faz nada
void Escalonador::listUrls(const Host &h) {
    if (!this->siteQueue.isHostInQueue(h)) return;

    this->siteQueue.getUrlsFromHost(h)->print(this->outputFile);

    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// @brief limpa as URLs do Host
// @param h (Host)
// Se o Host estiver ausente, faz nada
void Escalonador::clearHost(const Host &h) {
    if (!this->siteQueue.isHostInQueue(h)) return;

    this->siteQueue.getUrlsFromHost(h)->clear();
}

// @brief imprime os Hosts da fila
// Se a fila estiver vazia, faz nada
void Escalonador::listHosts() {
    this->siteQueue.printHosts(this->outputFile);

    erroAssert(!this->outputFile.fail(), "Erro ao escrever arquivo de saída");
}

// @brief limpa a fila
void Escalonador::clearAll() {
    this->siteQueue.clear();

    erroAssert(this->siteQueue.empty(), "Erro ao limpar fila");
}

// @brief adiona um conjunto de até n URLs a partir de um dado arquivo
// @param n, ist (arquivo de entrada)
void Escalonador::addUrls(const int &n, std::ifstream &ist) {
    string str;

    for (int i = 0; i < n; ++i) {
        std::getline(ist, str);

        if (ist.eof()) break;

        if (str.find("://") != string::npos) insertUrl(str);
    }
}

// @brief lê arquivo contendo instruções e as executa
// @param inputFile
void Escalonador::readFile(std::ifstream &inputFile) {
    do {
        string line;
        std::getline(inputFile, line);
        std::stringstream ss(line);

        if (line.find(COMMANDS[0]) != string::npos) {
            string str;
            int x;
            ss >> str >> x;
            addUrls(x, inputFile);
        } else if (line.find(COMMANDS[1]) != string::npos) {
            escalonaTudo();
        } else if (line.find(COMMANDS[3]) != string::npos) {
            Host h;
            string str;
            int x;
            ss >> str >> h >> x;
            escalonaHost(h, x);
        } else if (line.find(COMMANDS[2]) != string::npos) {
            string str;
            int x;
            ss >> str >> x;
            escalonaN(x);
        } else if (line.find(COMMANDS[4]) != string::npos) {
            Host h;
            string str;
            ss >> str >> h;
            listUrls(h);
        } else if (line.find(COMMANDS[5]) != string::npos) {
            listHosts();
        } else if (line.find(COMMANDS[6]) != string::npos) {
            Host h;
            string str;
            ss >> str >> h;
            clearHost(str);
        } else if (line.find(COMMANDS[7]) != string::npos)
            clearAll();

        erroAssert(!inputFile.bad(), "Erro ao ler do arquivo");

        if (inputFile.eof()) break;

    } while (true);
}
