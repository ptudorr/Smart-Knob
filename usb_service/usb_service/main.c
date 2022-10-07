/*
* Test suite program based of libusb-0.1-compat testlibusb
* Copyright (c) 2013 Nathan Hjelm <hjelmn@mac.ccom>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <stdio.h>
#include <string.h>
#include "libusb.h"
#include <time.h>
#include <Windows.h>

#define _POSIX_C_SOURCE 199309L

int verbose = 0;
char imageTransfer = 0,rec_trf = 0;

struct timeval t_zero = {.tv_sec = 0, .tv_usec = 00000};

static void print_endpoint_comp(const struct libusb_ss_endpoint_companion_descriptor* ep_comp)
{
	printf("      USB 3.0 Endpoint Companion:\n");
	printf("        bMaxBurst:           %u\n", ep_comp->bMaxBurst);
	printf("        bmAttributes:        %02xh\n", ep_comp->bmAttributes);
	printf("        wBytesPerInterval:   %u\n", ep_comp->wBytesPerInterval);
}

static void print_endpoint(const struct libusb_endpoint_descriptor* endpoint)
{
	int i, ret;

	printf("      Endpoint:\n");
	printf("        bEndpointAddress:    %02xh\n", endpoint->bEndpointAddress);
	printf("        bmAttributes:        %02xh\n", endpoint->bmAttributes);
	printf("        wMaxPacketSize:      %u\n", endpoint->wMaxPacketSize);
	printf("        bInterval:           %u\n", endpoint->bInterval);
	printf("        bRefresh:            %u\n", endpoint->bRefresh);
	printf("        bSynchAddress:       %u\n", endpoint->bSynchAddress);

	for (i = 0; i < endpoint->extra_length;) {
		if (LIBUSB_DT_SS_ENDPOINT_COMPANION == endpoint->extra[i + 1]) {
			struct libusb_ss_endpoint_companion_descriptor* ep_comp;

			ret = libusb_get_ss_endpoint_companion_descriptor(NULL, endpoint, &ep_comp);
			if (LIBUSB_SUCCESS != ret)
				continue;

			print_endpoint_comp(ep_comp);

			libusb_free_ss_endpoint_companion_descriptor(ep_comp);
		}

		i += endpoint->extra[i];
	}
}

static void print_altsetting(const struct libusb_interface_descriptor* interface)
{
	uint8_t i;

	printf("    Interface:\n");
	printf("      bInterfaceNumber:      %u\n", interface->bInterfaceNumber);
	printf("      bAlternateSetting:     %u\n", interface->bAlternateSetting);
	printf("      bNumEndpoints:         %u\n", interface->bNumEndpoints);
	printf("      bInterfaceClass:       %u\n", interface->bInterfaceClass);
	printf("      bInterfaceSubClass:    %u\n", interface->bInterfaceSubClass);
	printf("      bInterfaceProtocol:    %u\n", interface->bInterfaceProtocol);
	printf("      iInterface:            %u\n", interface->iInterface);

	for (i = 0; i < interface->bNumEndpoints; i++)
		print_endpoint(&interface->endpoint[i]);
}

static void print_2_0_ext_cap(struct libusb_usb_2_0_extension_descriptor* usb_2_0_ext_cap)
{
	printf("    USB 2.0 Extension Capabilities:\n");
	printf("      bDevCapabilityType:    %u\n", usb_2_0_ext_cap->bDevCapabilityType);
	printf("      bmAttributes:          %08xh\n", usb_2_0_ext_cap->bmAttributes);
}

static void print_ss_usb_cap(struct libusb_ss_usb_device_capability_descriptor* ss_usb_cap)
{
	printf("    USB 3.0 Capabilities:\n");
	printf("      bDevCapabilityType:    %u\n", ss_usb_cap->bDevCapabilityType);
	printf("      bmAttributes:          %02xh\n", ss_usb_cap->bmAttributes);
	printf("      wSpeedSupported:       %u\n", ss_usb_cap->wSpeedSupported);
	printf("      bFunctionalitySupport: %u\n", ss_usb_cap->bFunctionalitySupport);
	printf("      bU1devExitLat:         %u\n", ss_usb_cap->bU1DevExitLat);
	printf("      bU2devExitLat:         %u\n", ss_usb_cap->bU2DevExitLat);
}

static void print_bos(libusb_device_handle* handle)
{
	struct libusb_bos_descriptor* bos;
	uint8_t i;
	int ret;

	ret = libusb_get_bos_descriptor(handle, &bos);
	if (ret < 0)
		return;

	printf("  Binary Object Store (BOS):\n");
	printf("    wTotalLength:            %u\n", bos->wTotalLength);
	printf("    bNumDeviceCaps:          %u\n", bos->bNumDeviceCaps);

	for (i = 0; i < bos->bNumDeviceCaps; i++) {
		struct libusb_bos_dev_capability_descriptor* dev_cap = bos->dev_capability[i];

		if (dev_cap->bDevCapabilityType == LIBUSB_BT_USB_2_0_EXTENSION) {
			struct libusb_usb_2_0_extension_descriptor* usb_2_0_extension;

			ret = libusb_get_usb_2_0_extension_descriptor(NULL, dev_cap, &usb_2_0_extension);
			if (ret < 0)
				return;

			print_2_0_ext_cap(usb_2_0_extension);
			libusb_free_usb_2_0_extension_descriptor(usb_2_0_extension);
		}
		else if (dev_cap->bDevCapabilityType == LIBUSB_BT_SS_USB_DEVICE_CAPABILITY) {
			struct libusb_ss_usb_device_capability_descriptor* ss_dev_cap;

			ret = libusb_get_ss_usb_device_capability_descriptor(NULL, dev_cap, &ss_dev_cap);
			if (ret < 0)
				return;

			print_ss_usb_cap(ss_dev_cap);
			libusb_free_ss_usb_device_capability_descriptor(ss_dev_cap);
		}
	}

	libusb_free_bos_descriptor(bos);
}

static void print_interface(const struct libusb_interface* interface)
{
	int i;

	for (i = 0; i < interface->num_altsetting; i++)
		print_altsetting(&interface->altsetting[i]);
}

static void print_configuration(struct libusb_config_descriptor* config)
{
	uint8_t i;

	printf("  Configuration:\n");
	printf("    wTotalLength:            %u\n", config->wTotalLength);
	printf("    bNumInterfaces:          %u\n", config->bNumInterfaces);
	printf("    bConfigurationValue:     %u\n", config->bConfigurationValue);
	printf("    iConfiguration:          %u\n", config->iConfiguration);
	printf("    bmAttributes:            %02xh\n", config->bmAttributes);
	printf("    MaxPower:                %u\n", config->MaxPower);

	for (i = 0; i < config->bNumInterfaces; i++)
		print_interface(&config->interface[i]);
}

static void print_device(libusb_device* dev, libusb_device_handle* handle)
{
	struct libusb_device_descriptor desc;
	unsigned char string[256];
	const char* speed;
	int ret;
	uint8_t i;

	switch (libusb_get_device_speed(dev)) {
	case LIBUSB_SPEED_LOW:		speed = "1.5M"; break;
	case LIBUSB_SPEED_FULL:		speed = "12M"; break;
	case LIBUSB_SPEED_HIGH:		speed = "480M"; break;
	case LIBUSB_SPEED_SUPER:	speed = "5G"; break;
	case LIBUSB_SPEED_SUPER_PLUS:	speed = "10G"; break;
	default:			speed = "Unknown";
	}

	ret = libusb_get_device_descriptor(dev, &desc);
	if (ret < 0) {
		fprintf(stderr, "failed to get device descriptor");
		return;
	}

	printf("Dev (bus %u, device %u): %04X - %04X speed: %s\n",
		libusb_get_bus_number(dev), libusb_get_device_address(dev),
		desc.idVendor, desc.idProduct, speed);

	if (!handle)
		libusb_open(dev, &handle);

	if (handle) {
		if (desc.iManufacturer) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, string, sizeof(string));
			if (ret > 0)
				printf("  Manufacturer:              %s\n", (char*)string);
		}

		if (desc.iProduct) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
			if (ret > 0)
				printf("  Product:                   %s\n", (char*)string);
		}

		if (desc.iSerialNumber && verbose) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
			if (ret > 0)
				printf("  Serial Number:             %s\n", (char*)string);
		}
	}

	if (verbose) {
		for (i = 0; i < desc.bNumConfigurations; i++) {
			struct libusb_config_descriptor* config;

			ret = libusb_get_config_descriptor(dev, i, &config);
			if (LIBUSB_SUCCESS != ret) {
				printf("  Couldn't retrieve descriptors\n");
				continue;
			}

			print_configuration(config);

			libusb_free_config_descriptor(config);
		}

		if (handle && desc.bcdUSB >= 0x0201)
			print_bos(handle);
	}

	if (handle)
		libusb_close(handle);
}


void fail(int e, int line) { 
	if (e >= 0)return; 
	printf("%d@%d-%s-%s", e, line, libusb_error_name(e), libusb_strerror(e));
	exit(EXIT_FAILURE);
}


uint32_t benchPackets = 1;
uint32_t benchBytes = 0;
struct timespec t1, t2;
uint32_t diff = 0;


struct libusb_transfer* transfer_hap_in = NULL;
struct libusb_transfer* transfer_led_out = NULL;
struct libusb_transfer* transfer_hap_out = NULL;
struct libusb_transfer* dsp_dsp_out = NULL;
unsigned char buf[64],buf2[64],buf3[64], bufout[65] = {0xff,0xff,0xff};

int par = 0,nr_hap_in=0,nr_hap_out=0,nr_led_out=0,nr_dsp_out=0;

void cb_HAP_IN(struct libusb_transfer* transfer)
{
	nr_hap_in++;
	//submit the next transfer
	libusb_submit_transfer(transfer_hap_in);
	
	benchBytes += transfer->actual_length;
	//this averages the bandwidth over many transfers
	if (++benchPackets % 20 == 0) {
		par = 1 - par;
		diff = (t2.tv_sec - t1.tv_sec) * 1000000000L + (t2.tv_nsec - t1.tv_nsec);
		t1.tv_sec = t2.tv_sec;
		t1.tv_nsec = t2.tv_nsec;
		printf("\rreceived %4d transfers and %4d bytes in %4d us, %4.1f B/s|%02x;   h_in:%d;h_out:%d;l_out:%d;d_out:%d", 
			benchPackets, benchBytes, diff / 1000, benchBytes * 1000000.0 / (diff / 1000),buf2[0],nr_hap_in,nr_hap_out,nr_led_out,nr_dsp_out);
		fflush(stdout);
		benchPackets = 0;
		benchBytes = 0;
	}
}
void cb_LED_OUT(struct libusb_transfer* transfer)
{
	nr_led_out++;
	buf2[48] = (clock() / 1000 % 2) ? 0x97 : 0x99;
	libusb_submit_transfer(transfer_led_out);

}
void cb_DSP_OUT(struct libusb_transfer* transfer)
{
	nr_dsp_out++;
	libusb_submit_transfer(dsp_dsp_out);

}
void cb_HAP_OUT(struct libusb_transfer* transfer)
{
	nr_hap_out++;
	libusb_submit_transfer(transfer_hap_out);
}

void start_HAP_IN(libusb_device_handle* devh, uint8_t USB_ENDPOINT_IN) {
	transfer_hap_in = libusb_alloc_transfer(0);
	libusb_fill_interrupt_transfer(transfer_hap_in, devh, USB_ENDPOINT_IN,
		buf, 64,  // Note: in_buffer is where input data written.
		cb_HAP_IN, NULL, 0); // no user data
	libusb_submit_transfer(transfer_hap_in);
}
void start_LED_OUT(libusb_device_handle* devh, uint8_t USB_ENDPOINT_OUT) {
	transfer_led_out = libusb_alloc_transfer(0);
	libusb_fill_interrupt_transfer(transfer_led_out, devh, USB_ENDPOINT_OUT,
		buf2, 49,  // Note: in_buffer is where input data written.
		cb_LED_OUT, NULL, 0); // no user data
	int r = libusb_submit_transfer(transfer_led_out);
}
void start_DSP_OUT(libusb_device_handle* devh, uint8_t USB_ENDPOINT_OUT) {
	dsp_dsp_out = libusb_alloc_transfer(0);
	libusb_fill_interrupt_transfer(dsp_dsp_out, devh, USB_ENDPOINT_OUT,
		buf3, 64,  // Note: in_buffer is where input data written.
		cb_DSP_OUT, NULL, 0); // no user data
	int r = libusb_submit_transfer(dsp_dsp_out);
}

void start_HAP_OUT(libusb_device_handle* devh, uint8_t USB_ENDPOINT_OUT) {
	transfer_hap_out = libusb_alloc_transfer(0);
	libusb_fill_interrupt_transfer(transfer_hap_out, devh, USB_ENDPOINT_OUT,
		bufout, 64,  // Note: in_buffer is where input data written.
		cb_HAP_OUT, NULL, 0); // no user data
	int r = libusb_submit_transfer(transfer_hap_out);
}


int main(int argc, char* argv[])
{
	libusb_device** devs;
	ssize_t cnt;
	int r;


	r = libusb_init(NULL);
	if (r < 0)
		return r;

	libusb_device *knob = NULL;
	struct libusb_device_descriptor desc;
	static libusb_context* ctx = NULL;
	
	cnt = libusb_get_device_list(NULL, &devs); fail(cnt, __LINE__);
	if (cnt < 0) {
		libusb_exit(NULL);
		return 1;
	}
	for (int i = 0; devs[i]; i++) {
		cnt = libusb_get_device_descriptor(devs[i], &desc); fail(cnt,__LINE__);

		if (desc.idProduct == 0x0005E && desc.idVendor == 0x04D8) {
				printf("BAA!!%x\n",desc.bDeviceClass);
			char prd[256];
			libusb_device_handle *handle;
			cnt = libusb_open(devs[i], &handle); fail(cnt, __LINE__);
			int ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, prd, sizeof(prd));
			if (1 || ret > 0 && strcmp("Smart Knob", prd) == 0) {
				knob = devs[i];
				libusb_ref_device(devs[i]);
			}

			libusb_close(handle);
		}
		
	}
	libusb_free_device_list(devs, 1);
	if (knob == NULL) {
		libusb_exit(NULL);
		return 1;
	}
	print_device(knob,NULL);
	libusb_device_handle* handle;
	cnt = libusb_open(knob, &handle);fail(cnt, __LINE__);

	struct libusb_config_descriptor* config;
	printf("getconfig: %d\n", libusb_get_config_descriptor(knob, 0, &config));

	print_configuration(config);


	cnt = libusb_claim_interface(handle, 0);fail(cnt, __LINE__);
	cnt = libusb_claim_interface(handle, 1);fail(cnt, __LINE__);
	cnt = libusb_claim_interface(handle, 2);fail(cnt, __LINE__);


	uint8_t adr_HAP_IN  = config->interface[0].altsetting[0].endpoint[0].bEndpointAddress;
	uint8_t adr_HAP_OUT = config->interface[0].altsetting[0].endpoint[1].bEndpointAddress;
	uint8_t adr_LED_OUT = config->interface[1].altsetting[0].endpoint[1].bEndpointAddress;
	uint8_t adr_DSP_OUT = config->interface[2].altsetting[0].endpoint[1].bEndpointAddress;
	

	start_HAP_OUT(handle, adr_HAP_OUT);
	start_HAP_IN(handle, adr_HAP_IN);
	start_LED_OUT(handle, adr_LED_OUT);
	start_DSP_OUT(handle, adr_DSP_OUT);
	while (1) {
		if (!imageTransfer) {
			Sleep(1);
		}
		bufout[2] = clock() / 1000;
		
		r = libusb_handle_events_timeout_completed(ctx, &t_zero, NULL);

		
		if (r < 0) {   // negative values are errors
			break;
		}
	}



	

	libusb_free_config_descriptor(config);
	libusb_release_interface(handle, 0);
	libusb_release_interface(handle, 1);
	libusb_close(handle);
	libusb_unref_device(knob);
	libusb_exit(NULL);
	return r;
}
