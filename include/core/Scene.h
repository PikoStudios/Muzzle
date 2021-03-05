#pragma once

typedef void Scene;

void LoadScene(Scene (*func)())
{
    func();
}

