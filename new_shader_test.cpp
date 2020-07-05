#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

using namespace std;
using namespace sf;

using FrameTime = float;

static const string shaderCode = \
"uniform vec2 frag_LightOrigin;"\
"uniform vec3 frag_LightColor;"\
"uniform float frag_LightAttenuation;"\
"uniform vec2 frag_ScreenResolution;"\
"void main(){"\
"       vec2 baseDistance =  gl_FragCoord.xy;"\
"       baseDistance.y = frag_ScreenResolution.y-baseDistance.y;"\
"       vec2 distance=frag_LightOrigin - baseDistance;"\
"       float linear_distance = length(distance);"\
"       float attenuation=1.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);"\
"       vec4 lightColor = vec4(frag_LightColor, 1.0);"\
"       vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor; gl_FragColor=color;}";


static const unsigned int windowWidth{ 800 }, windowHeight{ 600 };

static const float walkerWidth{ 8.f }, walkerHeight{ 8.f };
static const float walkerVelocity{ 1.f };

static const float ftStep{ 1.f }, ftSlice{ 1.f };

static const int walkerCount{ 15 };

static const float directionMultiplier1{ 0.008f }, directionMultiplier2{ 0.002f };

static float directionMultiplier{ 0.008f };

/* UTILITY FUNCTIONS */

void normalize(Vector2f& source){
        float length = ((source.x * source.x) + (source.y * source.y));
        if (length != 0){
                source.x = source.x / length;
                source.y = source.y / length;
        }
}

/* GAME CLASSES */

struct Rectangle {
        RectangleShape shape;
        float x()      const _NOEXCEPT{ return shape.getPosition().x; }
        float y()      const _NOEXCEPT{ return shape.getPosition().y; }
        float left()   const _NOEXCEPT{ return x() - shape.getSize().x / 2.0f; }
        float right()  const _NOEXCEPT{ return x() + shape.getSize().x / 2.0f; }
        float top()    const _NOEXCEPT{ return y() - shape.getSize().y / 2.0f; }
        float bottom() const _NOEXCEPT{ return y() + shape.getSize().y / 2.0f; }
};


struct Walker : public Rectangle{

        Vector2f velocity;
        Vector3f color;

        Walker(float mX, float mY){
                shape.setPosition(mX, mY);
                shape.setSize({ walkerWidth, walkerHeight });
                color = Vector3f(rand() % 255, rand() % 255, rand() % 255);
                shape.setFillColor(Color(color.x, color.y, color.z));
                shape.setOrigin(walkerWidth / 2.0f, walkerHeight / 2.0f);
        }

        void update(FrameTime ft, RenderWindow& window){

                Vector2f mousePosition = (Vector2f)Mouse::getPosition(window);

                //follow mouse if it is inside of the window
                if (mousePosition.x > 0.f && mousePosition.y > 0.f &&
                        mousePosition.x < windowWidth && mousePosition.y < windowHeight){

                        Vector2f direction = mousePosition - shape.getPosition();

                        normalize(direction);

                        direction *= directionMultiplier;
                        direction.x += generateVelocityFloat() * 0.05;
                        direction.y += generateVelocityFloat() * 0.05;

                        velocity += direction;

                        //limit velocity
                        if(velocity.x > walkerVelocity) velocity.x = walkerVelocity;
                        if(velocity.y > walkerVelocity) velocity.y = walkerVelocity;
                        if(velocity.x < -walkerVelocity) velocity.x = -walkerVelocity;
                        if(velocity.y < -walkerVelocity) velocity.y = -walkerVelocity;

                } else {
                        if (( 1 + rand() % 100) == 1){
                                velocity.x = generateVelocityFloat();
                                velocity.y = generateVelocityFloat();
                        }
                }

                //guard edges of screen
                if ((right() >= windowWidth && velocity.x > 0) || (left() <= 0 && velocity.x < 0)){
                        velocity.x = 0;
                }
                if ((top() <= 0 && velocity.y < 0) || (bottom() >= windowHeight && velocity.y > 0)){
                        velocity.y = 0;
                }

                shape.move(velocity * ft);
        }

        float generateVelocityFloat(){
                return (-walkerVelocity) +static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (walkerVelocity - (-walkerVelocity))));
        }
};

struct Game {

        RenderWindow window{ VideoMode(windowWidth, windowHeight) , "Followers!" };
        FrameTime lastFt{ 0.f }, currentSlice{ 0.f };
        bool running{ false };

        RenderTexture myRenderTexture;
    Sprite spriteWorld;
        Shader shader;

        vector<Walker> walkers;

        void initializeWalkers(){
                walkers.clear();
                for (int a{ 0 }; a < walkerCount; ++a){
                        walkers.emplace_back(windowWidth / 2.f,
                                windowHeight/2.f);
                }
        }

        void checkInput(){
                Event event;
                while (window.pollEvent(event)) {
                        if (event.type == Event::Closed){
                                window.close();
                                break;
                        }
                        if (event.type == Event::MouseButtonPressed){
                                if (directionMultiplier == directionMultiplier1){
                                        directionMultiplier = directionMultiplier2;
                                }
                                else {
                                        directionMultiplier = directionMultiplier1;
                                }
                        }
				    if (event.type == sf::Event::KeyPressed) {
					    running = false;
				    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Escape)) running = false;

        }

        void update(){
                        currentSlice += lastFt;

                        //update multiple times based on fps
                        for (; currentSlice >= ftSlice; currentSlice -= ftSlice){

                                for (auto& walker : walkers){
                                        walker.update(ftStep, window);
                                }

                        }
        }

        void draw(){
                for (auto& walker : walkers){

                        myRenderTexture.draw(walker.shape);

                        shader.setParameter("frag_LightOrigin", walker.shape.getPosition());
                shader.setParameter("frag_LightColor", walker.color);
                shader.setParameter("frag_LightAttenuation", 50);

                sf::RenderStates states;
                states.shader = &shader;
                states.blendMode = sf::BlendAdd;

                myRenderTexture.draw(spriteWorld, states);

                }

                myRenderTexture.display();
        window.draw(spriteWorld);
                window.display();
        }


        void run(){

                myRenderTexture.create(windowWidth, windowHeight);
            spriteWorld.setTexture(myRenderTexture.getTexture());
        spriteWorld.setOrigin(spriteWorld.getTextureRect().width/2, spriteWorld.getTextureRect().height/2);
        spriteWorld.setPosition(windowWidth / 2, windowHeight / 2);

        shader.loadFromMemory(shaderCode, sf::Shader::Fragment);
        shader.setParameter("frag_ScreenResolution",sf::Vector2f(windowWidth, windowHeight));

                running = true;

                while (running) {

                        auto time1(chrono::high_resolution_clock::now());

                        window.clear(Color::Black);
                        myRenderTexture.clear();

                        checkInput();
                        update();
                        draw();

                        auto time2(chrono::high_resolution_clock::now());
                        auto elapsedTime(time2 - time1);
                        FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(elapsedTime).count() };

                        lastFt = ft;

                        auto ftSeconds(ft / 1000.f);
                        if (ftSeconds > 0.f){
                                auto fps(1.f / ftSeconds);
                                window.setTitle("FT: " + to_string(ft) + "\tFPS: " + to_string(fps));
                        }
                }
        }


        Game(){

                //framerate now handled by chrono library
                //to test with low framerate:
                //window.setFramerateLimit(15);
                window.setFramerateLimit(500);
                initializeWalkers();

        }
};


int main() {
        Game{}.run();
        return 0;
}
