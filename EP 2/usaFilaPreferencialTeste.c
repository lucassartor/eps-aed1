#include "filapreferencial.c"

PFILA criarFilaGAB1234()
{
	PFILA res = (PFILA)malloc(sizeof(FILAPREFERENCIAL));
	res->inicioPref = NULL;
	res->fimPref = NULL;
	res->inicioGeral = NULL;
	res->fimGeral = NULL;
	return res;
}

int tamanhoGAB1234(PFILA f)
{
	PONT atual = f->inicioGeral;
	int tam = 0;
	while (atual)
	{
		atual = atual->prox;
		tam++;
	}
	return tam;
}

int tamanhoFilaPreferencialGAB1234(PFILA f)
{
	PONT atual = f->inicioPref;
	int tam = 0;
	while (atual)
	{
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarIDGAB1234(PFILA f, int id)
{
	PONT atual = f->inicioGeral;
	while (atual)
	{
		if (atual->id == id)
			return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLogGAB1234(PFILA f)
{
	int numElementos = tamanho(f);
	printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
	PONT atual = f->inicioGeral;
	while (atual)
	{
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n");
	numElementos = tamanhoFilaPreferencial(f);
	printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
	atual = f->inicioPref;
	while (atual)
	{
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n\n");
}

bool inserirPessoaNaFilaGAB1234(PFILA f, int id, bool ehPreferencial)
{
	if (id < 0)
		return false;
	if (buscarID(f, id))
		return false;
	PONT novo = (PONT)malloc(sizeof(ELEMENTO));
	novo->id = id;
	novo->ehPreferencial = ehPreferencial;
	novo->prox = NULL;
	if (!f->inicioGeral)
	{
		f->inicioGeral = novo;
		f->fimGeral = novo;
	}
	else
	{
		f->fimGeral->prox = novo;
		f->fimGeral = novo;
	}
	if (ehPreferencial)
	{
		PONT novo2 = (PONT)malloc(sizeof(ELEMENTO));
		novo2->id = id;
		novo2->ehPreferencial = ehPreferencial;
		novo2->prox = NULL;
		if (!f->inicioPref)
		{
			f->inicioPref = novo2;
			f->fimPref = novo2;
		}
		else
		{
			f->fimPref->prox = novo2;
			f->fimPref = novo2;
		}
	}
	return true;
}

bool atenderPrimeiraDaFilaPreferencialGAB1234(PFILA f, int *id)
{
	if (!f->inicioGeral)
		return false;
	if (!f->inicioPref)
	{
		*id = f->inicioGeral->id;
		PONT apagar = f->inicioGeral;
		if (!f->inicioGeral->prox)
		{
			f->fimGeral = NULL;
			f->inicioGeral = NULL;
		}
		else
		{
			f->inicioGeral = f->inicioGeral->prox;
		}
		free(apagar);
	}
	else
	{
		PONT apagar = f->inicioPref;
		*id = apagar->id;
		PONT ant = NULL;
		PONT atual = f->inicioGeral;
		while (atual->id != apagar->id)
		{
			ant = atual;
			atual = atual->prox;
		}
		if (ant)
		{
			ant->prox = atual->prox;
		}
		else
		{
			f->inicioGeral = atual->prox;
		}
		if (!atual->prox)
			f->fimGeral = ant;
		free(atual);

		if (!f->inicioPref->prox)
		{
			f->fimPref = NULL;
			f->inicioPref = NULL;
		}
		else
		{
			f->inicioPref = f->inicioPref->prox;
		}
		free(apagar);
	}
	return true;
}

bool atenderPrimeiraDaFilaGeralGAB1234(PFILA f, int *id)
{
	if (!f->inicioGeral)
		return false;
	*id = f->inicioGeral->id;
	PONT apagar = f->inicioGeral;
	if (!f->inicioGeral->prox)
	{
		f->fimGeral = NULL;
		f->inicioGeral = NULL;
	}
	else
	{
		f->inicioGeral = f->inicioGeral->prox;
	}
	if (apagar->ehPreferencial)
	{
		PONT apagar2 = f->inicioPref;
		if (!f->inicioPref->prox)
		{
			f->fimPref = NULL;
			f->inicioPref = NULL;
		}
		else
		{
			f->inicioPref = f->inicioPref->prox;
		}
		free(apagar2);
	}
	free(apagar);
	return true;
}

bool desistirDaFilaGAB1234(PFILA f, int id)
{
	PONT ant = NULL;
	PONT atual = f->inicioGeral;
	while (atual)
	{
		if (atual->id == id)
			break;
		ant = atual;
		atual = atual->prox;
	}
	if (!atual)
		return false;

	PONT apagar = atual;
	if (!ant)
	{
		f->inicioGeral = atual->prox;
	}
	else
		ant->prox = apagar->prox;
	if (apagar == f->fimGeral)
		f->fimGeral = ant;
	if (apagar->ehPreferencial)
	{
		ant = NULL;
		atual = f->inicioPref;
		while (atual->id != id)
		{
			ant = atual;
			atual = atual->prox;
		}
		if (ant)
			ant->prox = atual->prox;
		else
			f->inicioPref = atual->prox;
		if (!atual->prox)
			f->fimPref = ant;

		free(atual);
	}
	free(apagar);
	return true;
}

/* INSERCAO */

void teste1()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, -1, false);
	exibirLogGAB1234(f);
	if (res)
		printf("Insercao retornou true (0).\n");
	res = inserirPessoaNaFila(f, -5, true);
	exibirLogGAB1234(f);
	if (res)
		printf("Insercao retornou true (1).\n");
	res = inserirPessoaNaFila(f, -20, false);
	exibirLogGAB1234(f);
	if (res)
		printf("Insercao retornou true (2).\n");
	exibirLogGAB1234(f);
}

void teste2()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, 1, false);
	exibirLogGAB1234(f);
	if (!res)
		printf("Insercao retornou false (0).\n");
	res = inserirPessoaNaFila(f, 2, false);
	exibirLogGAB1234(f);
	if (!res)
		printf("Insercao retornou false (1).\n");
	res = inserirPessoaNaFila(f, 3, false);
	if (!res)
		printf("Insercao retornou false (2).\n");
	exibirLogGAB1234(f);
}

void teste3()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, 1, true);
	if (!res)
		printf("Insercao retornou false (0).\n");
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 2, true);
	if (!res)
		printf("Insercao retornou false (1).\n");
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 3, true);
	if (!res)
		printf("Insercao retornou false (2).\n");
	exibirLogGAB1234(f);
}

void teste4()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, 6, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 5, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 4, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 3, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 2, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 1, false);
	exibirLogGAB1234(f);
}

void teste5()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, 1, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 2, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 3, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 4, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 5, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 6, true);
	exibirLogGAB1234(f);
}

void teste6()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	res = inserirPessoaNaFila(f, 1, false);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 2, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 1, true);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFila(f, 1, false);
	exibirLogGAB1234(f);
}

/* ATENDIMENTO */

void teste7()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, false);
	res = inserirPessoaNaFilaGAB1234(f, 2, false);
	res = inserirPessoaNaFilaGAB1234(f, 3, false);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

void teste8()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, true);
	res = inserirPessoaNaFilaGAB1234(f, 2, true);
	res = inserirPessoaNaFilaGAB1234(f, 3, true);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

void teste9()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, true);
	res = inserirPessoaNaFilaGAB1234(f, 2, false);
	res = inserirPessoaNaFilaGAB1234(f, 3, true);
	res = inserirPessoaNaFilaGAB1234(f, 4, false);
	res = inserirPessoaNaFilaGAB1234(f, 5, true);
	res = inserirPessoaNaFilaGAB1234(f, 6, false);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

void teste10()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 6, false);
	res = inserirPessoaNaFilaGAB1234(f, 5, true);
	res = inserirPessoaNaFilaGAB1234(f, 4, false);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = inserirPessoaNaFilaGAB1234(f, 3, true);
	res = inserirPessoaNaFilaGAB1234(f, 2, false);
	res = inserirPessoaNaFilaGAB1234(f, 1, true);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

void teste11()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	else
		printf("Atendimento retornou false [OK]\n");
}

/* DESISTIR */
void teste12()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 6);
	if (res)
		printf("Desistindo da fila retornou true [NOK].\n");
	else
		printf("Desistindo da fila retornou false [OK]\n");
	exibirLogGAB1234(f);
}

void teste13()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, false);
	res = inserirPessoaNaFilaGAB1234(f, 2, false);
	res = inserirPessoaNaFilaGAB1234(f, 3, false);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 6);
	if (res)
		printf("Desistindo da fila retornou true [NOK].\n");
	else
		printf("Desistindo da fila retornou false [OK]\n");
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 2);
	if (res)
		printf("Desistindo da fila retornou true [NOK].\n");
	else
		printf("Desistindo da fila retornou false [OK]\n");
	exibirLogGAB1234(f);
}

void teste14()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, true);
	res = inserirPessoaNaFilaGAB1234(f, 2, true);
	res = inserirPessoaNaFilaGAB1234(f, 3, true);
	res = desistirDaFila(f, 1);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 3);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 2);
	exibirLogGAB1234(f);
}

void teste15()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFilaGAB1234(f, 1, true);
	res = inserirPessoaNaFilaGAB1234(f, 2, false);
	res = inserirPessoaNaFilaGAB1234(f, 3, true);
	res = inserirPessoaNaFilaGAB1234(f, 4, false);
	res = inserirPessoaNaFilaGAB1234(f, 5, true);
	res = inserirPessoaNaFilaGAB1234(f, 6, false);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 2);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 1);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 5);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 2);
	exibirLogGAB1234(f);
}

/* MISTOS */

void teste16()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFila(f, 1, true);
	res = inserirPessoaNaFila(f, 2, false);
	res = inserirPessoaNaFila(f, 3, true);
	res = inserirPessoaNaFila(f, 4, false);
	res = inserirPessoaNaFila(f, 5, true);
	res = inserirPessoaNaFila(f, 6, false);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 2);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 1);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 5);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaGeral(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

void teste17()
{
	PFILA f = criarFilaGAB1234();
	bool res;
	int id;
	res = inserirPessoaNaFila(f, 1, 61);
	res = inserirPessoaNaFila(f, 3, 63);
	res = inserirPessoaNaFila(f, 5, 65);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
	res = desistirDaFila(f, 5);
	exibirLogGAB1234(f);
	res = atenderPrimeiraDaFilaPreferencial(f, &id);
	if (res)
		printf("Atendimento retornou true, id=%i.\n", id);
	exibirLogGAB1234(f);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	char comando = argv[1][0];
	//printf("%i:'%c'\n", argc, comando);


	teste15();
	teste16();
	teste17(); 

	return 0;
}
