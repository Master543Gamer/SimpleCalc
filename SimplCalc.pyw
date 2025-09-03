import tkinter as tk
import math

class SimplCalc:
    def __init__(self, top=None):
        top.geometry("315x686+578+2")
        top.title("SimplCalc v2.0")
        top.configure(background="#8f8f8f")

        self.top = top

        # Entry for user input
        self.Entry1 = tk.Entry(self.top, font=("Lucida Console", 45), bg="#b7b7b7")
        self.Entry1.place(relx=0.035, rely=0.015, height=80, relwidth=0.93)
        self.Entry1.bind('<Return>', self.evaluate_expression)

        # Result display
        self.result_var = tk.StringVar()
        self.Labelframe1 = tk.LabelFrame(self.top, text="Result", font=("Lucida Console", 12))
        self.Labelframe1.place(relx=0.035, rely=0.11, relheight=0.07, relwidth=0.93)
        self.EntryResult = tk.Entry(self.Labelframe1, textvariable=self.result_var, font=("Lucida Console", 12))
        self.EntryResult.pack(fill='both', expand=True)

        # Button configuration
        button_config = {"font": ("Segoe UI", 32), "bg": "#aeaeae",
                         "activebackground": "#aeaeae", "activeforeground": "#ffffff"}

        # Number buttons
        numbers = [
            ('1', 0.06, 0.25), ('2', 0.38, 0.25), ('3', 0.70, 0.25),
            ('4', 0.06, 0.37), ('5', 0.38, 0.37), ('6', 0.70, 0.37),
            ('7', 0.06, 0.49), ('8', 0.38, 0.49), ('9', 0.70, 0.49),
            ('0', 0.06, 0.61), ('.', 0.38, 0.61)
        ]
        for text, relx, rely in numbers:
            btn = tk.Button(self.top, text=text, **button_config, command=lambda t=text: self.append_to_entry(t))
            btn.place(relx=relx, rely=rely, height=76, width=77)

        # Operator buttons
        operators = [
            ('+', 0.38, 0.61), ('-', 0.70, 0.61),
            ('*', 0.06, 0.73), ('/', 0.38, 0.73),
            ('C', 0.70, 0.73), ('=', 0.70, 0.85)
        ]
        for op, relx, rely in operators:
            if op == 'C':
                btn = tk.Button(self.top, text=op, **button_config, command=self.clear_entry)
            elif op == '=':
                btn = tk.Button(self.top, text=op, **button_config, command=self.evaluate_expression)
            else:
                btn = tk.Button(self.top, text=op, **button_config, command=lambda t=op: self.append_to_entry(t))
            btn.place(relx=relx, rely=rely, height=76, width=77)

        # Version label (adjusted to fit on-screen)
        self.Label1 = tk.Label(self.top, text="SimplCalc v2.0", font=("Lucida Console", 12))
        self.Label1.place(relx=0.035, rely=0.95, height=30, width=174)

    def append_to_entry(self, value):
        current = self.Entry1.get()
        self.Entry1.delete(0, tk.END)
        self.Entry1.insert(0, current + value)

    def clear_entry(self):
        self.Entry1.delete(0, tk.END)
        self.result_var.set("")

    def evaluate_expression(self, event=None):
        user_input = self.Entry1.get().replace('x', '*').replace('÷', '/')
        try:
            # Safe eval using math module
            result = eval(user_input, {"__builtins__": None}, math.__dict__)
            self.result_var.set(result)
        except Exception:
            self.result_var.set("error")

if __name__ == '__main__':
    root = tk.Tk()
    app = SimplCalc(root)
    root.mainloop()
