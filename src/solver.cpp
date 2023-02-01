#include "parameters.hpp"
#include "mesh.hpp"
#include "explicit.hpp"
#include "export.hpp"

#include<iostream>

int main(){
    auto NSTEP=0;
    CHECK_PARAMETERS();
    GENERATE_MESH();
    APPLY_IC();
    APPLY_BC();
    CALC_COEFFICIENTS();
	WRITE_FILE(NSTEP);
    for(NSTEP=1; NSTEP <= (TMAX/DELT); NSTEP++){
        APPLY_BC();
        SOLVE_EXPLICIT();
        UPDATE_VALUES();
		if( NSTEP % WRITE_INTERVAL == 0){
			WRITE_FILE(NSTEP);
		}
        if( NSTEP % int(TMAX/(10*DELT)) == 0){
            std::cout << int(100*NSTEP*DELT/TMAX) << "% completed \n"; // To show the progress (Useful for large simulations)
        }
    }
    return 0;
}