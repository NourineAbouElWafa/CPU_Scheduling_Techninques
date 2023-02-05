CC = g++ -g


lab4:
	$(CC)  -o lab4 lab4.cc
clean:
	rm -f  lab4 *.o
