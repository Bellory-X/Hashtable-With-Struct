#include <gtest/gtest.h>
#include "hashtable.h"

TEST(constructor, Copy_Constructor) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);


    HashTable b(a);

    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(operators, Assignment_Constructor) {
    HashTable a;
    Value elements[5];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};
    elements[3] = {"Avgust", 33};
    elements[4] = {"Jfwkesf", 134};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    HashTable b;

    b = a;

    EXPECT_EQ(b.size(), a.size());
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(operators, Square_Brackets_When_Element_Existed) {
    HashTable a;
    Value element {"vfgr", 42};

    a.insert("a", element);

    Value result = a["a"];

    EXPECT_TRUE(result.name == element.name);
    EXPECT_TRUE(result.age == element.age);
    EXPECT_EQ(a.size(), 1);
}

TEST(operators, Square_Brackets_When_Element_Not_Existed) {
    HashTable a;
    Value elements[2];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);

    Value result = a["d"];

    EXPECT_TRUE(result.name.empty());
    EXPECT_EQ(result.age, 0);
    EXPECT_EQ(a.size(), 3);
}

TEST(operators, Equals_And_Not_Equals) {
    HashTable a;
    Value elements[5];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};
    elements[3] = {"Avgust", 33};
    elements[4] = {"Jfwkesf", 134};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.insert("d", elements[3]);

    HashTable b;
    b.insert("d", elements[3]);
    b.insert("c", elements[2]);
    b.insert("b", elements[1]);
    b.insert("a", elements[0]);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    a.insert("e", elements[0]);
    b.insert("e", elements[1]);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);

    a.erase("e");
    b.erase("e");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(size, Empty) {
    HashTable a;
    EXPECT_EQ(a.size(), 0);
}

TEST(size, Not_Empty) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_EQ(a.size(), 3);
}

TEST(swap, Swap_Correct) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    HashTable b;
    b.insert("a", elements[0]);
    b.insert("b", elements[1]);

    a.swap(b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(a["a"] == elements[0]);
    EXPECT_TRUE(a["b"] == elements[1]);
    EXPECT_TRUE(b["a"] == elements[0]);
    EXPECT_TRUE(b["b"] == elements[1]);
    EXPECT_TRUE(b["c"] == elements[2]);
}

TEST(clear, Not_Empty) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    a.clear();

    EXPECT_EQ(a.size(), 0);
    EXPECT_FALSE(a.contains("a"));
    EXPECT_FALSE(a.contains("b"));
    EXPECT_FALSE(a.contains("c"));
}

TEST(clear, Empty) {
    HashTable a;

    a.clear();

    EXPECT_EQ(a.size(), 0);
}

TEST(erase, Not_Empty) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.erase("a");

    EXPECT_EQ(a.size(), 2);
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_FALSE(a.contains("a"));
}

TEST(erase, Empty) {
    HashTable b;
    b.erase("ame");

    EXPECT_EQ(b.size(), 0);
}

TEST(contains, Find) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
}

TEST(contains, Not_Find) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);

    EXPECT_FALSE(a.contains("c"));
}

TEST(insert, Element_Exist) {
    HashTable a;

    a.insert("a", Value("reg"));
    a.insert("a", Value("vdf"));

    EXPECT_EQ(a.size(), 1);
    EXPECT_TRUE(a["a"].name == "vdf");
}

TEST(insert, Element_Not_Exist) {
    HashTable a;

    a.insert("a", Value("reg"));
    a.insert("b", Value("vdf"));

    EXPECT_EQ(a.size(), 2);
    EXPECT_TRUE(a["a"].name == "reg");
    EXPECT_TRUE(a["b"].name == "vdf");
}

TEST(at, Element_Exist) {
    HashTable a;
    Value element;
    element.name = "vfgr";
    element.age = 42;

    a.insert("a", element);

    Value result = a.at("a");

    EXPECT_TRUE(result == element);
}

TEST(at, Element_Not_Exist) {
    HashTable a;
    Value element;
    element.name = "vfgr";
    element.age = 42;

    a.insert("a", element);

    ASSERT_THROW(a.at("b"), std::out_of_range);
}

TEST(empty, Empty_For_Empty) {
    HashTable a;
    EXPECT_TRUE(a.empty());
}

TEST(empty, Empty_For_Not_Empty) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_FALSE(a.empty());
}

TEST(resize, Correct_Work_Resize) {
    HashTable a;
    Value elements[10];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};
    elements[3] = {"Avgust", 33};
    elements[4] = {"Jfwkesf", 134};
    elements[5] = {"erte", 13};
    elements[6] = {"jty", 42};
    elements[7] = {"gdas", 33};
    elements[8] = {"vfg", 134};
    elements[9] = {"erfge", 13};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.insert("d", elements[3]);
    a.insert("e", elements[4]);
    a.insert("f", elements[5]);
    a.insert("g", elements[6]);
    a.insert("h", elements[7]);
    a.insert("t", elements[8]);
    a.insert("y", elements[9]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_TRUE(a.contains("d"));
    EXPECT_TRUE(a.contains("e"));
    EXPECT_TRUE(a.contains("f"));
    EXPECT_TRUE(a.contains("g"));
    EXPECT_TRUE(a.contains("h"));
    EXPECT_TRUE(a.contains("t"));
    EXPECT_TRUE(a.contains("y"));
    EXPECT_EQ(a.size(), 10);
}