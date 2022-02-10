#include <stdlib.h>
#include <stdio.h>

void allowed_guesses(char** guesses);

int main() {
  printf("\e[0;30m\e[42m Hello, \e[0m\e[0;30m \e[43m wordle! \e[0m\n");
  allowed_guesses(NULL);
  return 0;
}

void allowed_guesses(char** guesses) {
  FILE* guess_file = fopen("wordle-allowed-guesses.txt", "r");
  fseek(guess_file, 0L, SEEK_END);
  int sz = ftell(guess_file);
  rewind(guess_file);
  printf("%d\n", sz);
  char* current_word = malloc(6);
  int count = 0;
  while(fgets(current_word, 7, guess_file) != NULL) {
    printf("%s\n", current_word);
    count++;
  }
  printf("%d words\n", count);
}
