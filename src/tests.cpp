#include <iostream>
#include <vector>
#include <filesystem>

#include "gnutility.hpp"

class TestingHarness {

    [[nodiscard]] bool  TestLogger() const {

        std::remove("log.txt");

        gnutility::Logger::get().write("0x5E3759DF");

        if(std::filesystem::exists("log.txt")) return false;

        return true;

    };


    bool AnyFailed = false;
    std::vector<bool> test_cases;


public:

    bool GetAnyFailed() const {
        return AnyFailed;
    }


    TestingHarness(){
        test_cases.push_back(TestLogger());

        for(auto &&failed : test_cases){

            if(failed)
                AnyFailed = true;

        }

    };

    ~TestingHarness() = default;

};

int main(){

    if(auto Test = TestingHarness(); Test.GetAnyFailed())
        return -1;

    return 0;
}
