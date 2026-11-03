#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "Sessao.h"

using json = nlohmann::json;
using namespace std;


int Menu()
{
	cout<<"===================\n"
		<<" CADASTRO E LOGIN\n"
		<<"===================\n"
		<< "1. CADASTRO\n"
		<< "2. LOGIN\n"
		<< "3. GERENCIAR\n"
		<< "4. SAIR"<<endl;
	int choice;
	cin>> choice;
	return choice;
}

int main() {
	Sessao usuario;
	int choice=0;
	while (choice!=4) {
		choice = Menu();
		switch (choice) {
			case 1: {
				Cadastro cadastro;
				cadastro.cadastro();
				break;
			}
			case 2: {
				Login login;
				login.login();
				break;
			}
			case 3: {
				cout << "Gerenciar selecionado." << endl;
				cout << Sessao::GetLogado() << endl;
				break;
			}
			case 4:
				cout << "Saindo..." << endl;
				break;	
			default:
				cout << "Opção inválida." << endl;
				break;
		}
	}
	return 0;
}