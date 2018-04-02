#pragma once
#include "stdafx.h"

//tipos_token enum
enum tipos_token : char {
	IDENTIFICADOR,
	PALAVRA_CHAVE,
	NUMERO_INTEIRO,
	NUMERO_REAL,
	DELIMITADOR,
	ATRIBUICAO,
	REL_OP, // OPERADOR REALCIONAL
	ADT_OP, // OPERADOR ADITIVO
	MUL_OP // OPERADOR MULTIPLICATIVO
};

class Token
{
public:
	Token();
	Token(std::string tipo, std::string valor, int linha);
	~Token();
	//get e set
	std::string getTipo();
	std::string getValor();
	int getLinha();
	void setTipo(std::string tipo);
	void setValor(std::string valor);
	void setLinha(int linha);
	//to_string
	std::string toString();
	
	//aux
	static std::string getTipos(tipos_token tipo);

private:
	std::string tipo;
	std::string valor;
	int linha;
};

const std::string tiposString[] = {
	"Identificador", "Palavra reservada", "Numero inteiro", "Numero real", "Delimitador", "Atribuicao",
	"Operador relacional", "Operador aditivo", "Operador multiplicativo"
};