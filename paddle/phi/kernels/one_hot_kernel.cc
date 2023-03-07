// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "paddle/phi/kernels/one_hot_kernel.h"

#include "paddle/phi/backends/all_context.h"
#include "paddle/phi/core/kernel_registry.h"

namespace phi {

template <typename T, typename Context>
void OneHotKernel(const Context& dev_ctx,
                  const DenseTensor& x,
                  const Scalar& num_classes_s,
                  DenseTensor* out) {
  OneHotRawKernel<T>(
      dev_ctx, x, num_classes_s, phi::DataType::FLOAT32, false, out);
}

}  // namespace phi

PD_REGISTER_KERNEL(one_hot, CPU, ALL_LAYOUT, phi::OneHotKernel, int, int64_t) {
  kernel->OutputAt(0).SetDataType(paddle::experimental::DataType::FLOAT32);
}

#if defined(PADDLE_WITH_CUDA) || defined(PADDLE_WITH_HIP)
PD_REGISTER_KERNEL(one_hot, GPU, ALL_LAYOUT, phi::OneHotKernel, int, int64_t) {
  kernel->OutputAt(0).SetDataType(paddle::experimental::DataType::FLOAT32);
}
#endif

#ifdef PADDLE_WITH_XPU
PD_REGISTER_KERNEL(one_hot, XPU, ALL_LAYOUT, phi::OneHotKernel, int, int64_t) {
  kernel->OutputAt(0).SetDataType(paddle::experimental::DataType::FLOAT32);
}
#endif
