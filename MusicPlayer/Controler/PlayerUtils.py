#! /usr/bin/env python


#coding: utf8

import sfml as sf

import thread

class PlayerUtils :
    '''
    Player base functions
    '''
    def __init__(self, music_file_):
        self.music_file = music_file_
        
    def __playMusicFromFile(self, music_file):
        self.music = sf.Music.from_file(music_file)
        ## Play it
        self.music.play()
        
        #loop while the sound is playing
        while self.music.status == sf.Music.PLAYING:
            #leave some cpu time for other processes
            sf.sleep(sf.milliseconds(100))

    def PlayMusic(self):
        try:
            self.__playMusicFromFile(self.music_file)
        except IOError, e:
            print "Open music file failed: {0}".format(e)

    def PauseMusic(self):
        
        self.music.pause()

    def StopMusic(self):
        self.music.stop()
        
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

