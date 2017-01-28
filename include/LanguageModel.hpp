#ifndef LANGUAGE_MODEL_HPP
#define LANGUAGE_MODEL_HPP

#include <iostream>
#include <fstream>
#include "NgramCollection.hpp"

class LanguageModel{

public:
  LanguageModel(unsigned N): coll(N){};//constructor
  
  void addWords(std::string fileName);//adds one vector of words to the language model

  std::vector<std::string> getFileNames(std::string fileName)const;//outputs vector of filenames

  std::string printModel(char option) const;//calls toString method of NgramCollection and prints the str

  std::string makeDocument()const;//uses getWord of NgramCollection to make a document

private:
  NgramCollection coll;
  
};

#endif
