#include "../rps.h"

void op(int NI, int *phi){
	int i, j;
	char name[100];
	sprintf(name, "dat/phi-%d.dat", NI);
	FILE *file= fopen(name,  "w");

#if Nz == 1
	for(j= 0; j< Ny; j++){
		for(i= 0; i< Nx; i++){
			fprintf(file, "%d ", phi[j*Nx+i]);
		}
		fprintf(file, "\n");
	}
#else
		int k;
		for(i= 0; i< Nx; i++){
			for(j= 0; j< Ny; j++){
				for(k= 0; k< Nz; k++){
					fprintf(file, "%d\n", phi[(i*Ny+j)*Nz+k]);
				}
			}
		}
#endif
	fclose(file);
}
