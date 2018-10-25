//
// Created by aluno on 17/10/18.
//

#ifndef FILME_MENU
#define FILME_MENU

#include <vector>
#include <memory>
#include "IMenu.h"
#include "../models/Filme.h"

#define BUFFER_SIZE 100

class FilmeMenu : public IMenu {
private:
    Filme atual;
    std::vector<Filme> filmes;
    bool editando = false;
    bool open = true;

    std::vector<char> generoBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<char> sinopseBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<char> anoBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<char> nomeBufferF = std::vector<char>(BUFFER_SIZE);

    std::shared_ptr<char> bufferPesquisaF = std::make_shared<char>(512);

    std::vector<std::string> messageFieldsF;

    void updateFilmes();
    void clearFilme();
    void editMenu(Filme filme);
    void refreshBuffers();
    void removeDuplicates(std::string &b);
    bool validateFields();

public:

    FilmeMenu();

    void render() override;

    std::vector<Filme> getFilmes();

    bool isOpen() const;

    void setOpen(bool open);
};

#endif
