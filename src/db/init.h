//
// Created by davi.henrique on 11/10/2018.
//

#include <string>
#include "../models/cliente.h"
#include <sqlite_orm/sqlite_orm.h>
#include "../models/Alocacao.h"
#include "../models/Filme.h"

#ifndef DATABASE_SQLITE
#define DATABASE_SQLITE

using namespace sqlite_orm;

class Database {
private:
  internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, int>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, double>>> storage = initDatabase("db.sqlite");

  static internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, int>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, double>>>
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
                                           make_column("cliente_id", &Alocacao::clienteId),
                                           make_column("data_inicial", &Alocacao::dataInicial),
                                           make_column("data_final", &Alocacao::dataFinal),
                                           make_column("filmes", &Alocacao::filmes),
                                           make_column("valor", &Alocacao::valor)
                                )
    );

    storage.sync_schema();

    return storage;
  }
public:

  internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, double>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, int>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, std::string>, internal::column_t<Alocacao, double>>>
  getStorage() const {
    return storage;
  }
};

#ifndef DB_INSTANCE
#define DB_INSTANCE
std::unique_ptr<Database> dbInstance = std::make_unique<Database>();
#endif

#endif