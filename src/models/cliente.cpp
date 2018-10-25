//
// Created by aluno on 10/10/18.
//

#include "cliente.h"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

Cliente::Cliente(int id, const std::string &nome, const std::string &endereco, const std::string &cpf, double divida)
        : id(id), nome(nome), endereco(endereco), cpf(cpf), divida(divida) {

}

Cliente::Cliente() {

}

Cliente Cliente::fromJson(std::string json) {
  Json j = Json::parse(json);

  return Cliente(j["id"], j["nome"], j["endereco"], j["cpf"], j["divida"]);
}

std::string Cliente::toJson() {

  Json j = {
    {"id", Cliente::id},
    {"nome", Cliente::nome},
    {"endereco", Cliente::endereco},
    {"divida", Cliente::divida},
    {"cpf", Cliente::cpf}
  };

  return j.dump();
}

bool Cliente::operator==(const Cliente &rhs) const {
  return nome == rhs.nome &&
         endereco == rhs.endereco &&
         cpf == rhs.cpf &&
         divida == rhs.divida;
}

bool Cliente::operator!=(const Cliente &rhs) const {
  return !(rhs == *this);
}


