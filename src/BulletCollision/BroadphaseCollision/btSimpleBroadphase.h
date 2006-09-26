/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SIMPLE_BROADPHASE_H
#define SIMPLE_BROADPHASE_H


#include "btOverlappingPairCache.h"


struct btSimpleBroadphaseProxy : public btBroadphaseProxy
{
	btSimdVector3	m_min;
	btSimdVector3	m_max;
	
	btSimpleBroadphaseProxy() {};

	btSimpleBroadphaseProxy(const SimdPoint3& minpt,const SimdPoint3& maxpt,int shapeType,void* userPtr,short int collisionFilterGroup,short int collisionFilterMask)
	:btBroadphaseProxy(userPtr,collisionFilterGroup,collisionFilterMask),
	m_min(minpt),m_max(maxpt)		
	{
	}
	

};

///SimpleBroadphase is a brute force aabb culling broadphase based on O(n^2) aabb checks
class btSimpleBroadphase : public btOverlappingPairCache
{

	btSimpleBroadphaseProxy*	m_proxies;
	int*				m_freeProxies;
	int				m_firstFreeProxy;

	btSimpleBroadphaseProxy** m_pProxies;
	int				m_numProxies;

	

	int m_maxProxies;
	
	
	inline btSimpleBroadphaseProxy*	GetSimpleProxyFromProxy(btBroadphaseProxy* proxy)
	{
		btSimpleBroadphaseProxy* proxy0 = static_cast<btSimpleBroadphaseProxy*>(proxy);
		return proxy0;
	}


	void	validate();

protected:


	virtual void	RefreshOverlappingPairs();
public:
	btSimpleBroadphase(int maxProxies=16384);
	virtual ~btSimpleBroadphase();


		static bool	AabbOverlap(btSimpleBroadphaseProxy* proxy0,btSimpleBroadphaseProxy* proxy1);


	virtual btBroadphaseProxy*	CreateProxy(  const btSimdVector3& min,  const btSimdVector3& max,int shapeType,void* userPtr ,short int collisionFilterGroup,short int collisionFilterMask);


	virtual void	DestroyProxy(btBroadphaseProxy* proxy);
	virtual void	SetAabb(btBroadphaseProxy* proxy,const btSimdVector3& aabbMin,const btSimdVector3& aabbMax);
		
	
	



};



#endif //SIMPLE_BROADPHASE_H

