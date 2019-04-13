.PHONY: run

OUTFILE=game.out

run:
	gcc tictactoe.c -o $(OUTFILE)
	./$(OUTFILE)
