//=================================================================================================
/*!
//  \file blaze/math/expressions/SMatTSMatMultExpr.h
//  \brief Header file for the sparse matrix/transpose sparse matrix multiplication expression
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

#ifndef _BLAZE_MATH_EXPRESSIONS_SMATTSMATMULTEXPR_H_
#define _BLAZE_MATH_EXPRESSIONS_SMATTSMATMULTEXPR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/Aliases.h>
#include <blaze/math/constraints/ColumnMajorMatrix.h>
#include <blaze/math/constraints/MatMatMultExpr.h>
#include <blaze/math/constraints/RequiresEvaluation.h>
#include <blaze/math/constraints/RowMajorMatrix.h>
#include <blaze/math/constraints/SparseMatrix.h>
#include <blaze/math/constraints/Symmetric.h>
#include <blaze/math/Exception.h>
#include <blaze/math/expressions/Computation.h>
#include <blaze/math/expressions/Forward.h>
#include <blaze/math/expressions/SparseMatrix.h>
#include <blaze/math/expressions/MatMatMultExpr.h>
#include <blaze/math/shims/Serial.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/math/typetraits/IsColumnMajorMatrix.h>
#include <blaze/math/typetraits/IsComputation.h>
#include <blaze/math/typetraits/IsExpression.h>
#include <blaze/math/typetraits/IsLower.h>
#include <blaze/math/typetraits/IsRowMajorMatrix.h>
#include <blaze/math/typetraits/IsStrictlyLower.h>
#include <blaze/math/typetraits/IsStrictlyUpper.h>
#include <blaze/math/typetraits/IsSymmetric.h>
#include <blaze/math/typetraits/IsUniLower.h>
#include <blaze/math/typetraits/IsUniUpper.h>
#include <blaze/math/typetraits/IsUpper.h>
#include <blaze/math/typetraits/RequiresEvaluation.h>
#include <blaze/math/typetraits/Size.h>
#include <blaze/math/views/Check.h>
#include <blaze/system/Thresholds.h>
#include <blaze/util/algorithms/Min.h>
#include <blaze/util/Assert.h>
#include <blaze/util/DisableIf.h>
#include <blaze/util/EnableIf.h>
#include <blaze/util/FunctionTrace.h>
#include <blaze/util/mpl/And.h>
#include <blaze/util/mpl/If.h>
#include <blaze/util/mpl/Or.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/RemoveReference.h>
#include <blaze/util/Unused.h>


namespace blaze {

//=================================================================================================
//
//  CLASS SMATTSMATMULTEXPR
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Expression object for sparse matrix-transpose sparse matrix multiplications.
// \ingroup sparse_matrix_expression
//
// The SMatTSMatMultExpr class represents the compile time expression for multiplications between
// a row-major and a column-major sparse matrix.
*/
template< typename MT1    // Type of the left-hand side sparse matrix
        , typename MT2 >  // Type of the right-hand side sparse matrix
class SMatTSMatMultExpr
   : public MatMatMultExpr< SparseMatrix< SMatTSMatMultExpr<MT1,MT2>, false > >
   , private Computation
{
 private:
   //**Type definitions****************************************************************************
   using RT1 = ResultType_<MT1>;     //!< Result type of the left-hand side sparse matrix expression.
   using RT2 = ResultType_<MT2>;     //!< Result type of the right-hand side sparse matrix expression.
   using CT1 = CompositeType_<MT1>;  //!< Composite type of the left-hand side sparse matrix expression.
   using CT2 = CompositeType_<MT2>;  //!< Composite type of the right-hand side sparse matrix expression.
   //**********************************************************************************************

   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   //! Helper structure for the explicit application of the SFINAE principle.
   /*! The CanExploitSymmetry struct is a helper struct for the selection of the optimal
       evaluation strategy. In case the target matrix is row-major and the right-hand side
       matrix operand of type \a T3 is symmetric or in case the target matrix is column-major
       and the left-hand side matrix operands of type \a T2 is symmetric, \a value is set to
       1 and an optimized evaluation strategy is selected. Otherwise \a value is set to 0 and
       the default strategy is chosen. */
   template< typename T1, typename T2, typename T3 >
   struct CanExploitSymmetry {
      enum : bool { value = ( IsRowMajorMatrix<T1>::value    && IsSymmetric<T3>::value ) ||
                            ( IsColumnMajorMatrix<T1>::value && IsSymmetric<T2>::value ) };
   };
   /*! \endcond */
   //**********************************************************************************************

 public:
   //**Type definitions****************************************************************************
   using This          = SMatTSMatMultExpr<MT1,MT2>;  //!< Type of this SMatTSMatMultExpr instance.
   using ResultType    = MultTrait_<RT1,RT2>;         //!< Result type for expression template evaluations.
   using OppositeType  = OppositeType_<ResultType>;   //!< Result type with opposite storage order for expression template evaluations.
   using TransposeType = TransposeType_<ResultType>;  //!< Transpose type for expression template evaluations.
   using ElementType   = ElementType_<ResultType>;    //!< Resulting element type.
   using ReturnType    = const ElementType;           //!< Return type for expression template evaluations.
   using CompositeType = const ResultType;            //!< Data type for composite expression templates.

   //! Composite type of the left-hand side sparse matrix expression.
   using LeftOperand = If_< IsExpression<MT1>, const MT1, const MT1& >;

   //! Composite type of the right-hand side sparse matrix expression.
   using RightOperand = If_< IsExpression<MT2>, const MT2, const MT2& >;
   //**********************************************************************************************

   //**Compilation flags***************************************************************************
   //! Compilation switch for the expression template assignment strategy.
   enum : bool { smpAssignable = false };
   //**********************************************************************************************

   //**Constructor*********************************************************************************
   /*!\brief Constructor for the SMatTSMatMultExpr class.
   //
   // \param lhs The left-hand side sparse matrix operand of the multiplication expression.
   // \param rhs The right-hand side sparse matrix operand of the multiplication expression.
   */
   explicit inline SMatTSMatMultExpr( const MT1& lhs, const MT2& rhs ) noexcept
      : lhs_( lhs )  // Left-hand side sparse matrix of the multiplication expression
      , rhs_( rhs )  // Right-hand side sparse matrix of the multiplication expression
   {
      BLAZE_INTERNAL_ASSERT( lhs.columns() == rhs.rows(), "Invalid matrix sizes" );
   }
   //**********************************************************************************************

   //**Access operator*****************************************************************************
   /*!\brief 2D-access to the matrix elements.
   //
   // \param i Access index for the row. The index has to be in the range \f$[0..M-1]\f$.
   // \param j Access index for the column. The index has to be in the range \f$[0..N-1]\f$.
   // \return The resulting value.
   */
   inline ReturnType operator()( size_t i, size_t j ) const {
      BLAZE_INTERNAL_ASSERT( i < lhs_.rows()   , "Invalid row access index"    );
      BLAZE_INTERNAL_ASSERT( j < rhs_.columns(), "Invalid column access index" );

      return row( lhs_, i, unchecked ) * column( rhs_, j, unchecked );
   }
   //**********************************************************************************************

   //**At function*********************************************************************************
   /*!\brief Checked access to the matrix elements.
   //
   // \param i Access index for the row. The index has to be in the range \f$[0..M-1]\f$.
   // \param j Access index for the column. The index has to be in the range \f$[0..N-1]\f$.
   // \return The resulting value.
   // \exception std::out_of_range Invalid matrix access index.
   */
   inline ReturnType at( size_t i, size_t j ) const {
      if( i >= lhs_.rows() ) {
         BLAZE_THROW_OUT_OF_RANGE( "Invalid row access index" );
      }
      if( j >= rhs_.columns() ) {
         BLAZE_THROW_OUT_OF_RANGE( "Invalid column access index" );
      }
      return (*this)(i,j);
   }
   //**********************************************************************************************

   //**Rows function*******************************************************************************
   /*!\brief Returns the current number of rows of the matrix.
   //
   // \return The number of rows of the matrix.
   */
   inline size_t rows() const noexcept {
      return lhs_.rows();
   }
   //**********************************************************************************************

   //**Columns function****************************************************************************
   /*!\brief Returns the current number of columns of the matrix.
   //
   // \return The number of columns of the matrix.
   */
   inline size_t columns() const noexcept {
      return rhs_.columns();
   }
   //**********************************************************************************************

   //**NonZeros function***************************************************************************
   /*!\brief Returns the number of non-zero elements in the sparse matrix.
   //
   // \return The number of non-zero elements in the sparse matrix.
   */
   inline constexpr size_t nonZeros() const noexcept {
      return 0UL;
   }
   //**********************************************************************************************

   //**NonZeros function***************************************************************************
   /*!\brief Returns the number of non-zero elements in the specified row.
   //
   // \param i The index of the row.
   // \return The number of non-zero elements of row \a i.
   */
   inline size_t nonZeros( size_t i ) const noexcept {
      UNUSED_PARAMETER( i );
      return 0UL;
   }
   //**********************************************************************************************

   //**Left operand access*************************************************************************
   /*!\brief Returns the left-hand side sparse matrix operand.
   //
   // \return The left-hand side sparse matrix operand.
   */
   inline LeftOperand leftOperand() const noexcept {
      return lhs_;
   }
   //**********************************************************************************************

   //**Right operand access************************************************************************
   /*!\brief Returns the right-hand side transpose sparse matrix operand.
   //
   // \return The right-hand side transpose sparse matrix operand.
   */
   inline RightOperand rightOperand() const noexcept {
      return rhs_;
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression can alias with the given address \a alias.
   //
   // \param alias The alias to be checked.
   // \return \a true in case the expression can alias, \a false otherwise.
   */
   template< typename T >
   inline bool canAlias( const T* alias ) const noexcept {
      return ( lhs_.isAliased( alias ) || rhs_.isAliased( alias ) );
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression is aliased with the given address \a alias.
   //
   // \param alias The alias to be checked.
   // \return \a true in case an alias effect is detected, \a false otherwise.
   */
   template< typename T >
   inline bool isAliased( const T* alias ) const noexcept {
      return ( lhs_.isAliased( alias ) || rhs_.isAliased( alias ) );
   }
   //**********************************************************************************************

   //**********************************************************************************************
   /*!\brief Returns whether the expression can be used in SMP assignments.
   //
   // \return \a true in case the expression can be used in SMP assignments, \a false if not.
   */
   inline bool canSMPAssign() const noexcept {
      return ( rows() * columns() >= SMP_SMATTSMATMULT_THRESHOLD );
   }
   //**********************************************************************************************

 private:
   //**Member variables****************************************************************************
   LeftOperand  lhs_;  //!< Left-hand side sparse matrix of the multiplication expression.
   RightOperand rhs_;  //!< Right-hand side sparse matrix of the multiplication expression.
   //**********************************************************************************************

   //**Assignment to row-major matrices************************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Assignment of a sparse matrix-transpose sparse matrix multiplication to a row-major
   //        matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the performance optimized assignment of a sparse matrix-transpose
   // sparse matrix multiplication expression to a row-major matrix.
   */
   template< typename MT >  // Type of the target matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      assign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( serial( rhs.rhs_ ) );
      assign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring assignment to row-major matrices**********************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring assignment of a sparse matrix-transpose sparse matrix multiplication to
   //        a row-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the symmetry-based restructuring assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a row-major matrix. Due to the explicit
   // application of the SFINAE principle this function can only be selected by the compiler in
   // case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      assign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      assign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Assignment to column-major matrices*********************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Assignment of a sparse matrix-transpose sparse matrix multiplication to a
   //        column-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the performance optimized assignment of a sparse matrix-transpose
   // sparse matrix multiplication expression to a column-major matrix.
   */
   template< typename MT >  // Type of the target matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      assign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( serial( rhs.lhs_ ) );
      assign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring assignment to column-major matrices*******************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring assignment of a sparse matrix-transpose sparse matrix multiplication to
   //        a column-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the symmetry-based restructuring assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a column-major matrix. Due to the
   // explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      assign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      assign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Addition assignment to row-major dense matrices*********************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Addition assignment of a sparse matrix-transpose sparse matrix multiplication to a
   //        row-major dense matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the performance optimized addition assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a row-major dense matrix.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      addAssign( DenseMatrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( serial( rhs.rhs_ ) );
      addAssign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring addition assignment to row-major matrices*************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring addition assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a row-major matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the symmetry-based restructuring addition assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a row-major matrix. Due to the
   // explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      addAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      addAssign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Addition assignment to column-major dense matrices******************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Addition assignment of a sparse matrix-transpose sparse matrix multiplication to a
   //        column-major dense matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the performance optimized addition assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a column-major dense matrix.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      addAssign( DenseMatrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( serial( rhs.lhs_ ) );
      addAssign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring addition assignment to column-major matrices**********************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring addition assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a column-major matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the symmetry-based restructuring addition assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a column-major matrix. Due to
   // the explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      addAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      addAssign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Addition assignment to sparse matrices******************************************************
   // No special implementation for the addition assignment to sparse matrices.
   //**********************************************************************************************

   //**Subtraction assignment to row-major dense matrices******************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Subtraction assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major dense matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the performance optimized subtraction assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a row-major dense matrix.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      subAssign( DenseMatrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( serial( rhs.rhs_ ) );
      subAssign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring subtraction assignment to row-major matrices**********************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring subtraction assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a row-major matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the symmetry-based restructuring subtraction assignment of a
   // sparse matrix-transpose sparse matrix multiplication expression to a row-major matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      subAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      subAssign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Subtraction assignment to column-major dense matrices***************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Subtraction assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a column-major dense matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the performance optimized subtraction assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a column-major dense matrix.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      subAssign( DenseMatrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( serial( rhs.lhs_ ) );
      subAssign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring subtraction assignment to column-major matrices*******************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring subtraction assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a column-major matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the symmetry-based restructuring subtraction assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a column-major matrix. Due to
   // the explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      subAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      subAssign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Subtraction assignment to sparse matrices***************************************************
   // No special implementation for the subtraction assignment to sparse matrices.
   //**********************************************************************************************

   //**Schur product assignment to row-major dense matrices****************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Schur product assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major dense matrix (\f$ C\circ=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression for the Schur product.
   // \return void
   //
   // This function implements the performance optimized Schur product assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a row-major dense matrix.
   */
   template< typename MT  // Type of the target dense matrix
           , bool SO >    // Storage order of the target dense matrix
   friend inline void schurAssign( DenseMatrix<MT,SO>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( ResultType );
      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( ResultType );
      BLAZE_CONSTRAINT_MUST_NOT_REQUIRE_EVALUATION( ResultType );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const ResultType tmp( serial( rhs ) );
      schurAssign( ~lhs, tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Schur product assignment to sparse matrices*************************************************
   // No special implementation for the Schur product assignment to sparse matrices.
   //**********************************************************************************************

   //**Multiplication assignment to dense matrices*************************************************
   // No special implementation for the multiplication assignment to dense matrices.
   //**********************************************************************************************

   //**Multiplication assignment to sparse matrices************************************************
   // No special implementation for the multiplication assignment to sparse matrices.
   //**********************************************************************************************

   //**SMP assignment to row-major matrices********************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP assignment of a sparse matrix-transpose sparse matrix multiplication to a
   //        row-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the performance optimized SMP assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a row-major matrix. Due to the
   // explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( rhs.rhs_ );
      smpAssign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP assignment to row-major matrices******************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a row-major matrix. Due to the explicit
   // application of the SFINAE principle this function can only be selected by the compiler in
   // case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpAssign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP assignment to column-major matrices*****************************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP assignment of a sparse matrix-transpose sparse matrix multiplication to a
   //        column-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the performance optimized SMP assignment of a sparse matrix-
   // transpose sparse matrix multiplication expression to a column-major matrix. Due to the
   // explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( rhs.lhs_ );
      smpAssign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP assignment to column-major matrices***************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a column-major matrix (\f$ C=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be assigned.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a column-major matrix. Due to
   // the explicit application of the SFINAE principle this function can only be selected by the
   // compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpAssign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP addition assignment to row-major dense matrices*****************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP addition assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major dense matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the performance optimized SMP addition assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a row-major dense matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAddAssign( DenseMatrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( rhs.rhs_ );
      smpAddAssign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP addition assignment to column-major dense matrices**************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP addition assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a column-major dense matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the performance optimized SMP addition assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a column-major dense matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAddAssign( DenseMatrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( rhs.lhs_ );
      smpAddAssign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP addition assignment to row-major matrices*********************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP addition assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a row-major matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP addition assignment of a
   // sparse matrix-transpose sparse matrix multiplication expression to a row-major matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAddAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpAddAssign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP addition assignment to column-major matrices******************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP addition assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a column-major matrix (\f$ C+=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be added.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP addition assignment of a
   // sparse matrix-transpose sparse matrix multiplication expression to a column-major matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpAddAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpAddAssign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP addition assignment to sparse matrices**************************************************
   // No special implementation for the SMP addition assignment to sparse matrices.
   //**********************************************************************************************

   //**SMP subtraction assignment to row-major dense matrices**************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP subtraction assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major dense matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the performance optimized SMP subtraction assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a row-major dense matrix. Due
   // to the explicit application of the SFINAE principle this function can only be selected by
   // the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpSubAssign( DenseMatrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( OppositeType_<MT2> );

      const OppositeType_<MT2> tmp( rhs.rhs_ );
      smpSubAssign( ~lhs, rhs.lhs_ * tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP subtraction assignment to column-major dense matrices***********************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP subtraction assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a column-major dense matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the performance optimized SMP subtraction assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a column-major dense matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target dense matrix
   friend inline DisableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpSubAssign( DenseMatrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( OppositeType_<MT1> );

      const OppositeType_<MT1> tmp( rhs.lhs_ );
      smpSubAssign( ~lhs, tmp * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP subtraction assignment to row-major matrices******************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP subtraction assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a row-major matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP subtraction assignment of a
   // sparse matrix-transpose sparse matrix multiplication expression to a row-major matrix. Due
   // to the explicit application of the SFINAE principle this function can only be selected by
   // the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpSubAssign( Matrix<MT,false>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpSubAssign( ~lhs, rhs.lhs_ * trans( rhs.rhs_ ) );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**Restructuring SMP subtraction assignment to column-major matrices***************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief Restructuring SMP subtraction assignment of a sparse matrix-transpose sparse matrix
   //        multiplication to a column-major matrix (\f$ C-=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side matrix.
   // \param rhs The right-hand side multiplication expression to be subtracted.
   // \return void
   //
   // This function implements the symmetry-based restructuring SMP subtraction assignment of a
   // sparse matrix-transpose sparse matrix multiplication expression to a column-major matrix.
   // Due to the explicit application of the SFINAE principle this function can only be selected
   // by the compiler in case the symmetry of either of the two matrix operands can be exploited.
   */
   template< typename MT >  // Type of the target matrix
   friend inline EnableIf_< CanExploitSymmetry<MT,MT1,MT2> >
      smpSubAssign( Matrix<MT,true>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_NOT_BE_SYMMETRIC_MATRIX_TYPE( MT );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      smpSubAssign( ~lhs, trans( rhs.lhs_ ) * rhs.rhs_ );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP subtraction assignment to sparse matrices***********************************************
   // No special implementation for the SMP subtraction assignment to sparse matrices.
   //**********************************************************************************************

   //**SMP Schur product assignment to row-major dense matrices************************************
   /*! \cond BLAZE_INTERNAL */
   /*!\brief SMP Schur product assignment of a sparse matrix-transpose sparse matrix multiplication
   //        to a row-major dense matrix (\f$ C\circ=A*B \f$).
   // \ingroup sparse_matrix
   //
   // \param lhs The target left-hand side dense matrix.
   // \param rhs The right-hand side multiplication expression for the Schur product.
   // \return void
   //
   // This function implements the performance optimized SMP Schur product assignment of a sparse
   // matrix-transpose sparse matrix multiplication expression to a row-major dense matrix.
   */
   template< typename MT  // Type of the target dense matrix
           , bool SO >    // Storage order of the target dense matrix
   friend inline void smpSchurAssign( DenseMatrix<MT,SO>& lhs, const SMatTSMatMultExpr& rhs )
   {
      BLAZE_FUNCTION_TRACE;

      BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( ResultType );
      BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( ResultType );
      BLAZE_CONSTRAINT_MUST_NOT_REQUIRE_EVALUATION( ResultType );

      BLAZE_INTERNAL_ASSERT( (~lhs).rows()    == rhs.rows()   , "Invalid number of rows"    );
      BLAZE_INTERNAL_ASSERT( (~lhs).columns() == rhs.columns(), "Invalid number of columns" );

      const ResultType tmp( rhs );
      smpSchurAssign( ~lhs, tmp );
   }
   /*! \endcond */
   //**********************************************************************************************

   //**SMP Schur product assignment to sparse matrices*********************************************
   // No special implementation for the SMP Schur product assignment to sparse matrices.
   //**********************************************************************************************

   //**SMP multiplication assignment to dense matrices*********************************************
   // No special implementation for the SMP multiplication assignment to dense matrices.
   //**********************************************************************************************

   //**SMP multiplication assignment to sparse matrices********************************************
   // No special implementation for the SMP multiplication assignment to sparse matrices.
   //**********************************************************************************************

   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( MT1 );
   BLAZE_CONSTRAINT_MUST_BE_ROW_MAJOR_MATRIX_TYPE( MT1 );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( MT2 );
   BLAZE_CONSTRAINT_MUST_BE_COLUMN_MAJOR_MATRIX_TYPE( MT2 );
   BLAZE_CONSTRAINT_MUST_FORM_VALID_MATMATMULTEXPR( MT1, MT2 );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL BINARY ARITHMETIC OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Multiplication operator for the multiplication of a row-major sparse matrix and a
//        column-major sparse matrix (\f$ A=B*C \f$).
// \ingroup sparse_matrix
//
// \param lhs The left-hand side sparse matrix for the matrix multiplication.
// \param rhs The right-hand side sparse matrix for the matrix multiplication.
// \return The product of the two matrices.
// \exception std::invalid_argument Matrix sizes do not match.
//
// This operator represents the multiplication of a row-major sparse matrix and a column-major
// sparse matrix:

   \code
   using blaze::rowMajor;
   using blaze::columnMajor;

   blaze::CompressedMatrix<double,rowMajor> A, C;
   blaze::CompressedMatrix<double,columnMajor> B;
   // ... Resizing and initialization
   C = A * B;
   \endcode

// The operator returns an expression representing a sparse matrix of the higher-order element
// type of the two involved matrix element types \a MT1::ElementType and \a MT2::ElementType.
// Both matrix types \a MT1 and \a MT2 as well as the two element types \a MT1::ElementType
// and \a MT2::ElementType have to be supported by the MultTrait class template.\n
// In case the current number of rows and columns of the two given matrices don't match, a
// \a std::invalid_argument is thrown.
*/
template< typename MT1    // Type of the left-hand side sparse matrix
        , typename MT2 >  // Type of the right-hand side sparse matrix
inline decltype(auto)
   operator*( const SparseMatrix<MT1,false>& lhs, const SparseMatrix<MT2,true>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   if( (~lhs).columns() != (~rhs).rows() ) {
      BLAZE_THROW_INVALID_ARGUMENT( "Matrix sizes do not match" );
   }

   using ReturnType = const SMatTSMatMultExpr<MT1,MT2>;
   return ReturnType( ~lhs, ~rhs );
}
//*************************************************************************************************




//=================================================================================================
//
//  SIZE SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct Size< SMatTSMatMultExpr<MT1,MT2>, 0UL >
   : public Size<MT1,0UL>
{};

template< typename MT1, typename MT2 >
struct Size< SMatTSMatMultExpr<MT1,MT2>, 1UL >
   : public Size<MT2,1UL>
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISLOWER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsLower< SMatTSMatMultExpr<MT1,MT2> >
   : public And< IsLower<MT1>, IsLower<MT2> >
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISUNILOWER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsUniLower< SMatTSMatMultExpr<MT1,MT2> >
   : public And< IsUniLower<MT1>, IsUniLower<MT2> >
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISSTRICTLYLOWER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsStrictlyLower< SMatTSMatMultExpr<MT1,MT2> >
   : public Or< And< IsStrictlyLower<MT1>, IsLower<MT2> >
              , And< IsStrictlyLower<MT2>, IsLower<MT1> > >
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISUPPER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsUpper< SMatTSMatMultExpr<MT1,MT2> >
   : public And< IsUpper<MT1>, IsUpper<MT2> >
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISUNIUPPER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsUniUpper< SMatTSMatMultExpr<MT1,MT2> >
   : public And< IsUniUpper<MT1>, IsUniUpper<MT2> >
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISSTRICTLYUPPER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, typename MT2 >
struct IsStrictlyUpper< SMatTSMatMultExpr<MT1,MT2> >
   : public Or< And< IsStrictlyUpper<MT1>, IsUpper<MT2> >
              , And< IsStrictlyUpper<MT2>, IsUpper<MT1> > >
{};
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
