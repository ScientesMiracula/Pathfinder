flags := -std=c11 -Wall -Wextra -Werror -Wpedantic
NAME := pathfinder
LIBMX := libmx

.PHONY: $(LIBMX) $(NAME)

all: $(LIBMX) $(NAME)

$(NAME): 
	clang $(flags) -I inc -L./libmx -lmx  src/*.c -o $(NAME)

$(LIBMX):
	make -C libmx reinstall

uninstall:
	make clean
	rm -rfd $(NAME) 
	make -C libmx uninstall

clean:
	rm -rfd /obj 

reinstall:
	make uninstall
	make 
