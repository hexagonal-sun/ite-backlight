#include <libusb-1.0/libusb.h>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ite-device.h"

void usage(const char *progname)
{
    std::cerr << "Usage: " << progname << " SPEED COLOUR COLOUR COLOUR COLOUR COLOUR COLOUR COLOUR\n";
    std::cerr << "\n";
    std::cerr << "Fade the provided COLOURs in and out in a wave style with SPEED.\n";
    std::cerr << "\n";
    Colour::printUsage(std::cerr);
    Speed::printUsage(std::cerr);
}

int main(int argc, char *argv[])
{
    libusb_context *ctx;

    if (argc != 9) {
        std::cerr << "Error: expected exactly eight arguments.\n";
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

        iteDev.setWaveStyle({Colour{argv[2]},
                             Colour{argv[3]},
                             Colour{argv[4]},
                             Colour{argv[5]},
                             Colour{argv[6]},
                             Colour{argv[7]},
                             Colour{argv[8]},},
                            Speed{argv[1]},
                            ITEBrightness::VERY_BRIGHT);


    } catch (std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
        usage(argv[0]);
        return 1;
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
