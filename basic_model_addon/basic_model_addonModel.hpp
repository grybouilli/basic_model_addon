#pragma once

#include <halp/audio.hpp>
#include <halp/controls.hpp>
#include <halp/meta.hpp>
#include <halp/file_port.hpp>
#include <ATen/core/ivalue.h>
#include <torch/script.h>
namespace Example
{

    class basic_model_addon
    {
    public:
        halp_meta(name, "Basic Model Addon")
        halp_meta(category, "Audio")
        halp_meta(c_name, "basic_model_addon")
        halp_meta(uuid, "fa596ddc-d7cc-423c-951e-1a53d8974231")

        // Define inputs and outputs ports.
        // See the docs at https://github.com/celtera/avendish
        struct model_info
        {
            torch::jit::script::Module  model;
            bool                        model_loaded;
        } model_data;

        struct
        {
            struct {
                static consteval auto name() { return "in"; }
                float value;
            } in;
            struct : halp::file_port<"Traced model file"> {
                void update(basic_model_addon& obj) {
                    obj.model_data.model_loaded = obj.load_model();
                }
            } model_file;
        } inputs;

        struct
        {
            struct {
                static consteval auto name() { return "out"; }
                float value;
            } out;
        } outputs;

        using setup = halp::setup;
        void prepare(halp::setup info)
        {
            model_data.model_loaded = false;
            model_data.model_loaded = load_model();
        }

        bool load_model()
        {
            std::string filename { inputs.model_file.file.filename };
            try
            {
                // Deserialize the Scriptmodel from a file using torch::jit::load().
                model_data.model = torch::jit::load(filename);
            }
            catch (const c10::Error& e)
            {
                std::cerr << "error loading the model : " << filename << "\n";
                return false;
            }

            std::cout << "Module : " << filename << " loaded\n";

            return true;
        }

        // Do our processing for N samples
        using tick = halp::tick;

        // Defined in the .cpp
        void operator()(halp::tick t);

        // UI is defined in another file to keep things clear.
        struct ui;
    };

}
