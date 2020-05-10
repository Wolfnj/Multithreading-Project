hw6: main.o Log.o Knight.o Rabbit.o SafeQueue.o
	g++ main.o Log.o Knight.o Rabbit.o SafeQueue.o -o hw6 -lpthread

main.o: main.cpp
	g++ -c main.cpp

Log.o: Log.cpp Log.h
	g++ -c Log.cpp

Knight.o: Knight.cpp Knight.h
	g++ -c Knight.cpp

Rabbit.o: Rabbit.cpp Rabbit.h
	g++ -c Rabbit.cpp

SafeQueue.o: SafeQueue.cpp SafeQueue.h
	g++ -c SafeQueue.cpp

clean:
	rm *.o