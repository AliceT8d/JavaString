#include <iostream>
#include <vector>
#include "JavaString.hpp" // 假设你的头文件叫这个
using namespace JavaString;
using std::cout;
using std::endl;

void test_trim()
{
    cout << "\n=== Test trim() ===" << endl;

    // Test 1: Normal spaces and tabs
    {
        Jstring s("   hello   ");
        Jstring t = s.trim();
        if (t.equals(Jstring("hello"))) {
            cout << "PASS: Spaces trimmed." << endl;
        } else {
            cout << "FAIL: Spaces not trimmed. Got [" << t << "]" << endl;
        }
    }

    // Test 2: Mixed whitespace: space, tab, newline, carriage return
    {
        Jstring s("\t\n\r hello world \r\n\t");
        Jstring t = s.trim();
        if (t.equals(Jstring("hello world"))) {
            cout << "PASS: Mixed whitespace trimmed." << endl;
        } else {
            cout << "FAIL: Mixed whitespace. Got [" << t << "]" << endl;
        }
    }

    // Test 3: Empty string
    {
        Jstring s;
        Jstring t = s.trim();
        if (t.isEmpty()) {
            cout << "PASS: Empty string handled." << endl;
        } else {
            cout << "FAIL: Empty string not preserved." << endl;
        }
    }

    // Test 4: All whitespace (should become empty)
    {
        Jstring s(" \t\n\r\x1F\x7F"); // includes 31 (0x1F) and 127 (DEL)
        Jstring t = s.trim();
        if (t.isEmpty()) {
            cout << "PASS: All whitespace trimmed to empty." << endl;
        } else {
            cout << "FAIL: All-whitespace not emptied. Got [" << t << "]" << endl;
        }
    }

    // Test 5: No whitespace (should remain unchanged)
    {
        Jstring s("hello");
        Jstring t = s.trim();
        if (t.equals(s)) {
            cout << "PASS: No whitespace unchanged." << endl;
        } else {
            cout << "FAIL: Unnecessary change. Got [" << t << "]" << endl;
        }
    }

    // Test 6: Single space
    {
        Jstring s(" ");
        Jstring t = s.trim();
        if (t.isEmpty()) {
            cout << "PASS: Single space trimmed." << endl;
        } else {
            cout << "FAIL: Single space not trimmed." << endl;
        }
    }

    // Test 7: Single non-whitespace char
    {
        Jstring s("a");
        Jstring t = s.trim();
        if (t.equals(Jstring("a"))) {
            cout << "PASS: Single char preserved." << endl;
        } else {
            cout << "FAIL: Single char altered." << endl;
        }
    }

    // Test 8: Whitespace in middle (should NOT be trimmed)
    {
        Jstring s("hello   world");
        Jstring t = s.trim();
        if (t.equals(s)) {
            cout << "PASS: Internal whitespace preserved." << endl;
        } else {
            cout << "FAIL: Internal whitespace incorrectly trimmed. Got [" << t << "]" << endl;
        }
    }

    // Test 9: DEL character (127) at ends
    {
        char withDel[] = "\x7F  hello  \x7F";
        Jstring s(withDel);
        Jstring t = s.trim();
        if (t.equals(Jstring("hello"))) {
            cout << "PASS: DEL (127) trimmed." << endl;
        } else {
            cout << "FAIL: DEL not trimmed. Got [" << t << "]" << endl;
        }
    }

    // Test 10: Null byte in string (ASCII 0) — your condition trims it
    {
        // Construct string with embedded \0 (not typical, but test robustness)
        char buf[] = "\0\0hello\0\0";
        // But note: std::strlen would stop at first \0, so we can't use const char* constructor
        // Instead, simulate via manual construction (not possible with current API)
        // So skip this edge case — your class assumes null-terminated C-string input.
        cout << "SKIP: Embedded null byte (not supported by current constructor)." << endl;
    }

    // Test 11: String with ASCII 31 (unit separator) and 32 (space)
    {
        char special[] = "\x1F\x20hello\x20\x1F"; // 31, 32, ..., 32, 31
        Jstring s(special);
        Jstring t = s.trim();
        if (t.equals(Jstring("hello"))) {
            cout << "PASS: ASCII 31 and 32 trimmed." << endl;
        } else {
            cout << "FAIL: ASCII 31/32 not trimmed. Got [" << t << "]" << endl;
        }
    }

    // Test 12: One char that is whitespace (e.g., tab)
    {
        Jstring s("\t");
        Jstring t = s.trim();
        if (t.isEmpty()) {
            cout << "PASS: Single tab trimmed." << endl;
        } else {
            cout << "FAIL: Single tab not trimmed." << endl;
        }
    }
}

// Add this to your main() or run separately
int main()
{
    test_trim();
    cout << "\n=== Trim tests completed ===" << endl;
    return 0;
}
