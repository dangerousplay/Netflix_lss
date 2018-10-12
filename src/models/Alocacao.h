//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_ALOCACAO_H
#define NETFLIX_LSS_ALOCACAO_H


#include <string>
#include <vector>
#include "Filme.h"
#include "cliente.h"

class Alocacao {
public:
  int id;
  int clienteId;
  std::string dataInicial;
  std::string dataFinal;
  std::string filmes;
  double valor;

  Alocacao(int id, int clienteId, const std::string &dataInicial, const std::string &dataFinal,
             const std::string &filmes, double valor);

  Alocacao();

  static Alocacao fromJson(std::string json);

  std::string toJson();
};


#endif //NETFLIX_LSS_ALOCACAO_H
