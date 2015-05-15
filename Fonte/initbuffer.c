#include "buffend.h"

// INICIALIZACAO DO BUFFER
tp_buffer * initbuffer(){
    
    tp_buffer *bp = (tp_buffer*)malloc(sizeof(tp_buffer)*PAGES);
    int i;
    if(bp == NULL)
        return ERRO_DE_ALOCACAO;
    for (i = 0;i < PAGES; i++){
        bp->db=0;
        bp->pc=0;
        bp->nrec=0;
        bp++;
    }

    return bp;
}
