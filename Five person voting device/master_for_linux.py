#!/usr/bin/env python
#-*- coding:utf-8 -*-

import os, sys
import serial
import serial.tools.list_ports
import time

try:
    from tkinter import *
except ImportError:  #Python 2.x
    PythonVersion = 2
    from Tkinter import *
    from tkFont import Font
    from ttk import *
    #Usage:showinfo/warning/error,askquestion/okcancel/yesno/retrycancel
    from tkMessageBox import *
    #Usage:f=tkFileDialog.askopenfilename(initialdir='E:/Python')
    #import tkFileDialog
    #import tkSimpleDialog
else:  #Python 3.x
    PythonVersion = 3
    from tkinter.font import Font
    from tkinter.ttk import *
    from tkinter.messagebox import *
    #import tkinter.filedialog as tkFileDialog
    #import tkinter.simpledialog as tkSimpleDialog    #askstring()

from tkinter import scrolledtext
from tkinter import messagebox

def main():
    top = Tk()
    Application(top).mainloop()
    try: top.destroy()
    except: pass

class Application_ui(Frame):
    #这个类仅实现界面生成功能，具体事件处理代码在子类Application中。
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master.title('小猪佩奇的五人表决器')
        self.master.geometry('1200x768')
        self.createWidgets()

    def createWidgets(self):
        self.top = self.winfo_toplevel()

        self.style = Style()

        self.style.configure('Label1.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label1 = Label(self.top, text='时间', style='Label1.TLabel')
        self.Label1.place(relx=0.025, rely=0.074, relwidth=0.059, relheight=0.053)

        #时间输入框
        self.Text1Var = StringVar(value='')
        self.Text1 = Entry(self.top, textvariable=self.Text1Var, font=('宋体',14))
        self.Text1.place(relx=0.099, rely=0.074, relwidth=0.092, relheight=0.058)

        #开始按钮
        self.style.configure('Command1.TButton',font=('宋体',9))
        self.Command1 = Button(self.top, text='开始', command=self.Command1_Cmd, style='Command1.TButton')
        self.Command1.place(relx=0.033, rely=0.316, relwidth=0.157, relheight=0.058)

        self.style.configure('Label2.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label2 = Label(self.top, text='状态：', style='Label2.TLabel')
        self.Label2.place(relx=0.025, rely=0.447, relwidth=0.075, relheight=0.053)

        #投票状态显示框
        self.style.configure('Label3.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label3 = Label(self.top, text='非投票时间', style='Label3.TLabel')
        self.Label3.place(relx=0.115, rely=0.447, relwidth=0.124, relheight=0.053)

        self.style.configure('Label4.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label4 = Label(self.top, text='倒计时', style='Label4.TLabel')
        self.Label4.place(relx=0.025, rely=0.595, relwidth=0.075, relheight=0.053)

        #倒计时显示框
        self.style.configure('Label5.TLabel',anchor='w', font=('宋体',60))
        self.Label5 = Label(self.top, text='0', style='Label5.TLabel')
        self.Label5.place(relx=0.123, rely=0.595, relwidth=0.116, relheight=0.207)

        self.style.configure('Label6.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label6 = Label(self.top, text='表决结果', style='Label6.TLabel')
        self.Label6.place(relx=0.305, rely=0.074, relwidth=0.092, relheight=0.053)

        #清空记录按钮
        self.style.configure('Command2.TButton',font=('宋体',9))
        self.Command2 = Button(self.top, text='清空记录', command=self.Command2_Cmd, style='Command2.TButton')
        self.Command2.place(relx=0.800, rely=0.074, relwidth=0.157, relheight=0.058)

        self.style.configure('Label7.TLabel',anchor='w', font=('宋体',14,'bold'))
        self.Label7 = Label(self.top, text='选手', style='Label7.TLabel')
        self.Label7.place(relx=0.025, rely=0.205, relwidth=0.059, relheight=0.053)

        #选手输入框
        self.Text2Var = StringVar(value='')
        self.Text2 = Entry(self.top, textvariable=self.Text2Var, font=('宋体',14))
        self.Text2.place(relx=0.099, rely=0.205, relwidth=0.092, relheight=0.058)

        #投票结果显示框
        self.SText = scrolledtext.ScrolledText(self.top,width=20,height=20,background='#ffffff',font=('宋体',18,'bold'))
        self.SText.place(relx=0.310, rely=0.150, relwidth=0.650, relheight=0.750)
        self.SText.config(state=DISABLED)

        #串口选择框
        port_list = list(serial.tools.list_ports.comports())
        port_list_1 = []
        for i in port_list:
            port_list_1.append(i[0])
        self.Combol1List = port_list_1
        self.Combol1Var = StringVar(value='')
        self.Combol1 = Combobox(self.top, text='', textvariable=self.Combol1Var, state = "readonly",values=self.Combol1List, font=('宋体',12))
        self.Combol1.place(relx=0.035, rely=0.800, relwidth=0.08, relheight=0.072)
        self.Combol1Var.trace('w', self.Combol1_Change)

        #连接表决器按钮
        self.style.configure('Command3.TButton',font=('宋体',9))
        self.Command3 = Button(self.top, text='连接表决器', command=self.Command3_Cmd, style='Command3.TButton')
        self.Command3.place(relx=0.033, rely=0.900, relwidth=0.157, relheight=0.058)

        #扫描串口按钮
        self.style.configure('Command4.TButton',font=('宋体',9))
        self.Command4 = Button(self.top, text='刷新', command=self.Command4_Cmd, style='Command4.TButton')
        self.Command4.place(relx=0.120, rely=0.800, relwidth=0.08, relheight=0.072)

class Application(Application_ui):
    #这个类实现具体的事件处理回调函数。界面生成代码在Application_ui中。
    def __init__(self, master=None):
        Application_ui.__init__(self, master)

        file = open("data.txt","r")
        content = file.read()
        self.SText.config(state=NORMAL)
        self.SText.insert(END, content)
        self.SText.config(state=DISABLED)
        #print(content)
        file.close()
        
    #开始按钮
    def Command1_Cmd(self, event=None):
        global COM
        num = int(self.Text1.get())
        name = self.Text2.get()
        try:
            COM.write(b"a\r\n")
            for i in range(num):
                self.Label5["text"] = num-i
                self.Label3["text"] = "正在投票"
                self.top.update()
                time.sleep(1)
            self.Label5["text"] = 0
            self.Label3["text"] = "非投票时间"
            self.top.update()
            COM.write(b"a\r\n")
            time.sleep(1)
            COM.flushInput()
            score = int(COM.readline())
            print(score)
            if score > 80:
                str1 = "选手" + self.Text2.get() + '  ' + str(score) + "分" + '  ' + "通过" + '  ' + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) + '\n\n'
            else:
                str1 = "选手" + self.Text2.get() + '  ' + str(score) + "分" + '  ' + "不通过" + '  ' + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) + '\n\n'
            self.SText.config(state=NORMAL)
            self.SText.insert(END, str1)
            self.SText.config(state=DISABLED)
            file = open("data", "a")
            file.write(str1)
            file.close()
        except Exception:
            messagebox.showinfo(title = "error",message = "请连接表决器")
        pass

    #清空记录按钮
    def Command2_Cmd(self, event=None):
        self.SText.config(state=NORMAL)
        self.SText.delete(1.0, END)
        self.SText.config(state=DISABLED)
        file = open("data","w")
        file.truncate()
        file.close()

    #连接表决器按钮
    def Command3_Cmd(self, event=None):
        global COM
        try:
            COM = serial.Serial(port=self.Combol1.get(), baudrate=9600)
            COM.close()
            COM.open()
        except Exception:
            print("COM Open Error!")
            messagebox.showinfo(title = "连接状态",message = "连接失败")
        if COM.isOpen():
            self.Command3["text"] = "断开表决器"
            messagebox.showinfo(title = "连接状态",message = "已连接")
        else:
            COM.close()
            self.Command3["text"] = "连接表决器"
            messagebox.showinfo(title = "连接状态",message = "连接已断开")
            #print(COM.isOpen())
        pass

    #扫描串口按钮
    def Command4_Cmd(self, event=None):
        self.Combol1["textvariable"] = StringVar(value='')
        port_list = list(serial.tools.list_ports.comports())
        port_list_1 = []
        for i in port_list:
            port_list_1.append(i[0])
        self.Combol1["values"] = port_list_1
        pass
    
    #串口选择框
    def Combol1_Change(self, *args):
        #print(self.Combol1.get())
        pass

if __name__ == "__main__":
    main()


