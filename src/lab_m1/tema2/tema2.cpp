#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/tema2/transform3D.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */



Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{
    // Initialize game timer

    gameTimer = GAME_TIMER;

    // Load meshes

    {
        Mesh* mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tankBody");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "myTank"), "myTankBody.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tankTracks");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "myTank"), "myTankTracks.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tankTurret");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "myTank"), "myTankTurret.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tankCannon");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "myTank"), "myTankCannon.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal

    {
        Shader* shader = new Shader("MyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Initialize player values

    player.position = glm::vec3(0.0f, 0.1f, 0.0f);
    player.bodyRotation = 0.0f;
    player.turretRotation = 0.0f;
    player.HP = MAX_HP;
    player.shootingCooldown = 0.0f;
    player.state = State::STAY;

    // Create camera

    camera = new mycamera::Camera();
    camera->Set(glm::vec3(player.position.x - camera->distanceToTarget, player.position.y + 0.9f, player.position.z), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    // Generate building locations and scales

    for (int i = 0; i < BUILDINGS_NO; i++) {
        Building newBuilding;

        float xpos = rand() % (BUILDING_POSITION_UPPER_BOUND - BUILDING_POSITION_LOWER_BOUND) + BUILDING_POSITION_LOWER_BOUND;
        float zpos = rand() % (BUILDING_POSITION_UPPER_BOUND - BUILDING_POSITION_LOWER_BOUND) + BUILDING_POSITION_LOWER_BOUND;

        while ((xpos < SAFE_ZONE_UPPER_BOUND && xpos > SAFE_ZONE_LOWER_BOUND) || (zpos < SAFE_ZONE_UPPER_BOUND && zpos > SAFE_ZONE_LOWER_BOUND)) {
            xpos = rand() % (BUILDING_POSITION_UPPER_BOUND - BUILDING_POSITION_LOWER_BOUND) + BUILDING_POSITION_LOWER_BOUND;
            zpos = rand() % (BUILDING_POSITION_UPPER_BOUND - BUILDING_POSITION_LOWER_BOUND) + BUILDING_POSITION_LOWER_BOUND;
        }

        newBuilding.position = glm::vec3(xpos, 0, zpos);

        newBuilding.scaleX = rand() % (BUILDING_SCALE_UPPER_BOUND - BUILDING_SCALE_LOWER_BOUND) + BUILDING_SCALE_LOWER_BOUND;
        newBuilding.scaleY = rand() % (BUILDING_SCALE_UPPER_BOUND - BUILDING_SCALE_LOWER_BOUND) + BUILDING_SCALE_LOWER_BOUND;
        newBuilding.scaleZ = rand() % (BUILDING_SCALE_UPPER_BOUND - BUILDING_SCALE_LOWER_BOUND) + BUILDING_SCALE_LOWER_BOUND;

        buildings.push_back(newBuilding);
    }

    // Generate enemies positions

    for (int i = 0; i < ENEMIES_NO; i++) {
        Tank newEnemy;

        float xpos = rand() % (ENEMY_POSITION_UPPER_BOUND - ENEMY_POSITION_LOWER_BOUND) + ENEMY_POSITION_LOWER_BOUND;
        float zpos = rand() % (ENEMY_POSITION_UPPER_BOUND - ENEMY_POSITION_LOWER_BOUND) + ENEMY_POSITION_LOWER_BOUND;

        while ((xpos < SAFE_ZONE_UPPER_BOUND && xpos > SAFE_ZONE_LOWER_BOUND) || (zpos < SAFE_ZONE_UPPER_BOUND && zpos > SAFE_ZONE_LOWER_BOUND)) {
            xpos = rand() % (ENEMY_POSITION_UPPER_BOUND - ENEMY_POSITION_LOWER_BOUND) + ENEMY_POSITION_LOWER_BOUND;
            zpos = rand() % (ENEMY_POSITION_UPPER_BOUND - ENEMY_POSITION_LOWER_BOUND) + ENEMY_POSITION_LOWER_BOUND;
        }

        newEnemy.position = glm::vec3(xpos, 0.1f, zpos);
        newEnemy.bodyRotation = 0.0f;
        newEnemy.turretRotation = 0.0f;
        newEnemy.HP = MAX_HP;
        newEnemy.shootingCooldown = 0.0f;
        newEnemy.state = State::STAY;
        newEnemy.stateCooldown = 1.0f;

        enemies.push_back(newEnemy);
    }
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
    /* Check if there is time remaining */

    gameTimer -= deltaTimeSeconds;

    if (gameTimer <= 0 && !printStatus) {
        cout << "Time's up!\n";
        cout << "Next time you'll do even better!\n";

        for (int i = 0; i < enemies.size(); i++)
            if (enemies[i].state == State::DEAD)
                score += 100;

        cout << "Score: " << score << "\n";

        player.state = State::DEAD;
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].state = State::DEAD;
            enemies[i].projectiles.clear();
        }

        printStatus = true;
    }

    /* Render player and calculate body / turret directions */

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(player.position);
    modelMatrix *= transform3D::RotateOY(player.bodyRotation);
    modelMatrix *= transform3D::Scale(TANK_SCALE, TANK_SCALE, TANK_SCALE);

    RenderMesh(meshes["tankBody"], shaders["MyShader"], modelMatrix, darkgreen, player.HP);
    RenderMesh(meshes["tankTracks"], shaders["MyShader"], modelMatrix, gray, player.HP);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(player.position);
    modelMatrix *= transform3D::RotateOY(player.turretRotation);
    modelMatrix *= transform3D::Scale(TANK_SCALE, TANK_SCALE, TANK_SCALE);

    RenderMesh(meshes["tankTurret"], shaders["MyShader"], modelMatrix, green, player.HP);
    RenderMesh(meshes["tankCannon"], shaders["MyShader"], modelMatrix, gray, player.HP);

    player.bodyDirection = glm::normalize(glm::vec3(cos(player.bodyRotation), 0, -sin(player.bodyRotation)));
    player.turretDirection = glm::normalize(glm::vec3(cos(player.turretRotation), 0, -sin(player.turretRotation)));

    /* Render plane */

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Scale(3.0f, 1.0f, 3.0f);
    RenderMesh(meshes["plane"], shaders["MyShader"], modelMatrix, brown, MAX_HP);

    /* Render projectiles */

    player.shootingCooldown -= deltaTimeSeconds;

    for (int i = 0; i < player.projectiles.size(); i++) {
        if (player.projectiles[i].ttl > 0) {
            player.projectiles[i].position += player.projectiles[i].direction * PROJECTILE_SPEED * deltaTimeSeconds;

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(player.projectiles[i].position);
            modelMatrix *= transform3D::Scale(PROJECTILE_SCALE, PROJECTILE_SCALE, PROJECTILE_SCALE);

            RenderMesh(meshes["projectile"], shaders["MyShader"], modelMatrix, red, MAX_HP);

            player.projectiles[i].ttl -= deltaTimeSeconds;
        }
        else {
            player.projectiles.erase(player.projectiles.begin() + i);
            break;
        }
    }

    /* Render buildings */

    for (int i = 0; i < buildings.size(); i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(buildings[i].position);
        modelMatrix *= transform3D::Scale(buildings[i].scaleX, buildings[i].scaleY, buildings[i].scaleZ);

        RenderMesh(meshes["building"], shaders["MyShader"], modelMatrix, white, MAX_HP);
    }

    /* Render enemies (and their projectiles) and calculate body / turret directions */

    for (int i = 0; i < enemies.size(); i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(enemies[i].position);
        modelMatrix *= transform3D::RotateOY(enemies[i].bodyRotation);
        modelMatrix *= transform3D::Scale(TANK_SCALE, TANK_SCALE, TANK_SCALE);

        RenderMesh(meshes["tankBody"], shaders["MyShader"], modelMatrix, darkred, enemies[i].HP);
        RenderMesh(meshes["tankTracks"], shaders["MyShader"], modelMatrix, gray, enemies[i].HP);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(enemies[i].position);
        modelMatrix *= transform3D::RotateOY(enemies[i].turretRotation);
        modelMatrix *= transform3D::Scale(TANK_SCALE, TANK_SCALE, TANK_SCALE);

        RenderMesh(meshes["tankTurret"], shaders["MyShader"], modelMatrix, red, enemies[i].HP);
        RenderMesh(meshes["tankCannon"], shaders["MyShader"], modelMatrix, gray, enemies[i].HP);

        enemies[i].bodyDirection = glm::normalize(glm::vec3(cos(enemies[i].bodyRotation), 0, -sin(enemies[i].bodyRotation)));
        enemies[i].turretDirection = glm::normalize(glm::vec3(cos(enemies[i].turretRotation), 0, -sin(enemies[i].turretRotation)));

        enemies[i].shootingCooldown -= deltaTimeSeconds;

        for (int j = 0; j < enemies[i].projectiles.size(); j++) {
            if (enemies[i].projectiles[j].ttl > 0) {
                enemies[i].projectiles[j].position += enemies[i].projectiles[j].direction * PROJECTILE_SPEED * deltaTimeSeconds;

                modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(enemies[i].projectiles[j].position);
                modelMatrix *= transform3D::Scale(PROJECTILE_SCALE, PROJECTILE_SCALE, PROJECTILE_SCALE);

                RenderMesh(meshes["projectile"], shaders["MyShader"], modelMatrix, red, MAX_HP);

                enemies[i].projectiles[j].ttl -= deltaTimeSeconds;
            }
            else {
                enemies[i].projectiles.erase(enemies[i].projectiles.begin() + j);
                break;
            }
        }
    }

    /* Check enemy health status */
    
    enemiesStillAlive = false;

    for (int i = 0; i < enemies.size(); i++)
        if (enemies[i].HP <= 0)
            enemies[i].state = State::DEAD;
        else
            enemiesStillAlive = true;

    if (!enemiesStillAlive && !printStatus) {
        cout << "Congratulations! You won!\n";
        cout << "You get a bonus 250p for winning :D\n";

        score += 250;
        for (int i = 0; i < enemies.size(); i++)
            if (enemies[i].state == State::DEAD)
                score += 100;

        cout << "Score: " << score << "\n";

        player.state = State::DEAD;
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].state = State::DEAD;
            enemies[i].projectiles.clear();
        }

        printStatus = true;
    }

    /* Check player HP status */

    if (player.HP <= 0 && !printStatus) {
        cout << "Game over! You died!\n";
        cout << "You only get 50p for a kill :(\n";

        for (int i = 0; i < enemies.size(); i++)
            if (enemies[i].state == State::DEAD)
                score += 50;

        cout << "Score: " << score << "\n";

        player.state = State::DEAD;
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].state = State::DEAD;
            enemies[i].projectiles.clear();
        }

        printStatus = true;
    }

    /* Perform enemy actions */

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].stateCooldown -= deltaTimeSeconds;

        if (enemies[i].state != State::DEAD) {

            if (enemies[i].stateCooldown <= 0) {
                enemies[i].stateCooldown = STATE_COOLDOWN;
                enemies[i].state = (State)(rand() % 5);
            }

            switch (enemies[i].state) {

            case State::MOVE_FORWARD:
                enemies[i].position += enemies[i].bodyDirection * (TANK_SPEED * ENEMY_SPEED_FACTOR * deltaTimeSeconds);
                break;

            case State::MOVE_BACKWARD:
                enemies[i].position -= enemies[i].bodyDirection * (TANK_SPEED * ENEMY_SPEED_FACTOR * deltaTimeSeconds);
                break;

            case State::ROTATE_LEFT:
                enemies[i].bodyRotation += deltaTimeSeconds * ENEMY_ROTATION_FACTOR;
                enemies[i].turretRotation += deltaTimeSeconds * ENEMY_ROTATION_FACTOR;
                break;

            case State::ROTATE_RIGHT:
                enemies[i].bodyRotation -= deltaTimeSeconds * ENEMY_ROTATION_FACTOR;
                enemies[i].turretRotation -= deltaTimeSeconds * ENEMY_ROTATION_FACTOR;
                break;

            case State::SHOOT:
                glm::vec3 distanceVec = glm::normalize(player.position - enemies[i].position);

                if (enemies[i].turretDirection.x > distanceVec.x + SHOOTING_DIRECTION_OFFSET ||
                    enemies[i].turretDirection.x < distanceVec.x - SHOOTING_DIRECTION_OFFSET ||
                    enemies[i].turretDirection.z > distanceVec.z + SHOOTING_DIRECTION_OFFSET ||
                    enemies[i].turretDirection.z < distanceVec.z - SHOOTING_DIRECTION_OFFSET) {
                    if (glm::cross(enemies[i].turretDirection, distanceVec).y > 0)
                        enemies[i].turretRotation += deltaTimeSeconds;
                    else
                        enemies[i].turretRotation -= deltaTimeSeconds;
                }
                else {
                    if (enemies[i].shootingCooldown <= 0) {
                        Projectile newProjectile;

                        newProjectile.direction = enemies[i].turretDirection;
                        newProjectile.position = enemies[i].position;
                        newProjectile.position += PROJECTILE_START_OFFSET * newProjectile.direction;
                        newProjectile.position.y += PROJECTILE_ELEVATION;
                        newProjectile.ttl = PROJECTILE_TTL;

                        enemies[i].projectiles.push_back(newProjectile);

                        enemies[i].shootingCooldown = SHOOTING_COOLDOWN;
                    }
                }
                break;

            }

        }

    }

    /* Check for projectile - building collisions */

    // PlayerProjectile-Building
    for (int i = 0; i < player.projectiles.size(); i++) 
        for (int j = 0; j < buildings.size(); j++)
            if (CheckProjectileBuildingCollision(player.projectiles[i], buildings[j])) {
                player.projectiles.erase(player.projectiles.begin() + i);
                break;
            }

    // EnemyProjectile-Building
    for (int i = 0; i < enemies.size(); i++)
        for (int j = 0; j < enemies[i].projectiles.size(); j++)
            for (int k = 0; k < buildings.size(); k++)
                if (CheckProjectileBuildingCollision(enemies[i].projectiles[j], buildings[k])) {
                    enemies[i].projectiles.erase(enemies[i].projectiles.begin() + j);
                    break;
                }


    /* Check for projectile - tank collisions */

    // PlayerProjectile-EnemyTank
    for (int i = 0; i < player.projectiles.size(); i++)
        for (int j = 0; j < enemies.size(); j++)
            if (CheckProjectileTankCollision(player.projectiles[i], enemies[j])) {
                player.projectiles.erase(player.projectiles.begin() + i);
                enemies[j].HP--;
                break;
            }

    // EnemyProjectile-PlayerTank
    for (int i = 0; i < enemies.size(); i++)
        for (int j = 0; j < enemies[i].projectiles.size(); j++)
            if (CheckProjectileTankCollision(enemies[i].projectiles[j], player)) {
                enemies[i].projectiles.erase(enemies[i].projectiles.begin() + j);
                player.HP--;
                break;
            }

    // EnemyProjectile-EnemyTank
    for (int i = 0; i < enemies.size(); i++)
        for (int j = 0; j < enemies[i].projectiles.size(); j++)
            for (int k = 0; k < enemies.size(); k++)
                if (i != j && CheckProjectileTankCollision(enemies[i].projectiles[j], enemies[k])) {
                    enemies[i].projectiles.erase(enemies[i].projectiles.begin() + j);
                    break;
                }

    /* Check for tank - building collisions */
    
    // Player-Building
    for (int i = 0; i < buildings.size(); i++) {
        if (CheckTankBuildingCollision(player, buildings[i])) {
            glm::vec3 buldingPosition = buildings[i].position;
            buldingPosition.y = 0.1f;

            glm::vec3 directionVec = glm::normalize(buldingPosition - player.position);
            
            player.position -= directionVec * (TANK_SPEED * deltaTimeSeconds);
            camera->position -= directionVec * (TANK_SPEED * deltaTimeSeconds);
        }
    }

    // Enemy-Building
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < buildings.size(); j++) {
            if (CheckTankBuildingCollision(enemies[i], buildings[j])) {
                glm::vec3 buldingPosition = buildings[j].position;
                buldingPosition.y = 0.1f;

                glm::vec3 directionVec = glm::normalize(buldingPosition - enemies[i].position);

                enemies[i].position -= directionVec * (TANK_SPEED * deltaTimeSeconds);
            }
        }
    }

    /* Check for tank - tank collisions */

    // Player-Enemy
    for (int i = 0; i < enemies.size(); i++) {
        if (CheckTankTankCollision(player, enemies[i])) {
            glm::vec3 distanceVec = enemies[i].position - player.position;

            float modP = 2 * TANK_COLLISION_RADIUS - glm::length(distanceVec);
            glm::vec3 P = modP * glm::normalize(distanceVec);
            P.z *= -1;
            player.position += 0.5f * P;
            camera->position += 0.5f * P;
            enemies[i].position -= 0.5f * P;
        }
    }

    // Enemy-Enemy
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (i != j) {
                if (CheckTankTankCollision(enemies[i], enemies[j])) {
                    glm::vec3 distanceVec = enemies[j].position - enemies[i].position;

                    float modP = 2 * TANK_COLLISION_RADIUS - glm::length(distanceVec);
                    glm::vec3 P = modP * glm::normalize(distanceVec);
                    P.z *= -1;
                    enemies[i].position += 0.05f * P;
                    enemies[j].position -= 0.05f * P;
                }
            }
        }
    }
    

}

void Tema2::FrameEnd()
{
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3& color, float HP)
{
    if (HP < 0)
        HP = 0;

    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Get shader location for uniform mat4 "Model"
    int modelLocation = glGetUniformLocation(shader->program, "Model");

    // Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Get shader location for uniform mat4 "View"
    int viewLocation = glGetUniformLocation(shader->program, "View");

    // Set shader uniform "View" to viewMatrix
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    // Get shader location for uniform mat4 "Projection"
    int projectionLocation = glGetUniformLocation(shader->program, "Projection");

    // Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Get shader location for uniform vec3 "Color"
    int colorLocation = glGetUniformLocation(shader->program, "Color");

    // Set shader uniform "Color" to color
    glUniform3f(colorLocation, color.x, color.y, color.z);

    // Get shader location for uniform float "HP"
    int hpLocation = glGetUniformLocation(shader->program, "HP");

    // Set shader uniform "HP" to HP
    glUniform1f(hpLocation, HP);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
    mesh->Render();

}

bool Tema2::CheckTankTankCollision(Tank tank1, Tank tank2)
{
    glm::vec3 distanceVec = tank2.position - tank1.position;
    float distance = glm::length(distanceVec);

    return distance < 2 * TANK_COLLISION_RADIUS;
}

bool Tema2::CheckTankBuildingCollision(Tank tank, Building building)
{
    if (tank.position.x < building.position.x + (building.scaleX / 2) &&
        tank.position.x > building.position.x - (building.scaleX / 2) &&
        tank.position.z < building.position.z + (building.scaleZ / 2) &&
        tank.position.z > building.position.z - (building.scaleZ / 2))
        return true;
    else return false;
}

bool Tema2::CheckProjectileTankCollision(Projectile projectile, Tank tank)
{
    if (projectile.position.x < tank.position.x + (PROJECTILE_COLLISION_RADIUS / 2) &&
        projectile.position.x > tank.position.x - (PROJECTILE_COLLISION_RADIUS / 2) &&
        projectile.position.z < tank.position.z + (PROJECTILE_COLLISION_RADIUS / 2) &&
        projectile.position.z > tank.position.z - (PROJECTILE_COLLISION_RADIUS / 2))
        return true;
    else return false;
}

bool Tema2::CheckProjectileBuildingCollision(Projectile projectile, Building building)
{
    if (projectile.position.x < building.position.x + (building.scaleX / 2) &&
        projectile.position.x > building.position.x - (building.scaleX / 2) &&
        projectile.position.z < building.position.z + (building.scaleZ / 2) &&
        projectile.position.z > building.position.z - (building.scaleZ / 2))
        return true;
    else return false;
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{

    if (player.state != State::DEAD) {
        if (window->KeyHold(GLFW_KEY_W)) {
            player.position += player.bodyDirection * (TANK_SPEED * deltaTime);
            camera->position += player.bodyDirection * (TANK_SPEED * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            player.bodyRotation += deltaTime;
            player.turretRotation += deltaTime;

            camera->RotateThirdPerson_OY(deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            player.position -= player.bodyDirection * (TANK_SPEED * deltaTime);
            camera->position -= player.bodyDirection * (TANK_SPEED * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            player.bodyRotation -= deltaTime;
            player.turretRotation -= deltaTime;

            camera->RotateThirdPerson_OY(-deltaTime);
        }
    }
    
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    float sensitivityTurret = 0.003f;

    if (shouldIgnore) {
        shouldIgnore = false;
        return;
    }

    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
        camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
    }
    else {
        player.turretRotation -= deltaX * sensitivityTurret; 
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && player.state != State::DEAD) {
        if (player.shootingCooldown <= 0) {
            Projectile newProjectile;

            newProjectile.direction = player.turretDirection;
            newProjectile.position = player.position;
            newProjectile.position += PROJECTILE_START_OFFSET * newProjectile.direction;
            newProjectile.position.y += PROJECTILE_ELEVATION;
            newProjectile.ttl = PROJECTILE_TTL;

            player.projectiles.push_back(newProjectile);

            player.shootingCooldown = SHOOTING_COOLDOWN;
        }
    }
}



void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        shouldIgnore = true;
    }
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

