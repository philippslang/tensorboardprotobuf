#include "record.h"
#include "event.pb.h"
#include "summary.pb.h"
#include "types.h"

#include <google/protobuf/arena.h>

#include <chrono>
#include <numeric>
#include <vector>

namespace {

void set_event_summary(tensorflow::Event *e, tensorflow::Summary *s) {
  e->set_allocated_summary(s);
}

void to_tensorflow(tbproto::Histogram const &from,
                   tensorflow::HistogramProto *to) {
  // https://github.com/lanpa/tensorboardX/blob/9d2cbeb26778cc9784a6a7028e75b7fd0950ce87/tensorboardX/summary.py#L147
  // https://github.com/tensorflow/tensorflow/blob/9c270922715306efefce848b87dee3690cdddd27/tensorflow/core/lib/histogram/histogram.cc#L201
  to->Clear();
  to->set_min(from.min);
  to->set_max(from.bins.back().max);
  to->set_sum(
      std::accumulate(std::begin(from.bins), std::end(from.bins), 0,
                      [](int running, const tbproto::Histogram::Bin &b) {
                        return running + b.count;
                      }));
  to->set_sum_squares(from.sum_squares);
  for (const auto &b : from.bins) {
    // TODO leaves zero buckets for now, see tf implementation
    to->add_bucket_limit(b.max);
    to->add_bucket(b.count);
  }
}

} // namespace

namespace tbproto {

struct Record::RecordPipml {
  google::protobuf::Arena arena;
  tensorflow::Event *e = nullptr;
  tensorflow::Summary *s = nullptr;
  tensorflow::HistogramProto *h = nullptr;
  std::string_view tag;

  RecordPipml()
      // managed via arena member, tied to instance lifetime
      : e(google::protobuf::Arena::CreateMessage<tensorflow::Event>(&arena)),
        s(google::protobuf::Arena::CreateMessage<tensorflow::Summary>(&arena)) {
  }

  void operator()(tbproto::Scalar const &arg) {
    auto *v = s->add_value();
    v->set_tag(tag.data());
    v->set_simple_value(arg.value);
  }

  void operator()(tbproto::Tensor const &arg) {}

  void operator()(tbproto::Histogram const &arg) {
    h = google::protobuf::Arena::CreateMessage<tensorflow::HistogramProto>(
        &arena);
    to_tensorflow(arg, h);
    auto *v = s->add_value();
    v->set_tag(tag.data());
    v->set_allocated_histo(h);
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
  mproto->tag = tag;
  std::visit(*mproto, value);
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
