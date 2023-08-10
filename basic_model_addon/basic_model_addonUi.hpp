#pragma once
#include <basic_model_addon/basic_model_addonModel.hpp>
#include <halp/layout.hpp>

namespace Example
{
struct basic_model_addon::ui
{
  using enum halp::colors;
  using enum halp::layouts;

  halp_meta(name, "Main")
  halp_meta(layout, vbox)
  halp_meta(background, dark)

  halp::label title{"My First Processor"};
  halp::item<&ins::gain> gain;
};
}
