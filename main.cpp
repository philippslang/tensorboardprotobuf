#include "tbproto/record.h"
#include "tbproto/run.h"
#include "tbproto/types.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Run run;
  tbproto::Record rec0, rec1;
  rec0.add("my/value", tbproto::Scalar(0.0));
  run.write(rec0);
  rec1.set_step(1);
  rec1.add("my/value", tbproto::Scalar(1.0));
  run.write(rec1);

  return 0;
}
