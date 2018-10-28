//
// Created by aluno on 17/10/18.
//

#include "cliente.h"
#include <vector>
#include <imgui.h>
#include <memory>
#include "../db/init.h"
#include "../utils/stringUtils.h"

const std::vector<Cliente> &ClienteMenu::getClientes() const {
    return clientes;
}

void ClienteMenu::updateClientes() {
    ClienteMenu::clientes = dbInstance->getStorage().get_all<Cliente>();

    globalHandler.callUpdate();
}

void ClienteMenu::clearCliente() {
    ClienteMenu::atual = Cliente();
    std::fill(enderecoBuffer.begin(), enderecoBuffer.end(), '\0');
    std::fill(cpfBuffer.begin(), cpfBuffer.end(), '\0');
    std::fill(nomeBuffer.begin(), nomeBuffer.end(), '\0');
}

void ClienteMenu::refreshBuffers(){
    std::copy(ClienteMenu::atual.nome.begin(), ClienteMenu::atual.nome.end(), nomeBuffer.begin());
    std::copy(ClienteMenu::atual.cpf.begin(),ClienteMenu::atual.cpf.end(), cpfBuffer.begin());
    std::copy(ClienteMenu::atual.endereco.begin(), ClienteMenu::atual.endereco.end(), enderecoBuffer.begin());

    std::fill(nomeBuffer.begin() + ClienteMenu::atual.nome.size(), nomeBuffer.end(), '\0');
    std::fill(cpfBuffer.begin() + ClienteMenu::atual.cpf.size(), cpfBuffer.end(), '\0');
    std::fill(enderecoBuffer.begin() + ClienteMenu::atual.endereco.size(), enderecoBuffer.end(), '\0');
}

void ClienteMenu::removeDuplicates(std::string &b){
    messageFields.erase(std::remove_if(messageFields.begin(), messageFields.end(), [b](std::string a){
        return a == b;
    }), messageFields.end());
}


ClienteMenu::ClienteMenu() {
    updateClientes();
}

bool ClienteMenu::validateFields() {
    std::string message;

    message = "O campo nome não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&nomeBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    message = "O campo CPF não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&cpfBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    message = "O campo endereco não pode ser vazio";
    removeDuplicates(message);

    if(std::string(&enderecoBuffer[0]).empty()){
        messageFields.push_back(message);
        return false;
    }

    return true;
}




void ClienteMenu::render() {

    ImGui::SetNextWindowSize(ImVec2(600,500),0);

    ImGui::Begin("Clientes");

    refreshBuffers();

    if(ImGui::CollapsingHeader("Cadastrar e editar clientes")){

        ImGui::Text("Nome:");

        if(ImGui::InputText("Nome", &nomeBuffer[0], nomeBuffer.size())){
            ClienteMenu::atual.nome = &nomeBuffer[0];
        }

        ImGui::Text("CPF: ");

        if(ImGui::InputText("CPF", &cpfBuffer[0], cpfBuffer.size())){
            ClienteMenu::atual.cpf = &cpfBuffer[0];
        }

        ImGui::Text("Endereco: ");

        if(ImGui::InputText("Endereco", &enderecoBuffer[0], enderecoBuffer.size())){
            ClienteMenu::atual.endereco = &enderecoBuffer[0];
        }

        for(const auto &str : messageFields){
            ImGui::Text(str.c_str());
        }

        if(ClienteMenu::editando){
            if(ImGui::Button("Editar Cliente")){
                if(validateFields()) {
                    ClienteMenu::editando = false;
                    dbInstance->getStorage().update<Cliente>(ClienteMenu::atual);
                    updateClientes();

                    clearCliente();
                }
            }
        } else {
            if(ImGui::Button("Salvar Cliente")){
                if(validateFields()){
                    dbInstance->getStorage().insert<Cliente>(ClienteMenu::atual);
                    updateClientes();

                    clearCliente();
                }
            }
        }
    }

    ImGui::Separator();
    ImGui::Separator();

    ImGui::Text("Pesquisar: ");
    ImGui::InputText("Pesquisar", bufferPesquisa.get(), 512);

    {

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



        std::string filter = bufferPesquisa.get();
        std::vector<Cliente> filtered(ClienteMenu::clientes.capacity());
        Cliente cliente = ClienteMenu::atual;

        std::copy_if(ClienteMenu::clientes.begin(), ClienteMenu::clientes.end(), filtered.begin(), [filter,cliente](Cliente cliente) {
            return filter.empty()                                      ? true :
                   contains(filter, cliente.endereco              )    ? true :
                   contains(filter, cliente.nome                  )    ? true :
                   contains(filter, cliente.cpf                   );
        });

        ImGui::Columns(5);

        for(auto cliente: filtered){
            ImGui::PushID(cliente.id);

            ImGui::Text(cliente.nome.c_str());

            ImGui::NextColumn();

            ImGui::Text(cliente.cpf.c_str());

            ImGui::NextColumn();

            ImGui::Text(cliente.endereco.c_str());

            ImGui::NextColumn();

            if(ImGui::Button("Alterar")){
                ClienteMenu::editando = true;
                ClienteMenu::atual = cliente;
            }

            ImGui::NextColumn();

            if(ImGui::Button("Remover")){
                dbInstance->getStorage().remove<Cliente>(cliente.id);

                updateClientes();

                if(ClienteMenu::editando)
                    ClienteMenu::editando = false;

                clearCliente();
            }

            ImGui::NextColumn();

            ImGui::PopID();
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    ImGui::TreePop();

}




