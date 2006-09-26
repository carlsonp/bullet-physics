/*
 * Copyright (c) 2005 Erwin Coumans http://continuousphysics.com/Bullet/
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies.
 * Erwin Coumans makes no representations about the suitability 
 * of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
*/
#ifndef VEHICLE_RAYCASTER_H
#define VEHICLE_RAYCASTER_H

#include "LinearMath/SimdVector3.h"

/// btVehicleRaycaster is provides interface for between vehicle simulation and raycasting
struct btVehicleRaycaster
{
virtual ~btVehicleRaycaster()
{
}
	struct btVehicleRaycasterResult
	{
		btVehicleRaycasterResult() :m_distFraction(-1.f){};
		btSimdVector3	m_hitPointInWorld;
		btSimdVector3	m_hitNormalInWorld;
		SimdScalar	m_distFraction;
	};

	virtual void* CastRay(const btSimdVector3& from,const btSimdVector3& to, btVehicleRaycasterResult& result) = 0;

};

#endif //VEHICLE_RAYCASTER_H

