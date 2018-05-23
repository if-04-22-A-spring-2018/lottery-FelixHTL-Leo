/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "lottery.h"

#define 	UUID_LEN   40
#define 	MAX_TIP_LEN   17
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN + 1)

static char* name_of_file;
static char seperator;
static int* drawing;
static bool drew_or_not = false;

bool 	init_lottery (char *csv_file, char csv_separator){
  FILE* fd = fopen(csv_file, "r");
  name_of_file = csv_file;
  seperator = csv_separator;
  drew_or_not = false;
  if(fd == 0){
    return false;
  }
  fclose(fd);
  return true;
}

bool 	get_tip (int tip_number, int tip[TIP_SIZE]){
  FILE* fd = fopen(name_of_file, "r");
  char input[MAX_LINE_LEN] = {0};
  int count = 0;
  if(tip_number < 0 || fd == 0){
    fclose(fd);
    return false;
  }
  char* lines = fgets(input, MAX_LINE_LEN, fd);
  while(lines != 0 && count < tip_number){
    lines = fgets(input, MAX_LINE_LEN, fd);
    count++;
    if(lines != input){
      fclose(fd);
      return false;
    }
  }
  if(ftell(fd) == EOF){
    fclose(fd);
    return false;
  }

  int position_of_seperator = 0;
  while (input[position_of_seperator] != seperator && position_of_seperator < UUID_LEN) {
    position_of_seperator++;
  }
  int pos_of_insertion = 0;
  int insertion = 0;
  while(pos_of_insertion < 6){
    position_of_seperator++;
    if(input[position_of_seperator] <= '9' && input[position_of_seperator] >= '0'){
      insertion = insertion * 10 + (input[position_of_seperator] - '0');
    }
    else{
      tip[pos_of_insertion] = insertion;
      insertion = 0;
      pos_of_insertion++;
    }
  }
  fclose(fd);
  return true;
}

bool 	set_drawing (int drawing_numbers[TIP_SIZE]){
  drew_or_not = true;
  drawing = drawing_numbers;
  return false;
}

int 	get_tip_result (int tip_number){
  if(!drew_or_not){
    return -1;
  }
  int array[6];
  if(!get_tip(tip_number, array)){
    return -2;
  }
  int count = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if(array[i] == drawing[j]){
        count++;
      }
    }
  }
  return count;
}

int 	get_right_tips_count (int right_digits_count){
  if(!drew_or_not || right_digits_count < 0 || right_digits_count > TIP_SIZE){
    return -1;
  }
  int v1 = 0;
  int v2 = 0;
  int count = 0;
  while(v1 != -2 && v1 != -1){
    v1 = get_tip_result(v2);
    if(v1 == right_digits_count){
      count++;
    }
    v2++;
  }
  return count;
}
