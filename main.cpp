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
  auto settings = tbproto::Run::RunSettings();
  settings.run_name = "run1";
  tbproto::Run run1(settings);
  tbproto::Record rec2, rec3;
  rec2.add_scalar("my/value", 0.5);
  run1.write(rec2);
  rec3.set_step(1);
  rec3.add_scalar("my/value", 0.8);
  run1.write(rec3);
  return 0;
}
