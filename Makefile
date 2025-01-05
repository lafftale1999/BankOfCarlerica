PROG = main.exe 
SRC = main.cpp src/account.cpp src/accountStorage.cpp src/bank.cpp src/bankerUI.cpp src/client.cpp src/clientStorage.cpp src/generateClients.cpp src/transaction.cpp src/transactionLink.cpp
CFLAGS = -g -Wall -Werror
LIBS =
CC = g++
OBJECTS= $(SOURCES:.cpp=.o)
BIN= BankOfCarlerica

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean