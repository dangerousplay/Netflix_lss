//
// Created by dangerous on 26/10/18.
//

#include <imgui.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "relatorio.h"
#include "../db/init.h"
#include "../utils/unixTime.h"
#include "../services/relatorio.h"
#include <fstream>

void RelatorioMenu::render() {

    ImGui::Begin("Relatórios");

    ImGui::Text("Gere o seu relatório mensal e salve o mesmo em um local adequado");

    static std::shared_ptr<char> buffer = std::shared_ptr<char>((char *) calloc(501, sizeof(char)));

    ImGui::InputText("Local relatorio", buffer.get(), 500);

    if (ImGui::Button("Salvar relatório")) {
        auto day = boost::gregorian::day_clock::local_day();

        auto monthDate = boost::gregorian::date(day.year(), day.month(), 1);

        auto allocacoes = dbInstance->getStorage().get_all<Alocacao>(
                where(c(&Alocacao::dataInicial) >= toMillisecondsEpoch(monthDate)));

        if (allocacoes.empty()) {
            return;
        }

        for (auto &aloc: allocacoes) {
            aloc.init();
        }

        ServicoRelatorio relatorio = ServicoRelatorio();

        try {
            auto pdf = relatorio.gerarRelatorio(allocacoes);

            std::fstream file(buffer.get());

            file.write((const char *) pdf.r0, pdf.r1);

            file.flush();

            file.close();
        } catch (std::exception &e) {
            std::cout << e.what();
        }
    }








}
