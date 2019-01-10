#include "csv_writer.hh"
#include "compute.hh"
#include "compute_temperature.hh"
#include "material_points_factory.hh"
#include "particles_factory_interface.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"
#include "system_evolution.hh"
#include <functional>
#include <iostream>
#include <pybind11/chrono.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;
//PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>, true);
PYBIND11_MODULE(pypart, m) {
  m.doc() = "pybinding for the particle codes"; // optional docstring

  py::class_<System>(m, "System");

  py::class_<SystemEvolution, std::shared_ptr<SystemEvolution>>(m, "SystemEvolution")
      .def("addCompute", [](SystemEvolution &system_evolution,
                            const std::shared_ptr<Compute> &compute) {
        system_evolution.addCompute(compute);
      })
    .def("setNSteps", &SystemEvolution::setNSteps)
    .def("setDumpFreq", &SystemEvolution::setDumpFreq)
    .def("evolve", &SystemEvolution::evolve)
    .def("getSystem", &SystemEvolution::getSystem)
    ;

  py::class_<ParticlesFactoryInterface,
             std::shared_ptr<ParticlesFactoryInterface>>(
      m, "ParticlesFactoryInterface")
      .def("getInstance", &ParticlesFactoryInterface::getInstance,
           py::return_value_policy::reference)
      .def_property("system_evolution",
                    &ParticlesFactoryInterface::getSystemEvolution,
                    &ParticlesFactoryInterface::setSystemEvolution);

  py::class_<MaterialPointsFactory, std::shared_ptr<MaterialPointsFactory>, ParticlesFactoryInterface>(
      m, "MaterialPointsFactory")
      .def("getInstance", &MaterialPointsFactory::getInstance,
           py::return_value_policy::reference)
      .def("createSimulation",
           py::overload_cast<const std::string &, Real, py::function>(
               &MaterialPointsFactory::createSimulation<py::function>),
           py::return_value_policy::reference);

  py::class_<PlanetsFactory, std::shared_ptr<PlanetsFactory>, ParticlesFactoryInterface>(
              m, "PlanetsFactory")
      .def("getInstance", &PlanetsFactory::getInstance,
           py::return_value_policy::reference)
      .def("createSimulation",
           py::overload_cast<const std::string &, Real, bool>(
               &ParticlesFactoryInterface::createSimulation),
           py::return_value_policy::reference);

  py::class_<PingPongBallsFactory, std::shared_ptr<PingPongBallsFactory>, ParticlesFactoryInterface>(
      m, "PingPongBallsFactory")
      .def("getInstance", &PingPongBallsFactory::getInstance,
           py::return_value_policy::reference)
      .def("createSimulation",
           py::overload_cast<const std::string &, Real, bool>(
               &PingPongBallsFactory::createSimulation),
           py::return_value_policy::reference);

  py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute");

  py::class_<ComputeTemperature, std::shared_ptr<ComputeTemperature>, Compute>(m, "ComputeTemperature")
      .def(py::init<>())
      // give read write access through acessors :
      .def_property("conductivity", &ComputeTemperature::getConductivityK,
                    &ComputeTemperature::setConductivityK)
      .def_property("capacity", &ComputeTemperature::getCapacity,
                    &ComputeTemperature::setCapacity)
      .def_property("density", &ComputeTemperature::getDensity,
                    &ComputeTemperature::setDensity)
      .def_property("deltat", &ComputeTemperature::getDeltaT,
                    &ComputeTemperature::setDeltaT)
      .def_property("L", &ComputeTemperature::getLength,
                    &ComputeTemperature::setLength)
      .def("compute", &ComputeTemperature::compute);
