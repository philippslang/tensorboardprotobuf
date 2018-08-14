#ifndef TBPROTO_RUN_H
#define TBPROTO_RUN_H

#include <chrono>
#include <optional>
#include <string>
#include <string_view>

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

  const RunSettings &settings() const { return *msettings; }
  void set_settings(const RunSettings &settings) { msettings = settings; }

  void write(const Record &);

private:
  using date_t = std::chrono::time_point<std::chrono::system_clock>;
  std::optional<date_t> mstart;
  RunSettings msettings;
};

} // namespace tbproto

#endif