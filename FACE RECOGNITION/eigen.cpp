#include <stdio.h>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <iostream>
using namespace std;

const int maxn = 1000;
double data[maxn*maxn];

int main(int argc, char** argv)
{
	int n;
	fstream fin(argv[1]);
	//cout << "eigen : argv[1]" << argv[1] << endl;
	fin >> n;
	//cout << "eigen : n" << n << endl;
	for(int i = 0; i < n*n; i++) fin >> data[i];
	fin.close();
	gsl_matrix_view m = gsl_matrix_view_array(data, n, n);
	gsl_vector *eval = gsl_vector_alloc(n);
	gsl_matrix *evec = gsl_matrix_alloc(n, n);
	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc(n);
	gsl_eigen_symmv(&m.matrix, eval, evec, w);
	gsl_eigen_symmv_free(w);
	gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);
	FILE* f = fopen(argv[1], "w+");
	for (int i = 0; i < n; i++)
	{
		double eval_i = gsl_vector_get(eval, i);
		gsl_vector_view evec_i = gsl_matrix_column(evec, i);
		fprintf(f, "%f\n", eval_i);
		gsl_vector_fprintf(f, &evec_i.vector, "%f");
	}
	fclose(f);
	gsl_vector_free(eval);
	gsl_matrix_free(evec);
	return 0;
}
