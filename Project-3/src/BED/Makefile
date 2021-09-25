CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g
OBJ = Objects

t1: $(OBJ)/main.o $(OBJ)/block.o $(OBJ)/checks.o $(OBJ)/location.o $(OBJ)/paths.o $(OBJ)/person.o $(OBJ)/qry.o $(OBJ)/system.o $(OBJ)/AVL.o $(OBJ)/Hash.o $(OBJ)/DynamicList.o $(OBJ)/svg.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -o t1 -lm

$(OBJ)/main.o: main.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/block.o: block.c block.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/checks.o: checks.c checks.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/location.o: location.c location.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/paths.o: paths.c paths.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/person.o: person.c person.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/qry.o: qry.c qry.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $< 
$(OBJ)/system.o: system.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/svg.o : svg.c svg.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/AVL.o: AVL_Tree/AVL.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/Hash.o: Hash/hash.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ)/DynamicList.o: DynamicList/dynamiclist.c |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<