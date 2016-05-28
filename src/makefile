IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -Wall

ODIR = ../obj

_DEPS = indexes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o indexes.o modify.o txt.o merge.o heapsort.o heap_nrr.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

indexes: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~