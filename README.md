# Analisadores
### Uso:

Compiladores <arquivo>(extensao .pas)

### Token (Léxico)

* Letra: [a-zA-Z]
* Digito: [0-9]
* Identificador: letra (letra | digito)*
* Inteiro: digito+
* Real: Inteiro.Inteiro
* Boolean: true | false
* Palavras-chave: program | var | integer | real | boolean | procedure | begin | end | if | then | else | while | do | not
* Delimitadores: ; | . | : | ( | ) | ,
* Operadores: OperadorRel | OperadorAtr | OperadorAdt | OperadorMul
* OperadorRel: == | < | > | <= | >= | <>
* OperadorAtr: :=
* OperadorAdt: + | - | or
* OperadorMul: * | / | and

### Gramatica (Sintático)

* programa →  program id; declaracoes_variaveis declaracoes_de_subprogramas comando_composto . 
* declaracoes_variaveis → var lista_declaracoes_variaveis  | ε 
* lista_declaracoes_variaveis → lista_declaracoes_variaveis lista_de_identificadores: tipo; | lista_de_identificadores: tipo; 
* lista_de_identificadores → id |lista_de_identificadores, id
* tipo → integer | real | boolean 
* declaracoes_de_subprogramas → declaracoes_de_subprogramas declaracao_de_subprograma; | ε 
* declaracao_de_subprograma → procedure id argumentos; declaracoes_variaveis declaracoes_de_subprogramas comando_composto 
* argumentos → (lista_de_parametros) | ε 
* lista_de_parametros → lista_de_identificadores: tipo | lista_de_parametros; lista_de_identificadores: tipo  
* comando_composto → begin comandos_opcionais end 
* comandos_opcionais → lista_de_comandos | ε 
* lista_de_comandos → comando | lista_de_comandos; comando 
* comando → variavel := expressao | ativacao_de_procedimento | comando_composto | if expressao then comando parte_else  | while expressao do comando 
* parte_else →  else comando  | ε 
* variavel → id
* ativacao_de_procedimento → id | id (lista_de_expressoes) 
* lista_de_expressoes → expressao | lista_de_expressoes, expressao 
* expressao → expressao_simples | expressao_simples op_relacional expressao_simples  
* expressao_simples →  termo | sinal termo | expressao_simples op_aditivo termo 
* termo → fator | termo op_multiplicativo fator  
* fator → id | id(lista_de_expressoes) | num_int | num_real | true | false | (expressao) | not fator 
* sinal → + | -
* op_relacional → = | < | > | <= | >= | <> 
* op_aditivo → + | - | or 
* op_multiplicativo → * | / | and 

### Regras (Semântico)
* ##### Regra um:
   * Em um mesmo escopo nao podera ser declarado identificadores com o mesmo nome; 
   * Identificadores ja declarados podem ser novamente declarados em escopos diferentes; 
   * Identificadores de procedimento seguem as regras gerais das variaveis; 
   * Identificadores nao podem ser usados sem antes terem sido declarados.
* ##### Regra dois (INCOMPLETO):
   * Devem ser identificadas atribuicoes e inicializacoes invalidas de variaveis. Por exemplo, variaveis do tipo boolean recebendo numeros. 
   * A seguinte tabela para operacoes aritmeticas deve ser observada para a operacao: V3 := V1 op V2 

| V1 | V2 | V3 | Validade |
| :---: | :---: | :---: | :---: |
| Integer | Integer | Integer | OK | 
| Integer | Real | Integer | Invalido |
| Real | Integer | Integer | Invalido |
| Real | Real | Integer | Invalido | 
| Integer | Integer | Real | OK |
| Integer | Real | Real | OK | 
| Real | Integer | Real | OK | 
| Real | Real | Real | OK | 
 
   * Obviamente, operacoes relacionais so podem ser realizadas entre valores numericos, enquanto operacoes logicas entre valores booleanos
