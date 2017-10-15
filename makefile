CC = clang
FLG = -std=c11 -Wall

HUFF = huffman/
SRCD = $(HUFF)src/
INCD = $(SRCD)inc/

SRC = $(wildcard $(SRCD)*.c)
OBJ = $(SRC:.c=.o)

all: build

build: $(SRCD)main.o
	@echo "Compilando Executável..."
	@$(CC) $(FLG) $(OBJ) -o $(HUFF)$@
	@echo "\tPronto"

$(SRCD)huffmanComponents.o: $(SRCD)huffmanComponents.c $(INCD)huffmanComponents.h
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)node.o: $(SRCD)node.c $(INCD)node.h $(SRCD)huffmanComponents.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)hashTable.o: $(SRCD)hashTable.c $(INCD)hashTable.h $(SRCD)node.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)huffmanTree.o: $(SRCD)huffmanTree.c $(INCD)huffmanTree.h $(SRCD)node.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)compress.o: $(SRCD)compress.c $(INCD)compress.h $(SRCD)hashTable.o $(SRCD)huffmanTree.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)descompress.o: $(SRCD)descompress.c $(INCD)descompress.h $(SRCD)huffmanTree.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

$(SRCD)main.o: $(SRCD)main.c $(SRCD)compress.o $(SRCD)descompress.o
	@echo "Compilando Objeto: $@"
	@$(CC) $(FLG) -c $< -o $@

rebuild: clean build

clean:
	@echo "Limpando diretório..."
	@rm $(SRCD)*.o -f
	@echo "\tPronto"
