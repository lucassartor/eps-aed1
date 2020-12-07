/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   2020 04 - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Lucas Sartor Chauvin                   11796718               **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max) {
    PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT *) malloc(sizeof(PONT) * max);
    res->heap = (PONT *) malloc(sizeof(PONT) * max);
    int i;
    for (i = 0; i < max; i++) {
        res->arranjo[i] = NULL;
        res->heap[i] = NULL;
    }
    res->elementosNoHeap = 0;
    return res;
}

void exibirLog(PFILA f) {
    printf("Log [elementos: %i]\n", f->elementosNoHeap);
    PONT atual;
    int i;
    for (i = 0; i < f->elementosNoHeap; i++) {
        atual = f->heap[i];
        printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
    }
    printf("\n\n");
}

int tamanho(PFILA f) {
    int tam = 0;

    //Percorre o heap ate que seja nulo
    while (f->heap[tam] != NULL) {
        tam++;
    }

    return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade) {
    bool res = false;

    float resposta;

    //Verifica se o elemento eh valido, caso nao for retorna false
    if (id < 0 || id >= f->maxElementos || consultarPrioridade(f, id, &resposta))
        return res;

    //Elemento eh valido, entao eh alocado espaco na memoria e colocado no arranjo
    PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
    novoElemento->id = id;
    novoElemento->prioridade = prioridade;
    f->arranjo[id] = novoElemento;

    int i;

    //Adiciona elemento no heap
    for (i = 0; i < f->maxElementos; i++) {
        //Caso o heap esteja vazio
        if (f->heap[i] == NULL) {
            novoElemento->posicao = 0;

            f->heap[i] = novoElemento;
            f->elementosNoHeap = f->elementosNoHeap + 1;
            i = f->maxElementos;
        }

            //Caso o elemento seja o primeiro de uma fila nao vazia
        else if (novoElemento->prioridade > f->heap[0]->prioridade) {
            int j = f->maxElementos - 1;
            while (j >= 0) {
                if (f->heap[j] != NULL) {
                    f->heap[j + 1] = f->heap[j];
                    f->heap[j + 1]->posicao++;
                }
                j--;
            }

            novoElemento->posicao = 0;
            f->heap[0] = novoElemento;

            f->elementosNoHeap = f->elementosNoHeap + 1;
            i = f->maxElementos;
        }

            //Caso o elemento pertenca ao final da fila
        else if (f->heap[i + 1] == NULL) {
            novoElemento->posicao = f->heap[i]->posicao + 1;

            f->heap[i + 1] = novoElemento;
            f->elementosNoHeap = f->elementosNoHeap + 1;
            i = f->maxElementos;
        }

            //Caso o elemento pertenca ao meio da fila
        else if (f->heap[i]->prioridade > novoElemento->prioridade &&
                 f->heap[i + 1]->prioridade < novoElemento->prioridade) {
            int j = f->maxElementos - 1;
            while (j > i) {
                if (f->heap[j] != NULL) {
                    f->heap[j + 1] = f->heap[j];
                    f->heap[j + 1]->posicao++;
                }
                j--;
            }

            novoElemento->posicao = f->heap[i]->posicao + 1;
            f->heap[i + 1] = novoElemento;

            f->elementosNoHeap = f->elementosNoHeap + 1;
            i = f->maxElementos;
        }
    }

    res = true;
    return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade) {
    bool res = false;

    float resposta;

    //Verifica se o elemento eh valido, caso nao for retorna false
    if (id < 0 || id >= f->maxElementos || !consultarPrioridade(f, id, &resposta))
        return res;

    //Procura qual eh o elemento dentro do heap
    int i;
    int posicaoHeap;
    for (i = 0; i < f->maxElementos; i++) {
        if (f->heap[i]->id == id) {
            //Verifica se elemento ja possui prioridade maior ou igual a nova prioridade, se sim retorna falso
            if (f->heap[i]->prioridade >= novaPrioridade)
                return res;

            posicaoHeap = i;
            i = f->maxElementos;
        }
    }

    //Muda a prioridade
    f->heap[posicaoHeap]->prioridade = novaPrioridade;

    //Cria elemento aux
    PONT pontElemento;
    pontElemento = f->heap[posicaoHeap];

    //Realoca as posicoes
    i = posicaoHeap;
    bool aux = false;

    //Verifica se ja n eh o primeiro da fila
    if (i > 0) {
        while (!aux) {
            //Caso nao seja o ultimo da fila
            if (f->heap[i + 1]) {
                if (f->heap[i - 1]->prioridade >= f->heap[i]->prioridade &&
                    f->heap[i + 1]->prioridade <= f->heap[i]->prioridade)
                    aux = true;
            }

                //Caso seja o ultimo da fila
            else {
                if (f->heap[i - 1]->prioridade > f->heap[i]->prioridade)
                    aux = true;
            }

            if (!aux) {
                f->heap[i] = f->heap[i - 1];
                f->heap[i - 1] = pontElemento;

                f->heap[i]->posicao++;
                f->heap[i - 1]->posicao--;
            }

            i--;
            if (i == 0)
                aux = true;
        }
    }

    res = true;
    return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade) {
    bool res = false;

    float resposta;

    //Verifica se o elemento eh valido, caso nao for retorna false
    if (id < 0 || id >= f->maxElementos || !consultarPrioridade(f, id, &resposta)) //mudar essa bagaça
        return res;

    //Procura qual eh o elemento dentro do heap
    int i;
    int posicaoHeap;
    for (i = 0; i < f->maxElementos; i++) {
        if (f->heap[i]->id == id) {
            //Verifica se elemento ja possui prioridade menor ou igual a nova prioridade, se sim retorna falso
            if (f->heap[i]->prioridade <= novaPrioridade)
                return res;

            posicaoHeap = i;
            i = f->maxElementos;
        }
    }

    //Muda a prioridade
    f->heap[posicaoHeap]->prioridade = novaPrioridade;

    //Cria elemento aux
    PONT pontElemento;
    pontElemento = f->heap[posicaoHeap];

    //Realoca as posicoes
    i = posicaoHeap;
    bool aux = false;

    //Verifica se ja n eh o ultimo da fila
    if (i < f->maxElementos - 1) {
        while (!aux) {
            //Caso nao seja o primeiro da fila
            if (f->heap[i]->posicao > 0) {
                if (f->heap[i - 1]->prioridade >= f->heap[i]->prioridade &&
                    f->heap[i + 1]->prioridade <= f->heap[i]->prioridade)
                    aux = true;
            }

                //Caso seja o primeiro da fila
            else {
                if (f->heap[i + 1]->prioridade < f->heap[i]->prioridade)
                    aux = true;
            }

            if (!aux) {
                f->heap[i] = f->heap[i + 1];
                f->heap[i + 1] = pontElemento;

                f->heap[i]->posicao--;
                f->heap[i + 1]->posicao++;
            }

            i++;
            if (i == f->elementosNoHeap - 1)
                aux = true;
        }
    }

    res = true;
    return res;
}

//Função auxiliar para exclusao
void refazHeapMaximo(PFILA f, PONT atual) {

    if (atual == NULL)
        return;

    int esq = (2 * atual->posicao) + 1;
    int dir = (2 * atual->posicao) + 2;

    //Verifica se os filhos da esq e dir sao validos, retorna caso nao forem
    if (dir >= f->elementosNoHeap)
        return;
    if (esq >= f->elementosNoHeap)
        return;

    int maior = esq;

    if (dir >= 2) {
        if (f->heap[esq]->prioridade < f->heap[dir]->prioridade) {
            maior = dir;
        }
    }

    if (atual->prioridade < f->heap[maior]->prioridade) {
        PONT noAux = f->heap[maior];
        int posicaoAux = atual->posicao;

        f->heap[maior] = atual;
        atual->posicao = maior;

        f->heap[posicaoAux] = noAux;
        noAux->posicao = posicaoAux;

        //Recursao
        refazHeapMaximo(f, atual);
    }
}

PONT removerElemento(PFILA f) {

    //Inicializa o resultado
    PONT res = NULL;

    //Verifica se o heap esta vazio
    if (f->elementosNoHeap == 0)
        return res;

    //Guarda o elemento que sera removido e o troca de posicao
    res = f->heap[0];
    f->heap[0] = f->heap[f->elementosNoHeap - 1];
    f->heap[0]->posicao = 0;

    //Arruma os ponteiros
    f->heap[f->elementosNoHeap - 1] = NULL;
    (f->elementosNoHeap)--;
    f->arranjo[res->id] = NULL;

    //Arruma as posicoes do heap
    refazHeapMaximo(f, f->heap[0]);

    return res;
}


bool consultarPrioridade(PFILA f, int id, float *resposta) {
    bool res = false;

    //Verifica se o elemento eh valido, caso nao for retorna false
    if (id < 0 || id >= f->maxElementos)
        return res;

    //Verifica se existe um elemento na fila com esse id
    PONT elemento = f->arranjo[id];
    if (elemento == NULL)
        return res;


    *resposta = elemento->prioridade;

    res = true;

    return res;
}