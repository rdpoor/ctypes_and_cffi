all: model

clean:
	rm -f *.o *.so _model.c model.h.preprocessed

libmodel.so: model.o
	gcc -shared $^ -o $@

model.h: ../c-code/model.h
	cp -p ../c-code/model.h .

model.c: ../c-code/model.c
	cp -p ../c-code/model.c .

model.o: model.h model.c
	cp -p ../c-code/model.* .
	gcc -c -Wall -Werror -fpic model.c

model: export LD_LIBRARY_PATH = $(shell pwd)
model: libmodel.so
	# technique to get around cffi's lack of #include support
	gcc -E model.h > model.h.preprocessed
	./build_model.py
	./test_model.py
