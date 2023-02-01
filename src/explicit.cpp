#include "explicit.hpp"
#include "mesh.hpp"
#include<cmath>
#include<algorithm>

matrix PHI(NIJ), PHI_OLD(NIJ); //Values of the scalar at the current and previous time-step
matrix AE(NIJ),AW(NIJ),AN(NIJ),AS(NIJ); // Advection term coefficients
matrix DE(NIJ),DW(NIJ),DN(NIJ),DS(NIJ),DP(NIJ); // Diffusion term coefficients

// Apply user-specified initial distribution
void APPLY_IC(){
	for(auto i=0; i<=NCELLI; i++){
		for(auto j=0; j<=NCELLJ; j++){
			PHI_OLD[i][j] = INITPHI;
			PHI[i][j] = INITPHI;
		}
	}
}

// Apply user-specified boundary conditions
void APPLY_BC(){
    for(auto j=0; j<=NCELLJ; j++){
        PHI[0][j] = std::max(BCW,0)*BCVALW - std::min(BCW,0)*(PHI[1][j] - BCVALW*DELX);
        PHI[NCELLI][j] = std::max(BCE,0)*BCVALE - std::min(BCE,0)*(PHI[NCELLI-1][j] - BCVALE*DELX);
        PHI_OLD[0][j] = std::max(BCW,0)*BCVALW - std::min(BCW,0)*(PHI_OLD[1][j] - BCVALW*DELX);
        PHI_OLD[NCELLI][j] = std::max(BCE,0)*BCVALE - std::min(BCE,0)*(PHI_OLD[NCELLI-1][j] - BCVALE*DELX);
    }
    for(auto i=0; i<=NCELLI; i++){
        PHI[i][0] = std::max(BCS,0)*BCVALS - std::min(BCS,0)*(PHI[i][1] - BCVALS*DELY);
        PHI[i][NCELLJ] =  std::max(BCN,0)*BCVALN - std::min(BCN,0)*(PHI[i][NCELLJ-1] - BCVALN*DELY);
        PHI_OLD[i][0] = std::max(BCS,0)*BCVALS - std::min(BCS,0)*(PHI_OLD[i][1] - BCVALS*DELY);
        PHI_OLD[i][NCELLJ] = std::max(BCN,0)*BCVALN - std::min(BCN,0)*(PHI_OLD[i][NCELLJ-1] - BCVALN*DELY); 
    }
}

// Calculate the coefficients for the advection and diffusion terms
void CALC_COEFFICIENTS(){
	for(auto i=1; i<NCELLI; i++){
		for(auto j=1; j<NCELLJ; j++){
			DW[i][j] = fabs(DIFF * S0[i][j] / DXF0[i][j]);
			DS[i][j] = fabs(DIFF * S1[i][j] / DXF1[i][j]);
			DE[i][j] = fabs(DIFF * S2[i][j] / DXF2[i][j]);
			DN[i][j] = fabs(DIFF * S3[i][j] / DXF3[i][j]);
			DP[i][j] = DW[i][j] + DS[i][j] + DE[i][j] + DN[i][j];
			AW[i][j] = fabs(U*S0[i][j]);
			AS[i][j] = fabs(V*S1[i][j]);
			AE[i][j] = fabs(U*S2[i][j]);
			AN[i][j] = fabs(V*S3[i][j]);
		}
	}
}

// Calculate the diffusion term
double CALC_DIF_TERM(int i, int j){
	return (DW[i][j]*PHI_OLD[i-1][j] + DE[i][j]*PHI_OLD[i+1][j] + DS[i][j]*PHI_OLD[i][j-1] + DN[i][j]*PHI_OLD[i][j+1] - DP[i][j]*PHI_OLD[i][j]);
}

// Calculate the advection term
double CALC_ADV_TERM(int i, int j){
	return std::max(U,0.)*(AE[i][j]*PHI_OLD[i][j] - AW[i][j]*PHI_OLD[i-1][j]) - std::min(U,0.)*(AE[i][j]*PHI_OLD[i+1][j] - AW[i][j]*PHI_OLD[i][j])
	       + std::max(V,0.)*(AN[i][j]*PHI_OLD[i][j] - AS[i][j]*PHI_OLD[i][j-1]) - std::min(V,0.)*(AN[i][j]*PHI_OLD[i][j+1] - AS[i][j]*PHI_OLD[i][j]);
}

// Solve the explicit form of the equation
void SOLVE_EXPLICIT(){
    for(auto i=1; i<NCELLI; i++)
	{
		for(auto j=1;j<NCELLJ; j++)
		{
			PHI[i][j] = PHI_OLD[i][j] + (DELT/VOL[i][j])*(CALC_DIF_TERM(i,j) - CALC_ADV_TERM(i,j));
		}
	}
}

//Update the previous values for the next time-step
void UPDATE_VALUES(){
    for(auto i=1; i<NCELLI; i++)
	{
		for(auto j=1;j<NCELLJ; j++)
		{
			PHI_OLD[i][j] = PHI[i][j];
		}
	}
}


