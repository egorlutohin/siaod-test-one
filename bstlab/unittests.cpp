#include <gtest/gtest.h>
#include "mybst.h"
#include <string>
#include <iostream>

TEST(MyBSTTestCase, InitTest)
{
	MyBST<int, int> *bst = new MyBST<int, int>();

	EXPECT_EQ(bst->get_size(), 0);
	EXPECT_TRUE(bst->is_empty());

	delete bst;
}

TEST(MyBSTTestCase, InsertTest)
{
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);
	EXPECT_EQ(4, bst->get_size());
	EXPECT_EQ(std::string("10 50 30 20"), bst->to_string());

	bst->insert(40, 40);
	EXPECT_EQ(5, bst->get_size());
	EXPECT_EQ(std::string("10 40 50 30 20"), bst->to_string());

	delete bst;
}

TEST(MyBSTTestCase, DeleteTest) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(40, 40);
	EXPECT_EQ(std::string("10 40 50 30 20"), bst->to_string());
	EXPECT_EQ(20, bst->get_head_value());

	bst->remove(30);
	EXPECT_EQ(std::string("10 40 50 20"), bst->to_string());
	EXPECT_EQ(20, bst->get_head_value());

	bst->insert(30, 30);
	EXPECT_EQ(std::string("10 30 40 50 20"), bst->to_string()); // hbz
	EXPECT_EQ(20, bst->get_head_value());

	bst->remove(20); //head delete test !!! ???

	delete bst;
}

TEST(MyBSTTestCase, TreeSizeTest) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(40, 40);
	EXPECT_EQ(5, bst->get_size());

	bst->remove(20);
	EXPECT_EQ(4, bst->get_size());

	bst->remove(30);
	bst->remove(40);
	EXPECT_EQ(2, bst->get_size());

	bst->insert(30, 30);
	EXPECT_EQ(3, bst->get_size());

	bst->insert(30, 30);
	EXPECT_EQ(3, bst->get_size());

	bst->clean();
	EXPECT_EQ(0, bst->get_size());

	bst->insert(10, 10);
	EXPECT_EQ(1, bst->get_size());

}

TEST(MyBSTTestCase, CleanTest) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);
	EXPECT_EQ(4, bst->get_size());

	bst->clean();
	EXPECT_EQ(std::string(""), bst->to_string());
	EXPECT_EQ(0, bst->get_size());

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);
	EXPECT_EQ(std::string("10 50 30 20"), bst->to_string());
}


