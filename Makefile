SRCS=  $(wildcard ./SRC/*.cpp) $(wildcard ./SRC/ParallelFunctions/*.cpp)
OBJS= $(SRCS:.cpp=.o)
CFLAGS= -fsycl -Wall -Wextra -fsanitize=address  -g -O3
CPP= icpx
NAME= math

.PHONY: clean

all: $(NAME)

launch : all
	./$(NAME)

%.o: %.cpp  $(wildcard ./SRC/*.h) $(wildcard ./SRC/*.hpp) $(wildcard ./include/*.h)
	$(CPP) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all