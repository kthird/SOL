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
	
	A->mat=malloc(3*sizeof(elem_t*));
	
	A->mat[0]=malloc(sizeof(elem_t*));
	A->mat[0]->col=0;
	A->mat[0]->val=35;
	A->mat[0]->next=malloc(sizeof(elem_t*));
	A->mat[0]->next->col=2;
	A->mat[0]->next->val=41.9;
	A->mat[0]->next->next=NULL;
	A->mat[2]=malloc(sizeof(elem_t*));
	A->mat[2]->col=1;
	A->mat[2]->val=23;
	A->mat[2]->next=NULL;
	
	B->mat=malloc(3*sizeof(elem_t*));
	
	B->mat[0]=malloc(sizeof(elem_t*));
	B->mat[0]->col=0;
	B->mat[0]->val=35;
	B->mat[0]->next=malloc(sizeof(elem_t*));
	B->mat[0]->next->col=2;
	B->mat[0]->next->val=41.9;
	B->mat[0]->next->next=NULL;
	B->mat[2]=malloc(sizeof(elem_t*));
	B->mat[2]->col=1;
	B->mat[2]->val=23;
	B->mat[2]->next=NULL;
	
	
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
