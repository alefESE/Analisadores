#pragma once
#include "stdafx.h"

void montaTabela(std::ifstream &is, std::vector<Token> *tabela);
bool aceitavel(char c);
int isRelacionalOperador(char c);
int isAdtOperador(char c);
int isMulOperador(char c);
int isDelimitador(char c);
int isPalavraChave(std::string str);
void montaTabela(std::ifstream &is, std::vector<Token> *tabela);