#pragma once

#include "megdnn/oprs/nn.h"

#include "src/common/utils.h"

namespace megdnn {
namespace cambricon {

class ConvolutionForwardImpl : public ConvolutionForward {
public:
    using ConvolutionForward::ConvolutionForward;
    void exec(
            _megdnn_tensor_in src, _megdnn_tensor_in filter, _megdnn_tensor_out dst,
            const PreprocessedFilter* preprocessed_filter,
            _megdnn_workspace workspace) override;
    std::vector<Algorithm*> get_all_algorithms(
            const TensorLayout& src, const TensorLayout& filter,
            const TensorLayout& dst) override;
    std::vector<Algorithm*> get_all_algorithms_safe(
            const TensorLayout& src, const TensorLayout& filter,
            const TensorLayout& dst) override;
    Algorithm* get_algorithm_heuristic(
            const TensorLayout& src, const TensorLayout& filter,
            const TensorLayout& dst, size_t workspace_limit_in_bytes,
            const AlgoAttribute& positive_attr,
            const AlgoAttribute& negative_attr) override;
    size_t get_workspace_in_bytes(
            const TensorLayout& src, const TensorLayout& filter,
            const TensorLayout& dst, const PreprocessedFilter*) override;

    size_t get_preprocess_workspace_in_bytes(
            const TensorLayout&, const TensorLayout&, const TensorLayout&) override {
        return 0;
    }

    void exec_preprocess(
            const TensorLayout&, _megdnn_tensor_in, const TensorLayout&,
            PreprocessedFilter*, _megdnn_workspace) override {
        megdnn_throw("convolution exec_preprocess has not implemented yet");
    }

    SmallVector<TensorLayout> deduce_preprocessed_filter_layout(
            const TensorLayout&, const TensorLayout&, const TensorLayout&) override {
        return {};
    }
    const char* get_algorithm_set_name() const override;

    Algorithm* get_algorithm_from_desc(const AlgorithmDesc& desc) override;

    class AlgoBase;
    class AlgoDefault;
    class AlgoPack;

    static const AlgoPack& algo_pack() { return sm_algo_pack; }

private:
    static AlgoPack sm_algo_pack;
};

/**
 * BackWardData opr.
 */
class ConvolutionBackwardDataImpl : public ConvolutionBackwardData {
public:
    using ConvolutionBackwardData::ConvolutionBackwardData;
    void exec(
            _megdnn_tensor_in filter, _megdnn_tensor_in diff, _megdnn_tensor_out grad,
            _megdnn_workspace workspace) override;

    std::vector<Algorithm*> get_all_algorithms(
            const TensorLayout& filter, const TensorLayout& diff,
            const TensorLayout& grad) override;

    std::vector<Algorithm*> get_all_algorithms_safe(
            const TensorLayout& filter, const TensorLayout& diff,
            const TensorLayout& grad) override;

    Algorithm* get_algorithm_heuristic(
            const TensorLayout& filter, const TensorLayout& diff,
            const TensorLayout& grad, size_t workspace_limit_in_bytes,
            const AlgoAttribute& positive_attr,
            const AlgoAttribute& negative_attr) override;

    size_t get_workspace_in_bytes(
            const TensorLayout& filter, const TensorLayout& diff,
            const TensorLayout& grad) override;

    const char* get_algorithm_set_name() const override {
        return "ConvBackWard_Data_DEFAULT";
    }

    Algorithm* get_algorithm_from_desc(const AlgorithmDesc& desc) override;

    class AlgoBase;
    class AlgoDefault;
    class AlgoPack;

    static const AlgoPack& algo_pack() { return sm_algo_pack; }

private:
    static AlgoPack sm_algo_pack;
};

/**
 * BackWardFilter opr.
 */
class ConvolutionBackwardFilterImpl : public ConvolutionBackwardFilter {
public:
    using ConvolutionBackwardFilter::ConvolutionBackwardFilter;
    void exec(
            _megdnn_tensor_in src, _megdnn_tensor_in diff, _megdnn_tensor_out grad,
            _megdnn_workspace workspace) override;

    std::vector<Algorithm*> get_all_algorithms(
            const TensorLayout& src, const TensorLayout& diff,
            const TensorLayout& grad) override;

    std::vector<Algorithm*> get_all_algorithms_safe(
            const TensorLayout& src, const TensorLayout& diff,
            const TensorLayout& grad) override;

    Algorithm* get_algorithm_heuristic(
            const TensorLayout& src, const TensorLayout& diff, const TensorLayout& grad,
            size_t workspace_limit_in_bytes, const AlgoAttribute& positive_attr,
            const AlgoAttribute& negative_attr) override;

    size_t get_workspace_in_bytes(
            const TensorLayout& src, const TensorLayout& diff,
            const TensorLayout& grad) override;

    const char* get_algorithm_set_name() const override {
        return "ConvBackWard_Filter_DEFAULT";
    }

    Algorithm* get_algorithm_from_desc(const AlgorithmDesc& desc) override;

    class AlgoBase;
    class AlgoDefault;
    class AlgoPack;

    static const AlgoPack& algo_pack() { return sm_algo_pack; }

private:
    static AlgoPack sm_algo_pack;
};

}  // namespace cambricon
}  // namespace megdnn

// vim: syntax=cpp.doxygen
