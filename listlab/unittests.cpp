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

//TEST(SillyTestCase, SecondSillyTest) {
//	EXPECT_TRUE(1);
//}

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
	} while (!i->is_end());
	EXPECT_EQ(**i, 100);
	EXPECT_TRUE(i->is_end());

	i->next();
	EXPECT_EQ(**i, 100);
	EXPECT_TRUE(i->is_end());

	i->begin();
	EXPECT_TRUE(i->is_begin());
	EXPECT_EQ(i->get_current_value(), 10);
	EXPECT_EQ(i->get_current_value(), **i);

	delete l, i;

}

int main(int argc, char **argv){
	testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
