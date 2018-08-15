#ifndef TBPROTO_RECORD_H
#define TBPROTO_RECORD_H

#include <cstdint>
#include <memory>
#include <string_view>

namespace tbproto {

class Record {
public:
  Record();
  using pbyte_t = std::string;

  void set_time_to_now();

  int64_t step() const;
  void set_step(int64_t step);

  void set_file_version(std::string_view tag);

  void add_scalar(std::string_view tag, float value);

  pbyte_t data() const;

private:
  struct RecordPipml;
  std::unique_ptr<RecordPipml, void (*)(RecordPipml *)> mproto;
};

} // namespace tbproto

#endif