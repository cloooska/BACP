#ifndef _GREEDY_H_INCLUDED_
#define _GREEDY_H_INCLUDED_

pSol Greedy2(malla m,pCurso cursos);
pSol appendPeriodo(pSol solucion,int semestre);
pCurso nuevo_curso(int num,int creditos);
void mostrar(pSol solucion);
void cosa(pCurso curso,int num);
pCurso buscarCurso(pCurso cursos);
void appendCur(int curso,pSol per_actual);
void marcarCurso(pCurso cursos,int curso,int flag);
void marcarPR(pCurso cursos,int curso);
void limpiarFallidos(pCurso cursos);
void showCursos(pCurso cursos);
void showPrerrequisitos(pCurso cursos,int numero);
int mediaCreditos(pCurso cursos,malla m);
int cursosNoAsignados(pCurso cursos);

#endif