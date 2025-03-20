#include <gtest/gtest.h>
#include <filesystem>
#include <AbcUtils.hpp>


std::string fullLibPath = std::filesystem::canonical("../../tech_libs").string();
std::string testDataPath = "../../test/test_data/optimization_utils";
std::string libPath = "../../tech_libs";

// Успешный сценарий
TEST(Resyn2Test, Success) {
  auto result = AbcUtils::resyn2("correct_filename.v", "sky130.lib",
                                 testDataPath, libPath);
  EXPECT_TRUE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(OptimizeWithLibTest, Success) {
  auto result = AbcUtils::optimizeWithLib("correct_filename.v", "sky130.lib",
                                          testDataPath, libPath);
  EXPECT_TRUE(result.correct);    
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(VerilogToBenchTest, Success) {
  auto result = AbcUtils::verilogToBench("correct_filename.v", testDataPath);
  EXPECT_TRUE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(GetStatsTest, Success) {
  auto result = AbcUtils::getStats("correct_filename.v", "sky130.lib",
                                   testDataPath, libPath);
  EXPECT_TRUE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

// Несуществующее название файла
TEST(Resyn2Test, ErrorWithInvalidFileName) {
  auto result = AbcUtils::resyn2("invalid_filename.v", "sky130.lib",
                                 testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(OptimizeWithLibTest, ErrorWithInvalidFileName) {
  auto result = AbcUtils::optimizeWithLib("invalid_filename.v", "sky130.lib",
                                          testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(VerilogToBenchTest, ErrorWithInvalidFileName) {
  auto result = AbcUtils::verilogToBench("invalid_filename.v", testDataPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(GetStatsTest, ErrorWithInvalidFileName) {
  auto result = AbcUtils::getStats("invalid_filename.v", "sky130.lib",
                                   testDataPath, libPath);
  EXPECT_FALSE(result.correct);                                 
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

// Несуществующее название библиотеки
TEST(Resyn2Test, NonExistentLibrary) {
  auto result = AbcUtils::resyn2("correct_filename.v", "nonexistent.lib",
                                 testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(OptimizeWithLibTest, NonExistentLibrary) {
  auto result = AbcUtils::optimizeWithLib("correct_filename.v", 
                                          "nonexistent.lib",
                                          testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

// Неверный путь до файла
TEST(Resyn2Test, ErrorWithInvalidFilePath) {
  auto result = AbcUtils::resyn2("correct_filename.v", "sky130.lib",
                                 "invalid_path", libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(OptimizeWithLibTest, ErrorWithInvalidFilePath) {
  auto result = AbcUtils::optimizeWithLib("correct_filename.v", "sky130.lib",
                                          "invalid_path", libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(VerilogToBenchTest, ErrorWithInvalidFilePath) {
  auto result = AbcUtils::verilogToBench("correct_filename.v",
                                         "invalid_path");
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

TEST(GetStatsTest, ErrorWithInvalidFilePath) {
  auto result = AbcUtils::getStats("correct_filename.v", "sky130.lib",
                                   "invalid_path", libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}

// Неверный путь до библиотеки
TEST(Resyn2Test, ErrorWithInvalidLibraryPath) {
  std::string libPath = "incorrect_libpath";
  auto result = AbcUtils::getStats("correct_filename.v", "lib130",
                                   testDataPath, libPath);
  std::string errorText =
      "Incorrect map: Warning: The network was "
      "strashed and balanced before mapping.\nThe current library "
      "is not available.\nError: Mapping has failed.\n\n";
  std::string errorResult = result.commandsOutput["error"];
  EXPECT_EQ(errorResult, errorText);
}

TEST(OptimizeWithLibTest, ErrorWithInvalidLibraryPath) {
  std::string libPath = "incorrect_libpath";
  auto result = AbcUtils::optimizeWithLib("correct_filename.v", "lib130",
                                          testDataPath, libPath);
  std::string errorText =
      "Incorrect map: The current library is not "
      "available.\nError: Mapping has failed.\n\n";
  std::string errorResult = result.commandsOutput["error"];
  EXPECT_EQ(errorResult, errorText);
}

TEST(GetStatsTest, ErrorWithInvalidLibraryPath) {
  std::string libPath = "incorrect_libpath";
  auto result = AbcUtils::getStats("correct_filename.v", "lib130",
                                   testDataPath, libPath);
  std::string errorText =
      "Incorrect map: Warning: The network was "
      "strashed and balanced before mapping.\nThe current library "
      "is not available.\nError: Mapping has failed.\n\n";
  std::string errorResult = result.commandsOutput["error"];
  EXPECT_EQ(errorResult, errorText);
}

// Обработка файлов с нестандартными названиями 
// (специальными символами, например, пробелом)
TEST(Resyn2Test, SpecialCharacters) {
  auto result = AbcUtils::resyn2("file with spaces.v", "sky130.lib",
                                  testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(OptimizeWithLibTest, SpecialCharacters) {
  auto result = AbcUtils::optimizeWithLib("file with spaces.v", "sky130.lib",
                                          testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(VerilogToBenchTest, SpecialCharacters) {
  auto result = AbcUtils::verilogToBench("file with spaces.v", testDataPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}

TEST(GetStatsTest, SpecialCharacters) {
  auto result = AbcUtils::getStats("file with spaces.v", "sky130.lib",
                                    testDataPath, libPath);
  EXPECT_FALSE(result.correct);
  EXPECT_EQ(result.commandsOutput["fileRead"], "true");
}