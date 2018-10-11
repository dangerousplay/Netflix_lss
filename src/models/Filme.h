//
// Created by aluno on 10/10/18.
//

#ifndef NETFLIX_LSS_FILME_H
#define NETFLIX_LSS_FILME_H


#include <string>

class Filme {
public:
    int id;
    std::string nome;
    std::string codigo;
    double valor;
    std::string anoLancamento;
    std::string sinopse;
    std::string genero;
};


#endif //NETFLIX_LSS_FILME_H
