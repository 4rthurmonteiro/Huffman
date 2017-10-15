#include "inc/compress.h"



void compress(char *to_encode_name){

	if (to_encode_name != NULL) {
		FILE *to_encode = NULL;
		FILE *encoded = NULL;


		to_encode = fopen(to_encode_name, "rb");

		if (to_encode != NULL) {

			hashTable_t *hash = createHash();

			huffmanTree_t *tree = createBinaryTree();

			char *encoded_name = (char *) calloc(strlen(to_encode_name) + 6,sizeof(char));


			strcpy(encoded_name, to_encode_name);

			strcat(encoded_name, ".huff");


			encoded_name[strlen(to_encode_name) + 6] = '\0';


			encoded = fopen(encoded_name, "wb");

			printf("\nComprimindo: %s\n", to_encode_name);
			printf("\nPegando Frequências...\n\n");

			getFrequency(to_encode, hash);
			printf("\nFormando a arvore...\n");

			hashTree(tree, hash);
			printf("\n\tPronto\n");
			printf("\nFormando Códigos...\n");

			setLeaf(tree);
			printf("\n\tPronto\n");
			printf("\nComprimindo...\n\n");

			saveCompress(to_encode, encoded, hash, tree);
			printf("\nArquivo Comprimido com Sucesso\n\n");

			fclose(to_encode);
			fclose(encoded);

			free(encoded_name);

			destroyHash(&hash);
			destroyBinaryTree(&tree);
		} else {
			printf("\nO arquivo %s não foi encontrado.\n\n", to_encode_name);
		}
	}
}

void getFrequency(FILE *src, hashTable_t *hash){

	if (src != NULL && hash != NULL) {
		unsigned char buffer;


		fread(&buffer, sizeof(unsigned char), 1, src);


		while (!feof(src)) {

			put(hash, buffer);

			fread(&buffer, sizeof(unsigned char), 1, src);
		}


		fseek(src, 0, SEEK_SET);
	}
}

void hashTree(huffmanTree_t *tree, hashTable_t *hash){

	if (tree != NULL && hash != NULL) {

     short int i;
		for (i = 0; i < 256; i++) {

			add(tree, get(hash, i));
		}

		forest(tree);
	}
}

void saveCompress(FILE *src, FILE *dest, hashTable_t *hash, huffmanTree_t *tree){

	if (src != NULL && dest != NULL && hash != NULL && tree != NULL) {
		unsigned char buffer;


		unsigned short int header = 0;

		unsigned short int data = 0;

		short int s = 8;


		fwrite(&header, sizeof(unsigned short int), 1, dest);


		saveHuffmanTree(tree, dest);


		fread(&buffer, sizeof(unsigned char), 1, src);


		while (!feof(src)) {

			char *tmp = representation(get(hash, buffer));


       short int i;
			for (i = 0; i < strlen(tmp); i++) {
				if (tmp[i] == '1') {

					data = bitSet(data, --s);
				} else if (tmp[i] == '0') {

					--s;
				}


				if (s == 0) {
					fwrite(&data, sizeof(unsigned char), 1, dest);


					data = 0;
					s = 8;
				}
			}


			fread(&buffer, sizeof(unsigned char), 1, src);
		}


		if (s != 8) {
			fwrite(&data, sizeof(unsigned char), 1, dest);
		} else {

			s = 0;
		}


		fseek(dest, 0, SEEK_SET);

		header = (s << 13 | numberOfNodes(tree));


		fwrite(&header, sizeof(unsigned short int), 1, dest);
	}
}

unsigned char bitSet(unsigned char base, short int i)
{

	unsigned char mask = 1 << i;

	return base | mask;
}
