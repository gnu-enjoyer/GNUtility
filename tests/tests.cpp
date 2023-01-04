#include <cassert>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "gnutility.hpp"

class TestingHarness {

  [[nodiscard]] bool TestLogger() const {

    std::remove("log.txt");

    auto thread_count = std::thread::hardware_concurrency();

    std::vector<std::future<void>> futures{};

    for (unsigned int i = 0; i < thread_count; ++i) {

      futures.emplace_back(std::async(
          std::launch::async, []() { gnutility::Log::write("0x5E3759DF"); }));
    }

    for (auto& i : futures)
      i.wait();

    return !std::filesystem::exists("log.txt");
  };

  [[nodiscard]] bool TestSettings() const {

    auto cfg = gnutility::Settings::ParseJSON("config.json");

    for (auto& i : *cfg) {
      if (i.first != "debug")
        return true;
    }

    return cfg->empty();
  }

  bool AnyFailed = false;

  std::vector<bool> test_cases;

public:
  bool GetAnyFailed() const { return AnyFailed; }

  TestingHarness() {

    /* Test Logger */
    test_cases.push_back(TestLogger());

    /* Test Settings parser */
    test_cases.push_back(TestSettings());

    for (auto&& failed : test_cases)
      if (failed)
        AnyFailed = true;
  };

  ~TestingHarness() = default;
};

int main() {

  if (auto Test = TestingHarness(); Test.GetAnyFailed())
    return 1;

  return 0;
}
