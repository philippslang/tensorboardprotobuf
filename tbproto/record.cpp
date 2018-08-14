#include "record.h"
#include "event.pb.h"
#include "summary.pb.h"

#include <google/protobuf/arena.h>

#include <chrono>
#include <vector>

namespace {

void set_event_summary(tensorflow::Event *e, tensorflow::Summary *s) {
  e->set_allocated_summary(s);
}

} // namespace

namespace tbproto {

struct Record::RecordPipml {
  google::protobuf::Arena arena;
  tensorflow::Event *e;
  tensorflow::Summary *s;

  RecordPipml()
      // managed via arena member, tied to instance lifetime
      : e(google::protobuf::Arena::CreateMessage<tensorflow::Event>(&arena)),
        s(google::protobuf::Arena::CreateMessage<tensorflow::Summary>(&arena)) {
  }
};

Record::Record()
    : m(new Record::RecordPipml(), [](RecordPipml *v) { delete v; }) {
  set_time_to_now();
}

void Record::set_step(int64_t step) { m->e->set_step(step); }

int64_t Record::step() const { return m->e->step(); }

void Record::set_time_to_now() {
  auto epoch_time = std::chrono::system_clock::now().time_since_epoch();
  auto seconds =
      std::chrono::duration_cast<std::chrono::seconds>(epoch_time).count();
  m->e->set_wall_time(static_cast<double>(seconds));
}

void Record::add_scalar(std::string_view tag, float value) {
  auto *v = m->s->add_value();
  v->set_tag(tag.data());
  v->set_simple_value(value);
}

std::string Record::data() const {
  std::string data;
  set_event_summary(m->e, m->s);
  m->e->SerializeToString(&data);
  return data;
}

} // namespace tbproto
