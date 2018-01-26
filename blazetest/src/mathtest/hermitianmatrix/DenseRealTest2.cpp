//=================================================================================================
/*!
//  \file src/mathtest/hermitianmatrix/DenseRealTest2.cpp
//  \brief Source file for the HermitianMatrix dense real test (part 2)
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
#include <memory>
#include <blaze/math/Column.h>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/Row.h>
#include <blaze/math/Submatrix.h>
#include <blazetest/mathtest/hermitianmatrix/DenseRealTest.h>


namespace blazetest {

namespace mathtest {

namespace hermitianmatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the HermitianMatrix dense test.
//
// \exception std::runtime_error Operation error detected.
*/
DenseRealTest::DenseRealTest()
{
   testMultAssign();
   testScaling();
   testFunctionCall();
   testIterator();
   testNonZeros();
   testReset();
   testClear();
   testResize();
   testExtend();
   testReserve();
   testShrinkToFit();
   testSwap();
   testTranspose();
   testCTranspose();
   testIsDefault();
   testSubmatrix();
   testRow();
   testColumn();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the HermitianMatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testMultAssign()
{
   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major dense matrix multiplication assignment (symmetric)
   {
      test_ = "Row-major/row-major HermitianMatrix dense matrix multiplication assignment (symmetric)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (symmetric)
   {
      test_ = "Row-major/column-major HermitianMatrix dense matrix multiplication assignment (symmetric)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix multiplication assignment (non-symmetric)
   {
      test_ = "Row-major/row-major HermitianMatrix dense matrix multiplication assignment (non-symmetric)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix multiplication assignment (non-symmetric)
   {
      test_ = "Row-major/column-major HermitianMatrix dense matrix multiplication assignment (non-symmetric)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Row-major/row-major HermitianMatrix dense matrix multiplication assignment (HermitianMatrix)";

      HT herm1( 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      HT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Row-major/column-major HermitianMatrix dense matrix multiplication assignment (HermitianMatrix)";

      OHT herm1( 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      HT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix multiplication assignment (symmetric)
   {
      test_ = "Row-major/row-major HermitianMatrix sparse matrix multiplication assignment (symmetric)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;
      mat.insert( 1UL, 2UL, 0 );

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (symmetric)
   {
      test_ = "Row-major/column-major HermitianMatrix sparse matrix multiplication assignment (symmetric)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;
      mat.insert( 1UL, 2UL, 0 );

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix multiplication assignment (non-symmetric)
   {
      test_ = "Row-major/row-major HermitianMatrix sparse matrix multiplication assignment (non-symmetric)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix multiplication assignment (non-symmetric)
   {
      test_ = "Row-major/column-major HermitianMatrix sparse matrix multiplication assignment (non-symmetric)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Row-major/row-major HermitianMatrix sparse matrix multiplication assignment (HermitianMatrix)";

      blaze::HermitianMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > herm1( 3UL, 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      HT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Row-major/column-major HermitianMatrix sparse matrix multiplication assignment (HermitianMatrix)";

      blaze::HermitianMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > herm1( 3UL, 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      HT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major dense matrix multiplication assignment (symmetric)
   {
      test_ = "Column-major/row-major HermitianMatrix dense matrix multiplication assignment (symmetric)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (symmetric)
   {
      test_ = "Column-major/column-major HermitianMatrix dense matrix multiplication assignment (symmetric)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix multiplication assignment (non-symmetric)
   {
      test_ = "Column-major/row-major HermitianMatrix dense matrix multiplication assignment (non-symmetric)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix multiplication assignment (non-symmetric)
   {
      test_ = "Column-major/column-major HermitianMatrix dense matrix multiplication assignment (non-symmetric)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Column-major/row-major HermitianMatrix dense matrix multiplication assignment (HermitianMatrix)";

      HT herm1( 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      OHT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Column-major/column-major HermitianMatrix dense matrix multiplication assignment (HermitianMatrix)";

      OHT herm1( 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      OHT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix multiplication assignment (symmetric)
   {
      test_ = "Column-major/row-major HermitianMatrix sparse matrix multiplication assignment (symmetric)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;
      mat.insert( 1UL, 2UL, 0 );

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (symmetric)
   {
      test_ = "Column-major/column-major HermitianMatrix sparse matrix multiplication assignment (symmetric)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,0) = 2;
      mat(1,1) = 2;
      mat(2,2) = 2;
      mat.insert( 1UL, 2UL, 0 );

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      herm *= mat;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  2 || herm(0,1) != -8 || herm(0,2) != 14 ||
          herm(1,0) != -8 || herm(1,1) !=  4 || herm(1,2) !=  0 ||
          herm(2,0) != 14 || herm(2,1) !=  0 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix multiplication assignment (non-symmetric)
   {
      test_ = "Column-major/row-major HermitianMatrix sparse matrix multiplication assignment (non-symmetric)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix multiplication assignment (non-symmetric)
   {
      test_ = "Column-major/column-major HermitianMatrix sparse matrix multiplication assignment (non-symmetric)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  6;
      mat(1,1) =  3;
      mat(2,0) =  6;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      try {
         herm *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-symmetric column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Column-major/row-major HermitianMatrix sparse matrix multiplication assignment (HermitianMatrix)";

      blaze::HermitianMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > herm1( 3UL, 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      OHT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (HermitianMatrix)
   {
      test_ = "Column-major/column-major HermitianMatrix sparse matrix multiplication assignment (HermitianMatrix)";

      blaze::HermitianMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > herm1( 3UL, 3UL );
      herm1(0,0) = 2;
      herm1(1,1) = 2;
      herm1(2,2) = 2;

      OHT herm2( 3UL );
      herm2(0,0) =  1;
      herm2(0,1) = -4;
      herm2(0,2) =  7;
      herm2(1,1) =  2;
      herm2(2,2) =  3;

      herm2 *= herm1;

      checkRows    ( herm2, 3UL );
      checkColumns ( herm2, 3UL );
      checkCapacity( herm2, 9UL );
      checkNonZeros( herm2, 7UL );
      checkNonZeros( herm2, 0UL, 3UL );
      checkNonZeros( herm2, 1UL, 2UL );
      checkNonZeros( herm2, 2UL, 2UL );

      if( herm2(0,0) !=  2 || herm2(0,1) != -8 || herm2(0,2) != 14 ||
          herm2(1,0) != -8 || herm2(1,1) !=  4 || herm2(1,2) !=  0 ||
          herm2(2,0) != 14 || herm2(2,1) !=  0 || herm2(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n(  2 -8 14 )\n( -8  4  0 )\n( 14  0  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of all HermitianMatrix (self-)scaling operations.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all available ways to scale an instance of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testScaling()
{
   //=====================================================================================
   // Row-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M*=s)";

      HT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm *= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M*s)";

      HT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm = herm * 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=s*M)";

      HT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm = 2 * herm;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M/=s)";

      HT herm( 3UL );
      herm(1,2) =  2;
      herm(2,0) = -4;
      herm(2,2) =  6;

      herm /= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0  1 )\n( -2 1  3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M/s)";

      HT herm( 3UL );
      herm(1,2) =  2;
      herm(2,0) = -4;
      herm(2,2) =  6;

      herm = herm / 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0  1 )\n( -2 1  3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major HermitianMatrix::scale()
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::scale()";

      // Initialization check
      HT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0 1 )\n( -2 1 3 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      herm.scale( 2 );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0 2 )\n( -4 2 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      herm.scale( 0.5 );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0 1 )\n( -2 1 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M*=s)";

      OHT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm *= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M*s)";

      OHT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm = herm * 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=s*M)";

      OHT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      herm = 2 * herm;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0  2 )\n( -4 2  6 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M/=s)";

      OHT herm( 3UL );
      herm(1,2) =  2;
      herm(2,0) = -4;
      herm(2,2) =  6;

      herm /= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0  1 )\n( -2 1  3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M/s)";

      OHT herm( 3UL );
      herm(1,2) =  2;
      herm(2,0) = -4;
      herm(2,2) =  6;

      herm = herm / 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0  1 )\n( -2 1  3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major HermitianMatrix::scale()
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::scale()";

      // Initialization check
      OHT herm( 3UL );
      herm(1,2) =  1;
      herm(2,0) = -2;
      herm(2,2) =  3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0 1 )\n( -2 1 3 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      herm.scale( 2 );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -4 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  2 ||
          herm(2,0) != -4 || herm(2,1) != 2 || herm(2,2) !=  6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -4 )\n(  0 0 2 )\n( -4 2 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      herm.scale( 0.5 );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) !=  0 || herm(0,1) != 0 || herm(0,2) != -2 ||
          herm(1,0) !=  0 || herm(1,1) != 0 || herm(1,2) !=  1 ||
          herm(2,0) != -2 || herm(2,1) != 1 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 0 -2 )\n(  0 0 1 )\n( -2 1 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the HermitianMatrix function call operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the function call operator
// of the HermitianMatrix specialization. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void DenseRealTest::testFunctionCall()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::operator()";

      HT herm( 3UL );

      // Writing the element (1,1)
      herm(1,1) = 1;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 1UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 1 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the elements (2,1) and (1,2)
      herm(2,1) = 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 3UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 1UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 2 ||
          herm(2,0) != 0 || herm(2,1) != 2 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 1 2 )\n( 0 2 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the elements (0,2) and (2,0)
      herm(0,2) = herm(1,2);

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 2 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 2 ||
          herm(2,0) != 2 || herm(2,1) != 2 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 2 )\n( 0 1 2 )\n( 2 2 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the elements (1,2) and (2,1)
      herm(1,2) += 3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 2 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 5 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 2 )\n( 0 1 5 )\n( 2 5 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the elements (0,1) and (1,0)
      herm(0,1) -= 4;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -4 || herm(0,2) != 2 ||
          herm(1,0) != -4 || herm(1,1) !=  1 || herm(1,2) != 5 ||
          herm(2,0) !=  2 || herm(2,1) !=  5 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -4  2 )\n( -4  1  5 )\n(  2  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,1)
      herm(2,0) *= -3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -4 || herm(0,2) != -6 ||
          herm(1,0) != -4 || herm(1,1) !=  1 || herm(1,2) !=  5 ||
          herm(2,0) != -6 || herm(2,1) !=  5 || herm(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -4 -6 )\n( -4  1  5 )\n( -6  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the elements (0,2) and (2,0)
      herm(1,0) /= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -2 || herm(0,2) != -6 ||
          herm(1,0) != -2 || herm(1,1) !=  1 || herm(1,2) !=  5 ||
          herm(2,0) != -6 || herm(2,1) !=  5 || herm(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -2 -6 )\n( -2  1  5 )\n( -6  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::operator()";

      OHT herm( 3UL );

      // Writing the element (1,1)
      herm(1,1) = 1;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 1UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 1UL );
      checkNonZeros( herm, 2UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 1 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the elements (2,1) and (1,2)
      herm(2,1) = 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 3UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 1UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 2 ||
          herm(2,0) != 0 || herm(2,1) != 2 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 1 2 )\n( 0 2 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the elements (0,2) and (2,0)
      herm(0,2) = herm(1,2);

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 2 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 2 ||
          herm(2,0) != 2 || herm(2,1) != 2 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 2 )\n( 0 1 2 )\n( 2 2 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the elements (1,2) and (2,1)
      herm(1,2) += 3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 5UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 2 ||
          herm(1,0) != 0 || herm(1,1) != 1 || herm(1,2) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 5 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 2 )\n( 0 1 5 )\n( 2 5 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the elements (0,1) and (1,0)
      herm(0,1) -= 4;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -4 || herm(0,2) != 2 ||
          herm(1,0) != -4 || herm(1,1) !=  1 || herm(1,2) != 5 ||
          herm(2,0) !=  2 || herm(2,1) !=  5 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -4  2 )\n( -4  1  5 )\n(  2  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,1)
      herm(2,0) *= -3;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -4 || herm(0,2) != -6 ||
          herm(1,0) != -4 || herm(1,1) !=  1 || herm(1,2) !=  5 ||
          herm(2,0) != -6 || herm(2,1) !=  5 || herm(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -4 -6 )\n( -4  1  5 )\n( -6  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the elements (0,2) and (2,0)
      herm(1,0) /= 2;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) !=  0 || herm(0,1) != -2 || herm(0,2) != -6 ||
          herm(1,0) != -2 || herm(1,1) !=  1 || herm(1,2) !=  5 ||
          herm(2,0) != -6 || herm(2,1) !=  5 || herm(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  0 -2 -6 )\n( -2  1  5 )\n( -6  5  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the HermitianMatrix iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testIterator()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      typedef HT::Iterator       Iterator;
      typedef HT::ConstIterator  ConstIterator;

      HT herm( 3UL );
      herm(0,1) =  1;
      herm(1,2) = -2;
      herm(2,2) =  3;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( herm, 1UL ) );

         if( it == end( herm, 1UL ) || *it != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row via Iterator (end-begin)
      {
         test_ = "Row-major Iterator subtraction (end-begin)";

         const ptrdiff_t number( end( herm, 0UL ) - begin( herm, 0UL ) );

         if( number != 3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row via Iterator (begin-end)
      {
         test_ = "Row-major Iterator subtraction (begin-end)";

         const ptrdiff_t number( begin( herm, 0UL ) - end( herm, 0UL ) );

         if( number != -3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: -3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator (end-begin)
      {
         test_ = "Row-major ConstIterator subtraction (end-begin)";

         const ptrdiff_t number( cend( herm, 1UL ) - cbegin( herm, 1UL ) );

         if( number != 3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator (begin-end)
      {
         test_ = "Row-major ConstIterator subtraction (begin-end)";

         const ptrdiff_t number( cbegin( herm, 1UL ) - cend( herm, 1UL ) );

         if( number != -3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: -3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( herm, 2UL ) );
         ConstIterator end( cend( herm, 2UL ) );

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 3UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Row-major assignment via Iterator";

         int value = 7;

         for( Iterator it=begin( herm, 2UL ); it!=end( herm, 2UL ); ++it ) {
            *it = value++;
         }

         if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 7 ||
             herm(1,0) != 1 || herm(1,1) != 0 || herm(1,2) != 8 ||
             herm(2,0) != 7 || herm(2,1) != 8 || herm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 1 7 )\n( 1 0 8 )\n( 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Row-major addition assignment via Iterator";

         int value = 4;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it += value++;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  5 || herm(0,2) !=  7 ||
             herm(1,0) != 5 || herm(1,1) !=  5 || herm(1,2) != 14 ||
             herm(2,0) != 7 || herm(2,1) != 14 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  5  7 )\n( 5  5 14 )\n( 7 14  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Row-major subtraction assignment via Iterator";

         int value = 4;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it -= value++;
         }

         if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 7 ||
             herm(1,0) != 1 || herm(1,1) != 0 || herm(1,2) != 8 ||
             herm(2,0) != 7 || herm(2,1) != 8 || herm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 1 7 )\n( 1 0 8 )\n( 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Row-major multiplication assignment via Iterator";

         int value = 2;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it *= value++;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  2 || herm(0,2) !=  7 ||
             herm(1,0) != 2 || herm(1,1) !=  0 || herm(1,2) != 32 ||
             herm(2,0) != 7 || herm(2,1) != 32 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  2  7 )\n( 2  0 32 )\n( 7 32  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Row-major division assignment via Iterator";

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it /= 2;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  1 || herm(0,2) !=  7 ||
             herm(1,0) != 1 || herm(1,1) !=  0 || herm(1,2) != 16 ||
             herm(2,0) != 7 || herm(2,1) != 16 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  1  7 )\n( 1  0 16 )\n( 7 16  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      typedef OHT::Iterator       Iterator;
      typedef OHT::ConstIterator  ConstIterator;

      OHT herm( 3UL );
      herm(0,1) =  1;
      herm(1,2) = -2;
      herm(2,2) =  3;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( herm, 1UL ) );

         if( it == end( herm, 1UL ) || *it != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column via Iterator (end-begin)
      {
         test_ = "Column-major Iterator subtraction (end-begin)";

         const ptrdiff_t number( end( herm, 0UL ) - begin( herm, 0UL ) );

         if( number != 3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column via Iterator (begin-end)
      {
         test_ = "Column-major Iterator subtraction (begin-end)";

         const ptrdiff_t number( begin( herm, 0UL ) - end( herm, 0UL ) );

         if( number != -3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: -3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st column via ConstIterator (end-begin)
      {
         test_ = "Column-major ConstIterator subtraction (end-begin)";

         const ptrdiff_t number( cend( herm, 1UL ) - cbegin( herm, 1UL ) );

         if( number != 3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st column via ConstIterator (begin-end)
      {
         test_ = "Column-major ConstIterator subtraction (begin-end)";

         const ptrdiff_t number( cbegin( herm, 1UL ) - cend( herm, 1UL ) );

         if( number != -3L ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: -3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( herm, 2UL ) );
         ConstIterator end( cend( herm, 2UL ) );

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 3UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Column-major assignment via Iterator";

         int value = 7;

         for( Iterator it=begin( herm, 2UL ); it!=end( herm, 2UL ); ++it ) {
            *it = value++;
         }

         if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 7 ||
             herm(1,0) != 1 || herm(1,1) != 0 || herm(1,2) != 8 ||
             herm(2,0) != 7 || herm(2,1) != 8 || herm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 1 7 )\n( 1 0 8 )\n( 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Column-major addition assignment via Iterator";

         int value = 4;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it += value++;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  5 || herm(0,2) !=  7 ||
             herm(1,0) != 5 || herm(1,1) !=  5 || herm(1,2) != 14 ||
             herm(2,0) != 7 || herm(2,1) != 14 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  5  7 )\n( 5  5 14 )\n( 7 14  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Column-major subtraction assignment via Iterator";

         int value = 4;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it -= value++;
         }

         if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 7 ||
             herm(1,0) != 1 || herm(1,1) != 0 || herm(1,2) != 8 ||
             herm(2,0) != 7 || herm(2,1) != 8 || herm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 1 7 )\n( 1 0 8 )\n( 7 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Column-major multiplication assignment via Iterator";

         int value = 2;

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it *= value++;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  2 || herm(0,2) !=  7 ||
             herm(1,0) != 2 || herm(1,1) !=  0 || herm(1,2) != 32 ||
             herm(2,0) != 7 || herm(2,1) != 32 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  2  7 )\n( 2  0 32 )\n( 7 32  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Column-major division assignment via Iterator";

         for( Iterator it=begin( herm, 1UL ); it!=end( herm, 1UL ); ++it ) {
            *it /= 2;
         }

         if( herm(0,0) != 0 || herm(0,1) !=  1 || herm(0,2) !=  7 ||
             herm(1,0) != 1 || herm(1,1) !=  0 || herm(1,2) != 16 ||
             herm(2,0) != 7 || herm(2,1) != 16 || herm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0  1  7 )\n( 1  0 16 )\n( 7 16  9 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testNonZeros()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::nonZeros()";

      // Empty matrix
      {
         HT herm( 3UL );

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 0UL );
         checkNonZeros( herm, 0UL, 0UL );
         checkNonZeros( herm, 1UL, 0UL );
         checkNonZeros( herm, 2UL, 0UL );

         if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
             herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
             herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Partially filled matrix
      {
         HT herm( 3UL );
         herm(0,0) =  1;
         herm(1,2) = -2;
         herm(2,0) =  0;
         herm(2,2) =  3;

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 4UL );
         checkNonZeros( herm, 0UL, 1UL );
         checkNonZeros( herm, 1UL, 1UL );
         checkNonZeros( herm, 2UL, 2UL );

         if( herm(0,0) != 1 || herm(0,1) !=  0 || herm(0,2) !=  0 ||
             herm(1,0) != 0 || herm(1,1) !=  0 || herm(1,2) != -2 ||
             herm(2,0) != 0 || herm(2,1) != -2 || herm(2,2) !=  3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1  0  0 )\n( 0  0 -2 )\n( 0 -2  3 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         HT herm( 3UL );
         herm(0,0) = -1;
         herm(0,1) =  2;
         herm(0,2) = -3;
         herm(1,1) =  4;
         herm(1,2) = -5;
         herm(2,2) =  6;

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm(0,0) != -1 || herm(0,1) !=  2 || herm(0,2) != -3 ||
             herm(1,0) !=  2 || herm(1,1) !=  4 || herm(1,2) != -5 ||
             herm(2,0) != -3 || herm(2,1) != -5 || herm(2,2) !=  6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( -1  2 -3 )\n(  2  4 -5 )\n( -3 -5  6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::nonZeros()";

      // Empty matrix
      {
         OHT herm( 3UL );

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 0UL );
         checkNonZeros( herm, 0UL, 0UL );
         checkNonZeros( herm, 1UL, 0UL );
         checkNonZeros( herm, 2UL, 0UL );

         if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
             herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
             herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Partially filled matrix
      {
         OHT herm( 3UL );
         herm(0,0) =  1;
         herm(1,2) = -2;
         herm(2,0) =  0;
         herm(2,2) =  3;

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 4UL );
         checkNonZeros( herm, 0UL, 1UL );
         checkNonZeros( herm, 1UL, 1UL );
         checkNonZeros( herm, 2UL, 2UL );

         if( herm(0,0) != 1 || herm(0,1) !=  0 || herm(0,2) !=  0 ||
             herm(1,0) != 0 || herm(1,1) !=  0 || herm(1,2) != -2 ||
             herm(2,0) != 0 || herm(2,1) != -2 || herm(2,2) !=  3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1  0  0 )\n( 0  0 -2 )\n( 0 -2  3 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         OHT herm( 3UL );
         herm(0,0) = -1;
         herm(0,1) =  2;
         herm(0,2) = -3;
         herm(1,1) =  4;
         herm(1,2) = -5;
         herm(2,2) =  6;

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm(0,0) != -1 || herm(0,1) !=  2 || herm(0,2) != -3 ||
             herm(1,0) !=  2 || herm(1,1) !=  4 || herm(1,2) != -5 ||
             herm(2,0) != -3 || herm(2,1) != -5 || herm(2,2) !=  6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( -1  2 -3 )\n(  2  4 -5 )\n( -3 -5  6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testReset()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::reset()";

      // Initialization check
      HT herm( 3UL );
      herm(0,0) = 1;
      herm(0,1) = 2;
      herm(0,2) = 3;
      herm(1,1) = 4;
      herm(1,2) = 5;
      herm(2,2) = 6;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 9UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
          herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a single element
      reset( herm(0,1) );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting row 1
      reset( herm, 1UL );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 4UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 0UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 3 || herm(2,1) != 0 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 0 0 )\n( 3 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( herm );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );
      checkNonZeros( herm, 2UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::reset()";

      // Initialization check
      OHT herm( 3UL );
      herm(0,0) = 1;
      herm(0,1) = 2;
      herm(0,2) = 3;
      herm(1,1) = 4;
      herm(1,2) = 5;
      herm(2,2) = 6;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 9UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
          herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a single element
      reset( herm(0,1) );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting column 1
      reset( herm, 1UL );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 4UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 0UL );
      checkNonZeros( herm, 2UL, 2UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 3 || herm(2,1) != 0 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 0 0 )\n( 3 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( herm );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );
      checkNonZeros( herm, 2UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testClear()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::clear()";

      // Initialization check
      HT herm( 3UL );
      herm(0,0) = 1;
      herm(0,1) = 2;
      herm(0,2) = 3;
      herm(1,1) = 4;
      herm(1,2) = 5;
      herm(2,2) = 6;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 9UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
          herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a single element
      clear( herm(0,1) );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( herm );

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::clear()";

      // Initialization check
      OHT herm( 3UL );
      herm(0,0) = 1;
      herm(0,1) = 2;
      herm(0,2) = 3;
      herm(1,1) = 4;
      herm(1,2) = 5;
      herm(2,2) = 6;

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 9UL );
      checkNonZeros( herm, 0UL, 3UL );
      checkNonZeros( herm, 1UL, 3UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
          herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a single element
      clear( herm(0,1) );

      checkRows    ( herm, 3UL );
      checkColumns ( herm, 3UL );
      checkCapacity( herm, 9UL );
      checkNonZeros( herm, 7UL );
      checkNonZeros( herm, 0UL, 2UL );
      checkNonZeros( herm, 1UL, 2UL );
      checkNonZeros( herm, 2UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 5 ||
          herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 3 )\n( 0 4 5 )\n( 3 5 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( herm );

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c resize() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c resize() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testResize()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::resize()";

      // Initialization check
      HT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Resizing to 2x2
      herm.resize( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      herm(0,1) = 1;
      herm(1,1) = 2;
      herm.resize( 4UL, true );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm,  3UL );
      checkNonZeros( herm,  0UL, 1UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 0UL );
      checkNonZeros( herm,  3UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 0 || herm(0,3) != 0 ||
          herm(1,0) != 1 || herm(1,1) != 2 || herm(1,2) != 0 || herm(1,3) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 || herm(2,3) != 0 ||
          herm(3,0) != 0 || herm(3,1) != 0 || herm(3,2) != 0 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 0 0 )\n( 1 2 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      herm(2,2) = 3;
      herm.resize( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 3UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 ||
          herm(1,0) != 1 || herm(1,1) != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 )\n( 1 2 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      herm.resize( 0UL );

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::resize()";

      // Initialization check
      OHT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Resizing to 2x2
      herm.resize( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      herm(0,1) = 1;
      herm(1,1) = 2;
      herm.resize( 4UL );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm,  3UL );
      checkNonZeros( herm,  0UL, 1UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 0UL );
      checkNonZeros( herm,  3UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 0 || herm(0,3) != 0 ||
          herm(1,0) != 1 || herm(1,1) != 2 || herm(1,2) != 0 || herm(1,3) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 || herm(2,3) != 0 ||
          herm(3,0) != 0 || herm(3,1) != 0 || herm(3,2) != 0 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 0 0 )\n( 1 2 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      herm(2,2) = 2;
      herm.resize( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 3UL );
      checkNonZeros( herm, 0UL, 1UL );
      checkNonZeros( herm, 1UL, 2UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 ||
          herm(1,0) != 1 || herm(1,1) != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 )\n( 1 2 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      herm.resize( 0UL );

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c extend() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c extend() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testExtend()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::extend()";

      // Initialization check
      HT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Extending the size of the matrix to 2x2
      herm.extend( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Extending to 4x4 and preserving the elements
      herm(0,1) = 1;
      herm(1,1) = 2;
      herm.extend( 2UL, true );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm,  3UL );
      checkNonZeros( herm,  0UL, 1UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 0UL );
      checkNonZeros( herm,  3UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 0 || herm(0,3) != 0 ||
          herm(1,0) != 1 || herm(1,1) != 2 || herm(1,2) != 0 || herm(1,3) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 || herm(2,3) != 0 ||
          herm(3,0) != 0 || herm(3,1) != 0 || herm(3,2) != 0 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 0 0 )\n( 1 2 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::extend()";

      // Initialization check
      OHT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Extending the size of the matrix to 2x2
      herm.extend( 2UL );

      checkRows    ( herm, 2UL );
      checkColumns ( herm, 2UL );
      checkCapacity( herm, 4UL );
      checkNonZeros( herm, 0UL );
      checkNonZeros( herm, 0UL, 0UL );
      checkNonZeros( herm, 1UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Extending to 4x4 and preserving the elements
      herm(0,1) = 1;
      herm(1,1) = 2;
      herm.extend( 2UL, true );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm,  3UL );
      checkNonZeros( herm,  0UL, 1UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 0UL );
      checkNonZeros( herm,  3UL, 0UL );

      if( herm(0,0) != 0 || herm(0,1) != 1 || herm(0,2) != 0 || herm(0,3) != 0 ||
          herm(1,0) != 1 || herm(1,1) != 2 || herm(1,2) != 0 || herm(1,3) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 0 || herm(2,3) != 0 ||
          herm(3,0) != 0 || herm(3,1) != 0 || herm(3,2) != 0 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 0 1 0 0 )\n( 1 2 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reserve() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reserve() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testReserve()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::reserve()";

      // Initialization check
      HT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Increasing the capacity of the matrix
      herm.reserve( 10UL );

      checkRows    ( herm,  0UL );
      checkColumns ( herm,  0UL );
      checkCapacity( herm, 10UL );
      checkNonZeros( herm,  0UL );

      // Further increasing the capacity of the matrix
      herm.reserve( 20UL );

      checkRows    ( herm,  0UL );
      checkColumns ( herm,  0UL );
      checkCapacity( herm, 20UL );
      checkNonZeros( herm,  0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::reserve()";

      // Initialization check
      OHT herm;

      checkRows    ( herm, 0UL );
      checkColumns ( herm, 0UL );
      checkNonZeros( herm, 0UL );

      // Increasing the capacity of the matrix
      herm.reserve( 10UL );

      checkRows    ( herm,  0UL );
      checkColumns ( herm,  0UL );
      checkCapacity( herm, 10UL );
      checkNonZeros( herm,  0UL );

      // Further increasing the capacity of the matrix
      herm.reserve( 20UL );

      checkRows    ( herm,  0UL );
      checkColumns ( herm,  0UL );
      checkCapacity( herm, 20UL );
      checkNonZeros( herm,  0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c shrinkToFit() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c shrinkToFit() member function of the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testShrinkToFit()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix::shrinkToFit()";

      // Shrinking a matrix without excessive capacity
      {
         HT herm{ { 1, 2, 3 }, { 2, 4, 5 }, { 3, 5, 6 } };

         herm.shrinkToFit();

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm.capacity() != herm.rows() * herm.spacing() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Capacity         : " << herm.capacity() << "\n"
                << "   Expected capacity: " << ( herm.rows() * herm.spacing() ) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
             herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
             herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Shrinking a matrix with excessive capacity
      {
         HT herm{ { 1, 2, 3 }, { 2, 4, 5 }, { 3, 5, 6 } };
         herm.reserve( 100UL );

         herm.shrinkToFit();

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm.capacity() != herm.rows() * herm.spacing() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Capacity         : " << herm.capacity() << "\n"
                << "   Expected capacity: " << ( herm.rows() * herm.spacing() ) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
             herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
             herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix::shrinkToFit()";

      // Shrinking a matrix without excessive capacity
      {
         OHT herm{ { 1, 2, 3 }, { 2, 4, 5 }, { 3, 5, 6 } };

         herm.shrinkToFit();

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm.capacity() != herm.spacing() * herm.columns() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Capacity         : " << herm.capacity() << "\n"
                << "   Expected capacity: " << ( herm.spacing() * herm.columns() ) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
             herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
             herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Shrinking a matrix with excessive capacity
      {
         OHT herm{ { 1, 2, 3 }, { 2, 4, 5 }, { 3, 5, 6 } };
         herm.reserve( 100UL );

         herm.shrinkToFit();

         checkRows    ( herm, 3UL );
         checkColumns ( herm, 3UL );
         checkCapacity( herm, 9UL );
         checkNonZeros( herm, 9UL );
         checkNonZeros( herm, 0UL, 3UL );
         checkNonZeros( herm, 1UL, 3UL );
         checkNonZeros( herm, 2UL, 3UL );

         if( herm.capacity() != herm.spacing() * herm.columns() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Capacity         : " << herm.capacity() << "\n"
                << "   Expected capacity: " << ( herm.spacing() * herm.columns() ) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( herm(0,0) != 1 || herm(0,1) != 2 || herm(0,2) != 3 ||
             herm(1,0) != 2 || herm(1,1) != 4 || herm(1,2) != 5 ||
             herm(2,0) != 3 || herm(2,1) != 5 || herm(2,2) != 6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Shrinking the matrix failed\n"
                << " Details:\n"
                << "   Result:\n" << herm << "\n"
                << "   Expected result:\n( 1 2 3 )\n( 2 4 5 )\n( 3 5 6 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c swap() functionality of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c swap() function of the HermitianMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testSwap()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major HermitianMatrix swap";

      HT herm1( 2UL );
      herm1(0,0) = 1;
      herm1(0,1) = 2;
      herm1(1,1) = 3;

      HT herm2( 2UL );
      herm2(0,0) = 4;
      herm2(0,1) = 5;

      swap( herm1, herm2 );

      checkRows    ( herm1, 2UL );
      checkColumns ( herm1, 2UL );
      checkCapacity( herm1, 4UL );
      checkNonZeros( herm1, 3UL );
      checkNonZeros( herm1, 0UL, 2UL );
      checkNonZeros( herm1, 1UL, 1UL );

      if( herm1(0,0) != 4 || herm1(0,1) != 5 || herm1(1,0) != 5 || herm1(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm1 << "\n"
             << "   Expected result:\n( 4 5 )\n( 5 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( herm2, 2UL );
      checkColumns ( herm2, 2UL );
      checkCapacity( herm2, 4UL );
      checkNonZeros( herm2, 4UL );
      checkNonZeros( herm2, 0UL, 2UL );
      checkNonZeros( herm2, 1UL, 2UL );

      if( herm2(0,0) != 1 || herm2(0,1) != 2 || herm2(1,0) != 2 || herm2(1,1) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n( 1 2 )\n( 2 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major HermitianMatrix swap";

      OHT herm1( 2UL );
      herm1(0,0) = 1;
      herm1(0,1) = 2;
      herm1(1,1) = 3;

      OHT herm2( 2UL );
      herm2(0,0) = 4;
      herm2(0,1) = 5;

      swap( herm1, herm2 );

      checkRows    ( herm1, 2UL );
      checkColumns ( herm1, 2UL );
      checkCapacity( herm1, 4UL );
      checkNonZeros( herm1, 3UL );
      checkNonZeros( herm1, 0UL, 2UL );
      checkNonZeros( herm1, 1UL, 1UL );

      if( herm1(0,0) != 4 || herm1(0,1) != 5 || herm1(1,0) != 5 || herm1(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm1 << "\n"
             << "   Expected result:\n( 4 5 )\n( 5 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( herm2, 2UL );
      checkColumns ( herm2, 2UL );
      checkCapacity( herm2, 4UL );
      checkNonZeros( herm2, 4UL );
      checkNonZeros( herm2, 0UL, 2UL );
      checkNonZeros( herm2, 1UL, 2UL );

      if( herm2(0,0) != 1 || herm2(0,1) != 2 || herm2(1,0) != 2 || herm2(1,1) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << herm2 << "\n"
             << "   Expected result:\n( 1 2 )\n( 2 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c transpose() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c transpose() member function of the HermitianMatrix
// specialization. Additionally, it performs a test of self-transpose via the \c trans()
// function. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testTranspose()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major self-transpose via transpose()";

      HT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      transpose( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-transpose via trans()";

      HT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      herm = trans( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major self-transpose via transpose()";

      OHT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      transpose( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-transpose via trans()";

      OHT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      herm = trans( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c ctranspose() member function of the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c ctranspose() member function of the HermitianMatrix
// specialization. Additionally, it performs a test of self-transpose via the \c ctrans()
// function. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testCTranspose()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major self-transpose via ctranspose()";

      HT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      ctranspose( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-transpose via ctrans()";

      HT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      herm = ctrans( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major self-transpose via ctranspose()";

      OHT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      ctranspose( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-transpose via ctrans()";

      OHT herm( 4UL );
      herm(0,0) = 1;
      herm(0,2) = 2;
      herm(0,3) = 3;
      herm(1,1) = 4;
      herm(1,3) = 5;
      herm(2,2) = 6;
      herm(2,3) = 7;

      herm = ctrans( herm );

      checkRows    ( herm,  4UL );
      checkColumns ( herm,  4UL );
      checkCapacity( herm, 16UL );
      checkNonZeros( herm, 11UL );
      checkNonZeros( herm,  0UL, 3UL );
      checkNonZeros( herm,  1UL, 2UL );
      checkNonZeros( herm,  2UL, 3UL );
      checkNonZeros( herm,  3UL, 3UL );

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 2 || herm(0,3) != 3 ||
          herm(1,0) != 0 || herm(1,1) != 4 || herm(1,2) != 0 || herm(1,3) != 5 ||
          herm(2,0) != 2 || herm(2,1) != 0 || herm(2,2) != 6 || herm(2,3) != 7 ||
          herm(3,0) != 3 || herm(3,1) != 5 || herm(3,2) != 7 || herm(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 4 0 5 )\n( 2 0 6 7 )\n( 3 5 7 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testIsDefault()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         HT herm;

         if( isDefault( herm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         HT herm( 3UL );

         if( isDefault( herm(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << herm(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( herm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         HT herm( 3UL );
         herm(0,1) = 1;

         if( isDefault( herm(0,1) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << herm(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( herm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         OHT herm;

         if( isDefault( herm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         OHT herm( 3UL );

         if( isDefault( herm(1,0) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << herm(1,0) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( herm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         OHT herm( 3UL );
         herm(1,0) = 1;

         if( isDefault( herm(1,0) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << herm(1,0) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( herm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << herm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c submatrix() function with the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c submatrix() function with the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testSubmatrix()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major submatrix() function";

      typedef blaze::Submatrix<HT>  SMT;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      SMT sm = submatrix( herm, 0UL, 1UL, 2UL, 2UL );

      if( sm(0,1) != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(0,1) << "\n"
             << "   Expected result: 7\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(0UL);

      if( it == sm.end(0UL) || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      sm(1,1) = -5;

      if( sm(0,0) != -4 || sm(0,1) !=  7 ||
          sm(1,0) !=  2 || sm(1,1) != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  7 )\n(  2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 0 0 )\n( 0 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major submatrix() function";

      typedef blaze::Submatrix<OHT>  SMT;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      SMT sm = submatrix( herm, 0UL, 1UL, 2UL, 2UL );

      if( sm(0,1) != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(0,1) << "\n"
             << "   Expected result: 7\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(0UL);

      if( it == sm.end(0UL) || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      sm(1,1) = -5;

      if( sm(0,0) != -4 || sm(0,1) !=  7 ||
          sm(1,0) !=  2 || sm(1,1) != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  7 )\n(  2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 0 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 0 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 0 0 )\n( 0 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c row() function with the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c row() function with the HermitianMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testRow()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major row() function";

      typedef blaze::Row<HT>  RT;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      RT row1 = row( herm, 1UL );

      if( row1[1] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: 2\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it( row1.begin() );

      if( it == row1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      row1[2] = -5;

      if( row1[0] != -4 || row1[1] != 2 || row1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( -4 2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row1 );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 7 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 7 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 0 0 )\n( 7 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major row() function";

      typedef blaze::Row<OHT>  RT;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      RT row1 = row( herm, 1UL );

      if( row1[1] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: 2\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it( row1.begin() );

      if( it == row1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      row1[2] = -5;

      if( row1[0] != -4 || row1[1] != 2 || row1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( -4 2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row1 );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 7 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 7 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 0 0 )\n( 7 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c column() function with the HermitianMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c column() function with the HermitianMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseRealTest::testColumn()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major column() function";

      typedef blaze::Column<HT>  CT;

      HT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      CT col1 = column( herm, 1UL );

      if( col1[1] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: 2\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it( col1.begin() );

      if( it == col1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[2] = -5;

      if( col1[0] != -4 || col1[1] != 2 || col1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -4 2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 7 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 7 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 0 0 )\n( 7 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major column() function";

      typedef blaze::Column<OHT>  CT;

      OHT herm( 3UL );
      herm(0,0) =  1;
      herm(0,1) = -4;
      herm(0,2) =  7;
      herm(1,1) =  2;
      herm(2,2) =  3;

      CT col1 = column( herm, 1UL );

      if( col1[1] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: 2\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it( col1.begin() );

      if( it == col1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[2] = -5;

      if( col1[0] != -4 || col1[1] != 2 || col1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -4 2 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) !=  1 || herm(0,1) != -4 || herm(0,2) !=  7 ||
          herm(1,0) != -4 || herm(1,1) !=  2 || herm(1,2) != -5 ||
          herm(2,0) !=  7 || herm(2,1) != -5 || herm(2,2) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n(  1 -4  7 )\n( -4  2 -5 )\n(  7 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( herm(0,0) != 1 || herm(0,1) != 0 || herm(0,2) != 7 ||
          herm(1,0) != 0 || herm(1,1) != 0 || herm(1,2) != 0 ||
          herm(2,0) != 7 || herm(2,1) != 0 || herm(2,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << herm << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 0 0 )\n( 7 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************

} // namespace hermitianmatrix

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running HermitianMatrix dense real test (part 2)..." << std::endl;

   try
   {
      RUN_HERMITIANMATRIX_DENSEREAL_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during HermitianMatrix dense real test (part 2):\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
