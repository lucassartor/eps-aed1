/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   2020 04 - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   Lucas Sartor Chauvin                    11796718              **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f){
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f){
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual) {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id){
  PONT atual = f->inicioGeral;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual){
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}


bool inserirPessoaNaFila(PFILA f, int id, int ehPreferencial){
  bool resposta = false;
  
  if(id < 0 || buscarID(f, id) != NULL)
    return resposta;

  PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
  novoElemento->id = id;
  novoElemento->ehPreferencial = ehPreferencial;
  novoElemento->prox = NULL;

  //Caso a fila nao esteja vazia
  if(f->fimGeral != NULL){
    f->fimGeral->prox = novoElemento;
    f->fimGeral = novoElemento;
  }
  //Caso a fila esteja vazia
  else{
    f->fimGeral = novoElemento;  
    f->inicioGeral = novoElemento;
  }
  
  if(ehPreferencial){
    PONT novoElementoPref = (PONT) malloc(sizeof(ELEMENTO));
    novoElementoPref->id = id;
    novoElementoPref->ehPreferencial = ehPreferencial;
    novoElementoPref->prox = NULL;

    //Caso a fila preferencial nao esteja vazia
    if(f->fimPref != NULL){
      f->fimPref->prox = novoElementoPref;
      f->fimPref = novoElementoPref;
    }
    //Caso a fila preferencial esteja vazia
    else{
      f->fimPref = novoElementoPref;  
      f->inicioPref = novoElementoPref;
    }
  }

  resposta = true;

  return resposta;
}



bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id){
  bool resposta = false;

  if(f->fimGeral == NULL)
    return resposta;

  PONT elementoAtendido = NULL;
  if(f->fimPref != NULL){

    elementoAtendido = f->inicioPref; 
    int idAtendido = elementoAtendido->id; 
    *id = idAtendido; //TA DANDO MERDA

    //Remover da Fila Preferencial
    f->inicioPref = elementoAtendido->prox;
    if(f->fimPref->id == elementoAtendido->id){
      f->fimPref = NULL;
    }

    //Remover da Fila Geral
    PONT atual = f->inicioGeral;
    bool teste = false;

    
    while(teste == false){
      if(atual->id == elementoAtendido->id){
        f->inicioGeral = atual->prox;
        teste = true;
      }
      else if (atual->prox->id == elementoAtendido->id){
        atual->prox = atual->prox->prox;
        teste = true;   
      }
      atual = atual->prox;
    }
    if(f->fimGeral->id == elementoAtendido->id){
      f->fimGeral = NULL;
    }
    free(elementoAtendido);
  }
  else{
    elementoAtendido = f->inicioGeral;
    int idAtendido = elementoAtendido->id; 
    *id = idAtendido;

    //Remover da Fila Geral
    f->inicioGeral = elementoAtendido->prox;
    if(f->fimGeral->id == elementoAtendido->id){
      f->fimGeral = NULL;
    }
  }

  resposta = true;
  return resposta;
}

bool atenderPrimeiraDaFilaGeral(PFILA f, int* id){
  bool resposta = false;

  if(f->fimGeral == NULL)
    return resposta;

  PONT elementoAtendido = NULL;
  if(f->inicioGeral->ehPreferencial){
    elementoAtendido = f->inicioPref;

    //Remover da Fila Preferencial
    f->inicioPref = elementoAtendido->prox;
    if(f->fimPref->id == elementoAtendido->id){
      f->fimPref = NULL;
    }
  }
  elementoAtendido = f->inicioGeral;
  int idAtendido = elementoAtendido->id; 
  *id = idAtendido;
  
  //Remover da Fila Geral
  f->inicioGeral = elementoAtendido->prox;
  if(f->fimGeral->id == elementoAtendido->id){
    f->fimGeral = NULL;
  }

  resposta = true;
  return resposta;
}



bool desistirDaFila(PFILA f, int id){
  bool resposta = false;

  PONT elementoExcluido = buscarID(f, id);

  if(elementoExcluido == NULL)
    return resposta;

  PONT atual;
  bool teste;

  if(elementoExcluido->ehPreferencial == true){
    //Remover da Fila Preferencial
    atual = f->inicioPref;
    teste = false;
    while(teste == false){
      if(atual->id == elementoExcluido->id){
        f->inicioPref = atual->prox;
        teste = true;
      }
      else if (atual->prox->id == elementoExcluido->id){
        atual->prox = atual->prox->prox;
        teste = true;   
      }
        atual = atual->prox;
    }

    if(f->fimPref->id == elementoExcluido->id)
      f->fimPref = NULL;
  }

  //Remover da Fila Geral
  atual = f->inicioGeral;
  teste = false;

  while(teste == false){
    if(atual->id == elementoExcluido->id){
      f->inicioGeral = atual->prox;
      teste = true;
    }
    else if (atual->prox->id == elementoExcluido->id){
      atual->prox = atual->prox->prox;
      teste = true;   
    }
    atual = atual->prox;
  }

  if(f->fimGeral->id == elementoExcluido->id)
    f->fimGeral = NULL;
  
  free(elementoExcluido);
  
  resposta = true;
  return resposta;
}

// DELETAR EM BAIXO DAQUI HEIN KRAI
int main(){
  /*PFILA f = criarFila();
	int id;
	bool res;

  	printf("################# INSERINDO #######################\n");

	
	res = inserirPessoaNaFila(f, -1, false);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	
	res = inserirPessoaNaFila(f, 1, false);
	if(res) printf("Insercao retornou true (1). [OK]\n");
	else printf("Insercao retornou false (1).\n");
	
	res = inserirPessoaNaFila(f, 2, true);
	if(res) printf("Insercao retornou true (2). [OK]\n");
	else printf("Insercao retornou false (2).\n");
	
	res = inserirPessoaNaFila(f, 3, false);
	if(res) printf("Insercao retornou true (3). [OK]\n");
	else printf("Insercao retornou false (3).\n");
	
	res = inserirPessoaNaFila(f, 4, true);
	if(res) printf("Insercao retornou true (4). [OK]\n");
	else printf("Insercao retornou false (4).\n");
	
	res = inserirPessoaNaFila(f, 5, true);
	if(res) printf("Insercao retornou true (5). [OK]\n");
	else printf("Insercao retornou false (5).\n");
	
	res = inserirPessoaNaFila(f, 6, false);
	if(res) printf("Insercao retornou true (6). [OK]\n");
	else printf("Insercao retornou false (6).\n");
	exibirLog(f);

  printf("################# ATENDENDO #######################\n");
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (7), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (7).\n");

	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (8), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (8).\n");

	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (9), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (9).\n");

	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (10), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (10).\n");

	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (11), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (11).\n");

	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (12), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (12).\n");

	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (13), id=%i.\n",id);
	else printf("Atendimento retornou false (13). [OK]\n");
	exibirLog(f);

  printf("################# INSERINDO PARTE 2 ###############\n");

	res = inserirPessoaNaFila(f, 7, false);
	if(res) printf("Insercao retornou true (14). [OK]\n");
	else printf("Insercao retornou false (14).\n");
	res = inserirPessoaNaFila(f, 8, true);
	if(res) printf("Insercao retornou true (15). [OK]\n");
	else printf("Insercao retornou false (15).\n");
	res = inserirPessoaNaFila(f, 9, false);
	if(res) printf("Insercao retornou true (16). [OK]\n");
	else printf("Insercao retornou false (16).\n");
	res = inserirPessoaNaFila(f, 10, true);
	if(res) printf("Insercao retornou true (17). [OK]\n");
	else printf("Insercao retornou false (17).\n");
	exibirLog(f);


	printf("################# SAINDO DA FILA ##################\n");

	res = desistirDaFila(f, 6);
	if(res) printf("Desistindo da fila retornou true (18).\n");
	else printf("Desistindo da fila retornou false (18). [OK]\n");
	res = desistirDaFila(f, 7);
	if(res) printf("Desistindo da fila retornou true (19). [OK]\n");
	else printf("Desistindo da fila retornou false (19).\n");
	res = desistirDaFila(f, 8);
	if(res) printf("Desistindo da fila retornou true (20). [OK]\n");
	else printf("Desistindo da fila retornou false (20).\n");
	res = desistirDaFila(f, 9);
	if(res) printf("Desistindo da fila retornou true (21). [OK]\n");
	else printf("Desistindo da fila retornou false (21).\n");
	res = desistirDaFila(f, 10);
	if(res) printf("Desistindo da fila retornou true (22). [OK]\n");
	else printf("Desistindo da fila retornou false (22).\n");
	exibirLog(f); */

  PFILA f = criarFila();
	int id;
	bool res;

	printf("################# INSERINDO #######################\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, -1, false);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 1, false);
	if(res) printf("Insercao retornou true (1). [OK]\n");
	else printf("Insercao retornou false (1).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 2, true);
	if(res) printf("Insercao retornou true (2). [OK]\n");
	else printf("Insercao retornou false (2).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 3, false);
	if(res) printf("Insercao retornou true (3). [OK]\n");
	else printf("Insercao retornou false (3).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 4, true);
	if(res) printf("Insercao retornou true (4). [OK]\n");
	else printf("Insercao retornou false (4).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 5, true);
	if(res) printf("Insercao retornou true (5). [OK]\n");
	else printf("Insercao retornou false (5).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 6, false);
	if(res) printf("Insercao retornou true (6). [OK]\n");
	else printf("Insercao retornou false (6).\n");
	exibirLog(f);


	printf("################# ATENDENDO #######################\n");
	exibirLog(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (7), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (7).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (8), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (8).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (9), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (9).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (10), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (10).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (11), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (11).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if(res) printf("Atendimento retornou true (12), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (12).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if(res) printf("Atendimento retornou true (13), id=%i.\n",id);
	else printf("Atendimento retornou false (13). [OK]\n");
	exibirLog(f);



	printf("################# INSERINDO PARTE 2 ###############\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, 7, false);
	if(res) printf("Insercao retornou true (14). [OK]\n");
	else printf("Insercao retornou false (14).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 8, true);
	if(res) printf("Insercao retornou true (15). [OK]\n");
	else printf("Insercao retornou false (15).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 9, false);
	if(res) printf("Insercao retornou true (16). [OK]\n");
	else printf("Insercao retornou false (16).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 10, true);
	if(res) printf("Insercao retornou true (17). [OK]\n");
	else printf("Insercao retornou false (17).\n");
	exibirLog(f);


	printf("################# SAINDO DA FILA ##################\n");

	exibirLog(f);
	res = desistirDaFila(f, 6);
	if(res) printf("Desistindo da fila retornou true (18).\n");
	else printf("Desistindo da fila retornou false (18). [OK]\n");
	exibirLog(f);
	res = desistirDaFila(f, 7);
	if(res) printf("Desistindo da fila retornou true (19). [OK]\n");
	else printf("Desistindo da fila retornou false (19).\n");
	exibirLog(f);
	res = desistirDaFila(f, 8);
	if(res) printf("Desistindo da fila retornou true (20). [OK]\n");
	else printf("Desistindo da fila retornou false (20).\n");
	exibirLog(f);
	res = desistirDaFila(f, 9);
	if(res) printf("Desistindo da fila retornou true (21). [OK]\n");
	else printf("Desistindo da fila retornou false (21).\n");
	exibirLog(f);
	res = desistirDaFila(f, 10);
	if(res) printf("Desistindo da fila retornou true (22). [OK]\n");
	else printf("Desistindo da fila retornou false (22).\n");
	exibirLog(f);

  
  return 0;
}