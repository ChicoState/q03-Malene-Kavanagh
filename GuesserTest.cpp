/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

//Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}


TEST(GuesserTest, case_sensitive_test){
	Guesser testobject("Test");
	ASSERT_FALSE(testobject.match("test"));
	ASSERT_EQ(testobject.remaining(), 2);
}

TEST(GuesserTest, different_test){
	Guesser object("different");
	ASSERT_FALSE(object.match("same"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, nothing_match_test){
	Guesser object("");
	object.match("");
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, nothing_fail_test){
	Guesser object("");
	ASSERT_FALSE(object.match("no_match"));

	ASSERT_EQ(object.remaining(),2);
}

TEST(GuesserTest, almost_test){  
	Guesser object("close");
	object.match("clos"); //  dist of 1
	object.match("closs"); //dist of 1
	ASSERT_TRUE(object.match("close")); //  its a match
	ASSERT_EQ(object.remaining(), 1);
}

TEST(GuesserTest, too_many_characters_test){
	Guesser object("abcdefghijklmnopqrstuvwxyz12345667890"); //36 characters
	ASSERT_FALSE(object.match("abcdefghijklmnopqrstuvwxyz123456")); //32 characters
	ASSERT_EQ(object.remaining(), 3);

}

TEST(GuesserTest, too_many_test) {
	Guesser object("tests");
	object.match("testa");
	object.match("tents");
	object.match("testw");
	ASSERT_TRUE(object.match("tests")); //after 3 guesses all answers are locked
	ASSERT_EQ(object.remaining(),0);
}

TEST(GuesserTest, all_nothing_test) {
	Guesser object("     "); // 4 spaces
	ASSERT_FALSE(object.match("    ")); //Spaces Fail
	ASSERT_EQ(object.remaining(), 2);
}