//
// Created by davi.henrique on 11/10/2018.
//

#include <string>
#include "../models/cliente.h"
#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

class Database {
private:
  static std::unique_ptr<Database> instance;
  internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>>> storage = initDatabase("db.sqlite");

  internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>>>
  initDatabase(std::string filename) {
    auto storage = make_storage(filename,
                                make_table("clientes",
                                           make_column("id", &Cliente::id, autoincrement(), primary_key()),
                                           make_column("nome", &Cliente::nome),
                                           make_column("endereco", &Cliente::endereco),
                                           make_column("divida", &Cliente::divida)),

                                make_table("filmes",
                                           make_column("id", &Filme::id, autoincrement(), primary_key()),
                                           make_column("nome", &Filme::nome),
                                           make_column("sinopse", &Filme::sinopse),
                                           make_column("ano_lancamento", &Filme::anoLancamento),
                                           make_column("valor", &Filme::valor),
                                           make_column("genero", &Filme::genero)
                                ),

                                make_table("alocacao",
                                           make_column("id", &Alocacao::id, autoincrement(), primary_key()),
                                           make_column("data_inicial", &Alocacao::dataInicial),
                                           make_column("data_final", &Alocacao::dataFinal),
                                           make_column("filmes", &Alocacao::filmes)
                                )
    );

    storage.sync_schema();

    return storage;
  }
public:

  static const std::unique_ptr<Database> &getInstance() {
    if(instance == nullptr)
      instance = std::make_unique<Database>();

    return instance;
  }

  internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>>>
  getStorage() const {
    return storage;
  }
};