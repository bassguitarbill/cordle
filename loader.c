#include "loader.h"

void answers(char **an, int *an_length) {
  load_word_file("wordle-answers-alphabetical.txt", an, an_length);
}

void allowed_guesses(char **ag, int *ag_length) {
  load_word_file("wordle-allowed-guesses.txt", ag, ag_length);
}

void load_word_file(char* filename, char **ls, int *ls_length) {
  FILE* guess_file = fopen(filename, "r");
  fseek(guess_file, 0L, SEEK_END);
  int sz = ftell(guess_file);
  int wc = (sz / 6) + 1;
  char* words = malloc(wc * 5);
  rewind(guess_file);

  char* current_word = malloc(6);
  int count = 0;
  while(fgets(current_word, 7, guess_file) != NULL) {
    char* wa = words + (count * 5);
    memcpy(wa, current_word, 5);
    count++;
  }

  fclose(guess_file);

  free(current_word);

  *ls = words;
  *ls_length = count;
}
