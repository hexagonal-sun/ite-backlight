#include <libusb-1.0/libusb.h>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <getopt.h>
#include <string>
#include <boost/algorithm/string.hpp>

#include "ite-device.h"

void usage(const char *progname)
{
    std::cerr << "Usage: " << progname << " [-r] COLOUR COLOUR COLOUR COLOUR\n";
    std::cerr << "\n";
    std::cerr << "Set the provided colours across the keyboard in the\n";
    std::cerr << "respective order: far left, left, right, far right.\n";
    std::cerr << "\n";
    std::cerr << "-r: When set continually read COLOURs from STDIN and set\n";
    std::cerr << "    after each newline.  When -r is specified no COLOURs\n";
    std::cerr << "    should be specified.\n";
    std::cerr << "\n";
    Colour::printUsage(std::cerr);
}

void setStaticColours(ITEDevice &device,
                      const std::string &c1,
                      const std::string &c2,
                      const std::string &c3,
                      const std::string &c4)
{
    Colour colour_fl(c1);
    Colour colour_l (c2);
    Colour colour_r (c3);
    Colour colour_fr(c4);

    device.setStaticStyle({colour_fl, colour_l,
                           colour_r, colour_fr}, ITEBrightness::VERY_BRIGHT);

}

int main(int argc, char *argv[])
{
    libusb_context *ctx;
    bool readFromStdin = false;


    while (true) {
        const auto opt = getopt(argc, argv, "r");

        if (opt == -1)
            break;

        switch (opt) {
            case 'r':
                readFromStdin = true;
                break;
            default: /* '?' */
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!readFromStdin && argc - optind != 4) {
        std::cerr << "Error: expected exactly four colours.\n";
        usage(argv[0]);
        return 1;
    }

    auto ret = libusb_init(&ctx);

    if (ret != 0) {
        std::cerr << "could not initalize USB library: "
                  << libusb_strerror((libusb_error)ret) << "\n";

        return -1;
    }

    auto const ctxDelete = gsl::finally([&ctx]() {
        libusb_exit(ctx);
    });

    try {
        ITEDevice iteDev(ctx);

        if (readFromStdin) {
            std::string line;
            while (std::getline(std::cin, line)) {
                std::vector<std::string> colours;

                boost::algorithm::trim(line);

                boost::algorithm::split(colours, line, boost::is_any_of(" "));

                if (colours.size() != 4)
                    std::cerr << "Warning string \"" << line << "\" does not specify four colours. Skipping\n";

                setStaticColours(iteDev,
                                 colours[0],
                                 colours[1],
                                 colours[2],
                                 colours[3]);
            }
        } else {
            setStaticColours(iteDev,
                             argv[optind],
                             argv[optind + 1],
                             argv[optind + 2],
                             argv[optind + 3]);
        }

    } catch (std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
        usage(argv[0]);
        return 1;
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
