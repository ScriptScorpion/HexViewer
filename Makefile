CC := gcc
CCF := -O1 -Wall -Wextra -std=c99
SRC := main.c
OUT := hv
main:
	$(CC) $(CCF) $(SRC) -o $(OUT)
