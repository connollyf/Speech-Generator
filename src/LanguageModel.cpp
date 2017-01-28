

#include "../include/LanguageModel.hpp"


std::vector<std::string> LanguageModel::getFileNames(std::string fileName)const{
  
  std::ifstream ifs;
  ifs.open(fileName.c_str(), std::ios::in);//opens filename that was passed as arg

  std::vector<std::string> fileNames{};
  std::string thisFileName;
  
  while(ifs >> thisFileName){
    fileNames.push_back(thisFileName);//adds filename to lsit
  }

  ifs.close(); //closes file
  return fileNames;
}


void LanguageModel::addWords(std::string fileName){

  std::vector<std::string> wordsForBigram{};

  for(int i = 1; i < (int)coll.getN(); i++){//adds start words e.g. <START_1>, <START_2>
    std::string startString = "<START_" + std::to_string(i) + ">";
    wordsForBigram.push_back(startString);//
  }

  std::ifstream ifs;
  ifs.open(fileName.c_str(), std::ios::in);//opens file

  std::string wordFromFile;

  while(ifs >> wordFromFile){//while there are still words in the file, adds them to vector
    wordsForBigram.push_back(wordFromFile);
  }

  for(int i = 1; i < (int)coll.getN(); i++){
    std::string endString = "<END_" + std::to_string(i) + ">";//adds <END> strings
    wordsForBigram.push_back(endString);
  }

  coll.increment(wordsForBigram.cbegin(), wordsForBigram.cend());//adds the words in the vector to the Ngram collection

}

std::string LanguageModel::printModel(char order)const{
  return coll.toString(order);//calls Ngram function
}

std::string LanguageModel::makeDocument()const{

  std::list<std::string> document{};
  std::string docString = "";

  for(int i = 1; i < (int)coll.getN(); i++){
    std::string startString = "<START_" + std::to_string(i) + ">";
    document.push_back(startString);//adds <START_X>'s to list
    docString+=startString;//adds <START_X>'s to string
    docString+=" ";
  }

  int endNum = ((int)coll.getN()) - 1;//number of last <END> tag
  std::string endString = "<END_" + std::to_string(endNum)+ ">";//creates last end tag to look for

  while(document.back() != endString){//while the last word in the list isn't <END_N-1>
    std::string wordGotten =  coll.pickWord(document.begin(), document.end());//generates word from list
    docString+=wordGotten;//adds word generated to string
    docString+= " ";
    document.push_back(wordGotten);//adds new word to list
    document.pop_front();//removes oldest word to list
  }
  return docString;
}
