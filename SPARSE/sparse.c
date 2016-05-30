/**
  \brief header file primo frammento
  \author Francesco Lorito 464604
*/

#include "sparse.h"
#include <errno.h>
#include <stdlib.h>
/** 
  stampa la matrice in forma canonica (FORNITA DAI DOCENTI)

  \param l putatore alla matrice da stampare
  \param f puntatore al file su cui scrivere

*/
static void print_elem_r(FILE * f, elem_t* p)  {
  if ( p == NULL ) return ;
  fprintf(f, "<%d,%f>",p->col,p->val);
  print_elem_r(f,p->next);
  return;
}
void print_smat (FILE * f, smatrix_t * a) { 
  int i;
  
 if ( f == NULL || a == NULL )
    return ;

  
  for (i=0; i< a->nrow ; i++) {
	  if(a->mat[i]!=NULL) {
		  fprintf(f,"%d: ",i);
		  print_elem_r(f,a->mat[i]);
          fprintf(f,"\n");}
  } 
  fprintf(f,"\n");
} 

/** 
  crea una nuova matrice vuota
  \param n numero di righe
  \param m numero di colonne

  \retval NULL se si e' verificato un errore
  \retval p ppuntatore alla matrice appena allocata

*/
smatrix_t * new_smat ( unsigned n, unsigned m ) {
	smatrix_t * p;
	int i;
	p=(smatrix_t*) malloc(sizeof(smatrix_t));
	if(p==NULL)
		errno=ENOMEM;
	else
	{
		p->nrow=n;
		p->ncol=m;
		p->mat=(elem_t**) malloc(n*sizeof(elem_t*));
		for(i=0;i<n;i++)
		{
			p->mat[i]=NULL;
		}
	}
	return p;
}

/**
   Controlla se due matrici sono uguali, elemento per elemento

   \param a puntatore alla prima matrice da confrontare
   \param b puntatore alla seconda matrice da confrontare

   \retval TRUE se sono uguali
   \retval FALSE altrimenti
 */
bool_t is_equal_smat ( smatrix_t * a , smatrix_t * b ){
	/* due matrici sono uguali se sono vuote entrambe o se hanno lo stesso numero di righe/colonne e gli stessi identici elementi */
	elem_t *tmpA, *tmpB;
	bool_t uguale; 
	int i;
	uguale = TRUE;
	if(a!=NULL)
	{
		if(b!=NULL)
		{
			if(a->nrow!=b->nrow)
				uguale = FALSE;
			else
				if(a->ncol!=b->ncol)
					uguale = FALSE;
				else
				{
					i=0;
					while((uguale == TRUE) && (i<(a->nrow)))
					{
						tmpA=a->mat[i];
						tmpB=b->mat[i];
						
						while((uguale==TRUE) && (tmpA!=NULL))
						{
							if(tmpB!=NULL)
							{
								if((a->mat[i]->val == b->mat[i]->val) && (a->mat[i]->col == b->mat[i]->col))
								{
									tmpA=tmpA->next;
									tmpB=tmpB->next;
								}
								else
								{
									uguale = FALSE;
								}
							}
							else
								uguale = FALSE;
						}
						if(tmpA==NULL)
						{
						/* Se B ha ancora elementi nella riga allora A e B sono diverse altrimenti controllo la riga successiva */
							if(tmpB!=NULL)
								uguale = FALSE;
							else
								i++;
						}
					}
				}
		}	
	}
	else
		if(b!=NULL)
			uguale = FALSE;
	return uguale;
}


/**
   inserisce un elemento in r passata con indice colonna j, per mantenere la
   rappresentazione consistente se il valore scritto è 0 l'elemento
   corrispondente deve essere eliminato dalla lista che rappresenta la riga

   \param r puntatore alla riga
   \param j colonna dell'elemento
   \param d valore dell'elemento da scrivere

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int put_elem_row(elem_t ** r,int j, int d)
{
	elem_t * tmpElem;
	if(*r!=NULL)
	{
		if(j < (*r)->col)
		{
			if(d!=0)
			{
				tmpElem=(elem_t*) malloc(sizeof(elem_t));
				if(tmpElem==NULL)
					return -1;
				else
				{
					tmpElem->col=j;
					tmpElem->val=d;
					tmpElem->next=*r;
					(*r)=tmpElem;
					free(tmpElem);
					return 0;
				}
			}
			else
				return 0;
		}
		else
			if(j == (*r)->col)
			{
				if(d!=0)
				{
					(*r)->val=d;
					return 0;
				}
				else
				{
					tmpElem=*r;
					*r=(*r)->next;
					free(tmpElem);
					return 0;
				}
			}
			else
			{
				return 0 + put_elem_row(&((*r)->next),j,d);
			}
	}
	else
	{
		if(d!=0)
		{
			tmpElem=(elem_t*) malloc(sizeof(elem_t));
			if(tmpElem==NULL)
				return -1;
			else
			{
				tmpElem->col=j;
				tmpElem->val=d;
				tmpElem->next=*r;
				(*r)=tmpElem;
				return 0;
			}
		}
		else
			return 0;
	}

}
/**
   scrive un valore nell'elemento i,j, per mantenere la
   rappresentazione consistente se il valore scritto è 0 l'elemento
   corrispondente deve essere eliminato dalla lista che rappresenta la riga

   \param m puntatore alla matrice
   \param (i,j) posizione dell'elemento
   \param d valore dell'elemento da scrivere

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int put_elem ( smatrix_t * m , unsigned i, unsigned j, double d )
{
	if(m!=NULL)
	{
		if(i >= m->nrow)
			return -1;
		else
			if(j >= m->ncol)
				return -1;
			else
			{
				if(m->mat[i]==NULL)
				{
					if(d!=0)
					{
						m->mat[i]=(elem_t*) malloc(sizeof(elem_t));
						if(m->mat[i]==NULL)
							return -1;
						else
						{
								m->mat[i]->col=j;
								m->mat[i]->val=d;
								m->mat[i]->next=NULL;
								return 0;
						}
					}
					else
						return 0;

				}
				else
				{
					return put_elem_row(&(m->mat[i]),j,d);	
				}
			}
	}
	else 
		return -1;
}


/**
   legge il valore dell'elemento nella colonna j

   \param r puntatore alla riga da leggere
   \param j colonna dell'elemento
   \param pd puntatore della variabile in cui scrivere il valore dell'elemento

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int get_elem_row ( elem_t * r,int j, double* pd )
{
	/* Se trovo NULL senza che si sia verificato un errore, vuol dire che l'elemento letto è uno ZERO */
	if(r!=NULL)
	{
		if(j < r->col)
		{
			*pd=0;
			return 0;
		}
		else
			if(j == r->col)
			{
				*pd=r->val;
				return 0;
			}
			else
				return 0 + get_elem_row(r->next,j,pd);
	}
	else
	{
		*pd=0;
		return 0;
	} 
}
	

/**
   legge il valore nell'elemento i,j

   \param m puntatore alla matrice
   \param (i,j) posizione dell'elemento
   \param pd puntatore della variabile in cui scrivere il valore dell'elemento

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int get_elem ( smatrix_t * m , unsigned i, unsigned j, double* pd )
{
	/* Se la riga è NULL vuol dire che ha tutti ZERI */
	if(m!=NULL)
	{
		if(i >= m->nrow)
				return -1;
			else
				if(j >= m->ncol)
					return -1;
				else
				{
					if(m->mat[i]==NULL)
					{
						*pd=0;
						return 0;
					}
					else
					{
						return get_elem_row(m->mat[i],j,pd);	
					}
				}
	}
	else
	{
		return -1;
	}
}

/**
  dealloca tutta la riga di una matrice

  \param pr puntatore al putatore della riga da deallocare
            (*pr viene messo a NULL dalla funzione)

 */
void free_row (elem_t ** pr)
{
	if(pr!=NULL)
	{
		if(*pr!=NULL)
		{
			if((*pr)->next == NULL)
			{
				free(*pr);
			}
			else
			{
				free_row(&((*pr)->next));
				free(*pr);
			}
			*pr = NULL;
		}
	}
}

/**
  dealloca tutta la matrice

  \param pm puntatore al putatore della matrice da deallocare
            (*pm viene messo a NULL dalla funzione)

 */
void free_smat (smatrix_t ** pm)
{
	int i;
	if(pm!=NULL)
	{
		if(*pm!=NULL)
		{
			for(i=0;i<((*pm)->nrow);i++)
			{
				free_row(&((*pm)->mat[i]));
				free((*pm)->mat[i]);
			}
			free((*pm)->mat);
			free(*pm);
			*pm = NULL;
		}
	}
}

/** 
    somma due matrici
    (se la somma è zero ricordarsi di non inserire l'elemento corrispondente)
    \param a, b matrici da sommare

    \retval c la matrice risultato (viene allocata dentro la funzione)
    \retval NULL se si è verificato un errore

*/
smatrix_t* sum_smat (smatrix_t* a, smatrix_t* b); 

/** 
    moltiplica due matrici
    (se il prodotto è zero ricordarsi di non inserire l'elemento corrispondente)
    \param a, b matrici da moltiplicare

    \retval c la matrice risultato (viene allocata dentro la funzione)
    \retval NULL se si è verificato un errore

*/
smatrix_t* prod_smat (smatrix_t* a, smatrix_t* b); 

/** 
    calcola la trasposta di una matrice
    (se un elemento è zero ricordarsi di non inserire)
    \param a matrice

    \retval c la matrice risultato (viene allocata dentro la funzione)
    \retval NULL se si è verificato un errore

*/
smatrix_t* transp_smat (smatrix_t* a); 

/** 
    carica da file una matrice nel formato
    nrighe1
    ncolonne1
    riga1 colonna1 valore1
    ...
    rigaN colonnaN valoreN
    
    Ad esempio la matrice

    3.1  0   0   0
     0   0   0   0
     0  7.2  0  9.0

    è rappresentata come
    3
    3
    0 0 3.1
    2 1 7.2
    2 2 9.0

    \param fd file da cui caricare la matrice (gia' aperto)

    \retval p puntatore alla nuove matrice caricata (allocata dentro la funzione)
    \retval NULL se si è verificato un errore (setta errno)

*/
smatrix_t* load_smat (FILE* fd); 

/* salva una matrice su file nel formato specificato per la funzione load_smat
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
 */
int save_smat (FILE* fd, smatrix_t* mat);
 
/** 
    carica da file una matrice in formato binario (scelto dallo studente e documentato nei commenti)

    \param fd file da cui caricare la matrice (gia' aperto)

    \retval p puntatore alla nuove matrice caricata (allocata dentro la funzione)
    \retval NULL se si è verificato un errore (setta errno)

*/
smatrix_t* loadbin_smat (FILE* fd); 

/** salva una matrice su file in formato binario (scelto dallo studente e documentato nei commenti)
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
 */
int savebin_smat (FILE* fd, smatrix_t* mat);  


