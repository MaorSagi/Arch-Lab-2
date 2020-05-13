# Arch-Lab-2
C programming - pointers, function pointers and simple data structures

Task 1a:Print unsinged

main:
toy_printf("Hex unsigned: %x\n", -1);
toy_printf("Octal unsigned: %o\n", -1);

#> main
Hex unsigned: ffffffff
Octal unsigned: 37777777777
#> 

T1b- Print unsigned integers

main:
toy_printf("Unsigned value: %u\n", 15);
toy_printf("Unsigned value: %u\n", -15);

#> main
Unsigned value: 15
Unsigned value: 4294967281
#> 

T1c - Printing arrays

main:
int integers_array[] = {1,2,3,4,5};
char * strings_array[] = {"This", "is", "array", "of", "strings"};
int array_size = 5;
toy_printf("Print array of integers: %Ad\n", integers_array, array_size);
toy_printf("Print array of strings: %As\n", strings_array, array_size);

#> main
Print array of integers: {1, 2, 3, 4, 5}
Print array of strings:  {This,  is,  array,  of,  strings}
#> 

T1d - The Width Field

main:
toy_printf("Non-padded string: %s\n", "str");
toy_printf("Right-padded string: %6s\n", "str");
toy_printf("Left-added string: %-6s\n", "str");

#> main
Non-padded string: str
Right-padded string: str   #
Left-padded string:    str
#>

main:
toy_printf("With numeric placeholders: %05d\n", -1);

#> main
With numeric placeholders: -0001
#>

