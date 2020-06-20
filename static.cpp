#include <libusb-1.0/libusb.h>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ite-device.h"

void usage(const char *progname)
{
    std::cerr << "Usage: " << progname << " COLOUR COLOUR COLOUR COLOUR\n";
    std::cerr << "\n";
    std::cerr << "Set the provided colours across the keyboard in the\n";
    std::cerr << "respective order: far left, left, right, far right.\n";
    std::cerr << "\n";
    Colour::printUsage(std::cerr);
}

int main(int argc, char *argv[])
{
    libusb_context *ctx;

    if (argc != 5) {
        std::cerr << "Error: expected exactly four arguments.\n";
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
        Colour colour_fl(argv[1]);
        Colour colour_l(argv[2]);
        Colour colour_r(argv[3]);
        Colour colour_fr(argv[4]);

        iteDev.setStaticStyle({colour_fl, colour_l,
                               colour_r, colour_fr}, ITEBrightness::VERY_BRIGHT);

    } catch (std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
        usage(argv[0]);
        return 1;
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
