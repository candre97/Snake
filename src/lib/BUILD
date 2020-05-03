# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "GameLib",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":SnakeLib",
        "@ncurses//:main",
    ],
)

cc_library(
    name = "SnakeLib",
    srcs = ["snake.cc"],
    hdrs = ["snake.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@ncurses//:main",
    ],
)
