.DEFAULT_GOAL := wordle

wordle-allowed-guesses.txt:
	curl https://gist.githubusercontent.com/cfreshman/cdcdf777450c5b5301e439061d29694c/raw/de1df631b45492e0974f7affe266ec36fed736eb/wordle-allowed-guesses.txt > wordle-allowed-guesses.txt

wordle-answers-alphabetical.txt:
	curl https://gist.githubusercontent.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b/raw/5d752e5f0702da315298a6bb5a771586d6ff445c/wordle-answers-alphabetical.txt > wordle-answers-alphabetical.txt

wordle: *.c
	cc -o wordle main.c

run: wordle wordle-allowed-guesses.txt wordle-answers-alphabetical.txt
	./wordle
