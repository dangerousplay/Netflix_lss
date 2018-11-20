//
// Created by moiseskaufmann on 19/11/18.
//

#ifndef RELATORIO_NEX
#define RELATORIO_NEX

#include <vector>
#include "pdf.h"
#include "../models/Alocacao.h"

class ServicoRelatorio {

public:
    generatePDF_return gerarRelatorio(std::vector<Alocacao> alocacoes);

};

extern ServicoRelatorio servicoRelatorio;


#endif //NETFLIX_LSS_RELATORIO_H

