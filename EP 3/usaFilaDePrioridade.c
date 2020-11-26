#include "filaDePrioridade.c"

int main() {
  PFILA f = criarFila(10);
  exibirLog(f);
  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (1)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (2)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (3)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0)) printf("ok\n");
  else printf("nok (4)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (5)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 5, 10)) printf("ok\n");
  else printf("nok (6)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 0, 15)) printf("ok\n");
  else printf("nok (7)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (8)\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 3, 4)) printf("ok\n");
  else printf("nok (9) - esperado, pois a nova prioridade nao eh maior\n");
  exibirLog(f);
  if(aumentarPrioridade(f, 4, 4)) printf("ok\n");
  else printf("nok (10) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);
  
  PONT prioritario;
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (1)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (2)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (3)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (4)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (5)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (6)\n");
  exibirLog(f);
  prioritario = removerElemento(f);
  if (prioritario) printf("Prioritario: %i, %f\n", prioritario->id, prioritario->prioridade);
  else printf("Fila vazia (7)\n");
  exibirLog(f);

  if(inserirElemento(f, 1, 1)) printf("ok\n");
  else printf("nok (10)\n");
  exibirLog(f);
  if(inserirElemento(f, 3, 3)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);
  if(inserirElemento(f, 2, 2)) printf("ok\n");
  else printf("nok (12)\n");
  exibirLog(f);
  if(inserirElemento(f, 0, 0.5)) printf("ok\n");
  else printf("nok (13)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 5)) printf("ok\n");
  else printf("nok (14)\n");
  exibirLog(f);

  printf("\n\nReduzindo prioridade\n");


  if(reduzirPrioridade(f, 5, 0)) printf("ok\n");
  else printf("nok (15)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 0, 1)) printf("ok\n");
  else printf("nok (16) - esperado, nova prioridade eh maior\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 2)) printf("ok\n");
  else printf("nok (17)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 3, 1.5)) printf("ok\n");
  else printf("nok (18)\n");
  exibirLog(f);
  if(reduzirPrioridade(f, 4, 1)) printf("ok\n");
  else printf("nok (19) - esperado, elemento com id=4 nao existe\n");
  exibirLog(f);



  return 0;
}
