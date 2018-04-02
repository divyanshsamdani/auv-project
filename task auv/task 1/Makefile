CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv` -lpthread
CC = g++
% : %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
