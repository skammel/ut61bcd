TRG = ut61bcd
CC = gcc
LD = gcc
CFLAGS = -W -Wall 
LD_FLAGS = -O2 
OBJ = $(TRG).o ut61bcd_ser.o
all: $(TRG)

$(TRG): obj
	$(LD) $(LD_FLAGS) -o $(TRG) $(OBJ)

obj: $(TRG).c ut61bcd_ser.c
	$(CC) $(CFLAGS) -c ut61bcd.c ut61bcd_ser.c

clean:
	rm -f *~ *.o jj.jj $(TRG)
