#include "stdafx.h"
#include "util.h"

int main(int argc, char* argv[]) {
	std::ifstream is;

	switch (argc){
	case 2:
		is.open(strcat(argv[1], ".pas"), std::ios::in);
		if (!is) {
			std::cout << "O arquivo nao pode ser aberto" << std::endl;
			system("pause");
			exit(ARQUIVO);
		}
		break;
	default:
		std::cout << "Sintaxe: Compiladores [arquivo] (.pas implicito)" << std::endl;
		system("PAUSE");
		exit(CHAMADA_DE_PROGRAMA);
	}

	is.seekg(0, is.end);
	int tamanho = is.tellg();
	if (tamanho == 0) {
		std::cout << "Arquvio vazio" << std::endl;
		system("pause");
		exit(ARQUIVO);
	} else 
		is.seekg(0, is.beg);
	
	std::ofstream os("token.csv", std::ios::out);
	
	std::vector<Token> tabela;
	
	montaTabela(is, &tabela);

	std::string str;
	os << "Token, tipo, linha" << std::endl;
	for (unsigned int i = 0; i < tabela.size(); i++) {
		str = tabela[i].toString();
		os << str << std::endl;
	}

	try {
		sintax(&tabela);
		semantico(&tabela);
	}
	catch (const std::out_of_range &ex) {
		std::cout << "Out of range: " << ex.what() << std::endl;
	}

	std::cout << "Sem erros!" << std::endl;
	system("pause");
	return SUCESSO;
}

