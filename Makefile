.RECIPEPREFIX = >
.PHONY = install

cmp = clang++
w_flags = -Wall -Wextra -Werror
flags = --std=c++20 -O2
build_dir = bin
src_dir = src

install: sap clean

sap: main.o cpu.o memory.o utils.o
> $(cmp) $? -o $(build_dir)/$@

cpu: cpu.o memory.o
> $(cmp) $? -o $(build_dir)/$@

memory: memory.o
> $(cmp) $? -o $(build_dir)/$@

debug: $(src_dir)/main.cpp $(src_dir)/cpu.cpp $(src_dir)/memory.cpp $(src_dir)/utils.cpp 
> $(cmp) $(w_flags) $(flags) -g $? -o $(build_dir)/$@

clean:
> rm -f *.o

clean_all: clean
> rm -f $(build_dir)/*

rebuild: clean_all all

%.o: $(src_dir)/%.cpp
> $(cmp) -c $(w_flags) $(flags) $?
