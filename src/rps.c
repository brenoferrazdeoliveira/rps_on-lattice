#include "../rps.h"

#define r (double)NG/NF
#define q pow(NG, 1.0/(NF-1))

void ic(const gsl_rng *w, int *);     /* initial conditions      */
void op(int , int *);                 /* data output             */

int main(int argc, char **argv){
	int i, j, t, ac, ps, tp, gd, nb, l=0;
#if Nz > 1
	int k;
#endif 
	int *phi, *dst;
	double at, n_m, n_p, n_r;
	PROBABILITY_OF_PREDATION
	FILE *file;

#if LS == 1
	double a0= 1.0;
#else
	double a0= r;
#endif

	phi= (int *) calloc(Nx*Ny*Nz, sizeof(int));
	dst= (int *) calloc((NS+1), sizeof(int));

	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

	ic(w, phi);

	for(i= 0; i< Nx*Ny*Nz; i++){
		dst[phi[i]]++;
	}

	n_m= n_p= n_r= 0.0; 
	for(t= 1; t<= NG; t++){
		gd= 0;
		while(gd < Nx*Ny*Nz){
#if Nz == 1
			i= gsl_rng_uniform(w)*Nx;
			j= gsl_rng_uniform(w)*Ny;
			ac= j*Nx+i;
#else
			i= gsl_rng_uniform(w)*Nx;
			j= gsl_rng_uniform(w)*Ny;
			k= gsl_rng_uniform(w)*Nz;
			ac= (k*Ny+j)*Nx+i;
#endif
			if(phi[ac] != 0){
#if Nz == 1
				nb= gsl_rng_uniform(w)*4;
				switch(nb){
					case 0:
					  ps= j*Nx+((i+1)%Nx);
					break;
					case 1:
				    ps= j*Nx+((i-1+Nx)%Nx);
					break;
					case 2:
			      ps= ((j+1)%Ny)*Nx+i;
					break;
					default:
						ps= ((j-1+Ny)%Ny)*Nx+i;
				}
#else
				nb= gsl_rng_uniform(w)*6;
				switch(nb){
          case 0:
            ps= (k*Ny+j)*Nx+((i+1)%Nx);
          break;
          case 1:
            ps= (k*Ny+j)*Nx+((i-1+Nx)%Nx);
          break;
          case 2:
            ps= ((k*Ny)+(j+1)%Ny)*Nx+i;
          break;
          case 3:
            ps= ((k*Ny)+(j-1+Ny)%Ny)*Nx+i;
          break;
          case 4:
            ps= (((k+1)%Nz)*Ny+j)*Nx+i;
          break;
          default:
            ps= (((k-1+Nz)%Nz)*Ny+j)*Nx+i;
        }
#endif
				at= gsl_rng_uniform(w);
				if(at < pm){
					tp= phi[ps];
					phi[ps]= phi[ac];
					phi[ac]= tp;
					gd++; n_m++;
				}else{
					if(at >= pm && at < (pm+ pp)){
						if(phi[ps] != 0 && gsl_rng_uniform(w) < p[(phi[ac]-1)*NS+phi[ps]-1]){
							dst[phi[ps]]--;
							dst[0]++;
							phi[ps]= 0;
							gd++; n_p++;
						}
					}else{
						if(phi[ps] == 0){
							phi[ps]= phi[ac];
							dst[phi[ps]]++;
							dst[0]--;
							gd++; n_r++;
						}
					}
				}
			}
		}

		file= fopen("dat/dst.dat", "a");
		for(i= 1; i< (NS+1); i++){
			fprintf(file, "%e ", (double)dst[i]/(Nx*Ny*Nz));
		}
		fprintf(file, "%e\n", (double)dst[0]/(Nx*Ny*Nz));
		fclose(file);
		if(t >= round(a0)){
#if LS == 1
			a0*= q;
#else
			a0+= r;
#endif
			op(++l, phi);
			printf("%d %d/%d\n", l, t, NG);
		}
	}
	file= fopen("dat/mpr.dat", "a");
	fprintf(file, "%e %e %e", n_m/(n_m+n_p+n_r), n_p/(n_m+n_p+n_r), n_r/(n_m+n_p+n_r));
	fclose(file);

	gsl_rng_free(w);
	free(phi);
	free(dst);
	return 0;
}
