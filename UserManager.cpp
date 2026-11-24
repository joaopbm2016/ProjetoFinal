#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

void UserManager::getUsers()
{
    json usuarios = carregarUsuarios();
    for(const auto& item : usuarios)
    {
        cout<<"======================"<<endl
            <<"nome: "<<item["nome"]<<endl
		    <<"usuario: "<<item["usuario"]<<endl
		    <<"ID: "<<item["ID"]<<endl;
    }
}

void UserManager::deleteUser()
{
    int deleteID=0;
    cout<<"qual usuario deletar?\n*escreva o ID*"<<endl;
    cin>>deleteID;
    if(cin.fail())
    {
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (deleteID==getID())
    {
        cout<<"\nVOCÊ NÃO PODE DELETAR UM USUARIO QUE ESTA LOGADO!\n"<<endl;
        return;
    }
    json newusers = carregarUsuarios();
    if(!newusers.is_array())
    {
        cout<<"Erro: cadastro.json nao contem uma lista de usuarios."<<endl;
        return;
    }

    bool encontrou=false;
    for (auto it = newusers.begin(); it != newusers.end(); it++)
    {
        if((*it).contains("ID") && (*it)["ID"] == deleteID)
        {
            newusers.erase(it);
            encontrou=true;
            break;
        }
    }
    if(!encontrou)
    {
        cout<<"ID NÃO ENCONTRADO!"<<endl;
        return;
    }

    ofstream arquivo("cadastro.json");
    if (!arquivo.is_open()) {
			cout << "Erro ao abrir o arquivo." << endl;
			return;
		}
		arquivo << newusers.dump(4);
		arquivo.close();
}

bool UserManager::logout()
{
    if(!getLogado())
    {
        cout << "VOCÊ NÃO ESTA LOGADO!" << endl;
        return false;
    }

    logado = false;
    setNome("");
    setUser("");
    setSenha("");
    setID(0);
 
    return true;
}