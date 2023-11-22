SRC_FILES=app.c lib.c
HEADER_FILES=lib.h
CFLAGS += -std=c99 -g -Wall -Wextra -Wno-missing-field-initializers

all: app makeDB

app: $(SRC_FILES) $(HEADER_FILES)
	gcc $(CFLAGS) -o $@ $(SRC_FILES) -lm

clean:
	rm -f app

run: app
	# Running our main function from file main.c
	./app
makeDB:
	mkdir ./Databases