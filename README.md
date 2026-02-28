# Okja

## Milestones:
- [X] Blink LED
- [X] Play something over DAC
- [X] Read SD Card and print the files
- [ ] Display Filestructure over the LCD
- [ ] GamePad Mapping
- [ ] Play/Pause of a fixed file
- [ ] File Selection to play
- [ ] SDCard organizer by artist/album/tracks
- [ ] Queues and Playlists
- [ ] Lidarr sync

## Architecture

```
    +-------------------------------+
    |            START              |
    |                               |
    |                               |
    |                               |                                  +--------------------------------+
    |                               |                                  |***********PLAYER_UI************|
    |                               |                                  |                                |
    |                               |                                  |1. Change the UI to player      |
    |                               |                                  |2. Show the metadata            |
    |                               |                                  |3. Play selected file over DAC  |
    |                               |                                  |                                |
    |                               |                                  +--------------------------------+
+---v----+                     +----v---+
| Player |                     |  GUI   |
|  Init  |                     |  Init  |
+--------+                     +---+----+
                                   |
                                   |                                   +--------------------------------+
                                                                       |***********LISTING_UI***********|
                                                                       |                                |
                                                                       |1. Change UI to Listing.        |
                                                                       |2. Show Metadata of hovered file.
                                                                       |3. Wait for Play                |
                                                                       |                                |
                                                                       +--------------------------------+

```

# Thanks to 
- [TobiKr](https://github.com/TobiKr) for [the display driver + lvgl template](https://github.com/TobiKr/T-Display-S3-ModernBasicTemplate)