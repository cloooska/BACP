#include "Librerias/general.h"

int getCantCursos(malla m)
{
    return m->cant_cursos;
}

int getCantPeriodos(malla m)
{
    return m->cant_periodos;
}

int getMinCreditos(malla m)
{
    return m->min_creditos;
}

int getMaxCreditos(malla m)
{
    return m->max_creditos;
}

int getMinCursos(malla m)
{
    return m->min_cursos;
}

int getMaxCursos(malla m)
{
    return m->max_cursos;
}

int getTotalPrereq(malla m)
{
    return m->total_prerrequisitos;
}
