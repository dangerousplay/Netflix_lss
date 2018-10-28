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
    AlocacaoMenu::todasAlocacoes = dbInstance->getStorage().get_all<Alocacao>();
    AlocacaoMenu::alocacoes = dbInstance->getStorage().get_all<Alocacao>(where(c(&Alocacao::paga) == false));
    AlocacaoMenu::clientes = dbInstance->getStorage().get_all<Cliente>();

    auto instance = this;

    globalHandler.registerOnUpdate([&instance]() {
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
    AlocacaoMenu::filmes = servicoLocadora.getAllFimesNotAllocated();
    AlocacaoMenu::todasAlocacoes = dbInstance->getStorage().get_all<Alocacao>();
    AlocacaoMenu::alocacoes = dbInstance->getStorage().get_all<Alocacao>(where(c(&Alocacao::paga) == false));
}

void AlocacaoMenu::clearAlocacao() {
    AlocacaoMenu::atual = Alocacao();
}

void AlocacaoMenu::render() {
    ImGui::SetNextWindowSize(ImVec2(600, 500), 0);

    ImGui::Begin("Alocação");

    refreshBuffers();

    if (ImGui::CollapsingHeader("Cadastrar e Editar alocação")) {
        std::vector<const char *> clientesStr;
        std::vector<const char *> filmesStr;

        int currentItemCliente = 0;
        int currentItemFilme = 0;

        for (const auto &cliente: clientes) {
            clientesStr.push_back(cliente.nome.c_str());
        }

        for (const auto &filme: filmes) {
            filmesStr.push_back(filme.nome.c_str());
        }

        std::vector<const char *> filteredCliente(clientesStr.capacity());
        std::vector<const char *> filteredFilme(filmesStr.capacity());

        ImGui::Text("Filtar clientes por nome: ");

        if (ImGui::InputText("Filtrar clientes", AlocacaoMenu::clienteBuffer.get(), 500)) {

        }

        auto bufferFilter = AlocacaoMenu::clienteBuffer;

        std::copy_if(clientesStr.begin(), clientesStr.end(), filteredCliente.begin(),
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

        std::copy_if(filmesStr.begin(), filmesStr.end(), filteredFilme.begin(),
                     [&bufferFilmeFilter](const char *nome) -> bool {
                         std::string str(bufferFilmeFilter.get());
                         return str.empty() ? true :
                                contains(str, std::string(nome));
                     });

        ImGui::Combo("Filme", &currentItemFilme, &filteredFilme[0], filteredFilme.size());

        ImGui::SameLine();

        if (ImGui::Button("Adicionar")) {
            filmeSelecionados.push_back(findFilmeByName(filteredFilme[currentItemCliente]));
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
                auto dataIn = boost::gregorian::date_from_iso_string(std::string(dataInicialBuffer.get()));
                AlocacaoMenu::atual.dataInicial = toMillisecondsEpoch(dataIn);
            } catch (std::exception &e) {

            }
        }

        ImGui::Text("Data Final: ");
        ImGui::Text("Exemplo de formatação: %s", exampleData.c_str());

        if (ImGui::InputText("Data Final", dataFinalBuffer.get(), 500)) {
            try {
                auto dataIn = boost::gregorian::date_from_iso_string(std::string(dataFinalBuffer.get()));
                AlocacaoMenu::atual.dataFinal = toMillisecondsEpoch(dataIn);
            } catch (std::exception &e) {

            }
        }

        ImGui::Text("Valor total da alocação: %f", sumFilmValues());

        if (AlocacaoMenu::editando) {
            if (ImGui::Button("Editar")) {
                dbInstance->getStorage().update<Alocacao>(AlocacaoMenu::atual);

                AlocacaoMenu::updateAlocacoes();
                AlocacaoMenu::clearAlocacao();
            }
        } else {
            if (ImGui::Button("Salvar")) {
                dbInstance->getStorage().insert<Alocacao>(AlocacaoMenu::atual);

                AlocacaoMenu::updateAlocacoes();
                AlocacaoMenu::clearAlocacao();
            }
        }
    }

    if (ImGui::CollapsingHeader("Pesquisar Alocações")) {

        ImGui::Text("Todas alocações: ");

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0, 300));

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Columns(8);

        for (auto alocacao: todasAlocacoes) {
            ImGui::PushID(alocacao.id);

            ImGui::Text(alocacao.cliente.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(alocacao.filme.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_string(alocacao.periodoAlocacao.begin()).c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_string(alocacao.periodoAlocacao.end()).c_str());

            ImGui::NextColumn();

            ImGui::Text(std::to_string(alocacao.valor).c_str());

            ImGui::NextColumn();

            ImGui::Text("Paga: %s", alocacao.paga ? "Sim" : "Não");

            ImGui::NextColumn();

            if (ImGui::Button("Alterar")) {
                AlocacaoMenu::atual = alocacao;
                filmeSelecionados = {alocacao.filme};

                AlocacaoMenu::editando = true;
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

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();

    }

    ImGui::Separator();
    ImGui::Separator();

    ImGui::Text("Pesquisar: ");
    ImGui::InputText("Pesquisar", bufferPesquisaF.get(), 512);

    {
        std::string filter = bufferPesquisaF.get();

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0, 300));

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Columns(8);
        std::vector<Alocacao> filtered(AlocacaoMenu::alocacoes.capacity());

        std::copy_if(AlocacaoMenu::alocacoes.begin(), AlocacaoMenu::alocacoes.end(), filtered.begin(),
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
            ImGui::PushID(alocacao.id);

            ImGui::Text(alocacao.cliente.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(alocacao.filme.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_string(alocacao.periodoAlocacao.begin()).c_str());

            ImGui::NextColumn();

            ImGui::Text(boost::gregorian::to_iso_string(alocacao.periodoAlocacao.end()).c_str());

            ImGui::NextColumn();

            ImGui::Text(std::to_string(alocacao.valor).c_str());

            ImGui::NextColumn();

            ImGui::Text("Paga: %s", alocacao.paga ? "Sim" : "Não");

            ImGui::NextColumn();

            if (ImGui::Button("Alterar")) {
                AlocacaoMenu::atual = alocacao;
                filmeSelecionados = {alocacao.filme};

                AlocacaoMenu::editando = true;
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

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    ImGui::TreePop();
}







