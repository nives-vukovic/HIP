/*
Copyright (c) 2015 - 2021 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "hip/hip_runtime.h"

texture<float, 2, hipReadModeElementType> ftex;
texture<int, 2, hipReadModeElementType> itex;
texture<short, 2, hipReadModeElementType> stex;
texture<char, 2, hipReadModeElementType> ctex;

__device__ float deviceGlobalFloat;

extern "C" __global__ void tex2dKernelFloat(float* outputData,
                                       int width, int height) {
#if !defined(__HIP_NO_IMAGE_SUPPORT) || !__HIP_NO_IMAGE_SUPPORT
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  int y = blockIdx.y * blockDim.y + threadIdx.y;
  if ((x < width) && (y < width)) {
    outputData[y * width + x] = tex2D(ftex, x, y);
  }
#endif
}

extern "C" __global__ void tex2dKernelInt(int* outputData,
                                          int width, int height) {
#if !defined(__HIP_NO_IMAGE_SUPPORT) || !__HIP_NO_IMAGE_SUPPORT
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  int y = blockIdx.y * blockDim.y + threadIdx.y;
  if ((x < width) && (y < width)) {
    outputData[y * width + x] = tex2D(itex, x, y);
  }
#endif
}

extern "C" __global__ void tex2dKernelInt16(short* outputData,
                                          int width, int height) {
#if !defined(__HIP_NO_IMAGE_SUPPORT) || !__HIP_NO_IMAGE_SUPPORT
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  int y = blockIdx.y * blockDim.y + threadIdx.y;
  if ((x < width) && (y < width)) {
    outputData[y * width + x] = tex2D(stex, x, y);
  }
#endif
}

extern "C" __global__ void tex2dKernelInt8(char* outputData,
                                          int width, int height) {
#if !defined(__HIP_NO_IMAGE_SUPPORT) || !__HIP_NO_IMAGE_SUPPORT
  int x = hipBlockIdx_x * hipBlockDim_x + hipThreadIdx_x;
  int y = hipBlockIdx_y * hipBlockDim_y + hipThreadIdx_y;
  if ((x < width) && (y < width)) {
    outputData[y * width + x] = tex2D(ctex, x, y);
  }
#endif
}
