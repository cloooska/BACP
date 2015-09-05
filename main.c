/*
 =====================================================
 Name        : main.c
 Author      : Claudia Escobar
 ROL         : 201073562-1
 =====================================================
 */
#include "Librerias/general.h"
#include "Librerias/greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

FILE *instancia;

int main(int argc,char *argv[])
{
	malla m;
	pPR nuevo_pr=(pPR)malloc(sizeof(tipoPR));
	int i,j,a,b;
	int cred;
	pPR aux2;
	pCurso raiz_cursos,nuevo;
	pCurso aux = (pCurso)malloc(sizeof(tipoCurso));
	m = (malla)malloc(sizeof(General));
	instancia=fopen("bacp10.txt","r");
	if (instancia == NULL)
	{
		printf("El archivo 'bacp10.txt' no se encuentra accesible. Favor revisar su disponibilidad.\n");
		return 1;
	}
	//leer la primera linea de la instancia
	fscanf(instancia,"%d %d %d %d %d %d %d\n",
		&m->cant_cursos,
		&m->cant_periodos,
		&m->min_creditos,
		&m->max_creditos,
		&m->min_cursos,
		&m->max_cursos,
		&m->total_prerrequisitos);
	printf("%d %d %d %d %d %d %d\n",
		m->cant_cursos,
		m->cant_periodos,
		m->min_creditos,
		m->max_creditos,
		m->min_cursos,
		m->max_cursos,
		m->total_prerrequisitos);
	//leer y guardar la segunda linea de la instancia
	for(i=0;i<m->cant_cursos;i++)
	{
		fscanf(instancia,"%d",&cred);
		nuevo = nuevo_curso(i,cred);
		if(i==0)
		{
			raiz_cursos = nuevo;
		}
		else
		{
			aux=raiz_cursos;
			for(j=1;j<i;j++)
			{
				aux=aux->sig;
			}
			aux->sig=nuevo;
		}
	}
	//leer y guardar la tercera linea de la instancia
	for(i=0;i<m->total_prerrequisitos;i++)
	{
		pPR nuevo_pr=(pPR)malloc(sizeof(tipoPR));
		fscanf(instancia,"%d",&a);
		fscanf(instancia,"%d",&b);
		nuevo_pr->num_curso=b;
		nuevo_pr->flag=1;
		nuevo_pr->sig=NULL;
		aux=raiz_cursos;
		while(aux->num_curso!=a)
		{
			aux=aux->sig;
		}
		aux->cant_prerrequisitos++;
		if(aux->sigPR==NULL)
		{
			aux->sigPR=nuevo_pr;
		}
		else
		{
			aux2=aux->sigPR;
			while(aux2->sig!=NULL)
			{
				aux2=aux2->sig;
			}
			aux2->sig=nuevo_pr;
		}
	}
	pSol hola=Greedy2(m,raiz_cursos);
	mostrar(hola);
	pSol hola2=SA(hola,m,raiz_cursos);
	free(raiz_cursos);
	free(nuevo);
	free(nuevo_pr);
	return 0;
}