#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <map>

class ShaderProgram
{
public:

	ShaderProgram();
	virtual ~ShaderProgram();

	void	bind();
	void	unBind();

	bool	isBound() const	{	return m_bound;	}

	void	compileFromFile(unsigned int a_type, const char* a_filename);
	void	compileFromString(unsigned int a_type, const char* a_shader);
	void	compileFromStrings(unsigned int a_type, unsigned int a_stringCount, const char** a_shaderStrings);

	bool	linkProgram();

	int		getUniform(const char* a_uniform);

	unsigned int	getProgram() const					{	return m_program;			}
	unsigned int	getShader(unsigned int a_type)		{	return m_shaders[a_type];	}

	static ShaderProgram*	getCurrentBoundProgram()	{	return sm_boundProgram;		}

protected:

	bool			m_bound;
	unsigned int	m_program;

	std::map<unsigned int,unsigned int>	m_shaders;

	static ShaderProgram*	sm_boundProgram;
};

#endif // __SHADERPROGRAM_H_