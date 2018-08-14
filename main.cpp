#include "tbproto/record.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  tbproto::Record r;
  r.add_scalar("my/value", 0.0);
  std::cout << r.data();
  return 0;
}
