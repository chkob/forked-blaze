//=================================================================================================
/*!
//  \file src/mathtest/smatsmatmult/DCbHCb.cpp
//  \brief Source file for the DCbHCb sparse matrix/sparse matrix multiplication math test
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
#include <blaze/math/DiagonalMatrix.h>
#include <blaze/math/HermitianMatrix.h>
#include <blazetest/mathtest/Creator.h>
#include <blazetest/mathtest/smatsmatmult/OperationTest.h>
#include <blazetest/system/MathTest.h>


//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running 'DCbHCb'..." << std::endl;

   using blazetest::mathtest::NumericB;

   try
   {
      // Matrix type definitions
      typedef blaze::DiagonalMatrix< blaze::CompressedMatrix<NumericB> >   DCb;
      typedef blaze::HermitianMatrix< blaze::CompressedMatrix<NumericB> >  HCb;

      // Creator type definitions
      typedef blazetest::Creator<DCb>  CDCb;
      typedef blazetest::Creator<HCb>  CHCb;

      // Running tests with small matrices
      for( size_t i=0UL; i<=6UL; ++i ) {
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,   0UL ), CHCb( i,     0UL ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,   0UL ), CHCb( i, 0.3*i*i ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,   0UL ), CHCb( i,     i*i ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i, 0.5*i ), CHCb( i,     0UL ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i, 0.5*i ), CHCb( i, 0.3*i*i ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i, 0.5*i ), CHCb( i,     i*i ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,     i ), CHCb( i,     0UL ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,     i ), CHCb( i, 0.3*i*i ) );
         RUN_SMATSMATMULT_OPERATION_TEST( CDCb( i,     i ), CHCb( i,     i*i ) );
      }

      // Running tests with large matrices
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 15UL,  7UL ), CHCb( 15UL,  7UL ) );
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 37UL,  7UL ), CHCb( 37UL,  7UL ) );
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 63UL, 13UL ), CHCb( 63UL, 13UL ) );
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 16UL,  8UL ), CHCb( 16UL,  8UL ) );
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 32UL,  8UL ), CHCb( 32UL,  8UL ) );
      RUN_SMATSMATMULT_OPERATION_TEST( CDCb( 64UL, 16UL ), CHCb( 64UL, 16UL ) );
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during sparse matrix/sparse matrix multiplication:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
