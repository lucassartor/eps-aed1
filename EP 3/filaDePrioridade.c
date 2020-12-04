/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <nome do(a) aluno(a)>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

enum lado {esquerdo, direito};

PFILA criarFila(int max){
    PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
    res->heap = (PONT*) malloc(sizeof(PONT)*max);
    int i;
    for (i=0;i<max;i++) {
        res->arranjo[i] = NULL;
        res->heap[i] = NULL;
    }
    res->elementosNoHeap = 0;
    return res;
}



void exibirLog(PFILA f){
    printf("Log [elementos: %i]\n", f->elementosNoHeap);
    PONT atual;
    int i;
    for (i=0;i<f->elementosNoHeap;i++){
        atual = f->heap[i];
        printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
    }
    printf("\n\n");
}

int tamanho(PFILA f){
    int tam = 0, i = 0;

    while (f->heap[i] != NULL) {
        tam++;
        i++;
    }

    return tam;
}

// Usado apenas na inserção e no aumento de prioridade
void maxHeapfyBottomUp(PFILA f, PONT elemento) {

    // Nó Raiz não possui pai
    if (elemento->posicao == 0) return;

    int indicePai = (elemento->posicao - 1) / 2;

    if (elemento->prioridade > f->heap[indicePai]->prioridade) {
        PONT tmpNo = f->heap[indicePai];
        int tmpPosicao = elemento->posicao;

        // Coloca o ex-filho no lugar do pai
        f->heap[indicePai] = elemento;
        elemento->posicao = indicePai;

        // Coloca o ex-pai no lugar do filho
        f->heap[tmpPosicao] = tmpNo;
        tmpNo->posicao = tmpPosicao;

        maxHeapfyBottomUp(f, elemento);
    }

    // Fim da função
}

void maxHeapfyTopDown(PFILA f, PONT elemento) {
    if (elemento == NULL) return;


    int indiceFilhoEsq = (2 * elemento->posicao) + 1;
    int indiceFilhoDir = (2 * elemento->posicao) + 2;

    // Testa se o índice dos filhos é válido
    if (indiceFilhoDir >= f->elementosNoHeap) indiceFilhoDir = -1;
    if (indiceFilhoEsq >= f->elementosNoHeap) indiceFilhoEsq = -1;

    if (indiceFilhoEsq == -1) return; // Elemento é uma folha, já que se ele não tem nem filho à esquerda, sequer terá à direita

    // Assumimos por ora que o filho à esquerda é o maior
    int indiceMaiorFilho = indiceFilhoEsq;

    if (indiceFilhoDir >= 2) { // Testamos se existe um filho à direita. O menor índice possível para um nó seja filho à direita de outro nó é pelo menos 2

        if (f->heap[indiceFilhoEsq]->prioridade < f->heap[indiceFilhoDir]->prioridade) {
            indiceMaiorFilho = indiceFilhoDir;
        }
    }



    if (elemento->prioridade < f->heap[indiceMaiorFilho]->prioridade) {
        PONT tmpNo = f->heap[indiceMaiorFilho];
        int tmpPosicao = elemento->posicao;

        // Coloca o ex-pai no lugar do filho
        f->heap[indiceMaiorFilho] = elemento;
        elemento->posicao = indiceMaiorFilho;

        // Coloca o ex-filho no lugar do pai
        f->heap[tmpPosicao] = tmpNo;
        tmpNo->posicao = tmpPosicao;

        maxHeapfyTopDown(f, elemento);
    }
}

bool inserirElemento(PFILA f, int id, float prioridade){
    bool res = false;

    // Condições de escape

    if (id < 0 || id >= f->maxElementos) return res;
    if (f->arranjo[id] != NULL) return res;

    // Aloca memória pro novo elemento
    PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));

    // Preenche os campos do novo elemento (a posição pode ser atualizada na função maxHeapfy)
    novoElemento->id = id;
    novoElemento->prioridade = prioridade;
    novoElemento->posicao = f->elementosNoHeap;

    // Atualiza informações da fila
    f->arranjo[id] = novoElemento;
    f->heap[f->elementosNoHeap] = novoElemento;
    (f->elementosNoHeap)++;

    // Correção das posições
    maxHeapfyBottomUp(f, novoElemento);


    // Fim
    res = true;

    return res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
    bool res = false;

    // Condições de invalidez
    if (id < 0 || id >= f->maxElementos) return res;
    PONT elemento = f->arranjo[id];
    if (elemento == NULL) return res;
    if (elemento->prioridade >= novaPrioridade) return res;

    // Troca de prioridade
    elemento->prioridade = novaPrioridade;

    // Correção das posições
    maxHeapfyBottomUp(f, elemento);

    // Fim
    res = true;

    return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
    bool res = false;
    // Condições de invalidez
    if (id < 0 || id >= f->maxElementos) return res;
    PONT elemento = f->arranjo[id];
    if (elemento == NULL) return res;
    if (elemento->prioridade <= novaPrioridade) return res;

    // Troca de prioridade
    elemento->prioridade = novaPrioridade;

    // Correção das posições
    maxHeapfyTopDown(f, elemento);

    // Fim
    res = true;

    return res;
}

PONT removerElemento(PFILA f){
    PONT res = NULL;

    if (f->elementosNoHeap == 0) return res;

    // Armazena o elemento a ser removido
    res = f->heap[0];

    // Coloca o último elemento no lugar do primeiro
    f->heap[0] = f->heap[f->elementosNoHeap - 1];
    f->heap[0]->posicao = 0;


    // Limpa a posição do último elemento e diminui a contagem de elementos
    f->heap[f->elementosNoHeap - 1] = NULL;
    (f->elementosNoHeap)--;

    // Limpa o registro do elemento removido do array de id's

    f->arranjo[res->id] = NULL;


    maxHeapfyTopDown(f, f->heap[0]);


    return res;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
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