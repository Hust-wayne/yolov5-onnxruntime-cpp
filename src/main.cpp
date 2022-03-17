#include <iostream>
#include <opencv2/opencv.hpp>

#include "cmdline.h"
#include "utils.h"
#include "detector.h"



int main(int argc, char* argv[])
{
    const float confThreshold = 0.3f;
    const float iouThreshold = 0.4f;

   /* cmdline::parser cmd;
    cmd.add<std::string>("model_path", 'm', "path to onnx model.", true, "yolov5.onnx");
    cmd.add<std::string>("image", 'i', "image source to be detected.", true, "bus.jpg");
    cmd.add<std::string>("class_names", 'c', "path to class names file.", true, "coco.names");
    cmd.add("gpu", '\0', "inference on cuda device.");

    cmd.parse_check(argc, argv);

    bool isgpu = cmd.exist("gpu");*/
    bool isGPU = true;
    const std::string classNamesPath = "/home/wayne/projects/onnxruntime-cpp/models/coco.names";
    const std::string imagePath = "/home/wayne/projects/onnxruntime-cpp/images/bus.jpg";
    const std::string modelPath = "/home/wayne/projects/onnxruntime-cpp/models/yolov5s.onnx";

    //const std::string classNamesPath = cmd.get<std::string>("class_names");
    const std::vector<std::string> classNames = utils::loadNames(classNamesPath);
    //const std::string imagePath = cmd.get<std::string>("image");
    //const std::string modelPath = cmd.get<std::string>("model_path");

    if (classNames.empty())
    {
        std::cerr << "Error: Empty class names file." << std::endl;
        return -1;
    }

    YOLODetector detector {nullptr};
    cv::Mat image;
    std::vector<Detection> result;

    try
    {
        detector = YOLODetector(modelPath, isGPU, cv::Size(640, 640));
        std::cout << "Model was initialized." << std::endl;

        image = cv::imread(imagePath);
        result = detector.detect(image, confThreshold, iouThreshold);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    utils::visualizeDetection(image, result, classNames);

    // cv::imshow("result", image);
    cv::imwrite("result.jpg", image);
    // cv::waitKey(0);

    return 0;
}
