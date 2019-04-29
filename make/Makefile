SRC = ./../src/
OBJ = ./../obj/
BIN = ./../bin/
INC = ./../include/
LOG = ./../log/log.txt
GFLAGS = gcc
CFLAGS = -c -g -Wall
OFLAGS = -o
IFLAG = -I./../include/
VFLAGS = --tool=memcheck --leak-check=yes --show-reachable=yes
LOGFLAG = --log-file=$(LOG)

all: $(OBJ)linked_list_driver.o $(OBJ)linked_list_utils.o
	$(GFLAGS) $(OFLAGS)output $(OBJ)linked_list_driver.o $(OBJ)linked_list_utils.o
	mv output $(BIN)
$(OBJ)linked_list_utils.o: $(SRC)linked_list_utils.c $(INC)linked_list_utils.h
	$(GFLAGS) $(CFLAGS) $(IFLAG) $(SRC)linked_list_utils.c
	mv linked_list_utils.o $(OBJ)
$(OBJ)linked_list_driver.o: $(SRC)linked_list_driver.c $(INC)linked_list_utils.h
	$(GFLAGS) $(CFLAGS) $(IFLAG) $(SRC)linked_list_driver.c
	mv linked_list_driver.o $(OBJ)

valgrind: $(BIN)output
	valgrind $(VFLAGS) $(LOGFLAG) $(BIN)output
clean:
	rm -f $(OBJ)*
	rm -f $(BIN)output

