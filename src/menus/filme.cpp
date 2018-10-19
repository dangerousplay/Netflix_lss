//
// Created by aluno on 17/10/18.
//

#include <imgui.h>
#include "filme.h"
#include "../db/init.h"

#define BUFFER_SIZE 100

std::vector<char> generoBuffer(BUFFER_SIZE);
std::vector<char> sinopseBuffer(BUFFER_SIZE);
std::vector<char> anoBuffer(BUFFER_SIZE);
std::vector<char> nomeBuffer(BUFFER_SIZE);

FilmeMenu::FilmeMenu() {
    FilmeMenu::filmes = dbInstance->getStorage().get_all<Filme>();
}

std::vector<Filme> FilmeMenu::getFilmes() {
    return FilmeMenu::filmes;
}

/*if (ImGui::BeginPopupContextItem("item context menu"))
            {
                if (ImGui::Selectable("Set to zero")) value = 0.0f;
                if (ImGui::Selectable("Set to PI")) value = 3.1415f;
                ImGui::PushItemWidth(-1);
                ImGui::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
                ImGui::PopItemWidth();
                ImGui::EndPopup();
            }*/

void FilmeMenu::render() {
    bool& open = FilmeMenu::open;

    ImGui::SetNextWindowSize(ImVec2(400,500),0);

    ImGui::Begin("Filmes", &open);

    if(ImGui::CollapsingHeader("Cadastrar e Editar Filme")) {

        ImGui::Text("Nome:");

        if(ImGui::InputText("Nome", &nomeBuffer[0], nomeBuffer.size())){
            FilmeMenu::atual.nome = &nomeBuffer[0];
        }

        ImGui::Text("Ano:");

        if(ImGui::InputText("Ano", &anoBuffer[0], anoBuffer.size())){
            FilmeMenu::atual.anoLancamento = &anoBuffer[0];
        }

        ImGui::Text("Sinopse:");

        if(ImGui::InputText("Sinopse", &sinopseBuffer[0], sinopseBuffer.size())){
            FilmeMenu::atual.sinopse = &sinopseBuffer[0];
        }

        ImGui::Text("Genero:");

        if(ImGui::InputText("Genero", &generoBuffer[0], generoBuffer.size())){
            FilmeMenu::atual.genero = &generoBuffer[0];
        }

        ImGui::Text("Valor:");
        ImGui::InputDouble("Valor", &FilmeMenu::atual.valor);

        if(editando){
            if(ImGui::Button("Editar Filme")){
                FilmeMenu::editando = false;

                //TODO Implement Save Logic
            }
        } else {
            if(ImGui::Button("Salvar Filme")){
                //TODO Implement Save Logic
            }
        }
    }

    ImGui::Separator();
    ImGui::Separator();

    char* buffer = (char*)calloc(512, sizeof(char));

    ImGui::Text("Pesquisar: ");
    ImGui::InputText("Pesquisar", buffer, 512);

    {

        std::string filter = buffer;

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0,300));
        /*if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }*/

        ImGui::Columns(5);
        std::vector<Filme> filtered;

        std::copy_if(FilmeMenu::filmes.begin(), FilmeMenu::filmes.end(), &filtered[0], [filter](Filme filme){
            return filter.empty() ? true :
            filter.find(std::to_string(filme.valor)) ? true :
            filter.find(filme.genero) ? true :
            filter.find(filme.nome) ? true :
            filter.find(filme.sinopse) ? true :
            filter.find(filme.anoLancamento) != 0;

        });

        for (int i = 0; i < 100; i++)
        {
            char buf[32];
            sprintf(buf, "%03d", i);
            ImGui::Button(buf, ImVec2(-1.0f, 0.0f));
            ImGui::NextColumn();
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    ImGui::TreePop();

}

bool FilmeMenu::isOpen() const {
    return open;
}

void FilmeMenu::setOpen(bool open) {
    FilmeMenu::open = open;
}
