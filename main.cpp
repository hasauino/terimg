#include <converter.hpp>

#include <argparse.hpp>
#include <csignal>
#include <filesystem>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

void sig_handler(int _)
{
    Converter::stopped = true;
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
        convr.spin_renderer(program.get<int>("--video"), 100ms);
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
