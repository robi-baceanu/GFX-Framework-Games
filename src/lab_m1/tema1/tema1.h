#pragma once

#include "components/simple_scene.h"

#define SQUARE_SIDE 100
#define SQUARE_GAP 25
#define REDLINE_WIDTH 50
#define STAR_RADIUS 30
#define HEXAGON_OUTER_RADIUS 30
#define HEXAGON_INNER_RADIUS 20
#define TURRET_HEIGHT 80
#define HITBOX 20
#define GRID_HITBOX 50
#define MOVE_SPEED 40
#define PROJECTILE_SPEED 100
#define STAR_SPAWN_INTERVAL_LOWER_BOUND 3
#define STAR_SPAWN_INTERVAL_UPPER_BOUND 5
#define ZOMBIE_SPAWN_INTERVAL_LOWER_BOUND 5
#define ZOMBIE_SPAWN_INTERVAL_UPPER_BOUND 10
#define PROJECTILE_DELAY 2
#define REMOVE_HP_ANIMATION_TIME 1
#define OOB 1300


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

        // For turretType field:
        // 0 -> no turret; 1 -> orange; 2 -> blue; 3 -> yellow; 4 -> purple
        class GridSquare
        {
        public:
            float x;
            float y; 
            int turretType = 0;
            float turretScale;
            bool removeTurret = false;
            float timeToShoot = 0;
        };

        class RedLine
        {
        public:
            float x;
            float y;
        };

        class ShopSquare
        {
        public:
            float x;
            float y;
        };

        class HealthBar
        {
        public:
            int healthPoints;
            float x;
            float y;
            bool removeHP = false;
            float removeAnimationTime = REMOVE_HP_ANIMATION_TIME;
        };

        class Game
        {
        public:
            HealthBar healthBar;
            int currency;
        };

        class CurrencyStar
        {
        public:
            float x;
            float y;
        };

        // For type field
        // 1 -> orange; 2 -> blue; 3 -> yellow; 4 -> purple
        class ProjectileStar
        {
        public:
            float x;
            float y;
            int type;
            float angularStep;
        };

        // For type field
        // 1 -> orange; 2 -> blue; 3 -> yellow; 4 -> purple
        class Zombie
        {
        public:
            float x = OOB;
            float y;
            float scale = 1;
            int type;   
            int hp = 3;
        };

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;

        Game game;

        GridSquare gridSquares[9];
        RedLine redLine;
        ShopSquare shopSquares[4];

        std::vector<CurrencyStar> currencyStars;
        float timeToSpawnNewStar = STAR_SPAWN_INTERVAL_LOWER_BOUND;

        std::vector<Zombie> zombies;
        float timeToSpawnZombie = ZOMBIE_SPAWN_INTERVAL_LOWER_BOUND;

        std::vector<ProjectileStar> projectiles;

        // For carryingTurret field
        // 1->orange; 2->blue; 3->yellow; 4->purple
        int carryingTurret = 0;
        float carryingTurretX;
        float carryingTurretY;

        // Colors
        glm::vec3 red = glm::vec3(1, 0, 0);
        glm::vec3 green = glm::vec3(0, 1, 0);
        glm::vec3 blue = glm::vec3(0, 0, 1);
        glm::vec3 yellow = glm::vec3(1, 1, 0);
        glm::vec3 purple = glm::vec3(0.5, 0, 0.5);
        glm::vec3 orange = glm::vec3(1, 0.5, 0);
        glm::vec3 gray = glm::vec3(0.5, 0.5, 0.5);
        glm::vec3 turquoise = glm::vec3(0, 1, 1);
        glm::vec3 pink = glm::vec3(1, 0, 1);

    };
}   // namespace m1