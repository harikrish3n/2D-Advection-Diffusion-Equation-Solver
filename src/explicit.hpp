/*
* Explicit solver implementation
*
* Apply the initial and boundary conditions
* and solve the explicit equation
*/

#ifndef EXPLICIT_H
#define EXPLICIT_H
#include "mesh.hpp"

extern matrix PHI,PHI_OLD;
extern matrix AE,AW,AN,AS;
extern matrix DE,DW,DN,DS,DP;

void APPLY_IC();
void APPLY_BC();
void CALC_COEFFICIENTS();
double CALC_DIF_TERM(int i, int j);
double CALC_ADV_TERM(int i, int j);
void SOLVE_EXPLICIT();
void UPDATE_VALUES();

#endif