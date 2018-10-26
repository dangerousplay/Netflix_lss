//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_FILME_H
#define NETFLIX_LSS_FILME_H


#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;


class Filme {
public:
    int id = -1;
    std::string nome = "";
    double valor = 0;
    std::string anoLancamento = "";
    std::string sinopse = "";
    std::string genero = "";

    bool operator==(const Filme &rhs) const;

    bool operator!=(const Filme &rhs) const;

    Filme();

    Filme(int id, const std::string &nome, double valor, const std::string &anoLancamento, const std::string &sinopse,
          const std::string &genero);

    std::string toJson();

    Json toJsonStruct();

    static Filme fromJson(std::string json);
};


#endif //NETFLIX_LSS_FILME_H
