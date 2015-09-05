#include "Librerias/general.h"
#include "Librerias/sa.h"
#include "Librerias/greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

pSol SA(pSol inicial,malla m,pCurso cursos)
{
	pSol aux=inicial;
	pSol nueva; //quizas deba hacerle malloc
	limpiarGreedy(cursos);
	int MaxCrSol=maxCreditosSolucion(inicial);
	int T=MaxCrSol,t=0;
	srand(time(NULL));
	printf("cantidad de ramos periodo 1: %d\n",getCantRamos(inicial));
	int cantPer = getCantPeriodos(m);
	//mover(inicial,cantPer,cursos);
	mostrar(inicial);
	nueva=duplicarSol(inicial);
	mostrar(nueva);
	/*while(maxCreditosSolucion(aux)>=promCreditos(cursos,m))
	{
		while(t%10!=0)
		{	
			float prob = rand()%1000000;
			prob=prob/1000000;
			//nueva=mover ramo de periodo
			//ifs correspondientes
		}
		T++;
	}*/
	return inicial;
}

int getCantCreditos(pCurso cursos, int num_curso)
{
	pCurso aux;
	while(aux->num_curso!=num_curso)
		aux=aux->sig;
	return aux->cant_creditos;
}

pSol mover(pSol solucion,int cantPer,pCurso cursos)
{
	pSol periodo1=solucion,periodo2=solucion;
	pCur aMover,anterior,aux;
	srand(time(NULL));
	cantPer--;
	//desde donde periodo1
	int deDonde = rand()%cantPer-1;
	deDonde++;
	while(periodo1->num_periodo!=deDonde)
		periodo1=periodo1->sig;
	printf("periodo1= %d\n", periodo1->num_periodo);
	int cantRamos=getCantRamos(periodo1);
	//ramo
	int ramo=rand()%cantRamos-1;
	ramo++;
	if(cantRamos!=0)
	{
		aMover=periodo1->sigcur;
		for(int i=1;i<=ramo;i++)
		{
			anterior=aMover;
			aMover=aMover->sigcur;
		}
		printf("aMover: %d\n", aMover->num_cur);
		printf("anterior: %d\n", anterior->num_cur);
	}
	//para donde periodo2
	int paraDonde =rand()%cantPer-1;
	paraDonde++;
	while(periodo2->num_periodo!=paraDonde)
		periodo2=periodo2->sig;
	printf("periodo2= %d\n", periodo2->num_periodo);
	//hacer el cambio
	anterior=aMover->sigcur;
	aux=periodo2->sigcur;
	while(aux->sigcur!=NULL)
		aux=aux->sigcur;
	printf("desde aquí hay violación de segmento\n");
	aux->sigcur=aMover;
	aMover->sigcur=NULL;
	int creditos=getCantCreditos(cursos,aMover->num_cur);
	periodo1->creditos=periodo1->creditos-creditos;
	periodo2->creditos=periodo2->creditos+creditos;
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
	//primer periodo
	if(aux->sigcur!=NULL)
	{
		aux2=aux->sigcur;
		dCur->num_cur=aux2->num_cur;
		dCur->sigcur=NULL;
		duplicada->sigcur=dCur;
		while(aux2!=NULL)
		{
			pCur dCur2=(pCur)malloc(sizeof(tipoCur));
			dCur2->num_cur=aux2->num_cur;
			dCur2->sigcur=NULL;
			aux2=aux2->sigcur;
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
			pCur dCur3=(pCur)malloc(sizeof(tipoCur));
			dCur3->num_cur=aux2->num_cur;
			dCur3->sigcur=NULL;
			actual->sigcur=dCur3;
			while(aux2!=NULL)
			{
				pCur dCur2=(pCur)malloc(sizeof(tipoCur));
				dCur2->num_cur=aux2->num_cur;
				dCur2->sigcur=NULL;
				aux2=aux2->sigcur;
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