#include <iostream>

class Player
{
private:
    int x_, y_;
    int width_, height_;
    float y_velocity_;

public:
    // getters and setters
    int &x() { return x_; };
    const int &x() const { return x_; };
    int &y() { return y_; };
    const int &y() const { return y_; };

    int &width() { return width_; };
    const int &width() const { return width_; };
    int &height() { return height_; };
    const int &height() const { return height_; };

    float &y_velocity() { return y_velocity_; };
    const float &y_velocity() const { return y_velocity_; };

    // methods
    void jump();
    bool on_platform(Level *level);
    bool hit_wall_left(Level *level);
    bool hit_wall_right(Level *level);
    void draw_player(SDL_Renderer *renderer);

    Player() : x_(0), y_(240), width_(10), height_(10), y_velocity_(1){};
    Player(int x_, int y_) : width_(10), height_(10), y_velocity_(1)
    {
        this->x_ = x_;
        this->y_ = y_;
    }
};