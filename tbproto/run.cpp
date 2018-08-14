#include "run.h"
#include "record.h"

#include <ctime>
#include <iostream>
#include <string_view>

namespace tbproto {

Run::Run() {}
Run::Run(const RunSettings &settings) : msettings(settings) {}

std::ofstream Run::file() {
  std::ofstream f;
  if (!mfname) {
    auto t = std::time(nullptr);
    char bstr[100];
    if (std::strftime(bstr, sizeof(bstr), "%Y%m%dT%H%M%S",
                      std::localtime(&t))) {
      mfname = {msettings.root_folder_name + "/" + msettings.run_name + "/" +
                "events.out.tfevents." + bstr};
    } else {
      // todo throw
    }

    f.open(mfname->c_str(), std::ofstream::out | std::ios::binary);
  } else {
    f.open(mfname->c_str(),
           std::ofstream::out | std::ofstream::app | std::ios::binary);
  }
  if (!f.is_open()) {
    // todo throw
  }
  return f;
}

void Run::write(const Record &record) {
  auto f = file();
  f.close();
  // construct
  // write record
}

} // namespace tbproto
