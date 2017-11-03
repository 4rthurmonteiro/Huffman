# Huffman Project

The huffman algorithm is used to compress files and descompress files with .huff extension. In this project was used 3 types of data structures to create this software:

    * Linked List.
    * Hash Table.
    * Binary Tree.

Using the huffman algorithm is possible reach 40% of compressing!!!

Compressing...

  The ideia is to read the input bytes files and put them into a hash table with 256 nodes, that's the number of elements um ASCII table, so its the size of the hash table. After that we catch the frequencies of the bytes in the hash table and forms a ordered linked list and call a function called "forest" to transform the linked list in a strictly binary tree. With the Huffman Tree formed, its time do set de new codes using the "setLeaf" function and save them using "saveCompress".
    "SaveCompress" fuction is where the program define the header, with the tree size and the trash, and puts the new codes in the output file.
    At the end if the file passed is non-NULL the output file is compressed with the same name but the extension ".huff" added.

Descompressing...

   First the extesion ".huff" is cut. After that the program catch up the header (two first bytes in the input file) and separe the trash and the tree size.
    So after that the function "getBinaryTree" is called to to build the tree with the bytes compressed.
    To finish the program call "saveDescompress" function, this function change the codes compressed to the standard codes, so the file is decompressed with the same size before.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

To use the program it's simples. Open the terminal in the paste ../huffman and run this command to see the instructions:

```
./build
```

### Prerequisites

To run this project it's necessary install the Clang 3-x.

You can install in terminal with this commands:

```
sudo apt-get update
sudo apt-get install clang-3.n
```

### Installing

In the Huffman paste, that's contains Comparaton, Teste_CUnit and huffman, open the terminal and puts this command:

```
make
```

So the build software is ready to be run in the /huffman paste.

## Running 

Like the "Getting Started" topic you have just to do this commands:

to compress:

```
./build c "the file addres and name with the extesion"
```
Example:

```
./build c /home/arthur/Downloads/ArduinoProKicad-master/ArduinoPro.kicad_pcb-bak
```

to descompress:
```
./build d "the file addres and name with the extesion and the .huff"
```

Example:

```
./build d /home/arthur/Downloads/ArduinoProKicad-master/ArduinoPro.kicad_pcb-bak.huff
```

## Authors

* **Arthur Monteiro Alves Melo** - *Computer Engineer** - https://github.com/4rthurmonteiro

* **Alvino Lessa** - *Computer Engineer** - https://github.com/AlvinoL

* **Edvonaldo Horácio** - *Computer Engineer** - https://github.com/NaldoHoracio

"*" - In progress :). 

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
