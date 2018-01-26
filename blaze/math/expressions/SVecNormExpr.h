//=================================================================================================
/*!
//  \file blaze/math/expressions/SVecNormExpr.h
//  \brief Header file for the sparse vector norm expression
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

#ifndef _BLAZE_MATH_EXPRESSIONS_SVECNORMEXPR_H_
#define _BLAZE_MATH_EXPRESSIONS_SVECNORMEXPR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/math/Aliases.h>
#include <blaze/math/expressions/SparseVector.h>
#include <blaze/math/functors/Cbrt.h>
#include <blaze/math/functors/Noop.h>
#include <blaze/math/functors/Pow2.h>
#include <blaze/math/functors/Pow3.h>
#include <blaze/math/functors/Sqrt.h>
#include <blaze/math/functors/UnaryPow.h>
#include <blaze/math/shims/Evaluate.h>
#include <blaze/math/shims/Invert.h>
#include <blaze/math/shims/IsZero.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/math/typetraits/UnderlyingBuiltin.h>
#include <blaze/util/Assert.h>
#include <blaze/util/FunctionTrace.h>
#include <blaze/util/typetraits/RemoveReference.h>


namespace blaze {

//=================================================================================================
//
//  GLOBAL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Computes a custom norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \param power The functor for the power operation.
// \param root The functor for the root operation.
// \return The norm of the given sparse vector.
//
// This function computes a custom norm of the given sparse vector by means of the given functors.
// The following example demonstrates the computation of the L2 norm by means of the blaze::Pow2
// and blaze::Sqrt functors:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l2 = norm( a, blaze::Pow2(), blaze::Sqrt() );
   \endcode
*/
template< typename VT      // Type of the sparse vector
        , bool TF          // Transpose flag
        , typename Power   // Type of the power operation
        , typename Root >  // Type of the root operation
decltype(auto) norm_backend( const SparseVector<VT,TF>& sv, Power power, Root root )
{
   using CT = CompositeType_<VT>;
   using ET = ElementType_<VT>;
   using RT = decltype( evaluate( root( std::declval<ET>() ) ) );
   using Iterator = ConstIterator_< RemoveReference_<CT> >;

   if( (~sv).size() == 0UL ) return RT();

   CT tmp( ~sv );

   const Iterator end( tmp.end() );
   Iterator element( tmp.begin() );

   if( element == end ) return RT();

   ET norm( power( element->value() ) );
   ++element;

   for( ; element!=end; ++element ) {
      norm += power( element->value() );
   }

   return evaluate( root( norm ) );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L2 norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The L2 norm of the given sparse vector.
//
// This function computes the L2 norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l2 = norm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) norm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sv, Pow2(), Sqrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the squared L2 norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The squared L2 norm of the given sparse vector.
//
// This function computes the squared L2 norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l2 = sqrNorm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) sqrNorm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sv, Pow2(), Noop() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L1 norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The L1 norm of the given sparse vector.
//
// This function computes the L1 norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l1 = l1Norm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) l1Norm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sv, Noop(), Noop() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L2 norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The L2 norm of the given sparse vector.
//
// This function computes the L2 norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l2 = l2Norm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) l2Norm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sv, Pow2(), Sqrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the L3 norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The L3 norm of the given sparse vector.
//
// This function computes the L3 norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double l3 = l3Norm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) l3Norm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return norm_backend( ~sv, Pow3(), Cbrt() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the Lp norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \param p The norm parameter (p > 0).
// \return The Lp norm of the given sparse vector.
//
// This function computes the Lp norm of the given sparse vector, where the norm is specified by
// the runtime argument \a p:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double lp = lpNorm( a, 2.3 );
   \endcode

// \note The norm parameter \a p is expected to be larger than 0. This precondition is only checked
// by a user assertion.
*/
template< typename VT    // Type of the sparse vector
        , bool TF        // Transpose flag
        , typename ST >  //
decltype(auto) lpNorm( const SparseVector<VT,TF>& sv, ST p )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_USER_ASSERT( !isZero( p ), "Invalid p for Lp norm detected" );

   using ScalarType = MultTrait_< UnderlyingBuiltin_<VT>, decltype( inv( p ) ) >;
   return norm_backend( ~sv, UnaryPow<ScalarType>( p ), UnaryPow<ScalarType>( inv( p ) ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Computes the maximum norm for the given sparse vector.
// \ingroup sparse_vector
//
// \param sv The given sparse vector for the norm computation.
// \return The maximum norm of the given sparse vector.
//
// This function computes the maximum norm of the given sparse vector:

   \code
   blaze::CompressedVector<double> a;
   // ... Resizing and initialization
   const double max = maxNorm( a );
   \endcode
*/
template< typename VT  // Type of the sparse vector
        , bool TF >    // Transpose flag
decltype(auto) maxNorm( const SparseVector<VT,TF>& sv )
{
   BLAZE_FUNCTION_TRACE;

   return max( abs( ~sv ) );
}
//*************************************************************************************************

} // namespace blaze

#endif
