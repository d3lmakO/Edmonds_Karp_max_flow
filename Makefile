CXXFLAGS=-W -Wextra -O3
LDLIBS=

MAXFLOW: main.o adjacency_list.o graph_source_file.o ford_fulkerson.o
	$(LINK.cc) $^ -o $@

main.o: main.cc 
	$(COMPILE.cc) main.cc -o main.o 

adjacency_list.o: adjacency_list.cc adjacency_list.h 
	$(COMPILE.cc) adjacency_list.cc -o adjacency_list.o

graph_source_file.o: graph_source_file.cc graph_source_file.h
	$(COMPILE.cc) graph_source_file.cc -o graph_source_file.o

ford_fulkerson.o: ford_fulkerson.cc ford_fulkerson.h
	$(COMPILE.cc) ford_fulkerson.cc -o ford_fulkerson.o

.PHONY: clean

clean: 
	$(RM) *.o
