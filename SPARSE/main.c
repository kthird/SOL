/**
  \brief header file primo frammento
  \author Francesco Lorito 464604
*/

#include "sparse.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	smatrix_t *A,*B;
	
	FILE *fA,*fB;
	
	A=new_smat(3,3);
	B=new_smat(3,3);
	
	printf("%s",((put_elem(A,0,0,25)==0)?"INSERITO 25\n":"ERRORE\n"));
	printf("%s",((put_elem(A,0,1,42)==0)?"INSERITO 42\n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,0,1)==0)?"INSERITO 1\n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,2,30)==0)?"INSERITO 30\n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,1,59.61)==0)?"INSERITO 59.61\n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,0,0)==0)?"INSERITO 0\n":"ERRORE\n"));
	
	printf("%s",((put_elem(B,0,0,25)==0)?"INSERITO 25\n":"ERRORE\n"));
	printf("%s",((put_elem(B,0,1,42)==0)?"INSERITO 42\n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,0,1)==0)?"INSERITO 1\n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,2,30)==0)?"INSERITO 30\n":"ERRORE\n"));
	printf("%s",((put_elem(B,2,1,59.61)==0)?"INSERITO 59.61\n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,0,451)==0)?"INSERITO 451\n":"ERRORE\n"));
	
	
	fA=fopen("print/A.txt","w");
	fB=fopen("print/B.txt","w");
	
	print_smat(fA,A);
	print_smat(fB,B);
	
	fclose(fA);
	fclose(fB);
	
	if(is_equal_smat(A,B)==TRUE)
		printf("UGUALI\n");
	else
		printf("DIVERSE\n");
	
	
	
	
	
	return 0;
}
