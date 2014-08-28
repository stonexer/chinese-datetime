CC=gcc
CFLAGS=-g -Wall -Wfatal-errors -std=c99 $(shell pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1 libgtop-2.0)

all: indicator-test

indicator-test: indicator-test.c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm -f *.o indicator-test

install:
	install --mode=755 indicator-test  /usr/bin/
	install indicator-test.gschema.xml /usr/share/glib-2.0/schemas/
	glib-compile-schemas /usr/share/glib-2.0/schemas/

uninstall:
	rm /usr/bin/indicator-test
	rm /usr/share/glib-2.0/schemas/indicator-test.gschema.xml

