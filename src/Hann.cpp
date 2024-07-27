#include "rosneuro_windows_hann/Hann.hpp"
#include "pluginlib/class_list_macros.h"

PLUGINLIB_EXPORT_CLASS(rosneuro::Hann<int>,    rosneuro::Window<int>)
PLUGINLIB_EXPORT_CLASS(rosneuro::Hann<float>,  rosneuro::Window<float>)
PLUGINLIB_EXPORT_CLASS(rosneuro::Hann<double>, rosneuro::Window<double>)

