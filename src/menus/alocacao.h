//
// Created by aluno on 17/10/18.
//

#include "IMenu.h"
#include "../models/Alocacao.h"
#include <vector>

class AlocacaoMenu : public IMenu {
private:
    std::vector<Alocacao> alocacoes;

    std::vector<Cliente> clientes;

    std::vector<Filme> filmes;

    std::vector<Filme> filmeSelecionados;

    std::shared_ptr<char> clienteBuffer = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));
    std::shared_ptr<char> filmeBuffer = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));
    std::shared_ptr<char> dataInicialBuffer = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));
    std::shared_ptr<char> dataFinalBuffer = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));
    std::shared_ptr<char> bufferPesquisaF = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));

    std::vector<std::string> messageFields;

    Alocacao atual = Alocacao();

    bool editando = false;

    void refreshBuffers();

    int findClienteByName(const char *name);

    Filme findFilmeByName(const char *name);

    double sumFilmValues();

    void updateAlocacoes();

    void clearAlocacao();

    bool validateFields();

    void removeDuplicates(std::string &b);

public:
    AlocacaoMenu();

    void render() override;


};
