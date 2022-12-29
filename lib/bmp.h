#include <iostream>
#include <vector>
#include <fstream>


struct Color {
    float r;
    float g;
    float b;

    Color();
    Color(float r, float g, float b);
    ~Color();


    static Color white() {
        return Color(255, 255, 255);
    }
    static Color green() {
        return Color(0,   255,   0);
    }
    static Color magenta() {
        return Color(255,   0, 255);
    }
    static Color yellow() {
        return Color(255, 255,   0);
    }
    static Color black() {
        return Color(0,   0,     0);
    }

};

class Image
{
public:
    Image(int width, int height);
    ~Image() = default;

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Export(const std::string& path) const;

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};