#include "run.h"
#include "record.h"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace tbproto {

Run::Run() {}
Run::Run(const RunSettings &settings) : msettings(settings) {}

std::ofstream Run::file() {
  std::ofstream f;
  std::string open_error_msg{"new file"};
  if (!mfname) {
    auto t = std::time(nullptr);
    char bstr[100];
    if (std::strftime(bstr, sizeof(bstr), "%Y%m%dT%H%M%S",
                      std::localtime(&t))) {
      mfname = {msettings.root_folder_name + "/" + msettings.run_name + "/" +
                "events.out.tfevents." + bstr};
    } else {
      throw std::runtime_error("cannot parse time");
    }
    f.open(mfname->c_str(), std::ofstream::out | std::ios::binary);
  } else {
    f.open(mfname->c_str(),
           std::ofstream::out | std::ofstream::app | std::ios::binary);
    open_error_msg = "existing file";
  }
  if (!f.is_open()) {
    throw std::runtime_error("cannot open " + open_error_msg + " " + *mfname);
  }
  return f;
}

void Run::write(const Record &record) {
  auto f = file();
  // construct
  // write record
  f.close();
}

} // namespace tbproto
