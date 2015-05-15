#include "buffend.h"

int pot10(int n) {
    if(n == 0)
        return 1;
    return 10 * pot10(n-1);
}

double convertD(char u[]) {
    return get_inteiro(u)+get_decimal(u);
    //Soma inteiro com decimal.ss
}

double get_inteiro(char v[]) {
    double inteiro=0;
    int i,tamanho = strtam(v);
    char u[10];
    strcpy(u,v); //copia o vetor para uma vaiável auxiliar para preservar sua originalidade
    for(i=0;i<tamanho && u[i]!='.';i++); // posiciona o indice i encima do ponto
    u[i]=0; // separa a parte inteira da parte decimal, inserindo um null no lugar do ponto
    inteiro=convertI(u);
    return inteiro;
}

double get_decimal(char u[]) {
    double decimal=0;
    int i,tamanho = strtam(u);
    for(i=0;i<tamanho && u[i]!='.';i++); // posiciona o indice i encima do ponto
    decimal=convertI(u+i+1);///(pot10(tamanho-i-1));
    decimal=(double)convertI(u+i+1)/(double)(pot10(tamanho-i-1));
    return decimal;
}

int convertI(char u[]) {
    if(strtam(u) == 0)
        return 0;
    return (u[0]-48)*pot10(strtam(u)-1) + convertI(u+1);
}

int strtam(char n[]) {
    if(n[0]==0)
        return 0;
    return 1+strtam(n+1);
}
