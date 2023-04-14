# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: feribot nostory p3 p4

run-p1:
	./feribot
run-p2:
	./nostory
run-p3:
	./p3
run-p4:
	./p4

# Nu uitați să modificați numele surselor și, eventual, ale executabilelor.
feribot: skel/feribot/feribot.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
nostory: skel/nostory/nostory.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p3: p3.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p4: p4.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f feribot nostory p3 p4
