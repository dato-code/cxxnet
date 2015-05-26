#ifndef CXXNET_TRAINER_INTERFACE_HPP
#define CXXNET_TRAINER_INTERFACE_HPP
#include <string>
#include <vector>
#include <map>
#include "../utils/io.h"
namespace cxxnet{

class DataBatch;
template <typename T>
class IIterator;


/*! \brief interface for network */
    class INetTrainer{
    public:
        virtual ~INetTrainer( void ){}
        /*! \brief set model parameters, call this before everything, including load model */
        virtual void SetParam( const char *name, const char *val ) = 0;
        /*! \brief random initalize model */
        virtual void InitModel( void ) = 0;
        /*! \brief save model to stream */
        virtual void SaveModel( utils::IStream &fo ) const = 0;
        /*! \brief load model from stream */
        virtual void LoadModel( utils::IStream &fi ) = 0;
        /*!
         * \brief inform the updater that a new round has been started
         * \param round round counter
         */
        virtual void StartRound( int round ) = 0;
        /*!
         * \brief update model parameter
         * \param training data batch
         */
        virtual void Update( const DataBatch& data ) = 0;

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

        virtual void FeatureExtract(std::vector<std::vector <double> > &feats, const DataBatch& batch, size_t layer_id) = 0;

        /*! \brief  predict labels */
        virtual void Predict( std::vector<float> &preds, const DataBatch& batch ) = 0;
        /*! \brief  predict topk score and index */
        virtual void PredictTopK( std::vector< std::pair<float,uint32_t > > &preds, const DataBatch& batch, uint32_t topk ) = 0;
        virtual size_t GetOutputSize ( void ) = 0; 
    };
};
#endif
