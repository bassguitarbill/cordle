#include "wordle.h"

void print_correct(char a) {
  printf("%s%s %c ", "\e[0;30m", "\e[42m", a);
}
void print_in_word(char a) {
  printf("%s%s %c ", "\e[0;30m", "\e[43m", a);
}
void print_incorrect(char a) {
  printf("%s%s %c ", "\e[0;30m", "\e[47m", a);
}

int is_correct(char a, char b) {
  return a == b;
}

int is_in_word(char a, char* word) {
  for (int i = 0; i < 5; i ++) {
    if (a == word[i]) return 1;
  }
  return 0;
}

void display_guess(char* answer, char* guess) {
  for (int i = 0; i < 5; i ++) {
    if (is_correct(answer[i], guess[i])) print_correct(guess[i]);
    else if(is_in_word(guess[i], answer)) print_in_word(guess[i]);
    else print_incorrect(guess[i]);
  }
  puts("\e[0m");
}

void display_empty_row() {
  puts(" _  _  _  _  _ ");
}

void display_board(char* answer, char** guesses, int num_guesses) {
  for (int i = 0; i < num_guesses; i++) {
    display_guess(answer, guesses[i]);
  }

  for (int i = num_guesses; i < MAX_GUESSES; i++) {
    display_empty_row();
  }

  // TODO display keyboard with keys highlighted
}
