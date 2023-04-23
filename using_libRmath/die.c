/* Example using  the R Standalone Math Library

See

https://www.stat.berkeley.edu/~spector/s243/rmath.html

In Debian based systems, install the library using

apt-get install r-mathlib

*/

#include <stdio.h>
#define MATHLIB_STANDALONE 
#include <Rmath.h>
#include <sys/time.h>


int main(){
  
  /* We set a seet using the clock 
  to get different values every time the program is run*/
  struct timeval ts;
  gettimeofday(&ts, NULL); // return value can be ignored
  set_seed(ts.tv_sec,ts.tv_usec);

  /* How many times do you want to repeat the experiment?*/
  int times=10;
  
  int frequency[7];

  for (int k=0;k< times;k++)
  {
    /* simultate a uniform random variable*/
    double u= runif(0,1);
    int die= floor(u*6)+1;
    printf("%i \n",die);
    frequency[die]++;  
  }
  putchar('\n');
  for(int j=1;j<7;j++)
  {
    printf("%i \t %i \n",j,frequency[j]);
  };
  return 0;
}