#include "parameters.hpp"
#include<cassert>

int NI=202; // Number of cells in x direction + 2 (to account for boundary cells)
int NJ=12; // Number of cells in y direction + 2 (to account for boundary cells)
double L=20.; // Length of the computational domain
double H=1.; // Height of the computational domain
double DELT=0.0001; // Time-step size
double TMAX=40.; // Maximum simulation time 
double U=1.; // Advection velocity in x direction
double V=0.; // Advection velocity in y direction
double DIFF=1/70.; // Diffusion coefficient
int WRITE_INTERVAL=10000; // Interval (time-steps) at which output files should be generated

double INITPHI=0.; // Initial condition of phi

//Boundary conditions : 1 for fixed value, -1 for fixed gradient
int BCE=-1; //BC at east boundary
int BCW=1; //BC at west boundary
int BCN=1; //BC at north boundary
int BCS=1; //BC at south boundary
//Boundary condition value : Set the value of the scalar or the gradient based on the selection
double BCVALE=0.; //East
double BCVALW=1.; //West
double BCVALN=0.; //North
double BCVALS=0.; //South

void CHECK_PARAMETERS(){
    assert(("There should be at least 1 grid cell in x direction",NI>2));
    assert(("There should be at least 1 grid cell in y direction",NJ>2));
    assert(("Length of domain cannot be zero or negative",L>0));
    assert(("Height of domain cannot be zero or negative",H>0));
    assert(("Time-step cannot be zero or negative",DELT>0));
    assert(("End time cannot be zero or negative",TMAX>0));
    assert(("Time-step cannot be larger than simulation end time",DELT<TMAX));
    assert(("Diffusion coefficient cannot be negative",DIFF>=0));
    assert(("Write interval cannot be zero or negative",WRITE_INTERVAL>0));

    assert(("Undefined boundary condition selected",(BCE==1 || BCE == -1) && (BCN==1 || BCN == -1) && (BCW==1 || BCW == -1) && (BCS==1 || BCS == -1)));
}
