if __name__ == '__main__':
    with open('conanfile.py', 'r') as file :
        lines = file.read()
    lines = lines.replace('name = "common"', 'name = "common_test"', 1)
    with open('conanfile.py', 'w') as file:
        file.write(lines)
