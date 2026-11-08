#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

bool Cadastro::verificarCadastro(string _nome,string _usuario, int _ID)
{
    json usuarios = carregarUsuarios();
    for(const auto& usuario : usuarios) {
    	if (usuario.contains("nome") && usuario["nome"] == _nome)
		{
    		cout << "nome já cadastrado." << endl;
    		return false;
    	}
    	if (usuario.contains("usuario") && usuario["usuario"] == _usuario)
		{
    		cout << "login já cadastrado." << endl;
    		return false;
    	}
		if (usuario.contains("ID") && usuario["ID"] == _ID)
		{
    		cout << "ID já Existente." << endl;
    		return false;
    	}
    }
    return true;
}

void Cadastro::cadastro()
{

	cout<< "Cadastro selecionado." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"Digite seu nome: ";
	getline(cin, nomeCadastro);
	cout<<"Digite seu usuario: ";
	cin>> usuarioCadastro;
	cout<<"Digite sua senha: ";
	cin>> senhaCadastro;
	senhaCadastro=cript(senhaCadastro,1); 
	IDCadastro = totalIDs()+1;
	if (verificarCadastro(nomeCadastro, usuarioCadastro, IDCadastro))
	{
		json usuarios = carregarUsuarios();

		usuarios.push_back({
			{"nome", nomeCadastro},
		    {"usuario", usuarioCadastro},
			{"senha", senhaCadastro},
			{"ID", IDCadastro}
		});
		ofstream arquivo("cadastro.json");
		if (!arquivo.is_open()) {
			cout << "Erro ao abrir o arquivo." << endl;
			return;
		}
		arquivo << usuarios.dump(4);
		arquivo.close();
		cout << "Cadastro realizado com sucesso!" << endl;
	}
}