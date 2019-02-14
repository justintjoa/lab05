table: tabledemo.o table.o entry.o 
	g++ -o $@ $^

clean:
	/bin/rm -f *.o table
