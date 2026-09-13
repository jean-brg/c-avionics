BUILD_TARGET = avionics
SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(patsubst ./src/%.c, ./obj/%.o, $(SOURCES))

all: $(BUILD_TARGET)

$(BUILD_TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $(BUILD_TARGET)

./obj/%.o: ./src/%.c | ./obj
	gcc -c $< -o $@

./obj:
	mkdir -p ./obj

run: $(BUILD_TARGET)
	./$(BUILD_TARGET)

clean:
	rm -rf ./obj $(BUILD_TARGET)