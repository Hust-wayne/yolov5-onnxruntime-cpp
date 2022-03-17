cmake_minimum_required(VERSION 3.0.0)
project(yolo_ort)

set(ONNXRUNTIME_DIR "/home/wayne/projects/onnxruntime-cpp/onnxruntime-linux-x64-gpu-1.10.0")
message(STATUS "ONNXRUNTIME_DIR: ${ONNXRUNTIME_DIR}")

find_package(OpenCV REQUIRED)

# setup CUDA
find_package(CUDA REQUIRED)
message(STATUS "    libraries: ${CUDA_LIBRARIES}")
message(STATUS "    include path: ${CUDA_INCLUDE_DIRS}")

include_directories(${CUDA_INCLUDE_DIRS})


include_directories("include/")

add_executable(yolo_ort
               src/main.cpp
               src/detector.cpp
               src/utils.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(yolo_ort PRIVATE "${ONNXRUNTIME_DIR}/include")
target_compile_features(yolo_ort PRIVATE cxx_std_14)
target_link_libraries(yolo_ort ${OpenCV_LIBS})
#target_link_libraries(yolo_ort cudart)

if (WIN32)
    target_link_libraries(yolo_ort "${ONNXRUNTIME_DIR}/lib/onnxruntime.lib")
endif(WIN32)

if (UNIX)
    target_link_libraries(yolo_ort "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")
endif(UNIX)

