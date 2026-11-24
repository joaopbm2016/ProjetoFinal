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
		    <<"ID: "<<item["ID"]<<endl
            <<"MOD: "<<item["MOD"]<<endl;
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

void UserManager::userMOD()
{
    int MODID;

    cout<<"qual usuario transformar em moderador?\n*escreva o ID*"<<endl;
    cin>>MODID;
    if(cin.fail())
    {
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (MODID==getID())
    {
        cout<<"\nVOCÊ JÁ É UM MODERADOR!\n"<<endl;
        return;
    }

    json users = carregarUsuarios();
    if(!users.is_array())
    {
        cout<<"Erro: cadastro.json nao contem uma lista de usuarios."<<endl;
        return;
    }

    bool encontrou = false;

    for (auto i = users.begin(); i!= users.end();i++)
    {
        if((*i)["ID"]==MODID)
        {
            if((*i)["MOD"]==true)
            {
                cout<< "ESSE USUÁRIO JÁ É UM MODERADOR!"<<endl;
                return;
            }
            (*i)["MOD"]=true;
            cout<<"MODERADOR ADICIONADO COM SUCESSO!"<<endl;
            encontrou = true;
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
		arquivo << users.dump(4);
		arquivo.close();
}

void UserManager::userDelMOD()
{
    int MODID;

    cout<<"qual usuario tirar poder moderador?\n*escreva o ID*"<<endl;
    cin>>MODID;
    if(cin.fail())
    {
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (MODID==getID())
    {
        cout<<"\nVOCÊ NÃO PODE TIRAR SEU PRÓPRIO MODERADOR!\n"<<endl;
        return;
    }

    json users = carregarUsuarios();
    if(!users.is_array())
    {
        cout<<"Erro: cadastro.json nao contem uma lista de usuarios."<<endl;
        return;
    }

    bool encontrou = false;

    for (auto i = users.begin(); i!= users.end();i++)
    {
        if((*i)["ID"]==MODID)
        {
            if((*i)["MOD"]==false)
            {
                cout<< "ESSE USUÁRIO NÃO ERA UM MODERADOR!"<<endl;
                return;
            }
            (*i)["MOD"]=false;
            cout<<"MODERADOR REMOVIDO COM SUCESSO!"<<endl;
            encontrou = true;
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
		arquivo << users.dump(4);
		arquivo.close();
}