#ifndef TBPROTO_RECORD_H
#define TBPROTO_RECORD_H

#include <cstdint>
#include <memory>

namespace tbproto {

struct RecordPipml;

class Record {

  std::unique_ptr<RecordPipml, void (*)(RecordPipml *)> m;

  void init();

public:
  Record();

  void set_step(int64_t step);
};
}

#endif