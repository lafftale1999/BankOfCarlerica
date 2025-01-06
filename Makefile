PROG = BankOfCarlerica.exe 
TESTPROG = test.exe
SRC = main.cpp src/account.cpp src/accountStorage.cpp src/bank.cpp src/bankerUI.cpp src/client.cpp src/clientStorage.cpp src/generateClients.cpp src/transaction.cpp src/transactionLink.cpp
TESTSRC = src/account.cpp src/transactionLink.cpp src/transaction.cpp test/test.cpp
CFLAGS = -g -Wall -Werror
LIBS =
CC = g++
BUILD_DIR = build
OBJECTS = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
BIN = BankOfCarlerica.exe
GTEST = gtest
LIBGTEST = C:\msys64\mingw64\lib\libgtest_main.a C:\msys64\mingw64\lib\libgtest.a

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTPROG): $(TESTSRC)
	g++ -o $@ $^  -I $(GTEST)  $(LIBGTEST)

test: $(TESTPROG)
	./$(TESTPROG)

clean:
	rm -f $(OBJECTS) $(BIN)

.PHONY: all clean