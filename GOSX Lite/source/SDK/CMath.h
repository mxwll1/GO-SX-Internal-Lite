//
//  Math.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include "Engine/common.h"

#include "SDK.h"
#include <math.h>
#include <cmath>

#define M_RADPI 57.295779513082f
#define M_PI_F  ((float)(M_PI))

#define SQUARE(a) a * a
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#define RAD2DEG(x)  ((float)(x) * (float)(180.f/M_PI_F))

enum
{
    PITCH = 0,	// up / down
    YAW,		// left / right
    ROLL		// fall over
};

class CMath
{
public:
    
    CMath();
    
    static void inline SinCos(float radians, float *sine, float *cosine);
    static void AngleVectors(const QAngle &angles, Vector *forward);
    static void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up);
    static void AngleVectors(const QAngle &angles, Vector& forward);
    static float DotProduct(Vector &v1, float* v2);
    static float Dot(const Vector &v1, Vector &v2);
    static void VectorTransform(Vector &in1, matrix3x4_t& in2, Vector &out);
    static float VecLength(Vector& vec);
    static float VecDist(const Vector& fVec1, Vector fVec2);
    static float GetFov(QAngle viewAngle, Vector playerHeadPosition, Vector entityHeadPosition);
    static float GetDistanceFov(QAngle viewAngle, Vector playerHeadPosition, Vector entityHeadPosition);
    static QAngle CalcAngle(Vector PlayerPos, Vector EnemyPos);
    static void VectorAngles( const Vector& dir, QAngle &angles );
    static void ClampAngle( QAngle& angles);
    static void NormalizeAngles(QAngle& angle);
    static void VectorNormalize( Vector& v);
    static void SmoothAngle(const QAngle& ViewAngle, QAngle& DestAngles, float smooth);
    static void MakeVector(Vector angle, Vector& vector);
    static Vector AngleToDirection( QAngle angle);
    static void VectorITransform( Vector& in1, const matrix3x4_t& in2, Vector& out);
    static void VectorIRotate( Vector& in1, const matrix3x4_t& in2, Vector& out);
    static Vector ExtrapolateTick(Vector p0, Vector v0);
    static void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
};

#endif /* Math_h */
