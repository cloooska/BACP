#ifndef _SA_H_INCLUDED_
#define _SA_H_INCLUDED_

pSol SA(pSol inicial,malla m,pCurso cursos);
void limpiarGreedy(pCurso cursos);
int maxCreditosSolucion(pSol solucion);
pSol mover(pSol solucion,int cantPer,pCurso cursos);
int getCantRamos(pSol periodo);
pSol duplicarSol(pSol solucion);

#endif