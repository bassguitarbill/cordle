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
void print_unknown(char a) {
  printf("%s%s %c ", "\e[0;37m", "\e[40m", a);
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

void display_guess(char* answer, char* guess, int* guessed_letters) {
  printf("      ");
  for (int i = 0; i < 5; i ++) {
    if (is_correct(answer[i], guess[i])) {
      print_correct(guess[i]);
      guessed_letters[guess[i] - 'a'] = 3;
    } else if(is_in_word(guess[i], answer)) {
      print_in_word(guess[i]);
      if (guessed_letters[guess[i] - 'a'] < 2) {
        guessed_letters[guess[i] - 'a'] = 2;
      }
    } else { 
      print_incorrect(guess[i]);
      if (guessed_letters[guess[i] - 'a'] < 1) {
        guessed_letters[guess[i] - 'a'] = 1;
      }
    }
  }
  puts("\e[0m");
}

void print_result(char c, int* guessed_letters) {
  int result = guessed_letters[c - 'a'];
  switch (result) {
    case 3:
      print_correct(c);
      break;
    case 2:
      print_in_word(c);
      break;
    case 1:
      print_unknown(c);
      break;
    default:
      print_incorrect(c);
  }
}
void display_guessed_letters(int* guessed_letters) {
  char top_row[10] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
  char middle_row[9] = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
  char bottom_row[7] = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
  for (int i = 0; i < 10; i++) {
    char c = top_row[i];
    print_result(c, guessed_letters);
  }
  printf("\e[0m\n ");
  for (int i = 0; i < 9; i++) {
    char c = middle_row[i];
    print_result(c, guessed_letters);
  }
  printf("\e[0m\n  ");
  for (int i = 0; i < 7; i++) {
    char c = bottom_row[i];
    print_result(c, guessed_letters);
  }
  puts("\e[0m");
  printf("\n");
}

void display_empty_row() {
  puts("       _  _  _  _  _ ");
}

void display_board(char* answer, char** guesses, int num_guesses) {
  int guessed_letters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = 0; i < num_guesses; i++) {
    display_guess(answer, guesses[i], guessed_letters);
  }

  for (int i = num_guesses; i < MAX_GUESSES; i++) {
    display_empty_row();
  }

  puts("");

  display_guessed_letters(guessed_letters);
}
