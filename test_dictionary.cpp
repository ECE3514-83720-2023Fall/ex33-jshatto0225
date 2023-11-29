#include "catch.hpp"

#include "hash_dictionary.hpp"

#include <iostream> // for debugging
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string

typedef unsigned int KeyType;
typedef std::string ValueType;
typedef std::size_t (*FunctionType)(const KeyType &key);
typedef HashDictionary<KeyType, ValueType, FunctionType> DictionaryType;

std::size_t hash(const KeyType& key) { return key; }

TEST_CASE("Basic Tests", "[Dictionary]") {
	//To DO
    DictionaryType dict(hash);

    REQUIRE(dict.isEmpty());
    REQUIRE(dict.size() == 0);

    REQUIRE_NOTHROW(dict.add(1, "one"));
    REQUIRE_FALSE(dict.isEmpty());
    REQUIRE(dict.size() == 1);

    REQUIRE(dict.contains(1));
    REQUIRE(dict.get(1) == "one");

    REQUIRE_NOTHROW(dict.add(2, "two"));
    REQUIRE_FALSE(dict.isEmpty());
    REQUIRE(dict.size() == 2);

    REQUIRE(dict.contains(1));
    REQUIRE(dict.get(1) == "one");
    REQUIRE(dict.contains(2));
    REQUIRE(dict.get(2) == "two");

    REQUIRE_NOTHROW(dict.remove(2));
    REQUIRE(dict.contains(1));
    REQUIRE(dict.get(1) == "one");
    REQUIRE_FALSE(dict.contains(2));
    REQUIRE_THROWS_AS(dict.get(2), std::logic_error);

    REQUIRE_NOTHROW(dict.remove(1));
    REQUIRE_FALSE(dict.contains(1));
    REQUIRE_THROWS_AS(dict.get(1), std::logic_error);

    REQUIRE_THROWS_AS(dict.remove(100), std::logic_error);

    REQUIRE(dict.isEmpty());
    REQUIRE(dict.size() == 0);
}

TEST_CASE("Test large Dictionary", "[Dictionary]") {
	//To Do
    DictionaryType dict(hash);

    for (KeyType i = 0; i < 1000; i++) {
        std::stringstream stream;
        stream << i;
        REQUIRE_NOTHROW(dict.add(i, stream.str()));
    }

    REQUIRE_FALSE(dict.contains(3000));
    REQUIRE_THROWS(dict.get(3000));
    REQUIRE_THROWS(dict.remove(3000));

    for (KeyType i = 0; i < 1000; i++) {
        std::ostringstream stream;
        stream << i;
        REQUIRE(dict.contains(i));
        REQUIRE(dict.get(i) == stream.str());
    }

    for (KeyType i = 0; i < 1000; i++) {
        REQUIRE_NOTHROW(dict.remove(i));
        REQUIRE_FALSE(dict.contains(i));
        REQUIRE_THROWS(dict.get(i));
    }
}

