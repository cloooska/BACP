#ifndef _GREEDY_H_INCLUDED_
#define _GREEDY_H_INCLUDED_

pSol Greedy2(malla m,pCurso cursos);					//retorna una solucion inicial para el Simulated Annealing
pSol appendPeriodo(pSol solucion,int semestre);			//retorna un puntero al nuevo periodo añadido a solucion
pCurso nuevo_curso(int num,int creditos);				//retorna un puntero al nuevo curso creado
void mostrar(pSol solucion);							//muestra solucion por consola
pCurso buscarCurso(pCurso cursos);						//retorna un curso no añadido con sus prerrequisitos satisfechos
void appendCur(int curso,pSol per_actual);				//agrega un curso a la solución
void marcarCurso(pCurso cursos,int curso,int flag);		//Marca el flag de un curso
void marcarPR(pCurso cursos,int curso);					//Marca con flag 0 en la lista de los cursos con el PR curso y les baja la cant de creditos
void limpiarFallidos(pCurso cursos);					//Marca con flag 1 los cursos con flag 2
void showCursos(pCurso cursos);							//Muestra la lista de cursos
void showPrerrequisitos(pCurso cursos,int numero);		//Muestra los prerrequisitos del curso cursos
int mediaCreditos(pCurso cursos,malla m);				//Retorna el promedio de creditos de la malla
int cursosNoAsignados(pCurso cursos);					//retorna la cantidad de cursos no asignados aún a la solución del Greedy
pSol periodoMenorCreditos(pSol solucion);				//retorna el periodo con menor cantidad de creditos

#endif