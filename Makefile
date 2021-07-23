SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = src/lex.yy.o src/y.tab.o $(SRC_FILES:%.c=%.o) 
C_FLAGS = -g
LIB_FLAGS = -Isrc -I.

all: $(OBJ_FILES)
	gcc $(OBJ_FILES) $(C_FLAGS) -o lisp

src/lex.yy.c: src/lexer.l
	cd src; flex lexer.l

src/y.tab.c src/y.tab.h: src/parser.y
	cd src; yacc -dtv parser.y

src/%.o: src/%.cpp
	gcc $(LIB_FLAGS) $(C_FLAGS) -c $< -o $@

src/y.tab.o: src/y.tab.c 
	cd src; gcc $(LIB_FLAGS) $(C_FLAGS) y.tab.c -DYYDEBUG -c

src/lex.yy.o: src/lex.yy.c src/y.tab.h 
	cd src; gcc $(LIB_FLAGS) $(C_FLAGS) lex.yy.c -c -o lex.yy.o

clean: 
	rm -f lisp; cd src; rm -f *.o *.output *tab* *yy*