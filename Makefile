## Author: Steffen Viken Valvaag <steffenv@cs.uit.no> 

CFLAGS = -g -Wall -Wextra

SOURCE = main.c tree.c common.c plot.c
HEADER = tree.h common.h plot.h

app: app_linux

app_linux: $(SOURCE) $(HEADER)
	gcc $(CFLAGS) -o app -Iinclude $(SOURCE)

clean:
	rm -f *~ *.o *./app


valgrind:
	valgrind --leak-check=full ./app

gdb:
	gdb -ex=r --args ./app