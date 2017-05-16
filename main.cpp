#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout << "You need proper args\n";
		return 0;
	}

	/*
	F-measure_EdgeDetection.exe input_list.txt truth_list.txt
	*/

	std::ifstream input_list(argv[1]);
	std::ifstream truth_list(argv[2]);

	int count = 0;

	int true_positive(0), true_negative(0), false_positive(0), false_negative(0);

	while (!input_list.eof()) { // Assumption : len(input_list) == len(output_list)
		count++;
		
		std::string input_path, truth_path;
		std::getline(input_list, input_path);
		std::getline(truth_list, truth_path);
		cv::Mat inputImg = cv::imread(input_path, cv::IMREAD_GRAYSCALE);
		cv::Mat truthImg = cv::imread(truth_path, cv::IMREAD_GRAYSCALE);

		cv::Mat inputBinary, truthBinary;
		cv::threshold(inputImg, inputBinary, 127, 255, cv::THRESH_BINARY);
		cv::threshold(truthImg, truthBinary, 127, 255, cv::THRESH_BINARY);

		if (inputBinary.size() != truthBinary.size()) {
			std::cout << "[Warning] count : " << count << ", img size is not same!\n";
			continue;
		}

		for (int j = 0; j = truthBinary.rows; ++j) {
			for (int i = 0; i = truthBinary.cols; ++i) {
				unsigned char pixel = truthImg.at<unsigned char>(j, i);
				bool isEqual = (truthBinary.at<unsigned char>(j, i) == inputBinary.at<unsigned char>(j, i));
				if (pixel == 255) { // white
					if (isEqual)
						true_positive++;
					else
						false_negative++;
				}
				else { // pixel == 0, black
					if (isEqual)
						true_negative++;
					else
						false_positive++;
				}
			}
		}
	}

	double precision = (double)true_positive / (true_positive + false_positive);
	double recall = (double)true_positive / (true_positive + false_negative);
	double Fmeasure = 2 * precision * recall / (precision + recall);
	
	std::cout << "Precision is " << precision << std::endl;
	std::cout << "Recall is " << recall << std::endl;
	std::cout << "F-measure is " << Fmeasure << std::endl;

	input_list.close();
	truth_list.close();

	return 0;

}
