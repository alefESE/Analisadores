#include "stdafx.h"

bool aceitavel(char c) {
	return (c == '.' || c == '(' || c == ')' || c == ',' || c == ';' || c == ':' ||
		c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' ||
		c == '>') ? true : false;
}

int isRelacionalOperador(char c) {
	if (c == '=' || c == '<' || c == '>')
		return true;
	return false;
}

int isAdtOperador(char c) {
	unsigned int i;
	for (i = 0; i < adt_op.size(); i++)
		if (adt_op[i][0] == c)
			return true;
	return false;
}

int isMulOperador(char c) {
	unsigned int i;
	for (i = 0; i < mul_op.size(); i++)
		if (mul_op[i][0] == c)
			return true;
	return false;
}

int isDelimitador(char c) {
	unsigned int i;
	for (i = 0; i < delimitadores.size(); i++)
		if (delimitadores[i] == c)
			return true;
	return false;
}

int isPalavraChave(std::string str) {
	unsigned int i;
	for (i = 0; i < palavras_chave.size(); i++)
		if (std::find(palavras_chave.begin(), palavras_chave.end(), str) != palavras_chave.end())
			return true;
	return false;
}

void montaTabela(std::ifstream &is, std::vector<Token> *tabela) {
	int linha = 1;
	char c;
	while ((c = is.get()) != EOF) {
		if (c == '\n')
			linha++;
		if (c == '{') {
			while ((c = is.get()) != '}') {
				if (c == EOF) {
					std::cout << "Comentario nao fechado" << std::endl;
					exit(INESPERADO);
				}
				if (c == '\n') linha++;
			}
		}
		if (ispunct(c)) {
			if (c == ':') {
				if ((c = is.get()) == '=') {
					tabela->push_back(Token(
						Token::getTipos(ATRIBUICAO),
						":=",
						linha));
				}
				else {
					is.seekg(-2, is.cur);
					c = is.get();
				}
			}
			if (isDelimitador(c)) {
				tabela->push_back(Token(
					Token::getTipos(DELIMITADOR),
					std::string(1, c),
					linha));
			}
			else if (isAdtOperador(c)) {
				if (c == 'o') {
					if ((c = is.get()) == 'r') {
						tabela->push_back(Token(
							Token::getTipos(ADT_OP),
							"or",
							linha));
					}
					else
						is.seekg(-2, is.cur);
				}
				else {
					tabela->push_back(Token(
						Token::getTipos(ADT_OP),
						std::string(1, c),
						linha));
				}
			}
			else if (isMulOperador(c)) {
				if (c == 'a') {
					if ((c = is.get()) == 'n') {
						if ((c = is.get()) == 'd') {
							tabela->push_back(Token(
								Token::getTipos(MUL_OP),
								"and",
								linha));
						}
					}
					else
						is.seekg(-3, is.cur);
				}
				else {
					tabela->push_back(Token(
						Token::getTipos(MUL_OP),
						std::string(1, c),
						linha));
				}
			}
			else if (isRelacionalOperador(c)) {
				if (c == '<' || c == '>') {
					std::string str;
					str.append(1, c);
					if ((c = is.get()) == '=' || c == '>') {
						str.append(1, c);
						tabela->push_back(Token(
							Token::getTipos(REL_OP),
							str,
							linha));
					}
					else {
						tabela->push_back(Token(
							Token::getTipos(REL_OP),
							str,
							linha));
						is.seekg(-1, is.cur);
					}
				}
				else if (c == '=') {
					if ((c = is.get()) == '=') {
						tabela->push_back(Token(
							Token::getTipos(REL_OP),
							"==",
							linha));
					}
					else
						is.seekg(-1, is.cur);
				}
			}
		}
		else if (isalpha(c)) {
			std::string str;
			str.append(1, c);
			while (isalnum(c = is.get())) str.append(1, c);
			if (isPalavraChave(str)) {
				tabela->push_back(Token(
					Token::getTipos(PALAVRA_CHAVE),
					str,
					linha));
			}
			else {
				tabela->push_back(Token(
					Token::getTipos(IDENTIFICADOR),
					str,
					linha));
			}
			is.seekg(-1, is.cur);
		}
		else if (isdigit(c)) {
			bool real = false;
			std::string str;
			str.append(1, c);
			while (isdigit(c = is.get()) || c == '.') {
				if (c == '.') {
					real = true;
					while (isdigit(c = is.get()))
						str.append(1, c);
				}
				else
					str.append(1, c);
			}
			real ?
				tabela->push_back(Token(
					Token::getTipos(NUMERO_REAL),
					str,
					linha))
				:
				tabela->push_back(Token(
					Token::getTipos(NUMERO_INTEIRO),
					str,
					linha));
			is.seekg(-1, is.cur);
		}
		else if (isspace(c)) continue;
		else {
			std::cout << "Caractere" << c << "invalido na linha " << linha << std::endl;
			exit(INESPERADO);
		}
	}
}