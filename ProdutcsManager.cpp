#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

json ProductsManager::carregarProdutos()
{
    json produtos;
	ifstream arquivo("produtos.json");
    if (arquivo.is_open()) {
        arquivo >> produtos;
        if (!produtos.is_array())
        {
            cout<<"\nerro abrindo json de produtos!\n"<<endl;
            return 1;
        }
    	arquivo.close();
    }
    return produtos;
};


void ProductsManager::getProducts()
{
    json produtos = carregarProdutos();
    for(const auto& item : produtos)
    {
        cout<<"======================"<<endl
            <<"nome: "<<item["nome"]<<endl
		    <<"quantidade: "<<item["quantidade"]<<endl
		    <<"ID: "<<item["ID"]<<endl;
    }
};

bool ProductsManager::verificarProdutCadastro(string Nome,int ID)
{
    json produtos = carregarProdutos();

    for(const auto& item : produtos)
    {
        if(item.contains("nome") && item["nome"]== Nome)
        {
            cout<<"NOME JÁ UTILIZADO!"<<endl;
            return false;
        }
        if(item.contains("ID") && item["ID"]==ID)
        {
            cout<<"ID JÁ UTILIZADO!"<<endl;
            return false;
        }
    }
    return true;
}

void ProductsManager::cadastrarProduto()
{
    string nomeProduto,tipoProduto;
    int quantProduto,ID;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Digite o nome do produto:"<<endl;
    getline(cin,nomeProduto);

    cout<<"Digite a quantidade do produto:"<<endl;
    cin>>quantProduto;

    cout<<"Qual ID usar? (0 para automatico)"<<endl;
    cin>>ID;

    if(verificarProdutCadastro(nomeProduto, ID))
    {
        json newProdutos = carregarProdutos();
        newProdutos.push_back({
            {"nome",nomeProduto},
            {"quantidade",quantProduto},
            {"ID",ID}
        });
        ofstream arquivo("produtos.json");
        if(!arquivo.is_open())
        {
            cout<<"FALHA PARA SALVAR ARQUIVO!"<<endl;
            return;
        }

        arquivo<<newProdutos.dump(4);
        arquivo.close();
        cout<<"PRODUTO CADASTRADO COM SUCESSO!"<<endl;
    }


    
};