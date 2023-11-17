#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
double silnia(double k) {
	double suma=1;
	while(k){
		suma*=k;
		k--;
	}
	return suma;
}

double pot(double a, double k) {
	if (k == 0)return 1;
	else return pot(a,k - 1) * a;
}

double fi(double n, double x) {
	double suma = 0;
	double k = 0;
	while(k<=n){
		suma += silnia(n) / (silnia(k) * silnia(k) * silnia(n - k)) * pot(x, k)* pot(-1,k);
		k++;
	}
return suma; 
}
double dfi(double n, double x) {
	double suma = 0;
	double k = 1;
	while (k <= n) {
		suma += (silnia(n) / (silnia(k) * silnia(k) * silnia(n - k))) * k * pot(-1, k) *pot(x,k-1);
		k++;
	}
	return suma;

}
double d2fi(double n, double x){
	double suma =0;
	double k =2;
	while(k<=n) {
		suma+= (silnia(n) / (silnia(k)*silnia(k) * silnia(n-k))) * pot(-1, k) *k *(k-1)* pot(x, k-2);
		k++;
	}
	return suma;
}
double d3fi(double n, double x){
	double suma = 0;
	double k=3;
	while(k<=n) {
		suma +=(silnia(n) / (silnia(k)*silnia(k) * silnia(n-k))) * pot(-1, k) * k *(k-1)*(k-2)*pot(x, k-3);
		k++;
	}
	return suma;
}
void make_spl(points_t *pts, spline_t *spl)
{
	matrix_t       *eqs= NULL;
	double         *x = pts->x;
	double         *y = pts->y;
	double		a = x[0];
	double		b = x[pts->n - 1];
	int		i, j, k;
	int		nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
	char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );

	eqs = make_matrix(nb, nb + 1);
	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(i, x[k]) * fi(j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(j, x[k]));
	}
		if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i*(b-a)/(spl->n-1);
			xx+= 10.0*DBL_EPSILON;  // zabezpieczenie przed ulokowaniem punktu w poprzednim przedziale
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double		ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * fi  (k, xx);
				spl->f1[i] += ck * dfi (k, xx);
				spl->f2[i] += ck * d2fi(k, xx);
				spl->f3[i] += ck * d3fi(k, xx);
			}
		}
	}

}
