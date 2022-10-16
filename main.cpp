#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <csignal>
#include <argparse.hpp>
#include <filesystem>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

bool stopped{false};
const std::string default_markers{"   .,:;i80@"};

class Converter
{
public:
    Converter(int _width = 100, std::string _markers = default_markers, int _brightness = 0, double _contrast = 1.0)
    {
        width = _width;
        markers = _markers;
        brightness = _brightness;
        contrast = _contrast;
    }
    std::string &convert(cv::Mat &_img)
    {
        result = "";
        process_img(_img);
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                result += map((img.at<unsigned char>(i, j) * contrast + brightness));
            }
            result += '\n';
        }
        return result;
    }
    template <class Duration>
    void spin_renderer(int video_indx = 0, Duration time = 100us)
    {
        cv::VideoCapture video{video_indx};
        if (!video.isOpened())
        {
            std::cerr << "ERROR! Unable to open camera\n";
            std::exit(1);
        }
        cv::Mat _img;
        std::cout << top_margin;
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

    void render(cv::Mat &_img)
    {
        convert(_img);
        std::cout << result << std::endl;
    }

private:
    std::string markers;
    uint8_t pixle_max{255};
    int width;
    int brightness;
    float contrast;
    float scale_factor;
    cv::Mat img, bw;
    std::string result;
    std::string top_margin{"\n\n\n"};

    char map(unsigned char intensity)
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
    void process_img(cv::Mat &_img)
    {
        cv::cvtColor(_img, bw, cv::COLOR_RGB2GRAY);
        scale_factor = float(width) / bw.cols;
        cv::resize(bw, img, cv::Size(0, 0), scale_factor * 2.0, scale_factor);
    }
    void zero_cursor()
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << "\e[A";
        }
        std::cout << top_margin;
    }
    void reset_cursor()
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << "\e[B";
        }
        std::cout << top_margin;
    }
};

void sig_handler(int _)
{
    stopped = true;
}
int main(int argc, char **argv)
{
    argparse::ArgumentParser program("terimg", "0.0.1");

    program.add_argument("--width", "-w")
        .default_value(100)
        .help("number of chars in a row of the output string")
        .scan<'d', int>();
    program.add_argument("--brightness", "-b")
        .default_value(0)
        .help("Number between 0-255 by which pixel intensities are incremented")
        .scan<'d', int>();
    program.add_argument("--contrast", "-c")
        .default_value(1.0)
        .help("Float number defining contrast. 1.0 is no change in contrast, "
              "0.5 decrease 50%, and 1.5 increase by 150%")
        .scan<'g', double>();
    program.add_argument("--text", "-t")
        .default_value(default_markers)
        .help("characters used in rendering the images. Ordered from darkest to brightest");
    program.add_argument("--path", "-p")
        .default_value(std::string{""})
        .help("Image input path. If not given, it will read from the video device");
    program.add_argument("--video", "-i")
        .default_value(0)
        .help("Index of video device (used in video device mode when image path is not given")
        .scan<'d', int>();

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::signal(SIGINT, sig_handler);
    const fs::path img_path(program.get<std::string>("--path"));
    Converter convr(program.get<int>("--width"),
                    program.get<std::string>("--text"),
                    program.get<int>("--brightness"), program.get<double>("--contrast"));
    if (img_path.string() == "")
    {
        convr.spin_renderer(program.get<int>("--video"), 100us);
        return 0;
    }

    if (!fs::exists(img_path))
    {
        std::cerr << "Image not found!\nPlease check the given image path" << std::endl;
        std::exit(1);
    }
    auto img = cv::imread(img_path.string());
    convr.render(img);

    return 0;
}
