#ifndef TBPROTO_RUN_H
#define TBPROTO_RUN_H

// TODO we don't need to expose fstream here
// if we move the file open stuff into a local
// function in the implementation
#include <fstream>
#include <optional>
#include <string>

namespace tbproto {

class Record;

class Run {
public:
  Run();

  void write(const Record &);

private:
  std::ofstream file();

  std::optional<std::string> mfname;
};

} // namespace tbproto

#endif