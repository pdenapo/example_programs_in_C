/* test.c */
#include <stdio.h>
#include <stdlib.h>
#include <linenoise.h>

int main(int argc, char *argv[]) {
  printf("Linenoise console\n");
  while (1)
  {
    char* line = linenoise (">");
	  if (!line)
     	break; 	
    printf("%s \n",line);
    free(line);  
  }
  return 0;
}