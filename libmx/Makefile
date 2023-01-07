NAME = libmx.a
flags := -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install: $(NAME)

$(NAME): objects
	ar -rcs $(NAME) obj/*.o
	ranlib $(NAME)

objects:
	mkdir -p obj
	clang $(flags )-c src/*.c -I inc/
	mv *.o obj/
	
uninstall:
	rm -rf $(NAME)
	rm -rfd obj

reinstall:
	make uninstall
	make all

clean:
	rm -rfd obj
