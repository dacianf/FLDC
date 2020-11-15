from model.finite_automata import FiniteAutomata


def handleOption(fa, option):
    if option == 1:
        print("Set of states: ", fa.states)
    elif option == 2:
        print("Alphabet: ", fa.alphabet)
    elif option == 3:
        print("All transitions: ")
        fa.showAllTransitions()
    elif option == 4:
        print("Final states: ", fa.finalStates)
    elif option == 5:
        print("FA: ", fa)
    elif option == 6:
        if fa.isDFA():
            print("FA is DNF")
        else:
            print("FA is NOT DNF")
    elif option == 7:
        if not fa.isDFA():
            print("FA must be DFA")
            return
        sequence = input("Type down the sequence you want to check:\n\t> ")
        if fa.isAccepted(sequence):
            print("Sequence is accepted")
        else:
            print("Sequence is not accepted")


def menu(fa):
    options = {0: "Exit", 1: "Set of states", 2: "Alphabet", 3: "All the transitions", 4: "Final states", 5: "Print FA",
               6: "Check if is DFA", 7: "Check sequence"}
    crtOption = -1
    string = "Menu:\n"
    for k in options.keys():
        string += "\t" + str(k) + ": " + options[k] + ";\n"
    print(string)
    while crtOption != 0:
        try:
            crtOption = int(input("> "))
            if crtOption not in list(options.keys()):
                print("Invalid key")
            else:
                handleOption(fa, crtOption)
        except:
            crtOption = -1
            print("Invalid key")


if __name__ == '__main__':
    finiteAutomata = FiniteAutomata.fromFile('data/fa.txt')
    menu(finiteAutomata)
