#include "../rps.h"

void ic(const gsl_rng *w, int *phi){
	int i;

	for(i= 0; i< Nx*Ny*Nz; i++){
		phi[i]= gsl_rng_uniform(w)*(NS+1);
	}
}
