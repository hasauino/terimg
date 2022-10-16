#include <converter.hpp>

bool Converter::stopped = false;

Converter::Converter(int _width, std::string _markers, int _brightness, double _contrast)
{
    width = _width;
    markers = _markers;
    brightness = _brightness;
    contrast = _contrast;
}
std::string &Converter::convert(cv::Mat &_img)
{
    result = "";
    process_img(_img);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            result += map(pixel_transform(img.at<unsigned char>(i, j)));
        }
        result += '\n';
    }
    return result;
}

void Converter::spin_renderer(int video_indx, std::chrono::duration<float> time)
{
    cv::VideoCapture video{video_indx};
    if (!video.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
        std::exit(1);
    }
    cv::Mat _img;
    while (!stopped)
    {
        video >> _img;
        if (_img.empty())
        {
            std::cout << "Warning! blank frame grabbed\n";
            std::this_thread::sleep_for(time);
            continue;
        }
        render(_img);
        std::this_thread::sleep_for(time);
        zero_cursor();
    }
    reset_cursor();
}

void Converter::render(cv::Mat &_img)
{
    convert(_img);
    std::cout << result << std::endl;
}

unsigned char Converter::pixel_transform(unsigned char intensity)
{
    auto result = float(intensity) * contrast + brightness;
    if (result > pixle_max)
        return pixle_max;
    if (result < 0)
        return 0;
    return result;
}

char Converter::map(unsigned char intensity)
{

    if (intensity > pixle_max)
    {
        intensity = pixle_max;
    }
    if (intensity < 0)
    {
        intensity = 0;
    }

    auto index = (intensity * (markers.size() - 1)) / pixle_max;
    return markers[index];
}

void Converter::process_img(cv::Mat &_img)
{
    cv::cvtColor(_img, bw, cv::COLOR_RGB2GRAY);
    scale_factor = float(width) / bw.cols;
    cv::resize(bw, img, cv::Size(0, 0), scale_factor * 2.0, scale_factor);
}

void Converter::zero_cursor()
{
    for (int i = 0; i < width; i++)
    {
        std::cout << "\e[A";
    }
    std::cout << top_margin;
}
void Converter::reset_cursor()
{
    for (int i = 0; i < width; i++)
    {
        std::cout << "\e[B";
    }
    std::cout << top_margin;
}
