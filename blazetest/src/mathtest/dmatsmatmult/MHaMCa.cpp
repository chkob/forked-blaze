//=================================================================================================
/*!
//  \file src/mathtest/dmatsmatmult/MHaMCa.cpp
//  \brief Source file for the MHaMCa dense matrix/sparse matrix multiplication math test
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


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/HybridMatrix.h>
#include <blazetest/mathtest/Creator.h>
#include <blazetest/mathtest/dmatsmatmult/OperationTest.h>
#include <blazetest/system/MathTest.h>


//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running 'MHaMCa'..." << std::endl;

   using blazetest::mathtest::TypeA;

   try
   {
      // Matrix type definitions
      typedef blaze::HybridMatrix<TypeA,128UL,67UL>  MHa;
      typedef blaze::CompressedMatrix<TypeA>         MCa;

      // Creator type definitions
      typedef blazetest::Creator<MHa>  CMHa;
      typedef blazetest::Creator<MCa>  CMCa;

      // Running tests with small matrices
      for( size_t i=0UL; i<=6UL; ++i ) {
         for( size_t j=0UL; j<=6UL; ++j ) {
            for( size_t k=0UL; k<=6UL; ++k ) {
               for( size_t l=0UL; l<=i*k; ++l ) {
                  RUN_DMATSMATMULT_OPERATION_TEST( CMHa( j, i ), CMCa( i, k, l ) );
               }
            }
         }
      }

      // Running tests with large matrices
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  31UL,  67UL ), CMCa(  67UL,  31UL,  7UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  31UL,  67UL ), CMCa(  67UL, 127UL, 13UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  67UL,  67UL ), CMCa(  67UL,  67UL,  7UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa( 127UL,  67UL ), CMCa(  67UL,  31UL,  7UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa( 127UL,  67UL ), CMCa(  67UL, 127UL, 13UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  32UL,  64UL ), CMCa(  64UL,  32UL,  8UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  32UL,  64UL ), CMCa(  64UL, 128UL, 16UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa(  64UL,  64UL ), CMCa(  64UL,  64UL,  8UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa( 128UL,  64UL ), CMCa(  64UL,  32UL,  8UL ) );
      RUN_DMATSMATMULT_OPERATION_TEST( CMHa( 128UL,  64UL ), CMCa(  64UL, 128UL, 16UL ) );
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during dense matrix/sparse matrix multiplication:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
