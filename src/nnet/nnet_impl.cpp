#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
// this is where the actual implementations are
#include "nnet_impl-inl.hpp"
// specialize the cpu implementation
namespace cxxnet {
namespace nnet {
template<>
GLINetTrainer* CreateNet<cpu>(int net_type) {
  return CreateNet_<cpu>(net_type);
}
#if MSHADOW_USE_CUDA == 0
template<>
GLINetTrainer* CreateNet<gpu>(int net_type) {
  utils::Error("CUDA is not supported");
  return NULL;
}
#endif
}  // namespace nnet
}  // namespace cxxnet
