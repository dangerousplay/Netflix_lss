//
// Created by aluno on 10/10/18.
//

#include "Alocacao.h"
#include "../db/init.h"

#include <nlohmann/json.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../utils/unixTime.h"

using Json = nlohmann::json;

Alocacao::Alocacao(int id, int clienteId, int filmeId, const boost::gregorian::date_period periodo,
                   double valor) : id(id), clienteId(clienteId), filmeId(filmeId), valor(valor) {

    Alocacao::dataInicial = toMillisecondsEpoch(periodo.begin());
    Alocacao::dataFinal = toMillisecondsEpoch(periodo.end());

    Alocacao::periodoAlocacao = periodo;

    Alocacao::filme = dbInstance->getStorage().get<Filme>(filmeId);
    Alocacao::cliente = dbInstance->getStorage().get<Cliente>(clienteId);
}

Alocacao::Alocacao() {}

Alocacao::Alocacao(int id, int clienteId, int filmeId, long dataInicial, long dataFinal, double valor, bool paga) : id(
        id), clienteId(clienteId), filmeId(filmeId), dataInicial(dataInicial), dataFinal(dataFinal), valor(valor),
                                                                                                                    paga(paga) {
    Alocacao::periodoAlocacao = boost::gregorian::date_period(to_bdate(dataInicial),to_bdate(dataFinal));

    Alocacao::filme = dbInstance->getStorage().get<Filme>(filmeId);
    Alocacao::cliente = dbInstance->getStorage().get<Cliente>(clienteId);
}

std::string Alocacao::toJson() {
    Json j = {
            {"id", Alocacao::id},
            {"clienteId", Alocacao::clienteId},
            {"dataInicial", Alocacao::dataInicial},
            {"dataFinal", Alocacao::dataFinal},
            {"filmeId", Alocacao::filmeId},
            {"valor", Alocacao::valor}
    };


    return j.dump();
}

Alocacao Alocacao::fromJson(std::string json) {
    Json j = Json::parse(json);

    return Alocacao(j["id"], j["clienteId"], j["filmeId"], j["dataInicial"], j["dataFinal"], j["valor"], j["paga"]);
}

bool Alocacao::operator==(const Alocacao &rhs) const {
    return clienteId == rhs.clienteId &&
           dataInicial == rhs.dataInicial &&
           dataFinal == rhs.dataFinal &&
           filmeId == rhs.filmeId &&
           valor == rhs.valor;
}

bool Alocacao::operator!=(const Alocacao &rhs) const {
    return !(rhs == *this);
}

void Alocacao::setDataInicial(boost::gregorian::date data) {
    Alocacao::dataInicial = toMillisecondsEpoch(data);
}

void Alocacao::setDataFinal(boost::gregorian::date data) {
    Alocacao::dataFinal = toMillisecondsEpoch(data);
}

void Alocacao::setPeriodo(boost::gregorian::date_period periodo) {
    Alocacao::setDataInicial(periodo.begin());
    Alocacao::setDataFinal(periodo.end());
}

void Alocacao::init() {
    Alocacao::periodoAlocacao = boost::gregorian::date_period(to_bdate(dataInicial), to_bdate(dataFinal));
    Alocacao::filme = dbInstance->getStorage().get<Filme>(filmeId);
    Alocacao::cliente = dbInstance->getStorage().get<Cliente>(clienteId);
}



