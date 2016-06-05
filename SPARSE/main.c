/**
  \brief header file primo frammento
  \author Francesco Lorito 464604
*/

#include "sparse.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>


#define FDATA1 "data1.txt"
#define FDATA2 "data2.txt"
#define FDATA3 "data3.txt"
#define FDATA4 "data4.txt"
#define FOUT1 "data_out1.txt"
#define FOUT2 "data_out2.txt"
#define FOUT3 "data_out3.bin"

int main (void) {
  FILE * fd1, * fd2;
  smatrix_t *a, *b;

  /* salvataggio formato testo corretto */
  if ( (fd1 = fopen(FDATA1,"r") ) == NULL ) {
    fprintf(stderr,"fopen:");
    perror(FDATA1);
    return (EXIT_FAILURE);
  }

  if ( ( a = load_smat(fd1) ) == NULL ) {
    fprintf(stderr,"load smat:");
    perror(FDATA1);
    return (EXIT_FAILURE);
  }

  fclose(fd1);

  print_smat(stdout,a);


   if ( (fd2 = fopen(FOUT1,"w") ) == NULL ) {
    fprintf(stderr,"fopen:");
    perror(FOUT1);
    return (EXIT_FAILURE);
  }

   if ( save_smat(fd2,a)  == -1 ) {
    fprintf(stderr,"save smat:");
    perror(FOUT1);
    return (EXIT_FAILURE);
  }

  fclose(fd2);

  /* ricarichiamo la matrice */
  if ( (fd1 = fopen(FOUT1,"r") ) == NULL ) {
    fprintf(stderr,"fopen:");
    perror(FOUT1);
    return (EXIT_FAILURE);
  }

 if ( ( b = load_smat(fd1) ) == NULL ) {
    fprintf(stderr,"load smat:");
    perror(FOUT1);
    return (EXIT_FAILURE);
  }

  fclose(fd1);

  print_smat(stdout,b);

  if ( ! is_equal_smat ( a, b ) ) {
    fprintf(stderr,"load smat:");
    perror("is_equal_smat");
    return (EXIT_FAILURE);
  }
	
  printf("PROVO A LIBERARE LE MATRICI\n");
  free_smat(&a);
  free_smat(&b);
  if(a!=NULL || b!=NULL)
  	printf("MATRICI NON LIBERATE");
  else
  	printf("MAATRICI LIBERATE");
	return 0;
}
