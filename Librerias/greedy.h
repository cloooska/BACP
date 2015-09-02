#ifndef _GREEDY_H_INCLUDED_
#define _GREEDY_H_INCLUDED_

//agregar nuevo periodo vacío al final
void appendPeriodo(pSol solucion,int semestre)
{
	pSol aux=solucion;
	pSol nuevo=(pSol)malloc(sizeof(tipoSol));
	nuevo->num_periodo=semestre;
	nuevo->creditos=0;
	nuevo->sig=NULL;
	nuevo->sigcur=NULL;
	if(aux==NULL)
		aux->sig=nuevo;
	else{
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
			printf("%d  ", aux2->num_cur);
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
	printf("entre a buscarCurso\n");
	pCurso aux=cursos;
	while(aux!=NULL)
		if(aux->flag==1 && aux->cant_prerrequisitos==0)
			return aux;
		aux=aux->sig;
	return NULL;
}

void appendCur(int curso,pSol per_actual)
{
	printf("entre a appendCur\n");
	pSol aux=per_actual;
	pCur aux2;
	pCur nuevo=(pCur)malloc(sizeof(tipoCur));
	nuevo->num_cur=curso;
	nuevo->sigcur=NULL;
	if(aux->sigcur==NULL){
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
	printf("entre a marcarCurso\n");
	pCurso aux=cursos;
	while(aux->num_curso!=curso)
		aux=aux->sig;
	aux->flag=flag;
	return;
}

void marcarPR(pCurso cursos,int curso)
{
	printf("entre a marcarPR\n");
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
	printf("entre a limpiarFallidos\n");
	pCurso aux=cursos;
	while(aux!=NULL)
	{
		if(aux->flag==2)
			aux->flag=1;
		aux=aux->sig;
	}
	return;
}

#endif