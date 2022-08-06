readline.o: readline.c readline.h
	gcc -c readline.c

inv_operations.o: inv_operations.c readline.h inv_operations.h
	gcc -c inv_operations.c

inventory.o: inventory.c inv_operations.h
	gcc -c inventory.c

inventory: readline.o inv_operations.o inventory.o
	gcc -o inventory readline.o inv_operations.o inventory.o
