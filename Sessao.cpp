#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

bool Sessao::getLogado()
{
	return logado;
}

void Sessao::getLogin()
{
	if(!logado)
	{
		cout<<"login: "<<getLogado()<<endl;
		return;
	}
	cout<<"nome: "<<nome<<endl
		<<"usuario: "<<usuario<<endl
		<<"ID: "<<ID<<endl
		<<"logado: "<<getLogado()<<endl;
}

int Sessao::getID()
{
	return ID;
}

void Sessao::setNome(string nomeSet)
{
	nome = nomeSet;
}
void Sessao::setUser(string userSet)
{
	usuario = userSet;
}
void Sessao::setSenha(string senhaSet)
{
	senha = senhaSet;
}

void Sessao::setID(int IDSet)
{
	ID = IDSet;
}

int Sessao::maiorID()//verificar se o ID já esta uso
{
	json dados = carregarUsuarios();

	int maiorID = 0;

	for (auto i : dados)
	{
		if (i.contains("ID") && i["ID"].is_number_integer() && maiorID < i["ID"].get<int>())
		{
			maiorID = i["ID"].get<int>();
		}
	}

	return maiorID;
}

json Sessao::carregarUsuarios()
{
    json usuarios = json::array();
	ifstream arquivo("cadastro.json");
    if (arquivo.is_open()) {
    	try {
    		arquivo >> usuarios;
    	} catch (const json::parse_error&) {
    		usuarios = json::array();
    	}
		if (!usuarios.is_array())
		{
    		usuarios = json::array();
    	}
    	
    	arquivo.close();
    }
	ofstream arquivoSaida("cadastro.json");
    if (arquivoSaida.is_open()) {
    	arquivoSaida << usuarios.dump(4);
    }
    arquivoSaida.close();
    return usuarios;
}

string Sessao::cript(string IN,int codecod)
{
    string OUT;
    OUT.reserve(IN.size());

	string alfabeto = "abcdefghijklmnopqrstuvwxyz"
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
                  "0123456789";

	string aleatorio = "H3hkXIP8bSqMQD2vdwOW5TnpjZ"
                "0gYAre7yJ CuR1foLiU6szEmF4V"
                "cB9xtNlaGK";

	size_t i=0;
	if (codecod==1)
	{
		while (i<IN.size())
		{
			size_t index = alfabeto.find(IN[i]);
			if (index == string::npos)
			{
				return string();
			}
			OUT.push_back(aleatorio[index]);
			i++;
		}
		return OUT;
    }else
	{
		while (i < IN.size())
		{
			size_t index = aleatorio.find(IN[i]);
			if (index == string::npos)
			{
				return string();
			}
			OUT.push_back(alfabeto[index]);
			i++;
		}
		return OUT;
    }
}