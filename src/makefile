IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -Wall

ODIR = ../obj

_DEPS = indices.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = indices.o insercao.o txt.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

indices: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~