#include "inc/descompress.h"

void descompress(char *toDescompressFile){ // Enter with the file to be descompressed.

	if (toDescompressFile != NULL) { // check if the file is valid.
		FILE *toDescompress = NULL; // Creates toDescompress file.
		FILE *descompress = NULL; // Creates descompress file.


		toDescompress = fopen(toDescompressFile, "rb"); // Read the file in "rb" mode, opening non-text files, that is the binaries.

		if (toDescompress != NULL) { // check if the file is ok.

			unsigned short int header; // The two first bytes.

			unsigned short int trash; // The trash bits.

			unsigned short int tree_size; // The tree size.


			huffmanTree_t *tree = createBinaryTree(); // creates the tree.

			/*
			   Allocates memory for the string to put the name of
			   the output file, which is the input file
			   name without ".huff" at the end.
			 */
			char *descompressedFile = (char *) calloc(strlen(toDescompressFile),sizeof(char));

			strcpy(descompressedFile, toDescompressFile); // Copies the source string to descompressedFile.

			descompressedFile[strlen(toDescompressFile) - 5] = '\0'; // Takes off the extension ".huff",

			descompress = fopen(descompressedFile, "wb"); // Write the file in "wb" mode, writing the binaries to descompressed file.

			fread(&header, sizeof(unsigned short int), 1, toDescompress); // Reads the header.

			trash = header >> 13; // gets the trash.

			tree_size = header << 3; // gets the bits which has the tree size information.

			tree_size = tree_size >> 3; // Adjust the bytes.

			printf("\nDescompressing: %s !!!\n", toDescompressFile);
			printf("\nForming the tree...\n");

			getBinaryTree(tree, toDescompress, tree_size); // This function catch/build the tree which was created to compress the file.
			printf("\nFirst Steps Ok!\n");
			printf("\nnDescompressing...\n\n");

			saveDecompress(toDescompress, descompress, tree, trash); // Saves the file using the standard codes.
			printf("\nFile Descompressed!!!!!\n\n");

			fclose(toDescompress); //  closes the stream. All buffers are flushed.
			fclose(descompress); //  closes the stream. All buffers are flushed.

			free(descompressedFile); // free memory.

			destroyBinaryTree(&tree); // destroy the tree and pointer to NULL.
		} else {
			printf("\nhe file %s wasn't found.\n\n", toDescompressFile);
		}
	}
}

/*
    This function catch/build the tree which was created to compress the file.

		MORE ABOUT THIS FUNCTION: open "descompress.h" file.
*/
void getBinaryTree(huffmanTree_t *tree, FILE *src, unsigned short int tree_size)
{

	if (tree != NULL && src != NULL) { // check if the arguments are valid.

		if (tree_size > 1) { // if the tree_size is greater than one, adds the returned node by getNode(See node.h to more information) in the tree.
			add(tree, getNode(src)); // Puts the node in the tree, AS LIST AND IN A ORDERED WAY.
		} else {
			/*
				If the tree_size isn't greather than one,
				adds the node which is the auxiliary item "*" with only the left child
				which is returned by getNode.
			*/
			add(tree, createNode(AUX, 0, getNode(src), NULL)); // Puts the node in the tree, AS LIST AND IN A ORDERED WAY.
		}
	}
}

/*
    Saves the file using the standard codes.

		MORE ABOUT THIS FUNCTION: open "descompress.h" file.
*/
void saveDecompress(FILE *src, FILE *dest, huffmanTree_t *tree, unsigned short int trash)
{

	if (src != NULL && dest != NULL && tree != NULL) { // check if the arguments are valid.
		unsigned char buffer; // the buffer which will used to reads the datas from the source.

		node_t *tmp = root(tree); // Starts in the root of the tree.

		fread(&buffer, sizeof(unsigned char), 1, src); // Reads the first byte data from src into the unsigned char buffer.


		while (!feof(src)) { // checks the loop until the end-of-file.
			unsigned char aux;

			/*
			  Tries to read the byte that follow the last read
			  Byte, it serves to know if the last Byte read was the
			  last one of the file, only in that case we consider
			  the amount of "trash bits".
			*/
			fread(&aux, sizeof(unsigned char), 1, src);

      short int i; // loop aux.
			for (i = 7; i >= 0; i--) { // checks each bit of the read file.

				/*
					To do not check the "trash bits", if the
					end-of-file flag was not raised we check all
					the bits of the read byte, but if it was
					raised then we only check until the last bit
					before the "trash bits".
				*/
				if (!feof(src) || trash <= i) {

					if (isBitSet(buffer, i)) { // checks if the bit is set or not.
						tmp = right(tmp); // if true puts in the right, like the huffman algorithm demands.
					} else {
						tmp = left(tmp); // if false, its "0", so puts in the left node.
					}

					if (isLeaf(tmp)) { // check if tmp is a leaf (no children nodes).

						unsigned char aux_tmp = item(tmp); // gets the item from the leaf.

						tmp = root(tree); // goes back to the root.

						fwrite(&aux_tmp, sizeof(unsigned char) , 1, dest); // wrties the leaf byte to the dest file.
					}
				}

			}

			buffer = aux; // Pass the byte previously read "aux" to the buffer.
		}
	}
}

/*
    Returns true if the i-th bit of a Byte is set and false otherwise.

		MORE ABOUT THIS FUNCTION: open "descompress.h" file.
*/
bool isBitSet(unsigned char base, short int i){

	unsigned char mask = 1 << i;

	return base & mask;
}
