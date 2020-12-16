#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "Criteria.h"
#include "Perf.h"
#include <iostream>
#include <string>
#include <vector>

class Performance {
public:
  /**
   * Performance standard constructor
   *
   * @param id Id name of the performance (ex: name of alternative or profile)
   * @param criteria Criterion object to base performance over
   */
  Performance(std::string id, Criteria &criteria);

  /**
   * Performance standard constructor
   *
   * @param id Id name of the performance (ex: name of alternative or profile)
   * @param criteria Criterion object to base performance over
   * @param performance vector of performance (float) to set
   */
  Performance(std::string id, Criteria &criteria, std::vector<float> &p);

  /**
   * Performance standard constructor
   *
   * @param performance vector of Perf to set
   */
  Performance(std::vector<Perf> &p);

  /**
   * Performance constructor by copy
   *
   * @param perf Performance object to copy
   */
  Performance(const Performance &p);

  ~Performance();

  friend std::ostream &operator<<(std::ostream &out, const Performance &p);

  /**
   * getPerf getter of the performance parameter
   *
   * @return perf vector of Perf object
   */
  std::vector<Perf> getPerf() const;

  /**
   * getId getter of id parameter
   *
   * @return id
   */
  std::string getId() const;

  /**
   * setId setter of id parameter
   *
   * @param id
   */
  void setId(std::string id);

  /**
   * Overloading [] operator for Performance
   *
   * @param criteria criterion name of the Perf we want
   *
   *@return Perf object with associated criterion
   */
  Perf operator[](std::string criterion) const;

private:
  std::string id_;
  // Performance on each criteria represented as a pair of criteria name and
  // perf value
  std::vector<Perf> performance_;
};

#endif