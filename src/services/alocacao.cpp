//
// Created by davi.henrique on 11/10/2018.
//

#include "alocacao.h"
#include "../db/init.h"
#include "../utils/unixTime.h"

ServicoLocadora servicoLocadora = ServicoLocadora();

std::vector<Alocacao> ServicoLocadora::alocarFilmes(Cliente cliente, boost::gregorian::date_period periodo, std::vector<Filme> filmes) noexcept {
    bool allocaded = std::any_of(filmes.begin(), filmes.end(), [](Filme filme) -> bool {
        return dbInstance->getStorage().count<Alocacao>(where(c(&Alocacao::filmeId) == filme.id)) != 0;
    });

    if(allocaded){
        throw std::exception();
    }

    std::vector<Alocacao> alocacoes;

    std::transform(filmes.begin(), filmes.end(), alocacoes.begin(), [&cliente, &periodo](Filme filme) -> Alocacao {
        return Alocacao(-1, cliente.id, filme.id, periodo, filme.valor);
    });

    dbInstance->getStorage().begin_transaction();

    dbInstance->getStorage().insert_range(alocacoes.begin(), alocacoes.end());

    dbInstance->getStorage().commit();

}

bool ServicoLocadora::quitarDivida(Cliente cliente) {
    try{
        dbInstance->getStorage().update_all(set(c(&Alocacao::paga) = true), where(c(&Alocacao::clienteId) == cliente.id));
    }catch (std::exception &e){
        std::cout << e.what();
        return false;
    }

  return true;
}

std::vector<Alocacao> ServicoLocadora::allocacoesEmAtraso() {
  return dbInstance->getStorage()
  .get_all<Alocacao>(
          where(
                  c(&Alocacao::dataFinal) < toMillisecondsEpoch(boost::gregorian::day_clock::local_day())
                  ));
}

bool ServicoLocadora::pagarDivida(Alocacao aloc) {
    aloc.paga = true;

    dbInstance->getStorage().update<Alocacao>(aloc);

  return false;
}

std::vector<Alocacao> ServicoLocadora::allocacoesEmAtrasoByCliente(Cliente cliente) {
  return dbInstance->getStorage()
          .get_all<Alocacao>(
                  where(
                          c(&Alocacao::dataFinal) < toMillisecondsEpoch(boost::gregorian::day_clock::local_day()) and
                          c(&Alocacao::clienteId) == cliente.id
                  ));
}

std::vector<Filme> ServicoLocadora::getAllFimesNotAllocated() {
    auto rows = dbInstance->getStorage()
            .select(columns(&Filme::id,
                            &Filme::nome,
                            &Filme::valor,
                            &Filme::anoLancamento,
                            &Filme::sinopse,
                            &Filme::genero,
                            &Alocacao::id),
                    left_join<Alocacao>(on(c(&Alocacao::clienteId) == &Filme::id)),
                    where(is_null(&Alocacao::id)));

    std::vector<Filme> filmes;

    for (auto row : rows) {
        filmes.emplace_back(std::get<0>(row), std::get<1>(row), std::get<2>(row), std::get<3>(row), std::get<4>(row),
                            std::get<5>(row));
    }

    return filmes;
}

std::vector<Filme> ServicoLocadora::getAllFimesAllocated() {
    auto rows = dbInstance->getStorage()
            .select(columns(&Filme::id,
                            &Filme::nome,
                            &Filme::valor,
                            &Filme::anoLancamento,
                            &Filme::sinopse,
                            &Filme::genero,
                            &Alocacao::id),
                    left_join<Alocacao>(on(c(&Alocacao::clienteId) == &Filme::id)),
                    where(is_not_null(&Alocacao::id)));

    std::vector<Filme> filmes;

    for (auto row: rows) {
        filmes.emplace_back(std::get<0>(row), std::get<1>(row), std::get<2>(row), std::get<3>(row), std::get<4>(row),
                            std::get<5>(row));
    }

    return filmes;
}

ServicoLocadora::ServicoLocadora() = default;
