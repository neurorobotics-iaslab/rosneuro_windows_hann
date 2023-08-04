# ROS-Neuro Hann window

This ROS-Neuro filter plugin applies an Hann window to the provided data.

## Algorithm:
The filter applies the Hann window to the data. The hann window is implemented as follows:
```cpp
	int nsamples;
	for(auto i = 0; i<nsamples; i++)
		window.at(i) = (1.0 - cos((2.0 * M_PI * i)/(nsamples-1))) * 0.5;
```
The provided window filters do not required mandatory parameters but the name and the type.
An example of the YAML configuration:
```
HannCfgTest:
  name: hann
  type: hannWindowFloat
```
