#include "run.h"
#include "record.h"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {

void write_record(const tbproto::Record &record, std::ofstream &f) {}

void write_header(std::ofstream &f) {}

} // namespace

namespace tbproto {

Run::Run() {}
Run::Run(const RunSettings &settings) : msettings(settings) {}

/// Provides a valid file for record writing
///
/// Uses mfname as proxy of whether file has not been created
/// yet (in which case we create it and write header) or if
/// file exists (in which case it is opened in append mode).
/// Returns file stream and sets mfname if new.
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
    write_header(f);
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
  write_record(record, f);
  f.close();
}

} // namespace tbproto
