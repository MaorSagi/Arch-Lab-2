
/* toy-io.c
 * Limited versions of printf and scanf
 *
 * Programmer: Mayer Goldberg, 2018
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* the states in the printf state-machine */
enum printf_state {
  st_printf_init,
  st_printf_percent,
  st_printf_octal2,
  st_printf_octal3
};

#define MAX_NUMBER_LENGTH 64
#define is_octal_char(ch) ('0' <= (ch) && (ch) <= '7')

int toy_printf(char *fs, ...);
int print_int_helper1(int n, int radix, const char *digit);
unsigned int print_int_helper(unsigned int n, int radix, const char *digit);
int print_int1(int n, int radix, const char * digit);
int print_int(int n, int radix, const char * digit);

const char *digit = "0123456789abcdef";
const char *DIGIT = "0123456789ABCDEF";

int print_int_helper1(int n, int radix, const char *digit) {
  int result;

  if (n < radix) {
    putchar(digit[n]);
    return 1;
  }
  else {
    result = print_int_helper(n / radix, radix, digit);
    putchar(digit[n % radix]);
    return 1 + result;
  }
}

unsigned int print_int_helper(unsigned int n, int radix, const char *digit) {
  	int result;
	
	

  if (n < radix) {
    putchar(digit[n]);
    return 1;
  }
  else {
    result = print_int_helper(n / radix, radix, digit);
    putchar(digit[n % radix]);
    return 1 + result;
  }
}

int print_int1(int n, int radix, const char * digit) {
  if (radix < 2 || radix > 16) {
    toy_printf("Radix must be in [2..16]: Not %d\n", radix);
    exit(-1);
  }

  if (n > 0) {
    return print_int_helper1(n, radix, digit);
  }
  if (n == 0) {
    putchar('0');
    return 1;
  }
  else {
    putchar('-');
    return 1 + print_int_helper1(-n, radix, digit);
  }
}


int print_int(int n, int radix, const char * digit) {
  if (radix < 2 || radix > 16) {
    toy_printf("Radix must be in [2..16]: Not %d\n", radix);
    exit(-1);
  }

  if (n > 0) {
    return print_int_helper(n, radix, digit);
  }
  if (n == 0) {
    putchar('0');
    return 1;
  }
  else {
	unsigned int tmp;
  	tmp = n;
    return print_int_helper(tmp, radix, digit);
  }
}



/* SUPPORTED:
 *   %b, %d, %o, %x, %X -- 
 *     integers in binary, decimal, octal, hex, and HEX
 *   %s -- strings
 */

int toy_printf(char *fs, ...) {
  int chars_printed = 0;
  int int_value = 0;
  char *string_value;
  char char_value;
  //char octal_char;
  va_list args;
  enum printf_state state;
  int arr_length = 0;
  int* int_arr;
  char** s_arr;
  char* c_arr;
  int left = 0;
  int char_counter=0;
  int width_val=0;
  int str_len=0;
  int tmp_value=0;

  va_start(args, fs);
  state = st_printf_init; 

  for (; *fs != '\0'; ++fs) {
    switch (state) {
    case st_printf_init:
      switch (*fs) {
      case '%':
	state = st_printf_percent;
	break;

      default:
	putchar(*fs);
	++chars_printed;
      }
      break;

    case st_printf_percent:
      switch (*fs) {
      case '%':
	putchar('%');
	++chars_printed;
	state = st_printf_init;
	break;

      case 'd':
	int_value = va_arg(args, int);
	chars_printed += print_int1(int_value, 10, digit);
	state = st_printf_init;
	break;

      case 'b':
	int_value = va_arg(args, int);
	chars_printed += print_int(int_value, 2, digit);
	state = st_printf_init;
	break;

      case 'o':
	int_value = va_arg(args, int);
	chars_printed += print_int(int_value, 8, digit);
	state = st_printf_init;
	break;
	
      case 'x':
	int_value = va_arg(args, int);
	chars_printed += print_int(int_value, 16, digit);
	state = st_printf_init;
	break;

      case 'X':
	int_value = va_arg(args, int);
	chars_printed += print_int(int_value, 16, DIGIT);
	state = st_printf_init;
	break;

      case 's':
	string_value = va_arg(args, char *);
	while(*string_value){
		chars_printed++;
		putchar(*string_value);
		string_value++;
	}
	state = st_printf_init;
	break;

      case 'c':
	char_value = (char)va_arg(args, int);
	putchar(char_value);
	++chars_printed;
	state = st_printf_init;
	break;

      case 'A':
	if(*fs != '\0')
	 ++fs;
 	switch (*fs) {
	case 'd':
	  toy_printf("{", *fs);
	  int_arr=va_arg(args, int*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int1(int_arr[i], 10, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'u':
	  int_arr=va_arg(args, int*);
	  toy_printf("{", *fs);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int(int_arr[i], 10, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'b':
	  toy_printf("{", *fs);
	  int_arr=va_arg(args, int*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int(int_arr[i], 2, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'o':
	  toy_printf("{", *fs);
	  int_arr=va_arg(args, int*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int(int_arr[i], 8, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'x':
	  toy_printf("{", *fs);
	  int_arr=va_arg(args, int*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int(int_arr[i], 16, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'X':
	  toy_printf("{", *fs);
	  int_arr=va_arg(args, int*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
	  	chars_printed += print_int(int_arr[i], 16, digit);
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 's':
	  toy_printf("{", *fs);
	  s_arr=va_arg(args, char**);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
		toy_printf("\"");
	  	chars_printed += toy_printf(s_arr[i]);
		toy_printf("\"");
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;
	case 'c':
	  toy_printf("{", *fs);
	  c_arr=va_arg(args, char*);
	  arr_length =  va_arg(args, int);
	  for(int i = 0 ; i<arr_length ; i++){
		toy_printf("'");
		putchar(c_arr[i]);
		toy_printf("'");
		++chars_printed;
	  	if(i<arr_length-1)
	  		toy_printf(", ", *fs);
	  }
	  toy_printf("}", *fs);
	  break;


	default:
	  toy_printf("Unhandled format %%A%c...\n", *fs);
	  exit(-1);
	}
	++chars_printed;
	state = st_printf_init;
	break;

      default:

	if(*fs=='-'){
		left=1;
		++fs;
	}
	if(isdigit(*fs)){
		for (; isdigit(*fs); ++fs) {
			++char_counter;
		}
		char num_arr[char_counter+1];
		fs=fs-char_counter;
		for (int i = 0; i<char_counter; ++i) {
			num_arr[i]=*fs;
			if(i != char_counter-1)
			++fs;
		}
		num_arr[char_counter]='\0';
		width_val = atoi(num_arr);
		
		if(*fs=='\0'){
			toy_printf("Unhandled format", *fs);
			exit(-1);
		}else ++fs;
		switch(*fs){


		case 'd':
			  int_value = va_arg(args, int);
			  if(int_value==0)
				++str_len;
			  else{
				  tmp_value=int_value;
	 			  if(int_value<0){
					++str_len;
					putchar('-');
					++chars_printed;
				  }
				  while(tmp_value!=0){
					tmp_value /= 10;
					++str_len;
				  }
			  }
			  for (int i = 0; i<(width_val-str_len); ++i) {
					toy_printf("0");
					++chars_printed;
					
				}
			  int_value=abs(int_value);
			  chars_printed += print_int1(int_value, 10, digit);
		 	  state = st_printf_init;
			  left = 0;
 			  char_counter=0;
			  width_val=0;
  			  str_len=0;
 			  tmp_value=0; 
			break;
			 

		case 's':
			string_value = va_arg(args, char *);
			str_len=strlen(string_value);
			if(left){
				for (int i = 0; i<(width_val-str_len); ++i) {
					toy_printf(" ");
					++chars_printed;
					
				}
				
				while(*string_value){
					chars_printed++;
					putchar(*string_value);
					string_value++;
				}
			state = st_printf_init;
			left = 0;
  			char_counter=0;
  			width_val=0;
			str_len=0;
			break;
			}
			else{
				while(*string_value){
					chars_printed++;
					putchar(*string_value);
					string_value++;
				}
				
				for (int i = 0; i<width_val-str_len; ++i) {
					toy_printf(" ");
					++chars_printed;
				}
				toy_printf("#");
		
			state = st_printf_init;
			left = 0;
  			char_counter=0;
  			width_val=0;
			str_len=0;
			break;
			}
		break;
		}

	}
	

	else{
	toy_printf("Unhandled format %%%c...\n", *fs);
	exit(-1);
	}
      }
      break;

    default:
      toy_printf("toy_printf: Unknown state -- %d\n", (int)state);
      exit(-1);
    }
  }

  va_end(args);

  return chars_printed;
}


