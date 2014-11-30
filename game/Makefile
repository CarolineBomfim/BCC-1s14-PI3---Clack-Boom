CC = gcc
CFLAGS = -std=c99 
EXEC = AngryRobots
MAIN = src/AngryRobots/main.c
LIBS = libs/*.c
OBJ = *.o
FLAGS = -lallegro -lallegro_color -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf\
				-lallegro_primitives -lallegro_audio -lallegro_acodec -lopencv_core -lopencv_highgui\
				-lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml\
				-lopencv_objdetect -lopencv_contrib -lopencv_legacy -lm
all: $(EXEC)

$(OBJ): $(LIBS) $(MAIN)
	$(CC) $(CFLAGS) $^ -c

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ)