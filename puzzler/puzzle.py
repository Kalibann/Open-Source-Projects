import numpy as np
import os
import pygame
import random
from PIL import Image


class Puzzle:

    def __init__(self, player_name, game_image, difficulty, row, column, cut_size, parts):
        self.IMAGES = []
        self.full_image = None
        self.frame_info = None
        self.frame_end = None
        self.frame_end_menu = None
        self.matrix_images = None
        self.matrix_shuffle = None
        self.player = player_name
        self.game_image = game_image
        self.str_image = "puzzler/puzzle_images/" + game_image
        self.level = difficulty
        self.C = column
        self.R = row
        self.CS = cut_size
        self.P = parts
        self.end = False

    def crop_image(self):
        # Função para cortar a imagem para ser utilizada no puzzle
        im_crop = []

        image = Image.open(self.str_image)

        LEFT = 0
        TOP = 0
        RIGHT = self.CS
        BOTTOM = self.CS

        if not os.path.isdir("puzzler/puzzle_crop"):
            os.mkdir("puzzler/puzzle_crop")

        k = 0
        for i in range(self.R):
            for j in range(self.C):
                im = image.crop((LEFT, TOP, RIGHT, BOTTOM))
                im_crop.append(im)
                LEFT += self.CS
                RIGHT += self.CS
                im.save("puzzler/puzzle_crop/" + str(k) + ".png", "PNG")
                k += 1

            LEFT = 0
            TOP += self.CS
            RIGHT = self.CS
            BOTTOM += self.CS

    def load_images(self):
        # Carregar a imagem já cortada
        k = 0
        for i in range(self.R):
            for j in range(self.C):
                im = pygame.image.load(os.path.join("puzzler/puzzle_crop/", str(k) + ".png"))
                self.IMAGES.append(im)
                k += 1

        self.full_image = pygame.image.load(os.path.join(self.str_image))
        self.frame_info = pygame.image.load("puzzler/config/frame_info.png")
        self.frame_end = pygame.image.load("puzzler/config/frame_end.png")
        self.frame_end_menu = pygame.image.load("puzzler/config/frame_end_menu.png")

    def randomize(self):
        images_shuffle = self.IMAGES.copy()
        random.shuffle(images_shuffle)

        # Transformar vetor em matrix
        self.matrix_images = np.empty([self.R, self.C]).tolist()
        self.matrix_shuffle = np.empty([self.R, self.C]).tolist()

        k = 0
        for i in range(self.R):
            for j in range(self.C):
                self.matrix_images[i][j] = self.IMAGES[k]
                self.matrix_shuffle[i][j] = images_shuffle[k]
                k += 1

    def puzzle_pygame(self):
        # Inicialização do jogo
        pygame.display.init()
        window = pygame.display.set_mode((1100, 600))
        clock = pygame.time.Clock()

        # Auxiliares na troca da posição das peças
        coord = [0, 0]
        aux_shift = [0, 0]
        aux_coord = 0
        movements = 0

        # Cores
        GREEN = (0, 255, 0)
        PURPLE = (102, 81, 173)
        WHITE = (255, 255, 255)

        # Ativação das bordas
        activate_borders = True

        # Inicialização Pygame
        running = True
        while running:
            clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()

                # Ícone e título
                pygame.init()
                icon = pygame.image.load("puzzler/config/icone.png")
                pygame.display.set_icon(icon)
                pygame.display.set_caption("Puzzle-R Game")

                # Quadro de execução
                pygame.font.init()
                font = pygame.font.SysFont("Comic Sans MS", 21)
                font2 = pygame.font.SysFont("Comic Sans MS", 14)
                if movements < 10:
                    text = font.render("0" + str(movements), 1, WHITE)
                else:
                    text = font.render(str(movements), 1, WHITE)

                text_player = font2.render("Player: " + self.player, 1, WHITE)
                text_puzzle = font2.render("Puzzle: " + self.game_image, 1, WHITE)
                text_level = font2.render("Dificuldade: " + str(self.level), 1, WHITE)

                window.blit(self.frame_info, (0, 0))
                window.blit(text, (141, 210))
                window.blit(text_player, (52, 320))
                window.blit(text_puzzle, (52, 340))
                window.blit(text_level, (52, 360))

                if self.end is False:
                    # Distribuir puzzle na window de execução
                    for i in range(self.R):
                        for j in range(self.C):
                            window.blit(self.matrix_shuffle[i][j], (300 + (j * self.CS), i * self.CS))
                            if activate_borders:
                                pygame.draw.rect(self.matrix_shuffle[i][j], PURPLE, [0, 0, self.CS, self.CS], 1)

                    # Condição para desativar a atualização das bordas em aux_shifto real
                    if activate_borders:
                        activate_borders = False
                else:
                    font3 = pygame.font.SysFont("Comic Sans MS", 36)
                    text_end1 = font3.render("Parabéns", 1, WHITE)
                    text_end2 = font.render("Você terminou o jogo em " + str(movements) + " movimentos", 1, WHITE)
                    window.blit(self.frame_end, (300, 0))
                    window.blit(self.frame_end_menu, (700, 450))
                    window.blit(text_end1, (650, 200))
                    window.blit(text_end2, (550, 300))

                pygame.display.update()

                # Eventos de clique -> MOUSEBUTTONDOWN: clicar, MOUSEBUTTONUP: soltar
                # Ações com botões: 1- Botão esquerdo do mouse, 3- Botão esquerdo do mouse
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 3:
                        for i in range(self.R):
                            for j in range(self.C):
                                saved_image = window.copy()
                                window.blit(self.full_image, (300, 0))
                                pygame.display.flip()
                                showing_solution = True

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        pos_mouse = pygame.mouse.get_pos()
                        if pos_mouse[0] > 300:
                            x = int((pos_mouse[0] - 300) / self.CS)
                            y = int(pos_mouse[1] / self.CS)
                            aux_shift[aux_coord] = (self.matrix_shuffle[y][x])
                            coord[aux_coord] = (y, x)
                            pygame.draw.rect(self.matrix_shuffle[y][x], GREEN, [0, 0, self.CS, self.CS], 1)
                            if aux_coord == 1:
                                self.matrix_shuffle[coord[0][0]][coord[0][1]] = aux_shift[1]
                                self.matrix_shuffle[coord[1][0]][coord[1][1]] = aux_shift[0]
                                pygame.draw.rect(self.matrix_shuffle[coord[0][0]][coord[0][1]], PURPLE,
                                                 [0, 0, self.CS, self.CS], 1)
                                pygame.draw.rect(self.matrix_shuffle[coord[1][0]][coord[1][1]], PURPLE,
                                                 [0, 0, self.CS, self.CS], 1)
                                aux_shift[0] = aux_shift[1] = aux_coord = 0
                                if self.end is False:
                                    movements += 1
                            else:
                                aux_coord += 1

                        if self.end is True:
                            pos_mouse = pygame.mouse.get_pos()
                            if 700 < pos_mouse[0] < 765 and 455 < pos_mouse[1] < 495:
                                running = False

                        finished = 0
                        for i in range(self.R):
                            for j in range(self.C):
                                if self.matrix_shuffle[i][j] == self.matrix_images[i][j]:
                                    finished += 1

                        if finished == self.P and self.end is False:
                            record = open("puzzler/config/records.txt", "a")
                            record.write(str(movements) + ",")
                            record.write(self.player + ",")
                            record.write(self.game_image + ",")
                            record.write(str(self.level) + '\n')
                            self.end = True

                        pygame.display.update()

                    if event.button == 3:
                        for i in range(self.R):
                            for j in range(self.C):
                                if showing_solution:
                                    window.blit(saved_image, (0, 0))
                                    pygame.display.flip()
                                    showing_solution = False

        pygame.quit()
        return True


'''
instance = Puzzle("teste", "puzzle_witch.png", 3, 12, 16, 50, 192)
instance.crop_image()
instance.load_images()
instance.randomize()
instance.puzzle_pygame()
'''
