#ifndef TBPROTO_RUN_H
#define TBPROTO_RUN_H

#include <fstream>
#include <optional>
#include <string>

namespace tbproto {

class Record;

class Run {
public:
  struct RunSettings {
    // such that results will be written to
    // root_folder_name/run_name/events.out.tfevents.<isotime>
    // and tensorboard is to be run as tensorboard --logdir folder_name
    std::string run_name = "run";
    std::string root_folder_name = "runs";
  };

  Run();
  explicit Run(const RunSettings &);

  RunSettings &settings() { return msettings; }
  const RunSettings &settings() const { return msettings; }

  void write(const Record &);

private:
  std::ofstream file();

  RunSettings msettings;
  std::optional<std::string> mfname;
};

} // namespace tbproto

#endif