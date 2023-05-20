

TARGET = app

objs = main.o msg.o

app: $(objs)
	g++ $^ -o final.o


%.o: %.cpp
	g++ -c $< -o $@


clean:
	rm -rf *.o
