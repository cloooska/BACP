#include "Librerias/general.h"
#include "Librerias/greedy.h"
#include <stdio.h>
#include <stdlib.h>


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
	int i,cantPer=getCantPeriodos(m);
	solucion->sig=NULL;
	solucion->sigcur=NULL;
	pSol aux=solucion;
	pCurso prueba;
	int cu=0;
	int verificador=0;
	int promCursos=getCantCursos(m)/cantPer;
	int maxCr=getMaxCreditos(m);
	for( i=1 ; i<=cantPer ; i++ )
	{
		appendPeriodo(solucion,i);
		while(aux->sig!=NULL)
			aux=aux->sig;
		while(aux->creditos<=maxCr && ++cu<=promCursos)
		{
			verificador=0;
			while(verificador==0)
			{
				prueba=buscarCurso(cursos);
				if(prueba!=NULL)
				{
					if(prueba->cant_creditos+aux->creditos<=maxCr)
					{
						appendCur(prueba->num_curso,aux);
						aux->creditos=prueba->cant_creditos+aux->creditos;
						mostrar(solucion);
						marcarCurso(cursos,prueba->num_curso,0);
						marcarPR(cursos,prueba->num_curso);
						limpiarFallidos(cursos);
						verificador=1;
					}
					else{
						prueba->flag=2;
					}
				}
			}
		}
	}
	return solucion;
}


void appendPeriodo(pSol solucion,int semestre)
{
	pSol aux=solucion;
	pSol nuevo=(pSol)malloc(sizeof(tipoSol));
	nuevo->num_periodo=semestre;
	nuevo->creditos=0;
	nuevo->sig=NULL;
	nuevo->sigcur=NULL;
	if(solucion->num_periodo!=1){
		while(aux->sig!=NULL)
			aux=aux->sig;
		aux->sig=nuevo;
	}
	return;
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
			printf("%d  -", aux2->num_cur);
			aux2=aux2->sigcur;
		}
		printf(": %d\n",aux->creditos);
		aux = aux->sig;
	}
	return;
}

void cosa(pCurso curso,int num)
{
	pCurso aux=curso;
	pPR aux2;
	while(aux->num_curso!=num)
		aux=aux->sig;
	aux2=aux->sigPR;
	while(aux2!=NULL){
		printf("el curso %d tiene el pr: %d\n",aux->num_curso,aux2->num_curso);
		aux2=aux2->sig;
	}
	return;
}

pCurso buscarCurso(pCurso cursos)
{
	pCurso aux=cursos;
	while(aux!=NULL)
		if(aux->flag==1 && aux->cant_prerrequisitos==0){
			return aux;
		}
		aux=aux->sig;
	return NULL;
}

void appendCur(int curso,pSol per_actual)
{
	pSol aux=per_actual;
	pCur aux2;
	pCur nuevo=(pCur)malloc(sizeof(tipoCur));
	nuevo->num_cur=curso;
	nuevo->sigcur=NULL;
	printf("agregando el nuevo curso %d en el periodo %d\n",nuevo->num_cur,aux->num_periodo);
	if(aux->sigcur==NULL){
		printf("entre a agregar el primer curso ene l periodo %d\n",aux->num_periodo);
		aux->sigcur=nuevo;
		return;
	}
	aux2=aux->sigcur;
	while(aux2->sigcur!=NULL)
		aux2=aux2->sigcur;
	aux2->sigcur=nuevo;
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
			if(aux2!=NULL){
				aux2->flag=0;
				aux->cant_prerrequisitos=aux->cant_prerrequisitos-1;
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