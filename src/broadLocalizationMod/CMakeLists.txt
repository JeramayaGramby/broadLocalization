# Define the module as a static or shared library
add_library(broadLocalizationMod broadLocalizationImpl.cc)

# Public headers
target_include_directories(broadLocalizationMod PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
