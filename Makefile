BUILD_DIR := src
RELEASE_DIR := release
DEBUG_DIR := debug
CXX = g++
OBJDIR_DEBUG = obj/debug
OBJDIR_RELEASE = obj/release
OUT_DEBUG = bin/debug/minesweeper
OUT_RELEASE = bin/release/minesweeper




OBJ_DEBUG = $(OBJDIR_DEBUG)/grid.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/rand.o  

OBJ_RELEASE = $(OBJDIR_RELEASE)/grid.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/rand.o  

all: debug release

clean: clean_debug clean_release

before_debug:
	test -d bin/debug || mkdir bin/debug

after_debug:

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG)
	$(CXX) -o $(OUT_DEBUG) $(OBJ_DEBUG) -g -ggdb

$(OBJDIR_DEBUG)/grid.o: src/grid.cpp
	$(CXX) -c src/grid.cpp -o $(OBJDIR_DEBUG)/grid.o -g -ggdb

$(OBJDIR_DEBUG)/rand.o: src/rand.cpp
	$(CXX) -c src/rand.cpp -o $(OBJDIR_DEBUG)/rand.o -g -ggdb

$(OBJDIR_DEBUG)/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o $(OBJDIR_DEBUG)/main.o -g -ggdb

clean_debug:

before_release:
	test -d bin/Release || mkdir -p bin/Release

after_release:

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE)
	$(CXX) -o $(OUT_RELEASE) $(OBJ_RELEASE) -s

$(OBJDIR_RELEASE)/grid.o: src/grid.cpp
	$(CXX) -c src/grid.cpp -o $(OBJDIR_RELEASE)/grid.o

$(OBJDIR_RELEASE)/rand.o: src/rand.cpp
	$(CXX) -c src/rand.cpp -o $(OBJDIR_RELEASE)/rand.o

$(OBJDIR_RELEASE)/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o $(OBJDIR_RELEASE)/main.o

clean_release:
