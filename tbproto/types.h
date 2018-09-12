#ifndef TBPROTO_TYPES_H
#define TBPROTO_TYPES_H

#include <vector>

namespace tbproto {

struct Scalar {
  Scalar() = default;
  explicit Scalar(float value) : value(value) {}

  double value;
};

struct Tensor {
  double value;
};

struct Histogram {

  struct Bin {
    Bin() = default;
    Bin(double max, int count) : max(max), count(count) {}
    double max = 0.0;
    int count = 0;
  };

  double min = 0.0;
  double sum_squares = 0.0;
  std::vector<Bin> bins;
};

} // namespace tbproto

#endif