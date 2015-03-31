all: queue

queue:
	gcc `pkg-config --cflags --libs glib-2.0` reqque.c
