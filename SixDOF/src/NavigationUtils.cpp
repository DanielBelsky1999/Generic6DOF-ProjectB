#include "NavigationUtils.h"


Vector3D NavigationUtils::LLH_to_ECEF(const Vector3D& llh_ddm)
{
    Vector3D llh = Vector3D(llh_ddm[0] * DEG2RAD, llh_ddm[1] * DEG2RAD, llh_ddm[2]);
    const double lat = llh[0];   // radians
    const double lon = llh[1];   // radians
    const double h = llh[2];   // meters

    const double sinLat = sin(lat);
    const double cosLat = cos(lat);
    const double sinLon = sin(lon);
    const double cosLon = cos(lon);

    // Radius of curvature in prime vertical
    const double N = WGS84::a / sqrt(1.0 - WGS84::e2 * sinLat * sinLat);

    double x = (N + h) * cosLat * cosLon;
    double y = (N + h) * cosLat * sinLon;
    double z = (N * (1.0 - WGS84::e2) + h) * sinLat;

    return Vector3D(x, y, z);
}

Vector3D NavigationUtils::ECEF_to_LLH(const Vector3D& ecef)
{
    const double x = ecef[0];
    const double y = ecef[1];
    const double z = ecef[2];

    const double lon = atan2(y, x);

    const double p = sqrt(x * x + y * y);

    // Initial latitude guess
    double lat = atan2(z, p * (1.0 - WGS84::e2));
    double h = 0.0;

    for (int i = 0; i < 5; ++i)
    {
        const double sinLat = sin(lat);

        const double N = WGS84::a / sqrt(1.0 - WGS84::e2 * sinLat * sinLat);

        h = p / cos(lat) - N;

        lat = atan2(z, p * (1.0 - WGS84::e2 * (N / (N + h))));
    }

    return Vector3D(lat, lon, h);
}

Quaternion NavigationUtils::EulerwrtNED_to_qeb(const EulerAngles& euler, const Vector3D& llh_ddm)
{
    Vector3D llh = Vector3D(llh_ddm[0] * DEG2RAD, llh_ddm[1] * DEG2RAD, llh_ddm[2]);
    Quaternion qnb = QuaternionFromEuler(euler);
    Quaternion qen = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
    Quaternion qeb = qen * qnb;
    return qeb;
}

Vector3D NavigationUtils::BodyVelwrtNED_to_ECEF(const EulerAngles& euler, const Vector3D& llh_ddm, const Vector3D& velCGwrtNED_body)
{
    Quaternion qeb = NavigationUtils::EulerwrtNED_to_qeb(euler, llh_ddm);
    return ImaginaryFromQuaternion(qeb * velCGwrtNED_body * qeb.Conjugate());
}

double NavigationUtils::RN(const Vector3D& llh_ddm)
{
    double phi = llh_ddm[0] * DEG2RAD;

    double s = sin(phi);
    double denom = sqrt(1.0 - WGS84::e2 * s * s);

    return WGS84::a / denom;
}

double NavigationUtils::RM(const Vector3D& llh_ddm)
{
    double phi = llh_ddm[0] * DEG2RAD;

    double s = sin(phi);
    double denom = pow(1.0 - WGS84::e2 * s * s, 1.5);

    return  WGS84::a * (1.0 - WGS84::e2) / denom;
}

Vector3D NavigationUtils::W_NB_B_to_W_IB_B(const Vector3D& W_IE_E, const Vector3D& w_nb_b, const EulerAngles& euler, const Vector3D& llh_ddm, const Vector3D& velCGwrtNED_body)
{

    Vector3D llh = Vector3D(llh_ddm[0] * DEG2RAD, llh_ddm[1] * DEG2RAD, llh_ddm[2]);

    Quaternion qnb = QuaternionFromEuler(euler);
    Vector3D velocity_inNED = ImaginaryFromQuaternion(qnb * velCGwrtNED_body * qnb.Conjugate());
    double phi_dot = velocity_inNED[0] / (RM(llh_ddm) + llh[2]);
    double lambda_dot = velocity_inNED[1] / ((RN(llh_ddm) + llh[2])*cos(llh[0]));
    Vector3D w_en_n(lambda_dot * cos(llh[0]), -phi_dot, -lambda_dot * sin(llh[0]));

    Vector3D w_en_b = ImaginaryFromQuaternion(qnb.Conjugate() * w_en_n * qnb);
    Quaternion qeb = EulerwrtNED_to_qeb(euler, llh_ddm);
    Vector3D w_ie_b = ImaginaryFromQuaternion(qeb.Conjugate() * W_IE_E * qeb);

    Vector3D w_ib_b = w_nb_b + w_en_b + w_ie_b;
    return w_ib_b;
}

Vector3D NavigationUtils::W_IB_B_to_W_NB_B(const Vector3D& W_IE_E, const Vector3D& w_ib_b, const EulerAngles& euler, const Vector3D& llh, const Vector3D& velCGwrtNED_body)
{
    
    Vector3D llh_ddm = Vector3D(llh[0] * RAD2DEG, llh[1] * RAD2DEG, llh[2]);
    
    Quaternion qnb = QuaternionFromEuler(euler);
    Vector3D velocity_inNED = ImaginaryFromQuaternion(qnb * velCGwrtNED_body * qnb.Conjugate());
    double phi_dot = velocity_inNED[0] / (RM(llh_ddm) + llh[2]);
    double lambda_dot = velocity_inNED[1] / ((RN(llh_ddm) + llh[2]) * cos(llh[0]));
    Vector3D w_en_n(lambda_dot * cos(llh[0]), -phi_dot, -lambda_dot * sin(llh[0]));
    Vector3D w_en_b = ImaginaryFromQuaternion(qnb.Conjugate() * w_en_n * qnb);
    
    Quaternion qeb = EulerwrtNED_to_qeb(euler, llh_ddm);
    Vector3D w_ie_b = ImaginaryFromQuaternion(qeb.Conjugate() * W_IE_E * qeb);
    
    Vector3D w_nb_b = w_ib_b - w_en_b - w_ie_b;
    
    return w_nb_b;
}

EulerAngles NavigationUtils::qeb_to_EulerwrtNED(const Quaternion& qeb, const Vector3D& ecef)
{
    Vector3D llh = ECEF_to_LLH(ecef);
    Quaternion qen = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
    Quaternion qnb = qen.Conjugate() * qeb;

    return EulerFromQuaternions(qnb);

}

Vector3D NavigationUtils::ECEF_to_NED(const Vector3D& v_ECEF, const Vector3D& ecef_position)
{
    Vector3D llh = ECEF_to_LLH(ecef_position);
    Quaternion qen = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
    Vector3D v_NED = ImaginaryFromQuaternion(qen.Conjugate() * v_ECEF * qen);
    return v_NED;
}

Vector3D NavigationUtils::XYZ_to_LLH(const Vector3D& XYZ, const Vector3D& origin_llh)
{
    Quaternion qen = QuaternionFromEuler(EulerAngles(origin_llh[1], -(origin_llh[0] + PI / 2), 0));
    Vector3D origin_ecef = LLH_to_ECEF(Vector3D(origin_llh[0] * RAD2DEG, origin_llh[1] * RAD2DEG, origin_llh[2]));
    Vector3D v_ECEF = ImaginaryFromQuaternion(qen * XYZ * qen.Conjugate());
    Vector3D llh = ECEF_to_LLH(origin_ecef + v_ECEF);
    return llh;
}


