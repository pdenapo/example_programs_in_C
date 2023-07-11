
add_requires("gtk4")

target("hello")
    set_kind("binary")
    add_files("./main.c")
    add_packages("gtk4")
    

    