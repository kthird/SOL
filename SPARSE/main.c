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

	smatrix_t *A,*Bin;
	
	
	FILE *fA,*fBin;
	
	
	A=new_smat(4,3);
	
	printf("%s",((put_elem(A,0,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,0,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,1,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,0,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,2,2,1)==0)?"INSERITO \n":"ERRORE\n"));
	printf("%s",((put_elem(A,3,1,1)==0)?"INSERITO \n":"ERRORE\n"));
	
	
	
	fA=fopen("print/Ab.bin","wb");
	

	if(savebin_smat(fA,A)==0)
		printf("SALVATA IN BINARIO\n");
	else
		printf("NON SALVATA\n");
	
	fBin=fopen("print/Ab.bin","rb");
	
	if((Bin=loadbin_smat(fBin))!=NULL)
	{
		fA=fopen("print/A.txt","w");
		fBin=fopen("print/Bin.txt","w");
		print_smat(fA,A);
		print_smat(fBin,Bin);
		if(is_equal_smat(A,Bin)==TRUE)
			printf("UGUALI\n");
		else
			printf("DIVERSE\n");
		fclose(fA);
		fclose(fBin);
	}
	else
		printf("BIN VUOTA");
	
	
		
	free_smat(&A);
	free_smat(&Bin);
	
	return 0;
}
