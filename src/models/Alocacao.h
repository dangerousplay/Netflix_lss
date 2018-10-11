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
  std::string alocante;
  std::string dataInicial;
  std::string dataFinal;
  std::string filmes;

  double valor;

};


#endif //NETFLIX_LSS_ALOCACAO_H
