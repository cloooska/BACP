#ifndef _GREEDY_H_INCLUDED_
#define _GREEDY_H_INCLUDED_

pSol Greedy2(malla m,pCurso cursos);
void appendPeriodo(pSol solucion,int semestre);
pCurso nuevo_curso(int num,int creditos);
void mostrar(pSol solucion);
void cosa(pCurso curso,int num);
pCurso buscarCurso(pCurso cursos);
void appendCur(int curso,pSol per_actual);
void marcarCurso(pCurso cursos,int curso,int flag);
void marcarPR(pCurso cursos,int curso);
void limpiarFallidos(pCurso cursos);

#endif