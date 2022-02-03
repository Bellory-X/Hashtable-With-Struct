#include <gtest/gtest.h>
#include "hashtable.h"

TEST(HashTable, SizeIsZeroForEmptyHashTable) {
    HashTable b;
    EXPECT_EQ(b.size(), 0);
}

/* tests for operator= */

TEST(HashTable, NotEmptyHashTablesIsEqualAfterCopy) {
    HashTable a;
    a.insert(Key("First"), Value("firts"));
    a.insert(Key("Second"), Value("second"));
    HashTable b;
    b = a;
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.at("First"), b.at("First"));
    EXPECT_EQ(a.at("Second"), b.at("Second"));
}

TEST(HashTable, EmptyHashTablesIsEqualAfterCopy) {
    HashTable a,b;
    a = b;
    EXPECT_EQ(a.size(), b.size());
}

/* tests for copyconstruct */

TEST(HashTable, HashTablesIsEqualAfterCreateNewHashtableWithCopyConstr) {
    HashTable a;
    a.insert(Key("first"), Value("f"));
    a.insert(Key("second"), Value("f"));
    a.insert(Key("third"), Value("f"));
    HashTable b(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.at("first"), b.at("first"));
    EXPECT_EQ(a.at("second"), b.at("second"));
    EXPECT_EQ(a.at("third"), b.at("third"));
}

TEST(HashTable, EmptyHastablesIsEqualAfterCreateNewHashTableWithCopyCon) {
    HashTable a;
    HashTable b(a);
    EXPECT_EQ(a.size(), b.size());
}

/* tests for swap */

TEST(HashTable, SizesOfHashTableIsEqualsAfterSwap) {
    HashTable a, b;
    a.insert(Key("a"), Value("f"));
    b.insert(Key("a"), Value("f"));
    b.insert(Key("b"), Value("f"));

    a.swap(b);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 1);
}

TEST(HashTable, StartAndFinishHashTablesIsEqualAfterSwap) {
    HashTable a, b;
    a.insert(Key("a"), Value("f"));
    b.insert(Key("a"), Value("f"));
    b.insert(Key("b"), Value("f"));

    HashTable a_copy(a);
    HashTable b_copy(b);

    a.swap(b);
    EXPECT_TRUE(b==a_copy);
    EXPECT_TRUE(a==b_copy);
}

/* tests for clear */

TEST(HashTable, SizeIsZeroAfterClear) {
    HashTable a;
    a.insert(Key("first"), Value("f"));
    a.insert(Key("second"), Value("f"));
    a.insert(Key("third"), Value("f"));

    a.clear();
    EXPECT_EQ(a.size(), 0);
}

/* tests for erase */

TEST(HashTable, ReturnTrueIfElementExists) {
    HashTable a;
    a.insert(Key("a"), Value("f"));
    a.insert(Key("b"), Value("f"));
    a.insert(Key("c"), Value("f"));
    a.insert(Key("d"), Value("f"));

    EXPECT_TRUE(a.erase(Key("a")));
    EXPECT_TRUE(a.erase(Key("b")));
    EXPECT_TRUE(a.erase(Key("c")));
    EXPECT_TRUE(a.erase(Key("d")));
}

TEST(HashTable, ReturnFalseIfElementNotExists) {
    HashTable a;
    EXPECT_EQ(a.erase(Key("a")), false);
}

TEST(HashTable, SizeChangeAfterRemovingAnElement) {
    HashTable a;
    a.insert(Key("a"), Value("f"));
    a.insert(Key("b"), Value("f"));
    a.insert(Key("c"), Value("f"));
    a.insert(Key("d"), Value("f"));

    a.erase(Key("a"));
    EXPECT_EQ(a.size(), 3);
    a.erase(Key("b"));
    EXPECT_EQ(a.size(), 2);
    a.erase(Key("c"));
    EXPECT_EQ(a.size(), 1);
    a.erase(Key("d"));
    EXPECT_EQ(a.size(), 0);
}

/* tests for insert */

TEST(HashTable, SizeIsIncAfterInsert) {
    HashTable a;

    EXPECT_EQ(a.size(), 0);
    a.insert(Key("a"), Value("f"));
    EXPECT_EQ(a.size(), 1);
    a.insert(Key("b"), Value("f"));
    EXPECT_EQ(a.size(), 2);
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.size(), 3);
    a.insert(Key("d"), Value("f"));
    EXPECT_EQ(a.size(), 4);
    a.insert(Key("m"), Value("f"));
    EXPECT_EQ(a.size(), 5);
    a.insert(Key("h"), Value("f"));
    EXPECT_EQ(a.size(), 6);
}

TEST(HashTable, SizeIsNotChangeAfterInsertElementsWithEqualsKey) {
    HashTable a;

    a.insert(Key("a"), Value("f"));
    EXPECT_EQ(a.size(), 1);
    a.insert(Key("a"), Value("c"));
    EXPECT_EQ(a.size(), 1);
}

/* tests for contains */

TEST(HashTable, ReturnTrueIfElenentExistsInHashTable) {
    HashTable a;
    a.insert(Key("a"), Value("f"));
    a.insert(Key("b"), Value("f"));
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.contains(Key("a")), true);
    EXPECT_EQ(a.contains(Key("b")), true);
    EXPECT_EQ(a.contains(Key("c")), true);
}

TEST(HashTable, ReturnFalseIfElenentExistsInHashTable) {
    HashTable a;
    a.insert(Key("a"), Value("f"));
    a.insert(Key("b"), Value("f"));
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.contains(Key("d")), false);
    EXPECT_EQ(a.contains(Key("e")), false);
    EXPECT_EQ(a.contains(Key("f")), false);
}

/* tests for at */

TEST(HashTable, ReturnValueIfItExists) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    a.insert(Key("b"), Value("e"));
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.at(Key("a")) == Value("d"), true);
    EXPECT_EQ(a.at(Key("b")) == Value("e") , true);
    EXPECT_EQ(a.at(Key("c")) == Value("f"), true);
}

TEST(HashTable, NotReturnValueIfItNotExists) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    a.insert(Key("b"), Value("e"));
    a.insert(Key("c"), Value("f"));
    bool not_error = false;
    try {
        a.at(Key("a"));
        a.at(Key("d"));
        a.at(Key("f"));
    }
    catch(std::out_of_range) {
        not_error = true;
    }
    if (not_error) {
        SUCCEED();
    }
    else
    {
        FAIL();
    }
}

/* tests for const at */

TEST(HashTable, ReturnConstValue) {
    HashTable a;
    a.insert(Key("a"), Value("a"));
    const Value& v = a.at(Key("a"));
    EXPECT_EQ(v, Value("a"));
}

/* tests for operator[] */

TEST(HashTable, ReturnValueIfKeyExists) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    a.insert(Key("b"), Value("e"));
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a[Key("a")] == Value("d"), true);
    EXPECT_EQ(a[Key("b")] == Value("e") , true);
    EXPECT_EQ(a[Key("c")] == Value("f"), true);
}

TEST(HashTable, InsertDefaultValueIfKeyNotExists) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    a.insert(Key("b"), Value("e"));
    a.insert(Key("c"), Value("f"));
    Value tmp = a[Key("d")];
    EXPECT_EQ(a[Key("d")] == Value(""), true);
    EXPECT_EQ(tmp == Value(""), true);
}

/* tests for size */

TEST(HashTable, ReturnZeroIfHashtableIsEmpty) {
    HashTable a;
    EXPECT_EQ(a.size(), 0);
}

TEST(HashTable, ReturnRealSizeAfterInsert) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    EXPECT_EQ(a.size(), 1);
    a.insert(Key("b"), Value("e"));
    EXPECT_EQ(a.size(), 2);
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.size(), 3);
}

TEST(HashTable, ReturnRealSizeAfterErase) {
    HashTable a;
    a.insert(Key("a"), Value("d"));
    EXPECT_EQ(a.size(), 1);
    a.insert(Key("b"), Value("e"));
    EXPECT_EQ(a.size(), 2);
    a.insert(Key("c"), Value("f"));
    EXPECT_EQ(a.size(), 3);
    a.erase(Key("a"));
    EXPECT_EQ(a.size(), 2);
    a.erase(Key("b"));
    EXPECT_EQ(a.size(), 1);
    a.erase(Key("c"));
    EXPECT_EQ(a.size(), 0);
}

/* tests for empty */

TEST(HashTable, ReturnTrueIfHashtableIsEmpty) {
    HashTable a;
    EXPECT_EQ(a.empty(), true);
}

TEST(HashTable, ReturnFalseIfHashtableIsntEmpty) {
    HashTable a;
    a.insert(Key("a"), Value("a"));
    EXPECT_EQ(a.empty(), false);
}

/* tests for operator== */

TEST(HashTable, ReturnTrueIfHashtablesIsEqual) {
    HashTable a;
    HashTable b;
    EXPECT_EQ(a==b, true);
    a.insert(Key("a"), Value("b"));
    b.insert(Key("a"), Value("b"));
    EXPECT_EQ(a==b, true);
    a.insert(Key("b"), Value("b"));
    b.insert(Key("b"), Value("b"));
    EXPECT_EQ(a==b, true);
}

TEST(HashTable, ReturnFalseIfHashtablesIsntEqual) {
    HashTable a;
    HashTable b;
    a.insert(Key("a"), Value("A"));
    a.insert(Key("b"), Value("A"));
    EXPECT_EQ(a==b, false);
}

TEST(HashTable, HashtablesIsEqualWithNotEqualSize) {
    HashTable a;
    HashTable b;
    a.insert(Key("a"), Value("A"));
    b.insert(Key("a"), Value("A"));
    b.insert(Key("b"), Value("A"));
    b.insert(Key("c"), Value("A"));
    b.insert(Key("d"), Value("A"));
    b.erase(Key("d"));
    b.erase(Key("c"));
    b.erase(Key("b"));
    EXPECT_TRUE(a == b);
}