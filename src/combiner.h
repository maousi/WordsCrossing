#ifndef COMBINER_H
#define COMBINER_H

#include <vector>
#include <string>
typedef std::vector<std::string> VecString; 
typedef std::vector< VecString > VecVecString; 

/*! This class is initially designed to cross lists of restrictions enzymes (contained in files)
 * 	for plasmid cloning design.\n
 * 
 * 	Use addGroups() to add different files, for example Gene_non_cutting_enzymes.txt, plasmid_enzymes.txt, ...
 *  Then the cross() function will return the words that are contained in all the added groups 
 */

class Combiner {

public:
	Combiner() : mData(new VecVecString) {}
	Combiner(int argc, char** argv);
	~Combiner();
	
//! Add a group of words. If file name provided, automatic recognition of words within file.

/*! @param fName file name
 *  @param vec vector of words
 *  @param inclusion specify if words must be contained in that group or note.
 */
	int addGroup(const std::string &fName, bool inclusion = true);
	void addGroup(const VecString &vec, bool inclusion = true);
	
//! Cross between all the groups
	VecString cross() const;
	
	static VecString extractWords(const std::string &t);

private:
//! Vectors representing groups of words (strings), which will then be compared
	VecVecString *mData;
	
	std::string extractFromFile(const std::string &fName);
/*! Recognizes words in a string, return them as a vector
 * 	Ignores spaces, uses coma ',' ad space ' ' as word separator
 */
};

#endif // COMBINER_H

