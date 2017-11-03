#include "inc/descompress.h"
#include "inc/compress.h"

void print_ajuda(); // Shows how to use the program.

int main(int argc, char *argv[]) {
	switch (argc) {
		case 1:
		case 2:
			print_ajuda();
			break;
		default:
			if (!strcmp(argv[1], "h")) {
				print_ajuda();
			} else if (!strcmp(argv[1], "c")) {
        int i;
        for (i = 2; i < argc; i++) {
					compress(argv[i]);
				}
			} else if (!strcmp(argv[1], "d")) {
        int i;
        for (i = 2; i < argc; i++) {
					descompress(argv[i]);
				}
			}
			break;

	}

	return 0;
}

void print_ajuda()
{
	printf("\nInstructions:\n\n\tbuild <mode> [<names>]\n\n<mode>\t\\c\tTo"
	" compress a file. Should be followed <name>.\n\t\\d\tTo"
	" descompress a file. Should be followed <name>.\n\t\\h\tTo show "
	"help function. Shouldn't be followed <name>.\n\n<names>\tFile relative addres "
	" or file(s) absolut which will be compress/de"
	"scompress with the extesion.\n\n");
}
