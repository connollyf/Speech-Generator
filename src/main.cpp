

#include "../include/LanguageModel.hpp"
#include <iostream>

int main(int argc, char* argv[]){

  if(argc != 4 && argc != 5){//checks number of args
    std::cout << "Invalid num of args\n";
    return 0;
  }

  LanguageModel model(atoi(argv[2]));//initiates NgramCollection with command line number
  std::vector<std::string> fileNames = model.getFileNames(argv[1]);//create vector of filenames
  for(std::string i : fileNames){
    model.addWords(i);
  }

  char choice = argv[3][0];

  if(choice == 'a'){//alphabetical output
    std::cout << model.printModel(choice);
  }else if(choice == 'r'){//reverse alphabetical output
    std::cout << model.printModel(choice);
  }else if(choice == 'c'){//count output
    std::cout << model.printModel(choice);
  }else if(choice == 'g'){//generate sentences
    for(int i = 0; i < atoi(argv[4]); i++){//generate number of sentences they specified
      std::cout << model.makeDocument() << "\n";
    }
  }else{
    std::cout << "Invalid input\n";
  }

  return 0;
}
