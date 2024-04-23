#include <gtest/gtest.h>

#include <AbcUtils.hpp>

TEST(GetStatsTest, ErrorWithInvalidLibraryName) {
  std::string libName = "incorrect_libname.lib";
  std::string libPath = "../../tech_libs";
  auto result =
      AbcUtils::getStats("correct_filename.v", libName,
                         "../../test/test_data/optimization_utils", libPath);
  std::string errorText = "Incorrect read: Cannot open input file \"" +
                          libPath + "/" + libName + "\". \n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);
}

TEST(GetStatsTest, ErrorWithInvalidFileName) {
  auto result = AbcUtils::getStats("correct_filename.v", "sky130.lib",
                                   "../../test/test_data/optimization_utils",
                                   "../../tech_libs");
  std::string readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "true");

  result = AbcUtils::getStats("incorrect_filename.v", "sky130.lib",
                              "../../test/test_data/optimization_utils",
                              "../../tech_libs");
  readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "false");
}

TEST(GetStatsTest, ErrorWithInvalidFilePath) {
  auto result = AbcUtils::getStats("correct_filename.v", "sky130.lib",
                                   "../../test/test_data/optimization_utils",
                                   "../../tech_libs");
  std::string readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "true");

  result = AbcUtils::getStats("correct_filename.v", "sky130.lib",
                              "incorrect_filepath", "../../tech_libs");
  readFlag = result.commandsOutput["fileRead"];

  EXPECT_EQ(readFlag, "false");
}

TEST(GetStatsTest, ErrorWithInvalidLibraryPath) {
  std::string libPath = "incorrect_libpath";
  auto result =
      AbcUtils::getStats("correct_filename.v", "lib130",
                         "../../test/test_data/optimization_utils", libPath);
  std::string errorText =
      "Incorrect map: Warning: The network was "
      "strashed and balanced before mapping.\nThe current library "
      "is not available.\nError: Mapping has failed.\n\n";
  std::string errorResult = result.commandsOutput["error"];

  EXPECT_EQ(errorResult, errorText);
}