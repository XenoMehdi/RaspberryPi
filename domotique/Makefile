# définition des variables
CC = gcc
EXEC = iHome
OBJ = *.o
LIBS = -lpthread -lwiringPi -lwiringPiDev
CFLAGS =

# all conditionnel
all : $(OBJ)
        $(CC) $^ -o $(EXEC) $(LIBS)

%.o: %.c
        $(CC) -c $< -o $@ $(CFLAGS)
        
# clean
clean:
        rm -rf *.o
