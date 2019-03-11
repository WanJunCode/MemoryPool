EXECUTABLE := main
all:
	g++ *.cpp -o $(EXECUTABLE)
.PHONY:clean
clean:
	rm -rf $(EXECUTABLE)
