#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// compile like:  gcc -Wall -O2 -DNROWS=10000 matrix1.c -o matrix1


#define NCOLS 100

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() {
  unsigned int i,j;
  double *table;
  double ts,te,aps;
  double time;
  FILE *f;

  f=fopen("results.csv","a");




  table = (double *)malloc(NROWS*NCOLS*sizeof(double)); 
  if (table==NULL) {
    printf("alloc error!\n");
    exit(1);
  }

  // warmup

  for(i=0;i<NROWS*NCOLS;i++){
    table[i] = 1.0;
  }
  
  
  // get starting time (double, seconds) 
  get_walltime(&ts);
  
  // workload
  
  for(i=0;i<NROWS;i++){
    for(j=0;j<NCOLS;j++){
      table[i*NCOLS+j]= table[i*NCOLS+j] + 2.0;
    }
  }
  
  // get ending time
  get_walltime(&te);

  // check results
  for(i=0;i<NROWS*NCOLS;i++){
	if(table[i] != 3.0){
		printf("Error on the code\n");
	}
  }
  
  
  // print time elapsed and/or Maccesses/sec
  time = te-ts;
  aps=(2.0*NROWS*NCOLS)/(time*1e6);

  printf("Time : %lf\n",time);
  printf("Maccesses/sec : %lf\n",aps);
  fprintf(f,"%lf\t",time);
  fprintf(f,"%lf\n",aps);
  
  free(table);
  fclose(f);

  return 0;
}
