#include <cassert>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "gnutility.hpp"

class TestingHarness {

    [[nodiscard]] bool  TestLogger() const {

        std::remove("log.txt");

        gnutility::Logger.write("0x5E3759DF");

        return !std::filesystem::exists("log.txt");

    };

    [[nodiscard]] bool  TestSettings() const {

        return *gnutility::Cfg.ConfigValue("debug") != "test";

    }

    bool AnyFailed = false;

    std::vector<bool> test_cases;

public:

    bool GetAnyFailed() const {

        return AnyFailed;

    }


    TestingHarness(){

        /* Test Logger singleton */
        test_cases.push_back(TestLogger());

        /* Test Settings parser */
        test_cases.push_back(TestSettings());

        for(auto &&failed : test_cases)
            if(failed)
                AnyFailed = true;        

    };

    ~TestingHarness() = default;

};


int main(){

    if(auto Test = TestingHarness(); Test.GetAnyFailed())
        return 1;

    return 0;

}

