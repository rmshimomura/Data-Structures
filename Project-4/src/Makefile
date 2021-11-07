CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
OBJ = Objects

t2: $(OBJ)/main.o $(OBJ)/block.o $(OBJ)/dijkstra.o $(OBJ)/edge.o $(OBJ)/vertex.o $(OBJ)/AVL.o $(OBJ)/Dynamic_list.o $(OBJ)/Graph.o $(OBJ)/Prior.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -o t2 -lm

$(OBJ)/main.o: main.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/block.o: block.c block.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/dijkstra.o: dijkstra.c dijkstra.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/edge.o: edge.c edge.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/vertex.o: vertex.c vertex.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/AVL.o: AVL_Tree/AVL.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Dynamic_list.o: Dynamic_list/dynamic_list.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Graph.o: Graph/graph.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Prior.o: Priority_queue/priority_queue.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<