#include "record.h"
#include "event.pb.h"
#include "summary.pb.h"
#include "types.h"

#include <google/protobuf/arena.h>

#include <chrono>
#include <vector>

namespace {

void set_event_summary(tensorflow::Event *e, tensorflow::Summary *s) {
  e->set_allocated_summary(s);
}

struct ValueTypeVisitor {
  tensorflow::Summary *s = nullptr;
  std::string_view tag;

  void operator()(tbproto::Scalar const &arg) {
    auto *v = s->add_value();
    v->set_tag(tag.data());
    v->set_simple_value(arg.value);
  }

  void operator()(tbproto::Tensor const &arg) {}

  void operator()(tbproto::Histogram const &arg) {}
};

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
    : mproto(new Record::RecordPipml(), [](RecordPipml *v) { delete v; }) {
  set_time_to_now();
}

void Record::set_step(int64_t step) { mproto->e->set_step(step); }

int64_t Record::step() const { return mproto->e->step(); }

void Record::set_time_to_now() {
  auto epoch_time = std::chrono::system_clock::now().time_since_epoch();
  auto seconds =
      std::chrono::duration_cast<std::chrono::seconds>(epoch_time).count();
  mproto->e->set_wall_time(static_cast<double>(seconds));
}

void Record::add(std::string_view tag,
                 const std::variant<Scalar, Tensor, Histogram> &value) {
  ValueTypeVisitor value_visitor;
  value_visitor.s = mproto->s;
  value_visitor.tag = tag;
  std::visit(value_visitor, value);
}

void Record::set_file_version(std::string_view tag) {
  mproto->e->set_file_version(tag.data());
}

Record::pbyte_t Record::data() const {
  pbyte_t data;
  set_event_summary(mproto->e, mproto->s);
  mproto->e->SerializeToString(&data);
  return data;
}

} // namespace tbproto
