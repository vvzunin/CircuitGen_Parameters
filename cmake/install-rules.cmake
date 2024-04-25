install(
    TARGETS OptimizationsVerilogLib
    RUNTIME COMPONENT OptimizationsVerilogLib_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/OptimizationsVerilogLib-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package OptimizationsVerilogLib)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT OptimizationsVerilogLib_Development
)

# install(
#     TARGETS OptimizationsVerilogLib
#     EXPORT OptimizationsVerilogLibTargets
#     RUNTIME #
#     COMPONENT OptimizationsVerilogLib_Runtime
#     LIBRARY #
#     COMPONENT OptimizationsVerilogLib_Runtime
#     NAMELINK_COMPONENT OptimizationsVerilogLib_Development
#     ARCHIVE #
#     COMPONENT OptimizationsVerilogLib_Development
#     INCLUDES #
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
# )

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    OptimizationsVerilogLib_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE OptimizationsVerilogLib_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(OptimizationsVerilogLib_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${OptimizationsVerilogLib_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT OptimizationsVerilogLib_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${OptimizationsVerilogLib_INSTALL_CMAKEDIR}"
    COMPONENT OptimizationsVerilogLib_Development
)

# install(
#     EXPORT OptimizationsVerilogLibTargets
#     NAMESPACE OptimizationsVerilogLib::
#     DESTINATION "${OptimizationsVerilogLib_INSTALL_CMAKEDIR}"
#     COMPONENT OptimizationsVerilogLib_Development
# )

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
