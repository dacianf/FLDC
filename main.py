from controller.Controller import Controller
from models.HashTable import HashTable
from models.Scanner import Scanner
from models.Specification import Specification

if __name__ == '__main__':
    fileName = input("Insert file name: ")
    controller = Controller(HashTable(), Scanner(Specification()), [])

    controller.run(fileName)

    controller.saveData()
