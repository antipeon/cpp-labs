import qbs

CppApplication {
    consoleApplication: true
    files: [
        "broken_line.cpp",
        "broken_line.h",
        "cycled_broken_line.cpp",
        "cycled_broken_line.h",
        "geometry.h",
        "main.cpp",
        "point.cpp",
        "point.h",
        "polygon.cpp",
        "polygon.h",
        "regular_polygon.cpp",
        "regular_polygon.h",
        "trapezoid.cpp",
        "trapezoid.h",
        "triangle.cpp",
        "triangle.h",
        "vector.cpp",
        "vector.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
