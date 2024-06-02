# SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
#
# SPDX-License-Identifier: MIT

sources = $(wildcard src/*.c)

objects = $(sources:.c=.o)
deps = $(sources:.c=.d)

CFLAGS ?= -O3
CFLAGS := ${CFLAGS} -std=c17 -MD -MP -I ${PWD}/include

RB ?= ruby

RBFLAGS ?= -rminitest/pride

all: libsdd.a

test:
	@$(RB) ${RBFLAGS} test/test_helper.rb

clean:
	rm -rf src/*.o
	rm -rf src/*.d
	rm -rf libsdd.a
	rm -rf test/samples/*.exe

-include ${deps}

libsdd.a: $(objects)
	$(AR) rcu $@ $+

# Add .exe extension to make it easier to .gitignore and cleanup
test/%.exe: test/%.c libsdd.a
	$(CC) $+ -I ${PWD}/include -L. -lsdd -o $@

love:
	@echo "Not war"

.PHONY: all clean test
