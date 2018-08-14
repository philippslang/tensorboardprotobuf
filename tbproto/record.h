#ifndef TBPROTO_RECORD_H
#define TBPROTO_RECORD_H

#include <cstdint>
#include <memory>
#include <string_view>

namespace tbproto {

class Record {

  struct RecordPipml;
  std::unique_ptr<RecordPipml, void (*)(RecordPipml *)> m;

public:
  Record();

  void set_step(int64_t step);
  int64_t step() const;
  void set_time_to_now();
  void add_scalar(std::string_view tag, float value);
  std::string data() const;
};

} // namespace tbproto

#endif