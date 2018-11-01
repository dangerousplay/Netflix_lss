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

    static internal::storage_t<table_t<internal::column_t<Cliente, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>, internal::column_t<Cliente, std::string>>, table_t<internal::column_t<Filme, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, std::string>, internal::column_t<Filme, double>, internal::column_t<Filme, std::string>>, table_t<internal::column_t<Alocacao, int, constraints::autoincrement_t, constraints::primary_key_t<>>, internal::column_t<Alocacao, int>, internal::column_t<Alocacao, long>, internal::column_t<Alocacao, long>, internal::column_t<Alocacao, int>, internal::column_t<Alocacao, double>, internal::column_t<Alocacao, bool>, internal::column_t<Alocacao, long>, constraints::foreign_key_t<int Alocacao::*, int Filme::*>, constraints::foreign_key_t<int Alocacao::*, int Cliente::*>>>
  initDatabase(std::string filename) {
    auto storage = make_storage(filename,
                                make_table("clientes",
                                           make_column("id", &Cliente::id, autoincrement(), primary_key()),
                                           make_column("nome", &Cliente::nome),
                                           make_column("endereco", &Cliente::endereco),
                                           make_column("cpf", &Cliente::cpf)
                                ),

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
                                           make_column("filmeId", &Alocacao::filmeId),
                                           make_column("valor", &Alocacao::valor),
                                           make_column("paga", &Alocacao::paga),
                                           make_column("data_entrega", &Alocacao::dataEntrega),

                                           foreign_key(&Alocacao::filmeId).references(&Filme::id),
                                           foreign_key(&Alocacao::clienteId).references(&Cliente::id)
                                )
    );

    storage.sync_schema();

    return storage;
  }

    decltype(initDatabase("")) storage = initDatabase("db.sqlite");
public:

  decltype(storage)
  getStorage() const {
    return storage;
  }
};

class EventHandler {
private:
    typedef std::function<void(void)> CallbackFunction;
    std::vector<CallbackFunction> callbacks;

public:

    void registerOnUpdate(CallbackFunction function);

    void callUpdate();
};

extern std::unique_ptr<Database> dbInstance;

extern EventHandler globalHandler;

#endif

