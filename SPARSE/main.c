/**
  \brief header file primo frammento
  \author Francesco Lorito 464604
*/

#include "sparse.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>

int main()
{

	smatrix_t *A,*B,*C;
	
	
	FILE *fA,*fB,*fC;
	
	
	A=new_smat(3,3);
	B=new_smat(3,4);
	
	printf("%s",((put_elem(A,0,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	
	printf("%s",((put_elem(B,0,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,0,3,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,2,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	
	
	C=prod_smat(A,B);
	
	if(C!=NULL)
		printf("PRODOTTO EFFETTUATO\n");
	else
		printf("ERRORE DURANTE IL PRODOTTO\n");
	
	fA=fopen("print/A.txt","w");
	fB=fopen("print/B.txt","w");
	fC=fopen("print/C.txt","w");
	
	
	print_smat(fA,A);
	print_smat(fB,B);
	print_smat(fC,C);
	
	fclose(fA);
	fclose(fB);
	fclose(fC);
	
		
	free_smat(&A);
	free_smat(&B);
	free_smat(&C);
	
	
	return 0;
}
