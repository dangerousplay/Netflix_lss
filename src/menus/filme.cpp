//
// Created by aluno on 17/10/18.
//

#include <imgui.h>
#include "filme.h"

#define BUFFER_SIZE 100

FilmeMenu::FilmeMenu() {

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
    ImGui::Begin("Filmes");

    if(ImGui::CollapsingHeader("Cadastrar e Editar Filme")) {
        std::vector<char> generoBuffer(BUFFER_SIZE);
        std::vector<char> sinopseBuffer(BUFFER_SIZE);
        std::vector<char> anoBuffer(BUFFER_SIZE);
        std::vector<char> nomeBuffer(BUFFER_SIZE);

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

}
