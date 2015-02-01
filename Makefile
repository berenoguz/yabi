PREFIX ?= /usr/local
SRC = src/yabi.cpp
CXXFLAGS = -std=c++11 -Wall -pedantic
BIN = yabi
INC = -Iinclude
.PHONY: clean uninstall
$(BIN):
	$(CXX) $(SRC) $(INC) $(CXXFLAGS) -o $@
install: $(BIN) ; install $(BIN_PREFIX)$(BIN) $(PREFIX)/bin
clean:
	rm -f $(BIN)
uninstall:
	rm -f $(PREFIX)/bin/$(BIN)
