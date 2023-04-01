#include <iostream>

#include "common_test/enum_classes.h"
#include "bettertest/run.h"

#ifdef WIN32
#include "Windows.h"
#endif

int main(int argc, char** argv)
{
    // Set path next to executable.
#ifdef WIN32
    {
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(NULL, path, MAX_PATH);
        std::filesystem::path workdir(path);
        const auto            p = workdir.parent_path();
        std::filesystem::current_path(p);
    }
#endif
    return bt::run<test::EnumClassOr,
                   test::EnumClassAnd,
                   test::EnumClassNot,
                   test::EnumClassToIntegral,
                   test::EnumClassReduction>(argc, argv, "common");
}
