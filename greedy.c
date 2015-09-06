#include "Librerias/general.h"
#include "Librerias/greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//GREEDY -> Solucion Inicial para el SA
//inicio: primer curso sin prerrequisitos.
//miope: agrega todos los cursos con sus prerequisitos satisfechos
//		en el periodo actual a menos que no satisfaga restricciones
//      del tipo min o max de creditos o cursos y ahí salta al sgte
//		periodo.
//funcion de evaluacion: max de carga academica entre periodos.
pSol Greedy2(malla m,pCurso cursos)
{
	pSol solucion=(pSol)malloc(sizeof(tipoSol));
	solucion->num_periodo=1;
	solucion->creditos=0;
	solucion->sig=NULL;
	solucion->sigcur=NULL;
	int i,noAsignados,cantPer=getCantPeriodos(m);
	solucion->sig=NULL;
	solucion->sigcur=NULL;
	pSol aux=solucion;
	pCurso prueba;
	int cu=0;
	//int promCursos=getCantCursos(m)/cantPer;
	int maxCr=getMaxCreditos(m);
	//int minCr=getMinCreditos(m);
	int maxCu=getMaxCursos(m);
	//int minCu=getMinCursos(m);
	int promCr=mediaCreditos(cursos,m);
	//primer periodo
	while(aux->creditos<=maxCr && ++cu<=maxCu)
	{
		prueba=buscarCurso(cursos);
		if(aux->creditos+prueba->cant_creditos<=promCr)
		{
			appendCur(prueba->num_curso,aux);
			marcarCurso(cursos,prueba->num_curso,0);
			marcarPR(cursos,prueba->num_curso);
			limpiarFallidos(cursos);
			aux->creditos=aux->creditos + prueba->cant_creditos;
		}
	}
	cu=0;
	//resto de los periodos
	for(i=2;i<=cantPer;i++)
	{
		aux=appendPeriodo(solucion,i);
		while(aux->creditos<=maxCr && ++cu<=maxCu)
		{
			prueba=buscarCurso(cursos);
			if(aux->creditos+prueba->cant_creditos<=promCr)
			{
				appendCur(prueba->num_curso,aux);
				marcarCurso(cursos,prueba->num_curso,0);
				marcarPR(cursos,prueba->num_curso);
				limpiarFallidos(cursos);
				aux->creditos=aux->creditos + prueba->cant_creditos;
			}
		}
		cu=0;
	}
	noAsignados=cursosNoAsignados(cursos);
	aux=periodoMenorCreditos(solucion);
	if(noAsignados!=0)
	{
		for(i=1;i<=noAsignados;i++)
		{
			prueba=buscarCurso(cursos);
			appendCur(prueba->num_curso,aux);
			marcarCurso(cursos,prueba->num_curso,0);
			marcarPR(cursos,prueba->num_curso);
			aux->creditos=aux->creditos + prueba->cant_creditos;
			aux=periodoMenorCreditos(solucion);
		}
	}
	return solucion;
}

pSol periodoMenorCreditos(pSol solucion)
{
	pSol aux=solucion;
	int mejorPeriodo=aux->num_periodo;
	int mejorCredito=aux->creditos;
	while(aux!=NULL)
	{
		if(mejorCredito>aux->creditos)
		{
			mejorPeriodo=aux->num_periodo;
			mejorCredito=aux->creditos;
		}
		aux=aux->sig;
	}
	aux=solucion;
	while(aux->num_periodo!=mejorPeriodo)
		aux=aux->sig;
	return aux;
}

int cursosNoAsignados(pCurso cursos)
{
	pCurso aux=cursos;
	int i=0;
	while(aux!=NULL)
	{
		if(aux->flag==1)
			i++;
		aux=aux->sig;
	}
	return i;
}

int mediaCreditos(pCurso cursos,malla m)
{
	pCurso aux=cursos;
	float creditos=0,media;
	while(aux!=NULL)
	{
		creditos=creditos+aux->cant_creditos;
		aux=aux->sig;
	}
	media=creditos/getCantPeriodos(m);
	return ceil(media);
}

void showCursos(pCurso cursos)
{
	pCurso aux=cursos;
	while(aux!=NULL)
	{
		printf("Curso %d flag: %d\n",aux->num_curso,aux->flag);
		aux=aux->sig;
	}
	return;
}

void showPrerrequisitos(pCurso cursos,int numero)
{
	pCurso aux=cursos;
	pPR aux2;
	while(aux->num_curso!=numero)
		aux=aux->sig;
	aux2=aux->sigPR;
	if(aux->sigPR==NULL){
		printf("curso %d sin prerrequisitos: %d flag: %d\n",aux->num_curso,aux->cant_prerrequisitos,aux->flag);
	}
	else{
		while(aux2!=NULL){
			printf("curso: %d cantPR: %d\n", aux2->num_curso,aux->cant_prerrequisitos);
			aux2=aux2->sig;
		}
	}
	return;
}

pSol appendPeriodo(pSol solucion,int semestre)
{
	//printf("entre a appendPeriodo\n");
	pSol aux=solucion;
	pSol nuevo=(pSol)malloc(sizeof(tipoSol));
	nuevo->num_periodo=semestre;
	nuevo->creditos=0;
	nuevo->sig=NULL;
	nuevo->sigcur=NULL;
	while(aux->sig!=NULL)
		aux=aux->sig;
	aux->sig=nuevo;
	return nuevo;
}

//funcion para crear curso unicamente con la
//cantidad de creditos y el numero del curso
pCurso nuevo_curso(int num,int creditos)
{
	pCurso nuevo;
	nuevo = (pCurso)malloc(sizeof(tipoCurso));
	nuevo->num_curso=num;
	nuevo->cant_creditos=creditos;
	nuevo->cant_prerrequisitos=0;
	nuevo->flag=1;
	nuevo->sig=NULL;
	nuevo->sigPR=NULL;
	return nuevo;
}

//muestra la solucion
void mostrar(pSol solucion){
	pSol aux=solucion;
	pCur aux2;
	while(aux!=NULL){
		printf("Periodo: %d\n",aux->num_periodo);
		aux2=aux->sigcur;
		while(aux2!=NULL){
			printf("%d  ", aux2->num_cur);
			aux2=aux2->sigcur;
		}
		printf(": %d\n",aux->creditos);
		aux = aux->sig;
	}
	return;
}

pCurso buscarCurso(pCurso cursos)
{
	pCurso aux=cursos;
	while(aux!=NULL)
	{
		if(aux->flag==1 && aux->cant_prerrequisitos==0){
			return aux;
		}
		else
			aux=aux->sig;
	}
	return NULL;
}

void appendCur(int curso,pSol per_actual)
{
	pSol aux=per_actual;
	pCur aux2;
	pCur nuevo=(pCur)malloc(sizeof(tipoCur));
	nuevo->num_cur=curso;
	nuevo->sigcur=NULL;
	if(aux->sigcur==NULL)
		aux->sigcur=nuevo;
	else{
		aux2=aux->sigcur;
		while(aux2->sigcur!=NULL)
			aux2=aux2->sigcur;
		aux2->sigcur=nuevo;
	}
	return;
}

void marcarCurso(pCurso cursos,int curso,int flag)
{
	pCurso aux=cursos;
	while(aux->num_curso!=curso)
		aux=aux->sig;
	aux->flag=flag;
	return;
}

void marcarPR(pCurso cursos,int curso)
{
	pCurso aux=cursos;
	pPR aux2;
	while(aux!=NULL){
		if(aux->cant_prerrequisitos!=0)
		{
			aux2=aux->sigPR;
			while(aux2 && aux2->num_curso!=curso)
				aux2=aux2->sig;
			if(aux2){
				aux2->flag=0;
				aux->cant_prerrequisitos--;
			}
		}
		aux=aux->sig;
	}
	return;
}

void limpiarFallidos(pCurso cursos)
{
	pCurso aux=cursos;
	while(aux!=NULL)
	{
		if(aux->flag==2)
			aux->flag=1;
		aux=aux->sig;
	}
	return;
}