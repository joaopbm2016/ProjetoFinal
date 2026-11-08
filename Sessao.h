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
		inline static string usuario = "";
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
		static void getLogin();
		static bool getLogado();
		static string cript(string IN,int codecod);
		int totalIDs();		
};

class Cadastro : public Sessao {
	private:
		string nomeCadastro,usuarioCadastro,senhaCadastro;
		int IDCadastro;
    public:
        void cadastro();
		bool verificarCadastro(string _nome,string _usuario, int _ID);
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
	
	public:
		void getUsers();
		void deleteUser();	
};

class ProductsManager : public Sessao {

	public:
		json carregarProdutos();
		void getProducts();
		void cadastrarProdutos();

};