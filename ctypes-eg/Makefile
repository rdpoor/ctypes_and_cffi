all: test

clean:
	rm -f *.o *.so *.html

model.so: model.o
	gcc -shared -o libmodel.so model.o

model.h: ../c-code/model.h
	cp -p ../c-code/model.h .

model.c: ../c-code/model.c
	cp -p ../c-code/model.c .

model.o: model.h model.c
	gcc -c -Wall -Werror -fpic model.c

test: model.so
	./test_model.py
