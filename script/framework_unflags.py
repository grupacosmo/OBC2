# blackpill_f411ce packages uses the register keyword
# this script suppreses the warning in c++17 build
# where register is deprecated keyword

Import("env")

framework_unflags = [ "-Wno-register", "-Wno-deprecated-declarations", "-Wno-address-of-packed-member" ]

env.Append(
    CXXFLAGS = framework_unflags
)