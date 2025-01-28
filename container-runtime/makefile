CC = clang
CFLAGS = -Wall

BASE = $(CC) $(CFLAGS)
BUILD = -o main main.c test.c
FMT = clang-format

build:
	$(BASE) ${BUILD}

run:
	$(BASE) $(BUILD) && ./main run ls

format:
	$(FMT) -i main.c

clean:
	rm -f main
