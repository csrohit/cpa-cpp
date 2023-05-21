

SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:%.cpp=%.o)


test.o: $(OBJS)
	g++ -o $@ $^


%.o: %.cpp
	gcc -o $@ -c $<


clean:
	rm -rf *.o
