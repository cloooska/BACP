#include "Librerias/greedy.h"
#include "Librerias/general.h"
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
			while(verificador==0)
			{
				prueba=buscarCurso(cursos);
				if(prueba!=NULL)
				{
					if(prueba->cant_creditos+aux->creditos<=maxCr)
					{
						appendCur(prueba->num_curso,aux);
						marcarCurso(cursos,prueba->num_curso,0);
						marcarPR(cursos,prueba->num_curso);
						limpiarFallidos(cursos);
						aux->creditos=prueba->cant_creditos+aux->creditos;
						verificador=1;
					}
					else{
						prueba->flag=2;
					}
				}
			}
		}
		aux=solucion;
	}
	return solucion;
}