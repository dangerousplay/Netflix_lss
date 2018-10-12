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
    int id = 0;
    std::string nome = "";
    std::string endereco = "";

    Cliente(int id, const std::string &nome, const std::string &endereco, double divida);

    double divida = 0;

    Cliente();

    static Cliente fromJson(std::string json);

    std::string toJson();

};

#endif //NETFLIX_LSS_CLIENTE_H
