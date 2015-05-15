#include "buffend.h"

// INSERE NA TABELA
column *insereValor(column *c, char *nomeCampo, char *valorCampo){
    
    int tamNome, tamValor, i;
    tamNome = strlen(nomeCampo);
    tamValor = strlen(valorCampo);
    column *aux;

    if(c == NULL){ // Se o valor a ser inserido é o primeiro, adiciona primeiro campo.
    
        column *e = (column *)malloc(sizeof(column)*1);

        if(e == NULL) {
            printf("Memoria insuficiente!!\nAbortando...");
            exit(1);
        }

        e->valorCampo = (char *)malloc((sizeof(valorCampo)));

        if(e->valorCampo == NULL) {
            printf("Memoria insuficiente!!\nAbortando...");
            exit(1);
        }
    
    //-----------------------------------Codigo de macho-------------------------------------------
        for(i=0; i < tamNome && i < (TAMANHO_NOME_CAMPO-1); i++) e->nomeCampo[i] = nomeCampo[i];        
        e->nomeCampo[i] = '\0';

        for(i=0; i < tamValor; i++) e->valorCampo[i] = valorCampo[i];        
        e->valorCampo[i] = '\0';

    //---------------------------------------------------------------------------------------------

    //----------------------Viadagem-----------------
        //strcpy(e->nomeCampo, nomeCampo); 
        //strcpy(e->valorCampo, valorCampo);
    //-----------------------------------------------
        e->next = NULL;
        c = e;
        return c;
    } else {
        for(aux = c; aux != NULL; aux = aux->next) { // Anda até o final da lista de valores a serem inseridos e adiciona um novo valor.
            if(aux->next == NULL){
                column *e = (column *)malloc(sizeof(column)*1);

                if(e == NULL) {
                    printf("Memoria insuficiente!!\nAbortando...");
                    exit(1);
                }

                e->valorCampo = (char *)malloc(sizeof(char) * (sizeof(valorCampo)));

                if(e->valorCampo == NULL) {
                    printf("Memoria insuficiente!!\nAbortando...");
                    exit(1);
                }

                e->next = NULL;
            
            //----------------------------mais codigo de macho-------------------------------------------
                for(i=0; i < tamNome && i < (TAMANHO_NOME_CAMPO-1); i++) e->nomeCampo[i] = nomeCampo[i];
                e->nomeCampo[i] = '\0';

                for(i=0; i < tamValor; i++) e->valorCampo[i] = valorCampo[i];
                e->valorCampo[i] = '\0';
            //-------------------------------------------------------------------------------------------

            //------------------------coisa de viado-----------------
                //strcpy(e->nomeCampo, nomeCampo);
                //strcpy(e->valorCampo, valorCampo);
            //-------------------------------------------------------
                aux->next = e;
                return c;
            }
        }
    }

    return ERRO_INSERIR_VALOR;
}
