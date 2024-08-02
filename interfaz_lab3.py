# Interfaz gráfica lab 3 

import serial
import tkinter as tk

class App:
    def __init__(self, master):
        self.master = master
        self.master.title("SPI Potentiometer Values")
        self.master.geometry("300x200")

        self.ser = serial.Serial('COM4', 9600, timeout=1)

        self.pot1_label = tk.Label(master, text="Potentiometer 1:")
        self.pot1_label.pack()

        self.pot1_value = tk.Label(master, text="0")
        self.pot1_value.pack()

        self.pot2_label = tk.Label(master, text="Potentiometer 2:")
        self.pot2_label.pack()

        self.pot2_value = tk.Label(master, text="0")
        self.pot2_value.pack()

        self.counter_label = tk.Label(master, text="Set Counter:")
        self.counter_label.pack()

        self.counter_entry = tk.Entry(master)
        self.counter_entry.pack()

        self.set_button = tk.Button(master, text="Set", command=self.set_counter)
        self.set_button.pack()

        self.update_values()

    def update_values(self):
        if self.ser.in_waiting >= 2:
            pot1 = self.ser.read()
            pot2 = self.ser.read()
            self.pot1_value.config(text=str(ord(pot1)))
            self.pot2_value.config(text=str(ord(pot2)))

        self.master.after(100, self.update_values)

    def set_counter(self):
        counter_value = self.counter_entry.get()
        try:
            value = int(counter_value)
            if 0 <= value <= 255:
                self.ser.write(bytes([value]))
            else:
                print("Enter a value between 0 and 255")
        except ValueError:
            print("Please enter a valid integer")

root = tk.Tk()
app = App(root)
root.mainloop()
