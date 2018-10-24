#include <utility>

#include <utility>

//
// Created by aluno on 17/10/18.
//

#include <imgui.h>
#include "filme.h"
#include "../db/init.h"
#include "../utils/stringUtils.h"

#define BUFFER_SIZE 100

std::vector<char> generoBuffer(BUFFER_SIZE);
std::vector<char> sinopseBuffer(BUFFER_SIZE);
std::vector<char> anoBuffer(BUFFER_SIZE);
std::vector<char> nomeBuffer(BUFFER_SIZE);

std::shared_ptr<char> buffer(new char[512]);

std::vector<std::string> messageFields;

FilmeMenu::FilmeMenu() {
    FilmeMenu::filmes = dbInstance->getStorage().get_all<Filme>();
}

std::vector<Filme> FilmeMenu::getFilmes() {
    return FilmeMenu::filmes;
}

void FilmeMenu::refreshBuffers(){
    std::copy(FilmeMenu::atual.nome.begin(),FilmeMenu::atual.nome.end(), nomeBuffer.begin());
    std::copy(FilmeMenu::atual.anoLancamento.begin(),FilmeMenu::atual.anoLancamento.end(), anoBuffer.begin());
    std::copy(FilmeMenu::atual.genero.begin(),FilmeMenu::atual.genero.end(), generoBuffer.begin());
    std::copy(FilmeMenu::atual.sinopse.begin(),FilmeMenu::atual.sinopse.end(), sinopseBuffer.begin());

    std::fill(nomeBuffer.begin() + FilmeMenu::atual.nome.size(), nomeBuffer.end(), '\0');
    std::fill(anoBuffer.begin() + FilmeMenu::atual.anoLancamento.size(), anoBuffer.end(), '\0');
    std::fill(generoBuffer.begin() + FilmeMenu::atual.genero.size(), generoBuffer.end(), '\0');
    std::fill(sinopseBuffer.begin() + FilmeMenu::atual.sinopse.size(), sinopseBuffer.end(), '\0');
}

void removeDuplicates(std::string &b){
    messageFields.erase(std::remove_if(messageFields.begin(), messageFields.end(), [b](std::string a){
        return a == b;
    }), messageFields.end());
}

bool validateFields(){
    std::string message;

    message = "O campo nome não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&nomeBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    message = "O campo ano não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&anoBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    message = "O campo genero não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&generoBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    message = "O campo sinopse não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&sinopseBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }


    return true;
}

bool contains(std::string first, const std::string &second){
    return findByRegex(std::move(first), second);
}

void FilmeMenu::render() {
    bool& open = FilmeMenu::open;

    ImGui::SetNextWindowSize(ImVec2(600,500),0);

    ImGui::Begin("Filmes", &open);

    refreshBuffers();

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

        for(const auto &str : messageFields){
            ImGui::Text(str.c_str());
        }

        if(editando){
            if(ImGui::Button("Editar Filme")){
                if(validateFields()) {
                    FilmeMenu::editando = false;
                    dbInstance->getStorage().update<Filme>(FilmeMenu::atual);
                    updateFilmes();

                    clearFilme();
                }
            }
        } else {
            if(ImGui::Button("Salvar Filme")){
                if(validateFields()){
                    dbInstance->getStorage().insert<Filme>(FilmeMenu::atual);
                    updateFilmes();

                    clearFilme();
                }
            }
        }
    }

    ImGui::Separator();
    ImGui::Separator();

    ImGui::Text("Pesquisar: ");
    ImGui::InputText("Pesquisar", buffer.get(), 512);

    {
        std::string filter = buffer.get();

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("Child2", ImVec2(0,300));

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Columns(7);
        std::vector<Filme> filtered(FilmeMenu::filmes.capacity());

        std::copy_if(FilmeMenu::filmes.begin(), FilmeMenu::filmes.end(), filtered.begin(), [filter](Filme filme) {
            return filter.empty()                                      ? true :
                   contains(filter, std::to_string(filme.valor))  ? true :
                   contains(filter, filme.genero               )  ? true :
                   contains(filter, filme.nome                 )  ? true :
                   contains(filter, filme.sinopse              )  ? true :
                   contains(filter, filme.anoLancamento        );
        });

        for(auto filme: filtered){
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

            if(ImGui::Button("Alterar")){
                FilmeMenu::editando = true;
                FilmeMenu::atual = filme;
            }

            ImGui::NextColumn();

            if(ImGui::Button("Remover")){
                dbInstance->getStorage().remove<Filme>(filme.id);

                updateFilmes();

                if(FilmeMenu::editando)
                    FilmeMenu::editando = false;

                clearFilme();
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    ImGui::TreePop();

}

void FilmeMenu::editMenu(Filme filme){
   ImGui::OpenPopup("Gerenciar Filme");

        if (ImGui::Selectable("Deletar Filme")){
            dbInstance->getStorage().remove<Filme>(filme.id);

            updateFilmes();
        }

        if (ImGui::Selectable("Alterar Filme")){
            FilmeMenu::editando = true;
            FilmeMenu::atual = filme;
        }

        ImGui::PushItemWidth(-1);
        ImGui::PopItemWidth();
        ImGui::EndPopup();
}

bool FilmeMenu::isOpen() const {
    return open;
}

void FilmeMenu::setOpen(bool open) {
    FilmeMenu::open = open;
}

void FilmeMenu::updateFilmes() {
    FilmeMenu::filmes = dbInstance->getStorage().get_all<Filme>();
}

void FilmeMenu::clearFilme() {
    FilmeMenu::atual = Filme();
}
