#include "tbproto/record.h"
#include "tbproto/run.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Run run;
  tbproto::Record rec0, rec1;
  rec0.add_scalar("my/value", 0.0);
  run.write(rec0);
  rec1.set_step(1);
  rec1.add_scalar("my/value", 1.0);
  run.write(rec1);

  return 0;
}
