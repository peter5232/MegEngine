// generated by gen_elemwise_multi_type_kern_impls_bool.py
#define KERN_IMPL_MODE(cb) MEGDNN_ELEMWISE_MODE_ENABLE(ISINF, cb)
#define KERN_IMPL_ARITY    1
#define KERN_IMPL_STYPE    dt_float16
#define KERN_IMPL_DTYPE    dt_bool
#include "../kern_impl_bool.inl"
