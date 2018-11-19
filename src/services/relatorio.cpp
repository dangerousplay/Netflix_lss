//
// Created by moiseskaufmann on 19/11/18.
//

#include "relatorio.h"
#include "../utils/unixTime.h"

generatePDF_return ServicoRelatorio::gerarRelatorio(std::vector<Alocacao> alocacoes) {

    std::vector<GoAlocacao>goalocacao;
    for (auto alok:alocacoes){
        double multa = 0;
        if ( alok.dataFinal < alok.dataEntrega){
            multa = (alok.periodoAlocacao.end() - to_bdate(alok.dataEntrega)).days()* 0.4;
        }
        GoAlocacao alocacao = createAlocacao(alok.id, (GoUint64)alok.dataInicial,(GoUint64)alok.dataFinal,(GoUint64)alok.dataEntrega,alok.valor,multa);
        goalocacao.push_back(alocacao);
    }
    return generatePDF(GoSlice{&goalocacao[0],(GoInt)goalocacao.size(),(GoInt)goalocacao.capacity()});
}

