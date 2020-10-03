NAME = libsha256

TARGET = dist/$(NAME).a
DST_INC = dist/sha256
DST_HDR = $(patsubst src/%,$(DST_INC)/%,$(HDR))
DST = $(TARGET) $(DST_HDR)

HDR = $(wildcard src/**/*.h) $(wildcard src/*.h)
SOURCES = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
LIBS = $(wildcard lib/**)

INCLUDE = $(patsubst %,-I%,$(LIBS))

all: $(DST)

run: $(TARGET)
	$^

.SECONDEXPANSION:

$(DST_INC)/%.h: src/%.h | $$(@D)/.keep
	cp $^ $@

$(TARGET): $(OBJECTS) | $$(@D)/.keep
	ar -r $@ $^

build/%.o: src/%.c | $$(@D)/.keep
	clang -std=c11 -Wall -O2 $(INCLUDE) -MD -o $@ -c $< 

.PRECIOUS: %/.keep

%/.keep:
	mkdir -p $(dir $@)
	@touch $@

clean:
	rm -rf $(DST) build

-include $(OBJECTS:.o=.d)
