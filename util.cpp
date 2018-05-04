#include "stdafx.h"



void printErroExitArg(std::string tipo, std::vector<Token> *tabela, int idx) {
	std::cout << "Erro de sintaxe na linha: " << tabela->at(idx).getLinha() << "."
		<< "Esperava-se: '" << tipo << "', encontrou-se: " << tabela->at(idx).getValor() << std::endl;
	system("pause");
	exit(SINTAX);
}

void printErroExit(std::string tipo, int linha) {
	std::cout << "Erro de sintaxe na linha: " << linha << "."
		<< "Esperava-se: '" << tipo << "'." << std::endl;
	system("pause");
	exit(SINTAX);
}

void printErroSemantico(std::string mensagem, int linha) {
	std::cout << "Erro semantico na linha: " << linha << "."
		<< mensagem << "." << std::endl;
	system("pause");
	exit(SEMANTICO);
}