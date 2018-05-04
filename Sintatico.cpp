#include "stdafx.h"

void sintax(std::vector<Token> *tabela) {
	int idx = 0;
	if (tabela->at(idx).getValor() == "program") {
		if (tabela->at(++idx).getTipo() == Token::getTipos(IDENTIFICADOR)) {
			tabela->at(idx).setValor(Token::getTipos(IDENTIFICADOR_PROGRAMA));
			if (tabela->at(++idx).getValor() == ";") {
				idx = declaracao_variaveis(tabela, ++idx);
				idx = declaracoes_de_subporgramas(tabela, idx);
				idx = comando_composto(tabela, idx);
				if (tabela->at(idx).getValor() == ".")
					return;
				else
					printErroExitArg("Delimitador: '.'", tabela, idx);
			}
			else
				printErroExitArg("Delimitador: ';'", tabela, idx);
		}
		else
			printErroExitArg("Identificador", tabela, idx);
	}
	else 
		printErroExitArg("Palavra Chave: 'program'", tabela, idx);
}

int declaracao_variaveis(std::vector<Token> *tabela, int idx) {
		if (tabela->at(idx).getValor() == "var")
			return lista_declaracoes_variaveis(tabela, ++idx);
		else
			return idx;//$
}

int lista_declaracoes_variaveis(std::vector<Token> *tabela, int idx) {
	if (idx = lista_de_identificadores(tabela, idx))
		if (tabela->at(idx).getValor() == ":") {
			idx = tipo(tabela, ++idx);
			if (tabela->at(idx).getValor() == ";")
				return lista_declaracoes_variaveis$(tabela, ++idx);
			else
				printErroExitArg("Delimitador: ';'", tabela, idx);
		}
		else
			printErroExitArg("Delimitador: ':'", tabela, idx);
	else
		printErroExit("Lista de identificadores", tabela->at(idx).getLinha());//nunca
}

int lista_declaracoes_variaveis$(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = lista_de_identificadores(tabela, idx))
		if (tabela->at(aux).getValor() == ":") {
			idx = tipo(tabela, ++aux);
			if (tabela->at(idx).getValor() == ";")
				return lista_declaracoes_variaveis$(tabela, ++idx);
			else
				printErroExitArg("Delimitador: ';'", tabela, idx);
		}
		else
			printErroExitArg("Delimitador: ':'", tabela, idx);
	else
		return idx;//$
}

int lista_de_identificadores(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getTipo() == Token::getTipos(IDENTIFICADOR))
		return lista_de_identificadores$(tabela, ++idx);
	else 
		return false;
}

int lista_de_identificadores$(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == ",")
		if (tabela->at(idx).getTipo() == Token::getTipos(IDENTIFICADOR))
			return lista_de_identificadores$(tabela, ++idx);
		else
			printErroExitArg("Identificador", tabela, idx);
	else
		return idx;//$
}

int tipo(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == "integer" || "real" || "boolean")
		return ++idx;
	else
		printErroExitArg("Tipo: integer, real ou boolean", tabela, idx);
}

int declaracoes_de_subporgramas(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = declaracao_de_subprograma(tabela, idx))
		if (tabela->at(aux).getValor() == ";")
			return declaracoes_de_subporgramas$(tabela, ++aux);
		else
			printErroExitArg("Delimitador: ';'", tabela, aux);
	else
		return idx;//$
}

int declaracoes_de_subporgramas$(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = declaracao_de_subprograma(tabela, idx)) {
		if (tabela->at(aux).getValor() == ";")
			return declaracoes_de_subporgramas$(tabela, ++aux);
		else
			printErroExitArg("Delimitador: ';'", tabela, aux);
	}
	else
		return idx;//$
}

int declaracao_de_subprograma(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == "procedure")
		if (tabela->at(++idx).getTipo() == Token::getTipos(IDENTIFICADOR)) {
			tabela->at(idx).setValor(Token::getTipos(IDENTIFICADOR_PROGRAMA));
			idx = argumentos(tabela, ++idx);
			if (tabela->at(idx).getValor() == ";") {
				idx = declaracao_variaveis(tabela, ++idx);
				idx = declaracoes_de_subporgramas(tabela, idx);
				return comando_composto(tabela, idx);
			}
			else 
				printErroExitArg("Delimitador: ';'", tabela, idx);
		}
		else
			printErroExitArg("Identificador", tabela, idx);
	else {
		return false;//$
	}
}

int argumentos(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == "(") {
		idx = lista_de_parametros(tabela, ++idx);
		if (tabela->at(idx).getValor() == ")")
			return ++idx;
		else
			printErroExitArg("Delimitador: ')'", tabela, idx);
	}
	else
		return idx;//$
}

int lista_de_parametros(std::vector<Token> *tabela, int idx) {
	if (idx = lista_de_identificadores(tabela, idx)) {
		if (tabela->at(idx).getValor() == ":") {
			idx = tipo(tabela, ++idx);
			return lista_de_parametros$(tabela, idx);
		}
		else
			printErroExitArg("Delimitador: ':'", tabela, idx);
	}
	else 
		printErroExit("Lista de parametros", tabela->at(idx).getLinha());//nunca
}

int lista_de_parametros$(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == ";") {
		idx = lista_de_parametros(tabela, ++idx);
		if (tabela->at(idx).getValor() == ":") {
			idx = tipo(tabela, ++idx);
			return lista_de_parametros$(tabela, idx);
		}
		else
			printErroExitArg("Delimitador: ':'", tabela, idx);
	}
	else
		return idx;//$
}

int comando_composto(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == "begin") {
		idx = comandos_opcionais(tabela, ++idx);
		if (tabela->at(idx).getValor() == "end")
			return ++idx;
		else
			printErroExitArg("Palavra chave: 'end'", tabela, idx);
	}
	else {
		std::cout << "ERRO AQUI" << std::endl;
		printErroExitArg("Palavra chave: 'begin'", tabela, idx);
	}
}

int comandos_opcionais(std::vector<Token> *tabela, int idx) {
	return lista_de_comandos(tabela, idx);
}

int lista_de_comandos(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = comando(tabela, idx))
		return lista_de_comandos$(tabela, aux);
	else
		return idx;//$
}

int lista_de_comandos$(std::vector<Token> *tabela, int idx) {
	int aux;
	if (tabela->at(idx).getValor() == ";") {
		if (aux = comando(tabela, ++idx))
			return lista_de_comandos$(tabela, aux);
		else
			return idx;//$
	}
	else
		printErroExitArg("Delimitador: ';'", tabela, idx);
}

int comando(std::vector<Token> *tabela, int idx) {
	int aux;
	if (variavel(tabela, idx)) {
		if (aux = ativacao_de_procedimento(tabela, idx))
			return aux;
		else 
			if (tabela->at(++idx).getValor() == ":=")
				return expressao(tabela, ++idx);
			else
				printErroExitArg("Atribuicao: ':='", tabela, idx);
	}
	else if (tabela->at(idx).getValor() == "begin") 
		return comando_composto(tabela, idx);
	else if (tabela->at(idx).getValor() == "if") {
		idx = expressao(tabela, ++idx);
		if (tabela->at(idx).getValor() == "then")
			return comando_parte_else(tabela, ++idx);
		else
			printErroExitArg("Palavra chave: 'then'", tabela, idx);
	}
	else if (tabela->at(idx).getValor() == "while") {
		idx = expressao(tabela, ++idx);
		if (tabela->at(idx).getValor() == "do")
			return comando(tabela, ++idx);
		else
			printErroExitArg("Palavra chave: 'do'", tabela, idx);
	} 
	else
		return false;//$
}

int comando_parte_else(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == "else")
		return comando(tabela, ++idx);
	else
		return idx;//$
}

int variavel(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getTipo() == Token::getTipos(IDENTIFICADOR))
		return true;
	else
		return false;
}

int ativacao_de_procedimento(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getTipo() == Token::getTipos(IDENTIFICADOR))
		if (tabela->at(idx + 1).getValor() == "(") {
			idx = lista_de_expressoes(tabela, ++idx);
			if (tabela->at(idx).getValor() == ")")
				return ++idx;
			else
				printErroExitArg("Delimitador: ')'", tabela, idx);
		}
		else
			return false;
	else
		return false;
}

int lista_de_expressoes(std::vector<Token> *tabela, int idx) {
	idx = expressao(tabela, idx);
	return lista_de_expressoes$(tabela, idx);
}

int lista_de_expressoes$(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getValor() == ",") {
		idx = expressao(tabela, ++idx);
		return lista_de_expressoes$(tabela, idx);
	}
	else 
		return idx;//$
}

int expressao(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = expressao_simples(tabela, idx)) {
		if (tabela->at(aux).getTipo() == Token::getTipos(REL_OP))
			return expressao_simples(tabela, ++aux);
		else 
			return aux;
	}
	else
		printErroExit("Expressao_simples", tabela->at(idx).getLinha());
}

int expressao_simples(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = termo(tabela, idx)) 
		return aux;
	else if (tabela->at(idx).getTipo() == Token::getTipos(ADT_OP))
		if (sinal(tabela, idx))
			if (aux = termo(tabela, ++idx))
				return aux;
			else
				printErroExit("Termo", tabela->at(idx).getLinha());
		else
			if (aux = termo(tabela, ++idx))
				return expressao_simples$(tabela, aux);
			else
				printErroExit("Termo", tabela->at(idx).getLinha());
	else
		return false;
}

int expressao_simples$(std::vector<Token> *tabela, int idx) {
	int aux;
	if (aux = termo(tabela, idx))
		return aux;
	else if (tabela->at(idx).getTipo() == Token::getTipos(ADT_OP))
		if (sinal(tabela, idx))
			if (aux = termo(tabela, ++idx))
				return aux;
			else
				printErroExit("Termo", tabela->at(idx).getLinha());
		else
			if (aux = termo(tabela, ++idx))
				return expressao_simples$(tabela, aux);
			else
				printErroExit("Termo", tabela->at(idx).getLinha());
	else
		return idx;//$
}

int termo(std::vector<Token> *tabela, int idx) {
	return fator(tabela, idx);
}

int termo$(std::vector<Token> *tabela, int idx) {
	int aux;
	if (tabela->at(idx).getValor() == Token::getTipos(MUL_OP)) {
		if (aux = fator(tabela, ++idx))
			return termo$(tabela, idx);
		else
			printErroExit("Fator", tabela->at(aux).getLinha());
	}
	else
		return idx;//$
}

int fator(std::vector<Token> *tabela, int idx) {
	if (tabela->at(idx).getTipo() == Token::getTipos(IDENTIFICADOR)) {
		if (tabela->at(++idx).getValor() == "(") {
			idx = lista_de_expressoes(tabela, idx);
			if (tabela->at(idx).getValor() == ")")
				return ++idx;
			else
				printErroExitArg("Delimitador: ')'", tabela, idx);
		}
		else
			return ++idx;
	}
	else if (tabela->at(idx).getTipo() == Token::getTipos(NUMERO_INTEIRO)) {
		//PcT.push_back(Token::getTipos(NUMERO_INTEIRO));
		return ++idx;
	}
	else if (tabela->at(idx).getTipo() == Token::getTipos(NUMERO_REAL)) {
		//PcT.push_back(Token::getTipos(NUMERO_REAL));
		return ++idx;
	}
	else if (tabela->at(idx).getValor() == "true") { 
		//PcT.push_back(Token::getTipos(BOOLEANO));
		return ++idx;
	}
	else if (tabela->at(idx).getValor() == "false") {
		//PcT.push_back(Token::getTipos(BOOLEANO));
		return ++idx;
	}
	else if (tabela->at(idx).getValor() == "(") {
		idx = expressao(tabela, ++idx);
		if (tabela->at(idx).getValor() == ")")
			return ++idx;
		else
			printErroExitArg("Delimitador: ')'", tabela, idx);
	}
	else if (tabela->at(idx).getValor() == "not")
		return fator(tabela, ++idx);
	else
		return false;
}

int sinal(std::vector<Token> *tabela, int idx) {
	return (tabela->at(idx).getValor() == "+" || "-") ? true : false;
}