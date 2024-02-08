//
// Created by ohf4fe on 08.02.24.
//
#include "python_function.hpp"

#include <pybind11/pybind11.h>

#include <utility>
#include <memory>

namespace cloe::py {
PythonFunction::PythonFunction(CallbackFunction py_fun, std::string_view name)
    : cloe::Action(std::string(name)), py_fun_(std::move(py_fun)) {}
ActionPtr PythonFunction::clone() const { return std::make_unique<PythonFunction>(*this); }
CallbackResult PythonFunction::operator()(const Sync& sync, TriggerRegistrar& /*registrar*/) {
  try {
    pybind11::gil_scoped_acquire gil;
    return py_fun_(sync);
  } catch (const std::exception &e) {
    throw cloe::Error("error executing Python function: {}", e.what());
  }
}
void PythonFunction::to_json(Json& j) const { j = {}; }

}
