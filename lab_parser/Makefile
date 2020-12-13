OBJECTS = main.o grammar.o parser.o production.o parser_output.o node.o
TARGET = run
COMP ?= clang++
CONFIG ?= debug
ARCHV ?= $(shell getconf LONG_BIT)
OUTDIR = bin

COMP_FLAGS = -std=gnu++20

ifeq ($(ARCHV), 32)
    COMP_FLAGS := ${COMP_FLAGS} -m32
else ifeq ($(ARCHV), 64)
    COMP_FLAGS := ${COMP_FLAGS} -m64
else
	$(error "Unknown archv ("$(ARCHV)")!")
endif

ifeq ($(CONFIG), debug)
	COMP_FLAGS := ${COMP_FLAGS} -g
else ifeq ($(CONFIG), release)
	COMP_FLAGS := ${COMP_FLAGS} -O3 -march=native
else
    $(error "Unknown config ("$(CONFIG)")!")
endif

ifeq ($(COMP), clang++)
	COMP_FLAGS := ${COMP_FLAGS} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-reserved-id-macro
else ifeq ($(COMP), g++)
	COMP_FLAGS := ${COMP_FLAGS} -Wall -Wextra
else
	$(error "Unknown comp ("$(COMP)")!")
endif

LINK_FLAGS := ${LINK_FLAGS} -lpthread

all: $(OBJECTS)
	mkdir -p $(OUTDIR)
	$(COMP) $(COMP_FLAGS) $(LINK_FLAGS) $(CDEFINES) $^ -o$(OUTDIR)/$(TARGET)

clean:
	$(RM) $(OBJECTS) $(OUTDIR)/$(TARGET)
	$(RM) -r $(OUTDIR)

%.o: %.cpp
	$(COMP) $(COMP_FLAGS) $(CDEFINES) -o "$@" -c $<

tidy:
	/usr/share/clang/run-clang-tidy.py -header-filter=.* . > tidy.log

tidyfix:
	/usr/share/clang/run-clang-tidy.py -fix . > tidyfix.log

valgrind:
	valgrind --leak-check=full --track-origins=yes $(OUTDIR)/$(TARGET)
