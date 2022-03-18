#include <iostream>
#include <string>
#include "AugmentedIntervalTree.h"
#include "MasterIntervalTree.h"
#include <functional>
#include <cmath>

using namespace std;

template<class T>
T const& quiet_assert_msg(string const& message, T const &observed, T const &expected) {
#ifdef VERBOSE
    cout << message << endl << "Expected:" << endl << expected << endl << "Observed:" << endl << observed << endl;
    if (expected != observed) {
        cerr << "FAILED" << endl;
        throw invalid_argument(((string) "FAILED TEST: ") + message);
    } else {
        cout << "PASSED" << endl;
    }
#else
    if (expected != observed) {
        cerr << message << endl;
        cerr << "Expected:" << endl << expected << endl << "Observed:" << endl << observed << endl;
        cerr << "FAILED" << endl;
        throw invalid_argument(((string) "FAILED TEST: ") + message);
    }
#endif
    return observed;
}

template<class T>
T const& quiet_assert(function<string()> const& get_message, T const &observed, T const &expected) {
#ifdef VERBOSE
    return quiet_assert_msg(get_message(), observed, expected);
#else
    if (expected != observed) {
        return quiet_assert_msg(get_message(), observed, expected);
    }
#endif
    return observed;
}

template<class T>
class TestingTree : public IntervalTree<T> {
    IntervalTree<T>* master;
    IntervalTree<T>* test;
public:
    TestingTree(IntervalTree<T>* master, IntervalTree<T>* test) : master(master), test(test) {}
    ~TestingTree() override  {
        delete master;
        delete test;
    }

    void clear() override {
        master->clear();
        test->clear();
    }

    bool is_empty() const override {
        return quiet_assert_msg((string)"is_empty", test->is_empty(), master->is_empty());
    }

    bool add(T const& lower, T const& upper) override {
        auto msg = [lower, upper](){
            stringstream ss;
            ss << "add [" << lower << "," << upper << ")";
            return ss.str();
        };
        return quiet_assert(msg, test->add(lower, upper), master->add(lower, upper));
    }

    bool remove(T const& lower, T const& upper) override {
        auto msg = [lower, upper](){
            stringstream ss;
            ss << "remove [" << lower << "," << upper << ")";
            return ss.str();
        };
        return quiet_assert(msg, test->remove(lower, upper), master->remove(lower, upper));
    }

    vector<Interval<T>> query(T const& point) const override {
        auto msg = [point]() {
            stringstream ss;
            ss << "query " << point;
            return ss.str();
        };
        return quiet_assert(msg, test->query(point), master->query(point));
    }

    void assert_structure() {
        quiet_assert_msg("Compare tree structure", test->to_string(), master->to_string());
    }
};


int main(int argc, char* argv[]) {
    TestingTree<int> tree(
            new MasterIntervalTree<int>(),
            new AugmentedIntervalTree<int>()
            );

    string mode = argv[1];

    if (mode == "add") {
        // Tree is empty
        tree.is_empty();

        // Add one interval
        tree.add(5, 8);
        // Should be false now
        tree.is_empty();

        // Add dup should return false
        tree.add(5, 8);

        // Add same lower bound is not dup - should return true
        tree.add(5, 10);
        tree.assert_structure();

        // Add more stuff
        // Fill in left branch
        tree.add(2, 5);
        tree.add(1, 3);
        tree.add(3, 8);

        // Fill in right branch
        tree.add(7, 10);
        tree.add(6, 7);

        tree.assert_structure();

        // Clear tree - should be empty
        tree.clear();
        tree.is_empty();

        // Should be able to add stuff to a cleared tree
        tree.add(5, 8);
        tree.assert_structure();
        tree.is_empty();
        tree.clear();
        tree.is_empty();

    } else if (mode == "query") {
        tree.add(5, 8);
        tree.add(2, 5);
        tree.add(7, 10);
        tree.assert_structure();

        // outside lower bound
        tree.query(0);

        // matching lower bound
        tree.query(2);

        // matching two intervals
        tree.query(7);

        // outside upper bound
        tree.query(100);

        // matching upper bound (exclusive), so shouldn't match
        tree.query(10);

        // Querying shouldn't change the structure
        tree.assert_structure();

        // Querying shouldn't affect my ability to clear the tree
        tree.clear();
        tree.is_empty();

    } else if (mode == "remove") {
        // Should be empty
        tree.remove(1, 3);

        vector<Interval<int>> intervals;
        int range = 17;
        int width = 3;
        for (int p = 1; p < 4; p++) {
            int step = range;
            for (int i = 1; i <= p; i++) {
                step /= 2;
            }
            for (int lower = 0; lower < range; lower += step) {
                tree.add(lower, lower+width);
                intervals.emplace_back(lower, lower+width);
            }
        }
        tree.assert_structure();

        int round = 0;
        for (const auto& interval : intervals) {
            tree.remove(interval.lower, interval.upper);
            if (++round % 5 == 0) {
                tree.assert_structure();
            }
        }

        // Should be empty
        tree.remove(1, 3);

    } else { // mode == advanced

        vector<Interval<int>> intervals;
        int range = 100;
        int width = 3;
        for (int p = 1; p < 7; p++) {
            int step = range;
            for (int i = 1; i <= p; i++) {
                step /= 2;
            }
            for (int lower = 0; lower < range; lower += step) {
                tree.add(lower, lower+width);
                intervals.emplace_back(lower, lower+width);
            }
        }
        tree.assert_structure();

        for (int i = 0; i < 100; i++) {
            tree.query(i);
        }

        int round = 0;
        for (const auto& interval : intervals) {
            tree.remove(interval.lower, interval.upper);
            if (++round % 20 == 0) {
                tree.assert_structure();
            }
        }
        tree.is_empty();

        // Shouldn't explode
        tree.clear();

        tree.is_empty();
    }

    cout << "All tests passed" << endl;

    return 0;
}
