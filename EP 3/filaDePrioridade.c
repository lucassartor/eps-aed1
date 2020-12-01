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

PFILA criarFila(int max)
{
  PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT *)malloc(sizeof(PONT) * max);
  res->heap = (PONT *)malloc(sizeof(PONT) * max);
  int i;
  for (i = 0; i < max; i++)
  {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

void exibirLog(PFILA f)
{
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f)
{
  /*
  int tam = 0;
  return tam; */
  // conferir se eh isso mesmo

  return f->elementosNoHeap;
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  bool res = false;

  int resposta;

  //Verifica se o elemento eh valido, caso nao for retorna false
  if (id < 0 || id >= f->maxElementos || consultarPrioridade(f, id, resposta))
    return res;

  //Elemento eh valido, entao eh alocado espaco na memoria e colocado no arranjo
  PONT novoElemento = (PONT)malloc(sizeof(ELEMENTO));
  novoElemento->id = id;
  novoElemento->prioridade = prioridade;
  f->arranjo[id] = novoElemento;

  int i;

  //Adiciona elemento no heap
  for (i = 0; i < f->maxElementos; i++)
  {
    //Caso o heap esteja vazio
    if (f->heap[i] == NULL)
    {
      novoElemento->posicao = 0;

      f->heap[i] = novoElemento;
      f->elementosNoHeap = f->elementosNoHeap + 1;
      i = f->maxElementos;
    }

    //Caso o elemento seja o primeiro de uma fila nao vazia
    else if (novoElemento->prioridade > f->heap[0]->prioridade)
    {
      int j = f->maxElementos - 1;
      while (j >= 0)
      {
        if (f->heap[j] != NULL)
        {
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
    else if (f->heap[i + 1] == NULL)
    {
      novoElemento->posicao = f->heap[i]->posicao + 1;

      f->heap[i + 1] = novoElemento;
      f->elementosNoHeap = f->elementosNoHeap + 1;
      i = f->maxElementos;
    }

    //Caso o elemento pertenca ao meio da fila
    else if (f->heap[i]->prioridade > novoElemento->prioridade && f->heap[i + 1]->prioridade < novoElemento->prioridade)
    {
      int j = f->maxElementos - 1;
      while (j > i)
      {
        if (f->heap[j] != NULL)
        {
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

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  int resposta;

  //Verifica se o elemento eh valido, caso nao for retorna false
  if (id < 0 || id >= f->maxElementos || !consultarPrioridade(f, id, resposta))
    return res;

  //Procura qual eh o elemento dentro do heap
  int i;
  int posicaoHeap;
  for (i = 0; i < f->maxElementos; i++)
  {
    if (f->heap[i]->id == id)
    {
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
  if (i > 0)
  {
    while (!aux)
    {
      //Caso nao seja o ultimo da fila
      if (f->heap[i + 1])
      {
        if (f->heap[i - 1]->prioridade > f->heap[i]->prioridade && f->heap[i + 1]->prioridade < f->heap[i]->prioridade)
          aux = true;
      }

      //Caso seja o ultimo da fila
      else
      {
        if (f->heap[i - 1]->prioridade > f->heap[i]->prioridade)
          aux = true;
      }

      if (!aux)
      {
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

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  return res;
}

PONT removerElemento(PFILA f)
{
  PONT res = NULL;

  /* COMPLETAR */

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
  bool res = false;

  //Verifica se o elemento eh valido, caso nao for retorna false
  if (id < 0 || id >= f->maxElementos)
    return res;

  //Verifica se existe um elemento na fila com esse id
  int i = 0;
  while (f->heap[i] != NULL)
  {
    if (f->heap[i]->id == id)
    {
      res = true;
      resposta = &f->heap[i]->prioridade;
    }
    i++;
  }

  return res;
}

int main()
{
  PFILA f = criarFila(10);
  exibirLog(f);
  if (inserirElemento(f, 1, 1))
    printf("ok\n");
  else
    printf("nok (1)\n");
  exibirLog(f);
  if (inserirElemento(f, 3, 3))
    printf("ok\n");
  else
    printf("nok (2)\n");
  exibirLog(f);
  if (inserirElemento(f, 2, 2))
    printf("ok\n");
  else
    printf("nok (3)\n");
  exibirLog(f);
  if (inserirElemento(f, 0, 0))
    printf("ok\n");
  else
    printf("nok (4)\n");
  exibirLog(f);
  if (inserirElemento(f, 5, 5))
    printf("ok\n");
  else
    printf("nok (5)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 5, 10))
    printf("ok\n");
  else
    printf("nok (6)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 0, 15))
    printf("ok\n");
  else
    printf("nok (7)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 3, 4))
    printf("ok\n");
  else
    printf("nok (8)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 3, 4))
    printf("ok\n");
  else
    printf("nok (9) - esperado, pois a nova prioridade nao eh maior\n");

  if (aumentarPrioridade(f, 4, 4))
    printf("ok\n");
  else
    printf("nok (10) - esperado, elemento com id=4 nao existe\n");

  if (aumentarPrioridade(f, 1, 12))
    printf("ok\n");
  else
    printf("nok (8)\n");
  exibirLog(f);

  return 0;
}
