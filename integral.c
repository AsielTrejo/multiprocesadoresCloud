#include <stdio.h>
#include <omp.h>
static long num_pasos = 100000000; 
//static long num_pasos = 500; 
   
//static long num_pasos = 1; 
double paso;

#define NUM_THREADS 18

//int NUM_THREADS;

void main() {

	//scanf("%lu", &num_pasos);
	int i, nthreads; 
	double pi, sum [NUM_THREADS], t1, t2, tiempo; 
	paso=1.0/num_pasos; 
	omp_set_num_threads (NUM_THREADS);
	const double startTime = omp_get_wtime();

#pragma omp parallel

{
	int i, id, nthrds; 
	double x;
	id = omp_get_thread_num(); 
	nthrds = omp_get_num_threads(); 
	if (id==0) nthreads=nthrds; 

	for (i=id, sum[id] =0.0;i<num_pasos; i=i+nthrds) {
		x=(i + 0.5) *paso;
		sum[id]+=4.0/(1.0+x*x);

	} 
}

for (i=0,pi=0.0;i<nthreads; i++) {
	pi+=sum[i]*paso;
	printf("el valor es %lf  con paso %lf  y pi igual a %lf \n",sum[i],paso,pi);
}
	const double endTime = omp_get_wtime();
	tiempo=t2-t1;
	printf("resultado es pi= (%lf), con %ld pasos \n",pi,num_pasos); 
	printf("Tiempo es %lf\n\n", (endTime - startTime));

}
