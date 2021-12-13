#include "escalonador.hpp"
#include "msgassert.hpp"
#include <sstream>

static constexpr int INVALID_COMMAND = -1;
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

        // Não insira linhas que não são URLs
        if (str.find("://") != string::npos) insertUrl(str);
    }
}

int isLineValid(const string &str) {

    // Testa ESCALONA_TUDO, LISTA_HOSTS e LIMPA_TUDO
    if (str == COMMANDS[1]) return 1;
    if (str == COMMANDS[5]) return 5;
    if (str == COMMANDS[7]) return 7;

    // Testa VER_HOST e LIMPA_HOST
    // A linha deve começar com essas instruções
    // Não nos preocupamos em validar o Host, 
    // porque se o Host não estiver presente, 
    // as funções lidam com essa exceção
    if (!str.find(COMMANDS[4])) return 4;
    if (!str.find(COMMANDS[6])) return 6;

    // Testa ESCALONA_HOST
    if (!str.find(COMMANDS[3])) {
        std::stringstream ss(str);
        string command, host;
        int quantity;
        ss >> command >> host >> quantity;
        avisoAssert(quantity >= 0, "Quantidade negativa: " << quantity);
        if (quantity >= 0) return 3;
    }

    // Testa ADD_URLS e ESCALONA
    // A quantidade não pode ser negativa
    for (unsigned i = 0; i <= 2; i += 2) {
        if (!str.find(COMMANDS[i])) {
            std::stringstream ss(str);
            string command;
            int quantity;
            ss >> command >> quantity;
            avisoAssert(quantity >= 0, "Quantidade negativa: " << quantity);
            if (quantity >= 0) return i;
        }
    }

    return INVALID_COMMAND;
}

// @brief lê arquivo contendo instruções e as executa
// @param inputFile
void Escalonador::readFile(std::ifstream &inputFile) {
    do {
        string line;
        std::getline(inputFile, line);
        std::stringstream ss(line);
        int commandIndex = isLineValid(line);

        switch (commandIndex) {
            case 1: escalonaTudo(); break;
            case 5: listHosts(); break;
            case 7: clearAll(); break;
            case 4: {
                Host h;
                string str;
                ss >> str >> h;
                listUrls(h);
                break;
            }
            case 6: {
                Host h;
                string str;
                ss >> str >> h;
                clearHost(str);
                break;
            }
            case 3: {
                Host h;
                string str;
                int x;
                ss >> str >> h >> x;
                escalonaHost(h, x);
                break;
            }
            case 0: {
                isLineValid(line);
                string str;
                int x;
                ss >> str >> x;
                addUrls(x, inputFile);
                break;
            }
            case 2: {
                string str;
                int x;
                ss >> str >> x;
                escalonaN(x);
                break;
            }
        }

        erroAssert(!inputFile.bad(), "Erro ao ler do arquivo");

        if (inputFile.eof()) break;

    } while (true);
}
