#include "../src/Criteria.h"
#include "../src/Performance.h"
#include "../src/PerformanceTable.h"
#include "gtest/gtest.h"
#include <sstream>
#include <utility>

TEST(TestPerformanceTable, TestBaseConstructor) {
  Criteria crit = Criteria(2, "a");
  PerformanceTable perf_table = PerformanceTable("test", 2, crit);
  std::ostringstream os;
  os << perf_table;
  EXPECT_EQ(os.str(),
            "PerformanceTable(Performance(Perf( name : test0, crit : a0, value "
            ": 0 ), Perf( name : test0, crit : a1, value : 0 ), ), "
            "Performance(Perf( name : test1, crit : a0, value : 0 ), Perf( "
            "name : test1, crit : a1, value : 0 ), ), )");
  EXPECT_EQ(perf_table.getMode(), "alt");
}

TEST(TestPerformanceTable, TestConstructorWithPerfVect) {
  std::vector<Performance> perf_vect;
  Criteria crit = Criteria(2, "a");
  perf_vect.push_back(Performance("test0", crit));
  perf_vect.push_back(Performance("test1", crit));
  PerformanceTable perf_table = PerformanceTable(perf_vect);

  std::ostringstream os;
  os << perf_table;
  EXPECT_EQ(os.str(),
            "PerformanceTable(Performance(Perf( name : test0, crit : a0, value "
            ": 0 ), Perf( name : test0, crit : a1, value : 0 ), ), "
            "Performance(Perf( name : test1, crit : a0, value : 0 ), Perf( "
            "name : test1, crit : a1, value : 0 ), ), )");
  EXPECT_EQ(perf_table.getMode(), "alt");
}

TEST(TestPerformanceTable, TestConstructorWithPerfVectErrors) {
  std::vector<Performance> perf_vect;

  try {
    PerformanceTable perf_table_0 = PerformanceTable(perf_vect);
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("The vector must contain performances."));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }

  Criteria crit_a = Criteria(2, "a");
  Criteria crit_b = Criteria(2, "b");
  perf_vect.push_back(Performance("test0", crit_a));
  perf_vect.push_back(Performance("test1", crit_b));

  try {
    PerformanceTable perf_table_1 = PerformanceTable(perf_vect);
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Each performance must be based on the same set of "
                          "criterion, in the same order."));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }

  Criteria crit_c = Criteria(1, "c");
  perf_vect[1] = Performance("test2", crit_c);
  try {
    PerformanceTable perf_table_2 = PerformanceTable(perf_vect);
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Each performance must be based on the same set of "
                          "criterion, in the same order."));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }

  std::vector<Performance> perf_vect_err;
  perf_vect_err.push_back(Performance("test0", crit_c));
  perf_vect_err.push_back(Performance("test0", crit_c));

  try {
    PerformanceTable pt_err = PerformanceTable(perf_vect_err);
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Each performance must have different ids."));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }
}

TEST(TestPerformanceTable, TestConstructorByCopy) {
  std::vector<Performance> perf_vect;
  Criteria crit = Criteria(2, "a");
  perf_vect.push_back(Performance("test0", crit));
  perf_vect.push_back(Performance("test1", crit));
  PerformanceTable perf_table = PerformanceTable(perf_vect);

  std::ostringstream os;

  PerformanceTable perf_table2 = PerformanceTable(perf_table);
  os << perf_table2;
  EXPECT_EQ(
      os.str(),
      "PerformanceTable(Performance(Perf( name : test0, crit : a0, value : 0 "
      "), Perf( name : test0, crit : a1, value : 0 ), ), Performance(Perf( "
      "name : test1, crit : a0, value : 0 ), Perf( name : test1, crit : a1, "
      "value : 0 ), ), )");
  EXPECT_EQ(perf_table.getMode(), "alt");
}

TEST(TestPerformanceTable, TestAccessOperator) {
  std::vector<Performance> perf_vect;
  Criteria crit = Criteria(2, "a");
  perf_vect.push_back(Performance("test0", crit));
  perf_vect.push_back(Performance("test1", crit));
  PerformanceTable perf_table = PerformanceTable(perf_vect);

  std::vector<Perf> p0 = perf_table["test0"];
  std::ostringstream os;
  os << Performance(p0);
  EXPECT_EQ(os.str(), "Performance(Perf( name : test0, crit : a0, value : 0 "
                      "), Perf( name : test0, crit : a1, value : 0 ), )");

  try {
    std::vector<Perf> p_z = perf_table["z"];
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Row not found in performance table"));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }
}

TEST(TestPerformanceTable, TestGetPerf) {
  std::vector<Performance> perf_vect;
  Criteria crit = Criteria(2, "a");
  perf_vect.push_back(Performance("test0", crit));
  perf_vect.push_back(Performance("test1", crit));
  PerformanceTable perf_table = PerformanceTable(perf_vect);

  Perf p = perf_table.getPerf("test1", "a0");
  std::ostringstream os;
  os << p;
  EXPECT_EQ(os.str(), "Perf( name : test1, crit : a0, value : 0 )");

  try {
    Perf p = perf_table.getPerf("test", "a0");
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Name not found in performance table"));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }

  try {
    Perf p = perf_table.getPerf("test0", "a");
    FAIL() << "should have throw invalid argument.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Criterion not found in performance table"));
  } catch (...) {
    FAIL() << "should have throw invalid argument.";
  }
}

TEST(TestPerformanceTable, TestAllInstancesDestroyed) {
  EXPECT_EQ(AtomicMCDAObject::get_nb_instances(), 0);
}