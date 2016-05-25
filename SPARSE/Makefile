################################
#
#     Makefile FRAMMENTO 1 2015/16
#    
################################

# inserire i nomi di tutti i file da consegnare
# se si usa piu' di un file modificare adeguatamente il makefile

FILE_DA_CONSEGNARE=sparse.c

# preferenze compilatore e flag di compilazione
CC=gcc
CFLAGS= -Wall -pedantic -g

# DA COMPLETARE se si usano piu' file
objects= sparse.o sparse_docenti.o

# phony targets
.PHONY: cleanall test1 test2 test3 test4 consegna

smatrix1 : test_one.o $(objects)
	$(CC) $(objects) test_one.o -o smatrix1

smatrix2 : test_two.o $(objects)
	$(CC) $(objects) test_two.o -o smatrix2

smatrix3 : test_three.o $(objects)
	$(CC) $(objects) test_three.o -o smatrix3

smatrix4 : test_four.o $(objects)
	$(CC) $(objects) test_four.o -o smatrix4

sparse_docenti.o: sparse_docenti.c sparse.h
test_one.o: test_one.c sparse.h
test_two.o: test_two.c sparse.h
test_three.o: test_three.c sparse.h
test_four.o: test_four.c sparse.h

# DA COMPLETARE inserire qua i target per eventuali file aggiuntivi
# (anche eventuali test aggiuntivi definiti dallo studente) 

sparse.o: sparse.c sparse.h



############################ fine parte studente


cleanall: 
	-rm -f *.o *~ ./core ./smatrix*


test1: 
	make cleanall
	-rm out_test_one*
	cp DATA/out_test_one.check .
	chmod 644 out_test_one.check
	make smatrix1
	./smatrix1 > out_test_one.txt
	diff out_test_one.txt out_test_one.check
	@echo "********** Test1 superato!"

test2: 
	make cleanall
	-rm out_test_two*
	cp DATA/out_test_two.check .
	chmod 644 out_test_two.check
	make smatrix2 
	./smatrix2 > out_test_two.txt
	diff out_test_two.txt out_test_two.check
	@echo "********** Test2 superato!"

test3: 
	make cleanall
	-rm out_test_three*
	cp DATA/out_test_three.check .
	chmod 644 out_test_three.check
	make smatrix3
	./smatrix3  > out_test_three.txt
	diff out_test_three.txt out_test_three.check
	@echo "********** Test3 superato!"

test4: 
	make cleanall
	-rm data?.txt data_out1.txt
	cp DATA/data?.txt .
	chmod 644 data?.txt
	make smatrix4
	./smatrix4  
	@echo "********** Test4 superato!"


consegna:
	make cleanall
	make test1
	make test2
	make test3
	make test4
	./gruppo-check.pl < gruppo.txt
	tar -cvf $(USER)-f1.tar ./gruppo.txt  $(FILE_DA_CONSEGNARE) 
	@echo "********** TAR creato inviare in allegato a una mail a <lso.di@listgateway.unipi.it> insieme a nome, cognome,  numero di matricola e corso di apprtenenza (A/B)"
