def brainfuck_interpreter(code): # 79 109 97 114
    memory = [0] * 30000
    pointer = 0
    code_pointer = 0
    brackets = []
    input = []

    while code_pointer < len(code):
        command = code[code_pointer]

        if command == '>':
            pointer += 1
        elif command == '<':
            pointer -= 1
        elif command == '+':
            memory[pointer] = (memory[pointer] + 1) % 256
        elif command == '-':
            memory[pointer] = (memory[pointer] - 1) % 256
        elif command == '.':
            print(chr(memory[pointer]), end='')
        elif command == ',':
            if input:
                memory[pointer] = ord(input.pop(0))
            else:
                memory[pointer] = ord(input("Inputu: ")[0])
        elif command == '[':
            if memory[pointer] == 0:
                brackets_open = 1
                while brackets_open != 0:
                    code_pointer += 1
                    if code[code_pointer] == '[':
                        brackets_open += 1
                    elif code[code_pointer] == ']':
                        brackets_open -= 1
            else:
                brackets.append(code_pointer)
        elif command == ']':
            if memory[pointer] != 0:
                code_pointer = brackets[-1] - 1
            else:
                brackets.pop()

        code_pointer += 1


while True:
    brainfuck_interpreter(input("\nWrite code: "))
    a = input("\n\nPress enter to continue: ")
