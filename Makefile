all: queue

queue:
	gcc `pkg-config --cflags --libs glib-2.0` queue.c reqque.c
