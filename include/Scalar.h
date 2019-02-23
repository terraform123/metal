#ifndef DIFF_SCALAR_H
#define DIFF_SCALAR_H


#include "ScalarBase.h"
#include <Eigen/Core>
#include <map>


namespace diff
{

    /**
     * @brief Concrete final type of the ET design architecture involving derivatives computation.
     *
     * Represents a scalar quantity including partial derivatives with respect to arbitrary number
     * of external parameters.
     *
     */
    class Scalar : public ScalarBase< Scalar >
    {

    public:
        /** Alias for type of partial derivative vector. Using Eigen row vector */
        using Partial = Eigen::Matrix< double, 1, -1 >;

        /** Alias for Eigen segment ET to represent part of the derivative vector */
        using PartialSegment = Eigen::VectorBlock< const Partial, -1 >;

        /** Alias for the iterator */
        using IteratorType = Iterator< Scalar >;

        /** Alias for type of representing the range of the derivative vector that holds information
         * w.r.t to a specific parameter */
        using Span = std::pair< int, int >;

        /** Alias for type mapping the parameter space to derivative vector space */
        using ParameterMap = std::map< ParameterPtr, Span >;


        /**
         * @brief Construct a new Scalar object without holding partial deriatives.
         *
         * Default for the value is zero.
         *
         * @param value Value of the scalar object
         */
        explicit Scalar( double value = 0.0 )
            : value_{ value }
            , partial_()
            , parameterMap_()
        {
        }

        /**
         * @brief Construct a new Scalar object and creates a parameter with the specified name.
         *
         * The partial derivative w.r.t. this parameter is initialized to unity.
         *
         * @param value Value of the scalar object
         * @param name Name of the internal parameter
         */
        Scalar( double value, const std::string& name )
            : value_{ value }
            , partial_{ Eigen::Matrix< double, 1, 1 >::Ones() }
            , parameterMap_{ { { std::make_shared< Parameter >( 1, name ), { 0, 1 } } } }
        {
        }

        /**
         * @brief Construct a new Scalar object from an existing expression by forcing the
         * evaluation of the value and partial derivatives.
         *
         * @tparam Expr Type of expression to evaluate
         * @param expr Expression to evaluate
         */
        template< typename Expr >
        Scalar( const ScalarBase< Expr >& expr )
            : value_{ expr.value() }
            , partial_{ expr.partial() }
            , parameterMap_{ expr.parameterMap() }
        {
        }

        /**
         *  @copydoc ScalarBase::value()
         */
        double value() const
        {
            return value_;
        }

        /**
         *  @copydoc ScalarBase::partial()
         */
        const Partial& partial() const
        {
            return partial_;
        }

        /**
         *  @copydoc ScalarBase::dim()
         */
        const ParameterMap& parameterMap() const
        {
            return parameterMap_;
        }

        /**
         *  @copydoc ScalarBase::dim()
         */
        size_t dim() const
        {
            return partial_.size();
        }

        /**
         *  @copydoc ScalarBase::size()
         */
        size_t size() const
        {
            return parameterMap_.size();
        }

        /**
         *  @copydoc ScalarBase::parameters()
         */
        ParameterPtrVector parameters() const
        {
            ParameterPtrVector out;
            for ( const auto& entry : parameterMap_ )
            {
                out.push_back( entry.first );
            }
            return out;
        }

        /**
         *  @copydoc ScalarBase::begin()
         */
        IteratorType begin() const
        {
            return IteratorType{ *this, parameterMap_.begin() };
        }

        /**
         *  @copydoc ScalarBase::end()
         */
        IteratorType end() const
        {
            return IteratorType{ *this, parameterMap_.end() };
        }

    private:
        /** Physical value of the scalar */
        double value_;

        /** Storage for partial derivative vector */
        Partial partial_;

        /** Associative map of parameters to their position and dimensino in the partial vector */
        ParameterMap parameterMap_;
    };

} // diff

#endif // DIFF_SCALAR_H
