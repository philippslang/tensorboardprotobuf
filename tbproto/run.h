#ifndef TBPROTO_RUN_H
#define TBPROTO_RUN_H

#include <optional>
#include <string>

namespace tbproto {

class Record;

class Run {
public:
  Run();

  void write(const Record &);

private:
  std::optional<std::string> mfname;
};

} // namespace tbproto

#endif