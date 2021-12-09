#include "escalonador.hpp"
#include "msgassert.hpp"

static const string OUT = "-out";

// @brief Adiciona o marcador de saída ao nome do arquivo
// @param nome do arquivo, marcador de saída
// @return nome do arquivo com marcador
void append(string &str, const string c) {
    (str.find('.') == string::npos) ? str += c : str.insert(str.find('.'), c);
}

// @brief Executa o programa principal
// @param argc, argv
// @return TODO
int main(int argc, char *argv[]) {
    erroAssert(argc > 1, "Passe o nome do arquivo de entrada como parâmetro");
    string fileName = argv[1];

    std::ifstream inputFile;
    inputFile.open(fileName);
    erroAssert(inputFile.is_open(), "Erro ao abrir arquivo de entrada");

    append(fileName, OUT);
    Escalonador E(fileName);

    E.readFile(inputFile);

    inputFile.close();
    erroAssert(!inputFile.is_open(), "Erro ao fechar arquivo de entrada");

    return 0;
}
