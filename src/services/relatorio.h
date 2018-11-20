//
// Created by moiseskaufmann on 19/11/18.
//

#ifndef NETFLIX_LSS_RELATORIO_H
#define NETFLIX_LSS_RELATORIO_H

#include <vector>
#include "pdf.h"
#include "../models/Alocacao.h"

class ServicoRelatorio{
    generatePDF_return gerarRelatorio(std::vector<Alocacao> alocacoes);



};
#endif //NETFLIX_LSS_RELATORIO_H
