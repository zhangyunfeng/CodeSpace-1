#coding: utf-8
import pygtk
import pango
import gtk
import gobject
import os
import sys
import time
import datetime
import threading
import platform, locale, shutil

gobject.threads_init()
 
def hideFile(filePath):
    if 'Windows' in platform.system():
        cmd = 'attrib +h "' + filePath +'"'
        cmd = cmd.encode(locale.getdefaultlocale()[1])
        os.popen(cmd).close()
        time.sleep(1)


class CheckInTimeSaver:
	def save(self, timestamp):
		with open(".checkintime", "wb") as f:
			f.write(str(timestamp))
		#hideFile(".checkintime")

	def delete(self):
		print "delete checkintime file"
		if os.path.exists(".checkintime"):
			os.remove(".checkintime")

	def isCheckInTimeFileExists(self):
		if os.path.exists(".checkintime"):
			return True
		return False

	def getCheckInTime(self):
		with open(".checkintime", "rb") as f:
			ts = float(f.readline())
			return ts
		return None

class WorkTimerUI:
	def __init__(self):
		self.checkInTime = None
		self.checkInTimeSaver = CheckInTimeSaver()
		self.bInWorking = False

		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect("delete_event", self.delete_event)
		self.window.connect("destroy", self.destroy)
		self.window.set_border_width(10)
		self.window.set_default_size(600, 500)
		self.window.set_title("工作计时器")
		#self.window.set_resizable(False)
		self.window.set_icon_from_file("icon.png")
		self.mainVBox = gtk.VBox(False, 0)
		self.window.add(self.mainVBox)

		self.hbox = gtk.HBox(False, 0)
		self.mainVBox.pack_start(self.hbox, True, True, 0)
		self.hbox2 = gtk.HBox(False, 0)
		self.mainVBox.pack_start(self.hbox2, True, True, 0)

		# label attributes
		self.pangoAttrList = pango.AttrList()
		self.pangoAttrList.insert(pango.AttrSize(100, 0, 30))
		self.pangoAttrList.insert(pango.AttrForeground(65535, 0, 0, 0, 30))

		self.button = gtk.Button("打卡")
		self.button.connect("clicked", self.onCheckInClicked, None)
		self.hbox.pack_start(self.button, True, True, 0)
		self.button.show()

		self.button2 = gtk.Button("下班")
		self.button2.connect("clicked", self.onGoOffWorkClicked, None)
		self.hbox.pack_start(self.button2, True, True, 0)
		self.button2.show()

		# 打卡时间
		self.checkInTimeTitleLabel = gtk.Label("打卡时间：")
		self.checkInTimeTitleLabel.set_alignment(1, 0.5)
		self.hbox2.pack_start(self.checkInTimeTitleLabel, False, True, 0)
		self.checkInTimeTitleLabel.show()

		self.checkInTimeLabel = gtk.Label("N/A")
		self.checkInTimeLabel.set_alignment(0, 0.5)
		self.checkInTimeLabel.set_attributes(self.pangoAttrList)
		self.hbox2.pack_start(self.checkInTimeLabel, True, True, 0)
		self.checkInTimeLabel.show()

		# 工作时间
		self.workedTimeTitleLabel = gtk.Label("已工作时间：")
		self.workedTimeTitleLabel.set_alignment(1, 0.5)
		self.hbox2.pack_start(self.workedTimeTitleLabel, False, True, 0)
		self.workedTimeTitleLabel.show()

		self.workedTimeLabel = gtk.Label("00小时 00分钟 00秒")
		self.workedTimeLabel.set_alignment(0, 0.5)
		self.workedTimeLabel.set_attributes(self.pangoAttrList)
		self.hbox2.pack_start(self.workedTimeLabel, True, True, 0)
		self.workedTimeLabel.show()

		self.window.show_all()

		#检查是否是工作状态
		if self.checkInTimeSaver.isCheckInTimeFileExists():
			self.checkInTime = self.checkInTimeSaver.getCheckInTime()
			self.bInWorking = True

		self.updateThread = threading.Thread(target=self.updateOnThread)
		self.stopUpdateThread = False

	def delete_event(self, widget, event, data=None):
		print "delete event"

	def destroy(self, widget, data=None):
		print "destroy"
		self.stopUpdateThread = True
		if not self.bInWorking:
			self.checkInTimeSaver.delete()
		else:
			self.checkInTimeSaver.save(self.checkInTime)
		gtk.main_quit()

	def onCheckInClicked(self, widget, data=None):
		if self.checkInTime == None:
			self.checkInTime = time.time()
		if self.bInWorking :
			gtk.MessageDialog(self.window,gtk.DIALOG_DESTROY_WITH_PARENT, gtk.MESSAGE_INFO, gtk.BUTTONS_NONE, "已经打过卡了").show()

		self.checkInTimeLabel.set_text(datetime.datetime.fromtimestamp(self.checkInTime).strftime("%Y/%m/%d %H:%M:%S"))
		self.checkInTimeSaver.save(self.checkInTime)
		self.bInWorking = True
		self.__updateWorkTime()


	def onGoOffWorkClicked(self, widget, data=None):
		'''下班'''
		md = gtk.MessageDialog(self.window, gtk.DIALOG_DESTROY_WITH_PARENT, gtk.MESSAGE_WARNING, 
			gtk.BUTTONS_OK_CANCEL, "你确定要下班吗?")
		ret = md.run()
		if ret == -5:  # click 确定
			print "删除本地保持的打卡时间"
			self.checkInTimeSaver.delete()
			self.bInWorking = False
		md.destroy()

	def __updateWorkTime(self):
		now_timestamp = time.time()
		if self.checkInTime != None and self.bInWorking:
			diff_secondes = now_timestamp - self.checkInTime
			hours = int(diff_secondes / 3600)
			minutes = int((diff_secondes - hours * 3600) / 60)
			seconds = int(diff_secondes % 60)
			self.checkInTimeLabel.set_text(datetime.datetime.fromtimestamp(self.checkInTime).strftime("%Y/%m/%d %H:%M:%S"))
			self.workedTimeLabel.set_text(str(hours) + "小时 " + str(minutes) + "分钟 " + str(seconds) + "秒")
			print "updateWorkTime " + str(diff_secondes)


	def updateOnThread(self):
		while True:
			self.__updateWorkTime()
			time.sleep(1)
			if self.stopUpdateThread: #退出线程
				break

	def main(self):
		self.updateThread.start()
		gtk.main()

if __name__ == '__main__':
	ui = WorkTimerUI()
	ui.main()

