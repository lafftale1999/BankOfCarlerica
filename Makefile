PROG = BankOfCarlerica.exe 
SRC = main.cpp src/account.cpp src/accountStorage.cpp src/bank.cpp src/bankerUI.cpp src/client.cpp src/clientStorage.cpp src/generateClients.cpp src/transaction.cpp src/transactionLink.cpp
CFLAGS = -g -Wall -Werror
LIBS =
CC = g++
BUILD_DIR = build
OBJECTS = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
BIN = BankOfCarlerica.exe

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(BIN)

.PHONY: all clean