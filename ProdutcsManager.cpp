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
    for (auto& produto : produtos["produtos"])
    {
        if (produto.contains("tipo") && produto["tipo"].is_string())
        {
            string& tipo = produto["tipo"].get_ref<string&>();
            tipo.erase(remove(tipo.begin(), tipo.end(), '\n'), tipo.end());
            tipo.erase(remove(tipo.begin(), tipo.end(), '\r'), tipo.end());
            const size_t inicio = tipo.find_first_not_of(" \t");
            const size_t fim = tipo.find_last_not_of(" \t");
            tipo = inicio == string::npos ? "" : tipo.substr(inicio, fim - inicio + 1);
        }
    }

    ofstream arquivoSaida("produtos.json");
    if (arquivoSaida.is_open()) {
        nlohmann::ordered_json produtosOrdenados = {
            {"tipos", produtos["tipos"]},
            {"produtos", produtos["produtos"]}
        };
    	arquivoSaida << produtosOrdenados.dump(4);
    }
    arquivoSaida.close();
    return produtos;
};

string ProductsManager::showTypes()
{
    json tipos = carregarProdutos();
    string produtTypes;
    if (!tipos.contains("tipos") || !tipos["tipos"].is_array())
    {
        return produtTypes;
    }

    for (const auto& tipo : tipos["tipos"])
    {
        if (!produtTypes.empty())
        {
            produtTypes += ", ";
        }
        produtTypes += tipo.get<string>();
    }

    return produtTypes;
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

bool ProductsManager::verificarProdutCadastro(string Nome,int ID)
{
    json produtos = carregarProdutos();

    for(const auto& item : produtos["produtos"])
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
    cout<<"Qual o tipo desse produto?\nuse apenas esses tipos:"<<showTypes()<<endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, tipoProduto);
    tipoProduto.erase(remove(tipoProduto.begin(), tipoProduto.end(), '\r'), tipoProduto.end());
    tipoProduto.erase(remove(tipoProduto.begin(), tipoProduto.end(), '\n'), tipoProduto.end());
    cout<<"Qual ID usar? (0 para automatico)"<<endl;
    cin>>ID;
    if(verificarProdutCadastro(nomeProduto, ID))
    {
        json newProdutos = carregarProdutos();
        newProdutos["produtos"].push_back({
            {"nome",nomeProduto},
            {"quantidade",quantProduto},
            {"tipo",tipoProduto},
            {"ID",ID}
        });
        ofstream arquivo("produtos.json");
        if(!arquivo.is_open())
        {
            cout<<"FALHA PARA SALVAR ARQUIVO!"<<endl;
            return;
        }
        nlohmann::ordered_json produtosOrdenados = {
            {"tipos", newProdutos["tipos"]},
            {"produtos", newProdutos["produtos"]}
        };
        arquivo<<produtosOrdenados.dump(4);
        arquivo.close();
        cout<<"PRODUTO CADASTRADO COM SUCESSO!"<<endl;
    }


    
};