//
// Created by aluno on 10/10/18.
//

#include "Filme.h"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

Filme Filme::fromJson(std::string json) {
    Json j = Json::parse(json);

    return Filme(j["id"], j["nome"], j["valor"], j["anoLancamento"], j["sinopse"], j["genero"]);
}

std::string Filme::toJson() {
    return toJsonStruct().dump();
}

Json Filme::toJsonStruct() {
    Json j = {
            {"id",Filme::id},
            {"nome", Filme::nome},
            {"valor", Filme::valor},
            {"anoLacamento", Filme::anoLancamento},
            {"sinopse", Filme::sinopse},
            {"genero", Filme::genero}
    };

    return j;
}

Filme::Filme(int id, const std::string &nome, double valor, const std::string &anoLancamento,
             const std::string &sinopse, const std::string &genero) : id(id), nome(nome), valor(valor),
                                                                      anoLancamento(anoLancamento), sinopse(sinopse),
                                                                      genero(genero) {

}

Filme::Filme() {
    Filme::id = -1;
    Filme::valor = 0;
}

bool Filme::operator==(const Filme &rhs) const {
    return nome == rhs.nome &&
           valor == rhs.valor &&
           anoLancamento == rhs.anoLancamento &&
           sinopse == rhs.sinopse &&
           genero == rhs.genero;
}

bool Filme::operator!=(const Filme &rhs) const {
    return !(rhs == *this);
}

