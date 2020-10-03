TARGET = dist/sha256.a

SOURCES = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
LIBS = $(wildcard lib/**)

INCLUDE = $(patsubst %,-I%,$(LIBS))

all: $(TARGET)

run: $(TARGET)
	$^

.SECONDEXPANSION:

$(TARGET): $(OBJECTS) | $$(@D)/.keep
	ar -r $@ $^

build/%.o: src/%.c | $$(@D)/.keep
	clang -std=c11 -Wall -O2 $(INCLUDE) -MD -o $@ -c $< 

.PRECIOUS: %/.keep

%/.keep:
	mkdir -p $(dir $@)
	@touch $@

clean:
	rm -rf dist build

-include $(OBJECTS:.o=.d)
