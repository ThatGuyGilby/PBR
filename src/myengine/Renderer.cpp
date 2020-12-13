#include "Renderer.h"
#include "Core.h"
#include "Transform.h"
#include "Entity.h"
#include "Exception.h"
#include "Camera.h"
#include "Model.h"

#include <fstream>
#include <string>
#include <iostream>

namespace myengine
{

void Renderer::onInitialize()
{
	const char* src =
	"\n#ifdef VERTEX\n                       " \
	"attribute vec3 a_Position;              " \
	"attribute vec2 a_TexCoord;              " \
	"attribute vec3 a_Normal;                " \
	"uniform mat4 u_Projection;              " \
	"uniform mat4 u_View;                    " \
	"uniform mat4 u_Model;                   " \
	"varying vec2 v_TexCoord;                " \
	"                                        " \
	"void main()                             " \
	"{                                       " \
	"  gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1); " \
	"  v_TexCoord = a_TexCoord;              " \
	"  if(a_Normal.x == 9) gl_Position.x = 7;" \
	"}                                       " \
	"                                        " \
	"\n#endif\n                              " \
	"\n#ifdef FRAGMENT\n                     " \
	"uniform sampler2D u_Texture;            " \
	"varying vec2 v_TexCoord;                " \
	"                                        " \
	"void main()                             " \
	"{                                       " \
	"  gl_FragColor = vec4(v_TexCoord, 0, 1);" \
	"}                                       " \
	"                                        " \
	"\n#endif\n                              ";

	shader = getCore()->context->createShader();
	//shader->parse(src);

	shader->parse(
		"D:/Users/Jack/Documents/GitHub/karsten/shaders/VertShader.glshader",
		"D:/Users/Jack/Documents/GitHub/karsten/shaders/FragShader.glshader"
	);
}

void Renderer::onRender()
{
  if(!model) return;

  shaderSetAll();

  std::shared_ptr<Camera> c = getCore()->getCamera();

  // iterate model parts
  //   set shader texture = part->texture
  //   render

  if(c->getRenderTexture())
  {
    shader->render(c->getRenderTexture());
  }
  else
  {
    shader->render();
  }
}

void Renderer::shaderSetAll()
{
	shader->setMesh(model->mesh);

	shader->setUniform("u_Projection", rend::perspective(rend::radians(45.0f),
		1.0f, 0.1f, 100.0f));

	shader->setUniform("u_View", getCore()->getCamera()->getView());
	shader->setUniform("u_Model", getEntity()->getTransform()->getModel());

	shader->setUniform("objectColor", rend::vec3(1.0f, 1.0f, 1.0f));

	rend::vec3 lightPos(1.2f, 1.0f, 2.0f);
	shader->setUniform("lightPos", lightPos);

	shader->setUniform("viewPos", getEntity()->getCore()->getCamera()->getTransform()->position);

	ShaderMaterial testMaterial;
	setShaderMaterial(testMaterial);

	ShaderLight testLight;
	setShaderLight(testLight);

	//shader->setSampler("u_Texture", texture->internal);
}

void Renderer::setShaderMaterial(ShaderMaterial _material)
{
	shader->setUniform("material.ambient", _material.ambient);
	shader->setUniform("material.diffuse", _material.diffuse);
	shader->setUniform("material.specular", _material.specular);
	shader->setUniform("material.shininess", _material.shininess);
}

void Renderer::setShaderLight(ShaderLight _light)
{
	shader->setUniform("light.ambient", _light.ambient);
	shader->setUniform("light.diffuse", _light.diffuse);
	shader->setUniform("light.specular", _light.specular);
}

void Renderer::setModel(std::shared_ptr<Model> model)
{
  this->model = model;
}
}