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
	F-measure_EdgeDetection.exe output_list.txt truth_list.txt
	*/

	std::ifstream input_list(argv[1]);
	std::ifstream truth_list(argv[2]);

	int count = 0;

	int true_positive(0), true_negative(0), false_positive(0), false_negative(0);

	while (!input_list.eof()) { // Assumption : len(input_list) == len(output_list)
		int true_positive_in(0), true_negative_in(0), false_positive_in(0), false_negative_in(0);

		count++;
		std::cout << "Count : " << count << std::endl;
		std::string input_path, truth_path;
		std::getline(input_list, input_path);
		std::getline(truth_list, truth_path);
		cv::Mat inputImg = cv::imread(input_path, cv::IMREAD_GRAYSCALE);
		cv::Mat truthImg = cv::imread(truth_path, cv::IMREAD_GRAYSCALE);

		cv::Mat inputBinary, truthBinary;
		cv::threshold(inputImg, inputBinary, 127, 255, cv::THRESH_BINARY);
		cv::threshold(truthImg, truthBinary, 127, 255, cv::THRESH_BINARY);

		if (inputBinary.size() != truthBinary.size()) {
			std::cout << "[Warning] img size is not same!\n";
			continue;
		}

		for (int j = 0; j < truthBinary.rows; ++j) {
			for (int i = 0; i < truthBinary.cols; ++i) {
				unsigned char pixel = truthImg.at<unsigned char>(j, i);
				bool isEqual = (truthBinary.at<unsigned char>(j, i) == inputBinary.at<unsigned char>(j, i));
				if (pixel == 255) { // white
					if (isEqual)
						true_positive_in++;
					else
						false_negative_in++;
				}
				else { // pixel == 0, black
					if (isEqual)
						true_negative_in++;
					else
						false_positive_in++;
				}
			}

		}

		double precision_in = (double)true_positive_in / (true_positive_in + false_positive_in);
		double recall_in = (double)true_positive_in / (true_positive_in + false_negative_in);
		double Fmeasure_in = 2 * precision_in * recall_in / (precision_in + recall_in);
		std::cout << "Precision is " << precision_in << std::endl;
		std::cout << "Recall is " << recall_in << std::endl;
		std::cout << "F-measure is " << Fmeasure_in << std::endl << std::endl;

		false_positive += false_positive_in;
		false_negative += false_negative_in;
		true_positive += true_positive_in;
		true_negative += true_negative_in;
	}

	double precision = (double)true_positive / (true_positive + false_positive);
	double recall = (double)true_positive / (true_positive + false_negative);
	double Fmeasure = 2 * precision * recall / (precision + recall);

	std::cout << "****************************************" << std::endl;
	std::cout << "OVERALL";
	std::cout << "Precision is " << precision << std::endl;
	std::cout << "Recall is " << recall << std::endl;
	std::cout << "F-measure is " << Fmeasure << std::endl;

	input_list.close();
	truth_list.close();

	return 0;

}
