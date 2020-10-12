#include "filaDePrioridade.c"

int main()
{
  PFILA f = criarFila(10);
  exibirLog(f);
  if (inserirElemento(f, 1, 1))
    printf("(1) Funcao retornou true\n");
  else
    printf("Funcao retornou false (1)\n");
  exibirLog(f);
  if (inserirElemento(f, 3, 3))
    printf("(2) Funcao retornou true\n");
  else
    printf("Funcao retornou false (2)\n");
  exibirLog(f);
  if (inserirElemento(f, 2, 2))
    printf("(3) Funcao retornou true\n");
  else
    printf("Funcao retornou false (3)\n");
  exibirLog(f);
  if (inserirElemento(f, 0, 0))
    printf("(4) Funcao retornou true\n");
  else
    printf("Funcao retornou false (4)\n");
  exibirLog(f);
  if (inserirElemento(f, 5, 5))
    printf("(5) Funcao retornou true\n");
  else
    printf("Funcao retornou false (5)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 5, 10))
    printf("(6) Funcao retornou true\n");
  else
    printf("Funcao retornou false (6)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 0, 15))
    printf("(7) Funcao retornou true\n");
  else
    printf("Funcao retornou false (7)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 3, 4))
    printf("(8) Funcao retornou true\n");
  else
    printf("Funcao retornou false (8)\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 3, 4))
    printf("(9) Funcao retornou true\n");
  else
    printf("Funcao retornou false (9) - esperado, pois a nova prioridade nao eh maior\n");
  exibirLog(f);
  if (aumentarPrioridade(f, 4, 4))
    printf("(10) Funcao retornou true\n");
  else
    printf("Funcao retornou false (10) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);

  /*PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (1)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (2)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (3)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (4)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (5)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (6)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario)
    printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else
    printf("Fila vazia (7)\n");
  exibirLog(f); */

  if (inserirElemento(f, 1, 1))
    printf("(11) Funcao retornou true\n");
  else
    printf("Funcao retornou false (11)\n");
  exibirLog(f);
  if (inserirElemento(f, 3, 3))
    printf("(12) Funcao retornou true\n");
  else
    printf("Funcao retornou false (12)\n");
  exibirLog(f);
  if (inserirElemento(f, 2, 2))
    printf("(13) Funcao retornou true\n");
  else
    printf("Funcao retornou false (13)\n");
  exibirLog(f);
  if (inserirElemento(f, 0, 0.5))
    printf("(14) Funcao retornou true\n");
  else
    printf("Funcao retornou false (14)\n");
  exibirLog(f);
  if (inserirElemento(f, 5, 5))
    printf("(15) Funcao retornou true\n");
  else
    printf("Funcao retornou false (15)\n");
  exibirLog(f);

  printf("\n\nReduzindo prioridade\n");

  if (reduzirPrioridade(f, 5, 0))
    printf("(16) Funcao retornou true\n");
  else
    printf("Funcao retornou false (16)\n");
  exibirLog(f);
  if (reduzirPrioridade(f, 0, 1))
    printf("(17) Funcao retornou true\n");
  else
    printf("Funcao retornou false (17) - esperado, nova prioridade eh maior\n");
  exibirLog(f);
  if (reduzirPrioridade(f, 3, 2))
    printf("(18) Funcao retornou true\n");
  else
    printf("Funcao retornou false (18)\n");
  exibirLog(f);
  if (reduzirPrioridade(f, 3, 2))
    printf("(19) Funcao retornou true\n");
  else
    printf("Funcao retornou false (19) - esperado, nova prioridade eh igual\n");
  exibirLog(f);
  if (reduzirPrioridade(f, 4, 1))
    printf("(20) Funcao retornou true\n");
  else
    printf("Funcao retornou false (20) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);

  return 0;
}