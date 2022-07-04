.PHONY: build run start

build dist/main:
	rm -rf dist/
	mkdir dist/
	gcc src/main.c src/sequencial/merge.c src/sequencial/mergesort.c -o dist/main
	chmod +x dist/main

run start: dist/main
	./dist/main