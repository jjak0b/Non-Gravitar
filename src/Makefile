NonGravitar: main.o
	g++ -o NonGravitar main.o

main.o: main.cpp *.cpp *.hpp *.cpp *.hpp *.cpp *.hpp
	g++ -Ishared -Iengine -Ientities -c main.cpp *.cpp *.cpp *.cpp

clean:
	del *.o NonGravitar.exe NonGravitar