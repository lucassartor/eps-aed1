/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   2020 04 - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   Lucas Sartor Chauvin                    	  11796718          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max)
{
    PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT *)malloc(sizeof(PONT) * max);
    int i;
    for (i = 0; i < max; i++)
        res->arranjo[i] = NULL;
    PONT cabeca = (PONT)malloc(sizeof(ELEMENTO));
    res->fila = cabeca;
    cabeca->ant = cabeca;
    cabeca->prox = cabeca;
    cabeca->id = -1;
    cabeca->prioridade = 1000000;
    return res;
}

void exibirLog(PFILA f)
{
    printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
    PONT atual = f->fila;
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
    while (atual != f->fila)
    {
        printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
        atual = atual->prox;
    }
    printf("\nElementos validos: ");
    atual = atual->prox;
    while (atual != f->fila)
    {
        printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
        atual = atual->prox;
    }

    printf("\nValores do arrajo:\n\[ ");
    int x;
    for (x = 0; x < f->maxElementos; x++)
        printf("%p ", f->arranjo[x]);
    printf("]\n\n");
}

int tamanho(PFILA f)
{
    int tam = 0;
    int i;

    //Percorre todo o arranja vendo qual elemento eh valido.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            tam++;
        }
    }

    return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
    bool resposta = false;

    //Caso id seja maior que num maximo de elementos permitidos na fila, retorna false.
    if (id >= f->maxElementos || id < 0)
        return resposta;

    int i;
    //Caso a fila nao esteja vazia, verifica se o id ja existe no arranjo, caso ja exista retorna false.
    if (f->fila->ant != f->fila || f->fila->prox != f->fila)
    {
        for (i = 0; i < f->maxElementos; i++)
        {
            if (f->arranjo[i] != NULL)
            {
                if (id == f->arranjo[i]->id)
                    return resposta;
            }
        }
    }

    //Id eh valido, portanto eh criado o elemento e adicionado no arranjo.
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->id = id;
    novo->prioridade = prioridade;
    f->arranjo[id] = novo;

    //Adiciona o elemento no caso da fila estar vazia.
    if (f->fila->ant == f->fila || f->fila->prox == f->fila)
    {
        f->fila->prox = novo;
        f->fila->ant = novo;
        novo->prox = f->fila;
        novo->ant = f->fila;
    }

    //Adiciona o elemento no caso da fila nao estar vazia.
    else
    {
        PONT maior = NULL;
        PONT menor = NULL;
        //Verifica em qual posicao o novo elemento pertence.
        for (i = 0; i < f->maxElementos; i++)
        {
            if (f->arranjo[i] != NULL)
            {
                if (novo->prioridade > f->arranjo[i]->prioridade)
                {
                    if (menor)
                    {
                        if (f->arranjo[i]->prioridade > menor->prioridade)
                            menor = f->arranjo[i];
                    }
                    else
                    {
                        menor = f->arranjo[i];
                    }
                }

                else if (novo->prioridade < f->arranjo[i]->prioridade)
                {
                    if (maior)
                    {
                        if (f->arranjo[i]->prioridade < maior->prioridade)
                            maior = f->arranjo[i];
                    }
                    else
                    {
                        maior = f->arranjo[i];
                    }
                }
            }
        }

        //Caso o novo elemento tenha a maior prioridade (primeiro da fila).
        if (maior == NULL)
        {
            novo->prox = menor;
            novo->ant = f->fila;

            menor->ant = novo;

            f->fila->prox = novo;
        }

        //Caso o novo elemento tenha a menor prioridade (ultimo da fila).
        else if (menor == NULL)
        {
            novo->ant = maior;
            novo->prox = f->fila;

            maior->prox = novo;

            f->fila->ant = novo;
        }

        //Caso o novo elemento esteja no meio da fila.
        else
        {
            novo->prox = menor;
            novo->ant = maior;
            menor->ant = novo;
            maior->prox = novo;
        }
    }

    resposta = true;
    return resposta;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
    bool resposta = false;
    bool elementoExiste = false;
    int identificador;

    //Caso id invalido, retorna false.
    if (id >= f->maxElementos || id < 0)
        return resposta;

    int i;
    //Caso nao exista o elemento com esse id ou a prioridade do elemento ja eh maior ou igual a passada na funcao, retorna false.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (id == f->arranjo[i]->id)
            {
                if (f->arranjo[i]->prioridade >= novaPrioridade)
                    return false;

                elementoExiste = true;
                identificador = i;
            }
        }
    }

    if (!elementoExiste)
        return resposta;

    //Altera a prioridade do elemento e o realoca caso necessario
    f->arranjo[identificador]->prioridade = novaPrioridade;

    PONT maior = NULL;
    PONT menor = NULL;
    //Verifica em qual posicao o novo elemento pertence.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (f->arranjo[identificador]->prioridade > f->arranjo[i]->prioridade)
            {
                if (menor)
                {
                    if (f->arranjo[i]->prioridade > menor->prioridade)
                        menor = f->arranjo[i];
                }
                else
                {
                    menor = f->arranjo[i];
                }
            }

            else if (f->arranjo[identificador]->prioridade < f->arranjo[i]->prioridade)
            {
                if (maior)
                {
                    if (f->arranjo[i]->prioridade < maior->prioridade)
                        maior = f->arranjo[i];
                }
                else
                {
                    maior = f->arranjo[i];
                }
            }
        }
    }

    //Caso o novo elemento tenha a maior prioridade (primeiro da fila).
    if (maior == NULL)
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->prox = menor;
        f->arranjo[identificador]->ant = f->fila;

        menor->ant = f->arranjo[identificador];

        f->fila->prox = f->arranjo[identificador];
    }

    //Caso o novo elemento tenha a menor prioridade (ultimo da fila).
    else if (menor == NULL)
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->ant = maior;
        f->arranjo[identificador]->prox = f->fila;

        maior->prox = f->arranjo[identificador];

        f->fila->ant = f->arranjo[identificador];
    }

    //Caso o novo elemento esteja no meio da fila.
    else
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->prox = menor;
        f->arranjo[identificador]->ant = maior;

        menor->ant = f->arranjo[identificador];
        maior->prox = f->arranjo[identificador];
    }

    resposta = true;
    return resposta;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
    bool resposta = false;
    bool elementoExiste = false;
    int identificador;

    //Caso id invalido, retorna false.
    if (id >= f->maxElementos || id < 0)
        return resposta;

    int i;
    //Caso nao exista o elemento com esse id ou a prioridade do elemento ja eh maior ou igual a passada na funcao, retorna false.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (id == f->arranjo[i]->id)
            {
                if (f->arranjo[i]->prioridade <= novaPrioridade)
                    return false;

                elementoExiste = true;
                identificador = i;
            }
        }
    }

    if (!elementoExiste)
        return resposta;

    //Altera a prioridade do elemento e o realoca caso necessario
    f->arranjo[identificador]->prioridade = novaPrioridade;

    PONT maior = NULL;
    PONT menor = NULL;
    //Verifica em qual posicao o novo elemento pertence.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (f->arranjo[identificador]->prioridade > f->arranjo[i]->prioridade)
            {
                if (menor)
                {
                    if (f->arranjo[i]->prioridade > menor->prioridade)
                        menor = f->arranjo[i];
                }
                else
                {
                    menor = f->arranjo[i];
                }
            }

            else if (f->arranjo[identificador]->prioridade < f->arranjo[i]->prioridade)
            {
                if (maior)
                {
                    if (f->arranjo[i]->prioridade < maior->prioridade)
                        maior = f->arranjo[i];
                }
                else
                {
                    maior = f->arranjo[i];
                }
            }
        }
    }

    //Caso o novo elemento tenha a maior prioridade (primeiro da fila).
    if (maior == NULL)
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->prox = menor;
        f->arranjo[identificador]->ant = f->fila;

        menor->ant = f->arranjo[identificador];

        f->fila->prox = f->arranjo[identificador];
    }

    //Caso o novo elemento tenha a menor prioridade (ultimo da fila).
    else if (menor == NULL)
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->ant = maior;
        f->arranjo[identificador]->prox = f->fila;

        maior->prox = f->arranjo[identificador];

        f->fila->ant = f->arranjo[identificador];
    }

    //Caso o novo elemento esteja no meio da fila.
    else
    {
        f->arranjo[identificador]->ant->prox = f->arranjo[identificador]->prox;
        f->arranjo[identificador]->prox->ant = f->arranjo[identificador]->ant;

        f->arranjo[identificador]->prox = menor;
        f->arranjo[identificador]->ant = maior;

        menor->ant = f->arranjo[identificador];
        maior->prox = f->arranjo[identificador];
    }

    resposta = true;
    return resposta;
}

PONT removerElemento(PFILA f)
{
    PONT resposta = NULL;

    //Fila vazia (somente no cabeca), retorna NULL.
    if (f->fila->ant == f->fila || f->fila->prox == f->fila)
    {
        return resposta;
    }

    //Caso nao seja vazia, remove o primeiro elemento da fila (maior elemento).

    //Faz uma copia do elemento que sera removido.
    resposta = (PONT)malloc(sizeof(ELEMENTO));
    resposta->id = f->fila->prox->id;
    resposta->prioridade = f->fila->prox->prioridade;

    //Acerta os ponteiros da fila.
    f->fila->prox = f->fila->prox->prox;
    f->fila->prox->ant = f->fila; 

    int i;
    //Anula o seu valor no arranjo.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (f->arranjo[i]->id == resposta->id)
            {
                f->arranjo[i] = NULL;   
            }
        }
    }

    return resposta;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
    bool resp = false;
    bool elementoExiste = false;

    //Caso id invalido, retorna false.
    if (id >= f->maxElementos || id < 0)
        return resp;

    int i;
    //Caso nao exista o elemento com esse id ou a prioridade do elemento ja eh maior ou igual a passada na funcao, retorna false.
    for (i = 0; i < f->maxElementos; i++)
    {
        if (f->arranjo[i] != NULL)
        {
            if (id == f->arranjo[i]->id)
            {
                resposta = &f->arranjo[i]->prioridade;
                elementoExiste = true;
            }
        }
    }

    if (!elementoExiste)
        return resp;

    resp = true;
    return resp;
}
