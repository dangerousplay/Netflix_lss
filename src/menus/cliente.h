//
// Created by aluno on 17/10/18.
//

#ifndef CLIENTE_MENU
#define CLIENTE_MENU

#include "IMenu.h"

class ClienteMenu : public IMenu {
public:
    ClienteMenu();

    void render() override;
};

#endif


