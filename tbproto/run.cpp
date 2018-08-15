#include "run.h"
#include "record.h"
#include "tensorflow/crc32c.h"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {

void write_record(const tbproto::Record &record, std::ofstream &f) {

  if (!f.is_open() or f.bad()) {
    throw std::runtime_error("file not valid to write record");
  }
  // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/lib/io/record_writer.cc#L95
  // Format of a single record:
  //  uint64    length
  //  uint32    masked crc of length
  //  byte      data[length]
  //  uint32    masked crc of data
  auto data = record.data();
  char header[sizeof(uint64_t) + sizeof(uint32_t)];
  tensorflow::crc32c::EncodeFixed64(header + 0, data.size());
  tensorflow::crc32c::EncodeFixed32(
      header + sizeof(uint64_t),
      tensorflow::crc32c::MaskedCrc(header, sizeof(uint64_t)));
  char footer[sizeof(uint32_t)];
  tensorflow::crc32c::EncodeFixed32(
      footer, tensorflow::crc32c::MaskedCrc(data.data(), data.size()));

  f.write(header, sizeof(header));
  f.write(data.data(), data.size());
  f.write(footer, sizeof(footer));
  if (f.bad()) {
    throw std::runtime_error("failed to write record");
  }
}

void write_header(std::ofstream &f) {
  tbproto::Record version;
  version.set_step(0);
  version.set_file_version("brain.Event:2");
  write_record(version, f);
}

void open_file(std::ofstream &f, std::string_view fname, bool is_new) {
  if (is_new) {
    f.open(fname.data(), std::ofstream::out | std::ios::binary);
  } else {
    f.open(fname.data(),
           std::ofstream::out | std::ofstream::app | std::ios::binary);
    if (!f.is_open()) {
      throw std::runtime_error("cannot open run file " + std::string(fname));
    }
  }
}

} // namespace

namespace tbproto {

Run::Run() {}

Run::Run(const RunSettings &settings) : msettings(settings) {}

// Provides a valid file for record writing
//
// Uses mfname as proxy of whether file has not been created
// yet (in which case we create it and write header) or if
// file exists (in which case it is opened in append mode).
// Returns file stream and sets mfname if new.
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
      throw std::runtime_error("cannot parse time");
    }
    open_file(f, *mfname, true);
    write_header(f);
  } else {
    open_file(f, *mfname, false);
  }
  return f;
}

void Run::write(const Record &record) {
  auto f = file();
  write_record(record, f);
  f.close();
}

} // namespace tbproto
