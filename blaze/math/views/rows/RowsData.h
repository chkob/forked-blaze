//=================================================================================================
/*!
//  \file blaze/math/views/rows/RowsData.h
//  \brief Header file for the implementation of the RowsData class template
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

#ifndef _BLAZE_MATH_VIEWS_ROWS_ROWSDATA_H_
#define _BLAZE_MATH_VIEWS_ROWS_ROWSDATA_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/util/Assert.h>
#include <blaze/util/SmallVector.h>
#include <blaze/util/Types.h>
#include <blaze/util/Unused.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Auxiliary class template for the data members of the Rows class.
// \ingroup rows
//
// The auxiliary RowsData class template represents an abstraction of the data members of the
// Rows class template. The necessary set of data members is selected depending on the number
// of compile time row arguments. The basic implementation of RowsData adapts the class template
// to the requirements of multiple compile time row arguments.
*/
template< size_t... CRAs >  // Compile time row arguments
struct RowsData
{
 public:
   //**Type definitions****************************************************************************
   using Indices = std::array<size_t,sizeof...(CRAs)>;  //!< Type of the container for row indices.
   //**********************************************************************************************

   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   template< typename... RRAs >
   explicit inline RowsData( RRAs... args ) noexcept;
   // No explicitly declared copy constructor.
   //@}
   //**********************************************************************************************

   //**Destructor**********************************************************************************
   // No explicitly declared destructor.
   //**********************************************************************************************

   //**Assignment operators************************************************************************
   RowsData& operator=( const RowsData& ) = delete;
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   inline static constexpr const Indices& idces() noexcept;
   inline static constexpr size_t         idx  ( size_t i ) noexcept;
   inline static constexpr size_t         rows () noexcept;
   //@}
   //**********************************************************************************************

 private:
   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   static constexpr Indices indices_{ { CRAs... } };  //!< The indices of the rows in the matrix.
   //@}
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
// Definition and initialization of the static member variables
template< size_t... CRAs >  // Compile time row arguments
constexpr typename RowsData<CRAs...>::Indices RowsData<CRAs...>::indices_;
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief The constructor for RowsData.
//
// \param args The optional row arguments.
*/
template< size_t... CRAs >    // Compile time row arguments
template< typename... RRAs >  // Optional row arguments
inline RowsData<CRAs...>::RowsData( RRAs... args ) noexcept
{
   UNUSED_PARAMETER( args... );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the indices of the specified rows in the underlying matrix.
//
// \return The indices of the specified rows.
*/
template< size_t... CRAs >  // Compile time row arguments
inline constexpr const typename RowsData<CRAs...>::Indices& RowsData<CRAs...>::idces() noexcept
{
   return indices_;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the index of the specified row in the underlying matrix.
//
// \param i Access index for the row.
// \return The index of the specified row.
*/
template< size_t... CRAs >  // Compile time row arguments
inline constexpr size_t RowsData<CRAs...>::idx( size_t i ) noexcept
{
   BLAZE_USER_ASSERT( i < rows(), "Invalid row access index" );
   return indices_[i];
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the number of rows.
//
// \return The number of rows.
*/
template< size_t... CRAs >  // Compile time row arguments
inline constexpr size_t RowsData<CRAs...>::rows() noexcept
{
   return sizeof...( CRAs );
}
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  CLASS TEMPLATE SPECIALIZATION FOR ZERO COMPILE TIME ROW ARGUMENTS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Specialization of the RowsData class template for zero compile time row arguments.
// \ingroup rows
//
// This specialization of RowsData adapts the class template to the requirements of zero compile
// time row arguments.
*/
template<>
struct RowsData<>
{
 public:
   //**Type definitions****************************************************************************
   using Indices = SmallVector<size_t,8UL>;  //!< Type of the container for row indices.
   //**********************************************************************************************

   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   template< typename T, typename... RRAs >
   explicit inline RowsData( const T* indices, size_t n, RRAs... args );

   inline RowsData( const RowsData& ) = default;
   inline RowsData( RowsData&& ) = default;
   //@}
   //**********************************************************************************************

   //**Destructor**********************************************************************************
   // No explicitly declared destructor.
   //**********************************************************************************************

   //**Assignment operators************************************************************************
   RowsData& operator=( const RowsData& ) = delete;
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   inline const Indices& idces() const noexcept;
   inline size_t         idx  ( size_t i ) const noexcept;
   inline size_t         rows () const noexcept;
   //@}
   //**********************************************************************************************

 private:
   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   Indices indices_;  //!< The indices of the rows in the matrix.
   //@}
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief The constructor for RowsData.
//
// \param indices Pointer to the first index of the selected rows.
// \param n The total number of indices.
// \param args The optional row arguments.
*/
template< typename T          // Type of the row indices
        , typename... RRAs >  // Optional row arguments
inline RowsData<>::RowsData( const T* indices, size_t n, RRAs... args )
   : indices_( indices, indices+n )  // The indices of the rows in the matrix
{
   UNUSED_PARAMETER( args... );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the indices of the specified rows in the underlying matrix.
//
// \return The indices of the specified rows.
*/
inline const RowsData<>::Indices& RowsData<>::idces() const noexcept
{
   return indices_;
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the index of the specified row in the underlying matrix.
//
// \param i Access index for the row.
// \return The index of the specified row.
//
// This function only performs an index check in case BLAZE_USER_ASSERT() is active.
*/
inline size_t RowsData<>::idx( size_t i ) const noexcept
{
   BLAZE_USER_ASSERT( i < rows(), "Invalid row access index" );
   return indices_[i];
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns the number of rows.
//
// \return The number of rows.
*/
inline size_t RowsData<>::rows() const noexcept
{
   return indices_.size();
}
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
