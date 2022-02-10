#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "loader.c"
#include "display.c"
#include "wordle.h"

void pick_random_answer(char* *answer, char* answer_list, int answer_count); 
void display_board(char* answer, char** guesses, int num_guesses);
void prompt_for_guess(char** guesses, int guess_index, char* guess_list, int guess_count);
int is_valid_guess(char* guess, char* guess_list, int guess_count);

int main() {

  srand(time(NULL));

  int ag_length;
  char *ag;
  allowed_guesses(&ag, &ag_length);

  int an_length;
  char *an;
  answers(&an, &an_length);

  char* all_valid_guesses = malloc(5 * (ag_length + an_length));
  memcpy(all_valid_guesses, ag, 5 * ag_length);
  memcpy(all_valid_guesses + (5 * ag_length), an, 5 * an_length);

  free(ag);

  puts("Welcome to Bill's Wordle Clone!");

  while (1) {
    char* ans;
    pick_random_answer(&ans, an, an_length);
    //printf("Random answer is %s\n", ans);

    char** guesses = calloc(MAX_GUESSES, sizeof(char*));
    int victory = 0;
    int i;
    for (i = 0; i < MAX_GUESSES; i++) {
      display_board(ans, guesses, i);
      prompt_for_guess(guesses, i, all_valid_guesses, ag_length + an_length);
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

    for (int x = 0; x < i; x++) {
      free(guesses[x]);
    }

    free(guesses);
    free(ans);

    printf("Would you like to play again? [y/n]\n");
    char* again = malloc(1);
    scanf("\n%c", again);
    if ((*again) == 'n') {
      free(again);
      break;
    }
    free(again);
  }

  free(an);
  free(all_valid_guesses);

  return 0;
}

void prompt_for_guess(char** guesses, int guess_index, char* guess_list, int guess_count) {
  char* guess = malloc(6);
  while (1) {
    puts("What's your guess?");
    scanf("%5s", guess);
    if (is_valid_guess(guess, guess_list, guess_count)) {
      guesses[guess_index] = guess;
      break;
    }
    printf("'%s' is not a valid guess\n", guess);
  }
}

int is_valid_guess(char* guess, char* guess_list, int guess_count) {
  // TODO these are sorted and this should be a binary search
  char* guess_from_list = calloc(6, sizeof(char));
  for (int i = 0; i < guess_count; i++) {
    memcpy(guess_from_list, guess_list + (i * 5), 5);
    if (strcmp(guess, guess_from_list) == 0) return 1;
  }
  return 0;
}

void pick_random_answer(char* *answer, char* answer_list, int answer_count) {
  int r = rand() % answer_count;

  char* a = calloc(6, sizeof(char));
  memcpy(a, answer_list + (r * 5), 5);
  *answer = a;
}
