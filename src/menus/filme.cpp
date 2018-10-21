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

template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc)
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(),
                                                 str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}

int contains(const std::string &first, const std::string &second){
    return ci_find_substr(first, second, std::locale());
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

        if(editando){
            if(ImGui::Button("Editar Filme")){
                FilmeMenu::editando = false;
                dbInstance->getStorage().update<Filme>(FilmeMenu::atual);
                updateFilmes();

                clearFilme();
            }
        } else {
            if(ImGui::Button("Salvar Filme")){
                dbInstance->getStorage().insert<Filme>(FilmeMenu::atual);
                updateFilmes();

                clearFilme();
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
                   contains(filter, std::to_string(filme.valor)) != -1 ? true :
                   contains(filter, filme.genero               ) != -1 ? true :
                   contains(filter, filme.nome                 ) != -1 ? true :
                   contains(filter, filme.sinopse              ) != -1 ? true :
                   contains(filter, filme.anoLancamento        ) != -1;
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
