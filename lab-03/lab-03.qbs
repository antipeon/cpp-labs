import qbs

CppApplication {
    consoleApplication: true
    files: [
        "main.cpp",
        "pugixml-1.11/src/pugixml.cpp",
        "transportation_dataset.cpp",
        "transportation_dataset.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++17"
}
