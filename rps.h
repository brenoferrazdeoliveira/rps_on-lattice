#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#define Nx 500     /* grid size                      */
#define Ny 500     /* grid size                      */
#define Nz 1       /* grid size                      */
#define NG 10000   /* number of generations          */
#define NF 10      /* number of output files         */
#define LS 0       /* 0-> nolog time || 1-> log time */
#define NS 3       /* number of types of species     */
/* pm + pr + pp = 1.0                                */
#define pm 0.80    /* probability of motion          */
#define pr 0.10    /* probability of reproduction    */
#define pp 0.10    /* probability of predation       */

#define PROBABILITY_OF_PREDATION \
const double p[NS*NS]= {\
	0.0, 1.0, 0.0, \
	0.0, 0.0, 1.0, \
	1.0, 0.0, 0.0, \
};
