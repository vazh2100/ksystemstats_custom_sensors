cmake_minimum_required(VERSION 3.16)

project(ksystemstats_plugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
add_compile_options(-fexceptions)


set(KSYSGUARD_VERSION "6.2.4")
set(QT_MIN_VERSION "6.7.0")
set(KF6_MIN_VERSION "6.8.0")
set(KDE_COMPILERSETTINGS_LEVEL "5.82")


find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(CheckIncludeFiles)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)
include(FeatureSummary)
include(ECMConfiguredInstall)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core)
find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS CoreAddons)
find_package(KSysGuard ${KSYSGUARD_VERSION} REQUIRED)

add_library(ksystemstats_plugin MODULE
  ksystemstatsplugin.cpp
  ksystemstatsplugin.h
)

target_link_libraries(ksystemstats_plugin
PRIVATE KF6::CoreAddons KSysGuard::SystemStats
)
set(KSYSTEMSTATS_PLUGIN_INSTALL_DIR ${KDE_INSTALL_PLUGINDIR}/ksystemstats)
install(TARGETS ksystemstats_plugin DESTINATION ${KSYSTEMSTATS_PLUGIN_INSTALL_DIR})
