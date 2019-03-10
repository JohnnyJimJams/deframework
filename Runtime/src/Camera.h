#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <Eigen/Dense>

class Camera
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Camera();
	~Camera();
	Eigen::Matrix4f &GetViewMatrix() { return m_MatView; }
	Eigen::Matrix4f &GetProjectionMatrix() { return m_MatProjection; }
	void LookAt(const Eigen::Vector3f & position, const Eigen::Vector3f & target, const Eigen::Vector3f & up);
	void SetPerspective(float fovY, float aspect, float near, float far);
private:
	Eigen::Matrix4f m_MatView;
	Eigen::Matrix4f m_MatProjection;
};

#endif // __CAMERA_H_