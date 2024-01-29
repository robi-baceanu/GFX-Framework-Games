#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/objects2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Initialize variables and element positions
    glm::vec3 center = glm::vec3(0, 0, 0);

    for (int i = 0; i < 9; i++) {
        gridSquares[i].x = 150 + (i % 3) * 125;
        gridSquares[i].y = 100 + (i / 3) * 125;
    }

    redLine.x = 50;
    redLine.y = 225;

    for (int i = 0; i < 4; i++) {
        shopSquares[i].x = (i + 1) * 150;
        shopSquares[i].y = 600;
    }

    game.healthBar.healthPoints = 3;
    game.healthBar.x = 850;
    game.healthBar.y = 600;

    game.currency = 0;

    // Load meshes

    // Load grid and red line
    Mesh* gridSquare = objects2D::CreateSquare("gridSquare", center, SQUARE_SIDE, green);
    AddMeshToList(gridSquare);

    Mesh* redLine = objects2D::CreateRectangle("redLine", center, 3 * SQUARE_SIDE + 2 * SQUARE_GAP, REDLINE_WIDTH, red);
    AddMeshToList(redLine);

    // Load shop and health point
    Mesh* shopSquare = objects2D::CreateSquare("shopSquare", center, SQUARE_SIDE, green, false);
    AddMeshToList(shopSquare);

    Mesh* healthPoint = objects2D::CreateHeart("healthPoint", center, red);
    AddMeshToList(healthPoint);

    // Load stars
    Mesh* orangeStar = objects2D::CreateStar("orangeStar", center, STAR_RADIUS, orange);
    AddMeshToList(orangeStar);

    Mesh* blueStar = objects2D::CreateStar("blueStar", center, STAR_RADIUS, blue);
    AddMeshToList(blueStar);

    Mesh* yellowStar = objects2D::CreateStar("yellowStar", center, STAR_RADIUS, yellow);
    AddMeshToList(yellowStar);

    Mesh* purpleStar = objects2D::CreateStar("purpleStar", center, STAR_RADIUS, purple);
    AddMeshToList(purpleStar);

    Mesh* pinkStar = objects2D::CreateStar("pinkStar", center, STAR_RADIUS, pink);
    AddMeshToList(pinkStar);

    Mesh* grayStar = objects2D::CreateStar("grayStar", center, STAR_RADIUS, gray);
    AddMeshToList(grayStar);

    // Load turrets
    Mesh* orangeTurret = objects2D::CreateTurret("orangeTurret", center, TURRET_HEIGHT, orange);
    AddMeshToList(orangeTurret);

    Mesh* blueTurret = objects2D::CreateTurret("blueTurret", center, TURRET_HEIGHT, blue);
    AddMeshToList(blueTurret);

    Mesh* yellowTurret = objects2D::CreateTurret("yellowTurret", center, TURRET_HEIGHT, yellow);                                  
    AddMeshToList(yellowTurret);

    Mesh* purpleTurret = objects2D::CreateTurret("purpleTurret", center, TURRET_HEIGHT, purple);
    AddMeshToList(purpleTurret);

    // Load hexagons
    Mesh* orangeHexagon3HP = objects2D::CreateHexagon("orangeHexagon3HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, orange, green);
    AddMeshToList(orangeHexagon3HP);
    Mesh* orangeHexagon2HP = objects2D::CreateHexagon("orangeHexagon2HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, orange, yellow);
    AddMeshToList(orangeHexagon2HP);
    Mesh* orangeHexagon1HP = objects2D::CreateHexagon("orangeHexagon1HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, orange, red);
    AddMeshToList(orangeHexagon1HP);

    Mesh* blueHexagon3HP = objects2D::CreateHexagon("blueHexagon3HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, blue, green);
    AddMeshToList(blueHexagon3HP);
    Mesh* blueHexagon2HP = objects2D::CreateHexagon("blueHexagon2HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, blue, yellow);
    AddMeshToList(blueHexagon2HP);
    Mesh* blueHexagon1HP = objects2D::CreateHexagon("blueHexagon1HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, blue, red);
    AddMeshToList(blueHexagon1HP);

    Mesh* yellowHexagon3HP = objects2D::CreateHexagon("yellowHexagon3HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, yellow, green);
    AddMeshToList(yellowHexagon3HP);
    Mesh* yellowHexagon2HP = objects2D::CreateHexagon("yellowHexagon2HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, yellow, yellow);
    AddMeshToList(yellowHexagon2HP);
    Mesh* yellowHexagon1HP = objects2D::CreateHexagon("yellowHexagon1HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, yellow, red);
    AddMeshToList(yellowHexagon1HP);

    Mesh* purpleHexagon3HP = objects2D::CreateHexagon("purpleHexagon3HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, purple, green);
    AddMeshToList(purpleHexagon3HP);
    Mesh* purpleHexagon2HP = objects2D::CreateHexagon("purpleHexagon2HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, purple, yellow);
    AddMeshToList(purpleHexagon2HP);
    Mesh* purpleHexagon1HP = objects2D::CreateHexagon("purpleHexagon1HP", center, HEXAGON_OUTER_RADIUS, HEXAGON_INNER_RADIUS, purple, red);
    AddMeshToList(purpleHexagon1HP);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (game.healthBar.healthPoints == 0) {
        std::cout << R"(
               _____          __  __ ______    ______      ________ _____  
              / ____|   /\   |  \/  |  ____|  / __ \ \    / /  ____|  __ \ 
             | |  __   /  \  | \  / | |__    | |  | \ \  / /| |__  | |__) |
             | | |_ | / /\ \ | |\/| |  __|   | |  | |\ \/ / |  __| |  _  / 
             | |__| |/ ____ \| |  | | |____  | |__| | \  /  | |____| | \ \ 
              \_____/_/    \_\_|  |_|______|  \____/   \/   |______|_|  \_\
        )" << std::endl;
        exit(0);
    }

    // Create the 3x3 grid and render turrets placed on it
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(gridSquares[i].x, gridSquares[i].y);
        RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(gridSquares[i].x, gridSquares[i].y);
        modelMatrix *= transform2D::Scale(gridSquares[i].turretScale);

        if (gridSquares[i].turretType == 1) {
            RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
        } else if (gridSquares[i].turretType == 2) {
            RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
        } else if (gridSquares[i].turretType == 3) {
            RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
        } else if (gridSquares[i].turretType == 4) {
            RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
        }

        if (gridSquares[i].removeTurret) {
            if (gridSquares[i].turretScale > 0)
                gridSquares[i].turretScale -= deltaTimeSeconds;
            else {
                gridSquares[i].turretType = 0;
                gridSquares[i].removeTurret = false;
            }
        }
    }

    // Create the red line
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(redLine.x, redLine.y);
    RenderMesh2D(meshes["redLine"], shaders["VertexColor"], modelMatrix);

    // Create the shop (shop squares and prices)

    // Orange turret slot (1 star)
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[0].x, shopSquares[0].y);
    RenderMesh2D(meshes["shopSquare"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[0].x, shopSquares[0].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    // Blue turret slot (2 stars)
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[1].x, shopSquares[1].y);
    RenderMesh2D(meshes["shopSquare"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[1].x - 20, shopSquares[1].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[1].x + 20, shopSquares[1].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    // Yellow turret slot (2 stars)
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[2].x, shopSquares[2].y);
    RenderMesh2D(meshes["shopSquare"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[2].x - 20, shopSquares[2].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[2].x + 20, shopSquares[2].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    // Purple turret slot (3 stars)
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[3].x, shopSquares[3].y);
    RenderMesh2D(meshes["shopSquare"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[3].x - 35, shopSquares[3].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[3].x, shopSquares[3].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shopSquares[3].x + 35, shopSquares[3].y - 75);
    modelMatrix *= transform2D::Scale(0.5);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    // Create health bar
    for (int i = 0; i < game.healthBar.healthPoints; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(game.healthBar.x + i * 125, game.healthBar.y);
        if (i == game.healthBar.healthPoints - 1 && game.healthBar.removeHP == true) {
            if ((game.healthBar.removeAnimationTime < 0.9 && game.healthBar.removeAnimationTime > 0.75) ||
                (game.healthBar.removeAnimationTime < 0.6 && game.healthBar.removeAnimationTime > 0.45) ||
                (game.healthBar.removeAnimationTime < 0.3 && game.healthBar.removeAnimationTime > 0.15))
                RenderMesh2D(meshes["healthPoint"], shaders["VertexColor"], modelMatrix);
            game.healthBar.removeAnimationTime -= deltaTimeSeconds;
            if (game.healthBar.removeAnimationTime < 0) {
                game.healthBar.healthPoints--;
                game.healthBar.removeHP = false;
                game.healthBar.removeAnimationTime = REMOVE_HP_ANIMATION_TIME;
            }
        } else {
            RenderMesh2D(meshes["healthPoint"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Create currency pile
    for (int i = 0; i < game.currency; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(game.healthBar.x - 35 + (i % 10) * 35, game.healthBar.y - 75 - (i / 10) * 35);
        modelMatrix *= transform2D::Scale(0.5);
        RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);
    }

    // Spawn currency stars
    timeToSpawnNewStar -= deltaTimeSeconds;
    if (timeToSpawnNewStar < 0) {
        timeToSpawnNewStar = rand() % (STAR_SPAWN_INTERVAL_UPPER_BOUND - STAR_SPAWN_INTERVAL_LOWER_BOUND) + STAR_SPAWN_INTERVAL_LOWER_BOUND;
        CurrencyStar newCurrencyStar;
        newCurrencyStar.x = rand() % 900 + 300; // [300 --> 1200]
        newCurrencyStar.y = rand() % 400 + 100; // [100 --> 500]
        currencyStars.push_back(newCurrencyStar);
    }
    for (int i = 0; i < currencyStars.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(currencyStars[i].x, currencyStars[i].y);
        RenderMesh2D(meshes["pinkStar"], shaders["VertexColor"], modelMatrix);
    }

    // Spawn zombies
    timeToSpawnZombie -= deltaTimeSeconds;
    if (timeToSpawnZombie < 0) {
        timeToSpawnZombie = rand() % (ZOMBIE_SPAWN_INTERVAL_UPPER_BOUND - ZOMBIE_SPAWN_INTERVAL_LOWER_BOUND) + ZOMBIE_SPAWN_INTERVAL_LOWER_BOUND;
        Zombie newZombie;
        newZombie.y = gridSquares[0].y + (rand() % 3) * 125;
        newZombie.type = rand() % 4 + 1;
        zombies.push_back(newZombie);
    }
    for (int i = 0; i < zombies.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(zombies[i].x, zombies[i].y);
        modelMatrix *= transform2D::Scale(zombies[i].scale);

        if (zombies[i].type == 1) {
            if (zombies[i].hp == 3)
                RenderMesh2D(meshes["orangeHexagon3HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp == 2)
                RenderMesh2D(meshes["orangeHexagon2HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp <= 1)
                RenderMesh2D(meshes["orangeHexagon1HP"], shaders["VertexColor"], modelMatrix);
        }
        else if (zombies[i].type == 2) {
            if (zombies[i].hp == 3)
                RenderMesh2D(meshes["blueHexagon3HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp == 2)
                RenderMesh2D(meshes["blueHexagon2HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp <= 1)
                RenderMesh2D(meshes["blueHexagon1HP"], shaders["VertexColor"], modelMatrix);
        }
        else if (zombies[i].type == 3) {
            if (zombies[i].hp == 3)
                RenderMesh2D(meshes["yellowHexagon3HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp == 2)
                RenderMesh2D(meshes["yellowHexagon2HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp <= 1)
                RenderMesh2D(meshes["yellowHexagon1HP"], shaders["VertexColor"], modelMatrix);
        }
        else if (zombies[i].type == 4) {
            if (zombies[i].hp == 3)
                RenderMesh2D(meshes["purpleHexagon3HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp == 2)
                RenderMesh2D(meshes["purpleHexagon2HP"], shaders["VertexColor"], modelMatrix);
            else if (zombies[i].hp <= 1)
                RenderMesh2D(meshes["purpleHexagon1HP"], shaders["VertexColor"], modelMatrix);
        }

        if (zombies[i].x - redLine.x > HITBOX && zombies[i].hp > 0) {
            zombies[i].x -= MOVE_SPEED * deltaTimeSeconds;
        } else if (zombies[i].scale >= 0) {
            zombies[i].scale -= deltaTimeSeconds;
        } else {
            if (zombies[i].hp > 0) {
                game.healthBar.removeHP = true;
            }
            zombies.erase(zombies.begin() + i);
        }
    }

    // Render carrying turret
    if (carryingTurret > 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(carryingTurretX, carryingTurretY);

        if (carryingTurret == 1) {
            RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);
        }
        else if (carryingTurret == 2) {
            RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);
        }
        else if (carryingTurret == 3) {
            RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);
        }
        else if (carryingTurret == 4) {
            RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Check for turret-zombie collisions
    for (int i = 0; i < 9; i++) {
        if (gridSquares[i].turretType > 0) {
            for (int j = 0; j < zombies.size(); j++) {
                if (zombies[j].y == gridSquares[i].y && zombies[j].x - gridSquares[i].x < GRID_HITBOX && zombies[j].x - gridSquares[i].x > 0)
                    gridSquares[i].removeTurret = true;
            }
        }
    }

    // Shoot projectiles
    for (int i = 0; i < 9; i++) {
        bool zombieOnLane = false;

        if (gridSquares[i].turretType > 0) {
            for (int j = 0; j < zombies.size(); j++) {
                if (zombies[j].y == gridSquares[i].y && zombies[j].type == gridSquares[i].turretType) {
                    zombieOnLane = true;

                    if (gridSquares[i].timeToShoot < 0) {
                        ProjectileStar newProjectile;
                        newProjectile.x = gridSquares[i].x;
                        newProjectile.y = gridSquares[i].y;
                        newProjectile.type = gridSquares[i].turretType;
                        newProjectile.angularStep = 0;

                        projectiles.push_back(newProjectile);
                        gridSquares[i].timeToShoot = PROJECTILE_DELAY;
                    }
                }
            }
        }

        if (zombieOnLane)
            gridSquares[i].timeToShoot -= deltaTimeSeconds;
    }

    // Check for projectile-zombie collisions
    bool shouldBreak = false;
    for (int i = 0; i < projectiles.size(); i++) {
        for (int j = 0; j < zombies.size(); j++) {
            if (projectiles[i].type == zombies[j].type && projectiles[i].y == zombies[j].y) {
                if (zombies[j].x - projectiles[i].x < HITBOX && zombies[j].x - projectiles[i].x > 0) {
                    shouldBreak = true;
                    zombies[j].hp--;
                    projectiles.erase(projectiles.begin() + i);
                    break;
                }
            }
        }
        if (shouldBreak)
            break;
    }

    // Render projectiles
    for (int i = 0; i < projectiles.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(projectiles[i].x, projectiles[i].y);
        modelMatrix *= transform2D::Rotate(projectiles[i].angularStep);

        if (projectiles[i].type == 1) {
            RenderMesh2D(meshes["orangeStar"], shaders["VertexColor"], modelMatrix);
        } else if (projectiles[i].type == 2) {
            RenderMesh2D(meshes["blueStar"], shaders["VertexColor"], modelMatrix);
        } else if (projectiles[i].type == 3) {
            RenderMesh2D(meshes["yellowStar"], shaders["VertexColor"], modelMatrix);
        } else if (projectiles[i].type == 4) {
            RenderMesh2D(meshes["purpleStar"], shaders["VertexColor"], modelMatrix);
        }

        projectiles[i].x += PROJECTILE_SPEED * deltaTimeSeconds;
        projectiles[i].angularStep -= deltaTimeSeconds;
    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    glm::ivec2 resolution = window->GetResolution();
    int scaledMouseX = 1280 * mouseX / resolution.x;
    int scaledMouseY = 720 * mouseY / resolution.y;
    scaledMouseY = 720 - scaledMouseY;

    carryingTurretX = scaledMouseX;
    carryingTurretY = scaledMouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    glm::ivec2 resolution = window->GetResolution();
    int scaledMouseX = 1280 * mouseX / resolution.x;
    int scaledMouseY = 720 * mouseY / resolution.y;
    scaledMouseY = 720 - scaledMouseY;

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        // Check if clicked on a currency star
        for (int i = 0; i < currencyStars.size(); i++) {
            if (scaledMouseX < currencyStars[i].x + HITBOX && scaledMouseX > currencyStars[i].x - HITBOX && scaledMouseY < currencyStars[i].y + HITBOX && scaledMouseY > currencyStars[i].y - HITBOX) {
                currencyStars.erase(currencyStars.begin() + i);
                game.currency++;
            }
        }

        // Check if clicked on a turret from the shop
        for (int i = 0; i < 4; i++) {
            if (scaledMouseX < shopSquares[i].x + GRID_HITBOX && scaledMouseX > shopSquares[i].x - GRID_HITBOX && scaledMouseY < shopSquares[i].y + GRID_HITBOX && scaledMouseY > shopSquares[i].y - GRID_HITBOX) {
                carryingTurret = i + 1;
            }
        }
    }

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < 9; i++) {
            if (scaledMouseX < gridSquares[i].x + GRID_HITBOX && scaledMouseX > gridSquares[i].x - GRID_HITBOX && scaledMouseY < gridSquares[i].y + GRID_HITBOX && scaledMouseY > gridSquares[i].y - GRID_HITBOX) {
                if (gridSquares[i].turretType > 0) {
                    gridSquares[i].removeTurret = true;
                }
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event

    glm::ivec2 resolution = window->GetResolution();
    int scaledMouseX = 1280 * mouseX / resolution.x;
    int scaledMouseY = 720 * mouseY / resolution.y;
    scaledMouseY = 720 - scaledMouseY;

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && carryingTurret > 0) {
        int carryingTurretCost = 0;
        if (carryingTurret == 1)
            carryingTurretCost = 1;
        else if (carryingTurret == 2 || carryingTurret == 3)
            carryingTurretCost = 2;
        else if (carryingTurret == 4)
            carryingTurretCost = 3;

        for (int i = 0; i < 9; i++) {
            if (scaledMouseX < gridSquares[i].x + GRID_HITBOX && scaledMouseX > gridSquares[i].x - GRID_HITBOX && scaledMouseY < gridSquares[i].y + GRID_HITBOX && scaledMouseY > gridSquares[i].y - GRID_HITBOX) {
                if (gridSquares[i].turretType == 0 && game.currency >= carryingTurretCost) {
                    gridSquares[i].turretType = carryingTurret;
                    gridSquares[i].turretScale = 1;
                    game.currency -= carryingTurretCost;
                }
            }
        }

        carryingTurret = 0;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}