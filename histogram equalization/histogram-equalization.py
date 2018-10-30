#-*-coding:utf-8-*-
#@Author:刘瀚轩
#@Date:2018-4-28
#@mail:m13143378602@163.com
#@function:histogram equalization

import PIL
import numpy as np
import matplotlib.pyplot as plt
from tkinter import *
from tkinter.ttk import *
from tkinter import messagebox
from tkinter.filedialog import askopenfilename
from collections import Counter

class Application_ui(Frame):
    #这个类仅实现界面生成功能，具体事件处理代码在子类Application中。
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master.title('直方图均衡')
        self.master.geometry('650x150')
        self.createWidgets()

    def createWidgets(self):
        self.top = self.winfo_toplevel()

        self.style = Style()

        self.v = IntVar()

        self.style.configure('Command1.TButton',font=('宋体',15))
        self.Command1 = Button(self.top, text='开始', command=self.Command1_Cmd, style='Command1.TButton')
        self.Command1.place(relx=0.697, rely=0.520, relwidth=0.182, relheight=0.200)

        self.style.configure('Command2.TButton',font=('宋体',7))
        self.Command1 = Button(self.top, text='...', command=self.Command2_Cmd, style='Command2.TButton')
        self.Command1.place(relx=0.760, rely=0.128, relwidth=0.03, relheight=0.166)

        self.style.configure('Option1.TRadiobutton',font=('宋体',12))
        self.Option1 = Radiobutton(self.top, text='灰度均衡', variable=self.v, value=0, style='Option1.TRadiobutton')
        self.Option1.place(relx=0.204, rely=0.455, relwidth=0.18, relheight=0.324)

        self.style.configure('Option2.TRadiobutton',font=('宋体',12))
        self.Option2 = Radiobutton(self.top, text='RGB均衡', variable=self.v, value=1, style='Option2.TRadiobutton')
        self.Option2.place(relx=0.400, rely=0.455, relwidth=0.18, relheight=0.324)

        self.style.configure('Label2.TLabel',anchor='w', font=('宋体',9))
        self.Label2 = Label(self.top, text='', style='Label2.TLabel',background='#ffffff')
        self.Label2.place(relx=0.260, rely=0.136, relwidth=0.500, relheight=0.150)
        
        self.style.configure('Label1.TLabel',anchor='w', font=('宋体',15))
        self.Label1 = Label(self.top, text='请选择图片', style='Label1.TLabel')
        self.Label1.place(relx=0.070, rely=0.136, relwidth=0.180, relheight=0.150)


class Application(Application_ui):
    #这个类实现具体的事件处理回调函数。界面生成代码在Application_ui中。
    def __init__(self, master=None):
        Application_ui.__init__(self, master)

    def Command1_Cmd(self, event=None):
        #灰度均衡
        def gray(filename):
            #计算部分
            img = np.array(PIL.Image.open(filename).convert("L"))#获取图像二维数组
            arr = img.flatten()#图像数组降维
            arr_list = arr.tolist()#数组转换为列表
            arr_list1 = set(arr_list)#获取无重复元素的列表
            #创建数据统计字典 key=元素，value=概率分布*255(即key转换后对应的灰度值)
            dic = {}
            s = 0
            for item in arr_list1:
                s = s + arr_list.count(item)/len(arr_list)#计算概率分布
                dic.update({item:s*255})

            arr_list2 = []
            for item1 in arr_list:
                arr_list2.append(dic[item1])

            img1 = []
            for item2 in range(0,len(arr_list2),len(img[0])):
                img1.append(arr_list2[item2:item2+len(img[0])])

            #绘图部分
            plt.figure("灰度直方图均衡")
            plt.subplot(221)
            plt.axis('off')
            plt.imshow(img,cmap = "gray")
            plt.subplot(222)
            plt.axis('off')
            plt.imshow(img1,cmap = "gray")
            plt.subplot(223)
            plt.hist(arr, 256, [0,256], facecolor="green")#绘制原始直方图
            plt.subplot(224)
            plt.hist(arr_list2, 256, [0,256], facecolor="red")#绘制均衡直方图

            plt.show()

        #RGB均衡
        def rgb(filename):
            #计算部分
            #加载RGB三通道的值
            r, g, b = [], [], []
            img = PIL.Image.open(filename)
            width, height = img.size[0], img.size[1]
            sum_pix = width * height
            pix = img.load()
            for x in range(width):
                for y in range(height):
                    r.append(pix[x, y][0])
                    g.append(pix[x, y][1])
                    b.append(pix[x, y][2])
            #统计概率分布               
            r_c = dict(Counter(r))
            g_c = dict(Counter(g))
            b_c = dict(Counter(b))
            r_p,g_p,b_p = [],[],[]

            for i in range(256):
                if i in r_c:
                    r_p.append(float(r_c[i])/sum_pix)
                else:
                    r_p.append(0)
                if i in g_c:
                    g_p.append(float(g_c[i])/sum_pix)
                else:
                    g_p.append(0)
                if i in b_c:
                    b_p.append(float(b_c[i])/sum_pix)
                else:
                    b_p.append(0)
            #计算均衡后的值
            temp_r,temp_g,temp_b = 0,0,0
            for i in range(256):
                temp_r += r_p[i]
                r_p[i] = int(temp_r * 255)
                temp_b += b_p[i]
                b_p[i] = int(temp_b * 255)
                temp_g += g_p[i]
                g_p[i] = int(temp_g * 255)
            new_photo = PIL.Image.new('RGB',(width,height))
            for x in range(width):
                for y in range(height):
                    new_photo.putpixel((x,y),(r_p[pix[x,y][0]],g_p[pix[x,y][1]],b_p[pix[x,y][2]]))
            n_r, n_g, n_b = [], [], []
            pix1 = new_photo.load()
            for x in range(width):
                for y in range(height):
                    n_r.append(pix1[x, y][0])
                    n_g.append(pix1[x, y][1])
                    n_b.append(pix1[x, y][2])            
            
            #绘图部分
            plt.figure("RGB直方图均衡")
            plt.subplot(421)
            plt.axis('off')
            plt.imshow(img)
            plt.subplot(422)
            plt.axis('off')
            plt.imshow(new_photo)
            plt.subplot(423)
            plt.hist(r, 256, [0,256], facecolor="red")#r通道绘制原始直方图
            plt.subplot(424)
            plt.hist(n_r, 256, [0,256], facecolor="red")#r通道绘制均衡直方图
            plt.subplot(425)
            plt.hist(g, 256, [0,256], facecolor="green")#g通道绘制原始直方图
            plt.subplot(426)
            plt.hist(n_g, 256, [0,256], facecolor="green")#g通道绘制均衡直方图
            plt.subplot(427)
            plt.hist(b, 256, [0,256], facecolor="blue")#b通道绘制原始直方图
            plt.subplot(428)
            plt.hist(n_b, 256, [0,256], facecolor="blue")#b通道绘制均衡直方图
            
            plt.show()

        #制图逻辑
        if not self.Label2["text"]:
            messagebox.showinfo(title = "警告",message = "请选择图片")
        else:
            if not self.v.get():
                gray(self.Label2["text"])
            else:
                rgb(self.Label2["text"])
                pass
        pass

    def Command2_Cmd(self, event=None):
        filename = askopenfilename(initialdir = './',filetypes = [('JPG', 'jpg'),('PNG', 'png')])
        self.Label2["text"] = filename
        pass

if __name__ == "__main__":
    top = Tk()
    Application(top).mainloop()
    try: top.destroy()
    except: pass
