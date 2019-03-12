EXECUTABLE := main
all:
	g++ -ggdb *.cpp -o $(EXECUTABLE)
.PHONY:clean
clean:
	rm -rf $(EXECUTABLE)
