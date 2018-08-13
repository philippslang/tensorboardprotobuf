#include "record.h"
#include "event.pb.h"

namespace tbproto {

struct RecordPipml {
  tensorflow::Event e;
};

Record::Record() : m(new RecordPipml(), [](RecordPipml *v) { delete v; }) {
  init();
}

void Record::set_step(int64_t step) { m->e.set_step(step); }

void Record::init() { m->e.set_wall_time(0); }

} // tbproto
