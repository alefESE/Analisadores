#pragma once
#include "stdafx.h"

#define MAX 10
//variaveis globais
static std::vector<std::string> palavras_chave = {
	"program", "var", "integer", "real", "boolean", "procedure", "begin", "end", "if", "then", "else",
	"while", "do", "not"
};

static std::vector<char> delimitadores = {
	';', '.', ':' , '(', ')', ','
};

static std::vector<std::string> rel_op = {
	"==", "<", ">", "<=", ">=", "<>"
};

static std::string atribuicao = ":=";

static std::vector<std::string> adt_op = {
	"+", "-", "or"
};

static std::vector<std::string> mul_op = {
	"*", "/", "and"
};

enum retornos {
	CHAMADA_DE_PROGRAMA,
	ARQUIVO,
	SUCESSO,
	INESPERADO,
	SINTAX
};

void printErroExitArg(std::string tipo, std::vector<Token> *tabela, int idx);
void printErroExit(std::string tipo, int linha);