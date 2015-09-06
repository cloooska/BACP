#include "Librerias/general.h"
#include "Librerias/sa.h"
#include "Librerias/greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

pSol SA(pSol inicial,malla m,pCurso cursos)
{
	limpiarGreedy(cursos);
	int MaxCrSol=maxCreditosSolucion(inicial);
	int T=MaxCrSol,t=1;
	srand(time(NULL));
	int cantPer = getCantPeriodos(m);
	pSol nueva=duplicarSol(inicial);
	pSol mejor=duplicarSol(inicial);
	pSol actual=duplicarSol(inicial);
	double deltaEval,prob;
	while(maxCreditosSolucion(mejor) >= mediaCreditos(cursos,m))
	{
		while(t%100!=0)
		{	
			prob = rand()%1000000;
			prob=prob/1000000;
			nueva=mover(nueva,cantPer,cursos);
			mostrar(nueva);
			deltaEval=maxCreditosSolucion(nueva) - maxCreditosSolucion(actual);
			if(deltaEval<=0)
			{
				printf("entre a mejor\n");
				mejor=duplicarSol(nueva);
				mostrar(mejor);
			}
			else
			{
				printf("entre a peor\n");
				if(exp(-deltaEval/T)>=prob)
				{
					actual=nueva;
				}
			}
			t++;
		}
		T++;
	}
	return mejor;
}

int getCantCreditos(pCurso cursos, int num_curso)
{
	pCurso aux=cursos;
	while(aux->num_curso!=num_curso)
		aux=aux->sig;
	return aux->cant_creditos;
}

pSol mover(pSol solucion,int cantPer,pCurso cursos)
{
	pSol periodo1=solucion,periodo2=solucion;
	pCur aMover,anterior,aux;
	int i=1;
	srand(time(NULL));
	cantPer--;
	//periodo 1: desde donde se sacará un ramo
	int deDonde = rand()%cantPer;
	deDonde++;
	while(periodo1->num_periodo!=deDonde)
		periodo1=periodo1->sig;
	int cantRamos=getCantRamos(periodo1);
	//en caso de que el periodo elegido no tenga ramos elegir uno nuevo
	while(cantRamos==0)
	{
		deDonde = rand()%cantPer-1;
		deDonde++;
		while(periodo1->num_periodo!=deDonde)
			periodo1=periodo1->sig;
		cantRamos=getCantRamos(periodo1);
	}
	//periodo 2: hacia donde moveremos el ramo
	int paraDonde =rand()%cantPer;
	paraDonde++;
	while(periodo2->num_periodo!=paraDonde)
		periodo2=periodo2->sig;
	//ramo a mover
	int ramo=rand()%cantRamos-1;
	ramo++;
	//caso especial: cuando es el primer ramo en la lista
	if(ramo==0)
	{
		aMover=periodo1->sigcur;
		periodo1->sigcur=NULL;
	}
	//caso de que no sea el primer ramo
	else
	{
		aMover=periodo1->sigcur;
		for(i=0;i<ramo;i++)
		{
			anterior=aMover;
			aMover=aMover->sigcur;
		}
		anterior->sigcur=aMover->sigcur;
		aMover->sigcur=NULL;
	}
	//aplicar el movimiento
	//caso especial: cuando la lista de cursos del periodo 2 está vacía
	if(periodo2->sigcur==NULL)
	{
		periodo2->sigcur=aMover;
		aMover->sigcur=NULL;
	}
	//en caso de que existan cursos en la lista del periodo 2
	else
	{
		aux=periodo2->sigcur;
		while(aux->sigcur!=NULL)
			aux=aux->sigcur;
		aux->sigcur=aMover;
		aMover->sigcur=NULL;
	}
	//reajustar los creditos de los periodos modificados
	periodo1->creditos= periodo1->creditos - getCantCreditos(cursos,aMover->num_cur);
	periodo2->creditos= periodo2->creditos + getCantCreditos(cursos,aMover->num_cur);
	return solucion;
}

pSol duplicarSol(pSol solucion)
{
	pSol duplicada=(pSol)malloc(sizeof(tipoSol));
	duplicada->num_periodo=1;
	duplicada->creditos=solucion->creditos;
	duplicada->sig=NULL;
	duplicada->sigcur=NULL;
	pSol aux=solucion;
	pCur dCur=(pCur)malloc(sizeof(tipoCur));
	pCur aux2;
	pSol actual;
	pCur dCur2;
	pCur dCur3;
	//primer periodo
	if(aux->sigcur!=NULL)
	{
		aux2=aux->sigcur;
		dCur->num_cur=aux2->num_cur;
		dCur->sigcur=NULL;
		duplicada->sigcur=dCur;
		aux2=aux2->sigcur;
		while(aux2!=NULL)
		{
			dCur2=(pCur)malloc(sizeof(tipoCur));
			dCur2->num_cur=aux2->num_cur;
			dCur2->sigcur=NULL;
			dCur->sigcur=dCur2;
			aux2=aux2->sigcur;
			dCur=dCur->sigcur;
		}
	}
	aux=aux->sig;
	//resto de los periodos
	while(aux!=NULL)
	{
		actual=appendPeriodo(duplicada,aux->num_periodo);
		actual->creditos=aux->creditos;
		if(aux->sigcur!=NULL)
		{
			aux2=aux->sigcur;
			dCur3=(pCur)malloc(sizeof(tipoCur));
			dCur3->num_cur=aux2->num_cur;
			dCur3->sigcur=NULL;
			actual->sigcur=dCur3;
			aux2=aux2->sigcur;
			while(aux2!=NULL)
			{
				dCur2=(pCur)malloc(sizeof(tipoCur));
				dCur2->num_cur=aux2->num_cur;
				dCur2->sigcur=NULL;
				dCur3->sigcur=dCur2;
				aux2=aux2->sigcur;
				dCur3=dCur3->sigcur;
			}
		}
		aux=aux->sig;
	}
	return duplicada;
}

int getCantRamos(pSol periodo)
{
	pCur aux;
	int i=0;
	if(periodo->sigcur==NULL)
		return 0;
	else
	{
		aux=periodo->sigcur;
		while(aux!=NULL)
		{
			i++;
			aux=aux->sigcur;
		}
	}
	return i;
}

void limpiarGreedy(pCurso cursos)
{
	pCurso aux=cursos;
	pPR aux2;
	while(aux!=NULL)
	{
		aux->flag=1;
		if(aux->sigPR==NULL)
			aux=aux->sig;
		else
		{
			aux2=aux->sigPR;
			while(aux2!=NULL){
				aux2->flag=1;
				aux2=aux2->sig;
			}
			aux=aux->sig;
		}
	}
	return;
}

int maxCreditosSolucion(pSol solucion)
{
	int eval=solucion->creditos;
	pSol aux=solucion;
	while(aux!=NULL)
	{
		if(aux->creditos>eval)
		{
			eval=aux->creditos;
		}
		aux=aux->sig;
	}
	return eval;
}