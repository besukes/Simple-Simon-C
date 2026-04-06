simpleSimon.o: simpleSimon.c
  gcc -Wall -ggdb -c simpleSimon.c -lSDL2 -lSDL2_image
simpleSimon : simpleSimon.o
  gcc -ggdb $^ -o $@
clean:
  rm simpleSimon.o simpleSimon
