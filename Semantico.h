#pragma once

#include "stdafx.h"

void semantico(std::vector<Token> *tabela);
int procurar(std::vector<Token> *pilha, std::string token, int escopo);
void fecha_escopo(std::vector<Token> *pilha);