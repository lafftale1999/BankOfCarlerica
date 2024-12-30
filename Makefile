PROG = main.exe 
SRC = main.cpp src/transaction.cpp src/transactionLink.cpp src/account.cpp src/accountStorage.cpp src/client.cpp
CFLAGS = -g -Wall -Werror
LIBS =
CC = g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean