#ifndef CRITERION_H
#define CRITERION_H

#include <iostream>
#include <string>
#include <vector>

#include "AtomicMCDAObject.h"

class Criterion : public AtomicMCDAObject {
public:
  /**
   * Criterion standard constructor
   *
   * @param id Identifier of the criterion
   * @param direction Equal to -1 if criterion is to minimize, 1 if the
   * criterion is to maximize
   * @param weight Weight of the criterion
   */
  Criterion(std::string id, int direction = 1, float weight = 0.0f);

  /**
   * Criterion constructor by copy
   *
   * @param crit Based criterion to copy
   */
  Criterion(const Criterion &crit);

  ~Criterion();
  friend std::ostream &operator<<(std::ostream &out, const Criterion &crit);

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
   * getName getter of name parameter
   *
   * @return name
   */
  int getDirection() const;

  /**
   * setDirection setter of direction parameter
   *
   * @param direction
   */
  void setDirection(int direction);

  /**
   * getWeight getter of weight parameter
   *
   * @return weight
   */
  float getWeight() const;

  /**
   * setWeight setter of weight parameter
   *
   * @param weight
   */
  void setWeight(float weight);

  /**
   * Randomizes the value of the weight of the Criterion object
   *
   * @param weight
   */
  void getRandomCriterionWeight(bool changeSeed = 1);

  /**
   * generateDirection generator of random direction
   * can also be used as reinitialisation for direction
   *
   * @param seed Optional: seed for random generation. Set to time(NULL) by
   * default
   *
   */
  void generateDirection(unsigned long int seed = time(NULL));

  /**
   * generateWeight generator of random weight
   * can also be used as reinitialisation for weight
   *
   * @param seed Optional: seed for random generation. Set to time(NULL) by
   * default
   *
   */
  void generateWeight(unsigned long int seed = time(NULL));

private:
  std::string id_;
  int direction_;
  float weight_;
};

#endif