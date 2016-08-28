import qbs 1.0

QtApplication {
    name: "DataReductionWSN"

    cpp.cppFlags: {
        if (cpp.compilerName.contains("g++")) {
            return "-std=c++11";
        } else if (cpp.compilerName.contains("clang++")) {
            return "-std=c++11";
        }
    }

    files: [
        "data.qrc",
        "src/main.cpp",
        "src/environment.cpp",
        "src/environment.hpp",
        "src/sensor.cpp",
        "src/sensor.hpp",
        "src/simulator.cpp",
        "src/simulator.hpp",
        "src/sink.cpp",
        "src/sink.hpp"
    ]

}
