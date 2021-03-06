#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const string &str) {
    long i = 0, j = str.length() - 1;
    for (; i <= j; i++, j--) {
        if (str[i] != str[j]) return false;
    }
    return true;
}

void TestAll() {
    Assert(IsPalindrom(""), "");
    Assert(IsPalindrom("a"), "a");
    Assert(IsPalindrom("madam"), "madam");
    Assert(!IsPalindrom(" madam"), "madam");
    Assert(!IsPalindrom("madam "), "madam");
    Assert(IsPalindrom(" madam "), "madam");
    Assert(IsPalindrom(" mad dam "), "madam");
    Assert(!IsPalindrom(" ma dam "), "madam");
    Assert(IsPalindrom("maddam"), "maddam");
    Assert(IsPalindrom("ma d am"), "ma d am");
    Assert(!IsPalindrom("madam2"), "madam2");
    Assert(!IsPalindrom("mada m"), "mada m");
    Assert(!IsPalindrom("maztam"), "maztam");
    Assert(IsPalindrom("madarradam"), "madarradam");
    Assert(!IsPalindrom("tadarradaz"), "madarradam");
}


int main() {
    TestRunner runner;
    runner.RunTest(TestAll, "all");
    return 0;
}