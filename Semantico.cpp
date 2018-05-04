#include "stdafx.h"

void semantico(std::vector<Token> *tabela) {
	int idx = 0; //'program'
	int aux = 0;
	int escopo = 0; // contagem do escopo
	std::vector<Token> pilha;

	pilha.push_back(Token("", "$", 0));//push $
	idx += 3; //'program' + ID_PROGRAM + ';'

	for (; idx < tabela->size(); idx++) {
		if (tabela->at(idx).getTipo().compare(Token::getTipos(IDENTIFICADOR_PROGRAMA)) == 0) { //subprograma
			if (!escopo) {//declarando
				if (procurar(&pilha, tabela->at(idx).getValor(), escopo) == -1) {
					pilha.push_back(tabela->at(idx)); //push ID_PROGRAM
					pilha.push_back(Token("", "$", 0)); // push $
					continue;
				}
				else {
					std::cout << "O identificador " << tabela->at(idx).getValor() <<
						" ja foi declarado no escopo." << std::endl;
					system("pause");
					exit(SEMANTICO);
				}	
			}
			else {//recuperando
				if (procurar(&pilha, tabela->at(idx).getValor(), escopo) != -1) {
					continue;
				}
				else {
					std::cout << "O identificador " << tabela->at(idx).getValor() <<
						" nao foi declarado no escopo." << std::endl;
					system("pause");
					exit(SEMANTICO);
				}
			}
		}//identificador
		if (tabela->at(idx).getTipo().compare(Token::getTipos(IDENTIFICADOR)) == 0) {
			if (!escopo) {//declarando
				if (procurar(&pilha, tabela->at(idx).getValor(), escopo) == -1) {
					pilha.push_back(tabela->at(idx));
					continue;
				}
				else {
					std::cout << "O identificador " << tabela->at(idx).getValor() <<
						" ja foi declarado no escopo." << std::endl;
					system("pause");
					exit(SEMANTICO);
				}
			}
			else {//recuperando
				if (procurar(&pilha, tabela->at(idx).getValor(), escopo) != -1) {//encontrado
					continue;
				}
				else {
					std::cout << "O identificador " << tabela->at(idx).getValor() <<
						" nao foi declarado no escopo." << std::endl;
					system("pause");
					exit(SEMANTICO);
				}
			}
		}
		if (tabela->at(idx).getValor().compare("begin") == 0) {
			escopo++;
			continue;
		}
		if (tabela->at(idx).getValor().compare("end") == 0) {
			escopo--;
			fecha_escopo(&pilha);
			continue;
		}
	}
}

int procurar(std::vector<Token> *pilha, std::string token, int escopo) {
	int i;
	for (i = pilha->size()-1; i >= 0; i--) {
		if (pilha->at(i).getValor().compare(token) == 0)
			return i;
		if (pilha->at(i).getValor().compare("$") == 0)
			if (!escopo)
				return -1;
			else
				escopo--;
	}
	return -1;
}

void fecha_escopo(std::vector<Token> *pilha) {
	while (pilha->back().getValor() != "$")
		pilha->pop_back();
	pilha->pop_back();
}
