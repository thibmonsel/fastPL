#include "AlternativesPerformance.h"

AlternativesPerformance::AlternativesPerformance(
    std::map<std::string, std::string> alt_assignment,
    std::vector<Performance> &perf_vect)
    : PerformanceTable(perf_vect) {
  // Need to check if alt_assignment is legit
  alt_assignment_ = alt_assignment;
}

AlternativesPerformance::AlternativesPerformance(
    std::vector<Performance> &perf_vect)
    : PerformanceTable(perf_vect) {
  if (mode_ != "alt") {
    throw std::domain_error(
        "Performance table mode should be alt to assign default categories.");
  }
  for (std::vector<Perf> pv : pt_) {
    std::string altName = pv[0].getName();
    alt_assignment_[altName] = "";
  }
}

AlternativesPerformance::AlternativesPerformance(
    std::map<std::string, std::string> alt_assignment, int nb_of_perfs,
    Criteria &crits, std::string prefix)
    : PerformanceTable(nb_of_perfs, crits, prefix) {
  // Need to check if alt_assignment is legit
  alt_assignment_ = alt_assignment;
}

AlternativesPerformance::AlternativesPerformance(int nb_of_perfs,
                                                 Criteria &crits,
                                                 std::string prefix)
    : PerformanceTable(nb_of_perfs, crits, prefix) {
  if (mode_ != "alt") {
    throw std::domain_error(
        "Performance table mode should be alt to assign categories.");
  }
  for (std::vector<Perf> pv : pt_) {
    std::string altName = pv[0].getName();
    alt_assignment_[altName] = "";
  }
}

AlternativesPerformance::AlternativesPerformance(
    std::map<std::string, std::string> alt_assignment,
    const PerformanceTable &perf_table)
    : PerformanceTable(perf_table) {
  alt_assignment_ = alt_assignment;
}

AlternativesPerformance::AlternativesPerformance(
    const PerformanceTable &perf_table)
    : PerformanceTable(perf_table) {
  if (perf_table.getMode() != "alt") {
    throw std::domain_error(
        "Performance table mode should be alt to assign categories.");
  }
  for (std::vector<Perf> pv : perf_table.getPerformanceTable()) {
    std::string altName = pv[0].getName();
    alt_assignment_[altName] = "";
  }
}

AlternativesPerformance::AlternativesPerformance(
    const AlternativesPerformance &alt)
    : PerformanceTable(alt) {
  // How to implement the copy for PerfTable?
}

AlternativesPerformance::~AlternativesPerformance() {}

std::ostream &operator<<(std::ostream &out,
                         const AlternativesPerformance &alt) {
  out << "AlternativesPerformance( PerformanceTable[ ";
  for (std::vector<Perf> p : alt.pt_) {
    out << "Performance: ";
    for (Perf perf : p) {
      out << perf << " ";
    }
    out << "| ";
  }
  out << "], AlternativesAssignment{ ";

  auto it = alt.alt_assignment_.begin();
  while (it != alt.alt_assignment_.end()) {
    out << it->first << "->" << it->second << " ";
    it++;
  }
  out << "}";
  return out;
}

std::map<std::string, std::string>
AlternativesPerformance::getAlternativesAssignments() const {
  return alt_assignment_;
}

std::string
AlternativesPerformance::getAlternativeAssignment(std::string altName) const {
  return alt_assignment_.find(altName)->second;
}