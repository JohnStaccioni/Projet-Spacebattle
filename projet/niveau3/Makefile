CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h graphics.h spaceship_data.h structure.h constante.h sdl2-ttf-light.h
SRC = main.c sdl2-light.c graphics.c spaceship_data.c sdl2-ttf-light.c
OBJ = $(SRC:%.c=%.o)

TEST_INC = spaceship_data.h structure.h constante.h
TEST_SRC = tests.c spaceship_data.c
TEST_OBJ = $(TEST_SRC:%.c=%.o)


PROG = spacebattle

DEFAULT:spacebattle spacebattle_test clean

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

spacebattle_test: $(TEST_OBJ)
	gcc $(CFLAGS) $(TEST_OBJ) $(LDFLAGS) -o $@


doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o
	rm -rf latex html