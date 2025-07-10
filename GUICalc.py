import tkinter as tk

class Toplevel1:
    def __init__(self, top=None):
        top.geometry("600x298+383+106")
        top.title("Calculator")
        top.configure(background="black")
        self.top = top
        
        self.Entry1 = tk.Entry(self.top, font=("Lucida Console", 40), background="#c0c0c0", foreground="black")
        self.Entry1.place(relx=0.017, rely=0.034, height=120, relwidth=0.957)
        self.Entry1.bind('<Return>', self.evaluate_expression)

        self.Label1 = tk.Label(self.top, text='* is Multiplying',
                               font=("Lucida Console", 30),
                               background="black", foreground="white", anchor='w')
        self.Label1.place(relx=0.133, rely=0.503, height=81, width=564)

        self.Label2 = tk.Label(self.top, text='/ is Dividing',
                               font=("Lucida Console", 30),
                               background="black", foreground="white", anchor='w')
        self.Label2.place(relx=0.2, rely=0.772, height=46, width=318)

    def evaluate_expression(self, event=None):
        user_input = self.Entry1.get()
        try:
            result = eval(user_input)
            self.Entry1.delete(0, tk.END)
            self.Entry1.insert(0, str(result))
        except Exception:
            self.Entry1.delete(0, tk.END)
            self.Entry1.insert(0, "error")

def main():
    root = tk.Tk()
    app = Toplevel1(root)
    root.mainloop()

if __name__ == "__main__":
    main()
