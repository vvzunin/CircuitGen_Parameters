#include <gtest/gtest.h>
#include <filesystem>
#include <YosysUtils.hpp>
#include <iostream>


std::string testDataPath = "../../test/test_data/optimization_utils";

// Корректная и безошибочная обработка файла
TEST(OptVerilogTest, CorrectFile) {
    auto result = YosysUtils::optVerilog("correct_filename.v",
                                         "output.v", testDataPath);
    EXPECT_TRUE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "");
}

TEST(WriteFirrtlTest, CorrectFile) {
    auto result = YosysUtils::writeFirrtl("correct_filename.v",
                                          "output.fir", testDataPath);
    EXPECT_TRUE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "");
}

// Обработка файлов с неверным форматом
TEST(OptVerilogTest, InvalidFormat) {
    auto result = YosysUtils::optVerilog("invalid_format.txt",
                                         "output.v", testDataPath);
    std::string errorText =
        "Incorrect write_verilog: ERROR: Can't open input file " 
        "`../../test/test_data/optimization_utils/invalid_format.txt'"
        " for reading: No such file or directory\n\n";
    std::string errorResult = result.commandsOutput["error"];
    EXPECT_EQ(errorResult, errorText);
}

TEST(WriteFirrtlTest, InvalidFormat) {
    auto result = YosysUtils::writeFirrtl("invalid_format.txt",
                                          "output.fir", testDataPath);
    EXPECT_TRUE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "");
}

// Обработка файлов с нестандартными названиями
// (специальными символами, например, пробелом)
TEST(OptVerilogTest, SpecialCharacters) {
    auto result = YosysUtils::optVerilog("file with spaces.v",
                                         "output.v", testDataPath);
    std::string errorText =
        "Incorrect write_verilog: ERROR: Can't open input file " 
        "`../../test/test_data/optimization_utils/file' "
        "for reading: No such file or directory\n\n";
    std::string errorResult = result.commandsOutput["error"];
    EXPECT_EQ(errorResult, errorText);
}

TEST(WriteFirrtlTest, SpecialCharacters) {
    auto result = YosysUtils::writeFirrtl("file with spaces.v",
                                          "output.fir", testDataPath);
    EXPECT_TRUE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "");
}

// Несуществующий файл
TEST(OptVerilogTest, NonExistentFile) {
    auto result = YosysUtils::optVerilog("nonexistent.v", "output.v",
                                         testDataPath);
    std::string errorText =
        "Incorrect write_verilog: ERROR: Can't open input file "
        "`../../test/test_data/optimization_utils/nonexistent.v' "
        "for reading: No such file or directory\n\n";
    std::string errorResult = result.commandsOutput["error"];
    EXPECT_EQ(errorResult, errorText);
}

TEST(WriteFirrtlTest, NonExistentFile) {
    auto result = YosysUtils::writeFirrtl("nonexistent.v", "output.fir",
                                        testDataPath);
    EXPECT_TRUE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "");
}

// Неверный путь к директории
TEST(OptVerilogTest, InvalidDirectory) {
    auto result = YosysUtils::optVerilog("correct_filename.v", "output.v",
                                         "invalid_path_to_directory");
    std::string errorText =
        "Incorrect write_verilog: ERROR: Can't open input file "
        "`invalid_path_to_directory/correct_filename.v' "
        "for reading: No such file or directory\n\n";
    std::string errorResult = result.commandsOutput["error"];
    EXPECT_EQ(errorResult, errorText);
}

TEST(WriteFirrtlTest, InvalidDirectory) {
    auto result = YosysUtils::writeFirrtl("correct_filename.v", "output.fir",
                                            "invalid_path_to_directory");
    EXPECT_FALSE(result.correct);
    EXPECT_EQ(result.commandsOutput["fileRead"], "false");
}