#include <gtest/gtest.h>
#include <ros/package.h>
#include <rosneuro_filters/rosneuro_filters_utilities.hpp>
#include "Hann.hpp"

namespace rosneuro {
    class HannTestSuite : public ::testing::Test {
        public:
            HannTestSuite() {}
            ~HannTestSuite() {}
            void SetUp() { hann_filter = new Hann <double>(); }
            void TearDown() { delete hann_filter; }
            Hann <double>* hann_filter;
    };

    TEST_F(HannTestSuite, Constructor) {
        ASSERT_EQ(hann_filter->name_, "hann");
        ASSERT_FALSE(hann_filter->is_window_set_);
    }

    TEST_F(HannTestSuite, Configure) {
        ASSERT_TRUE(hann_filter->configure());
    }

    TEST_F(HannTestSuite, ApplyWithValidWindow) {
        DynamicMatrix<double> inputMatrix(3, 3);
        inputMatrix << 1, 2, 3,
                       4, 5, 6,
                       7, 8, 9;
        DynamicMatrix<double> result = hann_filter->apply(inputMatrix);

        ASSERT_EQ(result.rows(), inputMatrix.rows());
        ASSERT_EQ(result.cols(), inputMatrix.cols());

        DynamicMatrix<double> expected(3, 3);
        expected << 0, 0, 0,
                    4, 5, 6,
                    0, 0, 0;

        ASSERT_TRUE(result.isApprox(expected, 0.01));
    }

    TEST_F(HannTestSuite, ApplyWithoutWindow) {
        DynamicMatrix<double> inputMatrix(-1, 0);
        ASSERT_THROW(hann_filter->apply(inputMatrix), std::bad_alloc);
    }

    TEST_F(HannTestSuite, CreateWindowWithValidSamples) {
        ASSERT_TRUE(hann_filter->create_window(1));
    }

    TEST_F(HannTestSuite, CreateWindowWithInvalidSamples) {
        ASSERT_THROW(hann_filter->create_window(-1), std::bad_alloc);
    }

    TEST_F(HannTestSuite, Integration){
        std::string base_path = ros::package::getPath("rosneuro_filters_hann");
        const std::string input_path = base_path + "/test/rawdata.csv";
        const std::string expected_path = base_path + "/test/expected.csv";

        DynamicMatrix<double> input = readCSV<double>(input_path);
        DynamicMatrix<double> expected = readCSV<double>(expected_path);
        DynamicMatrix<double> output = hann_filter->apply(input);

        ASSERT_TRUE(output.isApprox(expected, 1e-6));
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_hann");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}