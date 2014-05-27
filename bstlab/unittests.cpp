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

TEST(IteratorTest, CurrentValue) {
	MyBST<int, int> *bst = new MyBST<int, int>();
	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);

	EXPECT_THROW(i->current_value(), const char *); // дерево пустое

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	EXPECT_THROW(i->current_value(), const char *); // дерево изменилось
	delete i;

	i = new MyBST<int, int>::Iterator(bst);
	EXPECT_EQ(20, i->current_value());

	delete i;
}

TEST(IteratorTest, GoToMin) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);

	i->goto_min();
	EXPECT_EQ(10, i->current_value());

	bst->remove(20);
	EXPECT_THROW(i->current_value(), const char *);

	delete i;
	i = new MyBST<int, int>::Iterator(bst);
	i->goto_min();
	EXPECT_EQ(10, i->current_value());

	delete bst;
	delete i;
}

TEST(IteratorTest, GoToMax) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);
	i->goto_max();
	EXPECT_EQ(50, i->current_value());

	bst->remove(10);
	EXPECT_THROW(i->current_value(), const char *);

	delete i;

	bst->remove(50);
	i = new MyBST<int, int>::Iterator(bst);
	i->goto_max();
	EXPECT_EQ(40, i->current_value());

	delete i;
	delete bst;
}

TEST(IteratorTest, Previous) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);

	i->goto_max();
	EXPECT_EQ(50, i->current_value());

	i->previous();
	EXPECT_EQ(40, i->current_value());

	i->previous();
	EXPECT_EQ(35, i->current_value());

	i->previous();
	EXPECT_EQ(30, i->current_value());

	i->previous();
	EXPECT_EQ(25, i->current_value());

	i->previous();
	EXPECT_EQ(20, i->current_value());

	i->previous();
	EXPECT_EQ(10, i->current_value());

	i->previous();
	EXPECT_THROW(i->current_value(), const char *);

	i->previous();
	EXPECT_THROW(i->current_value(), const char *);
	i->previous();
	EXPECT_THROW(i->current_value(), const char *);
	i->previous();
	EXPECT_THROW(i->current_value(), const char *);

	delete i;
	delete bst;
}

TEST(IteratorTest, LoopForward) {

	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);
	bst->insert(5, 5);

	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);

	int arr[] = {5, 10, 20, 25, 30, 35, 40, 50}; // 0 .. 7
	int c = 0;
	i->goto_min();
	while(i->not_null()) {
		EXPECT_EQ(arr[c], i->current_value());
		i->next();
		c++;
	}


}

TEST(IteratorTest, LoopBackward) {
	MyBST<int, int> *bst = new MyBST<int, int>();

	bst->insert(20, 20);
	bst->insert(10, 10);
	bst->insert(40, 40);
	bst->insert(30, 30);
	bst->insert(50, 50);
	bst->insert(25, 25);
	bst->insert(35, 35);

	MyBST<int, int>::Iterator *i = new MyBST<int, int>::Iterator(bst);

	int arr[] = {50, 40, 35, 30, 25, 20, 10}; // 0 .. 6
	int c;
	i->goto_max();
	for(c = 0; i->not_null(); i->previous(), c++) {
		EXPECT_EQ(arr[c], i->current_value());
	}

	c = 0;
	i->goto_max();
	while(i->not_null()) {
		EXPECT_EQ(arr[c++], i->current_value());
		i->previous();
	}

	delete i;
	delete bst;
}

