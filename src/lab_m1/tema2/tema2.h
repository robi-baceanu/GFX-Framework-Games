#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"

#define RADIANS(angle) ((angle) * 0.0174532925194444f)
#define MAX_HP 5
#define TANK_SCALE 0.1f
#define TANK_SPEED 2.0f
#define TANK_COLLISION_RADIUS 0.3f
#define PROJECTILE_SPEED 4.0f
#define PROJECTILE_TTL 10.0f
#define PROJECTILE_SCALE 0.05f
#define PROJECTILE_ELEVATION 0.13f
#define PROJECTILE_START_OFFSET 0.38f
#define PROJECTILE_COLLISION_RADIUS 0.5f
#define SHOOTING_COOLDOWN 2.0f
#define SHOOTING_DIRECTION_OFFSET 0.02f
#define BUILDINGS_NO 10
#define BUILDING_SCALE_LOWER_BOUND 4
#define BUILDING_SCALE_UPPER_BOUND 8
#define BUILDING_POSITION_LOWER_BOUND -30
#define BUILDING_POSITION_UPPER_BOUND 30
#define ENEMIES_NO 5
#define ENEMY_POSITION_LOWER_BOUND -10
#define ENEMY_POSITION_UPPER_BOUND 10
#define ENEMY_SPEED_FACTOR 0.5f
#define ENEMY_ROTATION_FACTOR 0.25f
#define SAFE_ZONE_UPPER_BOUND 5
#define SAFE_ZONE_LOWER_BOUND -5
#define STATE_COOLDOWN 10.0f
#define GAME_TIMER 300.0f


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

        enum class State
        {
            MOVE_FORWARD,
            MOVE_BACKWARD,
            ROTATE_RIGHT,
            ROTATE_LEFT,
            SHOOT,
            STAY,
            DEAD
        };

        class Projectile
        {
        public:
            glm::vec3 position;
            glm::vec3 direction;
            float ttl = PROJECTILE_TTL;
        };

        class Tank
        {
        public:
            glm::vec3 position;

            glm::vec3 bodyDirection;
            glm::vec3 turretDirection;

            float bodyRotation;
            float turretRotation;

            std::vector<Projectile> projectiles;
            float shootingCooldown;

            float HP;

            State state;
            float stateCooldown;

            glm::mat4 modelMatrix;
        };

        class Building 
        {
        public:
            glm::vec3 position;

            float scaleX;
            float scaleY;
            float scaleZ;
        };

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 &color, float HP);
        bool CheckTankTankCollision(Tank tank1, Tank tank2);
        bool CheckTankBuildingCollision(Tank tank, Building building);
        bool CheckProjectileTankCollision(Projectile projectile, Tank tank);
        bool CheckProjectileBuildingCollision(Projectile projectile, Building building);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat4 modelMatrix;

        mycamera::Camera* camera;
        glm::mat4 projectionMatrix;

        Tank player;

        std::vector<Building> buildings;

        std::vector<Tank> enemies;

        float gameTimer;

        bool shouldIgnore = false;
        bool printStatus = false;
        bool enemiesStillAlive = false;

        int score = 0;

        // Colors

        glm::vec3 red = glm::vec3(1, 0, 0);
        glm::vec3 darkred = glm::vec3(0.5, 0, 0);
        glm::vec3 green = glm::vec3(0, 1, 0);
        glm::vec3 darkgreen = glm::vec3(0, 0.25, 0.125);
        glm::vec3 gray = glm::vec3(0.5, 0.5, 0.5);
        glm::vec3 brown = glm::vec3(0.35, 0.25, 0.25);
        glm::vec3 white = glm::vec3(0.8, 0.8, 0.8);

    };
}   // namespace m1