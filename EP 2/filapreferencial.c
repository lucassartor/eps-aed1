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