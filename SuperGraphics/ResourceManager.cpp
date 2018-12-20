#include "ResourceManager.h"

unordered_map<string, Shader*> ResourceManager::shaders;
unordered_map<string, Texture*> ResourceManager::textures;

void ResourceManager::initializeShaders()
{
    shaders["programShader"] = new Shader("shaders/VertexShader.vertexshader", "shaders/FragmentShader.fragmentshader");
    shaders["cubemapShader"] = new Shader("shaders/cubemap.vertexshader", "shaders/cubemap.fragmentshader");
    shaders["skyboxShader"] = new Shader("shaders/skybox.vertexshader", "shaders/skybox.fragmentshader");
}

void ResourceManager::initializeTextures()
{
    textures["cat"] = new Texture("Assets/cat.png", 0);
	textures["coin"] = new Texture("Assets/coin.png", 0);

	textures["hero"] = new Texture("Assets/alien/alien_front.png",0);

	textures["spaceship"] = new Texture("Assets/spaceship.png", 0);

    textures["box"] = new Texture(vector<string> {
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg"
    }, 0);

	textures["box1"] = new Texture(vector<string> {
		"Assets/box/box2.jpg",
			"Assets/box/box2.jpg",
			"Assets/box/box2.jpg",
			"Assets/box/box2.jpg",
			"Assets/box/box2.jpg",
			"Assets/box/box2.jpg"
	}, 0);
    textures["skybox"] = new Texture(vector<string> {
        "Assets/skybox/skybox_right.jpg",
        "Assets/skybox/skybox_left.jpg",
        "Assets/skybox/skybox_up.jpg",
        "Assets/skybox/skybox_down.jpg",
        "Assets/skybox/skybox_back.jpg",
        "Assets/skybox/skybox_front.jpg"
	}, 0);

	textures["brownBlock"] = new Texture(vector<string> {
		"Assets/box/brownBlock.jpg",
		"Assets/box/brownBlock.jpg",
		"Assets/box/brownBlock.jpg",
		"Assets/box/brownBlock.jpg",
		"Assets/box/brownBlock.jpg",
		"Assets/box/brownBlock.jpg"
	}, 0);

	
}

void ResourceManager::initializeResources()
{
    initializeShaders();
    initializeTextures();
}

Shader * ResourceManager::getShader(string shaderName)
{
    return shaders[shaderName];
}

Texture * ResourceManager::getTexture(string textureName)
{
    return ResourceManager::textures[textureName];
}

void ResourceManager::bindCamera(FPCamera * activeCamera, glm::vec3 heroPositon)
{
    //glm::vec3 cameraPosition = glm::vec3(heroPositon.x - 5.f, heroPositon.y + 1.5, -0.5f);
    //activeCamera->setPosition(cameraPosition);

    for (auto &shader : shaders) {
        shader.second->setMat4("ProjectionMatrix", &activeCamera->GetProjectionMatrix()[0][0]);
        shader.second->setMat4("ViewMatrix", &activeCamera->GetViewMatrix()[0][0]);

        shader.second->setVec3("cameraPos", &activeCamera->getPosition()[0]);
        shader.second->setVec3("lightPos", &activeCamera->getPosition()[0]);
    }
}

Shader * ResourceManager::getAppropriateShader(Texture * texture)
{
    if (texture && texture->textureType == GL_TEXTURE_CUBE_MAP) {
        return ResourceManager::getShader("cubemapShader");
    } else {
        return ResourceManager::getShader("programShader");
    }
}

ResourceManager::~ResourceManager()
{
    for (auto &shader : shaders) {
        delete shader.second;
    }
    for (auto &texture : textures) {
        delete texture.second;
    }
}
