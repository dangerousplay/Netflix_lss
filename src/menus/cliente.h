//
// Created by aluno on 17/10/18.
//

#ifndef CLIENTE_MENU
#define CLIENTE_MENU

#include "IMenu.h"
#include "../models/cliente.h"

class ClienteMenu : public IMenu {
private:
    std::vector<Cliente> clientes;
    Cliente atual = Cliente();
    bool editando = false;

    void refreshBuffers();
    void updateClientes();
    void clearCliente();

public:
    ClienteMenu();

    const std::vector<Cliente> &getClientes() const;

    void render() override;
};

#endif


