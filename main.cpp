#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main(int argc, char** argv)
{
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 9.8f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(250.0f, 480.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(100.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(250.0f, 250.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(25.0f, 25.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    sf::RenderWindow window(sf::VideoMode(1024, 500), "WHUT");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Blue);
    sf::RectangleShape fl(sf::Vector2f(500, 10));
    fl.setPosition(groundBody->GetPosition().x,groundBody->GetPosition().y+15.0f);
    fl.setRotation(groundBody->GetAngle());

    // This is our little game loop.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        shape.setPosition(position.x, position.y);
        shape.setRotation(angle);

        window.draw(shape);
        window.draw(fl);
        window.display();
    }

    return 0;
}