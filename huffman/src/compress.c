#include "inc/compress.h"

void compress(char *toCompressFile){ // Enter with the file to be compressed.

	if (toCompressFile != NULL) { // check if the file is valid.
		FILE *toCompress = NULL; // Creates toCompress file.
		FILE *compressed = NULL; // Creates compressed file.


		toCompress = fopen(toCompressFile, "rb"); // Read the file in "rb" mode, opening non-text files, that is the binaries.

		if (toCompress != NULL) { // check if the file is ok.

			hashTable_t *hash = createHash(); // creates the hash table.

			huffmanTree_t *tree = createBinaryTree(); // creates the tree.

			/*
					Allocates memory to the new name of the file, with the extension ".huff" added.
			*/
			char *compressedFile = (char *) calloc(strlen(toCompressFile) + 6,sizeof(char));


			strcpy(compressedFile, toCompressFile); // Copies the source string to compressedFile.

			strcat(compressedFile, ".huff"); // puts the huffman extension.

			compressedFile[strlen(toCompressFile) + 6] = '\0'; // Cuts the string with "\0".

			compressed = fopen(compressedFile, "wb"); // Write the file in "wb" mode, writing the binaries to compressed file.

			printf("\nCompressing: %s !!!\n", toCompressFile);
			printf("\nPicking up the frequencies ...\n\n");

			getFrequency(toCompress, hash); // Catch the frequency of each byte of a file and saves it in a hash table.
			printf("\nForming the tree...\n");

			hashTree(tree, hash); // Catch each item from the hash table and transforms it in a tree strictly binary tree.
			printf("\n\tFirst Steps Ok!\n");
			printf("\nForming Huffman Codes...\n");

			setLeaf(tree); //
			printf("\n\tHuffman Codes Ok!\n");
			printf("\nCompressing...\n\n");

			saveCompress(toCompress, compressed, hash, tree); // Saves the file with the new codes.
			printf("\nFile Compressed!!!!!\n\n");

			fclose(toCompress); //  closes the stream. All buffers are flushed.
			fclose(compressed); //  closes the stream. All buffers are flushed.

			free(compressedFile); // free memory.

			destroyHash(&hash); // destroy the hash and pointer to NULL.
			destroyBinaryTree(&tree); // destroy the tree and pointer to NULL.
		} else {
			printf("\nThe file %s wasn't found.\n\n", toCompressFile);
		}
	}
}

/*
    Catch the frequency of each byte of a file and saves it in a hash table.

		MORE ABOUT THIS FUNCTION: open "compress.h" file.
*/
void getFrequency(FILE *src, hashTable_t *hash){

	if (src != NULL && hash != NULL) { // check if the arguments are valid.
		unsigned char buffer; // the buffer which will used to reads the datas from the source.

		fread(&buffer, sizeof(unsigned char), 1, src); // Reads data from src into the unsigned char buffer.


		while (!feof(src)) { // check the loop until the end-of-file.

			put(hash, buffer); // Puts a item in the Hash.

			fread(&buffer, sizeof(unsigned char), 1, src); // Reads the next data from src into the unsigned char buffer.
		}


		fseek(src, 0, SEEK_SET); // sets the file position to the beginnig of file (SEEK_SET) with offset "0".
	}
}


/*
		Catch each item from the hash table and transforms it in a tree strictly binary tree.

		MORE ABOUT THIS FUNCTION: open "compress.h" file.
*/
void hashTree(huffmanTree_t *tree, hashTable_t *hash){

	if (tree != NULL && hash != NULL) { // check if the arguments are valid.

    short int i; // loop aux.

		/*
			The hash table has exactly 256 elements because are the maximum number of
			elements in the ASCII table (the possibility of differents bytes).
		*/
		for (i = 0; i < 256; i++) {
			add(tree, get(hash, i)); // Puts the node in the tree, AS LINKED LIST AND IN A ORDERED WAY.
		}

		forest(tree); // Transform a "tree linked list" in a strictly binary tree, like the huffman algorithm demands.
	}
}


/*
    Saves the file with the new codes.

		MORE ABOUT THIS FUNCTION: open "compress.h" file.
*/
void saveCompress(FILE *src, FILE *dest, hashTable_t *hash, huffmanTree_t *tree){

	if (src != NULL && dest != NULL && hash != NULL && tree != NULL) { // check if the arguments are valid.
		unsigned char buffer; // the buffer which will used to reads the datas from the source.

		unsigned short int header = 0; // header of the huffman, the first two bytes.

		unsigned short int data = 0; // byte which will be saved in the output file.

		short int s = 8; // This controls in which bit of the Byte that will be written to the output file. Also get the amount of "bits trash".

		fwrite(&header, sizeof(unsigned short int), 1, dest); // Writes two bytes to the header.

		saveHuffmanTree(tree, dest); // Saves the nodes items from a tree in preorder to a file.

		fread(&buffer, sizeof(unsigned char), 1, src); // Reads the first byte from src into the unsigned char buffer.

		while (!feof(src)){ // check the loop until the end-of-file.

			char *tmp = representation(get(hash, buffer)); //  Takes the representation from the hash table node, temp is the byte which was read.

      short int i; // loop aux.

			/*
			Works in position by position of the string and "build"
			the byte which will be saved into the output file
			*/
			for (i = 0; i < strlen(tmp); i++) {
				if (tmp[i] == '1') {

					data = bitSet(data, --s); // Sets and go to the next.
				} else if (tmp[i] == '0') {

					--s; // just go to the next
				}


				if (s == 0) { // If true the "build" was finished. So its time to save the data in the output file.
					fwrite(&data, sizeof(unsigned char), 1, dest); // writes "data" to dest.

					data = 0; // restart data.
					s = 8; // restart s.
				}
			}


			fread(&buffer, sizeof(unsigned char), 1, src); // reads the next byte.
		}


		if (s != 8) { // checking the last byte from the source file.
			fwrite(&data, sizeof(unsigned char), 1, dest); // writes the last byte.
		} else {

			s = 0;
		}


		fseek(dest, 0, SEEK_SET); // goes to the beginnig of the dest file.
		header = (s << 13 | numberOfNodes(tree)); // Define the two first bytes.

		fwrite(&header, sizeof(unsigned short int), 1, dest); // puts the header in the file.
	}
}

/*
    Shows if the byte picked was set.

		MORE ABOUT THIS FUNCTION: open "compress.h" file.
*/
unsigned char bitSet(unsigned char base, short int i)
{

	unsigned char mask = 1 << i;

	return base | mask;
}
