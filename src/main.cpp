#include "escalonador.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

memlog ml;

static const string OUT = "-out";
static const string LOG = "-log";

// @brief Adiciona marcador ao nome do arquivo
// @param nome do arquivo, marcador
// @return nome do arquivo com marcador
string append(string &str, const string c) {
    string s;
    if (str.find('.') == string::npos)
        s = str + c;
    else {
        s = str;
        s.insert(s.find('.'), c);
    }
    return s;
}

// @brief Executa o programa principal
int main(int argc, char *argv[]) {
    erroAssert(argc > 1, "Passe o nome do arquivo de entrada como parâmetro");
    string fileName = argv[1];

    std::ifstream inputFile;
    inputFile.open(fileName);
    erroAssert(inputFile.is_open(), "Erro ao abrir arquivo de entrada");

    string logName = append(fileName, LOG);
    ml.iniciaMemLog(logName);

    string outName = append(fileName, OUT);
    Escalonador E(outName);

    E.readFile(inputFile);

    inputFile.close();
    erroAssert(!inputFile.is_open(), "Erro ao fechar arquivo de entrada");

    return ml.finalizaMemLog();
}
