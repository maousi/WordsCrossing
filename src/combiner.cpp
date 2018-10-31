#include "combiner.h"
#include <fstream>
#include <iostream>
#include <tclap/CmdLine.h>

Combiner::Combiner(int argc, char** argv) : mData(new VecVecString) {
	TCLAP::CmdLine cmd("Combiner");
    TCLAP::UnlabeledMultiArg<std::string> arg_multi("Name", "Class name and "
    "optionaly destination path for writing", true, "string");
    cmd.add(arg_multi);
    cmd.parse(argc, argv);
    
	std::vector<std::string> multi(arg_multi.getValue());
	for(auto s : multi)
		addGroup(s);
	VecString vec(cross());
	std::cout << vec.size() <<  " words in common :\n\n";
	for(auto s : vec)
		std::cout << s << ", ";
	std::cout<<std::endl;
}

Combiner::~Combiner() {
	delete mData;
}

int Combiner::addGroup(const std::string &fName, bool inclusion) {
	std::string content(extractFromFile(fName));
	VecString vec( extractWords(content) );
	mData->push_back( vec );
	std::cout<<vec.size() << " words added\t\t("<<fName<<")" << "\n";
	return vec.size();
}

void Combiner::addGroup(const VecString &vec, bool inclusion) {
	mData->push_back(vec);
}

VecString Combiner::cross() const {
	VecString vec;
	// le vecteur 0 est la 'référence'
	const VecString &v0(mData->at(0));
	int s(v0.size()), d(mData->size());
	if(d == 1) // il faut plusieurs groupes pour comparer
		throw std::string("You must add more than 1 file to compare");
	// pour chaque mot du 1e vecteur on itère sur tous les autres pour trouver le mot
	for(int i(0); i < s; i++) { // itération des mots du 1e vec
		std::string word(v0[i]);
		// on itère sur les autre vecteurs pour trouver le mot
		int found_count(0);
		for(int j(1); j < d; j++) {
			const VecString &v_j(mData->at(j));
			int K(v_j.size());
			bool word_found_in_vector_j(false);
			for(int k(0); k < K; k++){ // on itère sur les mots k du vecteur
				if(v_j[k] == word)
					word_found_in_vector_j = true;
			}
			if(word_found_in_vector_j)
				found_count++;
		}
		// on doit verifier que le mot du vec0 est dans tous les autres vecteurs
		if(found_count == d-1)
			vec.push_back(word);
	}
	
	return vec;
}

VecString Combiner::extractWords(const std::string &t) {
	VecString vec;
	size_t s(t.size());
	std::string current;
	for(size_t i(0); i < s; i++) {
		char c(t[i]);
		if( (c == ',' or c == ' ')) {
			if(current.size() != 0) {				
				vec.push_back(current);
				current.clear();
			}
		} else
			current += c;
	}
	// ADDING LAST WORD
	//current.erase(' ');current.erase(',');
	if(current.size() != 0)
		vec.push_back(current);
		
	//for(std::string x : vec) std::cout<<x<<std::endl;
	return vec;
}

std::string Combiner::extractFromFile(const std::string &fName) {
	// testing if file exists
	if(!std::ifstream(fName).good())
		throw std::string("File '" + fName+ "' does not exist");
	std::ifstream reader;
	reader.open(fName);
	if(!reader.is_open())
		throw std::string("File '" + fName+ "' cannot be opened");
	std::string line, fileContent;
	while( getline( reader, line )) {
		fileContent += line;
	}
	reader.close();
	return fileContent;
}
