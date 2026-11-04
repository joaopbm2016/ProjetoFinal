#include <iostream>
#include <string>
#include <limits>
#include "json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Sessao {

	private:
		inline static string nome = "";
		inline static string usuario = "";//salvar o usuário atual para saber quem está logado
        inline static string senha = "" ; // criptografar com hash
		inline static int ID = 0;

	protected:	
		inline static bool logado = false;
        //----------------------------------
        json carregarUsuarios();
		void setNome(string nomeSet);
		void setUser(string userSet);
		void setSenha(string senhaSet);
		void setID(int IDSet);

    public:
		static json GetLogin();
		static bool GetLogado();
		int totalIDs();
		
};

class Cadastro : public Sessao {
	private:
		string nomeCadastro,usuarioCadastro,senhaCadastro;
		int IDCadastro;

    public:
        void cadastro();
		bool verificarCadastro(string _nome,string _usuario,string _senha, int _ID);
        ~Cadastro(){};
};

class Login : public Sessao {
	private:
		string nomeLogin,usuarioLogin,senhaLogin;
		bool loginRegister(string buscaUsuario);

    public:
        void login();
		bool verificarLogin(string _usuario,string _senha);
        ~Login(){};
};

class UserManager : public Sessao {
	
};

bool Sessao::GetLogado()
{
	return logado;
}

json Sessao::GetLogin()
{
	json info;
	if(!logado)
	{
		info["log"] = logado;
		return info;
	}
	info["nome"] = nome;
	info["usuario"] = usuario;
	info["ID"] = ID;
    info["log"] = logado;
	return info;
}

void Sessao::setNome(string nomeSet)
{
	nome = nomeSet;
}
void Sessao::setUser(string userSet)
{
	usuario = userSet;
}
void Sessao::setSenha(string senhaSet)
{
	senha = senhaSet;
}

void Sessao::setID(int IDSet)
{
	ID = IDSet;
}

int Sessao::totalIDs()
{
	json dados = carregarUsuarios();

	size_t IDs = dados.size();

	return IDs;
}

json Sessao::carregarUsuarios()
{
    json usuarios = json::array();
	ifstream arquivo("cadastro.json");
    if (arquivo.is_open()) {
    	
    	arquivo >> usuarios;
		if (!usuarios.is_array())
		{
    		usuarios = json::array();
    	}
    	
    	arquivo.close();
    }
	ofstream arquivoSaida("cadastro.json");
    if (arquivoSaida.is_open()) {
    	arquivoSaida << usuarios.dump(4);
    }
    arquivoSaida.close();
    return usuarios;
}

bool Cadastro::verificarCadastro(string _nome,string _usuario,string _senha, int _ID)
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
    	if (usuario.contains("senha") && usuario["senha"] == _senha)
		{
    		cout << "senha já cadastrada." << endl;
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
    cout << "Login não encontrado." << endl;
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
	IDCadastro = totalIDs()+1;
	if (verificarCadastro(nomeCadastro, usuarioCadastro, senhaCadastro, IDCadastro))
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

void Login::login()
{
    if (Sessao::GetLogado()) 
    {
        cout << "Você já está logado." << endl;
        return;
    }
    cout << "Login selecionado." << endl;
	cout << "Digite seu usuario: ";
	cin >> usuarioLogin;
    cout << "Digite sua senha: ";
    cin >> senhaLogin;
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