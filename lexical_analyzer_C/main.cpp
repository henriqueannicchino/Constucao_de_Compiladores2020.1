/*já havia mandado um antes mas optei por mandar outro este aqui não lê por arquivo mas
já mostra o funcionameto do analisador lexico de certo modo*/

#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

/* legenda: 1- Operador, 2- Keyword, 3- Integer, 4- float, 5- Identifier, 6- InvalidIdentifier*/
typedef struct lista{
    char lexem[20];
    int cod;
    struct lista* prox;
}Lista;

Lista* lst_cria(void){
    return NULL;
}

Lista* lst_insere(Lista* l, char lexem[], int cod){
    Lista* no = (Lista*)malloc(sizeof(Lista));
    strcpy(no->lexem,lexem);
    no->cod=cod;
    no->prox=l;
    return no;
}

Lista* lst_cpy_inver(Lista* dest, Lista* source){
    Lista* p;
    p=source;
    while(p!=NULL){
        dest=lst_insere(dest,p->lexem,p->cod);
        p=p->prox;
    }
    return dest;
}


void lst_imprime(Lista* l){
    Lista* p;
    p=l;
    while(p!=NULL){
        cout << "token: " << p->lexem << endl;
        cout << "cod: " << p->cod << endl;
        p=p->prox;
    }
}

int lst_vazia(Lista* l){
    return(l==NULL);
}

Lista* lst_pop(Lista* l, char lexem[], int cod){
    Lista* ant;
    ant = NULL;
    Lista* p;
    p=l;
    while(p!=NULL && strcmp(p->lexem,lexem)==0 && p->cod!=cod){
        ant = p;
        p=p->prox;
    }

    if(p==NULL){
        cout << "nao achou" << endl;
        return l;
    }

    if(ant==NULL){
        l=l->prox;
    }
    else{
        ant->prox = p->prox;
    }
    free(p);
    return l;
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


class Lexical_analyzer{
public:
    int left, right, len;

    Lista* setParse(char *iParse, int len, Lista* l){
        l=lst_cria();
        Lista* l2;
        l2=lst_cria();
        char parse[len];
        strcpy(parse,iParse);
        l = separateAndAnalyze(parse, l);
        l2=lst_cpy_inver(l2,l);
        lst_libera(l);
        return l2;
    }

    Lista* separateAndAnalyze(char *parse, Lista* l){
        char *token = strtok(parse,";");

        while(token != NULL){
            left=0, right=0, len = strlen(token);
             while (right <= len && left <= right) {
                if (isDelimiter(token[right]) == false)
                    right++;

                if (isDelimiter(token[right]) == true && left == right) {
                    if (isOperator(token[right]) == true){
                        //cout << token[right] << " IS AN OPERATOR" << endl;
                        char tokenCH[2];tokenCH[0]=token[right];tokenCH[1]='\0';
                        l = lst_insere(l, tokenCH, 1);
                    }
                    right++;
                    left = right;
                }
                else if (isDelimiter(token[right]) == true && left != right || (right == len && left != right)) {
                    char* subStr = subString(token, left, right - 1);
                    if (isKeyword(subStr) == true){
                        //cout << subStr<< " IS A KEYWORD" << endl;
                        l = lst_insere(l, subStr, 2);
                    }
                    else if (isInteger(subStr) == true){
                        //cout << subStr << " IS AN INTEGER" << endl;
                        l = lst_insere(l, subStr, 3);
                    }
                    else if (isFloat(subStr) == true){
                        //cout << subStr << " IS A float NUMBER" << endl;
                        l = lst_insere(l, subStr, 4);
                    }
                    else if (validIdentifier(subStr) == true && isDelimiter(token[right - 1]) == false){
                        //cout << subStr << " IS A VALID IDENTIFIER" << endl;
                        l = lst_insere(l, subStr, 5);
                    }
                    else if (validIdentifier(subStr) == false && isDelimiter(token[right - 1]) == false){
                        //cout << subStr << " IS NOT A VALID IDENTIFIER" << endl;
                        l = lst_insere(l, subStr, 6);
                    }
                    left = right;
                }
            }
            token = strtok(NULL,";");
        }
        return l;
    }

    // Returns 'true' if the character is a DELIMITER.
    bool isDelimiter(char ch){
        if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
            ch == '\n' || ch == '\0')
            return (true);
        return (false);
    }

    // Returns 'true' if the character is an OPERATOR.
    bool isOperator(char ch){
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=')
            return (true);
        return (false);
    }

    // Returns 'true' if the string is a VALID IDENTIFIER.
    bool validIdentifier(char* str){
        if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
            str[0] == '3' || str[0] == '4' || str[0] == '5' ||
            str[0] == '6' || str[0] == '7' || str[0] == '8' ||
            str[0] == '9' || isDelimiter(str[0]) == true)
            return (false);
        return (true);
    }

    // Returns 'true' if the string is a KEYWORD.
    bool isKeyword(char* token) {
        if (!strcmp(token, "if") || !strcmp(token, "else") ||
            !strcmp(token, "while") || !strcmp(token, "do") ||
            !strcmp(token, "break") || !strcmp(token, "continue") ||
            !strcmp(token, "int") || !strcmp(token, "float") ||
            !strcmp(token, "return") || !strcmp(token, "char") ||
            !strcmp(token, "case") || !strcmp(token, "sizeof") ||
            !strcmp(token, "typedef") || !strcmp(token, "switch") ||
            !strcmp(token, "unsigned") || !strcmp(token, "void") ||
            !strcmp(token, "static") || !strcmp(token, "struct"))
            return (true);
        return (false);
    }

    // Returns 'true' if the string is a float.
    bool isFloat(char* str) {
        int i, len = strlen(str);
        bool hasDecimal = false;

        if (len == 0)
            return (false);
        for (i = 0; i < len; i++) {
            if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' && str[i] != '.' ||
                (str[i] == '-' && i > 0))
                return (false);
            if (str[i] == '.')
                hasDecimal = true;
        }
        return (hasDecimal);
    }

    // Returns 'true' if the string is an INTEGER.
    bool isInteger(char* str) {
        int i, len = strlen(str);

        if (len == 0)
            return (false);
        for (i = 0; i < len; i++) {
            if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' || (str[i] == '-' && i > 0))
                return (false);
        }
        return (true);
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


};


int main(){
    Lexical_analyzer test;
    Lista* l;

    l=test.setParse("int a =b + 1c - 9.00;\nint c = 5 + 2y;",100,l);

    lst_imprime(l);
    lst_libera(l);

    return 0;
}
