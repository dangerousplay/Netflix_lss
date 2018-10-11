//
// Created by davi.henrique on 11/10/2018.
//

#include "../models/cliente.h"
#include "../models/Filme.h"
#include "../models/Alocacao.h"

class ServicoLocadora {
private:
  ServicoLocadora();
public:
  Alocacao* alocarFilmes(Cliente cliente, std::vector<Filme> filmes);

  bool pagarDivida(Cliente cliente, double valor);

  bool quitarDivida(Cliente cliente);

  std::vector<Alocacao> allocacoesEmAtraso();

  std::vector<Alocacao> allocacoesEmAtraso(Cliente cliente);

};