CFLAGS=-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla

COMP=g++

all:
	$(COMP) $(CFLAGS) -c main.cpp list.cpp func.cpp graphviz_gen.cpp list_ptr.cpp
	$(COMP) main.o list.o func.o graphviz_gen.o list_ptr.o
	mv graphviz_gen.o outputfiles/graphviz_gen.o
	mv list_ptr.o outputfiles/list_ptr.o
	mv main.o outputfiles/main.o
	mv list.o outputfiles/list.o
	mv func.o outputfiles/func.o

run:
	./a.out
	dot Graphviz/graph.dot -T png -o Graphviz/graph.png
	dot Graphviz/graph2.dot -T png -o Graphviz/graph2.png