/*
* Create mesh
*
* Generate the mesh data (coordinates of vertices, cell centres, surface areas, volumes)
* based on the user input
*/

#ifndef MESH_H
#define MESH_H

#include "parameters.hpp"
#include<vector>

#define NIJ NI,std::vector<double>(NJ)

typedef std::vector<std::vector<double>> matrix;

extern matrix X0,X1,X2,X3,Y0,Y1,Y2,Y3,XCELL,YCELL;
extern matrix S0,S1,S2,S3,DXF0,DXF1,DXF2,DXF3,VOL;
extern double DELX,DELY;
extern int NCELLI,NCELLJ;

void GENERATE_MESH();
#endif