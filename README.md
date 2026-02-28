# Okja

## Milestones:
- [X] Blink LED
- [X] Play something over DAC
- [X] Read SD Card and print the files
- [X] Display Something over LCD
- [ ] GamePad Mapping
- [ ] Display Filestructure over the LCD
- [ ] Play/Pause of a fixed file
- [ ] ListView: File Selection to play
- [ ] PlayerView
- [ ] Switch Between ListView and PlayerView
- [ ] SDCard organizer by artist/album/tracks
- [ ] Show Metadata of the file being played
- [ ] Show Album art
- [ ] Show equilizer in the player
- [ ] Queues and Playlists
- [ ] Lidarr sync

## Architecture

```ascii
                                                                                          
     ┌─────────────────────────────────────────────────────────────────────────────────┐  
     │                                GOD  THREAD                                      │  
     ▼─────────────────────────────────────────────────────────────────────────────────▼  
     │ +--------------------------------+        +--------------------------------+    │  
     │ |***********PLAYER_UI************|        |***********LISTING_UI***********|    │  
     │ |                                |        |                                |    │  
     │ |1. Change the UI to player      |        |1. Change UI to Listing.        |    │  
     │ |2. Show the metadata            |        |2. Show Metadata of hovered file.    │  
     │ |3. Play selected file over DAC  |        |3. Wait for Play                |    │  
     │ +--------------------------------+        +--------------------------------+    │  
     └───┬───────────────────────────────────┬───────────────────────────────────┬─────┘  
         │                                   │                                   │        
         │                                   │                                   │        
         │                                   │                                   │        
         │                                   │                                   │        
┌────────▼────────┐                   ┌──────▼────────┐                    ┌─────▼───────┐
│  AudioPlayBack  │                   │  FileSystem   │                    │  UI Thread  │
│      Thread     │                   │    Thread     │                    └─────────────┘
└─────────────────┘                   └───────────────┘                                   

```

# Thanks to 
- [TobiKr](https://github.com/TobiKr) for [the display driver + lvgl template](https://github.com/TobiKr/T-Display-S3-ModernBasicTemplate)