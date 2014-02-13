#include <gtest/gtest.h>
#include "mylist.h"

TEST(ListTestCase, InitTest)
{ 
	List<int> *l = new List<int>(100);

	EXPECT_EQ(l->get_size(), 0);
	EXPECT_EQ(l->get_storage_size(), 100);
	EXPECT_TRUE(l->is_empty());

	delete l;
}

TEST(ListTestCase, CleanTest){
	List<int> *l = new List<int>(100);

	for(int i = 0; i < 10; i++)
		l->insert((i + 1) * 10); // 10 20 30 40 ... 90

	EXPECT_EQ(l->get_size(), 10);

	l->clean();
	EXPECT_EQ(l->get_size(), 0);
	EXPECT_TRUE(l->is_empty());

	delete l;
}

/*
проверка последовательной вставки
создаем список из 10 значений
вставляем первое значение, длина = 1
вставляем еще 9 значений, длина равна 10
вставляем еще одно значение - выбрасывает ошибку
*/
TEST(ListTestCase, InsertTest){
	List<int> *l = new List<int>(10);

	l->insert(10);
	EXPECT_EQ(l->get_size(), 1);
	l->insert(20);
	EXPECT_EQ(l->get_size(), 2);

	for(int i = 3; i <= 10; i++)
		l->insert(i*10);
	EXPECT_EQ(l->get_size(), 10);

	EXPECT_THROW(l->insert(110), const char *);

	delete l;
}

TEST(ListTestCase, GetValueByNumberTest) {
	List<int> *l = new List<int>(100);

	for(int i = 10; i <= 100; i+=10)
		l->insert(i);
	// l = 10 20 30 40 50 60 70 80 90 100

	EXPECT_THROW(l->get_value_by_number(-1), const char *);
	EXPECT_THROW(l->get_value_by_number(-100), const char *);

	EXPECT_EQ(l->get_value_by_number(0), 10);
	EXPECT_EQ(l->get_value_by_number(1), 20);
	EXPECT_EQ(l->get_value_by_number(2), 30);
	EXPECT_EQ(l->get_value_by_number(3), 40);
	EXPECT_EQ(l->get_value_by_number(4), 50);
	EXPECT_EQ(l->get_value_by_number(5), 60);
	EXPECT_EQ(l->get_value_by_number(9), 100);

	EXPECT_THROW(l->get_value_by_number(10), const char *);

	EXPECT_EQ((*l)[4], 50);
	int i = (*l)[4]; // i = 50
	i = 60;
	EXPECT_EQ((*l)[4], 50);

	delete l;
}

TEST(ListTestCase, HasValueTest) {
	List<int> *l = new List<int>(100);

	for(int i = 10; i <= 100; i+=10)
		l->insert(i);
	// l = 10 20 30 40 50 60 70 80 90 100

	EXPECT_TRUE(l->has_value(10));
	EXPECT_TRUE(l->has_value(50));
	EXPECT_TRUE(l->has_value(100));

	EXPECT_FALSE(l->has_value(101));
	EXPECT_FALSE(l->has_value(25));
	EXPECT_FALSE(l->has_value(0));

	delete l;

}

TEST(ListTestCase, ChangeValueByNumberTest){
	List<int> *l = new List<int>(10);

	for(int i = 10; i <= 100; i+=10)
		l->insert(i);
	// l = 10 20 30 40 50 60 70 80 90 100

	EXPECT_EQ(l->get_value_by_number(3), 40);
	l->change_value_by_number(4, 140);
	EXPECT_EQ(l->get_value_by_number(4), 140);

	EXPECT_THROW(l->change_value_by_number(20, 444), const char *);
	EXPECT_THROW(l->change_value_by_number(-10, -10), const char *);
}

TEST(ListTestCase, GetValuePositionTest) {
	List<int> *l = new List<int>(10);

	for(int i = 10; i <= 100; i+=10)
		l->insert(i);
	// l = 10 20 30 40 50 60 70 80 90 100

	EXPECT_EQ(l->get_value_position(10), 0);
	EXPECT_EQ(l->get_value_position(100), 9);
	EXPECT_EQ(l->get_value_position(50), 4);

	EXPECT_EQ(l->get_value_position(1000), -1);

	delete l;
}

TEST(IteratorTestCase, IteratorTest){

	List<int> *l = new List<int>(100);

	for(int j = 10; j <= 100; j+=10)
		l->insert(j);
	// l = 10 20 30 40 50 60 70 80 90 100

	List<int>::Iterator *i = new List<int>::Iterator(l);
	for(int j = 10; j <= 100; j+=10, i->next()){
		EXPECT_EQ(**i, j);
	}

	i->begin();
	EXPECT_EQ(**i, 10);
	do {
		i->next();
	} while (i->in_boundary());
	EXPECT_EQ(i->get_current_value(), 100);

	i->next();
	EXPECT_EQ(i->get_current_value(), 100);

	i->begin();
	EXPECT_TRUE(i->in_begin());
	EXPECT_EQ(i->get_current_value(), 10);
	EXPECT_EQ(i->get_current_value(), **i);

	delete l, i;

}

TEST(IteratorTestCase, EmptyIteratorTest) {
	List<int> *l = new List<int>(100);

	List<int>::Iterator *i = new List<int>::Iterator(l);

	i->next(); i->next(); i->next();

	EXPECT_THROW(i->get_current_value(), const char *);
	EXPECT_THROW(l->get_value_by_number(0), const char *);

	i->in_begin(); i->in_boundary();

	int j = 0;
	for(i->begin(); i->in_boundary(); i->next())
		j++;
	EXPECT_EQ(j, 0);

	delete l, i;
}

int main(int argc, char **argv){
	testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
