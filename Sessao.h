#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Sessao {
	protected:
        string nome;
		string loginUsuario;//salvar o login atual para saber quem está logado
        string senha; // criptografar com hash
		inline static bool logado = false;
        //----------------------------------
		bool verificarCadastro(string _nome,string _login,string _senha);
        bool verificarLogin(string _login,string _senha);
        json carregarUsuarios();

    public:
		Sessao() = default;
		static bool GetLogado() {
            return logado;
        }
};

class Cadastro : public Sessao {
    public:
        void cadastro();
        ~Cadastro(){};
};

class Login : public Sessao {
    public:
        void login();
        ~Login(){};
};

json Sessao::carregarUsuarios()
{
    json usuarios = json::array();
    ifstream arquivo("usuarios.json");
    if (arquivo.is_open()) {
    	try {
    		arquivo >> usuarios;
    		if (!usuarios.is_array()) {
    			usuarios = json::array();
    		}
    	} catch (const json::parse_error&) {
    		usuarios = json::array();
    	}
    	arquivo.close();
    }
    ofstream arquivoSaida("usuarios.json");
    if (arquivoSaida.is_open()) {
    	arquivoSaida << usuarios.dump(4);
    }
    arquivoSaida.close();
    return usuarios;
}

bool Sessao::verificarCadastro(string _nome,string _login,string _senha)
{
    json usuarios = carregarUsuarios();
    for(const auto& usuario : usuarios) {
    	if (usuario.contains("nome") && usuario["nome"] == _nome)
		{
    		cout << "nome já cadastrado." << endl;
    		return false;
    	}
    	if (usuario.contains("login") && usuario["login"] == _login)
		{
    		cout << "login já cadastrado." << endl;
    		return false;
    	}
    	if (usuario.contains("senha") && usuario["senha"] == _senha)
		{
    		cout << "senha já cadastrada." << endl;
    		return false;
    	}
    }
    return true;
}

bool Sessao::verificarLogin(string _login,string _senha)
{
    json usuarios = carregarUsuarios();
    for(const auto& usuario : usuarios) {
    	if (usuario.contains("login") && usuario["login"] == _login) {
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

void Cadastro::cadastro()
{

	cout<< "Cadastro selecionado." << endl;
	cout<<"Digite seu nome: ";
	cin>> nome;
	cout<<"Digite seu login: ";
	cin>> loginUsuario;
	cout<<"Digite sua senha: ";
	cin>> senha;
	if (verificarCadastro(nome, loginUsuario, senha)) {
		json usuarios = carregarUsuarios();
		usuarios.push_back({
			{"nome", nome},
		    {"login", loginUsuario},
			{"senha", senha}
		});
		ofstream arquivo("usuarios.json");
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
    cout << "Digite seu login: ";
	cin >> loginUsuario;
    cout << "Digite sua senha: ";
    cin >> senha;
	if (verificarLogin(loginUsuario, senha)) 
    {
        cout << "Login bem-sucedido!" << endl;
        Sessao::logado = true;
    } else {
        cout << "Falha no login." << endl;
        Sessao::logado = false;
    }
}