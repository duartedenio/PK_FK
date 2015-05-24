#include "buffend.h"

/* ---------------------------------------------------------------------------------------------- 
    Objetivo:   Função para exclusão de tabelas.
    Parametros: Nome da tabela (char).    
    Retorno:    INT
                SUCCESS, 
                ERRO_REMOVER_ARQUIVO_OBJECT, 
                ERRO_REMOVER_ARQUIVO_SCHEMA, 
                ERRO_LEITURA_DADOS.
   ---------------------------------------------------------------------------------------------*/

int excluirTabela(char *nomeTabela) {
    struct fs_objects objeto, objeto1;
    tp_table *esquema, *esquema1;
    int x,erro, i, j, k, l, qtTable;
    char str[20]; 
    char dat[5] = ".dat";

    strcpy (str, nomeTabela); 
    strcat (str, dat);              //Concatena e junta o nome com .dat

    abreTabela(nomeTabela, &objeto, &esquema);
    qtTable = quantidadeTabelas();

    char **tupla = malloc(sizeof(char)*qtTable);
    for(i=0; i<qtTable; i++) {
    	tupla[i] = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    }

    tp_table *tab2 = (tp_table *)malloc(sizeof(struct tp_table));
    tab2 = procuraAtributoFK(objeto);

    FILE *dicionario;

    if((dicionario = fopen("fs_object.dat","a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    k=0;
    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        fread(tupla[k], sizeof(char), TAMANHO_NOME_TABELA , dicionario);
        k++;

        fseek(dicionario, 28, 1);
    }

    fclose(dicionario);

    /*for(i=0; i<qtTable; i++) {
    	printf(">>>>>>>>>>>>>>>>>>>>>>>>%s\n", tupla[i]);
    }*/
    
    for(i = 0; i < objeto.qtdCampos; i++){
        if(tab2[i].chave == PK){
            for(j=0; j<qtTable; j++) {
            	if(strcmp(tupla[j], nomeTabela) != 0) {
            		//printf("%s\n", tupla[j]);
            		abreTabela(tupla[j], &objeto1, &esquema1);

            		tp_table *tab3 = (tp_table *)malloc(sizeof(struct tp_table));
				    tab3 = procuraAtributoFK(objeto1);

				    FILE *dicionario1;

				    if((dicionario1 = fopen("fs_object.dat","a+b")) == NULL)
				        return ERRO_ABRIR_ARQUIVO;

				    k=0;
				    while(fgetc (dicionario1) != EOF){
				        fseek(dicionario1, -1, 1);

				        fread(tupla[k], sizeof(char), TAMANHO_NOME_TABELA , dicionario1);
				        k++;

				        fseek(dicionario1, 28, 1);
				    }

				    fclose(dicionario1);

				    for(l=0; l<objeto1.qtdCampos; l++) {
				    	if(tab3[l].chave == FK) {
				    		if(strcmp(nomeTabela, tab3[l].tabelaApt) == 0) {
				    			printf("Exclusao nao permitida!\n");
				    			return ERRO_CHAVE_ESTRANGEIRA;
				    		}
				    	}
				    }

            	}
            }
            //printf("------------------%s\n", tab2[i].nome);
        }
    }

    tp_buffer *bufferpoll = initbuffer();

    if(bufferpoll == ERRO_DE_ALOCACAO){
        printf("Erro ao alocar memória para o buffer.\n");
        return ERRO_LEITURA_DADOS;
    }

    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, esquema, objeto);        
    
    if(procuraSchemaArquivo(objeto) != 0)
        return ERRO_REMOVER_ARQUIVO_SCHEMA;

    if(procuraObjectArquivo(nomeTabela) != 0)
       return ERRO_REMOVER_ARQUIVO_OBJECT;
        
    remove(str);
    
    return SUCCESS;
}
