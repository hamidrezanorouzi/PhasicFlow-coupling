/*------------------------------- phasicFlow ---------------------------------
      O        C enter of
     O O       E ngineering and
    O   O      M ultiscale modeling of
   OOOOOOO     F luid flow       
------------------------------------------------------------------------------
 _____ _____ ____
|   __|   __|    \    Engineering    |
|   __|   __|  |  |   Fluid          |
|_____|__|  |____/    Dynamics       |  www.fluidDynamics.at

------------------------------------------------------------------------------- 
Licence:
  This file is part of phasicFlow code. It is a free software for simulating 
  granular and multiphase flows. You can redistribute it and/or modify it under
  the terms of GNU General Public License v3 or any other later versions. 
 
  phasicFlow is distributed to help others in their research in the field of 
  granular and multiphase flows, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

-----------------------------------------------------------------------------*/

#ifndef __resolvedCouplingSystem_hpp__
#define __resolvedCouplingSystem_hpp__

#include "triSurface.H"
#include "triSurfaceSearch.H"

#include "couplingSystem.hpp"
#include "virtualConstructor.hpp"


namespace pFlow::coupling
{


class resolvedCouplingSystem
:
	public couplingSystem
{
protected:

	Foam::volScalarField alpha_;
	
public:

	resolvedCouplingSystem(
		word shapeTypeName, 
		Foam::fvMesh& mesh,
		int argc, 
		char* argv[]);

	resolvedCouplingSystem(const resolvedCouplingSystem&) = delete;
	
	resolvedCouplingSystem& operator=(const resolvedCouplingSystem&) = delete;

	resolvedCouplingSystem(resolvedCouplingSystem&&) = delete;

	resolvedCouplingSystem& operator=(resolvedCouplingSystem&&) = delete;

	~resolvedCouplingSystem() override = default;

	const Foam::dictionary& resolvedDict()const
	{
		return this->subDict("resolved");
	}

	/// Const access to alpha
	inline
	const Foam::volScalarField& alpha()const
	{
		return alpha_;
	}

	/// Access to alpha
	inline
	Foam::volScalarField& alpha()
	{
		return alpha_;
	}

	/// Access to fluid torque
	inline 
	Plus::realx3ProcCMField& fluidTorque()
	{
		return couplingSystem::fluidTorque();
	}

	/// Access to fluid force
	inline
	Plus::realx3ProcCMField& fluidForce()
	{
		return couplingSystem::fluidForce();
	}

	/// Calculating the solid-fluid interaction
	void calculateSolidInteraction
	(
		const Foam::PtrList<Foam::triSurface>& particleSTLs,
		pFlow::uniquePtr<Foam::volScalarField>& particleIDPtr,
		Foam::volVectorField& Us
	);

	/// Calculating the fluid-solid interaction
	void calculateFluidInteraction
	(
		const Foam::volScalarField& p,	
		const Foam::volScalarField& rho,
		const Foam::volSymmTensorField& devRhoReff,
		const Foam::PtrList<Foam::triSurface>& particleSTLs
	);

}; 

} // pFlow::coupling

#endif //__resolvedCouplingSystem_hpp__
