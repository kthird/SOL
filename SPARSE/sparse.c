/**
  @file sparse.c
  @brief prototipi implementati
  @author Francesco Lorito 464604
*/

#include "sparse.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>



/** 
  crea una nuova matrice vuota
  \param n numero di righe
  \param m numero di colonne

  \retval NULL se si e' verificato un errore
  \retval p ppuntatore alla matrice appena allocata

*/
smatrix_t * new_smat ( unsigned n, unsigned m ) 
{
	if((n > 0) && (m>0))
	{
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
	else
		return NULL;
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
int put_elem_row(elem_t ** r,int j, double d)
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
				tmpElem->next=NULL;
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
		if((i >= m->nrow) || (i < 0))
			return -1;
		else
			if((j >= m->ncol) || (j < 0))
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
		if((i >= m->nrow) || (i < 0))
				return -1;
			else
				if((j >= m->ncol) || (j < 0))
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
			if((*pr)->next != NULL)
			{
				free_row(&((*pr)->next));
			}
			free(*pr);
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
smatrix_t* sum_smat (smatrix_t* a, smatrix_t* b)
{
	/* La somma fra matrici è possibile solo nel caso in cui abbiano lo stesso numero di righe e colonne */
	smatrix_t *c;
	int i,j;
	double da,db;
	bool_t errore;
	errore = FALSE;
	da=0;
	db=0;
	if(a!=NULL && b!=NULL)
	{
		if(a->nrow == b->nrow)
		{
			if(a->ncol == b->ncol)
			{
				c = new_smat(a->nrow,a->ncol);
				i=0;
				while(!errore && (i < a->nrow)) 
				{
					j=0;
					while(!errore && (j < a->ncol))
					{
						if(get_elem(a,i,j,&da) == 0)
						{
							if(get_elem(b,i,j,&db) == 0)
							{
								if(put_elem(c,i,j,(da + db)) == 0)
								{
									j++;
								}
								else
								{
									free_smat(&c);
									errore = TRUE;
								}
							}
							else
							{
								free_smat(&c);
								errore = TRUE;
							}
						}
						else
						{
							free_smat(&c);
							errore = TRUE;
						}
					}
					i++;
				}
				if(!errore)
					return c;
				else
				{
					free_smat(&c);
					return NULL;
				}
			}
			else 
				return NULL;
		}
		else
			return NULL;
	}
	else 
		return NULL;
}

/** 
    moltiplica due matrici
    (se il prodotto è zero ricordarsi di non inserire l'elemento corrispondente)
    \param a, b matrici da moltiplicare

    \retval c la matrice risultato (viene allocata dentro la funzione)
    \retval NULL se si è verificato un errore

*/
smatrix_t* prod_smat (smatrix_t* a, smatrix_t* b)
{
	/* Due matrici a e b possono essere moltiplicate tra loro solo se il numero di colonne di a è uguale al numero di righe di b */
	smatrix_t *c;
	int i,j,k;
	double da,db,somma;
	bool_t errore;
	errore = FALSE;
	da=0;
	db=0;
	somma=0;
	if(a!=NULL && b!=NULL)
	{
		if(a->ncol == b->nrow)
		{
			c = new_smat(a->nrow,b->ncol);
			i=0;
			while(!errore && (i < a->nrow))
			{
				j=0;
				while(!errore && (j < b->ncol))
				{
					k=0;
					while(!errore && (k < a->ncol))
					{
						if(get_elem(a,i,k,&da)==0)
						{
							if(get_elem(b,k,j,&db)==0)
							{
								somma = somma + (da*db);
							}
							else
							{
								free_smat(&c);
								errore = TRUE;
							}
						}
						else
						{
							free_smat(&c);
							errore = TRUE;
						}
						k++;
					}
					if(!errore)
					{
						if(put_elem(c,i,j,somma) != 0)
						{
							free_smat(&c);
							errore = TRUE;
						}
						else
						{
							somma=0;
							j++;
						}
					}
				}
				somma=0;
				i++;
				
			}
			if(errore)
			{
				free_smat(&c);
				return NULL;
			}
			else
				return c;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

/** 
    calcola la trasposta di una matrice
    (se un elemento è zero ricordarsi di non inserire)
    \param a matrice

    \retval c la matrice risultato (viene allocata dentro la funzione)
    \retval NULL se si è verificato un errore

*/
smatrix_t* transp_smat (smatrix_t* a)
{
	smatrix_t *c;
	int i,j;
	double da;
	bool_t errore;
	errore = FALSE;
	da=0;
	if(a!=NULL)
	{
		c=new_smat(a->ncol,a->nrow);
		if(c == NULL)
			return NULL;
		else
		{
			i=0;
			while(!errore && (i < a->nrow))
			{
				j=0;
				while(!errore && (j < a->ncol))
				{
					if(get_elem(a,i,j,&da) == 0)
					{
						if(put_elem(c,j,i,da) == 0)
						{
							j++;
						}
						else
						{
							free_smat(&c);
							errore = TRUE;
						}
					}
					else
					{
						free_smat(&c);
						errore = TRUE;
					}
				}
				i++;
			}
			if(!errore)
				return c;
			else
				return NULL; 
		}
	}
	else
		return NULL;
}

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
smatrix_t* load_smat (FILE* fd)
{
	smatrix_t * p;
	int ncol;
	int nrow;
	int i,j;
	double val;
	bool_t errore;
		
	errore = FALSE;
	
	ncol=0;
	nrow=0;
	i=0;
	j=0;
	val=0;
	
		
	if(fd != NULL)
	{	
		fscanf(fd,"%d", &nrow);
		fscanf(fd,"%d", &ncol);
		if(nrow <= 0 || ncol <= 0)
		{
			errno=EINVAL;
			return NULL;
		}
		p=new_smat(nrow,ncol);
		if(p == NULL)
		{
			errno=EINVAL;
			fclose(fd);
			return NULL;
		}
		else
			while(!errore && !feof(fd))
			{
				fscanf(fd,"%d",&i);
				fscanf(fd,"%d",&j);
				fscanf(fd,"%lf",&val);
				if(put_elem(p,i,j,val) != 0)
				{
					free_smat(&p);
					errno = EINVAL;
					errore = TRUE;
				}
			}
			if(errore)
			{
				return NULL;
			}
			else
			{
				return p;
			}
	}
	else
	{
		errno = EBADF;
		return NULL;
	}
	
} 

/** salva una matrice su file nel formato specificato per la funzione load_smat
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
*/
int save_smat (FILE* fd, smatrix_t* mat)
{
	int i,j;
	double val;
	bool_t errore;
		
	errore = FALSE;
	
	val=0;
	
		
	if(fd != NULL)
	{	
		if(mat!=NULL)
		{
			fprintf(fd,"%d\n", mat->nrow);
			fprintf(fd,"%d\n", mat->ncol);
			i=0;
			while(!errore && (i < mat->nrow))
			{
				j=0;
				while(!errore && (j < mat->ncol))
				{
					if(get_elem(mat,i,j,&val) == 0)
					{
						if(val!=0)
						{
							fprintf(fd,"%d ",i);
							fprintf(fd,"%d ",j);
							fprintf(fd,"%lf\n",val);
						}
					}
					else
					{
						errno = EINVAL;
						errore = TRUE;
					}
					j++;
				}
				i++;
			}
			if(errore)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			errno = EINVAL;
			return -1;
		}
				
	}
	else
	{
		errno = EBADF;
		return -1;
	}
}


/** 
    carica da file una matrice in formato binario (scelto dallo studente e documentato nei commenti)
        
		Il file binario si presenta come un'unica stringa di bit
			110010101110..............010101
		
		i primi sizeof(int) bit  indicano il numrow
		i secondi sizeof(int) bit  indicano il numcol
		i successivi bit indicano il contenuto della matrice esono disposti come segue:
			un blocco di sizeof(int) per l'indice di riga
			un blocco di sizeof(int) per l'indice di colonna
			e un blocco di sizeof(double) per il valore dell'elemento
		e così via per ogni elemento della matrice

    \param fd file da cui caricare la matrice (gia' aperto)

    \retval p puntatore alla nuove matrice caricata (allocata dentro la funzione)
    \retval NULL se si è verificato un errore (setta errno)

*/
smatrix_t* loadbin_smat (FILE* fd)
{
	smatrix_t * p;
	int ncol;
	int nrow;
	int i,j;
	double val;
	bool_t errore;
		
	errore = FALSE;
	
	ncol=0;
	nrow=0;
	i=0;
	j=0;
	val=0;
	
	if(fd != NULL)
	{	
		if(fread(&nrow, sizeof(int),1, fd) != 0)
	    {
	    	if(fread(&ncol, sizeof(int),1, fd) !=0)
	    	{
	    		p=new_smat(nrow,ncol);
				if(p == NULL)
				{
					fclose(fd);
					errno=ENOMEM;
					return NULL;
				}
				else
				{
					while(!errore && !feof(fd))
					{
						if(fread(&i, sizeof(int),1, fd) != 0)
						{
							if(fread(&j, sizeof(int),1, fd) !=0)
							{
								if(fread(&val, sizeof(double),1, fd) !=0)
								{
									if(put_elem(p,i,j,val) != 0)
									{
										free_smat(&p);
										errno = EINVAL;
										errore = TRUE;
									}
								}
								else
								{
									free_smat(&p);
									errno = EINVAL;
									errore = TRUE;
								}
							}
							else
							{
								free_smat(&p);
								errno = EINVAL;
								errore = TRUE;
							}
						}
					}
					if(errore)
					{
						return NULL;
					}
					else
					{
						return p;
					}
				}
			}
			else
			{
				errno=EINVAL;
				return NULL;
			}
		}
		else
		{
			errno=EINVAL;
			return NULL;
		}
		
		
	}
	else
	{
		errno = EBADF;
		return NULL;
	}
	
	
}

/** salva una matrice su file in formato binario (scelto dallo studente e documentato nei commenti)
  	[stesso formato documentato in loadbin_smat]
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
 */
 
int savebin_smat (FILE* fd, smatrix_t* mat)
{
	int i,j;
	double val;
	bool_t errore;
		
	errore = FALSE;
	
	val=0;
	
		
	if(fd != NULL)
	{	
		if(mat!=NULL)
		{
			 if(fwrite(&(mat->nrow), sizeof(int),1, fd) != 0)
			 {
			 	if(fwrite(&(mat->ncol), sizeof(int),1, fd) !=0)
			 	{
			 	    i=0;
					while(!errore && (i < mat->nrow))
					{
						j=0;
						while(!errore && (j < mat->ncol))
						{
							if(get_elem(mat,i,j,&val) == 0)
							{
								if(val!=0)
								{
									fwrite(&i,sizeof(int),1,fd);
									fwrite(&j,sizeof(int),1,fd);
									fwrite(&val,sizeof(double),1,fd);
								}
							}
							else
							{
								errno = EINVAL;
								errore = TRUE;
							}
							j++;
						}
						i++;
					}
					if(errore)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					errno = EINVAL;
					return -1;
				}
			}
			else
			{
				errno = EINVAL;
				return -1;
			}
		}
		else
		{
			errno = EINVAL;
			return -1;
		}
				
	}
	else
	{
		errno = EBADF;
		return -1;
	}
}
