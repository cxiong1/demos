HEADER=utils.h
SRC=gradebook.c student.c teacher.c admin.c utils.c
FLAGS=-no-pie -fno-pie -fno-stack-protector -z execstack

all: $(HEADER) $(SRC)
	mkdir -p bin
	gcc $(SRC) $(FLAGS) -o bin/gradebook

clean:
	rm -f bin/gradebook
