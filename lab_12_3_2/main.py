import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import ctypes
import os

# Путь к библиотеке по умолчанию
LIB_PATH = "./libarr.so"

# Основное окно
class MainApplication:
    def __init__(self, root):
        self.root = root
        self.root.title("Ctypes")

        # Ввод пути к библиотеке
        self.lib_path_label = tk.Label(root, text="Путь к библиотеке:")
        self.lib_path_label.pack()

        self.lib_path_entry = tk.Entry(root)
        self.lib_path_entry.insert(0, LIB_PATH)
        self.lib_path_entry.pack()
        
        self.mem_var = tk.StringVar()
        self.mem_var.set("Выделение с запасом")

        self.mem_label = ttk.Label(root, text="Выберите тип выделения памяти:")
        self.mem_label.pack()

        self.mem_menu = ttk.Combobox(root, values=["Выделение с запасом", "Рассчет, затем выделение"], textvariable=self.mem_var, state="readonly")
        self.mem_menu.pack()

        # Кнопка для открытия окна функции копирования
        self.input_array_button = tk.Button(root, text="Copy and add after even", command=self.open_input_array_window)
        self.input_array_button.pack()

        # Кнопка для открытия окна создания массива простых чисел
        self.create_primes_button = tk.Button(root, text="Create primes array", command=self.open_create_primes_window)
        self.create_primes_button.pack()
        
        # Кнопка для вывода информации
        self.info_button = tk.Button(root, text="Info", command=self.print_info)
        self.info_button.pack()
        
    def print_info(self):
        messagebox.showinfo("Info", f"Данная программа может создать массив заданной длины из простых чисел или вставить введенное число в введенном массиве после каждого четного числа")

    # Открытие окна функции копирования
    def open_input_array_window(self):
        lib_path = self.lib_path_entry.get()
        try:
            arr_lib = ctypes.CDLL(lib_path)
        except OSError as e:
            messagebox.showerror("Ошибка", f"Не удалось загрузить библиотеку: {e}")
            return
        
        ncpy_and_add = arr_lib.ncpy_and_add
        ncpy_and_add.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t), ctypes.c_int)
        ncpy_and_add.restype = ctypes.c_int
        
        old_geometry = root.geometry()
        old_width, old_height, old_x, old_y = map(int, old_geometry.split('+')[0].split('x') + old_geometry.split('+')[1:])
        
        new_x = old_x + old_width + 15
        new_y = old_y

        mem = self.mem_var.get()
        if (mem == "Выделение с запасом"):
            input_array_window = InputArrayWindow(self.root, ncpy_and_add, 1, new_x, new_y)
        else:
            input_array_window = InputArrayWindow(self.root, ncpy_and_add, 2, new_x, new_y)

    # Открытие окна создания массива простых чисел
    def open_create_primes_window(self):
        lib_path = self.lib_path_entry.get()
        try:
            arr_lib = ctypes.CDLL(lib_path)
        except OSError as e:
            messagebox.showerror("Ошибка", f"Не удалось загрузить библиотеку: {e}")
            return
        
        fill_primes = arr_lib.fill_primes
        fill_primes.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)
        
        old_geometry = root.geometry()
        old_width, old_height, old_x, old_y = map(int, old_geometry.split('+')[0].split('x') + old_geometry.split('+')[1:])
        
        new_x = old_x + old_width + 15
        new_y = old_y

        create_primes_window = CreatePrimesWindow(self.root, fill_primes, new_x, new_y)

# Окно функции копирования
class InputArrayWindow:
    def __init__(self, root, ncpy_and_add, mem_type, x, y):
        self.root = tk.Toplevel(root)
        self.root.title("Copy and add")
        self.root.geometry(f"300x200+{x}+{y}")

        self.ncpy_and_add = ncpy_and_add
        self.mem_type = mem_type

        # Ввод массива
        self.array_label = tk.Label(self.root, text="Введите массив (через пробел):")
        self.array_label.pack()

        self.array_entry = tk.Entry(self.root)
        self.array_entry.pack()

        # Ввод числа
        self.num_label = tk.Label(self.root, text="Введите число:")
        self.num_label.pack()

        self.num_entry = tk.Entry(self.root)
        self.num_entry.pack()

        # Кнопка для вызова функции ncpy_and_add
        self.submit_button = tk.Button(self.root, text="Выполнить", command=self.process_input_array)
        self.submit_button.pack()

    # Вызов функции ncpy_and_add
    def process_input_array(self):
        array_str = self.array_entry.get()
        try:
            num = int(self.num_entry.get())
        except ValueError:
            messagebox.showerror("Ошибка", "Неверное число")
            return

        try:
            array = list(map(int, array_str.split(' ')))
        except ValueError:
            messagebox.showerror("Ошибка", "Неверный формат массива")
            return

        arr_size = len(array)
        
        # Создание C-совместимого массива
        c_array = (ctypes.c_int * arr_size)()
        
        allocd_size = ctypes.c_size_t()
        
        if (self.mem_type == 1):
            allocd_size.value = arr_size * 2  # Достаточный размер для ncpy_and_add
        else:
            rc = self.ncpy_and_add(c_array, arr_size, None, 0, ctypes.byref(allocd_size), num)  # Рассчет нужного размера
            if rc:
                messagebox.showerror("Ошибка си", "Ошибка си: {rc}")
                return

        res_array = (ctypes.c_int * allocd_size.value)()

        # Заполнение C-совместимого массива
        for i in range(arr_size):
            c_array[i] = array[i]

        # Вызов функции ncpy_and_add
        result_size = ctypes.c_size_t()
        rc = self.ncpy_and_add(c_array, arr_size, res_array, allocd_size.value, ctypes.byref(result_size), num)
        if rc:
            messagebox.showerror("Ошибка си", f"Ошибка си: {rc}")
            return

        result_array = [res_array[i] for i in range(result_size.value)]

        messagebox.showinfo("Результат", f"Результат: {result_array}")

        self.root.destroy()

# Окно создания массива простых чисел
class CreatePrimesWindow:
    def __init__(self, root, fill_primes, x, y):
        self.root = tk.Toplevel(root)
        self.root.title("Create Primes Array")
        self.root.geometry(f"300x200+{x}+{y}")
        
        self.fill_primes = fill_primes

        # Ввод размера массива
        self.size_label = tk.Label(self.root, text="Введите размер массива:")
        self.size_label.pack()

        self.size_entry = tk.Entry(self.root)
        self.size_entry.pack()

        # Кнопка для вызова функции fill_primes
        self.submit_button = tk.Button(self.root, text="Выполнить", command=self.process_create_primes)
        self.submit_button.pack()

    # Вызов функции fill_primes
    def process_create_primes(self):
        try:
            size = int(self.size_entry.get())
        except ValueError:
            messagebox.showerror("Ошибка", "Неверный размер")
            return

        # Создание C-совместимого массива
        c_array = (ctypes.c_int * size)()

        # Вызов функции fill_primes
        self.fill_primes(c_array, size)

        result_array = [c_array[i] for i in range(size)]

        messagebox.showinfo("Результат", f"Результат: {result_array}")

        self.root.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = MainApplication(root)
    root.mainloop()
