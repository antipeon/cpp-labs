import qbs

CppApplication {
    consoleApplication: true
    files: [
        "circular_buffer-impl.hpp",
        "circular_buffer.hpp",
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++17"
}
