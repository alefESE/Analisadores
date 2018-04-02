#include "stdafx.h"


Token::Token()
{
	tipo = "";
	valor = "";
	linha = 0;
}

Token::Token(std::string tipo, std::string valor, int linha)
{
	this->tipo = tipo;
	this->valor = valor;
	this->linha = linha;
}

Token::~Token()
{
}

std::string Token::getTipo()
{
	return tipo;
}

std::string Token::getValor()
{
	return valor;
}

int Token::getLinha()
{
	return linha;
}

void Token::setTipo(std::string tipo)
{
	this->tipo = tipo;
}

void Token::setValor(std::string valor)
{
	this->valor = valor;
}

void Token::setLinha(int linha)
{
	this->linha = linha;
}

std::string Token::toString()
{
	return valor + ", " + tipo + ", " + std::to_string(linha);
}

std::string Token::getTipos(tipos_token tipo)
{
	return tiposString[tipo];
}