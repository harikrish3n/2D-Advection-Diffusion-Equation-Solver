#include "mesh.hpp"

double DELX = L / (NI-2.), DELY = H / (NJ-2.); // Calculate the grid spacing in x and y directions
int NCELLI = NI-1, NCELLJ = NJ-1; // Defined to make looping over grid cells easier (Without considering boundary cells)

matrix X0(NIJ),X1(NIJ),X2(NIJ),X3(NIJ),Y0(NIJ),Y1(NIJ),Y2(NIJ),Y3(NIJ),XCELL(NIJ),YCELL(NIJ); // Coordinates of the cell vertices and cell centre
matrix S0(NIJ),S1(NIJ),S2(NIJ),S3(NIJ),DXF0(NIJ),DXF1(NIJ),DXF2(NIJ),DXF3(NIJ),VOL(NIJ); // Nodal distance, surface areas and volume of cells

// Generate the mesh based on the user-specified number of cells and size of domain
void GENERATE_MESH(){
    for(auto i=1; i<NCELLI; i++){
        for(auto j=1; j<NCELLJ; j++){
            X0[i][j] = DELX * (i-1); // Bottom left vertex x coord
            X1[i][j] = DELX * i; // Bottom right vertex x coord
            X2[i][j] = DELX * i; // Top right vertex x coord
            X3[i][j] = DELX * (i-1); // Top left vertex x coord
            Y0[i][j] = DELY * (j-1); // Bottom left vertex y coord
            Y1[i][j] = DELY * (j-1); // Bottom right vertex y coord
            Y2[i][j] = DELY * j; // Top right vertex y coord
            Y3[i][j] = DELY * j; // Top left vertex y coord
            XCELL[i][j] = 0.25 * (X0[i][j] + X1[i][j] + X2[i][j] + X3[i][j]); // Cell centre x coord
            YCELL[i][j] = 0.25 * (Y0[i][j] + Y1[i][j] + Y2[i][j] + Y3[i][j]); // Cell centre y coord
            S0[i][j] = DELY; // Surface area of west face
			S1[i][j] = DELX; // Surface area of south face
			S2[i][j] = DELY; // Surface area of east face
			S3[i][j] = DELX; // Surface area of north face
			DXF0[i][j] = DELX; // Nodal distance in west
			DXF1[i][j] = DELY; // Nodal distance in south
			DXF2[i][j] = DELX; // Nodal distance in east
			DXF3[i][j] = DELY; // Nodal distance in north
			VOL[i][j] = DELX * DELY; //Volume of cell
        }
    }
    //Defining coords for boundaries (only required for output files, not for computation)
    for(auto j=0;j<=NCELLJ;j++){
		XCELL[0][j] = 0; //West
		YCELL[0][j] = YCELL[1][j]; //West
		XCELL[NCELLI][j] = L; //East
		YCELL[NCELLI][j] = YCELL[NCELLI-1][j]; //East
	}
    for(auto i=0;i<=NCELLI; i++){
		XCELL[i][0] = XCELL[i][1]; //South
		YCELL[i][0] = 0; //South
		XCELL[i][NCELLJ] = XCELL[i][NCELLJ-1]; //North
		YCELL[i][NCELLJ] = H; //North
	}
}
