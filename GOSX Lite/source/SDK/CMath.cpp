//
//  Math.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "CMath.h"

void CMath::SinCos(float radians, float *sine, float *cosine) {
    *sine = sin(radians);
    *cosine = cos(radians);
}

void CMath::AngleVectors(const QAngle &angles, Vector *forward) {
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[0]), &sy, &cy);
    SinCos(DEG2RAD(angles[1]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    if( forward ) {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }
}

void CMath::AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up) {
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[0]), &sy, &cy);
    SinCos(DEG2RAD(angles[1]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    if (forward) {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }
    
    if (right) {
        right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
        right->y = (-1 * sr * sp * sy + -1 * cr * cy);
        right->z = -1 * sr * cp;
    }
    
    if (up) {
        up->x = (cr * sp * cy + -sr * -sy);
        up->y = (cr * sp * sy + -sr * cy);
        up->z = cr * cp;
    }
}

float CMath::DotProduct(Vector &v1, float* v2) {
    return v1.x*v2[0] + v1.y*v2[1] + v1.z*v2[2];
}

float CMath::Dot(const Vector &v1, Vector &v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void CMath::VectorTransform(Vector &in1, matrix3x4_t &in2, Vector &out) {
    out.x = CMath::DotProduct(in1, in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
    out.y = CMath::DotProduct(in1, in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
    out.z = CMath::DotProduct(in1, in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

float CMath::VecLength(Vector& vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

float CMath::VecDist(const Vector& fVec1, Vector fVec2) {
    return sqrt(pow(fVec1.x - fVec2.x, 2) + pow(fVec1.y - fVec2.y, 2) + pow(fVec1.z - fVec2.z, 2));
}

float CMath::GetFov(QAngle viewAngle, Vector playerHeadPosition, Vector entityHeadPosition) {
    Vector ang, aim;

    AngleVectors(viewAngle, &aim);
    QAngle newAngles = CalcAngle(playerHeadPosition, entityHeadPosition);
    AngleVectors(newAngles, &ang);

    return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

float CMath::GetDistanceFov(QAngle viewAngle, Vector playerHeadPosition, Vector entityHeadPosition)
{
    float distance = VecDist(playerHeadPosition, entityHeadPosition);
    Vector aimingAt;
    AngleVectors(viewAngle, &aimingAt);
    aimingAt *= distance;

    QAngle newAngles = CalcAngle(playerHeadPosition, entityHeadPosition);
    Vector aimAt;
    AngleVectors(newAngles, &aimAt);
    aimAt *= distance;

    return VecDist(aimAt, aimingAt);
}

QAngle CMath::CalcAngle(Vector PlayerPos, Vector EnemyPos) {
    QAngle AimAngles;
    Vector delta = PlayerPos - EnemyPos;
    float hyp = sqrt((delta.x * delta.x) + (delta.y * delta.y));
    AimAngles.x = atanf(delta.z / hyp) * M_RADPI;
    AimAngles.y = atanf(delta.y / delta.x) * M_RADPI;
    if (delta.x >= 0.0) {
        AimAngles.y += 180.0f;
    }
    
    AimAngles.z = 0.f;
    return AimAngles;
}

void CMath::VectorAngles( const Vector& dir, QAngle &angles ) {
    float hyp = sqrt((dir.x * dir.x) + (dir.y * dir.y) );
    angles.x = atanf(dir.z / hyp) * M_RADPI;
    angles.y = atanf(dir.y / dir.x) * M_RADPI;
    if (dir.x >= 0.0) {
        angles.y += 180.0f;
    }

    angles.z = 0.f;
}

void CMath::VectorNormalize( Vector& v ) {
    float l = VecLength( v );
    if ( l != 0.0f ) {
        v /= l;
    } else {
        v.x = v.y = 0.0f; v.z = 1.0f;
    }
}

void CMath::SmoothAngle(const QAngle& ViewAngle, QAngle& DestAngles, float smooth) {
    QAngle vecDelta = ViewAngle - DestAngles;
    ClampAngle(vecDelta);
    DestAngles = ViewAngle - vecDelta / 100.0f * smooth; // 50.0f is ur smooth value
}

void CMath::MakeVector(Vector angle, Vector& vector) {
    float pitch = float(angle[0] * M_PI / 180);
    float yaw = float(angle[1] * M_PI / 180 );
    float tmp = float(cos(pitch));
    vector[0] = float(-tmp * -cos(yaw));
    vector[1] = float(sin(yaw) * tmp);
    vector[2] = float(-sin(pitch));
}

Vector CMath::AngleToDirection(QAngle angle) {
    angle.x = (float)DEG2RAD(angle.x);
    angle.y = (float)DEG2RAD(angle.y);
    angle.z = 0.f;
    
    float sinYaw = sin(angle.y);
    float cosYaw = cos(angle.y);
    
    float sinPitch = sin(angle.x);
    float cosPitch = cos(angle.x);
    
    Vector direction;
    direction.x = cosPitch * cosYaw;
    direction.y = cosPitch * sinYaw;
    direction.z = -sinPitch;
    
    return direction;
}

void CMath::VectorITransform(Vector& in1, const matrix3x4_t& in2, Vector& out)
{
    float in1t[3];
    
    in1t[0] = in1.x - in2.m_flMatVal[0][3];
    in1t[1] = in1.y - in2.m_flMatVal[1][3];
    in1t[2] = in1.z - in2.m_flMatVal[2][3];
    
    out.x = in1t[0] * in2.m_flMatVal[0][0] + in1t[1] * in2.m_flMatVal[1][0] + in1t[2] * in2.m_flMatVal[2][0];
    out.y = in1t[0] * in2.m_flMatVal[0][1] + in1t[1] * in2.m_flMatVal[1][1] + in1t[2] * in2.m_flMatVal[2][1];
    out.z = in1t[0] * in2.m_flMatVal[0][2] + in1t[1] * in2.m_flMatVal[1][2] + in1t[2] * in2.m_flMatVal[2][2];
}

void CMath::VectorIRotate( Vector& in1, const matrix3x4_t& in2, Vector& out )
{
    out.x = in1.x*in2.m_flMatVal[0][0] + in1.y*in2.m_flMatVal[1][0] + in1.z*in2.m_flMatVal[2][0];
    out.y = in1.x*in2.m_flMatVal[0][1] + in1.y*in2.m_flMatVal[1][1] + in1.z*in2.m_flMatVal[2][1];
    out.z = in1.x*in2.m_flMatVal[0][2] + in1.y*in2.m_flMatVal[1][2] + in1.z*in2.m_flMatVal[2][2];
}

Vector CMath::ExtrapolateTick(Vector position, Vector velocity)
{
    position.x += velocity.x * (Interfaces::GlobalVars()->interval_per_tick * 1.2f);
    position.y += velocity.y * (Interfaces::GlobalVars()->interval_per_tick * 1.2f);

    return position;
}

void CMath::ClampAngle( QAngle& angles )
{
    if (angles.x < -89.0f) {
        angles.x = -89.0f;
    }

    if (angles.x >  89.0f) {
        angles.x = 89.0f;
    }

    while (angles.y < -180.0f) {
        angles.y += 360.0f;
    }

    while (angles.y >  180.0f) {
        angles.y -= 360.0f;
    }

    angles.z = 0.0f;
}

void CMath::NormalizeAngles(QAngle& angle)
{
    while (angle.x > 89.0f) {
        angle.x -= 180.f;
    }

    while (angle.x < -89.0f) {
        angle.x += 180.f;
    }

    while (angle.y > 180.f) {
        angle.y -= 360.f;
    }

    while (angle.y < -180.f) {
        angle.y += 360.f;
    }
}

void CMath::CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
    float deltaView;
    float f1;
    float f2;

    if (vOldAngles.y < 0.f) {
        f1 = 360.0f + vOldAngles.y;
    } else {
        f1 = vOldAngles.y;
    }

    if (pCmd->viewangles.y < 0.0f) {
        f2 = 360.0f + pCmd->viewangles.y;
    } else {
        f2 = pCmd->viewangles.y;
    }

    if (f2 < f1) {
        deltaView = std::abs(f2 - f1);
    } else {
        deltaView = 360.0f - std::abs(f1 - f2);
    }

    deltaView = 360.0f - deltaView;

    pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}
