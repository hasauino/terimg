#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <thread>

const std::string default_markers{"   .,:;i80@"};

class Converter
{
public:
    Converter(int width = 100, std::string markers = default_markers, int brightness = 0, double contrast = 1.0);
    std::string &convert(cv::Mat &_img);

    void spin_renderer(int video_indx = 0, std::chrono::duration<float> time = std::chrono::milliseconds(100));

    void render(cv::Mat &_img);
    static bool stopped;

private:
    std::string markers;
    const uint8_t pixle_max{255};
    int width;
    int brightness;
    float contrast;
    float scale_factor;
    cv::Mat img, bw;
    std::string result;
    const std::string top_margin{"\n\n\n"};

    unsigned char pixel_transform(unsigned char intensity);
    char map(unsigned char intensity);
    void process_img(cv::Mat &_img);
    void zero_cursor();
    void reset_cursor();
};