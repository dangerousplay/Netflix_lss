//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_FILME_H
#define NETFLIX_LSS_FILME_H


#include <string>


class Filme {
public:
    int id;
    std::string nome;
    double valor;
    std::string anoLancamento;
    std::string sinopse;
    std::string genero;

    Filme();

    Filme(int id, const std::string &nome, double valor, const std::string &anoLancamento, const std::string &sinopse,
          const std::string &genero);

    std::string toJson();
    static Filme fromJson(std::string json);
};


#endif //NETFLIX_LSS_FILME_H
