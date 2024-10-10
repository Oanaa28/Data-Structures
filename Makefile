build:
	gcc -o tema1 main.c functii.c -g -Wall
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./tema1