#include <gtest/gtest.h>
#include "combiner.h"

TEST(CombineTest, WordExtractor) {
	std::string s = ",Cette phase a,5,mots";
	VecString v(Combiner::extractWords(s));
	EXPECT_EQ(v.size(), 5);
	EXPECT_TRUE( (v.at(0) == "Cette") );
	s = "Par  ,contre,, celle la en a 7";
	v = Combiner::extractWords(s);
	EXPECT_EQ(v.size(), 7);
}

TEST(CombineTest, AddGroupFile) {
	Combiner cmb;
	int i(cmb.addGroup("noncutting.txt"));
	EXPECT_EQ(i, 11);
}

TEST(CombineTest, Crossing) {
	Combiner cmb;
	VecString vec;
	vec.push_back("EcoRV");vec.push_back("SDSPAGE");vec.push_back("RBS");
	vec.push_back("EcoRI");vec.push_back("mRNA");vec.push_back("DNA");
	cmb.addGroup(vec);
	vec.clear();
	vec.push_back("EcoRV");
	cmb.addGroup(vec);
	VecString c(cmb.cross());
	EXPECT_EQ(c.size(), 1);
	EXPECT_TRUE(c[0] == "EcoRV");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
