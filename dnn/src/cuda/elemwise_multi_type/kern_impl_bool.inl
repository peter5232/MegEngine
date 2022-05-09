#pragma once

#ifndef KERN_IMPL_MODE
#error "KERN_IMPL_MODE, KERN_IMPL_ARITY, KERN_IMPL_STYPE, KERN_IMPL_DTYPE must be defined"
#endif

#include "src/cuda/elemwise_multi_type/kern_ops.cuh"

namespace megdnn {
namespace cuda {

#define cb(_m)                                                                     \
    typedef ElemwiseBoolKern<                                                      \
            megcorePlatformCUDA, param_enumv::Elemwise::Mode::_m, KERN_IMPL_STYPE, \
            KERN_IMPL_DTYPE>                                                       \
            KernImpl;                                                              \
    typedef kern_ops_quantized::QuantizedMultiTypeOp<                              \
            KERN_IMPL_ARITY, KERN_IMPL_STYPE, KERN_IMPL_DTYPE, KernImpl>           \
            Op;                                                                    \
    INST_RUN_ELEMWISE(Op, KERN_IMPL_STYPE, KERN_IMPL_ARITY);

KERN_IMPL_MODE(cb)

}  // namespace cuda
}  // namespace megdnn

// vim: syntax=cpp.doxygen
