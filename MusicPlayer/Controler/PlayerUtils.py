#! /usr/bin/env python


#coding: utf8

import sfml as sf

import thread
import time

##FIXME: Playing music need run in a thread env

class PlayerUtils :
    '''
    Player base functions
    '''
    def __init__(self, music_file_):
        self.music_file = music_file_
        self.player_thread = thread
        self.pausing = False
        self.music = None
    def __playMusicFromFile(self, music_file):
        if not self.pausing:
            self.music = sf.Music.from_file(music_file)
        ## Play it
        self.music.play()
        
        #loop while the sound is playing
        while self.music.status == sf.Music.PLAYING:
            #leave some cpu time for other processes
            sf.sleep(sf.milliseconds(100))

    def PlayMusic(self):
        try:
            self.pausing = False
            self.player_thread.start_new_thread(self.__playMusicFromFile, (self.music_file,))
        except IOError, e:
            print "Open music file failed: {0}".format(e)

    def ContinueMusic(self):
        self.__playMusicFromFile(self.music_file)
        self.pausing = False
        
    def PauseMusic(self):
        self.music.pause()
        self.pausing = True

    def StopMusic(self):
        self.music.stop()
        self.pausing = False
        
    def SetMusicAttributes(self, _3d_position, pitch, volume, loop):
        try:
            self.music.position = _3d_position
            self.music.pitch = pitch
            self.music.volume = volume
            self.music.loop = loop
        except Exception, e:
            print "Set Music Attributes failed: {0}".format(e)

    def SetMusicVolume(self, new_volume):
        if new_volume < 0:
            new_volume = 0
        self.music.volume = new_volume

    def SetMusicLoop(self, bLoop):
        self.music.loop = bLoop



player = PlayerUtils("/home/ken/Desktop/NoMatterWhat.ogg")

player.PlayMusic()

print "hello"
time.sleep(10)
print "pause .."
player.PauseMusic()
time.sleep(10)
player.ContinueMusic()
time.sleep(10)
