/*
 * RKF.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: forma
 */
#include "RKF.hpp"
#include<iostream>

std::ostream&
operator << (std::ostream& out, const ODE::RKFResult& res)
{
  out<<"# Number ot time steps:"<<res.time.size()<<" N. contractions:"<<res.contractions<<" N. expansions:"<<res.expansions<<std::endl;
  out<<"#   t    y   Estimated error="<<res.estimatedError<<std::endl;
  double hmin=res.time[1]-res.time[0];
  double hmax=hmin;
  for (unsigned int i=0;i<res.time.size()-1;++i)
    {
      auto delta=res.time[i+1]-res.time[i];
      hmax=std::max(hmax,delta);
      hmin=std::min(hmin,delta);
    }
  out<<"# hmin:"<<hmin<<" hmax:"<<hmax<<std::endl;
  std::size_t i=0;
  for (auto const & t: res.time)
    out<<t<<" "<<res.y[i++]<<std::endl;
  return out;
}
