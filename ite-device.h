#ifndef __ITE_DEVICE_H_
#define __ITE_DEVICE_H_

#include <libusb-1.0/libusb.h>

#include "quadrant.h"

class ITEDevice
{
    public:
        ITEDevice(libusb_context *ctx);
        ~ITEDevice();
        void setColour(ITEQuadrant quadrant, uint8_t red,
                       uint8_t green, uint8_t blue);

    private:
        libusb_device_handle *handle;

};


#endif // __ITE_DEVICE_H_
