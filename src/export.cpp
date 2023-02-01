#include<sstream>
#include<fstream>
#include<iostream>
#include "explicit.hpp"

//Export VTK files at user-specified interval
void WRITE_FILE(int NSTEP){
	std::ostringstream sstream;
	sstream << NSTEP*DELT;
	std::ofstream file("data_" + sstream.str() + ".vtk");

	file << "# vtk DataFile Version 3.0\n";
	file << "Time " << sstream.str() << "\n";
	file << "ASCII\n";
	file << "DATASET STRUCTURED_GRID\n";
	file << "DIMENSIONS " << NI << " " << NJ << " 1\n";
	file << "POINTS " << NI*NJ << " float\n";

	for(auto j=0; j<NJ; j++){
		for(auto i=0; i<NI; i++){
			file << XCELL[i][j] << " " << YCELL[i][j] << " 0\n"; //Mesh data
		}
	}

	file << "POINT_DATA " << NI*NJ << "\n";
	file << "SCALARS PHI float 1\n";
	file << "LOOKUP_TABLE default\n";
	for(auto j=0; j<NJ; j++){
		for(auto i=0; i<NI; i++){
			if(PHI[i][j]<1e-40){PHI[i][j]=0;}
			file << PHI[i][j] << "\n";
		}
	}
}