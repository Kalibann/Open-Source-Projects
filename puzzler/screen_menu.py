"""
 ============================================================================
 Name         : Puzzle-R
 Author       : Ramon Soares Mendes Meneses Leite
 Version      : 1.00
 E-mail:      : ramnsores1000@gmail.com
 University   : Universidade Federal de Goiás - Catalão GO
 Description  : Jogo de Quebra-Cabeça em Python
 Objective    : Por pura diversão
 ============================================================================
"""

import os
import tkinter as tk
import tkinter.filedialog as fdlg
from tkinter import messagebox
from tkinter import ttk
from PIL import Image
from puzzler import puzzle


class HomeScreen(object):

    def __init__(self, window):
        # Janela
        self.window = window
        self.font = ('Verdana', '36', 'bold')

        # Frames
        self.frame1_main = tk.Frame(window, bg='pink')
        self.frame2_main = tk.Frame(window, bg='white')

        self.frame1_add_image = tk.Frame(window, bg='black', pady=10)
        self.frame2_add_image = tk.Frame(window, bg='black')

        self.frame1_record = tk.Frame(window, bg='black')
        self.frame2_record = tk.Frame(window, bg='black')
        self.frame3_record = tk.Frame(window, bg='black')

        self.frame1_game_config = tk.Frame(window, bg='black')
        self.frame2_game_config = tk.Frame(window, bg='black')
        self.frame3_game_config = tk.Frame(window, bg='black')
        self.frame4_game_config = tk.Frame(window, bg='black')

        # Widgets main_menu
        self.title_main = tk.Label(self.frame1_main, text='Puzzle - R', fg='pink', bg='black', font='Times 40 bold')
        self.credits = tk.Label(self.frame1_main, text='Desenvolvido por Ramon Soares', fg='black', bg='white',
                                font='Times 10 bold')
        self.b1 = tk.Button(self.frame2_main, text='Jogar', bg='black', fg='pink', width=20, relief="groove", pady=5,
                            command=self.game_config)
        self.b2 = tk.Button(self.frame2_main, text='Adicionar Imagem', bg='black', fg='pink', width=20,
                            command=self.add_image, relief="groove", pady=5)
        self.b3 = tk.Button(self.frame2_main, text='Record', bg='black', fg='pink', width=20, relief="groove", pady=5,
                            command=self.record)
        self.b4 = tk.Button(self.frame2_main, text='Sair', bg='black', fg='pink', width=20, relief="groove", pady=5,
                            command=self.exit)

        # Widgets add_image
        self.lb_add_image = tk.Label(self.frame1_add_image, text='Importe uma imagem 800x600', bg='black', fg='pink',
                                     width=23, font='Times 12 bold')
        self.search_image = tk.Button(self.frame2_add_image, text='Procurar', width=10, relief="groove", bg='black',
                                      fg='pink', command=self.get_diretory_image)
        self.breset_image = tk.Button(self.frame2_add_image, text='Redefinir', width=10, relief="groove", bg='black',
                                      fg='pink', command=self.reset_image)
        self.back1_main = tk.Button(self.frame2_add_image, text='Voltar', width=10, relief="groove", bg='black',
                                    fg='pink', command=self.back_menu1)

        # Widgets record
        self.lb_record = tk.Label(self.frame1_record, text='Records', bg='black', fg='pink',
                                  width=23, font='Times 14 bold')
        self.tree = ttk.Treeview(self.frame2_record, height=14)
        self.tree_scroll = ttk.Scrollbar(self.frame2_record, orient="vertical", command=self.tree.yview)
        self.back2_main = tk.Button(self.frame3_record, text='Voltar', width=10, relief="groove", bg='black',
                                    fg='pink', command=self.back_menu2)
        self.tree.configure(yscrollcommand=self.tree_scroll.set)

        # Widgets game_config
        self.easy = tk.IntVar()
        self.normal = tk.IntVar()
        self.hard = tk.IntVar()
        self.images_available = [im for im in os.listdir("puzzler/puzzle_images/")]
        self.lb_name = tk.Label(self.frame1_game_config, text='Nome:', fg='pink', bg='black', font='Times 14 bold')
        self.entry_name = tk.Entry(self.frame1_game_config, width=20, font='Times 14', fg='black', bg='lightgray',
                                   justify=tk.CENTER)
        self.lb_CB = tk.Label(self.frame2_game_config, text='Puzzle:', fg='pink', bg='black', font='Times 9 bold')
        self.CB_puzzle = ttk.Combobox(self.frame2_game_config, width=20, values=self.images_available, state='readonly')
        self.cb1 = tk.Checkbutton(self.frame3_game_config, text='Fácil [1]', width=7, var=self.easy,
                                  command=self.checkbutton1)
        self.cb2 = tk.Checkbutton(self.frame3_game_config, text='Médio [2]', width=7, var=self.normal,
                                  command=self.checkbutton2)
        self.cb3 = tk.Checkbutton(self.frame3_game_config, text='Difícil [3]', width=7, var=self.hard,
                                  command=self.checkbutton3)
        self.start = tk.Button(self.frame4_game_config, text='Começar', bg='black', fg='pink', width=20,
                               relief="groove", pady=5, command=self.running_game)
        self.back3_main = tk.Button(self.frame4_game_config, text='Voltar', bg='black', fg='pink', width=20,
                                    relief="groove", pady=5, command=self.back_menu3)

    def running_game(self):

        player_name = self.entry_name.get()
        game_image = self.CB_puzzle.get()

        if self.easy.get():
            difficulty = 1
            row = 3
            column = 4
            cut_size = 200
            parts = 12
        elif self.normal.get():
            difficulty = 2
            row = 6
            column = 8
            cut_size = 100
            parts = 48
        else:
            difficulty = 3
            row = 12
            column = 16
            cut_size = 50
            parts = 192

        if len(player_name) == 0 or len(game_image) == 0:
            tk.messagebox.showinfo("Inválido", "Preencha todos os campos!")
        else:
            self.frame1_game_config.grid_forget()
            self.frame2_game_config.grid_forget()
            self.frame3_game_config.grid_forget()
            self.frame4_game_config.grid_forget()
            game = puzzle.Puzzle(player_name, game_image, difficulty, row, column, cut_size, parts)
            game.crop_image()
            game.load_images()
            game.randomize()
            win = game.puzzle_pygame()
            if win:
                self.main_menu()

    def main_menu(self):

        self.frame1_main.grid(row=3, pady=60, padx=65)
        self.frame2_main.grid(pady=30)
        self.title_main.grid()
        self.credits.grid(pady=5)
        self.b1.grid()
        self.b2.grid()
        self.b3.grid()
        self.b4.grid()

    def game_config(self):

        self.frame1_main.grid_forget()
        self.frame2_main.grid_forget()

        self.frame1_game_config.grid(pady=40, padx=80)
        self.frame2_game_config.grid(pady=20)
        self.frame3_game_config.grid()
        self.frame4_game_config.grid(pady=40)
        self.lb_name.grid()
        self.entry_name.grid()
        self.lb_CB.grid()
        self.CB_puzzle.grid()
        self.cb1.grid()
        self.cb2.grid()
        self.cb3.grid()
        self.start.grid()
        self.back3_main.grid()

        self.entry_name.delete(0, tk.END)
        self.entry_name.insert(0, "Player")
        self.cb1.select()
        self.CB_puzzle.current(0)

    def add_image(self):

        if not os.path.isdir("puzzler/puzzle_images"):
            os.mkdir("puzzler/puzzle_images")

        self.frame1_main.grid_forget()
        self.frame2_main.grid_forget()

        self.frame1_add_image.grid(pady=60, padx=65)
        self.frame2_add_image.grid()
        self.lb_add_image.grid()
        self.search_image.grid()
        self.breset_image.grid()
        self.back1_main.grid()

    def record(self):

        self.frame1_main.grid_forget()
        self.frame2_main.grid_forget()

        self.tree["columns"] = ("one", "two", "three")
        self.tree.column("#0", width=95, minwidth=80, stretch=tk.NO)
        self.tree.column("one", width=100, minwidth=80, stretch=tk.NO)
        self.tree.column("two", width=40, minwidth=40, stretch=tk.NO)
        self.tree.column("three", width=75, minwidth=40, stretch=tk.NO)
        self.tree.heading("#0", text="Nome", anchor=tk.W)
        self.tree.heading("one", text="Puzzle", anchor=tk.W)
        self.tree.heading("two", text="Nível", anchor=tk.W)
        self.tree.heading("three", text="Movimentos", anchor=tk.W)

        try:
            records = open("puzzler/config/records.txt", "r")
        except:
            records = open("puzzler/config/records.txt", "w")
            records.close()

        records_sort = []

        for row in records:
            records_split = row.split(",")
            records_split[0] = int(records_split[0])
            records_sort.append(records_split)

        records_sort.sort()

        for values in records_sort:
            self.tree.insert("", "end", text=values[1], values=(values[2], values[3], values[0]))

        records.close()

        self.frame1_record.grid(pady=40)
        self.frame2_record.grid(padx=10)
        self.frame3_record.grid(pady=30)
        self.tree.grid(column=0, row=0)
        self.tree_scroll.grid(column=1, row=0, sticky='NSW')
        self.lb_record.grid()
        self.back2_main.grid()

    def exit(self):
        self.window.destroy()
        quit(0)

    def back_menu1(self):
        self.frame1_add_image.grid_forget()
        self.frame2_add_image.grid_forget()
        self.main_menu()

    def back_menu2(self):
        self.frame1_record.grid_forget()
        self.frame2_record.grid_forget()
        self.frame3_record.grid_forget()
        self.main_menu()

    def back_menu3(self):
        self.frame1_game_config.grid_forget()
        self.frame2_game_config.grid_forget()
        self.frame3_game_config.grid_forget()
        self.frame4_game_config.grid_forget()
        self.main_menu()

    def checkbutton1(self):
        self.cb2.deselect()
        self.cb3.deselect()

    def checkbutton2(self):
        self.cb1.deselect()
        self.cb3.deselect()

    def checkbutton3(self):
        self.cb1.deselect()
        self.cb2.deselect()

    def get_diretory_image(self):
        options = {'defaultextension': '.png', 'filetypes': [('PNG Image', '.png')], 'initialdir': '',
                   'initialfile': '', 'title': 'Escolha um arquivo .png'}
        new_image = fdlg.askopenfilename(**options)

        if new_image:
            image = Image.open(new_image)
            resolution = image.size
            if resolution[0] == 800 and resolution[1] == 600:
                split_image = new_image.split("/")
                name_image = split_image[len(split_image) - 1]
                image.save("puzzler/puzzle_images/" + name_image, "PNG")
                tk.messagebox.showinfo("Importação", "Imagem importada com sucesso!")
            elif resolution[0] > 800 and resolution[1] > 600:
                if tk.messagebox.askyesno("Importação", "OBS: A imagem será cortada para 800x600! Deseja continuar?"):
                    x_left = (resolution[0] / 2) - 400
                    x_right = (resolution[0] / 2) + 400
                    y_top = (resolution[1] / 2) - 300
                    y_bottom = (resolution[1] / 2) + 300
                    image = image.crop((x_left, y_top, x_right, y_bottom))
                    split_image = new_image.split("/")
                    name_image = split_image[len(split_image) - 1]
                    image.save("puzzler/puzzle_images/" + name_image, "PNG")
                    tk.messagebox.showinfo("Importação", "Imagem importada com sucesso!")
            else:
                tk.messagebox.showinfo("Inválido", "A imagem tem que ter ser no mínimo 800x600!")

    def reset_image(self):
        if tk.messagebox.askyesno("Voltar ao padrão", "Todas as imagens importadas serão perdidas!\nDeseja continuar?"):
            default_images = ["puzzle_dark_souls.png", "puzzle_witch.png", "puzzle_pokemon.png"]
            for im in self.images_available:
                if im not in default_images:
                    os.remove("puzzler/puzzle_images/" + im)
            tk.messagebox.showinfo("Voltar ao padrão", "Redefinição completa!")


window = tk.Tk()
window.title('Puzzle-R Menu')
window.geometry('350x500')
window.resizable(0, 0)
window['bg'] = 'white'
window.iconbitmap("puzzler/config/icone.ico")

back = tk.Label(window)
back.la = tk.PhotoImage(file='puzzler/config/background.png')
back['image'] = back.la
back.place(x=-8, y=-6)

menu = HomeScreen(window)
menu.main_menu()
window.mainloop()
