/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 hathach for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SHARED_MODULE_USB_HID_DEVICE_H
#define SHARED_MODULE_USB_HID_DEVICE_H

#include <stdint.h>
#include <stdbool.h>

#include "py/obj.h"
#include "py/objint.h"

typedef struct  {
    mp_obj_base_t base;
    // Python buffer object whose contents are the descriptor.
    const uint8_t *report_descriptor;
    uint8_t *in_report_buffers[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint8_t *out_report_buffers[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint8_t out_report_buffers_updated[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint16_t report_descriptor_length;
    uint8_t report_ids[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint8_t in_report_lengths[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint8_t out_report_lengths[CIRCUITPY_USB_HID_MAX_REPORT_IDS_PER_DESCRIPTOR];
    uint16_t usage_page;
    uint16_t usage;
    uint8_t num_report_ids;
    uint8_t flags:4;    // currently there are only 3 flags, so 4 bits should be enough for now
    uint8_t hid_idx:4;  // MAX_HID_DEVICES=8, so 4 bits are enough even if someone wants to double max count
} usb_hid_device_obj_t;

extern usb_hid_device_obj_t usb_hid_device_keyboard_obj;
extern usb_hid_device_obj_t usb_hid_device_mouse_obj;
extern const usb_hid_device_obj_t usb_hid_device_consumer_control_obj;

#define USB_HID_DEVICE_FLAG_BOOT            (0x1)
#define USB_HID_DEVICE_FLAG_BOOT_REQUESTED  (0x2)
#define USB_HID_DEVICE_FLAG_STANDALONE      (0x4)

void usb_hid_device_create_report_buffers(usb_hid_device_obj_t *self);

#endif /* SHARED_MODULE_USB_HID_DEVICE_H */
