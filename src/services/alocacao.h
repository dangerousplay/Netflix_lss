//
// Created by davi.henrique on 11/10/2018.
//

#include <memory>
#include "../models/cliente.h"
#include "../models/Filme.h"
#include "../models/Alocacao.h"

#ifndef SERVICO_LOCADORA
#define SERVICO_LOCADORA

class ServicoLocadora {
public:
  ServicoLocadora();

  std::shared_ptr<Alocacao> alocarFilmes(Cliente cliente, std::vector<Filme> filmes);

  bool pagarDivida(Cliente cliente, double valor);

  bool quitarDivida(Cliente cliente);

  std::vector<Alocacao> allocacoesEmAtraso();

  std::vector<Alocacao> allocacoesEmAtrasoByCliente(Cliente cliente);

};

extern ServicoLocadora servicoLocadora;

#endif