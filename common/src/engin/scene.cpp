#include "engin/scene.hpp"

string Scene::GetName(){
    return name;
}

void Scene::Update() {
    step();
}

string Scene::GetImageLoadFilename(){
    return image_load_filename;
}

Scene::~Scene(){}