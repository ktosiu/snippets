//
//  AppDelegate.swift
//  TrackMix
//
//  Created by zouivex on 2014/6/28.
//  Copyright (c) 2014年 zouxu. All rights reserved.
//

import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    init(){
        track = Track()
        super.init()
    }
    
    @IBOutlet var window: NSWindow


    func applicationDidFinishLaunching(aNotification: NSNotification?) {
        // Insert code here to initialize your application
        updateUserInterface()
    }

    func applicationWillTerminate(aNotification: NSNotification?) {
        // Insert code here to tear down your application
    }
    
    func updateUserInterface(){
        let volume = track.volume
        textField.floatValue = volume
        slider.floatValue = volume
    }

    @IBAction func mute(sender : AnyObject) {
        track.volume = 0
        updateUserInterface()
    }

    @IBAction func takeFloatValueForVolumeFrom(sender : AnyObject) {
        track.volume = sender.floatValue
        updateUserInterface()
    }
    
    @IBOutlet var textField : NSTextField
    @IBOutlet var slider : NSSlider
    var track:Track
}

