#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

json ProductsManager::carregarProdutos()
{
    json produtos = {
        {"tipos", {"Medicamentos", "Higiene", "Cosmeticos"}},
        {"produtos", json::array()}
    };
	ifstream arquivo("produtos.json");
    if (arquivo.is_open()) {
        json arquivoProdutos;
        arquivo >> arquivoProdutos;
        if (arquivoProdutos.is_object() && arquivoProdutos["produtos"].is_array())
        {
            produtos = arquivoProdutos;
        }
        else if (arquivoProdutos.is_array())
        {
            produtos["produtos"] = arquivoProdutos;
        }

    	arquivo.close();
    }
	ofstream arquivoSaida("produtos.json");
    if (arquivoSaida.is_open()) {
    	arquivoSaida << produtos.dump(4);
    }
    arquivoSaida.close();
    return produtos;
};

void ProductsManager::getProducts()
{
    json produtos = carregarProdutos();
    for(const auto& item : produtos["produtos"])
    {
        cout<<"======================"<<endl
            <<"nome: "<<item["nome"]<<endl
		    <<"tipo: "<<item["tipo"]<<endl
		    <<"quantidade: "<<item["quantidade"]<<endl
		    <<"ID: "<<item["ID"]<<endl;
    }
};

void ProductsManager::cadastrarProdutos()
{
    string nomeProduto;
    int quantProduto;
    json newProdutos;
    newProdutos= carregarProdutos();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Digite o nome do produto:"<<endl;
    getline(cin,nomeProduto);
    cout<<"Digite a quantidade do produto:"<<endl;
    cin>>quantProduto;
    
    
};