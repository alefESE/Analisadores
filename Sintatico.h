#pragma once
#include "stdafx.h"

/*sintax->'program' 'id'';'
declaracao_variaveis
declaracoes_de_subprogramas
comando_composto
'.'
*/
void sintax(std::vector<Token> *tabela);
//declaracao_variaveis->'var' lista_declaracoes_variaveis | $
int declaracao_variaveis(std::vector<Token> *tabela, int idx);
//lista_declaracoes_variaveis->lista_de_identificadores ':' tipo ';' lista_declaracoes_variaveis$
int lista_declaracoes_variaveis(std::vector<Token> *tabela, int idx);
//lista_declaracoes_variaveis$->lista_de_identificadoes ':' tipo ';' lista_declaracoes_variaveis$ | $
int lista_declaracoes_variaveis$(std::vector<Token> *tabela, int idx);
//lista_de_identificadores->'id' lista_de_identificadores$
int lista_de_identificadores(std::vector<Token> *tabela, int idx);
//lista_de_identificadores$->',' 'id' lista_de_identificadores$ | $
int lista_de_identificadores$(std::vector<Token> *tabela, int idx);
//tipo->'integer' | 'real' | 'boolean'
int tipo(std::vector<Token> *tabela, int idx);
//declaracoes_de_subprogramas->declaracao_de_subprograma ';' declaracoes_de_subprogramas$ | $
int declaracoes_de_subporgramas(std::vector<Token> *tabela, int idx);
//declaracoes_de_subprogramas$->declaracao_de_subprograma ';' declaracoes_de_subprogramas$ | $
int declaracoes_de_subporgramas$(std::vector<Token> *tabela, int idx);
/*declaracao_de_subprograma->'procedure' 'id' argumentos ';'
declaracao_variaveis
declaracoes_de_subprogramas
comando_composto
*/
int declaracao_de_subprograma(std::vector<Token> *tabela, int idx);
//argumentos->'(' lista_de_parametros ')' | $
int argumentos(std::vector<Token> *tabela, int idx);
//lista_de_parametros->lista_de_identificadores ':' tipo lista_de_parametros$
int lista_de_parametros(std::vector<Token> *tabela, int idx);
//lista_de_parametros$->';' lista_de_identificadores ':' tipo | $
int lista_de_parametros$(std::vector<Token> *tabela, int idx);
//comando_composto->'begin' comandos_opcionais 'end'
int comando_composto(std::vector<Token> *tabela, int idx);
//comandos_opcionais->lista_de_comandos | $
int comandos_opcionais(std::vector<Token> *tabela, int idx);
//lista_de_comandos->comando lista_de_comandos$
int lista_de_comandos(std::vector<Token> *tabela, int idx);
//lista_de_comandos$->';' comando lista_de_comandos$ | $
int lista_de_comandos$(std::vector<Token> *tabela, int idx);
/*comando->variavel ':=' expressao
| ativacao_de_procedimento
| comando_composto
| 'if' expressao 'then' comando_parte_else
| 'while' expressao 'do' comando
| $
*/
int comando(std::vector<Token> *tabela, int idx);
//comando_parte_else->comando | $
int comando_parte_else(std::vector<Token> *tabela, int idx);
//variavel->'id'
int variavel(std::vector<Token> *tabela, int idx);
//ativacao_de_procedimento->'id' | 'id' '(' lista_de_expressoes ')'
int ativacao_de_procedimento(std::vector<Token> *tabela, int idx);
//lista_de_expressoes->expressao lista_de_expressoes$
int lista_de_expressoes(std::vector<Token> *tabela, int idx);
//lista_de_expressoes$->',' expressao lista_de_expressoes$ | $
int lista_de_expressoes$(std::vector<Token> *tabela, int idx);
//expressao->expressao_simples | expressao_simples 'REL_OP' expressao_simples
int expressao(std::vector<Token> *tabela, int idx);
//expressao_simples->termo | sinal termo | 'ADT_OP' termo expressao_simples$
int expressao_simples(std::vector<Token> *tabela, int idx);
//expressao_simples$->termo | sinal termo | 'ADT_OP' termo expressao_simples$ | $
int expressao_simples$(std::vector<Token> *tabela, int idx);
//termo->fator termo$
int termo(std::vector<Token> *tabela, int idx);
//termo$->'MUL_OP' fator termo$ | $
int termo$(std::vector<Token> *tabela, int idx);
/*fator-> 'id' | 'id' '(' lista_de_expressoes ')'
| 'NUMMERO_INTEIRO' | NUMERO_REAL | true | false
| '(' expressao ')' | 'not' fator
*/
int fator(std::vector<Token> *tabela, int idx);
//sinal->'+' | '-'
int sinal(std::vector<Token> *tabela, int idx);