#ifndef YOSYS_UTILS_H
#define YOSYS_UTILS_H

#include <string>
#include <vector>

#include "StandartUtils.hpp"

/*
This class is made for basic work with yosys.
Using it, it is possible to read verlog file,
make opt and to write file into verilog
*/

namespace YosysUtils {
CommandWorkResult optVerilog(std::string i_inputFileName,
                             std::string i_outputFileName,
                             std::string i_directory = ".");
CommandWorkResult writeFirrtl(std::string i_inputFileName,
                              std::string i_outputFileName,
                              std::string i_directory = ".");

// IMPORTANT parseAll here is TRUE
std::vector<StandartCommandInfo> parseCommand(std::string i_command);

CommandWorkResult standartExecutor(std::string i_command,
                                   std::vector<StandartCommandInfo> i_info);

template <typename... Args>
CommandWorkResult runCommand(const std::string& i_command,
                             CommandWorkResult (*executableFunc)(
                                 std::string, std::vector<StandartCommandInfo>),
                             Args&&... filenames) {
  std::string command = StandartUtils::format(i_command, filenames...);

  return executableFunc(command, parseCommand(command));
}
}  // namespace YosysUtils

#endif