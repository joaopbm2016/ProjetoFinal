#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

int Cadastro::verificarCadastro(string _nome,string _usuario, int _ID)
{
    json usuarios = carregarUsuarios();
    for(const auto& usuario : usuarios) {
    	if (usuario.contains("nome") && usuario["nome"] == _nome)
		{
    		return 1;
    	}
    	if (usuario.contains("usuario") && usuario["usuario"] == _usuario)
		{
    		return 2;
    	}
		if (usuario.contains("ID") && usuario["ID"] == _ID)
		{
    		return 3;
    	}
    }
    return 0;
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
	IDCadastro = maiorID()+1;
	int erro = verificarCadastro(nomeCadastro, usuarioCadastro, IDCadastro);
	switch(erro){
		case 0:
			pushCadastro();
			break;
		case 1:
			cout << "nome já cadastrado." << endl;
			break;
		case 2:
			cout << "login já cadastrado." << endl;
			break;
		case 3:
			cout << "ID já Existente." << endl;
			break;
		default:
			cout<<"erro não identificado!"<<endl;
			break;
	}
}	

void Cadastro::pushCadastro()
{
	json usuarios = carregarUsuarios();

		usuarios.push_back({
			{"nome", nomeCadastro},
		    {"usuario", usuarioCadastro},
			{"senha", senhaCadastro},
			{"ID", IDCadastro}
		});
		cout<<usuarios.dump(4)<<endl;
		ofstream arquivo("cadastro.json");
		if (!arquivo.is_open()) {
			cout << "Erro ao abrir o arquivo." << endl;
			return;
		}
		arquivo.close();
		cout << "Cadastro realizado com sucesso!" << endl;
}