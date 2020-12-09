/*Compilador feito como trabalho final da disciplina de compiladoresDCC605 ministrada pelo
professor Luciano*/
//Author: Luis Henrique Matos Sales(Henrique Annicchino)

#include <cstdlib>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stack>
#include <windows.h>

#define OPEN_FILE_BUTTON 1
#define SAVE_FILE_BUTTON 2
#define COMPILE_BUTTON 3

using namespace std;

char erroMsg[200];
int error=0;

//************************analise lexica****************************

/* legenda: 1- Operador, 2- Keyword, 3- Integer, 4- float, 5- Identifier, 6- delimiter, 7- finalDelimeter,8- InvalidIdentifier*/
typedef struct lista{
    char token[35];
    int cod;
    struct lista* prox;
    int line;
}Lista;

Lista* lst_cria(void){
    return NULL;
}

Lista* lst_insere(Lista* l, char token[], int cod, int line){
    Lista* no = (Lista*)malloc(sizeof(Lista));
    strcpy(no->token,token);
    no->cod=cod;
    no->line=line;
    no->prox=l;
    return no;
}

Lista* lst_cpy_inver(Lista* dest, Lista* source){
    Lista* p;
    p=source;
    while(p!=NULL){
        dest=lst_insere(dest,p->token,p->cod,p->line);
        p=p->prox;
    }
    return dest;
}

void lst_imprime(Lista* l){
    Lista* p;
    p=l;
    while(p!=NULL){
        cout << "token: " << p->token << endl;
        cout << "codigo: " << p->cod << endl;
        cout << "linha: " << p->line << endl;
        p=p->prox;
    }
}

int lst_vazia(Lista* l){
    return(l==NULL);
}

void lst_libera(Lista* l){
    Lista* p;
    p=l;
    while(p!=NULL){
        Lista* t = p->prox;
        free(p);
        p=t;
    }
}

bool isKeyword(char* token) {
    if (!strcmp(token, "int") || !strcmp(token, "float"))
        return (true);
    return (false);
}

//L = {w|w (+|-|num)(num)num*}
int AutomatoInteger (char *str){
    //inicial 0, final 2
    int i;
    /* Declarando a matriz de estados do automato M */
    int M[3][3]={{1, -1, -1},{1, -1, -1},{2, 2, 2}};

    /* Definindo o estado inicial */
    int e = 0;

    /* Recebera a indexacao referente ao caractere*/
    int c;

    /* Percorrendo toda a sentenca de avaliacao*/
    for(i=0;str[i]!='\0';i++){
        switch(str[i]){
            case '0': c=2; break;
            case '1': c=2; break;
            case '2': c=2; break;
            case '3': c=2; break;
            case '4': c=2; break;
            case '5': c=2; break;
            case '6': c=2; break;
            case '7': c=2; break;
            case '8': c=2; break;
            case '9': c=2; break;
            case '+': c=0; break;
            case '-': c=1; break;
            default:
                return 0;
        }

        /* Definindo o sistema de transicao*/
        e = M[c][e];
        if(e==-1){
            return 0;
        }
    }
    if(e==2)
        return 1;
    else
        return 0;
}

//L = {w|w (+|-|num)(num)num*(.)(num)num*}
int AutomatoFloat (char *str){
    //inicial 0, final 4
    int i;
    /* Declarando a matriz de estados do automato M */
    int M[4][5]={{1, -1, -1, -1, -1}, {1, -1, -1, -1, -1}, {2, 2, 2, 4, 4}, {-1, -1, 3, -1, -1}};

    /* Definindo o estado inicial */
    int e = 0;

    /* Recebera a indexacao referente ao caractere*/
    int c;

    /* Percorrendo toda a sentenca de avaliacao*/
    for(i=0;str[i]!='\0';i++){
        switch(str[i]){
            case '0': c=2; break;
            case '1': c=2; break;
            case '2': c=2; break;
            case '3': c=2; break;
            case '4': c=2; break;
            case '5': c=2; break;
            case '6': c=2; break;
            case '7': c=2; break;
            case '8': c=2; break;
            case '9': c=2; break;
            case '+': c=0; break;
            case '-': c=1; break;
            case '.': c=3; break;
            default:
                return 0;
        }

        /* Definindo o sistema de transicao*/
        e = M[c][e];
        if(e==-1)
            return 0;
    }
    if(e==4)
        return 1;
    else
        return 0;
}

//L = {w|w letra(letra|numero)*}
int AutomatoIdentifier (char *str){
    int i;
    /* Declarando a matriz de estados do automato M */
    int M[2][2]={{-1, 1},{1, 1}};

    /* Definindo o estado inicial */
    int e = 0;

    /* Recebera a indexacao referente ao caractere*/
    int c;

    /* Percorrendo toda a sentenca de avaliacao*/
    for(i=0;str[i]!='\0';i++){
        switch(str[i]){
            case 'A': c=1; break; case 'a': c=1; break;
            case 'B': c=1; break;case 'b': c=1; break;
            case 'C': c=1; break;case 'c': c=1; break;
            case 'D': c=1; break;case 'd': c=1; break;
            case 'E': c=1; break;case 'e': c=1; break;
            case 'F': c=1; break;case 'f': c=1; break;
            case 'G': c=1; break;case 'g': c=1; break;
            case 'H': c=1; break;case 'h': c=1; break;
            case 'I': c=1; break;case 'i': c=1; break;
            case 'J': c=1; break;case 'j': c=1; break;
            case 'K': c=1; break;case 'k': c=1; break;
            case 'L': c=1; break;case 'l': c=1; break;
            case 'M': c=1; break;case 'n': c=1; break;
            case 'O': c=1; break;case 'o': c=1; break;
            case 'P': c=1; break;case 'p': c=1; break;
            case 'Q': c=1; break;case 'q': c=1; break;
            case 'R': c=1; break;case 'r': c=1; break;
            case 'S': c=1; break;case 's': c=1; break;
            case 'T': c=1; break;case 't': c=1; break;
            case 'U': c=1; break;case 'u': c=1; break;
            case 'V': c=1; break;case 'v': c=1; break;
            case 'W': c=1; break;case 'w': c=1; break;
            case 'X': c=1; break;case 'x': c=1; break;
            case 'Y': c=1; break;case 'y': c=1; break;
            case 'Z': c=1; break;case 'z': c=1; break;
            case '0': c=0; break;
            case '1': c=0; break;
            case '2': c=0; break;
            case '3': c=0; break;
            case '4': c=0; break;
            case '5': c=0; break;
            case '6': c=0; break;
            case '7': c=0; break;
            case '8': c=0; break;
            case '9': c=0; break;
            default:
                return 0;
        }

        /* Definindo o sistema de transicao*/
        e = M[c][e];
        if(e==-1)
            return 0;
    }
    if(e==1)
        return 1;
    else
        return 0;
}

bool isDelimiterfinal(char ch){
    if (ch == ';')
        return (true);
    return (false);
}

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch){
    if (ch == ' ' || ch == ';' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == '=' || ch == '(' ||
        ch == ')' || ch == '\n' || ch == '\0' || ch == '\'' || ch == '"')
        return (true);
    return (false);
}

bool isDelimiterChar(char ch){
    if (ch == ',' || ch == '(' || ch == ')' ||
        ch == '\'' || ch == '"')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch){
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '=')
        return (true);
    return (false);
}

Lista* separateAndAnalyze(char *parse, Lista* l, int line);
char* subString(char* str, int left, int right);

Lista* analise_lexica(char *iParse, int len, Lista* l, int line){
    char parse[len];
    strcpy(parse,iParse);
    l = separateAndAnalyze(parse, l, line);
    return l;
}

Lista* separateAndAnalyze(char *parse, Lista* l, int line){
    int left, right, len, buffer=0,temPontoEVirgula=0;
    char linha[100];
    strcpy(linha,parse);
    char *token = strtok(parse,";");

    while(token != NULL){
        buffer+=strlen(token);
        if(linha[buffer]==';'){
            temPontoEVirgula=1;
            buffer++;
        }
        left=0, right=0, len = strlen(token);
        while (right <= len && left <= right) {
            if (isDelimiter(token[right]) == false)
                right++;

            if (isDelimiter(token[right]) == true && left == right) {
                if (isOperator(token[right]) == true){
                    //cout << token[right] << " IS AN OPERATOR" << endl;
                    char tokenCH[2];tokenCH[0]=token[right];tokenCH[1]='\0';
                    l = lst_insere(l, tokenCH, 1, line);
                }
                else if(isDelimiterChar(token[right]) == true){
                    //if(token[right]==';')
                        //cout << token[right] << endl<<endl<<endl;
                    char tokenCH[2];tokenCH[0]=token[right];tokenCH[1]='\0';
                    l = lst_insere(l, tokenCH, 6, line);
                }
                else if(isDelimiterfinal(token[right]) == true){
                    //cout << token[right] << endl<<endl<<endl;
                    char tokenCH[2];tokenCH[0]=token[right];tokenCH[1]='\0';
                    l = lst_insere(l, tokenCH, 7, line);
                }
                right++;
                left = right;
            }
            else if (isDelimiter(token[right]) == true && left != right || (right == len && left != right)) {
                char* subStr = subString(token, left, right - 1);
                if (isKeyword(subStr) == true){
                    //cout << subStr<< " IS A KEYWORD" << endl;
                    l = lst_insere(l, subStr, 2, line);
                }
                else if (AutomatoInteger(subStr) == true){
                    //cout << subStr << " IS AN INTEGER" << endl;
                    l = lst_insere(l, subStr, 3, line);
                }
                else if (AutomatoFloat(subStr) == true){
                    //cout << subStr << " IS A float NUMBER" << endl;
                    l = lst_insere(l, subStr, 4, line);
                }
                else if (AutomatoIdentifier(subStr) == true && isDelimiter(token[right - 1]) == false){
                    if(strlen(subStr)>1){
                        char str[10];
                        sprintf(str, "%d", line+1);
                        strcpy(erroMsg, "erro lexico\n");
                        strcat(erroMsg, "Linha: ");
                        strcat(erroMsg, str);
                        strcat(erroMsg, " ");
                        strcat(erroMsg, subStr);
                        strcat(erroMsg, " eh muito grande este compilador nao esta apto a lidar com indentificadores maiores do que 1 caractere");
                        error=1;
                        break;
                    }
                    //cout << subStr << " IS A VALID IDENTIFIER" << endl;
                    l = lst_insere(l, subStr, 5, line);
                }
                //esta sendo carregado algum caractere oculto pela interface causando mal funcionamento desta parte
                /*else if (AutomatoIdentifier(subStr) == false && isDelimiter(token[right - 1]) == false){
                    //cout << subStr << " IS NOT A VALID IDENTIFIER" << endl;
                    char str[10];
                    strcpy(erroMsg, "erro lexico\n");
                    strcat(erroMsg, "Iidentificador invalido ");
                    strcat(erroMsg, subStr);
                    strcat(erroMsg, " na linha: ");
                    sprintf(str, "%d", line+1);
                    strcat(erroMsg, str);
                    error=1;
                    break;
                    l = lst_insere(l, subStr, 8, line);
                }*/
                left = right;
            }
        }
        if(temPontoEVirgula){
            l = lst_insere(l, ";", 7, line);
            temPontoEVirgula=0;
        }
        token = strtok(NULL,";");
    }
    return l;
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right) {
    int i;
    char *subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++){
        subStr[i - left] = str[i];
    }
    subStr[right - left + 1] = '\0';

    return (subStr);
}

//**********************analise sintatica*******************************

int blockWeakTree = 0;
stack<char>pilha_arvore;
stack<char>pilha_arvore_exp;
int blockWeakTreeS = 0;
stack<char>pilha_gen_arvS;
stack<char>pilha_gen_arvS_exp;

typedef struct no{
    char info[35];
    struct no *esq;
    struct no *center;
    struct no *dir;
}Nodo;

typedef struct noS{
    char info[35];
    struct noS *esq;
    struct noS *dir;
}NodoS;

typedef struct quadrupla{
    char op[1];
    char arg1[10];
    char arg2[10];
    char result[10];
    struct quadrupla* prox;
}Quadrupla;

typedef struct arv{
    Nodo *raiz;
}Arv;

typedef struct arvS{
    NodoS *raiz;
}ArvS;

Arv* arv_cria(void){
    Arv* arv = (Arv*)malloc(sizeof(Arv));
    arv->raiz = NULL;
    return arv;
}

ArvS* arv_criaS(void){
    ArvS* arvS = (ArvS*)malloc(sizeof(ArvS));
    arvS->raiz = NULL;
    return arvS;
}

Nodo* arv_busca_no(Nodo* raiz, char *info);

Nodo* arv_busca(Arv* arv, char *info){
    return arv_busca_no(arv->raiz, info);
}

Nodo* arv_busca_no(Nodo* raiz, char *info){
    if(raiz==NULL){
        return raiz;
    }
    else if(strcmp(raiz->info, info)==0 && (raiz->esq==NULL || raiz->center==NULL || raiz->dir==NULL)){
        return raiz;
    }

    Nodo *no;
    no = arv_busca_no(raiz->esq, info);
    if(no==NULL)
        no = arv_busca_no(raiz->center, info);
    if(no==NULL)
        no = arv_busca_no(raiz->dir, info);
    return no;
}

//função para corrigir ambiguidade do E;E+S, M;S-M, M;M*D, D;D/P, P;(E)
void check_lower(Nodo *raiz, Nodo *raiz2, char *info, char *info2){
    if(raiz==NULL || strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0 || strcmp(raiz->info, "-")==0 ||
       strcmp(raiz->info, "(")==0 || strcmp(raiz->info, ")")==0 || strcmp(raiz->info, "v")==0 || strcmp(raiz->info, "&")==0 || blockWeakTree)
        return;

    if(raiz->esq==NULL && raiz->center==NULL){
        char str[2];
        if(strcmp(raiz->info, "E")==0 && strcmp(raiz->dir->info, "S")==0 && info[0]=='+'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        else if(strcmp(raiz->info, "S")==0 && strcmp(raiz->dir->info, "M")==0 && info[0]=='-'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        else if(strcmp(raiz->info, "M")==0 && strcmp(raiz->dir->info, "D")==0 && info[0]=='*'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        else if(strcmp(raiz->info, "D")==0 && strcmp(raiz->dir->info, "P")==0 && info[0]=='/'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        else if(strcmp(raiz->info, "P")==0 && strcmp(raiz->dir->info, ")")==0 && info[0]=='E'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
    }


    check_lower(raiz->dir, raiz2->dir, info, info2);
    check_lower(raiz->center, raiz2->center, info, info2);
    check_lower(raiz->esq, raiz2->esq, info, info2);
}


void bloqueia_nao_terminais_filhos(Nodo *raiz, Nodo *raiz2){
    if(raiz==NULL || strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0 || strcmp(raiz->info, "/")==0 ||
       strcmp(raiz->info, "(")==0 || strcmp(raiz->info, ")")==0 || strcmp(raiz->info, "v")==0 || strcmp(raiz->info, "&")==0)
        return;

    if(raiz->esq==NULL && raiz->center==NULL){
        raiz->center = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz->center->info, "&");
        raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;
        raiz->esq = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz->esq->info, "&");
        raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

        raiz2->center = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz2->center->info, "&");
        raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;
        raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz2->esq->info, "&");
        raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;
    }

    bloqueia_nao_terminais_filhos(raiz->dir, raiz2->dir);
    bloqueia_nao_terminais_filhos(raiz->center, raiz2->center);
    bloqueia_nao_terminais_filhos(raiz->esq, raiz2->esq);
}

//Nodo* inserir_arv_no(Nodo* raiz, char *info);

void arv_insert_content_no(Nodo* raiz, Nodo* raiz2, char *info, char *info2){
    if(raiz==NULL || strcmp(raiz->info, "+")==0 || strcmp(raiz->info, "-")==0 || strcmp(raiz->info, "*")==0 || strcmp(raiz->info, "/")==0 ||
       strcmp(raiz->info, "(")==0 || strcmp(raiz->info, ")")==0 || strcmp(raiz->info, "v")==0 || strcmp(raiz->info, "&")==0 || blockWeakTree)
        return;

    char str[2];
    if(raiz->esq==NULL && raiz->center==NULL && raiz->dir==NULL){
        str[0]=info[0];str[1]='\0';
        raiz->dir = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz->dir->info, str);
        raiz->dir->esq = raiz->dir->center = raiz->dir->dir = NULL;

        str[0]=info2[0];str[1]='\0';
        raiz2->dir = (Nodo*)malloc(sizeof(Nodo));
        strcpy(raiz2->dir->info, str);
        raiz2->dir->esq = raiz2->dir->center = raiz2->dir->dir = NULL;

        if(info[0]=='v'){
            raiz->center = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->center->info, "&");
            raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, "&");
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            raiz2->center = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->center->info, "&");
            raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, "&");
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;
        }

        blockWeakTree=1;
        return;
    }

    else if(raiz->esq==NULL && raiz->center==NULL){
        //expresão E->E+S
        if(strcmp(raiz->info, "E")==0 && strcmp(raiz->dir->info, "S")==0 && info[0]=='+'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        //expressão S->S-M
        else if(strcmp(raiz->info, "S")==0 && strcmp(raiz->dir->info, "M")==0 && info[0]=='-'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        //expressão M->M*D
        else if(strcmp(raiz->info, "M")==0 && strcmp(raiz->dir->info, "D")==0 && info[0]=='*'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        //expressão D->D/P
        else if(strcmp(raiz->info, "D")==0 && strcmp(raiz->dir->info, "P")==0 && info[0]=='/'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        //expressão P->(E)
        else if(strcmp(raiz->info, "P")==0 && strcmp(raiz->dir->info, ")")==0 && info[0]=='E'){
            check_lower(raiz->dir, raiz2->dir, info, info2);
            if(blockWeakTree==0){
                str[0]=info[0];str[1]='\0';
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, str);
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;

                str[0]=info2[0];str[1]='\0';
                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, str);
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;

                blockWeakTree=1;
                return;
            }
        }
        //bloqueia os esq e center do nó
        else if(strcmp(raiz->dir->info, ")")==0 && info[0]!='E'){
            raiz->center = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->center->info, "&");
            raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, "&");
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            raiz2->center = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->center->info, "&");
            raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, "&");
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;
        }
        if(raiz->dir->esq!=NULL && raiz->dir->center!=NULL){
            if(strcmp(raiz->dir->esq->info, "&")==0 && strcmp(raiz->dir->center->info, "&")==0){
                raiz->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->center->info, "&");
                raiz->center->esq = raiz->center->center = raiz->center->dir = NULL;
                raiz->esq = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz->esq->info, "&");
                raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

                raiz2->center = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->center->info, "&");
                raiz2->center->esq = raiz2->center->center = raiz2->center->dir = NULL;
                raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
                strcpy(raiz2->esq->info, "&");
                raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;
            }
        }
    }
    else if(raiz->esq==NULL){
        //expresão E->E+S
        if(strcmp(raiz->info, "E")==0 && strcmp(raiz->center->info, "+")==0 && strcmp(raiz->dir->info, "S")==0 && info[0]=='E'){
            str[0]=info[0];str[1]='\0';
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, str);
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            str[0]=info2[0];str[1]='\0';
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, str);
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;

            blockWeakTree=1;
            return;
        }
        //expressão S->S-M
        else if(strcmp(raiz->info, "S")==0 && strcmp(raiz->center->info, "-")==0 && strcmp(raiz->dir->info, "M")==0 && info[0]=='S'){
            str[0]=info[0];str[1]='\0';
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, str);
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            str[0]=info2[0];str[1]='\0';
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, str);
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;

            blockWeakTree=1;
            return;
        }
        //expressão M->M*D
        else if(strcmp(raiz->info, "M")==0 && strcmp(raiz->center->info, "*")==0 && strcmp(raiz->dir->info, "D")==0 && info[0]=='M'){
            str[0]=info[0];str[1]='\0';
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, str);
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            str[0]=info2[0];str[1]='\0';
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, str);
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;

            blockWeakTree=1;
            return;
        }
        //expressão D->D/P
        else if(strcmp(raiz->info, "D")==0 && strcmp(raiz->center->info, "/")==0 && strcmp(raiz->dir->info, "P")==0 && info[0]=='D'){
            str[0]=info[0];str[1]='\0';
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, str);
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            str[0]=info2[0];str[1]='\0';
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, str);
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;

            blockWeakTree=1;
            return;
        }
        //expressão P->(E)
        else if(strcmp(raiz->info, "P")==0 && strcmp(raiz->center->info, "E")==0 && strcmp(raiz->dir->info, ")")==0 && info[0]=='('){
            str[0]=info[0];str[1]='\0';
            raiz->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz->esq->info, str);
            raiz->esq->esq = raiz->esq->center = raiz->esq->dir = NULL;

            str[0]=info2[0];str[1]='\0';
            raiz2->esq = (Nodo*)malloc(sizeof(Nodo));
            strcpy(raiz2->esq->info, str);
            raiz2->esq->esq = raiz2->esq->center = raiz2->esq->dir = NULL;
            bloqueia_nao_terminais_filhos(raiz->center, raiz2->center);

            blockWeakTree=1;
            return;
        }
    }

    arv_insert_content_no(raiz->dir, raiz2->dir, info, info2);
    arv_insert_content_no(raiz->center, raiz2->center, info, info2);
    arv_insert_content_no(raiz->esq, raiz2->esq, info, info2);
}

void inserir_arv(Arv* arv, Arv* arv2, char *info, char *info2){
    if(arv->raiz==NULL){
        char str[1];
        str[0]=info[0];str[1]='\0';
        arv->raiz = (Nodo*)malloc(sizeof(Nodo));
        strcpy(arv->raiz->info, str);
        arv->raiz->esq = arv->raiz->center = arv->raiz->dir = NULL;

        str[0]=info2[0];str[1]='\0';
        arv2->raiz = (Nodo*)malloc(sizeof(Nodo));
        strcpy(arv2->raiz->info, str);
        arv2->raiz->esq = arv2->raiz->center = arv2->raiz->dir = NULL;
    }
    else{
        arv_insert_content_no(arv->raiz, arv2->raiz, info, info2);
        blockWeakTree=0;
    }

}

void cria_pilha_gen(Nodo* raiz, Nodo* raiz2){
    if(raiz!=NULL && raiz->info[0]!='&'){
        if(raiz->info[0]=='v' || raiz->info[0]=='+' || raiz->info[0]=='-' || raiz->info[0]=='*' || raiz->info[0]=='/'){
            pilha_gen_arvS.push(raiz->info[0]);
            pilha_gen_arvS_exp.push(raiz2->info[0]);
        }
        cria_pilha_gen(raiz->dir, raiz2->dir);
        cria_pilha_gen(raiz->esq, raiz2->esq);
        cria_pilha_gen(raiz->center, raiz2->center);
	}
}

void check_lowerS(NodoS* raiz, NodoS* raiz2){
    if(raiz==NULL || strcmp(raiz->info, "v")==0 || blockWeakTreeS)
        return;

    if(raiz->esq==NULL &&!blockWeakTreeS){
        char info[2];
        info[0]=pilha_gen_arvS.top();info[1]='\0';
        raiz->esq = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz->esq->info, info);
        raiz->esq->esq = raiz->esq->dir = NULL;
        pilha_gen_arvS.pop();

        info[0]=pilha_gen_arvS_exp.top();info[1]='\0';
        raiz2->esq = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz2->esq->info, info);
        raiz2->esq->esq = raiz2->esq->dir = NULL;
        pilha_gen_arvS_exp.pop();

        blockWeakTreeS=1;
        return;
    }
    else if(raiz->esq->info[0]=='+' || raiz->esq->info[0]=='-' || raiz->esq->info[0]=='*' || raiz->esq->info[0]=='/')
        check_lowerS(raiz->esq, raiz2->esq);
    if(raiz->dir==NULL && !blockWeakTreeS){
        char info[2];
        info[0]=pilha_gen_arvS.top();info[1]='\0';
        raiz->dir = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz->dir->info, info);
        raiz->dir->esq = raiz->dir->dir = NULL;
        pilha_gen_arvS.pop();

        info[0]=pilha_gen_arvS_exp.top();info[1]='\0';
        raiz2->dir = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz2->dir->info, info);
        raiz2->dir->esq = raiz2->dir->dir = NULL;
        pilha_gen_arvS_exp.pop();

        blockWeakTreeS=1;
        return;
    }
    check_lowerS(raiz->esq, raiz2->esq);
    check_lowerS(raiz->dir, raiz2->dir);
}

void constroi_arvS(NodoS* raiz, NodoS* raiz2){
    if(raiz==NULL || strcmp(raiz->info, "v")==0 || blockWeakTreeS)
        return;

    if(raiz->esq==NULL &&!blockWeakTreeS){
        char info[2];
        info[0]=pilha_gen_arvS.top();info[1]='\0';
        raiz->esq = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz->esq->info, info);
        raiz->esq->esq = raiz->esq->dir = NULL;
        pilha_gen_arvS.pop();

        info[0]=pilha_gen_arvS_exp.top();info[1]='\0';
        raiz2->esq = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz2->esq->info, info);
        raiz2->esq->esq = raiz2->esq->dir = NULL;
        pilha_gen_arvS_exp.pop();

        blockWeakTreeS=1;
        return;
    }
    else if(raiz->esq->info[0]=='+' || raiz->esq->info[0]=='-' || raiz->esq->info[0]=='*' || raiz->esq->info[0]=='/')
        check_lowerS(raiz->esq, raiz2->esq);

    if(raiz->dir==NULL && !blockWeakTreeS){
        char info[2];
        info[0]=pilha_gen_arvS.top();info[1]='\0';
        raiz->dir = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz->dir->info, info);
        raiz->dir->esq = raiz->dir->dir = NULL;
        pilha_gen_arvS.pop();

        info[0]=pilha_gen_arvS_exp.top();info[1]='\0';
        raiz2->dir = (NodoS*)malloc(sizeof(NodoS));
        strcpy(raiz2->dir->info, info);
        raiz2->dir->esq = raiz2->dir->dir = NULL;
        pilha_gen_arvS_exp.pop();

        blockWeakTreeS=1;
        return;
    }

    constroi_arvS(raiz->esq, raiz2->esq);
    constroi_arvS(raiz->dir, raiz2->dir);
}

void simplifica_arvore_fraca(Arv* arv, Arv* arv2, ArvS* arvS, ArvS* arvS2){
    cria_pilha_gen(arv->raiz, arv2->raiz);
    char info[2];
    if(arvS->raiz==NULL){
        info[0]=pilha_gen_arvS.top();info[1]='\0';
        arvS->raiz = (NodoS*)malloc(sizeof(NodoS));
        strcpy(arvS->raiz->info, info);
        arvS->raiz->esq = arvS->raiz->dir = NULL;
        pilha_gen_arvS.pop();

        info[0]=pilha_gen_arvS_exp.top();info[1]='\0';
        arvS2->raiz = (NodoS*)malloc(sizeof(NodoS));
        strcpy(arvS2->raiz->info, info);
        arvS2->raiz->esq = arvS2->raiz->dir = NULL;
        pilha_gen_arvS_exp.pop();
    }
    while(!pilha_gen_arvS.empty()){
        constroi_arvS(arvS->raiz, arvS2->raiz);
        blockWeakTreeS=0;
    }
}

void arv_imprime_no(Nodo* raiz);

void arv_imprime(Arv* arv){
    return arv_imprime_no(arv->raiz);
}

void arv_imprime_no(Nodo* raiz){
	printf("<");
	if(raiz!=NULL && raiz->info[0]!='&'){
        printf("%s",raiz->info);
        arv_imprime_no(raiz->esq);
        arv_imprime_no(raiz->center);
        arv_imprime_no(raiz->dir);
	}
	printf(">");
}

void arv_imprime_noS(NodoS* raiz){
	printf("<");
	if(raiz!=NULL){
        printf("%s",raiz->info);
        arv_imprime_noS(raiz->esq);
        arv_imprime_noS(raiz->dir);
	}
	printf(">");
}

void liberar_avr_no(Nodo* raiz);

void liberar_avr(Arv* arv){
    liberar_avr_no(arv->raiz);
    free(arv);
}

void liberar_avr_no(Nodo* raiz){
    if(raiz!=NULL){
        liberar_avr_no(raiz->esq);
        liberar_avr_no(raiz->center);
        liberar_avr_no(raiz->dir);
        free(raiz);
    }
}

void liberar_avr_noS(NodoS* raiz){
    if(raiz!=NULL){
        liberar_avr_noS(raiz->esq);
        liberar_avr_noS(raiz->dir);
        free(raiz);
    }
}

int AutomatoM(char *str, char *str2, int line){
    /* concatenando o simbolo delimitador na sentenca */
    strcat(str,"$");
    strcat(str2,"$");

    /* Declarando a tabela sintatica para o automato M */
    char M[13][8]={{'D', '\0', '\0', '\0', '\0', 'D', '\0', '\0'}, {'R', 'D', '\0', '\0', '\0', 'R', '\0', 'R'}, {'R', 'R', 'D', '\0', '\0', 'R', '\0', 'R'}, {'R', 'R', 'R', 'D', '\0', 'R', '\0', 'R'}, {'R', 'R', 'R', 'R', '\0', 'R', '\0', 'R'},
                    {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'}, {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'}, {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'}, {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'}, {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'},
                    {'R', 'R', 'R', 'R', '\0', 'R', '\0', 'R'}, {'R', 'R', 'R', 'R', '\0', 'R', '\0', 'R'}, {'\0', '\0', '\0', '\0', 'D', '\0', 'D', '\0'}};

    int QLinhasProducoes=10;
    char producoes[QLinhasProducoes][6]={{"E;E+S"},{"E;S"},{"S;S-M"},{"S;M"},{"M;M*D"},{"M;D"},{"D;D/P"},{"D;P"},{"P;(E)"},{"P;v"}};

    /*Declarando a pilha*/
    stack<char>pilha;
    stack<char>pilha_aux;

    /* Colocando o simbolo delimitador na pilha*/
    pilha.push('$');

    /* Recebera a indexação referente ao matriz*/
    int c,l,i;
    /* Recebera as produções*/
    char Prod[4];

    int parentese=0;
    i=0;
    while(str[i]!='$'){
        if(str[i]=='(')
            parentese++;
        else if(str[i]==')')
            parentese--;
        i++;
    }
    if(parentese>0){
        char temp[10];
        sprintf(temp, "%d", line+1);
        strcpy(erroMsg, "erro Sintatico\n");
        strcat(erroMsg, "Linha: ");
        strcat(erroMsg, temp);
        strcat(erroMsg, " esperava )");
        error=2;
    }
    else if(parentese<0){
        char temp[10];
        sprintf(temp, "%d", line+1);
        strcpy(erroMsg, "erro Sintatico\n");
        strcat(erroMsg, "Linha: ");
        strcat(erroMsg, temp);
        strcat(erroMsg, " esperava (");
        error=2;
    }

    int k,QProd;
    /* Percorrendo toda a sentenca de avaliacao*/
    i=0;
    while(str[i]!='\0' && error==0){
        switch(str[i]){
            case '+':
                c=0;
                break;
            case '-':
                c=1;
                break;
            case '*':
                c=2;
                break;
            case '/':
                c=3;
                break;
            case '(':
                c=4;
                break;
            case ')':
                c=5;
                break;
            case 'v':
                c=6;
                break;
            case '$':
                c=7;
                break;
            default:
                return 0;
        }

        while(1){
            switch(pilha.top()){
                case 'E':
                    l=0;
                    break;
                case 'S':
                    l=1;
                    break;
                case 'M':
                    l=2;
                    break;
                case 'D':
                    l=3;
                    break;
                case 'P':
                    l=4;
                    break;
                case '+':
                    l=5;
                    break;
                case '-':
                    l=6;
                    break;
                case '*':
                    l=7;
                    break;
                case '/':
                    l=8;
                    break;
                case '(':
                    l=9;
                    break;
                case ')':
                    l=10;
                    break;
                case 'v':
                    l=11;
                    break;
                case '$':
                    l=12;
                    break;
                default:
                    return 0;
            }

            /* Escolhendo a produção a ser aplicada pela tabela sintática */

            char Nprod = M[l][c];
            int producoes_compativeis[2];

            /* Fazendo equivalência entre a produção e ordem inversa e o seu número da tabela */
            switch(Nprod){
                case 'D':
                    pilha.push(str[i]);
                    pilha_arvore.push(str[i]);
                    pilha_arvore_exp.push(str2[i]);
                    i++;
                    break;
                case 'R':
                    QProd=0;
                    for(int j=0;j<QLinhasProducoes;j++){
                        k = strlen(producoes[j]);
                        if(producoes[j][k-1]==pilha.top()){
                            producoes_compativeis[QProd] = j;
                            QProd++;

                        }
                    }

                    if(QProd==1){
                        pilha.pop();
                        pilha.push(producoes[producoes_compativeis[QProd-1]][0]);
                        pilha_arvore.push(producoes[producoes_compativeis[QProd-1]][0]);
                        pilha_arvore_exp.push(producoes[producoes_compativeis[QProd-1]][0]);
                    }
                    else{
                        int tamanho=0,block;
                        char producao_comp[5];
                        for(int j=0;j<QProd;j++){//produção maior precisa vim antes para está implentação funcionar
                            for(k=strlen(producoes[producoes_compativeis[j]])-1;k>1;k--){
                                pilha_aux.push(pilha.top());
                                producao_comp[tamanho]=pilha.top();
                                tamanho++;
                                pilha.pop();
                                if(pilha.empty() || producoes[producoes_compativeis[j]][k]!=pilha_aux.top()){
                                    block=1;
                                    break;
                                }
                            }
                            producao_comp[tamanho]='\0';
                            if(block==0){
                                for(k=0;producao_comp[k]==pilha_aux.top();k++){
                                    pilha.push(pilha_aux.top());
                                    pilha_aux.pop();
                                    if(pilha_aux.empty())
                                        break;
                                }
                            };
                            if(pilha_aux.empty()){
                                for(k=strlen(producoes[producoes_compativeis[j]])-1;k>1;k--){
                                    pilha.pop();
                                }
                                pilha.push(producoes[producoes_compativeis[j]][0]);
                                pilha_arvore.push(producoes[producoes_compativeis[j]][0]);
                                pilha_arvore_exp.push(producoes[producoes_compativeis[j]][0]);
                                break;
                            }
                            else{
                                while(!pilha_aux.empty()){
                                    pilha.push(pilha_aux.top());
                                    pilha_aux.pop();
                                }
                            }
                            block=0;
                        }
                    }
                    break;
                default:
                    error=1;
                    return 0;
            }

            /* Verificando se há o sentencial no topo da pilha e se o delimitador é o caractere em analise*/
            if(pilha.top()=='E' && str[i]=='$')
                return 1;
            /* Mudança de estado do autômato */
            else
                break;

        }
    }
};

Quadrupla* quadrupla_cria(void);
void gera_codigo(NodoS* raiz, int vAmount, Lista* l);
Quadrupla* quadrupla_cpy_inver(Quadrupla* dest, Quadrupla* source);
void quadrupla_imprime(Quadrupla* q);
void quadrupla_libera(Quadrupla* q);
void imprime_cod_itermediario(Quadrupla* q);
void otimiza_cod_intermediario(Quadrupla* q);
void imprime_cod_itermediario_otimizado(Quadrupla* q);
void gera_mips(char *linha);
void gera_mips2(Quadrupla *q);

Quadrupla* q1;
Quadrupla* q2;
int erroSyntax=0;

stack<char>pilha_atribuicao;

int analise_sintatica(Lista* l){
    Lista* p;
    p=l;
    q1=quadrupla_cria();
    char atribuicao[2];
    int useExp=0,declaracao=0;
    while(p!=NULL && error==0){
        char exp[40];exp[0]='\0';
        char exp2[40];exp2[0]='\0';
        while(p->token[0]!=';' && p!=NULL){
            if(p->cod==2 && p->prox->cod==5 && p->prox->prox->cod==7){
                declaracao=1;
                p=p->prox->prox;
                break;
            }
            else if((p->cod==3 || p->cod==4 || p->cod==5 || p->token[0]==')') && p->prox!=NULL){
                if(p->prox->cod!=1 && p->prox->token[0]!=')' && p->prox->cod!=7){
                    char temp[10];
                    sprintf(temp, "%d", p->line+2);
                    strcpy(erroMsg, "erro Sintatico\n");
                    strcat(erroMsg, "Linha: ");
                    strcat(erroMsg, temp);
                    strcat(erroMsg, " falta ; antes de ");
                    strcat(erroMsg, p->prox->token);
                    error=1;
                    break;
                }
                else if(p->cod==5 && p->prox->cod==7)
                    useExp=1;
            }
            if(p->prox->token[0]=='='){
                pilha_atribuicao.push(p->token[0]);
            }
            if(useExp==0 && p->prox->token[0]=='+' || p->prox->token[0]=='-' || p->prox->token[0]=='*' ||
                    p->prox->token[0]=='/' || p->token[0]=='(' || p->token[0]==')'){
                useExp=1;
            }
            if(useExp){
                if(p->token[0]=='+' || p->token[0]=='-' || p->token[0]=='*' || p->token[0]=='/' ||
                   p->token[0]=='(' || p->token[0]==')')
                    strcat(exp2,p->token);
                else if(p->cod==3 || p->cod==4 || p->cod==5)
                    strcat(exp2,"v");
                strcat(exp,p->token);
            }
            else if(p->token[0]=='='){
                pilha_atribuicao.push(p->token[0]);
                useExp=1;
            }
            p=p->prox;
        }
        if(declaracao==0 && error==0){
            exp[strlen(exp)]='\0';
            int res = AutomatoM(exp2, exp, p->line);
            if(res==1){
                Arv* arv1 = arv_cria();
                Arv* arvExp1 = arv_cria();
                ArvS* arv2 = arv_criaS();
                ArvS* arvExp2 = arv_criaS();
                char topo_pilha[1];
                char topo_pilha_exp[1];
                int vAmount=0;
                while(!pilha_arvore.empty()){ //pilha_arvare_exp tem o mesmo tamnho que pilha_arvore
                    topo_pilha_exp[0]=pilha_arvore_exp.top();topo_pilha_exp[1]='\0';
                    topo_pilha[0]=pilha_arvore.top();topo_pilha[1]='\0';
                    inserir_arv(arv1, arvExp1, topo_pilha, topo_pilha_exp);
                    if(pilha_arvore.top()=='v')
                        vAmount++;
                    pilha_arvore.pop();
                    pilha_arvore_exp.pop();
                }
                simplifica_arvore_fraca(arv1, arvExp1, arv2, arvExp2);
                liberar_avr(arv1);
                liberar_avr(arvExp1);
                gera_codigo(arvExp2->raiz, vAmount, l);
                liberar_avr_noS(arv2->raiz);
            }
            else if(error!=2){
                erroSyntax++;
                if(erroSyntax<2){
                    char temp[10];
                    sprintf(temp, "%d", p->line+1);
                    strcpy(erroMsg, "erro Sintatico\n");
                    strcat(erroMsg, "Linha: ");
                    strcat(erroMsg, temp);
                    strcat(erroMsg, " erro de syntax");
                }
                break;
            }
            else
                break;
        }
        declaracao=0;
        useExp=0;
        p=p->prox;
    }
    if(error==0){
        q2=quadrupla_cria();
        q2=quadrupla_cpy_inver(q2,q1);
        quadrupla_imprime(q2);
        cout << endl;
        imprime_cod_itermediario(q2);
        otimiza_cod_intermediario(q2);
        cout << endl;
        imprime_cod_itermediario_otimizado(q2);
    }
    quadrupla_libera(q1);
}

//*********************** Semantica *************************************
Lista* var_declara;
Lista* lst_cpy_var(Lista* dest, Lista* source){
    Lista* p;
    p=source;
    while(p!=NULL){
        if(p->cod==2 && p->prox!=NULL){
            if(p->prox->prox!=NULL){
                if(p->prox->cod==5 && (p->prox->prox->token[0]=='=' || p->prox->prox->token[0]==';')){
                    dest=lst_insere(dest,p->prox->token,p->cod,p->prox->line);
                    gera_mips(p->prox->token);
                }
            }
        }
        p=p->prox;
    }
    return dest;
}


int busca_identificador(char *token, int line){
    Lista *p;
    p=var_declara;
    while(p!=NULL){
        if(strcmp(p->token,token)==0 && p->line<=line)
            return 1;
        p=p->prox;
    }
    return 0;
}

void checa_var_declara(Lista* l){
    Lista *p;
    p=l;
    int flag=0;
    while(p!=NULL){
        if(p->cod==5){
            flag = busca_identificador(p->token, p->line);
            if(!flag){
                char temp[10];
                sprintf(temp, "%d", p->line+1);
                strcpy(erroMsg, "erro Semantico\n");
                strcat(erroMsg, "Linha: ");
                strcat(erroMsg, temp);
                strcat(erroMsg, " ");
                strcat(erroMsg, p->token);
                strcat(erroMsg, " nao foi declarado neste escopo");
                error=1;
                break;
            }
        }
        p=p->prox;
    }
}



//************************Geracao do codigo ******************************
string quadruplaSTR;

Quadrupla* quadrupla_cria(void){
    return NULL;
}

Quadrupla* quadrupla_insere(Quadrupla* q, char op[], char arg1[], char arg2[], char result[]){
    Quadrupla* linha = (Quadrupla*)malloc(sizeof(Quadrupla));
    linha->op[0]=op[0];linha->op[1]='\0';
    strcpy(linha->arg1,arg1);
    strcpy(linha->arg2, arg2);
    strcpy(linha->result,result);
    linha->prox=q;
    return linha;
}

Quadrupla* quadrupla_cpy_inver(Quadrupla* dest, Quadrupla* source){
    Quadrupla* p;
    p=source;
    while(p!=NULL){
        dest=quadrupla_insere(dest,p->op,p->arg1,p->arg2,p->result);
        p=p->prox;
    }
    return dest;
}

void quadrupla_imprime(Quadrupla* q){
    Quadrupla* p;
    p=q;
    cout << "op| " << "arg1| " << "arg2| " << "result" << endl;
    quadruplaSTR = "op | arg1 |  arg2 | result \r\n";
    char tempOp[1];
    while(p!=NULL){
        tempOp[0]=p->op[0];tempOp[1]='\0';
        quadruplaSTR = quadruplaSTR + tempOp + " | ";
        quadruplaSTR = quadruplaSTR + p->arg1 + " | ";
        quadruplaSTR = quadruplaSTR + p->arg2 + " | ";
        quadruplaSTR = quadruplaSTR + p->result + " \r\n";
        cout << p->op[0] << " | ";
        cout << p->arg1 << " | ";
        cout << p->arg2 << " | ";
        cout << p->result << endl;
        p=p->prox;
    }
    cout << endl;
    cout << quadruplaSTR << endl;
}

void quadrupla_libera(Quadrupla* q){
    Quadrupla* p;
    p=q;
    while(p!=NULL){
        Quadrupla* t = p->prox;
        free(p);
        p=t;
    }
}

int num;


void le_e_altera_arvore2(NodoS* raiz, Lista* l){
    if(raiz==NULL)
        return;

    if(raiz->esq!=NULL && raiz->dir!=NULL){
        if(raiz->esq->info[0]!='+' && raiz->esq->info[0]!='-' && raiz->esq->info[0]!='*' && raiz->esq->info[0]!='/' &&
           raiz->dir->info[0]!='+' && raiz->dir->info[0]!='-' && raiz->dir->info[0]!='*' && raiz->dir->info[0]!='/'){
            char str[10], temp[10]={"_t"};
            int a1=0,a2=0;
            sprintf(str, "%d", num);
            strcat(temp,str);
            q1=quadrupla_insere(q1,raiz->info,raiz->esq->info,raiz->dir->info,temp);
            //quadrupla_imprime(q);
            strcpy(raiz->info,temp);
            raiz->esq=NULL;
            raiz->dir=NULL;
            num++;
        }
    }
    le_e_altera_arvore2(raiz->dir, l);
    le_e_altera_arvore2(raiz->esq, l);

}

void le_e_altera_arvore(NodoS* raiz, Lista* l){
    while(raiz->esq!=NULL && raiz->dir!=NULL){
        le_e_altera_arvore2(raiz, l);
    }
    if(!pilha_atribuicao.empty()){
        char str[10];
        char op[5], str2[10], *ttt;
        op[0]=pilha_atribuicao.top();op[1]='\0';
        pilha_atribuicao.pop();
        str2[0]=pilha_atribuicao.top();str2[1]='\0';
        q1=quadrupla_insere(q1,op,raiz->info,"&",str2);
        pilha_atribuicao.pop();
    }
}

void gera_codigo(NodoS* raiz, int vAmount, Lista* l){
    num=1;
    le_e_altera_arvore(raiz, l);
    //quadrupla_imprime(q);
}

string cod_intermediarioSTR;

void imprime_cod_itermediario(Quadrupla* q){
    Quadrupla *p;
    p=q;
    cod_intermediarioSTR="";
    char tempOp[1];
    while(p!=NULL){
        cod_intermediarioSTR = cod_intermediarioSTR + p->result + " := " + p->arg1 + " ";
        cout << p->result << " := ";
        cout << p->arg1 << " ";
        if(p->op[0]!='='){
            tempOp[0]=p->op[0];tempOp[1]='\0';
            cod_intermediarioSTR = cod_intermediarioSTR + tempOp + " ";
            cout << p->op[0] << " ";
        }
        if(strcmp(p->arg2,"&")!=0){
            cod_intermediarioSTR = cod_intermediarioSTR + p->arg2;
            cout << p->arg2;
        }
        cod_intermediarioSTR = cod_intermediarioSTR + "\r\n";
        cout << endl;
        p=p->prox;
    }
}

void otimiza_cod_intermediario(Quadrupla* q){
    Quadrupla *p;
    char temp[10], id[10];
    p=q;
    while(p!=NULL){
        //v+0 ou 0+v
        if(p->op[0]=='+' && (strcmp(p->arg1,"0")==0 || strcmp(p->arg2,"0")==0)){
            if(strcmp(p->arg1,"0")!=0){
                strcpy(id, p->arg1);
                strcpy(temp,p->result);
                strcpy(p->result,"&");
                if(strcmp(p->prox->arg1,temp)==0){
                    strcpy(p->prox->arg1,id);
                }
                else if(strcmp(p->prox->arg2,temp)==0){
                    strcpy(p->prox->arg2,id);
                }
            }
            else if(strcmp(p->arg2,"0")!=0){
                strcpy(id, p->arg2);
                strcpy(temp,p->result);
                strcpy(p->result,"&");
                if(strcmp(p->prox->arg1,temp)==0){
                    strcpy(p->prox->arg1,id);
                }
                else if(strcmp(p->prox->arg2,temp)==0){
                    strcpy(p->prox->arg2,id);
                }
            }
        }
        //v-0
        else if(p->op[0]=='-' && strcmp(p->arg2,"0")==0){
            strcpy(id, p->arg1);
            strcpy(temp,p->result);
            strcpy(p->result,"&");
            if(strcmp(p->prox->arg1,temp)==0){
                strcpy(p->prox->arg1,id);
            }
            else if(strcmp(p->prox->arg2,temp)==0){
                strcpy(p->prox->arg2,id);
            }
        }
        //v*1 ou 1*v
        else if(p->op[0]=='*' && (strcmp(p->arg1,"1")==0 || strcmp(p->arg2,"1")==0)){
            if(strcmp(p->arg1,"1")!=0){
                strcpy(id, p->arg1);
                strcpy(temp,p->result);
                strcpy(p->result,"&");
                if(strcmp(p->prox->arg1,temp)==0){
                    strcpy(p->prox->arg1,id);
                }
                else if(strcmp(p->prox->arg2,temp)==0){
                    strcpy(p->prox->arg2,id);
                }
            }
            else if(strcmp(p->arg2,"1")!=0){
                strcpy(id, p->arg2);
                strcpy(temp,p->result);
                strcpy(p->result,"&");
                if(strcmp(p->prox->arg1,temp)==0){
                    strcpy(p->prox->arg1,id);
                }
                else if(strcmp(p->prox->arg2,temp)==0){
                    strcpy(p->prox->arg2,id);
                }
            }
        }
        //v/1
        else if(p->op[0]=='/' && strcmp(p->arg2,"1")==0){
            strcpy(id, p->arg1);
            strcpy(temp,p->result);
            strcpy(p->result,"&");
            if(strcmp(p->prox->arg1,temp)==0){
                strcpy(p->prox->arg1,id);
            }
            else if(strcmp(p->prox->arg2,temp)==0){
                strcpy(p->prox->arg2,id);
            }
        }
        p=p->prox;
    }
}

string cod_intermediario_otimiSTR;

void imprime_cod_itermediario_otimizado(Quadrupla* q){
    Quadrupla *p;
    p=q;
    cod_intermediario_otimiSTR="";
    char tempOp[1];
    while(p!=NULL){
        if(strcmp(p->result,"&")!=0){
            cod_intermediario_otimiSTR = cod_intermediario_otimiSTR + p->result + " := " + p->arg1 + " ";
            cout << p->result << " := ";
            cout << p->arg1 << " ";
            if(p->op[0]!='='){
                tempOp[0]=p->op[0];tempOp[1]='\0';
                cod_intermediario_otimiSTR = cod_intermediario_otimiSTR + tempOp + " ";
                cout << p->op[0] << " ";
            }
            if(strcmp(p->arg2,"&")){
                cod_intermediario_otimiSTR = cod_intermediario_otimiSTR + p->arg2;
                cout << p->arg2;
            }

            cod_intermediario_otimiSTR = cod_intermediario_otimiSTR + "\r\n";
            cout << endl;
        }
        p=p->prox;
    }
    cout << endl << cod_intermediarioSTR << endl;
}

void gera_mips(char *var){
    FILE *p;
    p = fopen("saida.txt","a");

    if(p == NULL){
        printf("Arquivo nao pode ser aberto");
    }
    else{
        char line[100];
        strcpy(line, var);
        strcat(line, ": .word\n");
        fprintf(p, line);

        fclose(p);
    }
}

void gera_mips2(Quadrupla *q){
    FILE *p;
    p = fopen("saida.txt","a");
    if(p == NULL){
        printf("Arquivo nao pode ser aberto");
    }
    else{
        char line[100];
        Quadrupla *g;
        g=q;
        fprintf(p, "\nmain:\n\n");
        while(g!=NULL){
            if(g->op[0]=='+' || g->op[0]=='-'){
                if(g->op[0]=='-')
                    strcpy(line, "add ");
                else
                    strcpy(line, "sub ");
                if(g->result[0]=='_')
                    g->result[0]='$';
                strcat(line, g->result);
                strcat(line, ",");
                if(g->arg1[0]=='_')
                    g->arg1[0]='$';
                strcat(line, g->arg1);
                strcat(line, ",");
                if(g->arg2[0]=='_')
                    g->arg2[0]='$';
                strcat(line, g->arg2);
                strcat(line, "\n");
            }
            else if(g->op[0]=='*' || g->op[0]=='/'){
                strcpy(line, "li ");
                if(g->result[0]=='_')
                    g->result[0]='$';
                strcat(line, g->result);
                strcat(line, ",");
                if(g->arg1[0]=='_')
                    g->arg1[0]='$';
                strcat(line, g->arg1);
                strcat(line, "\n");
                if(g->op[0]=='*')
                    strcat(line, "mult ");
                else
                    strcat(line, "div ");
                strcat(line, g->result);
                strcat(line, ",");
                if(g->arg2[0]=='_')
                    g->arg2[0]='$';
                strcat(line, g->arg2);
                strcat(line, "\n");
            }
            if(g->op[0]=='='){
                strcpy(line, "lw ");
                strcat(line, g->result);
                strcat(line, ",");
                if(g->arg1[0]=='_')
                    g->arg1[0]='$';
                strcat(line, g->arg1);
                strcat(line, "\n");
            }
            if(g->result[0]!='&')
                fprintf(p, line);
            g=g->prox;
        }
        fclose(p);
    }
}

//interface
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddControls(HWND);

HWND hMainWindow,hEdit, hQuadrupla, hCod_inter, hCod_inter_otimi;

//main
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR atgs, int ncmdshow){

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    hMainWindow = CreateWindowW(L"myWindowClass",L"Compilador",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,1060,500,NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while(GetMessage(&msg,NULL,NULL,NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void display_file(char *path){
    FILE *file;
    file = fopen(path,"rb");
    fseek(file,0,SEEK_END);
    int _size = ftell(file);
    rewind(file);
    char *data = new char[_size+1];
    fread(data,_size,1,file);
    data[_size] = '\0';
    SetWindowText(hEdit,data);


    fclose(file);
}

void open_file(HWND hWnd){
    OPENFILENAME ofn;

    char file_name[200];

    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 200;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    //MessageBox(NULL,ofn.lpstrFile,"",MB_OK); //mostra o caminho do arquivo

    display_file(ofn.lpstrFile);
}

void write_file(char *path){
    FILE *file;
    file = fopen(path,"w");

    int _size = GetWindowTextLength(hEdit);
    char *data = new char[_size+1];
    GetWindowText(hEdit,data,_size+1);

    fwrite(data,_size+1,1,file);

    fclose(file);
}

void save_file(HWND hWnd){
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    GetSaveFileName(&ofn);

    write_file(ofn.lpstrFile);
}

void compilar(HWND hWnd){
    Lista* l;
    l=lst_cria();

    FILE *p;
    p = fopen("saida.txt", "w");
    fprintf(p,".data\n\n");
    fclose(p);

    int _size = GetWindowTextLength(hEdit);
    char *data = new char[_size+1];
    GetWindowText(hEdit,data,_size+1);
    //cout << data << endl << endl;
    char exp[100];
    int i=0,i2=0,numLinha=0;
    while(i<_size){
        exp[i2]=data[i];
        i++;
        i2++;
        if(data[i-1]==';'){
            exp[i2]='\0';
            l=analise_lexica(exp,100,l,numLinha);
            exp[0]='\0';
            i2=0;
        }
        if(data[i]=='\n')
            numLinha++;
    }

    Lista* l2;
    l2=lst_cria();

    if(error==0){
        l2=lst_cpy_inver(l2,l);
        analise_sintatica(l2);
    }
    lst_libera(l);
    if(error==0){
        var_declara=lst_cria();
        var_declara=lst_cpy_var(var_declara,l2);
        checa_var_declara(l2);
        lst_libera(var_declara);
        if(error==1)
            quadrupla_libera(q2);

    }
    lst_libera(l2);
    if(error==0){
        gera_mips2(q2);
        int i=0;
        char quadruplaCharArr[quadruplaSTR.length()];
        while(i<quadruplaSTR.length()){
            quadruplaCharArr[i]=quadruplaSTR[i];
            i++;
        }
        quadruplaCharArr[i]='\0';
        SetWindowText(hQuadrupla,quadruplaCharArr);
        i=0;
        char cod_intermediario_arr[cod_intermediarioSTR.length()];
        while(i<cod_intermediarioSTR.length()){
            cod_intermediario_arr[i]=cod_intermediarioSTR[i];
            i++;
        }
        cod_intermediario_arr[i]='\0';
        SetWindowText(hCod_inter, cod_intermediario_arr);
        i=0;
        char cod_intermediario_otimi_arr[cod_intermediario_otimiSTR.length()];
        while(i<cod_intermediario_otimiSTR.length()){
            cod_intermediario_otimi_arr[i]=cod_intermediario_otimiSTR[i];
            i++;
        }
        cod_intermediario_otimi_arr[i]='\0';
        SetWindowText(hCod_inter_otimi, cod_intermediario_otimi_arr);
        quadrupla_libera(q2);
    }
    if(error==1 || error==2){
        error=0;
        wchar_t wtext[201];
        if(erroSyntax<2){
            SetWindowText(hQuadrupla, "");
            SetWindowText(hCod_inter, "");
            SetWindowText(hCod_inter_otimi, "");

            mbstowcs(wtext, erroMsg, strlen(erroMsg)+1);
            LPWSTR ptr = wtext;
            MessageBoxW(hWnd,ptr,L"Erro!", MB_OK | MB_ICONEXCLAMATION);
        }
        cout << erroMsg << endl;
        strcpy(erroMsg,"");
        while(!pilha_arvore.empty()){
            pilha_arvore.pop();
            pilha_arvore_exp.pop();
        }
        while(!pilha_gen_arvS.empty()){
            pilha_gen_arvS.pop();
            pilha_gen_arvS_exp.pop();
        }
        if(erroSyntax<2 && erroSyntax>0)
            compilar(hWnd);
        else
            erroSyntax=0;
    }
}

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp){
    switch(msg)
    {
    case WM_COMMAND:
        {
            switch(wp)
            {
            case OPEN_FILE_BUTTON:
                open_file(hWnd);
                break;
            case SAVE_FILE_BUTTON:
                save_file(hWnd);
                break;
            case COMPILE_BUTTON:
                compilar(hWnd);
                break;
            }
        }
        break;
    case WM_CREATE:
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void AddControls(HWND hWnd){
    CreateWindowW(L"button",L"Abrir arquivo:", WS_VISIBLE | WS_CHILD,115,10,250,36,hWnd,(HMENU)OPEN_FILE_BUTTON,NULL,NULL);
    CreateWindowW(L"button",L"Salvar:", WS_VISIBLE | WS_CHILD,375,10,250,36,hWnd,(HMENU)SAVE_FILE_BUTTON,NULL,NULL);
    CreateWindowW(L"button",L"Compilar:", WS_VISIBLE | WS_CHILD,635,10,250,36,hWnd,(HMENU)COMPILE_BUTTON,NULL,NULL);
    hEdit = CreateWindowW(L"Edit",L"Insira o codigo aqui",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                  10,50,250,300,hWnd,NULL,NULL,NULL);
    hQuadrupla = CreateWindowW(L"Edit",L"Quadruplas",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                  270,50,250,300,hWnd,NULL,NULL,NULL);
    hCod_inter = CreateWindowW(L"Edit",L"Codigo Intermediario",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                  530,50,250,300,hWnd,NULL,NULL,NULL);
    hCod_inter_otimi = CreateWindowW(L"Edit",L"Codigo Intermediario otimizado",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                  790,50,250,300,hWnd,NULL,NULL,NULL);
}
