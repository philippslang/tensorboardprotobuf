#ifndef TBPROTO_TYPES_H
#define TBPROTO_TYPES_H

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
  double value;
};

} // namespace tbproto

#endif