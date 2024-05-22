import hid

vid = 0x0483
pid = 0x5750

h = hid.Device(vid,pid)

print("Manufacturer: %s" % h.get_manufacturer_string())
print("Product: %s" % h.get_product_string())
print("Serial No: %s" % h.get_serial_number_string())

h.set_nonblocking()
print("reach before loop")

while True:
    print("in loop")
    d = h.read(24)
    if d:
        print(d)
    else:
        break
print("closing device")
h.close()

