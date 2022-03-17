# yolov5-onnxruntime

C++ YOLO v5 ONNX Runtime inference code for object detection.

## Dependecies:
- OpenCV 4.x
- ONNXRuntime 1.7+
- OS: Tested on Windows 11 and Ubuntu 20.04-WSL
- CUDA 11+ [Optional]


## Build
To build the project you should run the following commands, don't forget to change `ONNXRUNTIME_DIR` cmake option:

```bash
mkdir build
cd build
cmake ..
make
```

## Run
`On Windows`: to run the executable you should add OpenCV and ONNX Runtime libraries to your environment path `or` put all needed libraries near the executable (onnxruntime.dll and opencv_world.dll).

Run from CLI:
```bash
./yolo_ort
```

