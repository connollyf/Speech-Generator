

#include "../include/NgramCollection.hpp"
#include <algorithm>
#include <iostream>
 

std::string NgramCollection::toStringAlpha()const{
  
  std::string str = "";

  for(auto itera = counts.begin(); itera != counts.end(); itera++){//iterate through map
    for(auto iterb = (itera->second).begin(); iterb != (itera->second).end(); iterb++){//iterate through counts and word choices
      for(auto iterc = (itera->first).begin(); iterc != (itera->first).end(); iterc++){//iterate through vector
	str+=(*iterc);//add vector words
	str+=" ";
      }
      str+= iterb->first;//add word in second map
      str+=" ";
      str+= std::to_string(iterb->second);//add count
      str+="\n";
    }
  }
  return str;
}

std::string NgramCollection::toStringReverseAlpha()const{

  std::string str = "";

  for(auto ritera = counts.rbegin(); ritera != counts.rend(); ritera++){//iterate backwards through counts
    for(auto iterb = (ritera->second).begin(); iterb != (ritera->second).end(); iterb++){//iterate forwards through counts and word choices
      for(auto iterc = (ritera->first).begin(); iterc != (ritera->first).end(); iterc++){//iterate forwards through vectors
	str+=(*iterc);//add vector words
	str+=" ";
      }
      str+= iterb->first;//add words in second map
      str+=" ";
      str+= std::to_string(iterb->second);//add count
      str+="\n";
    }
  }
  return str;
}

bool countSort(std::tuple<std::vector<std::string>, unsigned> a, std::tuple<std::vector<std::string>, unsigned> b){

  if(std::get<1>(a) < std::get<1>(b)){//compare counts
    return true;
  }else if(std::get<1>(a) == std::get<1>(b)){//if equal
    int index = 0;
    while(std::get<0>(a).at(index) == std::get<0>(b).at(index)){//if equal keep cycling through words until the two words aren't equal
      index++;
    }
    return std::get<0>(a).at(index) < std::get<0>(b).at(index);//return if first word < second word
  }
  return false;//if b < a
}

std::string NgramCollection::toStringCount()const{

  std::string str = "";
  std::vector<std::tuple<std::vector<std::string>, unsigned>> lines{};

  for(auto itera = counts.begin(); itera != counts.end(); itera++){//iterate through map
    for(auto iterb = (itera->second).begin(); iterb != (itera->second).end(); iterb++){//iterate through counts and word choices
      std::vector<std::string> thisLine = itera->first;//create vector of the word choices
      thisLine.push_back( iterb->first);
      std::tuple<std::vector<std::string>, unsigned> lineAndCount = std::make_tuple(thisLine, iterb->second);//makes tuple using lines and count
      lines.push_back(lineAndCount);//make vector of tuples above
    }
  }

  std::sort(lines.begin(), lines.end(), countSort);//sort tuples by count
  for(auto iter = lines.begin(); iter != lines.end(); iter++){
    for(std::string word: std::get<0>(*iter)){//convert tuple vector into str
      str+=word;
      str+=" ";
    }
    str+=std::to_string(std::get<1>(*iter));
    str+="\n";
  }

  return str;
}

std::string NgramCollection::toString(char order)const{ 

  if(order == 'a'){//alphabetic
    return toStringAlpha();
  } else if(order == 'r'){//reverse alphabetic
    return toStringReverseAlpha();
  } else if(order == 'c'){//count
    return toStringCount();
  }
  return "ERROR: INVALID ARG";

}




void NgramCollection::increment(std::vector<std::string>::const_iterator begin,
	       std::vector<std::string>::const_iterator end){

  int ni = (int) n;//int of n
  
  for(std::vector<std::string>::const_iterator iter = begin; iter != (end - ni + 1); iter++){//loops through vector up until n from the end

    std::vector<std::string> entry{};
    for(int i = 0; i < (ni-1); i++){//constructs vector that will be a key in counts
      entry.push_back(*(iter + i));
    }
    if(counts.find(entry) != counts.end()){//checks if counts has this key
      if(counts[entry].find(*(iter + ni - 1)) != counts[entry].end()){//checks if counts has this vaue
	counts[entry][*(iter + ni - 1)]++;//increments count
      } else {
	counts[entry][*(iter + ni - 1)] = 1;//sets count to 1
      }
    } else {//if counts doesn't have this key
      std::map<std::string, unsigned> wordFreq{};
      wordFreq[*(iter + ni - 1)] = 1;//create a map with the last word and a count of 1
      counts[entry] = wordFreq;//set that key value equal to the map
    }
  }
}


std::string NgramCollection::pickWord(std::list<std::string>::const_iterator begin,
		     std::list<std::string>::const_iterator end)const{


  
  
  std::vector<std::string> line{};
  while(begin != end){//creates vector from list
    line.push_back(*begin);
    //std::cout << *begin << "|";
    begin++;
  }

  
  std::map<std::string, unsigned> choicesMap = counts.at(line);//gets map


  std::vector<std::string> choicesVector{};

  for(auto iter = choicesMap.begin(); iter != choicesMap.end(); iter++){//creates vector of choices for next word
    for(int i = 0; i < (int)iter->second; i++){
      choicesVector.push_back(iter->first);
    }
  }

  return choicesVector.at(rand() % choicesVector.size());
}

  
						   
