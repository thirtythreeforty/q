/*=============================================================================
   Copyright (c) 2014-2023 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(CYCFI_Q_LINEAR_GEN_HPP_APRIL_29_2023)
#define CYCFI_Q_LINEAR_GEN_HPP_APRIL_29_2023

#include <q/support/base.hpp>
#include <q/support/literals.hpp>

namespace cycfi::q
{
   ////////////////////////////////////////////////////////////////////////////
   // Linear growth generator.
   //
   // The linear growth generator generates a linearly increasing amplitude
   // from 0.0 to 1.0 specified by the duration (width) and samples per
   // second (sps) parameters. This is essentially a basic straight ramp
   // from 0.0 to 1.0.
   ////////////////////////////////////////////////////////////////////////////
   struct linear_growth_gen
   {
       linear_growth_gen(duration width, float sps)
       : _rate{1.0f / (as_float(width) * sps)}
      {
      }

      float operator()()
      {
         _y += _rate;
         return _y;
      }

      void config(duration width, float sps)
      {
         _rate = 1.0f / (as_float(width) * sps);
      }

      void reset()
      {
         _y = 0;
      }

   private:

      float _rate;
      float _y = 0;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Linear decay generator.
   //
   // The inverse of the linear growth generator. This is essentially a basic
   // straight ramp from 1.0 to 0.0.
   ////////////////////////////////////////////////////////////////////////////
   struct linear_decay_gen : linear_growth_gen
   {
      linear_decay_gen(duration width, float sps)
       : linear_growth_gen{width, sps}
      {
      }

      float operator()()
      {
         return 1.0f - linear_growth_gen::operator()();
      }
   };
}

#endif
