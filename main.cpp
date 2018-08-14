#include "tbproto/record.h"
#include "tbproto/run.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Record rec;
  rec.add_scalar("my/value", 0.0);
  tbproto::Run run;
  run.write(rec);
  return 0;
}
