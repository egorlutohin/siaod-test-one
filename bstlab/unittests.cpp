#include <gtest/gtest.h>
#include "mybst.h"
#include <string>
#include <iostream>

TEST(MyBSTTest, Init)
{
	MyBST<int, int> *bst = new MyBST<int, int>();

	EXPECT_EQ(bst->get_size(), 0);
	EXPECT_TRUE(bst->is_empty());

	delete bst;
}

TEST(MyBSTTest, GetHeadValue) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	EXPECT_THROW(bst->get_head_value(), const char *);

	bst->insert(20, 20);
	EXPECT_EQ(20, bst->get_head_value());

	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(40, 40);
	bst->insert(50, 50);
	bst->remove(20);
	EXPECT_EQ(30, bst->get_head_value());

	bst->remove(40);
	EXPECT_EQ(30, bst->get_head_value());

	delete bst;
}

TEST(MyBSTTest, GetInnerPathValue) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	EXPECT_EQ(3, bst->get_inner_path_value());

	delete bst;
}

TEST(MyBSTTest, GetValue) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(30, 30);
	bst->insert(50, 50);

	EXPECT_EQ(20, bst->get_value(20));
	EXPECT_EQ(50, bst->get_value(50));
	EXPECT_EQ(30, bst->get_value(30));

	EXPECT_THROW(bst->get_value(0), const char *);
	EXPECT_THROW(bst->get_value(10000), const char *);

	delete bst;
}

TEST(MyBSTTest, Insert)
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

TEST(MyBSTTest, Delete) {

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
	EXPECT_EQ(std::string("10 30 40 50 20"), bst->to_string());
	EXPECT_EQ(20, bst->get_head_value());

	bst->remove(20);
	EXPECT_EQ(std::string("10 40 50 30"), bst->to_string());
	EXPECT_EQ(30, bst->get_head_value());

	delete bst;
}

TEST(MyBSTTest, TreeSize) {

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

	delete bst;
}

TEST(MyBSTTest, Clean) {

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

	delete bst;
}

TEST(MyBSTTest, DISABLED_Print) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	bst->print();

	delete bst;
}

TEST(MyBSTTest, GetOperationCounter) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	EXPECT_EQ(1, bst->get_operation_counter());
	bst->insert(10, 10);
	EXPECT_EQ(2, bst->get_operation_counter());
	bst->insert(40, 40);
	EXPECT_EQ(2, bst->get_operation_counter());
	bst->insert(30, 30);
	EXPECT_EQ(3, bst->get_operation_counter());
	bst->insert(50, 50);
	EXPECT_EQ(3, bst->get_operation_counter());
	bst->insert(25, 25);
	EXPECT_EQ(4, bst->get_operation_counter());
	bst->insert(35, 35);
	EXPECT_EQ(4, bst->get_operation_counter());

	bst->remove(35);
	EXPECT_EQ(4, bst->get_operation_counter());
	bst->remove(40);
	EXPECT_EQ(3, bst->get_operation_counter());

	delete bst;


	bst = new MyBST<int, int>();
	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	bst->get_value(30);
	EXPECT_EQ(3, bst->get_operation_counter());
	bst->get_value(25);
	EXPECT_EQ(4, bst->get_operation_counter());
	bst->get_value(40);
	EXPECT_EQ(2, bst->get_operation_counter());

	delete bst;
}

