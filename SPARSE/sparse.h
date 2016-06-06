/**
  @file sparse.h
  @brief header file contenente i prototipi da implementare
  @author Francesco Lorito 464604
*/

#ifndef __SPARSE_H
#define __SPARSE_H
#include <stdio.h>

/** valori booleani */
typedef enum bool {FALSE=0, TRUE=1} bool_t;

/**
Le matrici sparse di valori double sono rappresentate da un array di liste ciascuna
delle quali rappresenta una riga. In ogni lista sono contenuti solo
gli elementi non uguali a zero con il numero di colonna
corrispondente.

Ad esempio la matrice

3.1  0   0   0
 0   0   0   0
 0  7.2  0  9.0

è rappresentata come
   
0 | ------>([0,3.1] , NULL)
1 | NULL
2 | ------>([1,7.2] , --)-->( [3,9.0] ,NULL)

*/


/** elemento della matrice sparsa */
typedef struct elem {
  /** indice di colonna */
  unsigned col;
  /** valore dell'elemento */ 
  double val;
  /** puntatore al prossimo elemento nella riga */
  struct elem * next;
} elem_t;


/** rappresentazione della matrice sparsa */
typedef struct {
  /** puntatore all'array delle righe */
  elem_t ** mat;
  /** numero di righe */
  int nrow;
  /** numero di colonne */
  int ncol;
} smatrix_t;
  
/** 
  stampa la matrice in forma canonica (FORNITA DAI DOCENTI)

  \param l putatore alla matrice da stampare
  \param f puntatore al file su cui scrivere

*/
void print_smat (FILE * f, smatrix_t * l);

/** 
  crea una nuova matrice vuota
  \param n numero di righe
  \param m numero di colonne

  \retval NULL se si e' verificato un errore
  \retval p ppuntatore alla matrice appena allocata

*/
smatrix_t * new_smat ( unsigned n, unsigned m ) ;

/**
   Controlla se due matrici sono uguali, elemento per elemento

   \param a puntatore alla prima matrice da confrontare
   \param b puntatore alla seconda matrice da confrontare

   \retval TRUE se sono uguali
   \retval FALSE altrimenti
 */
bool_t is_equal_smat ( smatrix_t * a , smatrix_t * b );

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
int put_elem_row(elem_t ** r,int j, double d);

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
int put_elem ( smatrix_t * m , unsigned i, unsigned j, double d );


/**
   legge il valore dell'elemento nella colonna j

   \param r puntatore alla riga da leggere
   \param j colonna dell'elemento
   \param pd puntatore della variabile in cui scrivere il valore dell'elemento

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int get_elem_row ( elem_t * r,int j, double* pd );

/**
   legge il valore nell'elemento i,j

   \param m puntatore alla matrice
   \param (i,j) posizione dell'elemento
   \param pd puntatore della variabile in cui scrivere il valore dell'elemento

   \retval -1 se si e' verificato un errore 
   \retval 0 altrimenti
 */
int get_elem ( smatrix_t * m , unsigned i, unsigned j, double* pd );

/**
  dealloca tutta la riga di una matrice

  \param pr puntatore al putatore della riga da deallocare
            (*pr viene messo a NULL dalla funzione)

 */
void free_row (elem_t ** pr);

/**
  dealloca tutta la matrice

  \param pm puntatore al putatore della matrice da deallocare
            (*pm viene messo a NULL dalla funzione)

 */
void free_smat (smatrix_t ** pm);

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

/** salva una matrice su file nel formato specificato per la funzione load_smat
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
 */
int save_smat (FILE* fd, smatrix_t* mat);
 

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
smatrix_t* loadbin_smat (FILE* fd); 


/** salva una matrice su file in formato binario (scelto dallo studente e documentato nei commenti)
  	[stesso formato documentato in loadbin_smat]
  
   \param fd file su cui scrivere la matrice (gia' aperto)
   \param mat la matrice da scrivere su file

   \retval 0 se tutto e' andato bene
   \retval -1 se si è verificato un errore (setta errno)
 */
 
int savebin_smat (FILE* fd, smatrix_t* mat); 
#endif
  

