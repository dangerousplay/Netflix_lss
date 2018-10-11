#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "models/cliente.h"
#include "models/Filme.h"
#include <nlohmann/json.hpp>

using namespace sqlite_orm;

using json = nlohmann::json;

int main() {

    json t;
    t["pi"] = 3.45;

    std::cout << t;
    /*auto storage = make_storage("db.sqlite",
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
                                           make_column("valor", &Filme::valor)
                                           )
                               );

    Cliente cliente(-1,"Davi", "Rua DR", 0);

    try {
        auto key = storage.insert(cliente);

        std::cout << "User Key generated: " << key << std::endl;


        auto cc = storage.get<Cliente>(key);

        std::cout << "CC name: " << cc.nome << std::endl;

    } catch (std::exception e){
        std::cout << e.what() << std::endl;
    }*/


    return 0;
}