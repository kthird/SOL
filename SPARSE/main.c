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

	smatrix_t *A,*B,*C,*P;
	
	
	FILE *fA,*fB,*fC,*fP;
	
	
	A=new_smat(4,3);
	B=new_smat(3,4);
	
	printf("%s",((put_elem(A,0,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,0,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,3,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	
	printf("%s",((put_elem(B,0,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,0,3,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,1,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(B,2,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	
	
	C=transp_smat(A);
	
	if(C!=NULL)
		printf("MATRICE TRASPOSTA \n");
	else
		printf("ERRORE DI TRASPOSIZIONE\n");
	
	fA=fopen("print/A.txt","w");
	fB=fopen("print/B.txt","w");
	fC=fopen("print/C.txt","w");
	
	fP=fopen("DATA/data1.txt","r");
	
	P=load_smat(fP);
	
	fP=fopen("print/P.txt","w");
	
	print_smat(fA,A);
	print_smat(fB,B);
	print_smat(fC,C);
	
	if(save_smat(fP,P)==0)
		printf("SALVATA\n");
	else
		printf("NON SALVATA\n");
	
	fclose(fA);
	fclose(fB);
	fclose(fC);
	
		
	free_smat(&A);
	free_smat(&B);
	free_smat(&C);
	free_smat(&P);
	
	return 0;
}
