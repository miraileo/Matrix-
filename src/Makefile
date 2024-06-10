CFLAGS = -Wall -Werror -Wextra -std=c++17
FLAGS = -lgtest -lpthread -lstdc++ -lm

all: s21_matrix_oop.a

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

s21_matrix_oop.o: s21_matrix_oop.C
	gcc $(CFLAGS) -c s21_matrix_oop.C -o s21_matrix_oop.o $(FLAGS)

test: s21_matrix_oop.a s21_matrix_oop_test.o
	gcc $(CFLAGS) s21_matrix_oop_test.o s21_matrix_oop.a $(FLAGS) -o test
	./test

s21_matrix_oop_test.o: s21_matrix_oop_test.C
	gcc $(CFLAGS) -c s21_matrix_oop_test.C -o s21_matrix_oop_test.o

style:
	clang-format -n -style=google *.h *.C
	clang-format -i -style=google *.h *.C

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./test

full-check: style clean test valgrind
	
clean:
	rm -f *.o *.a test