import qbs

CppApplication {
    consoleApplication: true
    files: [
        "main.cpp",
        "primitive_algorithms-impl.h",
        "primitive_algorithms.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++17"
}
