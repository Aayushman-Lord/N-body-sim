#include <raylib.h>
#include <vector>
#include <iostream>
#include <cmath>

const float g = 5000;
Color TrailsColor = BLACK;

Color getcolor(float mass)
{
    if (mass < 1000)
        return RED;
    else if (mass < 5000)
        return YELLOW;
    else if (mass < 10000)
        return ORANGE;
    else if (mass < 50000)
        return BLUE;
    else if (mass < 100000)
        return WHITE;
    else
        return BLACK;
}

class Object
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    std::vector<Vector2> Trails;
    double mass;
    double radius;

    Object(Vector2 pos, Vector2 vel, Vector2 acc, double m, double r)
    {
        position = pos;
        velocity = vel;
        acceleration = acc;
        mass = m;
        radius = r;
        Trails.push_back(position);
    }

    void display()
    {
        Color color = getcolor(mass);
        
        

        //Trails
        for (int i = 0; i < Trails.size(); i++)
        {
                DrawPixel(Trails[i].x, Trails[i].y, TrailsColor);
        }
            Trails.push_back(position);

            if (Trails.size() > 440)
                Trails.erase(Trails.begin());

             
        
       
        

        //Drawing main object with outline
        DrawCircle(position.x, position.y, radius + 1.5, WHITE);
        DrawCircle(position.x, position.y, radius, color);
    }
};

int main()
{
    const int screenWidth = 1900;
    const int screenHeight = 1000;

    Object obj({screenWidth / 2, screenHeight / 2}, {0, 0}, {0, 0}, 16000, 20);
    Object obj2({screenWidth / 2 + 800, screenHeight / 2}, {0, 200}, {0, 0}, 16000, 20);
    // Object obj3({screenWidth / 2 - 800, screenHeight / 2}, {0, -200}, {0, 0}, 2000, 20);
    // Object obj4({screenWidth / 2 - 800, screenHeight / 2 + 800}, {-100, 0}, {0, 0}, 1000, 10);
    // Object obj5({screenWidth / 2 + 800, screenHeight / 2 - 800}, {100, 0}, {0, 0}, 1000, 10);

    std::vector<Object> objects;
    objects.push_back(obj);
    objects.push_back(obj2);
    // objects.push_back(obj3);
    // objects.push_back(obj4);
    // objects.push_back(obj5);

    InitWindow(screenWidth, screenHeight, "Gravity Sim");

    Camera2D camera = {0};
    camera.target = {screenWidth / 2, screenHeight / 2};
    camera.offset = {screenWidth / 2, screenHeight / 2};
    camera.zoom = 1;

    SetTargetFPS(60);

    double timeScale = 1.0;

    bool dragging = false;
    Vector2 dragStart = {0, 0};
    Vector2 dragCurrent = {0, 0};

    const double velocityScale = 1.0;

    while (!WindowShouldClose())
    {
        // time interval for physics updates
        float dt = GetFrameTime() * timeScale;

        // TIME CONTROL
        if (IsKeyPressed(KEY_EQUAL))
            timeScale *= 2.0;

        if (IsKeyPressed(KEY_MINUS))
            timeScale *= 0.5;

        if (IsKeyPressed(KEY_SPACE))
            timeScale = (timeScale == 0) ? 1.0 : 0;

        if (timeScale > 100000)
            timeScale = 100000;

        if (timeScale < 0.00001)
            timeScale = 0;

        // --------------- LEAPFROG ------------------
        // First Half Velocity Update
        for (auto &o : objects)
        {
            o.velocity.x += o.acceleration.x * (dt / 2);
            o.velocity.y += o.acceleration.y * (dt / 2);
        }

        // Full Position Update
        for (auto &o : objects)
        {
            o.position.x += o.velocity.x * dt;
            o.position.y += o.velocity.y * dt;
        }

        // Reset acceleration for the new positions
        for (auto &o : objects)
        {
            o.acceleration = {0, 0};
        }
        // GRAVITY
        for (int i = 0; i < objects.size(); i++)
        {
            for (int j = 0; j < objects.size(); j++)
            {
                if (i == j)
                    continue;

                float dx = objects[j].position.x - objects[i].position.x;
                float dy = objects[j].position.y - objects[i].position.y;

                float distance = sqrt(dx * dx + dy * dy);
                if (distance < 5)
                    distance = 5;

                float accel = g * objects[j].mass / (distance * distance);

                objects[i].acceleration.x += dx / distance * accel;
                objects[i].acceleration.y += dy / distance * accel;
            }
        }

        // UPDATE physics

        for (auto &o : objects)
        {
            o.velocity.x += o.acceleration.x * (dt / 2);
            o.velocity.y += o.acceleration.y * (dt / 2);
        }

        // --------------- LEAPFROG END ------------------

        // COLLISION
        for (int i = 0; i < objects.size(); i++)
        {
            for (int j = i + 1; j < objects.size(); j++)
            {
                float dx = objects[j].position.x - objects[i].position.x;
                float dy = objects[j].position.y - objects[i].position.y;

                float distance = sqrt(dx * dx + dy * dy);

                if (distance <= objects[i].radius + objects[j].radius)
                {
                    float newvx =
                        (objects[i].mass * objects[i].velocity.x +
                         objects[j].mass * objects[j].velocity.x) /
                        (objects[i].mass + objects[j].mass);

                    float newvy =
                        (objects[i].mass * objects[i].velocity.y +
                         objects[j].mass * objects[j].velocity.y) /
                        (objects[i].mass + objects[j].mass);

                    objects[j].mass += objects[i].mass;

                    float total_area =
                        objects[i].radius * objects[i].radius +
                        objects[j].radius * objects[j].radius;

                    objects[j].radius = sqrt(total_area);
                    objects[j].velocity = {newvx, newvy};

                    objects.erase(objects.begin() + i);
                    i--;
                    break;
                }
            }
        }

        // CAMERA
        float camSpeed = 500 * GetFrameTime();

        if (IsKeyDown(KEY_W))
            camera.target.y -= camSpeed;
        if (IsKeyDown(KEY_S))
            camera.target.y += camSpeed;
        if (IsKeyDown(KEY_A))
            camera.target.x -= camSpeed;
        if (IsKeyDown(KEY_D))
            camera.target.x += camSpeed;

        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.1f)
                camera.zoom = 0.1f;
        }

        // MOUSE DRAG
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            dragging = true;
            dragStart = mouseWorld;
        }

        if (dragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            dragCurrent = mouseWorld;

        if (dragging && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            Vector2 velocity =
                {
                    (dragCurrent.x - dragStart.x) * velocityScale,
                    (dragCurrent.y - dragStart.y) * velocityScale};

            objects.push_back(Object(dragStart, velocity, {0, 0}, 1000, 10));
            dragging = false;
        }

        // ORBIT ASSIST
        if (objects.size() >= 2)
        {
            Object &sat = objects.back();

            // find most massive object
            int centerIndex = 0;
            float maxMass = objects[0].mass;

            for (int i = 1; i < objects.size(); i++)
            {
                if (objects[i].mass > maxMass)
                {
                    maxMass = objects[i].mass;
                    centerIndex = i;
                }
            }

            Object &center = objects[centerIndex];

            float dx = sat.position.x - center.position.x;
            float dy = sat.position.y - center.position.y;

            float eps = 0.1f;
            float r = sqrt(dx * dx + dy * dy + eps * eps);

            float rx = dx / r;
            float ry = dy / r;

            float tx = -ry;
            float ty = rx;

            float v = sqrt(g * center.mass / r);

            if (IsKeyPressed(KEY_C))
            {
                sat.velocity.x = tx * v;
                sat.velocity.y = ty * v;
            }

            if (IsKeyPressed(KEY_E))
            {
                sat.velocity.x = tx * v * 0.8f;
                sat.velocity.y = ty * v * 0.8f;
            }
        }

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        // Velo lines
        for (auto &o : objects)
        {
            o.display();

            DrawLine(
                o.position.x,
                o.position.y,
                o.position.x + o.velocity.x * 0.1,
                o.position.y + o.velocity.y * 0.1,
                GREEN);
        }

        if (dragging)
        {
            DrawCircle(dragStart.x, dragStart.y, 5, GREEN);
            DrawLine(dragStart.x, dragStart.y, dragCurrent.x, dragCurrent.y, GREEN);
        }
        
        //toggle trails
        if (IsKeyPressed(KEY_V))
        {
            TrailsColor = WHITE;
        }   
        if (IsKeyPressedRepeat(KEY_V))
        {
            TrailsColor = BLACK;
        }
        
        EndMode2D();

        // UI TEXT
        DrawText(TextFormat("Time Scale: %.5fx", timeScale), 20, 20, 20, WHITE);

        DrawText("CONTROLS:", 20, 60, 20, GRAY);
        DrawText("+ / - : Change Time", 20, 90, 20, GRAY);
        DrawText("SPACE : Pause", 20, 120, 20, GRAY);
        DrawText("WASD : Move Camera", 20, 150, 20, GRAY);
        DrawText("Mouse Wheel : Zoom", 20, 180, 20, GRAY);
        DrawText("Drag Mouse : Spawn Object", 20, 210, 20, GRAY);
        DrawText("C : Circular Orbit Assist", 20, 240, 20, GRAY);
        DrawText("E : Elliptical Orbit Assist", 20, 270, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
}