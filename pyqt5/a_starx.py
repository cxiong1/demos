from a_star import *
import sys
from functools import partial
from a_star_logic import a_star
import imgs_rc

def clicked(button):
    currtext = button.text()
    if currtext == 'road':
        button.setText('grass')
        button.setIcon(QtGui.QIcon(':/imgs/grass.jpg'))
    elif currtext == 'grass':
        button.setText('mountain')
        button.setIcon(QtGui.QIcon(':/imgs/mountain.png'))
    elif currtext == 'mountain':
        button.setText('water')
        button.setIcon(QtGui.QIcon(':/imgs/water.jpg'))
    elif currtext == 'water':
        button.setText('goal')
        button.setIcon(QtGui.QIcon(':/imgs/goal.png'))
    elif currtext == 'goal':
        button.setText('start')
        button.setIcon(QtGui.QIcon(':/imgs/start.jpg'))
    elif currtext == 'start':
        button.setText('road')
        button.setIcon(QtGui.QIcon(':/imgs/road.jpg'))

def reverseclicked(button):
    currtext = button.text()
    if currtext == 'road':
        button.setText('start')
        button.setIcon(QtGui.QIcon(':/imgs/start.jpg'))
    elif currtext == 'grass':
        button.setText('road')
        button.setIcon(QtGui.QIcon(':/imgs/road.jpg'))
    elif currtext == 'mountain':
        button.setText('grass')
        button.setIcon(QtGui.QIcon(':/imgs/grass.jpg'))
    elif currtext == 'water':
        button.setText('mountain')
        button.setIcon(QtGui.QIcon(':/imgs/mountain.png'))
    elif currtext == 'start':
        button.setText('goal')
        button.setIcon(QtGui.QIcon(':/imgs/goal.png'))
    elif currtext == 'goal':
        button.setText('water')
        button.setIcon(QtGui.QIcon(':/imgs/water.jpg'))

def set_all_road(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/road.jpg'))
        button.setText("road")

def set_all_grass(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/grass.jpg'))
        button.setText("grass")

def set_all_mountain(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/mountain.png'))
        button.setText("mountain")

def set_all_water(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/water.jpg'))
        button.setText("water")

def set_road_layout(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/grass.jpg'))
        button.setText("grass")

        roadbuttons = ['pushButton13', 'pushButton19','pushButton25','pushButton26','pushButton27']

        if button.objectName() == 'pushButton7':
            button.setIcon(QtGui.QIcon(':/imgs/start.jpg'))
            button.setText("start")
        if button.objectName() in roadbuttons:
            button.setIcon(QtGui.QIcon(':/imgs/road.jpg'))
            button.setText("road")
        if button.objectName() == 'pushButton28':
            button.setIcon(QtGui.QIcon(':/imgs/goal.png'))
            button.setText("goal")

def set_mountain_layout(layout):
    items = (layout.itemAt(i) for i in range(layout.count()))
    for w in items:
        button = w.widget()
        button.setIcon(QtGui.QIcon(':/imgs/grass.jpg'))
        button.setText("grass")

        roadbuttons = ['pushButton6', 'pushButton12','pushButton18','pushButton19','pushButton20','pushButton14','pushButton8']
        mountainbuttons = ['pushButton1', 'pushButton7','pushButton13']

        if button.objectName() == 'pushButton0':
            button.setIcon(QtGui.QIcon(':/imgs/start.jpg'))
            button.setText("start")
        if button.objectName() in roadbuttons:
            button.setIcon(QtGui.QIcon(':/imgs/road.jpg'))
            button.setText("road")
        if button.objectName() in mountainbuttons:
            button.setIcon(QtGui.QIcon(':/imgs/mountain.png'))
            button.setText("mountain")
        if button.objectName() == 'pushButton2':
            button.setIcon(QtGui.QIcon(':/imgs/goal.png'))
            button.setText("goal")

class MyWin(QtWidgets.QMainWindow):

    def run_clicked(self,layout,grid_list):
        items = (layout.itemAt(i) for i in range(layout.count()))
        i = 0
        for w in items:
            button = w.widget()
            index = button.objectName()
            index = index[10:]
            index_int = int(index)

            #print(index_int, button.text())
            grid_list[index_int] = (button.text())[0]
            if(button.text() == 'goal'):
                grid_list[index_int] = 'x'

        #print(grid_list)

        map = [[0 for i in range(6)] for i in range(6)]

        i = 0
        counter = 0
        start = 0
        goal = 0
        while i < 6:
            j = 0
            while j < 6:
                map[i][j] = grid_list[counter]
                if(grid_list[counter] == 's'):
                    start+=1
                if(grid_list[counter] == 'x'):
                    goal+=1
                j+=1
                counter +=1
            i+=1

        msg = QtWidgets.QMessageBox()
        msg.setIcon(QtWidgets.QMessageBox.Warning)
        msg.setWindowTitle("Paramter Mismatch")

        if(start < 1):
            msg.setText("You need to have a START point.")
            msg.exec_()
            return
        elif(start > 1):
            msg.setText("You have more than one START point.")
            msg.exec_()
            return
        elif(goal < 1):
            msg.setText("You need to have a GOAL point.")
            msg.exec_()
            return
        elif(goal > 1):
            msg.setText("You have more than one GOAL point.")
            msg.exec_()
            return

        secmap = a_star(map)

        secmap1d = []
        for x in secmap:
            secmap1d = secmap1d + x
            print(x)
        print()
        #print(secmap1d)

        labels = (self.ui.gridLayout_display.itemAt(i) for i in range(self.ui.gridLayout_display.count()))
        for label in labels:
            try:
                label = label.widget()
                index = label.objectName()[6:]
                index_int = int(index)

                if(secmap1d[index_int] == '_'):
                    label.setStyleSheet("QLabel { background-color : red;border: 1px solid black; border-radius: 6px }");
                else:
                    label.setStyleSheet("QLabel { background-color : green;border: 1px solid black; border-radius: 6px }");
            except:
                pass

    def __init__(self):
        QtWidgets.QWidget.__init__(self)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("A Star Pathfinder")

        grid_list = [None] * 36

        self.iterateButton()

        buttons = (self.ui.gridLayout_utility.itemAt(i) for i in range(self.ui.gridLayout_utility.count()))
        for btn in buttons:
            try:
                #print(btn.widget().objectName())
                btnname = btn.widget().objectName()
                if btnname == 'set_road':
                    btn.widget().clicked.connect(partial(set_all_road,self.ui.gridLayout))
                if btnname == 'set_grass':
                    btn.widget().clicked.connect(partial(set_all_grass,self.ui.gridLayout))
                if btnname == 'set_mountain':
                    btn.widget().clicked.connect(partial(set_all_mountain,self.ui.gridLayout))
                if btnname == 'set_water':
                    btn.widget().clicked.connect(partial(set_all_water,self.ui.gridLayout))
                if btnname == 'roadlayout':
                    btn.widget().clicked.connect(partial(set_road_layout,self.ui.gridLayout))
                if btnname == 'mountainlayout':
                    btn.widget().clicked.connect(partial(set_mountain_layout,self.ui.gridLayout))

            except:
                pass

        buttons = (self.ui.gridLayout_run.itemAt(i) for i in range(self.ui.gridLayout_utility.count()))
        for btn in buttons:
            try:
                btn.widget().clicked.connect(partial(self.run_clicked,self.ui.gridLayout,grid_list))
            except:
                pass

        labels = (self.ui.gridLayout_display.itemAt(i) for i in range(self.ui.gridLayout_display.count()))
        for label in labels:
            try:
                label.widget().setText('')
                label.widget().setStyleSheet("QLabel { background-color: none;border: 1px solid black; border-radius: 6px; }");
            except:
                pass

    def iterateButton(self):
        layout = self.ui.gridLayout
        items = (layout.itemAt(i) for i in range(layout.count()))
        for w in items:
            #print(w.widget().objectName())
            button = w.widget()
            button.setIcon(QtGui.QIcon(":/imgs/grass.jpg"))
            button.setText("grass")
            button.setSizePolicy(QtWidgets.QSizePolicy.Preferred,
        QtWidgets.QSizePolicy.Expanding)
            button.clicked.connect(partial(clicked,button))
            button.installEventFilter(self)

    def eventFilter(self, obj, event):
        if event.type() == QtCore.QEvent.MouseButtonPress:
            if event.button() == QtCore.Qt.LeftButton:
                pass
            elif event.button() == QtCore.Qt.RightButton:
                reverseclicked(obj)
                #print(obj.objectName(), "Right click")
        return QtCore.QObject.event(obj, event)


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
