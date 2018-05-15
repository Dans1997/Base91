IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./obj
LDIR= ../lib

_DEPS=
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=caminho_inverso.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main

main:	$(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
