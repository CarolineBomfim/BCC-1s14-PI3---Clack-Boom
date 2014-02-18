CC=gcc -std=c99
CFLAGS = -W -Wall -pedantic
EXEC = main
LIBS_H = $(wildcard */*/*.h) $(wildcard */*.h) $(wildcard *.h)
SRC=  $(wildcard */*/*.c) $(wildcard */*.c) $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS=-lallegro -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(OBJ)