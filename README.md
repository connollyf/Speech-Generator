# Speech-Generator
A program that generates speech using an ngram algorithm

The program takes 3 arguments

The first argument is the size of the ngrams, increasing this will make the generated speech more lifelike

The second argument is a path to a text file with the list of filenames you want the speech to be based on

The third argument is a character specifiying what you want the program to do
a: outputs an alphabetical ngram model of the basis text
r: outputs a reverse alphabetical ngram model of the basis text
c: outputs an ngram model of the basis text sorted by how often the ngram appears
g: generates speech (you can also put a 4th argument to specify the number of paragraphs)
