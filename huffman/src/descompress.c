#include "inc/descompress.h"

void descompress(char *to_decode_name){

	if (to_decode_name != NULL) {
		FILE *to_decode = NULL;
		FILE *decoded = NULL;


		to_decode = fopen(to_decode_name, "rb");

		if (to_decode != NULL) {

			unsigned short int header;

			unsigned short int trash;

			unsigned short int tree_size;


			huffmanTree_t *tree = createBinaryTree();

			char *decoded_name = (char *) calloc(strlen(to_decode_name),sizeof(char));

			strcpy(decoded_name, to_decode_name);


			decoded_name[strlen(to_decode_name) - 5] = '\0';


			decoded = fopen(decoded_name, "wb");

			fread(&header, sizeof(unsigned short int), 1, to_decode);


			trash = header >> 13;

			tree_size = header << 3;

			tree_size = tree_size >> 3;

			printf("\nDescomprimindo: %s\n", to_decode_name);
			printf("\nFormando a arvore...\n");

			getBinaryTree(tree, to_decode, tree_size);
			printf("\n\tPronto\n");
			printf("\nDescomprimindo...\n\n");

			saveDecompress(to_decode, decoded, tree, trash);
			printf("\nArquivo Descomprimido com Sucesso\n\n");

			fclose(to_decode);
			fclose(decoded);

			free(decoded_name);

			destroyBinaryTree(&tree);
		} else {
			printf("\nO arquivo %s não foi encontrado.\n\n", to_decode_name);
		}
	}
}

void getBinaryTree(huffmanTree_t *tree, FILE *src, unsigned short int tree_size)
{

	if (tree != NULL && src != NULL) {

		if (tree_size > 1) {
			add(tree, getNode(src));
		} else {

			add(tree, createNode(AUX, 0, getNode(src), NULL));
		}
	}
}

void saveDecompress(FILE *src, FILE *dest, huffmanTree_t *tree, unsigned short int trash)
{

	if (src != NULL && dest != NULL && tree != NULL) {
		unsigned char buffer;

		node_t *tmp = root(tree);


		fread(&buffer, sizeof(unsigned char), 1, src);


		while (!feof(src)) {
			unsigned char aux;


			fread(&aux, sizeof(unsigned char), 1, src);


       short int i;
			for (i = 7; i >= 0; i--) {

				if (!feof(src) || trash <= i) {

					if (isBitSet(buffer, i)) {

						tmp = right(tmp);
					} else {

						tmp = left(tmp);
					}


					if (isLeaf(tmp)) {

						unsigned char aux_tmp = item(tmp);

						tmp = root(tree);


						fwrite(&aux_tmp, sizeof(unsigned char) , 1, dest);
					}
				}

			}


			buffer = aux;
		}
	}
}

bool isBitSet(unsigned char base, short int i){

	unsigned char mask = 1 << i;

	return base & mask;
}
