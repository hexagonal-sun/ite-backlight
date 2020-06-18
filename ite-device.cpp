#include <gsl/gsl>

#include "ite-device.h"

ITEDevice::ITEDevice(libusb_context *ctx)
    : handle(nullptr)
{
    int ret;
    libusb_device **devices;

    auto count = libusb_get_device_list(ctx, &devices);
    auto const freeList = gsl::finally([&devices] {
        libusb_free_device_list(devices, 1);
    });

    for (int i = 0; i < count; i++)
    {
        libusb_device *dev = devices[i];
        libusb_device_descriptor desc;

        ret = libusb_get_device_descriptor(dev, &desc);

        if (ret != 0)
            throw std::runtime_error(std::string("could not get USB device descriptor: ") +
                                     libusb_strerror((libusb_error)ret));

        if (desc.idVendor == 0x048d && desc.idProduct == 0xce00) {
            ret = libusb_open(dev, &handle);

            if (ret != 0)
                throw std::runtime_error(std::string("could not open USB device: ")
                                         + libusb_strerror((libusb_error)ret));
        }
    }

    if (!handle)
        throw std::runtime_error("could not find backlight controller\n");
}

ITEDevice::~ITEDevice()
{
    libusb_close(handle);
}

void ITEDevice::setColour(ITEQuadrant quadrant, uint8_t red, uint8_t green, uint8_t blue)
{
    std::array<uint8_t, 8> msg =
        {0x14, 0x00, (uint8_t)quadrant, red, green, blue, 0x00, 0x00};

    auto ret = libusb_control_transfer(handle, 0x21, 9, 0x0300, 1,
                                       &msg[0], msg.size(), 1000);

    if (ret < 0)
        throw std::runtime_error(std::string("transfer failed: ") +
                                 libusb_strerror((libusb_error)ret));
}
