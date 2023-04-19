# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: feribot nostory sushi semnale badgpt

run-p1:
	./feribot
run-p2:
	./nostory
run-p3:
	./sushi
run-p4:
	./semnale
run-p5:
	./badgpt

# Nu uitați să modificați numele surselor și, eventual, ale executabilelor.
feribot: skel/feribot/feribot.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
nostory: skel/nostory/nostory.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
sushi: skel/sushi/sushi.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
semnale: skel/semnale/semnale.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
badgpt: skel/badgpt/badgpt.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f feribot nostory sushi semnale badgpt
