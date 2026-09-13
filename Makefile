BUILD_TARGET = avionics
OBJECTS = ./obj/main.o ./obj/rocket.o ./obj/environment.o

all: $(BUILD_TARGET)

$(BUILD_TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $(BUILD_TARGET)

./obj/%.o: ./src/%.c | make_obj_dir
	gcc -c $< -o $@

make_obj_dir:
	mkdir -p ./obj

run: $(BUILD_TARGET)
	./$(BUILD_TARGET)

clean:
	rm -rf ./obj $(BUILD_TARGET)