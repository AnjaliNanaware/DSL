class Hashtable:
    def __init__(self):
        self.size = 7
        self.h = [[None, None] for _ in range(self.size)]
        self.count = 0

    def input(self):
        key = input("\nEnter the key: ")
        value = input("Enter the value: ")
        self.hashf(key, value)

    def hashf(self, key, value):
        sum = 0
        for char in key:
            sum += ord(char)

        ch = sum % self.size
        self.linearp(key, value, ch)

    def linearp(self, key, value, ch):
        if self.count == self.size:
            print("Table is Full")
        else:
            while self.h[ch][0] is not None and self.count != self.size:
                ch = (ch + 1) % self.size

            self.h[ch][0] = key
            self.h[ch][1] = value
            self.count += 1

    def display(self):
        print("\n\t[Key]\t[Value]")
        for i in range(self.size):
            for j in range(2):
                print("\t", self.h[i][j], end="")
            print()

    def search(self):
        k = input("\nEnter the string to search: ")
        sum = 0
        for char in k:
            sum += ord(char)

        ch = sum % self.size
        if self.count == self.size:
            print("\nSearch is not found")
        else:
            while self.h[ch][0] != k and self.count != self.size:
                ch = (ch + 1) % self.size

            self.count += 1
            if self.h[ch][0] == k:
                print(f"String '{k}' found at index {ch}")

    def delete(self):
        k = input("\nEnter the string to delete: ")
        sum = 0
        for char in k:
            sum += ord(char)

        ch = sum % self.size
        if self.count == self.size:
            print("Search is not found")
        else:
            while self.h[ch][0] != k and self.count != self.size:
                ch = (ch + 1) % self.size

        self.h[ch][0] = None
        self.h[ch][1] = None
        print(f"String '{k}' deleted from index {ch}")


def main():
    h1 = Hashtable()
    while True:
        print("\nEnter choice\n1. input  2. display  3. search  4. delete\nChoice [1/2/3/4]: ")
        ch = int(input())
        if ch == 1:
            h1.input()
        elif ch == 2:
            h1.display()
        elif ch == 3:
            h1.search()
        elif ch == 4:
            h1.delete()
        else:
            break


if __name__ == "__main__":
    main()
