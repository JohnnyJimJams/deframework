#include "EMesh.h"

EMesh::EMesh()
{
	m_mesh = new Mesh();
}

EMesh::~EMesh()
{
	delete m_mesh;
}
