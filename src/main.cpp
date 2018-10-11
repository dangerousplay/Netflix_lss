#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "models/cliente.h"
#include "models/Filme.h"
#include <nlohmann/json.hpp>

using namespace sqlite_orm;

using json = nlohmann::json;

int main() {

  Cliente t{1,"nome", "Ednereco",0};

  std::cout << "Json: " << t.toJson() << std::endl;

  Cliente fr = Cliente::fromJson(t.toJson());

  return 0;
}