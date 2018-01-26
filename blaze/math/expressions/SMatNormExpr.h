//=================================================================================================
/*!
//  \file blaze/math/expressions/SMatNormExpr.h
//  \brief Header file for the sparse matrix norm expression
//
//  Copyright (C) 2012-2018 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_EXPRESSIONS_SMATNORMEXPR_H_
#define _BLAZE_MATH_EXPRESSIONS_SMATNORMEXPR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/math/Aliases.h>
#include <blaze/math/expressions/SparseMatrix.h>
#include <blaze/math/functors/Cbrt.h>
#include <blaze/math/functors/Noop.h>
#include <blaze/math/functors/Pow2.h>
#include <blaze/math/functors/Pow3.h>
#include <blaze/math/functors/Sqrt.h>
#include <blaze/math/functors/UnaryPow.h>
#include <blaze/math/shims/Evaluate.h>
#include <blaze/math/shims/Invert.h>
#include <blaze/math/shims/IsDefault.h>
#include <blaze/math/shims/IsZero.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/math/typetraits/IsResizable.h>
#include <blaze/math/typetraits/IsRowMajorMatrix.h>
#include <blaze/math/typetraits/UnderlyingBuiltin.h>
#include <blaze/util/Assert.h>
#include <blaze/util/FunctionTrace.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/RemoveReference.h>


namespace blaze {

//=================================================================================================
//
//  GLOBAL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default backend implementation of the norm of a sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The norm of the given matrix.
//
// This function implements the performance optimized norm of a sparse matrix. Due to the
// explicit application of the SFINAE principle, this function can only be selected by the
// compiler in case vectorization cannot be applied.
*/
template< typename MT      // Type of the sparse matrix
        , bool SO          // Storage order
        , typename Power   // Type of the power operation
        , typename Root >  // Type of the root operation
inline decltype(auto) norm_backend( const SparseMatrix<MT,SO>& sm, Power power, Root root )
{
   using CT = CompositeType_<MT>;
   using ET = ElementType_<MT>;
   using RT = decltype( evaluate( root( std::declval<ET>() ) ) );

   using ConstIterator = ConstIterator_< RemoveReference_<CT> >;

   if( (~sm).rows() == 0UL || (~sm).columns() == 0UL ) return RT();

   CT tmp( ~sm );

   const size_t N( IsRowMajorMatrix<MT>::value ? tmp.rows(): tmp.columns() );

   ET norm{};

   for( size_t i=0UL; i<N; ++i )
   {
      const ConstIterator end( tmp.end(i) );
      for( ConstIterator element=tmp.begin(i); element!=end; ++element ) {
         if( IsResizable<ET>::value && isDefault( norm ) )
            norm = power( element->value() );
         else
            norm += power( element->value() );
      }
   }

   return evaluate( root( norm ) );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L2 norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The L2 norm of the given sparse matrix.
//
// This function computes the L2 norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double l2 = norm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) norm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sm, Pow2(), Sqrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the squared L2 norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The squared L2 norm of the given sparse matrix.
//
// This function computes the squared L2 norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double l2 = sqrNorm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) sqrNorm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sm, Pow2(), Noop() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L1 norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The L1 norm of the given sparse matrix.
//
// This function computes the L1 norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double l1 = l1Norm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) l1Norm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sm, Noop(), Noop() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L2 norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The L2 norm of the given sparse matrix.
//
// This function computes the L2 norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double l2 = l2Norm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) l2Norm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sm, Pow2(), Sqrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L3 norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The L3 norm of the given sparse matrix.
//
// This function computes the L3 norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double l3 = l3Norm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) l3Norm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sm, Pow3(), Cbrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the Lp norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \param p The norm parameter (p > 0).
// \return The Lp norm of the given sparse matrix.
//
// This function computes the Lp norm of the given sparse matrix, where the norm is specified by
// the runtime argument \a p:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double lp = lpNorm( A, 2.3 );
   \endcode

// \note The norm parameter \a p is expected to be larger than 0. This precondition is only checked
// by a user assertion.
*/
template< typename MT    // Type of the sparse matrix
        , bool SO        // Storage order
        , typename ST >  //
decltype(auto) lpNorm( const SparseMatrix<MT,SO>& sm, ST p )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_USER_ASSERT( !isZero( p ), "Invalid p for Lp norm detected" );

   using ScalarType = MultTrait_< UnderlyingBuiltin_<MT>, decltype( inv( p ) ) >;
   return norm_backend( ~sm, UnaryPow<ScalarType>( p ), UnaryPow<ScalarType>( inv( p ) ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the maximum norm for the given sparse matrix.
// \ingroup sparse_matrix
//
// \param sm The given sparse matrix for the norm computation.
// \return The maximum norm of the given sparse matrix.
//
// This function computes the maximum norm of the given sparse matrix:

   \code
   blaze::CompressedMatrix<double> A;
   // ... Resizing and initialization
   const double max = maxNorm( A );
   \endcode
*/
template< typename MT  // Type of the sparse matrix
        , bool SO >    // Storage order
decltype(auto) maxNorm( const SparseMatrix<MT,SO>& sm )
{
   BLAZE_FUNCTION_TRACE;

   return max( abs( ~sm ) );
}
//*************************************************************************************************

} // namespace blaze

#endif
