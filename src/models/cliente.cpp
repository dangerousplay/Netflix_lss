//
// Created by aluno on 10/10/18.
//

#include "cliente.h"

Cliente::Cliente(int id, const std::string &nome, const std::string &endereco, double divida) : id(id), nome(nome),
                                                                                                endereco(endereco),
                                                                                                divida(divida) {

}

Cliente::Cliente() {}
