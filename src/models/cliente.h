//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_CLIENTE_H
#define NETFLIX_LSS_CLIENTE_H

#include <string>
#include <vector>

#include "Filme.h"

class Cliente {
public:
    int id = -1;
    std::string nome = "";
    std::string endereco = "";
    std::string cpf = "";

    Cliente(int id, const std::string &nome, const std::string &endereco, const std::string &cpf);

    Cliente();

    static Cliente fromJson(std::string json);

    std::string toJson();

    bool operator==(const Cliente &rhs) const;

    bool operator!=(const Cliente &rhs) const;
};

#endif //NETFLIX_LSS_CLIENTE_H
