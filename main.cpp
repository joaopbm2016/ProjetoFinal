#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include <limits>
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
	if(!Sessao::getMOD())
	{
		cout<< " VOCÊ NÃO É UM MODERADOR!\nVOLTANDO PARA O MENU..."<<endl;
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
		<< "4 - Adicionar Moderador\n"
		<< "5 - Remover Moderador\n"
		<< "6 - logout\n"
		<< "7 - Voltar"<<endl;
		cin >> choice;
		if(cin.fail()){
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = 10;
    	}
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
				manager.userMOD();
				cout<<"========================="<<endl;
				break;
			case 5:
				manager.userDelMOD();
				cout<<"========================="<<endl;
				break;
			case 6:
				cout<<"========================="<<endl;
				if(manager.logout())
				{
					choice = 7;
					cout << "logout realizado com sucesso!"<< endl;
				}else{
					cout<<"logout não realizado"<< endl;
				}
				break;
			case 7:
				cout<<"VOLTANDO PARA MENU PRINCIPAL..."<<endl;
				break;
			default:
				cout<<"OPÇÃO INVALIDA!"<<endl;
				break;
		}
	}while(choice!=7);
}

void productManagerMenu()
{
	if(!Sessao::getLogado())
	{
		cout<<"VOCÊ NÃO ESTA LOGADO!\n"
			<<"VOLTANDO PARA MENU..."<<endl;
		return;
	}

	ProductsManager produtmanager;

	int choice;
	do{
		cout<<"=========================\n"
			<<" GERENCIADOR DE PRODUTOS\n"
			<<"=========================\n"
			<< "1 - Mostrar lista de produtos\n"
			<< "2 - Cadastrar novo produto\n"
			<< "3 - Deletar produto\n"
			<< "4 - Voltar"<<endl;
		cin>> choice;
		if(cin.fail()){
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = 10;
    	}
		switch (choice)
		{
			case 1:
				cout<<"========================="<<endl;
				produtmanager.getProducts();
				break;
			case 2:
				produtmanager.cadastrarProduto();//criar detecção de id automatico
				cout<<"========================="<<endl;
				break;
			case 3:
				cout<<"========================="<<endl;// criar deletar
				produtmanager.deleteProduto();
				break;
			case 4:
				cout<<"VOLTANDO PARA MENU PRINCIPAL...\n"<<endl;
				break;
			default:
				cout<<"OPÇÃO INVALIDA!"<<endl;
				break;
		}
	}while(choice!=4);
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
		<< "5 - LOGOUT\n"
		<< "6 - SAIR"<<endl;
	int choice;
	cin>> choice;
	if(cin.fail()){
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = 10;
    }
	return choice;
}

int main() {
	//Sessao usuario;
	int choice=0;
	while (choice!=6) {
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
				cout<<"========================="<<endl;				
				userManager();
				break;
			}
			case 4:
				cout<<"========================="<<endl;
				productManagerMenu();
				break;	

			case 5:
				UserManager logout;
				cout<<"\nRealizando Logout!"<<endl;
				logout.logout();
				break;
			case 6:
				cout << "Saindo..." << endl;
				break;
			default:
				cout<<"OPÇÃO INVALIDA!"<<endl;
				break;
		}
	}
	return 0;
}