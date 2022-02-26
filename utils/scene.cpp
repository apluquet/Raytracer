/**
 * @file scene.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Scene class methods.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/scene.h"

void Scene::addObject(Object *object) { objects.push_back(object); }
void Scene::addLight(Light light) { lights.push_back(light); }

// void Scene::deleteObject(Object object) { objects.remove(object); }
// void Scene::deleteLight(Light light) { lights.remove(light); }
