# Add the broadLocalizationMod subdirectory
add_subdirectory(broadLocalizationMod)

# Define the main executable
add_executable(broadLocalization main.cc)

# Link the module library
target_link_libraries(broadLocalization PRIVATE broadLocalizationMod)

# If main.cc needs headers from the mod, include them
target_include_directories(broadLocalization PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/broadLocalizationMod)
