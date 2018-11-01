//
// Created by aluno on 17/10/18.
//

#include <imgui.h>
#include "alocacao.h"
#include "../utils/stringUtils.h"
#include "../utils/unixTime.h"
#include "../db/init.h"
#include "../services/alocacao.h"

AlocacaoMenu::AlocacaoMenu() {
    AlocacaoMenu::filmes = servicoLocadora.getAllFimesNotAllocated();
    AlocacaoMenu::alocacoes = dbInstance->getStorage().get_all<Alocacao>();
    AlocacaoMenu::clientes = dbInstance->getStorage().get_all<Cliente>();

    for (auto aloc: alocacoes) {
        aloc.init();
    }

    auto instance = this;

    globalHandler.registerOnUpdate([instance]() {
        instance->updateAlocacoes();
    });
}

void AlocacaoMenu::refreshBuffers() {

}

double AlocacaoMenu::sumFilmValues() {
    double sum = 0;

    for (auto filme: filmeSelecionados) {
        sum += filme.valor;
    }

    return sum;
}


int AlocacaoMenu::findClienteByName(const char *name) {
    auto it = std::find_if(clientes.begin(), clientes.end(), [name](Cliente cliente) -> bool {
        return cliente.nome == name;
    });

    return it[0].id;
}

Filme AlocacaoMenu::findFilmeByName(const char *name) {
    auto it = std::find_if(filmes.begin(), filmes.end(), [name](Filme filme) -> bool {
        return filme.nome == name;
    });

    return it[0];
}

void AlocacaoMenu::updateAlocacoes() {
    AlocacaoMenu::alocacoes = dbInstance->getStorage().get_all<Alocacao>();
    AlocacaoMenu::filmes = servicoLocadora.getAllFimesNotAllocated();
    AlocacaoMenu::clientes = dbInstance->getStorage().get_all<Cliente>();

    for (auto aloc: alocacoes) {
        aloc.init();
    }
}

void AlocacaoMenu::clearAlocacao() {
    AlocacaoMenu::filmeSelecionados.clear();
    AlocacaoMenu::atual = Alocacao();
    AlocacaoMenu::dataInicialBuffer = std::shared_ptr<char>((char*)calloc(501, sizeof(char)));
    AlocacaoMenu::dataFinalBuffer = std::shared_ptr<char>((char*)calloc(501, sizeof(char)));
}

void AlocacaoMenu::render() {
    ImGui::SetNextWindowSize(ImVec2(900, 500), 0);

    ImGui::Begin("Alocação");

    refreshBuffers();

    if (ImGui::CollapsingHeader("Cadastrar e Editar alocação")) {
        std::vector<const char *> clientesStr;
        std::vector<const char *> filmesStr;

        static int currentItemCliente = 0;
        static int currentItemFilme = 0;

        for (const auto &cliente: clientes) {
            clientesStr.push_back(cliente.nome.c_str());
        }

        for (const auto &filme: filmes) {
            filmesStr.push_back(filme.nome.c_str());
        }

        std::vector<const char *> filteredCliente;
        std::vector<const char *> filteredFilme;

        ImGui::Text("Filtar clientes por nome: ");

        if (ImGui::InputText("Filtrar clientes", AlocacaoMenu::clienteBuffer.get(), 500)) {

        }

        auto bufferFilter = AlocacaoMenu::clienteBuffer;

        std::copy_if(clientesStr.begin(), clientesStr.end(), std::back_inserter(filteredCliente),
                     [&bufferFilter](const char *nome) -> bool {
                         std::string str(bufferFilter.get());

                         return str.empty() ? true :
                                contains(str, std::string(nome));
                     });

        if (ImGui::Combo("Cliente", &currentItemCliente, &filteredCliente[0], filteredCliente.size())) {
            AlocacaoMenu::atual.clienteId = findClienteByName(filteredCliente[currentItemCliente]);
        }

        ImGui::Text("Filtar filmes por nome: ");

        if (ImGui::InputText("Filtrar filmes", AlocacaoMenu::filmeBuffer.get(), 500)) {

        }

        auto bufferFilmeFilter = AlocacaoMenu::filmeBuffer;

        std::copy_if(filmesStr.begin(), filmesStr.end(), std::back_inserter(filteredFilme),
                     [&bufferFilmeFilter](const char *nome) -> bool {
                         std::string str(bufferFilmeFilter.get());

                         return str.empty() ? true :
                                contains(str, std::string(nome));
                     });

        ImGui::Combo("Filme", &currentItemFilme, &filteredFilme[0], filteredFilme.size());

        ImGui::SameLine();

        if (ImGui::Button("Adicionar")) {
            auto selected = findFilmeByName(filteredFilme[currentItemFilme]);

            if (std::find(filmeSelecionados.begin(), filmeSelecionados.end(), selected) == filmeSelecionados.end())
                filmeSelecionados.push_back(selected);
        }

        ImGui::Text("Filmes alocados: ");

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0, 300));

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        for (int i = 0; i < 6; i++) {
            ImGui::Spacing();
        }

        ImGui::Separator();

        ImGui::Columns(6);

        for (auto filme: filmeSelecionados) {
            ImGui::PushID(filme.id);

            ImGui::Text(filme.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(filme.anoLancamento.c_str());

            ImGui::NextColumn();

            ImGui::Text(filme.sinopse.c_str());

            ImGui::NextColumn();

            ImGui::Text(filme.genero.c_str());

            ImGui::NextColumn();

            ImGui::Text(std::to_string(filme.valor).c_str());

            ImGui::NextColumn();

            if (ImGui::Button("Remover")) {
                filmeSelecionados.erase(std::remove(filmeSelecionados.begin(), filmeSelecionados.end(), filme),
                                        filmeSelecionados.end());
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();

        ImGui::Text("Data Inicio: ");
        std::string exampleData = boost::gregorian::to_iso_extended_string(boost::gregorian::day_clock::local_day());

        ImGui::Text("Exemplo de formatação: %s", exampleData.c_str());

        if (ImGui::InputText("Data Inicio", dataInicialBuffer.get(), 500)) {
            try {
                auto dataIn = boost::gregorian::date_from_iso_string(
                        replaceSeparator(std::string(dataInicialBuffer.get())));
                AlocacaoMenu::atual.dataInicial = toMillisecondsEpoch(dataIn);
            } catch (std::exception &e) {

            }
        }

        ImGui::Text("Data Final: ");
        ImGui::Text("Exemplo de formatação: %s", exampleData.c_str());

        if (ImGui::InputText("Data Final", dataFinalBuffer.get(), 500)) {
            try {
                auto dataIn = boost::gregorian::date_from_iso_string(
                        replaceSeparator(std::string(dataFinalBuffer.get())));
                AlocacaoMenu::atual.dataFinal = toMillisecondsEpoch(dataIn);
            } catch (std::exception &e) {

            }
        }

        ImGui::Text("Valor total da alocação: %f", sumFilmValues());

        for (auto message: messageFields) {
            ImGui::Text(message.c_str());
        }

        if (AlocacaoMenu::editando) {
            if (ImGui::Button("Editar")) {
                if (validateFields()) {
                    AlocacaoMenu::atual.clienteId = findClienteByName(filteredCliente[currentItemCliente]);

                    dbInstance->getStorage().update<Alocacao>(AlocacaoMenu::atual);

                    AlocacaoMenu::updateAlocacoes();
                    AlocacaoMenu::clearAlocacao();
                }
            }
        } else {
            if (ImGui::Button("Salvar")) {
                if (validateFields()) {
                    AlocacaoMenu::atual.clienteId = findClienteByName(filteredCliente[currentItemCliente]);

                    servicoLocadora.alocarFilmes(AlocacaoMenu::atual, filmeSelecionados);

                    AlocacaoMenu::updateAlocacoes();
                    AlocacaoMenu::clearAlocacao();
                }
            }
        }
    }

    if (ImGui::CollapsingHeader("Pesquisar Alocações")) {
        ImGui::Text("Pesquisar: ");
        ImGui::InputText("Pesquisar", bufferPesquisaF.get(), 512);

        std::string filter = bufferPesquisaF.get();

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0, 300));

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        for (int i = 0; i < 6; i++) {
            ImGui::Spacing();
        }

        ImGui::Separator();

        ImGui::Columns(9);
        std::vector<Alocacao> filtered;

        std::copy_if(AlocacaoMenu::alocacoes.begin(), AlocacaoMenu::alocacoes.end(), std::back_inserter(filtered),
                     [filter](Alocacao alocacao) {
                         return filter.empty() ? true :
                                contains(filter, std::to_string(alocacao.valor)) ? true :
                                contains(filter, alocacao.filme.nome) ? true :
                                contains(filter, alocacao.cliente.nome) ? true :
                                contains(filter, boost::gregorian::to_iso_string(alocacao.periodoAlocacao.begin()))
                                ? true :
                                contains(filter, boost::gregorian::to_iso_string(alocacao.periodoAlocacao.end()));
                     });

        for (auto alocacao: filtered) {
            alocacao.init();

            ImGui::PushID(alocacao.id);

            ImGui::Text(alocacao.cliente.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(alocacao.filme.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_extended_string(alocacao.periodoAlocacao.begin()).c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_extended_string(alocacao.periodoAlocacao.end()).c_str());

            ImGui::NextColumn();

            ImGui::Text(std::to_string(alocacao.valor).c_str());

            ImGui::NextColumn();

            ImGui::Text("Paga: %s", alocacao.paga ? "Sim" : "Não");

            ImGui::NextColumn();

            if (ImGui::Button("Alterar")) {
                AlocacaoMenu::atual = alocacao;
                filmeSelecionados = {alocacao.filme};

                auto dataInicial = boost::gregorian::to_iso_extended_string(alocacao.periodoAlocacao.begin());
                auto dataFinal = boost::gregorian::to_iso_extended_string(alocacao.periodoAlocacao.end());

                std::shared_ptr<char> sDataInicial = std::shared_ptr<char>((char*)calloc(501, sizeof(char)));

                dataInicial.copy(sDataInicial.get(), dataInicial.size());

                std::shared_ptr<char> sDataFinal = std::shared_ptr<char>((char*)calloc(501, sizeof(char)));

                dataFinal.copy(sDataFinal.get(), dataFinal.size());

                AlocacaoMenu::editando = true;
                AlocacaoMenu::dataInicialBuffer = sDataInicial;
                AlocacaoMenu::dataFinalBuffer = sDataFinal;
            }

            ImGui::NextColumn();

            if (ImGui::Button("Remover")) {
                dbInstance->getStorage().remove<Alocacao>(alocacao.id);

                updateAlocacoes();

                if (AlocacaoMenu::editando)
                    AlocacaoMenu::editando = false;

                clearAlocacao();
            }

            ImGui::NextColumn();

            if (ImGui::Button("Pagar") && !alocacao.paga) {
                alocacao.paga = true;

                dbInstance->getStorage().update(alocacao);

                updateAlocacoes();

                if (AlocacaoMenu::editando)
                    AlocacaoMenu::editando = false;

                clearAlocacao();
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    ImGui::TreePop();
}

bool AlocacaoMenu::validateFields() {
    std::string message;

    message = "Deve haver amenos um filme alocado!";
    removeDuplicates(message);

    if (filmeSelecionados.empty()) {
        messageFields.push_back(message);
        return false;
    }

    message = "A data inicial deve conter um valor válido!";
    removeDuplicates(message);

    std::regex dateRegex{R"([0-9]{4}-[0-9]{2}-[0-9]{2})"};

    std::string dataInicial = std::string(dataInicialBuffer.get());
    std::string dataFinal = std::string(dataFinalBuffer.get());

    if (!std::regex_match(dataInicial, dateRegex)) {
        messageFields.push_back(message);
        return false;
    }

    message = "A data final deve conter um valor válido!";
    removeDuplicates(message);

    if (!std::regex_match(dataFinal, dateRegex)) {
        messageFields.push_back(message);
        return false;
    }

    boost::gregorian::date dateInicialG = boost::gregorian::date_from_iso_string(replaceSeparator(dataInicial));
    boost::gregorian::date dateFinalG = boost::gregorian::date_from_iso_string(replaceSeparator(dataFinal));

    message = "A data final e inicial deve, conter um periodo válido!";
    removeDuplicates(message);

    if (toMillisecondsEpoch(dateFinalG) <= toMillisecondsEpoch(dateInicialG)) {
        messageFields.push_back(message);
        return false;
    }

    return true;
}

void AlocacaoMenu::removeDuplicates(std::string &b) {
    messageFields.erase(std::remove_if(messageFields.begin(), messageFields.end(), [b](std::string a) {
        return a == b;
    }), messageFields.end());
}







