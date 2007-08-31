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

/*
	Draft high-level generic physics C-API. For low-level access, use the physics SDK native API's.
	Work in progress, functionality will be added on demand.

	If possible, use the richer Bullet C++ API, by including "btBulletDynamicsCommon.h"
*/

#ifndef BULLET_C_API_H
#define BULLET_C_API_H

#define PL_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

#ifdef BT_USE_DOUBLE_PRECISION
typedef double	plReal;
#else
typedef float	plReal;
#endif

typedef plReal	plVector3[3];
typedef plReal	plQuaternion[4];

#ifdef __cplusplus
extern "C" { 
#endif

/*	Particular physics SDK */
	PL_DECLARE_HANDLE(plPhysicsSdkHandle);
/* 	Dynamics world, belonging to some physics SDK */
	PL_DECLARE_HANDLE(plDynamicsWorldHandle);
/* Rigid Body that can be part of a Dynamics World */	
	PL_DECLARE_HANDLE(plRigidBodyHandle);
/* 	Collision Shape/Geometry, property of a Rigid Body */
	PL_DECLARE_HANDLE(plCollisionShapeHandle);
/* Constraint for Rigid Bodies */
	PL_DECLARE_HANDLE(plConstraintHandle);
/* Triangle Mesh interface */
	PL_DECLARE_HANDLE(plMeshInterfaceHandle);

/*
	Create and Delete a Physics SDK	
*/

	extern	plPhysicsSdkHandle	plNewBulletSdk(); //this could be also another sdk, like ODE, PhysX etc.
	extern	void		plDeletePhysicsSdk(plPhysicsSdkHandle	physicsSdk);

/* Dynamics World */

	extern  plDynamicsWorldHandle plCreateDynamicsWorld(plPhysicsSdkHandle physicsSdk);

	extern  void           plDeleteDynamicsWorld(plDynamicsWorldHandle world);

	extern	void	plStepSimulation(plDynamicsWorldHandle,	plReal	timeStep);

	extern  void plAddRigidBody(plDynamicsWorldHandle world, plRigidBodyHandle object);

	extern  void plRemoveRigidBody(plDynamicsWorldHandle world, plRigidBodyHandle object);


/* Rigid Body  */

	extern  plRigidBodyHandle plCreateRigidBody(	void* user_data,  float mass, plCollisionShapeHandle cshape );

	extern  void plDeleteRigidBody(plRigidBodyHandle body);


/* Collision Shape definition */

	extern  plCollisionShapeHandle plNewSphereShape(plReal radius);
	extern  plCollisionShapeHandle plNewBoxShape(plReal x, plReal y, plReal z);
	extern  plCollisionShapeHandle plNewCapsuleShape(plReal radius, plReal height);	
	extern  plCollisionShapeHandle plNewConeShape(plReal radius, plReal height);
	extern  plCollisionShapeHandle plNewCylinderShape(plReal radius, plReal height);
	extern	plCollisionShapeHandle plNewCompoundShape();
	extern	void	plAddChildShape(plCollisionShapeHandle compoundShape,plCollisionShapeHandle childShape, plVector3 childPos,plQuaternion childOrn);

	extern  void plDeleteShape(plCollisionShapeHandle shape);

	/* Convex Meshes */
	extern  plCollisionShapeHandle plNewConvexHullShape();
	extern  void		plAddVertex(plCollisionShapeHandle convexHull, plReal x,plReal y,plReal z);
/* Concave static triangle meshes */
	extern  plMeshInterfaceHandle		   plNewMeshInterface();
	extern  void		plAddTriangle(plMeshInterfaceHandle meshHandle, plVector3 v0,plVector3 v1,plVector3 v2);
	extern  plCollisionShapeHandle plNewStaticTriangleMeshShape(plMeshInterfaceHandle);

	extern  void plSetScaling(plCollisionShapeHandle shape, plVector3 scaling);

/* SOLID has Response Callback/Table/Management */
/* PhysX has Triggers, User Callbacks and filtering */
/* ODE has the typedef void dNearCallback (void *data, dGeomID o1, dGeomID o2); */

/*	typedef void plUpdatedPositionCallback(void* userData, plRigidBodyHandle	rbHandle, plVector3 pos); */
/*	typedef void plUpdatedOrientationCallback(void* userData, plRigidBodyHandle	rbHandle, plQuaternion orientation); */

	/* get world transform */
	extern void	plGetOpenGLMatrix(plRigidBodyHandle object, plReal* matrix);
	extern void	plGetPosition(plRigidBodyHandle object,plVector3 position);
	extern void plGetOrientation(plRigidBodyHandle object,plQuaternion orientation);

	/* set world transform (position/orientation) */
	extern  void plSetPosition(plRigidBodyHandle object, const plVector3 position);
	extern  void plSetOrientation(plRigidBodyHandle object, const plQuaternion orientation);
	extern	void plSetEuler(plReal yaw,plReal pitch,plReal roll, plQuaternion orient);

	typedef struct plRayCastResult {
		plRigidBodyHandle		m_body;  
		plCollisionShapeHandle	m_shape; 		
		plVector3				m_positionWorld; 		
		plVector3				m_normalWorld;
	} plRayCastResult;

	extern  int plRayCast(plDynamicsWorldHandle world, const plVector3 rayStart, const plVector3 rayEnd, plRayCastResult res);

	/* Sweep API */

	/* extern  plRigidBodyHandle plObjectCast(plDynamicsWorldHandle world, const plVector3 rayStart, const plVector3 rayEnd, plVector3 hitpoint, plVector3 normal); */

	/* Continuous Collision Detection API */

#ifdef __cplusplus
}
#endif

#endif //BULLET_C_API_H

