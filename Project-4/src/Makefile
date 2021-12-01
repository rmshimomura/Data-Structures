CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall -lm
OBJ = Objects

t2: $(OBJ)/main.o $(OBJ)/block.o $(OBJ)/dijkstra.o $(OBJ)/edge.o $(OBJ)/vertex.o $(OBJ)/AVL.o $(OBJ)/Dynamic_list.o $(OBJ)/Graph.o $(OBJ)/Prior.o $(OBJ)/Hash.o $(OBJ)/system.o $(OBJ)/paths.o $(OBJ)/checks.o $(OBJ)/kruskal.o $(OBJ)/svg.o $(OBJ)/qry.o $(OBJ)/Stack.o $(OBJ)/kosaraju.o $(OBJ)/viewbox.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -o t2 -lm

$(OBJ)/main.o: main.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/block.o: block.c block.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/dijkstra.o: dijkstra.c dijkstra.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/kruskal.o: kruskal.c kruskal.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/edge.o: edge.c edge.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/vertex.o: vertex.c vertex.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/system.o: system.c system.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/paths.o: paths.c paths.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/checks.o: checks.c checks.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/svg.o: svg.c svg.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/qry.o: qry.c qry.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/kosaraju.o: kosaraju.c kosaraju.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/viewbox.o: viewbox.c viewbox.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/AVL.o: AVL_Tree/AVL.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Dynamic_list.o: Dynamic_list/dynamic_list.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Graph.o: Graph/graph.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Hash.o: Hash/hash.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Prior.o: Priority_queue/priority_queue.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Stack.o: Stack/Stack.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<