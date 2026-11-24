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

int ProductsManager::maiorIDProduto()
{
    json dados = carregarProdutos();

    int maiorID = 0;

    for(auto i : dados)
    {
        if(i.contains("ID") && i["ID"].is_number_integer() && i["ID"]>maiorID)
        {
            maiorID = i["ID"].get<int>();
        }
    }
    return maiorID;
}

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

    if(nomeProduto=="")
    {
        cout<< "de um nome não vazio ao produto"<< endl;
        return;
    }

    cout<<"Digite a quantidade do produto:"<<endl;
    cin>>quantProduto;
    if(cin.fail() || quantProduto<0)
    {
        cout<< "\n digite apenas numeros positivos!\n"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
    }

    cout<<"Qual ID usar? (0 para automatico)"<<endl;
    cin>>ID;
    if(cin.fail()){
        cout<< "\n digite apenas numeros!\n escolhendo ID automático"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		ID = 0;
    }
    if(ID<0) 
    {
        cout<<" numeros negativos não são aceitos!"<<endl;
        return;
    }
    if(ID==0)
    {
        ID=maiorIDProduto()+1;
    }

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

void ProductsManager::deleteProduto()
{
    json oldprodutos = carregarProdutos();
    bool encontrado=false;
    int deleteID;

    cout<<"Qual produto deletar?\n*escreva o ID*"<<endl;
    cin>>deleteID;
    if(cin.fail()){
        cout<< "\n digite apenas numeros!"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
    }
    if(deleteID<=0) 
    {
        cout<<" numeros negativos ou 0 não são aceitos!"<<endl;
        return;
    }
    for(auto it = oldprodutos.begin();it != oldprodutos.end();it++)
    {
        if((*it).contains("ID") && (*it)["ID"] == deleteID)
        {
            oldprodutos.erase(it);
            encontrado=true;
            break;
        }
    }

    if(!encontrado)
    {
        cout<< "ID NÃO ENCONTRADO!"<<endl;
        return;
    }

    ofstream arquivo("produtos.json");
    if(!arquivo.is_open())
    {
        cout<<"FALHA AO ABRIR O ARQUIVO!"<<endl;
        return;
    }
    arquivo<< oldprodutos.dump(4);
    arquivo.close();

}