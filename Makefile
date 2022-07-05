.PHONY: build run start

build dist/main:
	rm -rf dist/
	mkdir dist/
	gcc src/main.c -o dist/main -pthread -lm
	chmod +x dist/main

run start: dist/main
	./dist/main