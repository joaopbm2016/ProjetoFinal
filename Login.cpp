#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

#include "Sessao.h"

using namespace std;
using json = nlohmann::json;

bool Login::verificarLogin(string _usuario,string _senha)
{
    json usuarios = carregarUsuarios();
    for(const auto& usuario : usuarios) {
    	if (usuario.contains("usuario") && usuario["usuario"] == _usuario) {
    		if (usuario.contains("senha") && usuario["senha"] == _senha)
			{
    			return true;
    		}else
			{
    			cout << "Senha incorreta." << endl;
    			return false;
    		}
    	}
    }
    cout << "usuario não encontrado." << endl;
    return false;
}

bool Login::loginRegister(string buscaUsuario)
{
	json usuarios = carregarUsuarios();

	for (const auto& item : usuarios)
	{
		if (item.contains("usuario") && item["usuario"]==buscaUsuario)
		{
			setNome(item["nome"]);
			setUser(item["usuario"]);
			setSenha(item["senha"]);
			if (item.contains("ID") && item["ID"].is_number_integer())
			{
				setID(item["ID"]);
			}
			else
			{
				setID(0);
			}
			return true;
		}
	}

	return false;

}

void Login::login()
{
    if (Sessao::getLogado()) 
    {
        cout << "Você já está logado." << endl;
        return;
    }
    cout << "Login selecionado." << endl;
	cout << "Digite seu usuario: ";
	cin >> usuarioLogin;
    cout << "Digite sua senha: ";
    cin >> senhaLogin;
	senhaLogin= cript(senhaLogin,1);
	if (verificarLogin(usuarioLogin, senhaLogin)) 
    {
        cout << "Login bem-sucedido!" << endl;
		loginRegister(usuarioLogin);
        Sessao::logado = true;
    } else {
        cout << "Falha no login." << endl;
        Sessao::logado = false;
    }
}