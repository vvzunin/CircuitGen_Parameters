#ifndef ABC_UTILS_H
#define ABC_UTILS_H

#include <string>
#include <vector>

#include "StandartUtils.hpp"

/*
This class is made for basic work with abc.
Using it, it is possible to read verlog file,
read aiger file, make strash and to write file into
verilog or aiger
*/
namespace AbcUtils {
CommandWorkResult getStats(std::string i_inputFileName, std::string i_libName,
                           std::string i_fileDirectory = ".",
                           std::string i_libDirectory = ".");

CommandWorkResult resyn2(std::string i_inputFileName, std::string i_libName,
                         std::string i_fileDirectory = ".",
                         std::string i_libDirectory = ".");

CommandWorkResult optimizeWithLib(std::string i_inputFileName,
                                  std::string i_libName,
                                  std::string i_fileDirectory = ".",
                                  std::string i_libDirectory = ".");

CommandWorkResult verilogToBench(std::string i_inputFileName,
                                 std::string i_fileDirectory = ".");

std::vector<StandartCommandInfo> parseCommand(std::string i_command);

CommandWorkResult standartExecutor(std::string i_command,
                                   std::vector<StandartCommandInfo> i_info);

CommandWorkResult runExecutorForStats(std::string i_command,
                                      std::vector<StandartCommandInfo> i_info);

template <typename... Args>
CommandWorkResult runCommand(const std::string& i_command,
                             CommandWorkResult (*executableFunc)(
                                 std::string, std::vector<StandartCommandInfo>),
                             Args&&... filenames) {
  std::string command = StandartUtils::format(i_command, filenames...);

  return executableFunc(command, parseCommand(command));
}
}  // namespace AbcUtils

#endif