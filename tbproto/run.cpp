#include "run.h"
#include "record.h"

#include <ctime>
#include <iostream>
#include <string_view>

namespace tbproto {

Run::Run() {}
Run::Run(const RunSettings &settings) : msettings(settings) {}

std::string_view Run::init_file() {
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

    // write header (version record)
  }
  return *mfname;
}

void Run::write(const Record &record) {
  auto fname = init_file();
  std::cout << fname;
  // construct
  // write record
}

} // namespace tbproto
