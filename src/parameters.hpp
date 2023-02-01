/*
* Input parameters
*
* Allow the user to choose the input parameters for the simulation
* and check the correctness of the parameters.
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

extern double DELT,TMAX,L,H,U,V,DIFF;
extern int NI,NJ,WRITE_INTERVAL;

extern int BCE,BCW,BCN,BCS;
extern double INITPHI,BCVALE,BCVALW,BCVALN,BCVALS;

void CHECK_PARAMETERS();

#endif