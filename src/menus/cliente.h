//
// Created by aluno on 17/10/18.
//

#ifndef CLIENTE_MENU
#define CLIENTE_MENU

#include <memory>
#include "IMenu.h"
#include "../models/cliente.h"

#define BUFFER_SIZE 100

class ClienteMenu : public IMenu {
private:
    std::vector<Cliente> clientes;
    Cliente atual = Cliente();
    bool editando = false;

    std::shared_ptr<char> bufferPesquisa = std::make_shared<char>(512);
    std::vector<char> enderecoBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<char> cpfBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<char> nomeBuffer = std::vector<char>(BUFFER_SIZE);
    std::vector<std::string> messageFields;

    void refreshBuffers();
    void updateClientes();
    void clearCliente();
    bool validateFields();
    void removeDuplicates(std::string &b);

public:
    ClienteMenu();

    const std::vector<Cliente> &getClientes() const;

    void render() override;
};

#endif


