//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_ALOCACAO_H
#define NETFLIX_LSS_ALOCACAO_H


#include <string>
#include <vector>
#include "Filme.h"
#include "cliente.h"
#include "boost/date_time/gregorian/gregorian.hpp"


class Alocacao {
private:


public:
  int id = -1;
  int clienteId;
  int filmeId;

  long dataInicial = 0;
  long dataFinal = 0;
  long dataEntrega = 0;

  Filme filme;
  Cliente cliente;

  boost::gregorian::date_period periodoAlocacao = boost::gregorian::date_period(boost::gregorian::date(),boost::gregorian::date());

  boost::gregorian::date dataEntregaP = boost::gregorian::date();

  double valor = 0;

  bool paga = false;

  Alocacao(int id, int clienteId, int filmeId, boost::gregorian::date_period periodo,
           double valor);

  Alocacao(int id, int clienteId, int filmeId, long dataInicial, long dataFinal, long dataEntrega, double valor, bool paga);


  Alocacao();

  static Alocacao fromJson(std::string json);

  std::string toJson();

  void setDataInicial(boost::gregorian::date data);

  void setDataFinal(boost::gregorian::date data);

  void setPeriodo(boost::gregorian::date_period periodo);

    void init();

  bool operator==(const Alocacao &rhs) const;

  bool operator!=(const Alocacao &rhs) const;

    bool isAtrasada();
};


#endif //NETFLIX_LSS_ALOCACAO_H
