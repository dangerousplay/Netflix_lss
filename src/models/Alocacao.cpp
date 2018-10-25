//
// Created by aluno on 10/10/18.
//

#include "Alocacao.h"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;


Alocacao::Alocacao(int id, int clienteId, const std::string &dataInicial, const std::string &dataFinal,
                   const std::string &filmes, double valor) : id(id), clienteId(clienteId), dataInicial(dataInicial),
                                                              dataFinal(dataFinal), filmes(filmes), valor(valor) {}

Alocacao::Alocacao() {}

std::string Alocacao::toJson() {
    Json j = {
            {"id", Alocacao::id},
            {"clienteId", Alocacao::clienteId},
            {"dataInicial", Alocacao::dataInicial},
            {"dataFinal", Alocacao::dataFinal},
            {"filmes", Alocacao::filmes},
            {"valor", Alocacao::valor}
    };


    return j.dump();
}

Alocacao Alocacao::fromJson(std::string json) {
    Json j = Json::parse(json);

    return Alocacao(j["id"], j["clienteId"], j["dataInicial"], j["dataFinal"], j["filmes"], j["valor"]);
}

bool Alocacao::operator==(const Alocacao &rhs) const {
    return clienteId == rhs.clienteId &&
           dataInicial == rhs.dataInicial &&
           dataFinal == rhs.dataFinal &&
           filmes == rhs.filmes &&
           valor == rhs.valor;
}

bool Alocacao::operator!=(const Alocacao &rhs) const {
    return !(rhs == *this);
}
