//
// Created by davi.henrique on 11/10/2018.
//

#include <memory>
#include "../models/cliente.h"
#include "../models/Filme.h"
#include "../models/Alocacao.h"

#ifndef SERVICO_LOCADORA
#define SERVICO_LOCADORA

#include "boost/date_time/gregorian/gregorian.hpp"

class ServicoLocadora {
public:
  ServicoLocadora();

  std::vector<Alocacao> alocarFilmes(Cliente cliente, boost::gregorian::date_period periodo, std::vector<Filme> filmes) noexcept;

  bool pagarDivida(Alocacao aloc);

  bool quitarDivida(Cliente cliente);

  std::vector<Alocacao> allocacoesEmAtraso();

  std::vector<Alocacao> allocacoesEmAtrasoByCliente(Cliente cliente);

};

extern ServicoLocadora servicoLocadora;

#endif