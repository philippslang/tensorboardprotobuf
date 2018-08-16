#ifndef TBPROTO_RECORD_H
#define TBPROTO_RECORD_H

#include <cstdint>
#include <memory>
#include <string_view>
#include <variant>

namespace tbproto {

struct Scalar;
struct Tensor;
struct Histogram;

class Record {
public:
  Record();
  using pbyte_t = std::string;

  void set_time_to_now();

  int64_t step() const;
  void set_step(int64_t step);

  void set_file_version(std::string_view tag);

  void add(std::string_view tag,
           const std::variant<Scalar, Tensor, Histogram> &value);

  pbyte_t data() const;

private:
  struct RecordPipml;
  std::unique_ptr<RecordPipml, void (*)(RecordPipml *)> mproto;
};

} // namespace tbproto

#endif