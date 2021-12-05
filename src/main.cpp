#include "escalonador.hpp"
#include "msgassert.hpp"

void appendOut(string &str) {
    (str.find('.') == string::npos) ? str += "-out"
                                    : str.insert(str.find('.'), "-out");
}

int main(int argc, char *argv[]) {
    erroAssert(argc > 1, "Passe o nome do arquivo de entrada como parâmetro");
    string fileName = argv[1];

    std::ifstream inputFile;
    inputFile.open(fileName);
    erroAssert(inputFile.is_open(), "Erro ao abrir arquivo de entrada");

    appendOut(fileName);
    Escalonador E(fileName);

    E.readFile(inputFile);

    inputFile.close();
    erroAssert(!inputFile.is_open(), "Erro ao fechar arquivo de entrada");

    return 0;
}
