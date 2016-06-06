#PROGETTO SOL 2015/2016
Realizzazione di due frammenti

#SPARSE 
=========
  
Il progetto prevede la realizzazione di un insieme di funzioni C che
lavorano su matrici sparse di double. Si intendono "sparse" la matrici che
contengo una bassissima percentuale di elementi diversi da 0. Queste
matrici vengono solitamente rappresentate registrando solo gli
elementi diversi da 0 e la loro posizione. 
Nel nostro caso utilizzeremo un array di puntatori a righe che
contiene NULL se la riga contiene tutti valori uguali a zero o la
lista delle colonne e dei valori diversi da zero.

Ad esempio la matrice

3.1  0   0   0
 0   0   0   0
 0  7.2  0  9.0

è rappresentata come
   
0 | ------>([0,3.1] , NULL)
1 | NULL
2 | ------>([1,7.2] , --)-->( [3,9.0] ,NULL)

Le strutture dati da utilizzare per la realizzazione delle matrici sparse   
e i prototipi delle funzioni da implementare sono definiti nel file
sparse.h.
Consigliamo di leggere accuratamente sparse.h prima di proseguire.
 
 
L'implementazione della funzione di stampa e' fornita nel file
sparse_docenti.c.
  
Le funzioni definite in sparse.h possono essere implementate in un
unico file "sparse.c".  Se si vogliono usare piu' file si deve
modificare il Makefile in modo che la compilazione avvenga
automaticamente in modo corretto e tutti i file sviluppati vengano
consegnati nel tar finale.

I commenti in sparse.h spiegano in dettaglio il comportamento delle
varie funzioni, il significato dei parametri ed i valori restituiti
secondo il formato Doxygen (chi e' interessato puo' leggere
README.doxygen per i dettagli).
  
Conviene testare le funzioni man mano che vengono sviluppate con dei  
main() di test evitando di scrivere tutto il codice prima di testarne  
il funzionamento.    
Questo permette di localizzare molto meglio errori ed anomalie.  
Solo quando siamo ragionevolmente convinti della correttezza del  
codice si puo' passare al testing automatico del codice con i test  
forniti dai docenti.   

#MEMBOX
=========

Lo scopo del progetto è lo sviluppo di un server concorrente che implementa uno spazio
di memorizzazione di oggetti (repository). Un oggetto è una sequenza continua di bytes
di dimensione non nulla ed avente una size massima stabilita nel file di configurazione
del server memBox con l’opzione MaxObjSize (vedi Sez. 2.2). L’oggetto è identificato
univocamente da una chiave numerica (codificata su un intero a 32 bits). Ogni richiesta
inviata al server deve contenere la chiave dell’oggetto a cui la richiesta si riferisce.
Uno o più processi client comunicano con il server per inviare richieste di vario
tipo. In particolare le richieste possono essere: di inserimento (PUT OP), di ag-
giornamento di un oggetto già inserito (UPDATE OP), di rimozione di un oggetto
presente nel repository (REMOVE OP), di recupero (GET OP) del contenuto di un
oggetto, di acquisizione della lock (LOCK OP) sull’intero repository e rilascio della
stessa (UNLOCK OP). È possibile effettuare un’operazione PUT OP solo per chiavi
non presenti nel repository. È possibile effettuare un’operazione UPDATE OP solo se
la size dell’oggetto inviato nella richiesta coincide con la size dell’oggetto memorizzato
nel server.
3Ad esempio, una richesta di recupero di un oggetto con chiave 100 sarà codificata
inviando un messaggio di richiesta al server contenente le informazioni <100, GET OP>
opportunamente formattate. Il server risponderà con un messaggio il cui header con-
terrà l’esito dell’operazione (e.s OP OK, OP FAIL, ....), mentre il payload conterrà i
bytes dell’oggetto con chiave 100. Se l’oggetto non è presente nel repository (ad esem-
pio perché è stato rimosso da un altro processo), verrà ritornato al client un messaggio
di errore opportunamente codificato. Per questo esempio, il messaggio di errore è, ad
esempio, OP GET NONE. Per i possibili codici dei messaggi di risposta inviati dal server
al client, vedere il file ops.h nel tarball del kit fornito dai docenti.
La comunicazione avviene tramite socket di tipo AF UNIX. Il path da utilizzare
per la creazione del socket AF UNIX deve essere specificato nel file di configurazione
utilizzando l’opzione UnixPath. Per rendere più agevole lo sviluppo ed il testing dell’ap-
plicazione sulle macchine del centro di calcolo per la didattica, le socket create dallo
studente con numero di matricola matricola potranno avere un nome che rispetta il
seguente formato: membox_sock_matricola. L’obiettivo è minimizzare possibili inter-
azioni indesiderate fra progetti sviluppati da utenti diversi sulla stessa macchina del
laboratorio.
Le operazioni di lock/unlock si intendono sull’intero repository e non sul singolo
oggetto. Se il server ha ricevuto un messaggio di tipo LOCK OP da un client a
cui è associata la connessione n, allora il server dovrà servire solamente le richieste
provenienti dalla connessione n (cioè dal client che mantiene la lock). Se il client chiude
la connessione, la lock sull’intero repository dovrà essere rilasciata anche se non è stata
inviata una esplicita operazione di UNLOCK OP.
Il server può contenere un numero massimo di oggetti pari a StorageSize e non
dovrà occupare una size complessiva per gli oggetti maggiore di StorageByteSize (se
StorageSize e/o StorageByteSize valgono 0 vuol dire che non c’è nessun limite sul
numero massimo di oggetti/dimensione dello storage). Oltre tali valori di soglia, il
server non dovrà più accettare richieste di inserimento di nuovi oggetti, mentre dovrà
continuare ad accettare altri tipi di richieste (rimozione, aggiornamento, recupero,
lock/unlock). Nello sviluppo del codice del server si dovrà tenere in considerazione
che:
• il server deve essere in grado di poter memorizzare decine di migliaia di oggetti
• il server deve essere in grado di gestire efficientemente alcune decina di connes-
sioni contemporanee.
Il server al suo interno implementa un sistema multi-threaded che è in grado
di gestire contemporaneamente sia nuove connessioni dai client che gestire le richi-
esti su connessioni già stabilite. Un cliente può sia inviare una richiesta per singola
connessione oppure, per una data connessione, inviare più richieste (sia sullo stesso
oggetto che su oggetti diversi). Il numero massimo di connessioni concorrenti che
il server memBox gestisce è stabilito dall’opzione di configurazione MaxConnections.
Se tale numero viene superato, dovrà essere ritornato al client un opportuno mes-
saggio di errore. Ogni connessione viene gestita interamente da un solo thread. Il
numero di thread utilizzati per gestire le connessioni è specificato nel file di configu-
razione con l’opzioni ThreadsInPool. Tale numero (che non può essere 0), specifica
la dimensione di un pool di threads che rimangono sempre attivi per tutta la durata
dell’esecuzione del server. Il server utilizza i thread del pool per gestire le connessioni
dei client. Qualora tutti i thread del pool risultino occupati, possono essere accodate
fino a M axConnections − T hreadsInP ool connessioni in attesa che il pool ne serva
le richieste. Un thread appartenente al pool, non appena conclude la gestione di una
connessione (la socket è stata chiusa), controlla se ci sono connessioni pendenti in coda
ed in caso affermativo ne preleva una da gestire. Se non ci sono connessioni in coda, il
thread “rientra” nel pool di thread disponibili in attesa di essere svegliato per gestire
una nuova connessione.

