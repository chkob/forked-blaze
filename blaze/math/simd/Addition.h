//=================================================================================================
/*!
//  \file blaze/math/simd/Addition.h
//  \brief Header file for the SIMD addition functionality
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
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

#ifndef _BLAZE_MATH_SIMD_ADDITION_H_
#define _BLAZE_MATH_SIMD_ADDITION_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/Aliases.h>
#include <blaze/math/simd/BasicTypes.h>
#include <blaze/math/traits/AddTrait.h>
#include <blaze/system/Inline.h>
#include <blaze/system/Vectorization.h>


namespace blaze {

//=================================================================================================
//
//  SIMD ADDITION OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Addition of two vectors of 8-bit integral SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2 and AVX2.
*/
template< typename T1    // Type of the left-hand side operand
        , typename T2 >  // Type of the right-hand side operand
BLAZE_ALWAYS_INLINE AddTrait_<T1,T2>
   operator+( const simd_i8_t<T1>& a, const simd_i8_t<T2>& b ) noexcept
#if BLAZE_AVX2_MODE
{
   return _mm256_add_epi8( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi8( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 8-bit integral complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2 and AVX2.
*/
template< typename T >  // Type of both operands
BLAZE_ALWAYS_INLINE T
   operator+( const simd_ci8_t<T>& a, const simd_ci8_t<T>& b ) noexcept
#if BLAZE_AVX2_MODE
{
   return _mm256_add_epi8( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi8( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 16-bit integral SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2 and AVX2.
*/
template< typename T1    // Type of the left-hand side operand
        , typename T2 >  // Type of the right-hand side operand
BLAZE_ALWAYS_INLINE AddTrait_<T1,T2>
   operator+( const simd_i16_t<T1>& a, const simd_i16_t<T2>& b ) noexcept
#if BLAZE_AVX2_MODE
{
   return _mm256_add_epi16( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi16( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 16-bit integral complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2 and AVX2.
*/
template< typename T >  // Type of both operands
BLAZE_ALWAYS_INLINE T
   operator+( const simd_ci16_t<T>& a, const simd_ci16_t<T>& b ) noexcept
#if BLAZE_AVX2_MODE
{
   return _mm256_add_epi16( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi16( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 32-bit integral SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX2, and AVX-512.
*/
template< typename T1    // Type of the left-hand side operand
        , typename T2 >  // Type of the right-hand side operand
BLAZE_ALWAYS_INLINE AddTrait_<T1,T2>
   operator+( const simd_i32_t<T1>& a, const simd_i32_t<T2>& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_epi32( (~a).value, (~b).value );
}
#elif BLAZE_AVX2_MODE
{
   return _mm256_add_epi32( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi32( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 32-bit integral complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX2, and AVX-512.
*/
template< typename T >  // Type of both operands
BLAZE_ALWAYS_INLINE T
   operator+( const simd_ci32_t<T>& a, const simd_ci32_t<T>& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_epi32( (~a).value, (~b).value );
}
#elif BLAZE_AVX2_MODE
{
   return _mm256_add_epi32( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi32( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 64-bit integral SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX2, and AVX-512.
*/
template< typename T1    // Type of the left-hand side operand
        , typename T2 >  // Type of the right-hand side operand
BLAZE_ALWAYS_INLINE AddTrait_<T1,T2>
   operator+( const simd_i64_t<T1>& a, const simd_i64_t<T2>& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_epi64( (~a).value, (~b).value );
}
#elif BLAZE_AVX2_MODE
{
   return _mm256_add_epi64( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi64( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of 64-bit integral complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX2, and AVX-512.
*/
template< typename T >  // Type of both operands
BLAZE_ALWAYS_INLINE T
   operator+( const simd_ci64_t<T>& a, const simd_ci64_t<T>& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_epi64( (~a).value, (~b).value );
}
#elif BLAZE_AVX2_MODE
{
   return _mm256_add_epi64( (~a).value, (~b).value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_epi64( (~a).value, (~b).value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of single precision floating point SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE, AVX, and AVX-512.
*/
BLAZE_ALWAYS_INLINE simd_float_t
   operator+( const simd_float_t& a, const simd_float_t& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_ps( a.value, b.value );
}
#elif BLAZE_AVX_MODE
{
   return _mm256_add_ps( a.value, b.value );
}
#elif BLAZE_SSE_MODE
{
   return _mm_add_ps( a.value, b.value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of single precision complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE, AVX, and AVX-512.
*/
BLAZE_ALWAYS_INLINE simd_cfloat_t
   operator+( const simd_cfloat_t& a, const simd_cfloat_t& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_ps( a.value, b.value );
}
#elif BLAZE_AVX_MODE
{
   return _mm256_add_ps( a.value, b.value );
}
#elif BLAZE_SSE_MODE
{
   return _mm_add_ps( a.value, b.value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of double precision floating point SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX, and AVX-512.
*/
BLAZE_ALWAYS_INLINE simd_double_t
   operator+( const simd_double_t& a, const simd_double_t& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_pd( a.value, b.value );
}
#elif BLAZE_AVX_MODE
{
   return _mm256_add_pd( a.value, b.value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_pd( a.value, b.value );
}
#else
= delete;
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Addition of two vectors of double precision complex SIMD values.
// \ingroup simd
//
// \param a The left-hand side SIMD operand.
// \param b The right-hand side SIMD operand.
// \return The result of the addition.
//
// This operation is only available for SSE2, AVX, and AVX-512.
*/
BLAZE_ALWAYS_INLINE simd_cdouble_t
   operator+( const simd_cdouble_t& a, const simd_cdouble_t& b ) noexcept
#if BLAZE_MIC_MODE
{
   return _mm512_add_pd( a.value, b.value );
}
#elif BLAZE_AVX_MODE
{
   return _mm256_add_pd( a.value, b.value );
}
#elif BLAZE_SSE2_MODE
{
   return _mm_add_pd( a.value, b.value );
}
#else
= delete;
#endif
//*************************************************************************************************




//=================================================================================================
//
//  ADDTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template<> struct AddTrait< simd_int8_t , simd_int8_t  > { using Type = simd_int8_t;  };
template<> struct AddTrait< simd_int8_t , simd_uint8_t > { using Type = simd_uint8_t; };
template<> struct AddTrait< simd_uint8_t, simd_int8_t  > { using Type = simd_uint8_t; };
template<> struct AddTrait< simd_uint8_t, simd_uint8_t > { using Type = simd_uint8_t; };

template<> struct AddTrait< simd_int16_t , simd_int16_t  > { using Type = simd_int16_t;  };
template<> struct AddTrait< simd_int16_t , simd_uint16_t > { using Type = simd_uint16_t; };
template<> struct AddTrait< simd_uint16_t, simd_int16_t  > { using Type = simd_uint16_t; };
template<> struct AddTrait< simd_uint16_t, simd_uint16_t > { using Type = simd_uint16_t; };

template<> struct AddTrait< simd_int32_t , simd_int32_t  > { using Type = simd_int32_t;  };
template<> struct AddTrait< simd_int32_t , simd_uint32_t > { using Type = simd_uint32_t; };
template<> struct AddTrait< simd_uint32_t, simd_int32_t  > { using Type = simd_uint32_t; };
template<> struct AddTrait< simd_uint32_t, simd_uint32_t > { using Type = simd_uint32_t; };

template<> struct AddTrait< simd_int64_t , simd_int64_t  > { using Type = simd_int64_t;  };
template<> struct AddTrait< simd_int64_t , simd_uint64_t > { using Type = simd_uint64_t; };
template<> struct AddTrait< simd_uint64_t, simd_int64_t  > { using Type = simd_uint64_t; };
template<> struct AddTrait< simd_uint64_t, simd_uint64_t > { using Type = simd_uint64_t; };
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
