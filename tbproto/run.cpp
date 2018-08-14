#include "run.h"
#include "record.h"

namespace tbproto {

Run::Run() {}

Run::Run(const RunSettings &settings) : msettings(settings) {}

void Run::write(const Record &record) {
  if (!mstart) {
    mstart = std::chrono::system_clock::now();
    // construct fname
    // write header (version record)
  }
  // construct fname
  // write record
}

} // namespace tbproto
