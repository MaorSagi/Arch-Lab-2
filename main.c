#include "toy_stdio.h"


int main(int argc, char *argv[]) {
toy_printf("Left-padded string: %-00006s\n", "str");
toy_printf("Right-padded string: %000006s\n", "str");
toy_printf("With numeric placeholders: %0005d\n", -1);
toy_printf("With numeric placeholders: %05d\n", 1);
toy_printf("With numeric placeholders: %05d\n", 0);
}
