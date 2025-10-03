#include <iostream>
#include <vector>
#include "JavaString.hpp"

using namespace JavaString;
using std::cout;
using std::endl;

void test_default_constructor()
{
    cout << "\n=== Test default constructor ===" << endl;
    Jstring s;
    if (s.length() == 0 && s.isEmpty()) {
        cout << "PASS: Default constructor creates empty string." << endl;
    } else {
        cout << "FAIL!" << endl;
    }
}

void test_cstr_constructor()
{
    cout << "\n=== Test const char* constructor ===" << endl;
    try {
        Jstring s1("hello");
        if (s1.length() == 5 && s1.charAt(0) == 'h') {
            cout << "PASS: Normal string." << endl;
        }

        Jstring s2("");
        if (s2.isEmpty()) {
            cout << "PASS: Empty string." << endl;
        }

        Jstring s3(nullptr); // should throw
        cout << "FAIL: nullptr not caught!" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: nullptr correctly throws." << endl;
    }
}

void test_copy_constructor_and_assignment()
{
    cout << "\n=== Test copy constructor & assignment ===" << endl;
    Jstring s1("hello");
    Jstring s2(s1);
    if (s2.equals(s1)) {
        cout << "PASS: Copy constructor works." << endl;
    }

    Jstring s3("world");
    s3 = s1;
    if (s3.equals(s1) && s3.length() == 5) {
        cout << "PASS: Assignment works." << endl;
    }

    // Self-assignment
    s3 = s3;
    if (s3.equals(s1)) {
        cout << "PASS: Self-assignment safe." << endl;
    }
}

void test_operator_plus()
{
    cout << "\n=== Test operator+ ===" << endl;
    Jstring s1("hello");
    Jstring s2(" world");
    Jstring s3 = s1 + s2;
    if (s3.length() == 11 && s3.charAt(5) == ' ') {
        cout << "PASS: Jstring + Jstring works." << endl;
    }

    Jstring s4 = s1 + "!";
    if (s4.length() == 6 && s4.charAt(5) == '!') {
        cout << "PASS: Jstring + const char* works." << endl;
    }

    try {
        Jstring s5 = s1 + nullptr;
        cout << "FAIL: nullptr in operator+ not caught!" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: nullptr in operator+ throws." << endl;
    }

    // Edge: empty + empty
    Jstring empty1, empty2;
    Jstring empty3 = empty1 + empty2;
    if (empty3.isEmpty()) {
        cout << "PASS: Empty + empty = empty." << endl;
    }
}

void test_substring()
{
    cout << "\n=== Test substring ===" << endl;
    Jstring s("abcdef");

    // Normal
    Jstring sub1 = s.substring(1, 4); // "bcd"
    if (sub1.length() == 3 && sub1.charAt(0) == 'b') {
        cout << "PASS: substring(1,4) = 'bcd'" << endl;
    }

    // Default endIndex
    Jstring sub2 = s.substring(3); // "def"
    if (sub2.length() == 3 && sub2.charAt(0) == 'd') {
        cout << "PASS: substring(3) = 'def'" << endl;
    }

    // Empty substring
    Jstring sub3 = s.substring(2, 2);
    if (sub3.isEmpty()) {
        cout << "PASS: substring(i,i) is empty." << endl;
    }

    // Full string
    Jstring sub4 = s.substring(0);
    if (sub4.equals(s)) {
        cout << "PASS: substring(0) = full string." << endl;
    }

    // Exceptions
    try {
        s.substring(10); // beginIndex > size
        cout << "FAIL: Out-of-range beginIndex not caught!" << endl;
    } catch (...) {
        cout << "PASS: beginIndex > size throws." << endl;
    }

    try {
        s.substring(2, 1); // endIndex < beginIndex
        cout << "FAIL: endIndex < beginIndex not caught!" << endl;
    } catch (...) {
        cout << "PASS: endIndex < beginIndex throws." << endl;
    }

    try {
        s.substring(0, 100); // endIndex > size
        cout << "FAIL: endIndex > size not caught!" << endl;
    } catch (...) {
        cout << "PASS: endIndex > size throws." << endl;
    }
}

void test_replace()
{
    cout << "\n=== Test replace ===" << endl;
    Jstring s("aabbcc");
    Jstring t = s.replace('a', 'x');
    if (t.length() == 6 && t.charAt(0) == 'x' && t.charAt(2) == 'b') {
        cout << "PASS: replace works." << endl;
    }

    // No match
    Jstring u = s.replace('z', 'x');
    if (u.equals(s)) {
        cout << "PASS: replace with no match returns original." << endl;
    }

    // Replace with same char
    Jstring v = s.replace('a', 'a');
    if (v.equals(s)) {
        cout << "PASS: replace same char works." << endl;
    }
}

void test_case_conversion()
{
    cout << "\n=== Test toUpperCase / toLowerCase ===" << endl;
    Jstring s("Hello World!");
    Jstring upper = s.toUpperCase();
    Jstring lower = s.toLowerCase();

    if (upper.charAt(0) == 'H' && upper.charAt(1) == 'E') {
        cout << "PASS: toUpperCase works." << endl;
    }
    if (lower.charAt(0) == 'h' && lower.charAt(6) == 'w') {
        cout << "PASS: toLowerCase works." << endl;
    }

    // Non-alphabet
    Jstring num("123!@#");
    if (num.toUpperCase().equals(num) && num.toLowerCase().equals(num)) {
        cout << "PASS: Non-alphabet unchanged." << endl;
    }
}

void test_equals_and_ignore_case()
{
    cout << "\n=== Test equals / equalsIgnoreCase ===" << endl;
    Jstring s1("Hello");
    Jstring s2("hello");
    Jstring s3("Hello");

    if (s1.equals(s3) && !s1.equals(s2)) {
        cout << "PASS: equals is case-sensitive." << endl;
    }
    if (s1.equalsIgnoreCase(s2) && s1.equalsIgnoreCase(s3)) {
        cout << "PASS: equalsIgnoreCase ignores case." << endl;
    }

    // Different lengths
    Jstring s4("Hell");
    if (!s1.equals(s4) && !s1.equalsIgnoreCase(s4)) {
        cout << "PASS: Different lengths return false." << endl;
    }
}

void test_charAt_and_index_operator()
{
    cout << "\n=== Test charAt / operator[] ===" << endl;
    Jstring s("abc");
    if (s.charAt(1) == 'b' && s[1] == 'b') {
        cout << "PASS: charAt and [] work." << endl;
    }

    try {
        s.charAt(10);
        cout << "FAIL: Out-of-range charAt not caught!" << endl;
    } catch (...) {
        cout << "PASS: charAt out-of-range throws." << endl;
    }
}

void test_toCharArray()
{
    cout << "\n=== Test toCharArray ===" << endl;
    Jstring s("ab");
    std::vector<char> v = s.toCharArray();
    if (v.size() == 3 && v[0] == 'a' && v[1] == 'b' && v[2] == '\0') {
        cout << "PASS: toCharArray includes null terminator." << endl;
    }

    Jstring empty;
    std::vector<char> v2 = empty.toCharArray();
    if (v2.size() == 1 && v2[0] == '\0') {
        cout << "PASS: Empty string toCharArray works." << endl;
    }
}

void test_contains_and_startsWith()
{
    cout << "\n=== Test contains / startsWith ===" << endl;
    Jstring s("Hello World");

    if (s.contains(Jstring("World")) && !s.contains(Jstring("xyz"))) {
        cout << "PASS: contains works." << endl;
    }

    if (s.startsWith(Jstring("Hello")) && s.startsWith(Jstring(""), 5)) {
        cout << "PASS: startsWith works." << endl;
    }

    if (!s.startsWith(
            Jstring("World"),
            6)) { // "World" starts at 6, but "World" != "World" → actually true!
                  // Wait: s = "Hello World", startsWith("World", 6) → compares "World" vs
                  // "World" → true So this condition is wrong.
    }
    // Correct test:
    if (s.startsWith(Jstring("World"), 6)) {
        cout << "PASS: startsWith with offset works." << endl;
    }

    if (!s.startsWith(Jstring("Hello"), 1)) {
        cout << "PASS: startsWith false case works." << endl;
    }
}

void test_indexOf()
{
    cout << "\n=== Test indexOf ===" << endl;
    Jstring s("abcbc");

    if (s.indexOf('b') == 1 && s.indexOf('b', 2) == 3) {
        cout << "PASS: indexOf(char) works." << endl;
    }

    if (s.indexOf('z') == -1) {
        cout << "PASS: indexOf(char) not found returns -1." << endl;
    }

    if (s.indexOf(Jstring("bc")) == 1 && s.indexOf(Jstring("bc"), 2) == 3) {
        cout << "PASS: indexOf(Jstring) works." << endl;
    }

    if (s.indexOf(Jstring("")) == 0) {
        cout << "PASS: indexOf(empty) returns 0." << endl;
    }

    if (s.indexOf(Jstring("xyz")) == -1) {
        cout << "PASS: indexOf(Jstring) not found returns -1." << endl;
    }
}

void test_concat_and_toString()
{
    cout << "\n=== Test concat / toString ===" << endl;
    Jstring s1("Hello");
    Jstring s2(" World");
    Jstring s3 = s1.concat(s2);
    if (s3.length() == 11) {
        cout << "PASS: concat works." << endl;
    }

    std::string stds = s1.toString();
    if (stds == "Hello") {
        cout << "PASS: toString works." << endl;
    }
}

int main()
{
    test_default_constructor();
    test_cstr_constructor();
    test_copy_constructor_and_assignment();
    test_operator_plus();
    test_substring();
    test_replace();
    test_case_conversion();
    test_equals_and_ignore_case();
    test_charAt_and_index_operator();
    test_toCharArray();
    test_contains_and_startsWith();
    test_indexOf();
    test_concat_and_toString();

    cout << "\n=== All tests completed ===" << endl;
    return 0;
}
