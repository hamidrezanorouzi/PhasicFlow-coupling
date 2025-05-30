/*------------------------------- phasicFlow ---------------------------------
      O        C enter of
     O O       E ngineering and
    O   O      M ultiscale modeling of
   OOOOOOO     F luid flow       
------------------------------------------------------------------------------
  Copyright (C): www.cemf.ir
  email: hamid.r.norouzi AT gmail.com
------------------------------------------------------------------------------  
Licence:
  This file is part of phasicFlow code. It is a free software for simulating 
  granular and multiphase flows. You can redistribute it and/or modify it under
  the terms of GNU General Public License v3 or any other later versions. 
 
  phasicFlow is distributed to help others in their research in the field of 
  granular and multiphase flows, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

-----------------------------------------------------------------------------*/

#ifndef __Rong_hpp__ 
#define __Rong_hpp__

// from OpenFOAM
#include "OFCompatibleHeader.hpp"

#include "typeInfo.hpp"

namespace pFlow::coupling
{
class Rong

{

	Foam::scalar 		residualRe_;

public:

	// type info
	TypeInfo("Rong");

	Rong(const Foam::dictionary& dict);

	virtual ~Rong() = default;

	inline
	Foam::scalar dimlessDrag(Foam::scalar Re, Foam::scalar ep)const
	{

		auto Rec = Foam::max(Re,residualRe_);
		Foam::scalar xi = 2.65*(1+ep) - (5.3-(3.5*ep))*Foam::pow(ep , 2)*Foam::exp(-0.5*Foam::pow(1.5-Foam::log10(Rec),2));
		Foam::scalar Cd = Foam::pow(0.63+4.8/Foam::sqrt(Rec),2);

		return Cd/24 * Re * Foam::pow(ep, -xi ); 
		
	}

	inline 
	Foam::scalar operator()(Foam::scalar Re, Foam::scalar ep)const
	{
		return dimlessDrag(Re, ep);
	}
		
	
}; 

} // pFlow::coupling


#endif
