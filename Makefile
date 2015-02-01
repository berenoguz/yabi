PREFIX ?= /usr/local
SRC = src/yabi.cpp
INCLUDE = include
INCLUDE_DIR = /usr/
CXXFLAGS = -std=c++11 -Wall -pedantic
BIN = yabi
INC = -Iinclude
.PHONY: clean uninstall
$(BIN):
	$(CXX) $(SRC) $(INC) $(CXXFLAGS) -o $@
install: $(BIN)
	install $(BIN) $(PREFIX)/bin
	cp -r $(INCLUDE) $(INCLUDE_DIR)
clean:
	rm -f $(BIN)
uninstall:
	rm -f $(PREFIX)/bin/$(BIN)
