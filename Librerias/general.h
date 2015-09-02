#ifndef _GENERAL_H_INCLUDED_
#define _GENERAL_H_INCLUDED_

//estructura general de la malla
typedef struct Generals
{
	int cant_cursos;
	int cant_periodos;
	int min_creditos;
	int max_creditos;
	int min_cursos;
	int max_cursos;
	int total_prerrequisitos;
}General;

typedef General *malla;

//estructura de lista de prerrequisitos de un curso
typedef struct _pr
{
	int num_curso;
	int flag;
	struct _pr *sig;
}tipoPR;

typedef tipoPR *pPR;

//estructura de lista para los cursos
typedef struct _curso
{
	int num_curso;
	int cant_creditos;
	int cant_prerrequisitos;
	int flag;					//normal:1 , agregado:0 , fallido:2
	struct _pr *sigPR;
	struct _curso *sig;
}tipoCurso;

typedef tipoCurso *pCurso;

typedef struct _cur{
	int num_cur;
	struct _cur *sigcur;
}tipoCur;

typedef tipoCur *pCur;

//estructura de representacion para SA y Greedy
typedef struct _sol
{
	int num_periodo;
	int creditos;
	struct  _sol *sig;
	struct _cur *sigcur;
}tipoSol;

typedef tipoSol *pSol;

int getCantCursos(malla m);
int getCantPeriodos(malla m);
int getMinCreditos(malla m);
int getMaxCreditos(malla m);
int getMinCursos(malla m);
int getMaxCursos(malla m);
int getTotalPrereq(malla m);

#endif
