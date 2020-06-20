#include <libusb-1.0/libusb.h>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ite-device.h"

void usage(const char *progname)
{
    std::cerr << "Usage: " << progname << " COLOUR\n";
    std::cerr << "\n";
    std::cerr << "Set a single colour across the entire keyboard on an ITE device.\n";
    std::cerr << "\n";
    Colour::printUsage(std::cerr);
}

int main(int argc, char *argv[])
{
    libusb_context *ctx;

    if (argc != 2) {
        std::cerr << "Error: expected exactly one argument.\n";
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
        Colour colour(argv[1]);

        iteDev.setMonoColour(colour,
                             ITEBrightness::VERY_BRIGHT);

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
