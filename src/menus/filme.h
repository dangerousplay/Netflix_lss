//
// Created by aluno on 17/10/18.
//

#ifndef FILME_MENU
#define FILME_MENU

#include <vector>
#include "IMenu.h"
#include "../models/Filme.h"

class FilmeMenu : public IMenu {
private:
    Filme atual;
    std::vector<Filme> filmes;
    bool editando = false;
public:

    FilmeMenu();

    void render() override;

    std::vector<Filme> getFilmes();
};

#endif
