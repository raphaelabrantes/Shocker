import time
class Controller:
    BYTE_L2 = 9
    BYTE_R2 = BYTE_SIZE    = 8
    BIT_TRI = BIT_R3       = 7
    BIT_CIR = BIT_L3       = BYTE_SPECIALS = 6
    BIT_X   = BIT_OPT      = BYTE_BUTTONS  = 5
    BIT_SQR = BIT_SHARE    = BYTE_RIGHT_Y  = 4
    BIT_R2  = BYTE_RIGHT_X = 3
    BIT_L2  = BYTE_LEFT_Y  = 2
    BIT_R1  = BYTE_LEFT_X  = 1
    BIT_L1  = 0


    def __init__(self):
        pass

    def check_press(self, bytes):
        buttoms_byte = self.__normalize_bits(bytes[self.BYTE_BUTTONS], self.BYTE_SIZE)
        special_byte = self.__normalize_bits(bytes[self.BYTE_SPECIALS], self.BYTE_SIZE)
        print(bytes[self.BYTE_LEFT_X])
        if int(buttoms_byte[self.BIT_SQR]):
            print('□')
        if int(buttoms_byte[self.BIT_CIR]):
            print("◯")
        if int(buttoms_byte[self.BIT_X]):
            print("x")
        if int(buttoms_byte[self.BIT_TRI]):
            print("Δ")


    def __normalize_bits(self, bits, size):
        bits = bin(bits)
        norm = '0' * (size - len(bits[2:])) + bits[2:]
        return norm[::-1]


com = Controller()
with open('/dev/hidraw3', 'rb') as filename:
    while True:
        x = filename.read(64)
        com.check_press(x)

