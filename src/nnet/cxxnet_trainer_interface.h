#ifndef CXXNET_TRAINER_INTERFACE_HPP
#define CXXNET_TRAINER_INTERFACE_HPP
//#include <string>
//#include <vector>
#include <map>
#include "./nnet.h"

namespace dmlc{
class Stream;
}

namespace cxxnet{

namespace utils{
typedef dmlc::Stream IStream;
}

class DataBatch;
template <typename T>
class IIterator;


/*! \brief interface for network */
    class GLINetTrainer : public nnet::INetTrainer{
    public:
        /*! \brief print the cumulative training evaluation */
        virtual std::string PrintTrainEvaluate() = 0;
        /*! \brief print the cumulative training evaluation */
        virtual std::map<std::string,float> GetTrainEvaluate() = 0;
        /*! \brief clear the cumulative training evaluatinon */
        virtual void ClearTrainEvaluate() = 0;
        /*! \brief  evaluate a test statistics, output results into fo */
        virtual std::string Evaluate( IIterator<DataBatch> *iter_eval, const char* evname ) = 0;
        /*! \brief  evaluate test statistics, output name and result */      
        virtual std::map<std::string, std::vector<float> > EvalMetrics( IIterator<DataBatch> *iter_eval, const std::vector<std::string>& metrics ) = 0;
        /*! \brief predict topk */
        virtual void PredictTopK( std::vector< std::pair<float,index_t> > &preds, const DataBatch& batch, index_t topk ) = 0;
    };


namespace nnet{
/*!
 * \brief create a net implementation
 * \param net_type network type, used to select trainer variants
 * \tparam device type the net lies
 */
template<typename xpu>
GLINetTrainer* CreateNet(int net_type);
}  // namespace nnet
}// namespace cxxnet
#endif
