CC = g++
CFLAGS = -Iinclude

SRCS = src/main.cpp src/Jogador.cpp src/Embarcacao.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

// make && ./jogo