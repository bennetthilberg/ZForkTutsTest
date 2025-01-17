# Project-specific settings
PROJECT := symbulation
TEST_MAIN := source/catch/main
EMP_DIR := Empirical/include

# Flags to use regardless of compiler
CFLAGS_all := -Wall -Wno-unused-function -std=c++20 -I$(EMP_DIR)/

# Native compiler information
CXX_nat := g++
CFLAGS_nat := -O3 -DNDEBUG $(CFLAGS_all)
CFLAGS_nat_debug := -g -DEMP_TRACK_MEM $(CFLAGS_all)
CFLAGS_nat_coverage := --coverage $(CFLAGS_all)

# Emscripten compiler information
CXX_web := emcc
OFLAGS_web_all := -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'stringToUTF8', 'UTF8ToString']" -s TOTAL_MEMORY=268435456 --js-library $(EMP_DIR)/emp/web/library_emp.js -s EXPORTED_FUNCTIONS="['_main', '_empCppCallback', '_empDoCppCallback']" -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=1 -s ASSERTIONS=1 #--embed-file configs
OFLAGS_web := -Oz -DNDEBUG
OFLAGS_web_debug := -g4 -Oz -pedantic -Wno-dollar-in-identifier-extension

CFLAGS_web := $(CFLAGS_all) $(OFLAGS_web) $(OFLAGS_web_all)
CFLAGS_web_debug := $(CFLAGS_all) $(OFLAGS_web_debug) $(OFLAGS_web_all)


default: $(PROJECT)
native: $(PROJECT)
web: $(PROJECT).js
all: $(PROJECT) $(PROJECT).js

debug:	CFLAGS_nat := $(CFLAGS_nat_debug)
debug:	$(PROJECT)

debug-web:	CFLAGS_web := $(CFLAGS_web_debug)
debug-web:	$(PROJECT).js

web-debug:	debug-web

$(PROJECT):	source/native/$(PROJECT).cc
	$(CXX_nat) $(CFLAGS_nat) source/native/$(PROJECT).cc -o $(PROJECT)
	@echo To build the web version use: make web

$(PROJECT).js: source/web/$(PROJECT)-web.cc
	$(CXX_web) $(CFLAGS_web) source/web/$(PROJECT)-web.cc -o web/$(PROJECT).js

.PHONY: clean test serve

serve:
	python3 -m http.server

clean:
	rm -f $(PROJECT) web/$(PROJECT).js web/*.js.map web/*.js.map *~ source/*.o

test:
	$(CXX_nat) $(CFLAGS_nat) $(TEST_MAIN).cc -o $(PROJECT).test
	./$(PROJECT).test

test-debug:
	$(CXX_nat) $(CFLAGS_nat_debug) $(TEST_MAIN).cc -o $(PROJECT).test
	./$(PROJECT).test

coverage:
	$(CXX_nat) $(CFLAGS_nat_coverage) $(TEST_MAIN).cc -o $(PROJECT).test
	./$(PROJECT).test


# Debugging information
print-%: ; @echo '$(subst ','\'',$*=$($*))'
