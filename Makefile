CC=gcc 
CFLAGS = -std=c99 -W -Wall -pedantic
EXEC = main
SRC= $(wildcard */*.c) $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS=-lallegro -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lm


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

FILE_O = $(wildcard *.o) $(wildcard */*.o)

.PHONY: clean

clean:
	rm -f $(FILE_O)