all:
	g++ main.cpp ./classes/func/*.cpp -o Exec; mv Exec exec; exec/Exec