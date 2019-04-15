.PHONY: run

OUTFILE=game.out

run:
	gcc main.c -o $(OUTFILE)
	./$(OUTFILE)
