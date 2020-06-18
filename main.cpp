#include <libusb-1.0/libusb.h>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ite-device.h"

int main()
{
    libusb_context *ctx;

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

        for (const auto quadrant : allQuadrants)
            iteDev.setColour(quadrant, 0xff, 0, 0);

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
