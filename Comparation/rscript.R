setwd(dir = "/home/arthur/Documentos/UFAL/Huffman/Comparation")
data <- read.table("file.txt")

col2 <- data[,2]
col3 <- data[,3]

x <- 1:length(col2)

plot(x,col2, type='l', ylim=c(min(col2,col3),max(col2,col3)))
points(col3, type='l', col='red', lty=2)
