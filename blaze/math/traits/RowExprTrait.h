//=================================================================================================
/*!
//  \file blaze/math/traits/RowExprTrait.h
//  \brief Header file for the RowExprTrait class template
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

#ifndef _BLAZE_MATH_TRAITS_ROWEXPRTRAIT_H_
#define _BLAZE_MATH_TRAITS_ROWEXPRTRAIT_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/math/typetraits/IsMatrix.h>
#include <blaze/math/views/Forward.h>
#include <blaze/util/InvalidType.h>
#include <blaze/util/mpl/If.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/RemoveReference.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Evaluation of the expression type type of a row operation.
// \ingroup math_traits
//
// Via this type trait it is possible to evaluate the return type of a row operation. Given the
// dense or sparse matrix type \a MT, the nested type \a Type corresponds to the resulting return
// type. In case the given type is neither a dense nor a sparse matrix type, the resulting data
// type \a Type is set to \a INVALID_TYPE.
*/
template< typename MT       // Type of the matrix operand
        , size_t... CRAs >  // Compile time row arguments
struct RowExprTrait
{
 private:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   struct Failure { using Type = INVALID_TYPE; };
   /*! \endcond */
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   struct CompileTime { using Type = decltype( row<CRAs...>( std::declval<MT>() ) ); };
   /*! \endcond */
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   struct Runtime { using Type = decltype( row( std::declval<MT>(), std::declval<size_t>() ) ); };
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   using Type = typename If_< IsMatrix< RemoveReference_<MT> >
                            , IfTrue_< ( sizeof...( CRAs ) > 0UL )
                                     , CompileTime
                                     , Runtime >
                            , Failure >::Type;
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary alias declaration for the RowExprTrait type trait.
// \ingroup math_traits
//
// The RowExprTrait_ alias declaration provides a convenient shortcut to access the nested
// \a Type of the RowExprTrait class template. For instance, given the matrix type \a MT the
// following two type definitions are identical:

   \code
   using Type1 = typename RowExprTrait<MT>::Type;
   using Type2 = RowExprTrait_<MT>;
   \endcode
*/
template< typename MT       // Type of the matrix operand
        , size_t... CRAs >  // Compile time row arguments
using RowExprTrait_ = typename RowExprTrait<MT,CRAs...>::Type;
//*************************************************************************************************

} // namespace blaze

#endif
