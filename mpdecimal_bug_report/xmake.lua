add_rules("mode.debug", "mode.release")
add_requires("mpdecimal")

target("test")
    set_kind("binary")
    add_files("./*.c")
    add_packages("mpdecimal")

