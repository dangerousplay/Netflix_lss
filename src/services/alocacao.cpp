//
// Created by davi.henrique on 11/10/2018.
//

#include "alocacao.h"
#include "../db/init.h"

ServicoLocadora servicoLocadora = ServicoLocadora();

std::shared_ptr<Alocacao> ServicoLocadora::alocarFilmes(Cliente cliente, std::vector<Filme> filmes) {
  //dbInstance->getStorage().select()
}

bool ServicoLocadora::quitarDivida(Cliente cliente) {
  return false;
}

std::vector<Alocacao> ServicoLocadora::allocacoesEmAtraso() {
  return std::vector<Alocacao>();
}

bool ServicoLocadora::pagarDivida(Cliente cliente, double valor) {
  return false;
}

std::vector<Alocacao> ServicoLocadora::allocacoesEmAtrasoByCliente(Cliente cliente) {
  return std::vector<Alocacao>();
}

ServicoLocadora::ServicoLocadora() = default;
