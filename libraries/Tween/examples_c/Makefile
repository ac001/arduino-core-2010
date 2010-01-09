all:
	g++ -Wall -I.. -c -o Tween.o ../Tween.cpp
	g++ -Wall -I.. -c -o tween_test.o tween_test.cpp
	g++ -Wall -o tween_test tween_test.o Tween.o

clean:
	rm -f *.o tween_test 
