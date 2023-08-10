cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

if(NOT TARGET score_lib_base)
  include(ScoreExternalAddon)
endif()

if(NOT TARGET score_plugin_avnd)
  return()
endif()

project(score_addon_basic_model_addon LANGUAGES CXX)

avnd_score_plugin_init(
  BASE_TARGET score_addon_basic_model_addon
)

avnd_score_plugin_add(
  BASE_TARGET score_addon_basic_model_addon
  SOURCES
    basic_model_addon/basic_model_addon.hpp
    basic_model_addon/basic_model_addonModel.hpp
    basic_model_addon/basic_model_addonModel.cpp
    basic_model_addon/basic_model_addonUi.hpp
  TARGET basic_model_addon
  MAIN_CLASS basic_model_addon
  NAMESPACE Example
)

avnd_score_plugin_finalize(
  BASE_TARGET score_addon_basic_model_addon
  PLUGIN_VERSION 1
  PLUGIN_UUID "a1a3bb71-aab1-446f-a897-de7eed02c873"
)
