#include <ros/ros.h>
#include <rosneuro_filters/rosneuro_filters_utilities.hpp>
#include "rosneuro_windows_hann/Hann.hpp"

int main(int argc, char** argv) {
	ros::init(argc, argv, "hann_window");
	std::string datapath;
	rosneuro::Window<double>* hann = new rosneuro::Hann<double>();

	if(ros::param::get("~datapath", datapath) == false) {
		ROS_ERROR("Cannot find 'datapath' parameter");
		return 0;
	}
	
	const std::string fileinput = datapath + "/example/rawdata.csv";
	const std::string fileout   = datapath + "/example/hann_window.csv";
	rosneuro::DynamicMatrix<double> input = readCSV<double>(fileinput);
	
	ros::WallTime start_hann, stop_hann;
	ROS_INFO("Applying filter");
	start_hann = ros::WallTime::now();
	rosneuro::DynamicMatrix<double> output = hann->apply(input);
	stop_hann = ros::WallTime::now();

	ROS_INFO("Hann applied on data in %9.6f ms", ((stop_hann-start_hann).toNSec())/1000.0f);

	writeCSV<double>(fileout, output);
	ros::shutdown();
	return 0;
}
