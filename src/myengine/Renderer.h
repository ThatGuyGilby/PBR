#include "Component.h"

#include <rend/rend.h>

#include <memory>

namespace myengine
{

struct Model;
struct ShaderMaterial;
struct ShaderLight;

struct Renderer : public Component
{
  void onInitialize();
  void onRender();

  void shaderSetAll();

  void setShaderMaterial(ShaderMaterial _material);
  void setShaderLight(ShaderLight _light);

  void setModel(std::shared_ptr<Model> model);
  bool CheckShaderCompiled(GLint shader);
  //void setShader(std::shared_ptr<Shader> shader);

private:
  std::shared_ptr<rend::Shader> shader;
  std::shared_ptr<Model> model;

};

struct ShaderMaterial
{
	rend::vec3 ambient;
	rend::vec3 diffuse;
	rend::vec3 specular;

	float shininess;

	ShaderMaterial()
	{
		ambient = rend::vec3(0, 0, 0);
		diffuse = rend::vec3(0.55f, 0.55f, 0.55f);
		specular = rend::vec3(0.7f, 0.7f, 0.7f);

		shininess = 32.0f;
	}

	ShaderMaterial(rend::vec3 _ambient, rend::vec3 _diffuse, rend::vec3 _specular, float _shininess)
	{
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;

		shininess = _shininess;
	}

	void emerald()
	{
		ambient = rend::vec3(0.0215f, 0.1745f, 0.0215f);
		diffuse = rend::vec3(0.07568f, 0.61424f, 0.07568f);
		specular = rend::vec3(0.633f, 0.727811f, 0.633);
		shininess = 32.0f;
	};
};

struct ShaderLight
{
	rend::vec3 colour;

	rend::vec3 ambient;
	rend::vec3 diffuse;
	rend::vec3 specular;

	ShaderLight()
	{
		colour = rend::vec3(1, 1, 1);

		diffuse = colour * rend::vec3(0.5f);
		ambient = diffuse * rend::vec3(0.2f);
		specular = rend::vec3(1.0f, 1.0f, 1.0f);
	}
	
	ShaderLight(rend::vec3 _colour, rend::vec3 _specular)
	{
		colour = _colour;

		diffuse = colour * rend::vec3(0.5f);
		ambient = diffuse * rend::vec3(0.2f);
		specular = _specular;
	}
	
	ShaderLight(rend::vec3 _colour, rend::vec3 _diffuse, rend::vec3 _ambient, rend::vec3 _specular)
	{
		colour = _colour;

		diffuse = _diffuse;
		ambient = _ambient;
		specular = _specular;
	}
};
}
