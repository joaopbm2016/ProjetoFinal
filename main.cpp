#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "Sessao.h"

using json = nlohmann::json;
using namespace std;

string usuarioAtual;

void userManager()
{
	if(!Sessao::getLogado())
	{
		cout<<"VOCÊ NÃO ESTA LOGADO!\n"
			<<"VOLTANDO PARA MENU..."<<endl;
		return;
	}

	UserManager manager;

	
	int choice;
	do{
		cout<<"=========================\n"
		<<" GERENCIADOR DE USUARIOS\n"
		<<"=========================\n"
		<< "1 - Mostrar seu usuario\n"
		<< "2 - Mostrar usuarios\n"
		<< "3 - Deletar usuario\n"
		<< "4 - Voltar"<<endl;
		cin>> choice;
		switch (choice)
		{
			case 1:
				cout<<"========================="<<endl;
				Sessao::getLogin();
				break;
			case 2:
				cout<<"========================="<<endl;
				manager.getUsers();
				break;
			case 3:
			manager.deleteUser();
				cout<<"========================="<<endl;
				break;
			case 4:
				cout<<"VOLTANDO PARA MENU PRINCIPAL...\n"<<endl;
			default:
				break;
		}
	}while(choice!=4);
}

void productManager()
{
	
}

int Menu()
{
	cout<<"======================\n"
		<<" FARMACIA GERENCIATOR\n"
		<<"======================\n"
		<< "1 - CADASTRO\n"
		<< "2 - LOGIN\n"
		<< "3 - GERENCIAR USUARIOS\n"
		<< "4 - GERENCIAR PRODUTOS\n"
		<< "5 - SAIR"<<endl;
	int choice;
	cin>> choice;
	return choice;
}

int main() {
	//Sessao usuario;
	int choice=0;
	while (choice!=5) {
		choice = Menu();
		switch (choice) {
			case 1: {
				cout<<"========================="<<endl;
				Cadastro cadastro;
				cadastro.cadastro();
				break;
			}
			case 2: {
				cout<<"========================="<<endl;
				Login login;
				login.login();
				break;
			}
			case 3: {				
				userManager();
				break;
			}
			case 4:
				cout<<"Gerenciador de produtos"<<endl;
				
				break;	

			case 5:
				cout << "Saindo..." << endl;
				break;
			default:
				cout << "Opção inválida." << endl;
				break;
		}
	}
	return 0;
}