#include "Camera.h"

using namespace Eigen;

Camera::Camera()
{
	LookAt(Vector3f(0,0, -10.0f), Vector3f(0,0,0), Vector3f(0,1,0));
	SetPerspective(90.0f, 1.0f, 0.1f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::LookAt(const Eigen::Vector3f & position, const Eigen::Vector3f & target, const Eigen::Vector3f & up)
{
	Matrix3f R;
	R.col(2) = (position - target).normalized();
	R.col(0) = up.cross(R.col(2)).normalized();
	R.col(1) = R.col(2).cross(R.col(0));
	m_MatView.topLeftCorner<3, 3>() = R.transpose();
	m_MatView.topRightCorner<3, 1>() = -R.transpose() * position;
	m_MatView(3, 3) = 1.0f;
}

void Camera::SetPerspective(float fovY, float aspect, float near, float far)
{
	float theta = fovY * 0.5f;
	float range = far - near;
	float invtan = (float)(1. / tan(theta));

	m_MatProjection(0, 0) = invtan / aspect;
	m_MatProjection(1, 1) = invtan;
	m_MatProjection(2, 2) = -(near + far) / range;
	m_MatProjection(3, 2) = -1;
	m_MatProjection(2, 3) = -2 * near * far / range;
	m_MatProjection(3, 3) = 0;
}
