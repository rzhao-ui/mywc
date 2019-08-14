word:word.c libmylist.a
	gcc word.c ./libmylist.a -g -o myls -Wall
libmylist.a: mylist.o
	ar -rc libmylist.a mylist.o
mylist.o:mylist.c mylist.h
	gcc -g -c mylist.c -o mylist.o -Wall
.PHONY:clean
clean:
	rm word libmylist.a  mylist.o 
