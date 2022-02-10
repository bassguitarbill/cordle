#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "loader.c"
void pick_random_answer(char* *answer, char* answer_list, int answer_count); 
void display_board(char* answer, char** guesses, int num_guesses);
void prompt_for_guess(char** guesses, int guess_index, char* guess_list, int guess_count, char* answer_list, int answer_count);
int is_valid_guess(char* guess, char* guess_list, int guess_count, char* answer_list, int answer_count);

#define MAX_GUESSES 6
int main() {

  srand(time(NULL));

  int ag_length;
  char *ag;
  allowed_guesses(&ag, &ag_length);

  int an_length;
  char *an;
  answers(&an, &an_length);

  char* ans;
  pick_random_answer(&ans, an, an_length);
  //printf("Random answer is %s\n", ans);

  char** guesses = calloc(MAX_GUESSES, sizeof(char*));
  int victory = 0;
  int i;
  for (i = 0; i < MAX_GUESSES; i++) {
    display_board(ans, guesses, i);
    prompt_for_guess(guesses, i, ag, ag_length, an, an_length);
    if (strcmp(guesses[i], ans) == 0) {
      i++;
      victory = 1;
      break;
    }
  }
  display_board(ans, guesses, i);
  if (victory) {
    printf("You did it!\n");
  } else {
    printf("You're out of guesses!\nThe word was '%s'\n", ans);
  }

  return 0;
}

void prompt_for_guess(char** guesses, int guess_index, char* guess_list, int guess_count, char* answer_list, int answer_count) {
  char* guess = malloc(6);
  while (1) {
    puts("What's your guess?");
    scanf("%5s", guess);
    if (is_valid_guess(guess, guess_list, guess_count, answer_list, answer_count)) {
      // printf("Ok that looks good\n");
      guesses[guess_index] = guess;
      break;
    }
    printf("'%s' is not a valid guess\n", guess);
  }
}

int is_valid_guess(char* guess, char* guess_list, int guess_count, char* answer_list, int answer_count) {
  // TODO these are sorted and this should be a binary search
  char* guess_from_list = calloc(6, sizeof(char));
  for (int i = 0; i < guess_count; i++) {
    memcpy(guess_from_list, guess_list + (i * 5), 5);
    if (strcmp(guess, guess_from_list) == 0) return 1;
  }
  for (int i = 0; i < answer_count; i++) {
    memcpy(guess_from_list, answer_list + (i * 5), 5);
    if (strcmp(guess, guess_from_list) == 0) return 1;
  }
  return 0;
}

void pick_random_answer(char* *answer, char* answer_list, int answer_count) {
  int max_rand = (RAND_MAX / answer_count) * answer_count; // all words should be equally likely
  int r = rand() % answer_count;

  char* a = calloc(6, sizeof(char));
  memcpy(a, answer_list + (r * 5), 5);
  *answer = a;
}

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
}
