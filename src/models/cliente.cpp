//
// Created by aluno on 10/10/18.
//

#include "cliente.h"

Cliente::Cliente(int id, const std::string &nome, const std::string &endereco, double divida) : id(id), nome(nome),
                                                                                                endereco(endereco),
                                                                                                divida(divida) {
}

Cliente::Cliente() {

}

Cliente Cliente::fromJson(std::string json) {
  Json j = Json::parse(json);

  return Cliente(j["id"], j["nome"], j["endereco"], j["divida"]);
}

std::string Cliente::toJson() {

  Json j = {
    {"id", Cliente::id},
    {"nome", Cliente::nome},
    {"endereco", Cliente::endereco},
    {"divida", Cliente::divida}
  };

  return j.dump();
}
