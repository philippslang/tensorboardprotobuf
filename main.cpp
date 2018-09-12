#include "tbproto/record.h"
#include "tbproto/run.h"
#include "tbproto/types.h"
#include <cmath>
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Run run;

  tbproto::Histogram histo;
  histo.bins.emplace_back(tbproto::Histogram::Bin{1.0, 3});
  histo.bins.emplace_back(tbproto::Histogram::Bin{2.0, 4});
  histo.bins.emplace_back(tbproto::Histogram::Bin{3.0, 1});
  histo.sum_squares = std::pow(0.2, 2);

  // first iteration (e.g.)
  {
    tbproto::Record rec;
    rec.set_step(0);
    rec.add("my/value", tbproto::Scalar{0.0});
    rec.add("my/othervalue", tbproto::Scalar{1.0});
    rec.add("my/histo", histo);
    run.write(rec);
  }
  // second iteration (e.g.)
  {
    tbproto::Record rec;
    rec.set_step(1);
    rec.add("my/value", tbproto::Scalar{1.0});
    rec.add("my/othervalue", tbproto::Scalar{0.8});
    run.write(rec);
  }

  return 0;
}
