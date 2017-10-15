#include "inc/descompress.h"
#include "inc/compress.h"

/*
 * Writes program help on standard output.
 */
void print_ajuda();

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
	printf("\nForma de usar:\n\n\tbuild <modo> [<nomes>]\n\n<modo>\t\\c\tPa"
	"ra comprimir um arquivo. Deve ser seguido de <nome>.\n\t\\d\tPara desc"
	"omprimir um arquivo. Deve ser seguido de <nome>.\n\t\\h\tPara mostrar "
	"essa ajuda. Não deve ser seguido de <nome>.\n\n<nomes>\tCaminho(s) rel"
	"ativo(s) ou absoluto(s) do(s) arquivo(s) que sera(ão) comprimido(s)/de"
	"scomprimido(s) com extensão.\n\n");
}
