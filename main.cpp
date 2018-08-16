#include "tbproto/record.h"
#include "tbproto/run.h"
#include "tbproto/types.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Run run;

  // first iteration (e.g.)
  {
    tbproto::Record rec;
    rec.set_step(0);
    rec.add("my/value", tbproto::Scalar(0.0));
    rec.add("my/othervalue", tbproto::Scalar(1.0));
    run.write(rec);
  }
  // second iteration (e.g.)
  {
    tbproto::Record rec;
    rec.set_step(1);
    rec.add("my/value", tbproto::Scalar(1.0));
    rec.add("my/othervalue", tbproto::Scalar(0.8));
    run.write(rec);
  }

  return 0;
}
