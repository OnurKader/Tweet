clean:
	rm -f Main
build:
	g++ -o Main Main.cpp -O3 -std=c++14
run:
	clear && ./Main
