/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class name here>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * File:			lottery.h
 * Author:			Peter Bauer
 * Due Date:		#due#
 * ----------------------------------------------------------
 * Description:
 * Header for lottery tips analysis.
 * ----------------------------------------------------------
 */
 #ifndef ___LOTTERY_H
#define ___LOTTERY_H

#include "general.h"

#define TIP_SIZE 6

bool init_lottery(char *csv_file, char csv_separator);

bool get_tip(int tip_number, int tip[TIP_SIZE]);

bool set_drawing(int drawing_numbers[TIP_SIZE]);

int get_tip_result(int tip_number);

int get_right_tips_count(int right_digits_count);

 #endif
